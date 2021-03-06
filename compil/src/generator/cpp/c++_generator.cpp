// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * The name of George Georgiev can not be used to endorse or
// promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: george.georgiev@hotmail.com (George Georgiev)
//

#include "generator/cpp/c++_generator.h"

#include "library/compil/package.h"

#include "language/compil/all/object_factory.h"

#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"

namespace cf = cpp::frm;

namespace compil
{

using namespace lib::compil;

const int CppGenerator::copyrightStream = 0;
const int CppGenerator::includeStream = 1;
const int CppGenerator::definitionStream = 2;
const int CppGenerator::cache1Stream = 3;
const int CppGenerator::cache2Stream = 4;

CppGenerator::CppGenerator()
{
    for (int i = 0; i <= 4; ++i)
    {
        mStreams.push_back(boost::shared_ptr<std::stringstream>(new std::stringstream()));
        mIndent.push_back(0);
    }
}

CppGenerator::~CppGenerator()
{
}

void CppGenerator::generateEnumerationValueDefinition(const EnumerationValueSPtr& pEnumerationValue)
{
    EnumerationSPtr pEnumeration = pEnumerationValue->enumeration().lock();
    TypeSPtr pParameterType = pEnumeration->parameterType().lock();
    StructureSPtr pStructure = pEnumeration->structure().lock();

    cf::TypeSPtr type;
    if (pEnumeration->cast() == CastableType::ECast::weak())
        type = impl->cppType(pParameterType);
    else if (pEnumeration->cast() == CastableType::ECast::strong())
        type = frm->cppEnumType(pEnumeration);
    else
        assert(false && "unknown enumeration cast");

    fdef()  << (cf::methodRef() << frm->constType(type)
                                << frm->cppEnumNamespace(pEnumeration)
                                << frm->methodName(pEnumerationValue->name()->value()));
    openBlock(definitionStream);
    line()  << "return ";
    if (pEnumeration->cast() == CastableType::ECast::strong())
        line()  << frm->cppInnerEnumType(pEnumeration, pStructure) << "(";
    line()  << frm->enumValueName(pEnumerationValue);
    if (pEnumeration->cast() == CastableType::ECast::strong())
        line()  << ")";
    line()  << ";";
    closeBlock(definitionStream);
    eol(definitionStream);
}

void CppGenerator::generateEnumerationDefinition(const EnumerationSPtr& pEnumeration)
{
    TypeSPtr pParameterType = pEnumeration->parameterType().lock();
    StructureSPtr pStructure = pEnumeration->structure().lock();

    cf::TypeSPtr outerType = impl->cppType(pEnumeration);
    cf::TypeSPtr innerDecoratedType = impl->cppInnerDecoratedType(pEnumeration, pStructure);

    fdef()  << (cf::constructorRef() << frm->cppEnumNamespace(pEnumeration)
                                     << frm->cppConstructorName(pEnumeration));
    eofd(definitionStream);

    line()  << ": ";

    cf::ConstructorNameSPtr constructorName = impl->inheritClass(pEnumeration, pStructure);
    cf::VariableNameSPtr variableName;
    if (!constructorName)
        variableName = frm->memberVariableName(value);

    if (pEnumeration->flags())
    {
        line()  << (cf::initializationRef() << constructorName
                                            << variableName
                                            << cf::parameterValueRef("0"));
    }
    else
    {
        std::string invalid = frm->enumValueName(Document::invalidEnumerationValue(pEnumeration));
        line()  << (cf::initializationRef() << constructorName
                                            << variableName
                                            << cf::parameterValueRef(invalid));
    }
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::constructorRef() << frm->cppEnumNamespace(pEnumeration)
                                     << frm->cppConstructorName(pEnumeration)
                                     << (cf::argumentRef() << impl->cppDecoratedType(pParameterType)
                                                           << value));
    eofd(definitionStream);

    line()  << ": "
            << (cf::initializationRef() << constructorName
                                        << variableName
                                        << frm->parameterValue(value));
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);

    if (pEnumeration->flags())
        generateEnumerationValueDefinition(Document::nilEnumerationValue(pEnumeration));
    else
        generateEnumerationValueDefinition(Document::invalidEnumerationValue(pEnumeration));

    const std::vector<EnumerationValueSPtr>& enumerationValues = pEnumeration->enumerationValues();
    std::vector<EnumerationValueSPtr>::const_iterator it;
    for (it = enumerationValues.begin(); it != enumerationValues.end(); ++it)
        generateEnumerationValueDefinition(*it);

    if (pEnumeration->flags())
        generateEnumerationValueDefinition(Document::allEnumerationValue(pEnumeration));

    fdef()  << (cf::methodRef() << impl->cppDecoratedType(pParameterType)
                                << frm->cppEnumNamespace(pEnumeration)
                                << fnValue
                                << cf::EMethodDeclaration::const_());
    openBlock(definitionStream);
    line()  << "return "
            << frm->memberName("value")
            << ";";
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << const_char_ptr
                                << frm->cppEnumNamespace(pEnumeration)
                                << fnShortName
                                << (cf::argumentRef() << impl->cppDecoratedType(pParameterType)
                                                      << value));
    openBlock(definitionStream);

    long min = pEnumeration->getMinValue();
    long max = pEnumeration->getMaxValue();
    if (!pEnumeration->flags() && (max - min < (long)enumerationValues.size() + 10))
    {
        line()  << "static const char* names[] =";
        openBlock(definitionStream);
        for (long i = 0; i <= max; ++i)
        {
            for (it = enumerationValues.begin(); it != enumerationValues.end(); ++it)
            {
                AbsoluteEnumerationValueSPtr pAbsoluteValue =
                    ObjectFactory::downcastAbsoluteEnumerationValue(*it);
                if (pAbsoluteValue->value() == i)
                {
                    line()  << "\""
                            << pAbsoluteValue->name()->value()
                            << "\",";
                    eol(definitionStream);
                    break;
                }
            }
            if (it == enumerationValues.end())
            {
                line()  << "\"\", // alignment";
                eol(definitionStream);
            }
        }
        closeBlock(definitionStream, "};");
        line()  << "return names[(size_t)value";
        if (min < 0)
        {
            line()  << " - ("
                    << boost::lexical_cast<std::string>(min)
                    << ")";
        }
        else
        if (min > 0)
        {
            line()  << " - "
                    << boost::lexical_cast<std::string>(min);
        }
        line()  << "];";
        eol(definitionStream);
    }
    else
    {
        line()  << "switch (value)";
        openBlock(definitionStream);
        for (it = enumerationValues.begin(); it != enumerationValues.end(); ++it)
        {
            EnumerationValueSPtr pEnumerationValue = *it;
            table() << TableAligner::row()
                    << "case "
                    << frm->enumValueName(pEnumerationValue)
                    << TableAligner::col()
                    << ": "
                    << "return "
                    << "\""
                    << pEnumerationValue->name()->value()
                    << "\";";
        }

        table() << TableAligner::row()
                << "default"
                << TableAligner::col()
                << ": "
                << "return "
                << "\"custom\";";
        eot(definitionStream);
        closeBlock(definitionStream);
    }
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << const_char_ptr
                                << frm->cppEnumNamespace(pEnumeration)
                                << fnShortName
                                << cf::EMethodDeclaration::const_());
    openBlock(definitionStream);
    line()  << "return "
            << (cf::functionCallRef() << fnShortName
                                      << cf::parameterValueRef("value()"))
            << ";";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    if (pEnumeration->cast() == CastableType::ECast::strong())
    {
        fdef()  << (cf::methodRef() << bl
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnOperatorEq
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << rValue)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << " == rValue."
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << bl
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnOperatorNe
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << rValue)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << " != rValue."
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);
    }
    else if (pEnumeration->cast() == CastableType::ECast::weak())
    {
        fdef()  << (cf::castOperatorRef() << frm->cppEnumNamespace(pEnumeration)
                                          << impl->cppDecoratedType(pParameterType)
                                          << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);
    }

    if (impl->implementFlagsEnumerationMethods(pEnumeration))
    {
        fdef()  << (cf::methodRef() << vd
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnReset
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << value));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " = value.value() | (this->value() & ~mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << vd
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnSet
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " |= mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << vd
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnClear
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " &= ~mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << vd
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnTurn
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " ^= mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << outerType
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnAssemble
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << value)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "("
                << " value.value() | (this->value() & ~mask.value()));";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << outerType
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnCombine
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "(value() | mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << outerType
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnIntersect
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "(value() & ~mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << outerType
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnFlip
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "(value() ^ mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << bl
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnTest
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << value)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return (this->value() & mask.value()) == value.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << bl
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnIsSet
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return (value() & mask.value()) == mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << bl
                                    << frm->cppEnumNamespace(pEnumeration)
                                    << fnIsClear
                                    << (cf::argumentRef() << innerDecoratedType
                                                          << mask)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return (value() & mask.value()) == 0;";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);
    }
}

void CppGenerator::generateSpecimenDefinition(const SpecimenSPtr& pSpecimen)
{
    SpecimenSPtr pBaseSpecimen = pSpecimen->baseSpecimen().lock();

    fdef()  << (cf::constructorRef() << frm->cppClassNamespace(pSpecimen)
                                     << frm->cppConstructorName(pSpecimen));
    line()  << ": ";
    eofd(definitionStream);

    if (pBaseSpecimen)
    {
        line()  << (cf::initializationRef() << frm->cppConstructorName(pBaseSpecimen));
    }
    else
    {
        line()  << (cf::initializationRef() << frm->memberVariableName(value));
    }
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::constructorRef() << frm->cppClassNamespace(pSpecimen)
                                     << frm->cppConstructorName(pSpecimen)
                                     << (cf::argumentRef() << impl->cppDecoratedType(pSpecimen->parameterType().lock())
                                                           << value));
    eofd(definitionStream);

    line()  << ": ";
    if (pBaseSpecimen)
    {
        line()  << (cf::initializationRef() << frm->cppConstructorName(pBaseSpecimen)
                                            << frm->parameterValue(value));
    }
    else
    {
        line()  << (cf::initializationRef() << frm->memberVariableName(value)
                                            << frm->parameterValue(value));
    }
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);
}

void CppGenerator::generateHierarchyFactoryDefinition(const FactorySPtr& pFactory)
{
    TypeSPtr pParameterType = pFactory->parameterType().lock();
    StructureSPtr pParameterStructure = ObjectFactory::downcastStructure(pParameterType);
    std::vector<StructureSPtr> structs = impl->hierarchie(mDocument,
                                                          pParameterStructure,
                                                          &Structure::hasRuntimeIdentification);
    EnumerationSPtr pEnumeration = impl->objectEnumeration(mDocument, structs, pFactory);
    generateEnumerationDefinition(pEnumeration);

    std::vector<StructureSPtr>::const_iterator it;
    for (it = structs.begin(); it != structs.end(); ++it)
    {
        StructureSPtr pStructure = *it;

        fdef()  << (cf::methodRef() << impl->identificationEnum(pParameterStructure)
                                    << frm->cppAutoClassNamespace(pStructure)
                                    << impl->staticIdentificationMethodName(pParameterStructure));
        openBlock(definitionStream);
        line()  << "return "
                << frm->cppEnumNamespace(pEnumeration)
                << "::"
                << frm->methodName(pStructure->name()->value())
                << "();";
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << impl->identificationEnum(pParameterStructure)
                                    << frm->cppAutoClassNamespace(pStructure)
                                    << impl->runtimeIdentificationMethodName(pParameterStructure)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << impl->staticIdentificationMethodName(pParameterStructure)
                << "();";
        closeBlock(definitionStream);
        eol(definitionStream);
    }

    fdef()  << (cf::methodRef() << impl->cppPtrType(pParameterType)
                                << frm->cppClassNamespace(pFactory)
                                << fnClone
                                << (cf::argumentRef() << impl->cppPtrDecoratedType(pParameterType)
                                                      << frm->ptrVariableName(object)));
    openBlock(definitionStream);
    line()  << "switch ("
            << frm->ptrVariableName(object)
            << "->"
            << impl->runtimeIdentificationMethodName(pParameterStructure)
            << "().value())";
    openBlock(definitionStream);

    for (it = structs.begin(); it != structs.end(); ++it)
    {
        StructureSPtr pStructure = *it;
        if (pStructure->abstract()) continue;

        line()  << "case "
                << frm->cppEnumNamespace(pEnumeration)
                << "::"
                << frm->enumValueName(pStructure->name()->value())
                << ":";
        openBlock(definitionStream);

        line()  << impl->cppPtrType(pStructure)
                << " pClone(new "
                << frm->cppMainClassType(pStructure)
                << "());";
        eol(definitionStream);
        if (pStructure != pParameterStructure)
        {
            line()  << "*pClone = *"
                    << frm->downcastMethodName(pStructure)
                    << "("
                    << frm->ptrVariableName(object)
                    << ");";
        }
        else
        {
            line()  << "*pClone = *"
                    << frm->ptrVariableName(object)
                    << ";";
        }
        eol(definitionStream);
        line()  << "return pClone;";
        eol(definitionStream);
        closeBlock(definitionStream);
    }
    eot(definitionStream);
    line()  << "default:";
    eol(definitionStream);
    ++mIndent[definitionStream];

    addDependency(impl->assert_dependency());
    line()  << impl->assert_method()
            << "(false && \"unknown objId\");";

    eol(definitionStream);
    --mIndent[definitionStream];

    closeBlock(definitionStream);

    line()  << "return "
            << impl->cppNullPtr(pParameterType)
            << ";";
    eol(definitionStream);

    closeBlock(definitionStream);
    eol(definitionStream);

    for (it = structs.begin(); it != structs.end(); ++it)
    {
        StructureSPtr pStructure = *it;
        if (pParameterStructure == pStructure) continue;

        fdef()  << (cf::methodRef() << impl->cppPtrType(pStructure)
                                    << frm->cppClassNamespace(pFactory)
                                    << frm->downcastMethodName(pStructure)
                                    << (cf::argumentRef() << impl->cppPtrDecoratedType(pParameterStructure)
                                                          << frm->ptrVariableName(object)));
        openBlock(definitionStream);
        line()  << "bool b = ("
                << frm->ptrVariableName(object)
                << "->"
                << impl->runtimeIdentificationMethodName(pParameterStructure)
                << "() == "
                << frm->cppMainClassNamespace(pStructure)
                << "::"
                << impl->staticIdentificationMethodName(pParameterStructure)
                << "())";

        bool bFirst = true;
        std::vector<StructureSPtr>::const_iterator itc;
        for (itc = structs.begin(); itc != structs.end(); ++itc)
        {
            StructureSPtr pChild = *itc;

            if (!pChild->isRecursivelyInherit(pStructure))
                continue;

            eol(definitionStream);
            if (bFirst)
            {
                bFirst = false;
                line()  << "      // or any of the derived classes";
                eol(definitionStream);
            }
            line()  << "      || ("
                    << frm->ptrVariableName(object)
                    << "->"
                    << impl->runtimeIdentificationMethodName(pParameterStructure)
                    << "() == "
                    << frm->cppMainClassNamespace(pChild)
                    << "::"
                    << impl->staticIdentificationMethodName(pParameterStructure)
                    << "())";
        }

        line()  << ";";
        eol(definitionStream);
        eol(definitionStream);

        line()  << "if (b)";
        eol(definitionStream);
        ++mIndent[definitionStream];
        line()  << "return boost::static_pointer_cast<"
                << frm->cppMainClassType(pStructure)
                << ">("
                << frm->ptrVariableName(object)
                << ");";
        eol(definitionStream);
        --mIndent[definitionStream];

        line()  << "return "
                << impl->cppNullPtr(pStructure)
                << ";";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);
    }
}

void CppGenerator::generateObjectFactoryDefinition(const FactorySPtr& pFactory)
{
    TypeSPtr pParameterType = pFactory->parameterType().lock();
    StructureSPtr pParameterStructure =  ObjectFactory::downcastStructure(pParameterType);

    cf::NamespaceSPtr nmspace;
    cf::MethodNameSPtr methodName;
    if (pFactory->function())
    {
        methodName = cf::methodNameRef(pFactory->name()->value());
    }
    else
    {
        nmspace = frm->cppClassNamespace(pFactory);
        methodName = fnCreate;
    }

    std::vector<compil::FieldSPtr> iteration;
    while (pParameterStructure->fieldIterate(iteration))
    {
        cf::MethodSPtr method = cf::methodRef() << impl->cppPtrType(pParameterType)
                                                << nmspace
                                                << methodName;

        std::vector<compil::FieldSPtr>::iterator it;
        for (it = iteration.begin(); it != iteration.end(); ++it)
        {
            method << (cf::argumentRef() << impl->cppSetDecoratedType((*it)->type())
                                         << frm->cppVariableName(*it));
        }

        fdef()  << method;
        openBlock(definitionStream);

        if (!pParameterStructure->immutable())
        {
            line()  << impl->cppPtrType(pParameterStructure)
                    << " pObj(new "
                    << frm->cppMainClassType(pParameterStructure)
                    << "());";
            eol(definitionStream);

            for (it = iteration.begin(); it != iteration.end(); ++it)
            {
                line()  << "pObj->"
                        << frm->setMethodName(*it)
                        << "("
                        << frm->cppVariableName(*it)
                        << ");";
                eol(definitionStream);
            }
            line()  << "return pObj;";
            eol(definitionStream);
        }
        else
        {
            line()  << frm->cppMainClassType(pParameterStructure)
                    << "::"
                    << builder
                    << " builder;";
            eol(definitionStream);

            for (it = iteration.begin(); it != iteration.end(); ++it)
            {
                FilterSPtr pFilter = pFactory->findFilter((*it)->name()->value());
                if (!pFilter)
                {
                    line()  << "builder."
                            << (cf::functionCallRef() << frm->setMethodName(*it)
                                                      << frm->cppVariableNameAsParameter(*it))
                            << ";";
                }
                else
                {
                    line()  << "builder."
                            << frm->setMethodName(*it)
                            << "("
                            << (cf::functionCallRef() << frm->cppMainClassNamespace(pParameterStructure)
                                                      << cf::functionNameRef(pFilter->method())
                                                      << frm->cppVariableNameAsParameter(*it))
                            << ");";
                }
                eol(definitionStream);
            }
            line()  << "return builder.finalize();";
            eol(definitionStream);
        }

        closeBlock(definitionStream);
        eol(definitionStream);
    }
}

void CppGenerator::generatePluginFactoryDefinition(const FactorySPtr& pFactory)
{
    fdef()  << (cf::constructorRef() << frm->cppClassNamespace(pFactory)
                                     << frm->cppConstructorName(pFactory));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::destructorRef() << frm->cppClassNamespace(pFactory)
                                    << frm->cppDestructorName(pFactory));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << bl
                                << frm->cppClassNamespace(pFactory)
                                << fnRegisterCloneFunction
                                << (cf::argumentRef() << st
                                                      << object)
                                << (cf::argumentRef() << cloneFunction
                                                      << function));
    openBlock(definitionStream);
    line()  << "get().cloneFunctions[object] = function;";
    eol(definitionStream);
    line()  << "return true;";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << bl
                                << frm->cppClassNamespace(pFactory)
                                << fnRegisterRelationship
                                << (cf::argumentRef() << st
                                                      << parent)
                                << (cf::argumentRef() << st
                                                      << child));
    openBlock(definitionStream);
    line()  << "get().relationships.insert(Pair(parent, child));";
    eol(definitionStream);
    line()  << "return true;";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << bl
                                << frm->cppClassNamespace(pFactory)
                                << fnIsParent
                                << (cf::argumentRef() << st
                                                      << parent)
                                << (cf::argumentRef() << st
                                                      << child));
    openBlock(definitionStream);
    line()  << "return get().relationships.find(Pair(parent, child)) != get().relationships.end();";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << frm->typeRef(frm->cppClassType(pFactory))
                                << frm->cppClassNamespace(pFactory)
                                << fnGet);
    openBlock(definitionStream);
    line()  << "static "
            << frm->cppClassType(pFactory)
            << " factory;";
    eol(definitionStream);
    line()  << "return factory;";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);
}

void CppGenerator::generateFactoryDefinition(const FactorySPtr& pFactory)
{
    switch (pFactory->type().value())
    {
        case Factory::EType::kHierarchy:
            generateHierarchyFactoryDefinition(pFactory);
            break;
        case Factory::EType::kObject:
            generateObjectFactoryDefinition(pFactory);
            break;
        case Factory::EType::kPlugin:
            generatePluginFactoryDefinition(pFactory);
            break;
        default:
            assert(false && "unknown factory type");
    }
}

void CppGenerator::generateIdentifierDefinition(const IdentifierSPtr& pIdentifier)
{
    TypeSPtr pParameterType = pIdentifier->parameterType().lock();

    fdef()  << (cf::constructorRef() << frm->cppClassNamespace(pIdentifier)
                                     << frm->cppConstructorName(pIdentifier));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::constructorRef() << frm->cppClassNamespace(pIdentifier)
                                     << frm->cppConstructorName(pIdentifier)
                                     << (cf::argumentRef() << impl->cppDecoratedType(pParameterType)
                                                           << value));
    eofd(definitionStream);

    line()  << ": "
            << (cf::initializationRef() << frm->memberVariableName(value)
                                        << frm->parameterValue(value));
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << impl->cppDecoratedType(pParameterType)
                                << frm->cppClassNamespace(pIdentifier)
                                << fnValue
                                << cf::EMethodDeclaration::const_());
    openBlock(definitionStream);
    line()  << "return "
            << frm->memberName("value")
            << ";";
    closeBlock(definitionStream);
    eol(definitionStream);

    if (pIdentifier->cast() == CastableType::ECast::strong())
    {
        fdef()  << (cf::methodRef() << bl
                                    << frm->cppClassNamespace(pIdentifier)
                                    << fnOperatorEq
                                    << (cf::argumentRef() << impl->cppDecoratedType(pIdentifier)
                                                          << rValue)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << " == rValue."
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << bl
                                    << frm->cppClassNamespace(pIdentifier)
                                    << fnOperatorNe
                                    << (cf::argumentRef() << impl->cppDecoratedType(pIdentifier)
                                                          << rValue)
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << " != rValue."
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);
    }
    else if (pIdentifier->cast() == CastableType::ECast::weak())
    {
        fdef()  << (cf::castOperatorRef() << frm->cppClassNamespace(pIdentifier)
                                          << impl->cppDecoratedType(pParameterType)
                                          << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);
    }
}

void CppGenerator::generateInitialization(const cpp::frm::InitializationSPtr& initialization)
{
    if (table().isEmpty())
    {
        table() << TableAligner::row()
                << ": ";
    }
    else
    {
        table() << TableAligner::row()
                << ", ";
    }
    table() << initialization;
}

void CppGenerator::generateStructureFieldMemberInitialization(const FieldSPtr& pField)
{
    if (impl->needConstructorInitialization(pField))
    {
        generateInitialization(
            cf::initializationRef() << frm->memberVariableName(frm->cppVariableName(pField))
                                    << cf::parameterValueRef(frm->defaultMethodName(pField)->value() + "()"));
    }
}

void CppGenerator::generateStructureObjectMemberInitialization(const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kField:
        {
            FieldSPtr pField = boost::static_pointer_cast<Field>(pObject);
            generateStructureFieldMemberInitialization(pField);
            break;
        }
        case EObjectId::kIdentification:
        case EObjectId::kUpcopy:
        case EObjectId::kOperator:
        case EObjectId::kEnumeration:
        case EObjectId::kAlter:
        case EObjectId::kFieldOverride:
            break;
        default:
            assert(false);
    }
}

void CppGenerator::generateStructureFieldWritingDefinition(const StructureSPtr& pStructure, const FieldSPtr& pField)
{
    StructureSPtr pBelongStructure = pField->structure().lock();
    assert(pBelongStructure);

    cf::NamespaceSPtr classNamesp = frm->cppAutoClassNamespace(pStructure);
    cf::NamespaceSPtr namesp = boost::make_shared<cf::Namespace>(*classNamesp);

    cf::NamespaceSPtr belongClassBuilderNamesp = frm->cppAutoClassNamespace(pBelongStructure);
    *belongClassBuilderNamesp << nsBuilder;

    std::string accessObject;
    cf::TypeSPtr resultType = frm->typeRef(impl->cppType(pStructure));

    std::string returnThis;
    if (!pStructure->immutable() && pStructure->partial())
        returnThis = "return *(" + frm->cppClassType(pStructure)->name()->value() + "*)this;";
    else
        returnThis = "return *this;";

    if (pStructure->immutable())
    {
        *namesp << nsBuilder;
        if (pBelongStructure->baseStructure().lock())
            accessObject = "((" + frm->cppAutoClassType(pStructure)->name()->value() + "*)"
                           + frm->memberPtrName("object") + ")->";
        else
            accessObject = frm->memberPtrName("object") + "->";

        resultType = cf::typeRef() << classNamesp
                                   << builder->name()
                                   << cf::ETypeDecoration::reference();
    }

    if ((!pStructure->immutable() || pStructure->isBuildable()) && !pStructure->isOverriden(pField))
    {
        fdef()  << (cf::methodRef() << resultType
                                    << namesp
                                    << frm->setMethodName(pField)
                                    << (cf::argumentRef() << impl->cppInnerSetDecoratedType(pField->type(), pStructure)
                                                          << frm->cppVariableName(pField)));
        openBlock(definitionStream);

        if (pStructure == pBelongStructure)
        {
            table() << TableAligner::row()
                    << accessObject
                    << frm->cppMemberName(pField)
                    << ' '
                    << TableAligner::col()
                    << TableAligner::col()
                    << "= "
                    << TableAligner::col()
                    << frm->cppVariableName(pField)
                    << ";";

            if (pStructure->controlled())
            {
                table() << TableAligner::row()
                        << accessObject
                        << frm->memberName("bits")
                        << " "
                        << TableAligner::col()
                        << "|"
                        << TableAligner::col()
                        << "= "
                        << TableAligner::col()
                        << (cf::functionCallRef() << frm->bitmaskMethodName(pField))
                        << ";";
            }
            eot(definitionStream);

            line()  << returnThis;
            eol(definitionStream);
        }
        else
        {
            if (pStructure->isBuildable())
            {
                line()  << "return ("
                        << (cf::typeRef() << classNamesp
                                          << builder->name()
                                          << cf::ETypeDecoration::reference())
                        << ")"
                        << (cf::functionCallRef() << belongClassBuilderNamesp
                                                  << frm->setMethodName(pField)
                                                  << frm->cppVariableNameAsParameter(pField))
                        << ";";
                eol(definitionStream);
            }
            else
            {
                line()  << (cf::functionCallRef() << frm->cppAutoClassNamespace(pBelongStructure)
                                                  << frm->setMethodName(pField)
                                                  << frm->cppVariableNameAsParameter(pField))
                        << ";";
                eol(definitionStream);

                line()  << returnThis;
                eol(definitionStream);
            }
        }
        closeBlock(definitionStream);
        eol(definitionStream);

        if (impl->needMutableMethod(pField, pStructure))
        {
            fdef()  << (cf::methodRef() << (frm->typeRef(impl->cppType(pField->type())))
                                        << namesp
                                        << frm->mutableMethodName(pField));
            openBlock(definitionStream);

            if (pStructure->controlled())
            {
                line()  << accessObject
                        << frm->memberName("bits")
                        << " |= "
                        << (cf::functionCallRef() << frm->bitmaskMethodName(pField))
                        << ";";
                eol(definitionStream);
            }
            line()  << "return "
                    << accessObject
                    << frm->cppMemberName(pField)
                    << ";";

            closeBlock(definitionStream);
            eol(definitionStream);
        }

        if (pStructure->streamable())
        {
            cf::TypeSPtr belongType = cf::typeRef();
            if (pStructure->isBuildable())
            {
                belongType << frm->cppAutoClassNamespace(pBelongStructure)
                           << builder->name();
            }
            else
            {
                belongType << frm->cppClassType(pBelongStructure)->name();
            }

            fdef()  << (cf::methodRef() << resultType
                                        << namesp
                                        << fnOperatorStore
                                        << (cf::argumentRef() << impl->cppInnerSetDecoratedType(pField->type(),
                                                                                                pStructure)
                                                              << frm->cppVariableName(pField)));
            openBlock(definitionStream);

            if (pStructure == pBelongStructure)
            {
                line()  << "return "
                        << frm->setMethodName(pField)
                        << "("
                        << frm->cppVariableName(pField)
                        << ");";
                eol(definitionStream);
            }
            else
            {
                line()  << "*("
                        << belongType
                        << "*)this << "
                        << frm->cppVariableName(pField)
                        << ";";

                eol(definitionStream);

                line()  << returnThis;
                eol(definitionStream);
            }

            closeBlock(definitionStream);
            eol(definitionStream);

            cf::TypeSPtr reference = impl->cppPtrDecoratedType(pStructure);

            if (!pStructure->immutable())
            {
                addDependency(impl->assert_dependency());

                fdef()  << (cf::methodRef() << reference
                                            << fnOperatorStore
                                            << (cf::argumentRef() << reference
                                                                  << object)
                                            << (cf::argumentRef() << impl->cppSetDecoratedType(pField->type())
                                                                  << frm->cppVariableName(pField)));
                openBlock(definitionStream);

                line()  << impl->assert_method()
                        << "(object);";
                eol(definitionStream);

                line()  << "*object << "
                        << frm->cppVariableName(pField)
                        << ";";
                eol(definitionStream);

                line()  << "return object;";
                eol(definitionStream);

                closeBlock(definitionStream);
                eol(definitionStream);
            }

            UnaryContainerSPtr pUnaryContainer = ObjectFactory::downcastUnaryContainer(pField->type());
            if (pUnaryContainer)
            {
                cf::TypeSPtr type = impl->cppInnerSetDecoratedType(pUnaryContainer->parameterType().lock(),
                                                                   pStructure);
                fdef()  << (cf::methodRef() << resultType
                                            << namesp
                                            << fnOperatorStore
                                            << (cf::argumentRef() << type
                                                                  << frm->cppItemVariableName(pField)));
                openBlock(definitionStream);

                if (pStructure == pBelongStructure)
                {
                    if (pStructure->controlled())
                    {
                        line()  << accessObject
                                << frm->memberName("bits")
                                << " |= "
                                << (cf::functionCallRef() << frm->bitmaskMethodName(pField))
                                << ";";
                        eol(definitionStream);
                    }
                    line()  << accessObject
                            << frm->cppMemberName(pField)
                            << ".push_back("
                            << frm->cppVariableName(pField)
                            << "Item"
                            << ");";
                    eol(definitionStream);
                }
                else
                {
                    line()  << "*("
                            << belongType
                            << "*)this << "
                            << frm->cppVariableName(pField)
                            << "Item"
                            << ";";
                    eol(definitionStream);
                }

                line()  << returnThis;
                eol(definitionStream);

                closeBlock(definitionStream);
                eol(definitionStream);

                if (!pStructure->immutable())
                {
                    cf::TypeSPtr type = impl->cppInnerSetDecoratedType(pUnaryContainer->parameterType().lock(),
                                                                       pStructure);
                    fdef()  << (cf::methodRef() << reference
                                                << fnOperatorStore
                                                << (cf::argumentRef() << reference
                                                                      << object)
                                                << (cf::argumentRef() << type
                                                                      << frm->cppItemVariableName(pField)));
                    openBlock(definitionStream);

                    line()  << impl->assert_method()
                            << "(object);";
                    eol(definitionStream);

                    line()  << "*object << "
                            << frm->cppVariableName(pField)
                            << "Item"
                            << ";";
                    eol(definitionStream);

                    line()  << "return object;";
                    eol(definitionStream);

                    closeBlock(definitionStream);
                    eol(definitionStream);
                }
            }
        }
    }

    if (pStructure == pBelongStructure)
    {
        if (pStructure->controlled())
        {
            if (  pField->defaultValue()
                && !pField->defaultValue()->optional())
            {
                cf::TypeSPtr type = impl->cppInnerSetDecoratedType(pField->type(),
                                                                   pStructure);

                fdef()  << (cf::methodRef() << resultType
                                            << namesp
                                            << frm->updateMethodName(pField)
                                            << (cf::argumentRef() << type
                                                                  << frm->cppVariableName(pField)));
                openBlock(definitionStream);

                if (pStructure == pBelongStructure)
                {
                    line()  << "if ("
                            << accessObject
                            << frm->defaultMethodName(pField)
                            << "() != "
                            << frm->cppVariableName(pField)
                            << ")";
                    eol(definitionStream);

                    line()  << "return "
                            << frm->setMethodName(pField)
                            << "("
                            << frm->cppVariableName(pField)
                            << ");";
                    eol(definitionStream, 1);

                    eol(definitionStream);

                    line()  << frm->resetMethodName(pField)
                            << "();";
                    eol(definitionStream);

                    line()  << returnThis;
                    eol(definitionStream);
                }
                else
                {
                    line()  << "return ("
                            << (cf::typeRef() << classNamesp
                                              << builder->name()
                                              << cf::ETypeDecoration::reference())
                            << ")"
                            << (cf::functionCallRef() << belongClassBuilderNamesp
                                                      << frm->updateMethodName(pField)
                                                      << frm->cppVariableNameAsParameter(pField))
                            << ";";
                    eol(definitionStream);
                }
                closeBlock(definitionStream);
                eol(definitionStream);
            }

            fdef()  << (cf::methodRef() << vd
                                        << namesp
                                        << frm->destroyMethodName(pField));
            openBlock(definitionStream);

            if (pField->defaultValue() && !pField->defaultValue()->optional())
            {
                table() << TableAligner::row()
                        << accessObject
                        << frm->cppMemberName(pField)
                        << " "
                        << TableAligner::col()
                        << TableAligner::col()
                        << "= "
                        << TableAligner::col()
                        << TableAligner::col()
                        << accessObject
                        << (cf::functionCallRef() << frm->defaultMethodName(pField))
                        << ";";
            }
            else
            {
                switch (pField->type()->runtimeObjectId().value())
                {
                    case EObjectId::kType:
                        if (pField->type()->name()->value() == "string")
                        {
                            switch (impl->mConfiguration->mString)
                            {
                                case ImplementerConfiguration::use_char_pointer:
                                    table() << TableAligner::row()
                                            << accessObject
                                            << frm->cppMemberName(pField)
                                            << " "
                                            << TableAligner::col()
                                            << TableAligner::col()
                                            << "= "
                                            << TableAligner::col()
                                            << TableAligner::col()
                                            << "\"\";";
                                    break;
                                case ImplementerConfiguration::use_stl_string:
                                    table() << TableAligner::row_line()
                                            << accessObject
                                            << frm->cppMemberName(pField)
                                            << ".clear();";
                                    break;
                                default: assert(false && "unknown string implementation type");
                            }
                        }
                        if (pField->type()->package())
                        {
                            if (pField->type()->name()->value() == "datetime")
                            {
                                if (pField->type()->package() == CompilPackage::time())
                                {
                                    table() << TableAligner::row()
                                            << accessObject
                                            << frm->cppMemberName(pField)
                                            << " "
                                            << TableAligner::col()
                                            << TableAligner::col()
                                            << "= "
                                            << TableAligner::col()
                                            << TableAligner::col()
                                            << "boost::posix_time::not_a_date_time;";
                                }
                            }
                        }
                        break;
                    case EObjectId::kEnumeration:
                        table() << TableAligner::row()
                                << accessObject
                                << frm->cppMemberName(pField)
                                << " "
                                << TableAligner::col()
                                << TableAligner::col()
                                << "= "
                                << TableAligner::col()
                                << TableAligner::col()
                                << impl->cppType(pField->type())
                                << "::invalid();";
                        break;
                    case EObjectId::kFactory:
                    case EObjectId::kIdentifier:
                    case EObjectId::kSpecimen:
                    case EObjectId::kStructure:
                        table() << TableAligner::row()
                                << accessObject
                                << frm->cppMemberName(pField)
                                << " "
                                << TableAligner::col()
                                << TableAligner::col()
                                << "= "
                                << TableAligner::col()
                                << TableAligner::col()
                                << impl->cppType(pField->type())
                                << "();";
                        break;
                    case EObjectId::kInteger:
                        table() << TableAligner::row()
                                << accessObject
                                << frm->cppMemberName(pField)
                                << " "
                                << TableAligner::col()
                                << TableAligner::col()
                                << "= "
                                << TableAligner::col()
                                << TableAligner::col()
                                << "0;";
                        break;

                    case EObjectId::kReference:
                        switch (impl->mConfiguration->mPointer)
                        {
                            case ImplementerConfiguration::use_raw_pointers:
                                table() << TableAligner::row()
                                        << accessObject
                                        << frm->cppMemberName(pField)
                                        << " "
                                        << TableAligner::col()
                                        << TableAligner::col()
                                        << "= "
                                        << TableAligner::col()
                                        << TableAligner::col()
                                        << impl->null()
                                        << ";";
                                break;
                            case ImplementerConfiguration::use_boost_pointers:
                                table() << TableAligner::row_line()
                                        << accessObject
                                        << frm->cppMemberName(pField)
                                        << ".reset();";
                                break;
                            default: assert(false && "unknown pointer type");
                                break;
                        }
                        break;

                    case EObjectId::kUnaryContainer:
                        table() << TableAligner::row_line()
                                << accessObject
                                << frm->cppMemberName(pField)
                                << ".clear();";
                        break;

                    default:
                        BOOST_ASSERT(false && "unknown type objId");
                }
            }

            table() << TableAligner::row()
                    << accessObject
                    << frm->memberName("bits")
                    << " "
                    << TableAligner::col()
                    << "&"
                    << TableAligner::col()
                    << "= "
                    << TableAligner::col()
                    << "~"
                    << TableAligner::col()
                    << (cf::functionCallRef() << frm->bitmaskMethodName(pField))
                    << ";";
            eot(definitionStream);

            closeBlock(definitionStream);
            eol(definitionStream);
        }
    }
}

void CppGenerator::generateStructureFieldConstantDefinition(const StructureSPtr& pStructure,
                                                            const FieldSPtr& pField,
                                                            const Type::ELiteral literal,
                                                            const DefaultValueSPtr& pDefaultValue)
{
    fdef()  << (cf::methodRef() << impl->cppType(pField->type())
                                << frm->cppAutoClassNamespace(pStructure)
                                << frm->constantMethodName(pStructure, pField));

    openBlock(definitionStream);
    if (pDefaultValue->value() == "null")
    {
        line()  << "static "
                << impl->cppType(pField->type())
                << " defaultObject;";
        eol(definitionStream);
        line()  << "return defaultObject;";
        eol(definitionStream);
    }
    else if (pDefaultValue->value() == "empty")
    {
        line()  << "static "
                << impl->cppType(pField->type())
                << " defaultObject;";
        eol(definitionStream);
        line()  << "return defaultObject;";
        eol(definitionStream);
    }
    else if (pField->type()->runtimeObjectId() == EObjectId::enumeration())
    {
        EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pField->type());
        line() << "return "
               << frm->cppEnumNamespace(pEnumeration)
               << "::"
               << pDefaultValue->value()
               << "();";
    }
    else if (pField->type()->runtimeObjectId() == EObjectId::specimen())
    {
        line()  << "return "
                << impl->cppType(pField->type())
                << "("
                << frm->defaultValue(literal, pDefaultValue->value())
                << ");";
        eol(definitionStream);
    }
    else
    {
        line() << "return "
                << frm->defaultValue(literal, pDefaultValue->value())
                << ";";
        eol(definitionStream);
    }
    closeBlock(definitionStream);
    eol(definitionStream);
}

void CppGenerator::generateStructureFieldDefinition(const FieldSPtr& pField)
{
    StructureSPtr pStructure = pField->structure().lock();
    assert(pStructure);

    fdef()  << (cf::methodRef() << impl->cppDecoratedType(pField->type())
                                << frm->cppAutoClassNamespace(pStructure)
                                << frm->getMethodName(pField)
                                << cf::EMethodDeclaration::const_());

    openBlock(definitionStream);

    if (pStructure->controlled())
    {
        if (!pField->defaultValue() || pField->defaultValue()->optional())
        {
            addDependency(impl->assert_dependency());
            line() << impl->assert_method()
                   << "("
                   << frm->availableMethodName(pField)
                   << "());";
            eol(definitionStream);
        }
    }
    line()  << "return "
            << impl->cppGetReturn(pField)
            << ";";
    eol(definitionStream);

    closeBlock(definitionStream);
    eol(definitionStream);

    if (pStructure->controlled())
    {
        fdef()  << (cf::methodRef() << bl
                                    << frm->cppAutoClassNamespace(pStructure)
                                    << frm->availableMethodName(pField)
                                    << cf::EMethodDeclaration::const_());

        openBlock(definitionStream);

        line()  << "return ("
                << frm->memberName("bits")
                << " & "
                << (cf::functionCallRef() << frm->bitmaskMethodName(pField))
                << ") != 0;";
        eol(definitionStream);

        closeBlock(definitionStream);
        eol(definitionStream);
    }

    if (pField->defaultValue() && !pField->defaultValue()->optional())
    {
        generateStructureFieldConstantDefinition(pStructure,
                                                 pField,
                                                 pField->type()->literal(),
                                                 pField->defaultValue());
    }

    generateStructureFieldWritingDefinition(pStructure, pField);
}

void CppGenerator::generateStructureFieldOverrideDefinition(const FieldOverrideSPtr& pFieldOverride)
{
    const FieldSPtr& pField = pFieldOverride->field();
    StructureSPtr pStructure = pField->structure().lock();

    ReferenceSPtr pReference = ObjectFactory::downcastReference(pField->type());

    fdef()  << (cf::methodRef() << impl->cppType(pField->type())
                                << frm->cppAutoClassNamespace(pStructure)
                                << frm->getMethodName(pField)
                                << cf::EMethodDeclaration::const_());

    openBlock(definitionStream);
    line() << "return boost::static_pointer_cast<"
           << impl->cppType(pReference->parameterType().lock())
           << ">("
           << frm->cppAutoClassNamespace(pFieldOverride->overriddenField()->structure().lock())
           << "::"
           << frm->getMethodName(pField)
           << "());";
    closeBlock(definitionStream);
    eol(definitionStream);

    cf::NamespaceSPtr classNamesp = frm->cppAutoClassNamespace(pStructure);
    cf::NamespaceSPtr namesp = boost::make_shared<cf::Namespace>(*classNamesp);

    cf::TypeSPtr resultType;
    if (pStructure->immutable())
    {
        resultType = cf::typeRef() << classNamesp
                                   << builder->name()
                                   << cf::ETypeDecoration::reference();
        *namesp << nsBuilder;
    }
    else
    {
        resultType = frm->typeRef(impl->cppType(pStructure));
    }

    fdef()  << (cf::methodRef() << resultType
                                << namesp
                                << frm->setMethodName(pField)
                                << (cf::argumentRef() << impl->cppInnerSetDecoratedType(pField->type(), pStructure)
                                                      << frm->cppVariableName(pField)));

    openBlock(definitionStream);
    line()  << frm->cppAutoClassNamespace(pFieldOverride->overriddenField()->structure().lock())
            << "::";
    if (pStructure->immutable())
    {
        line()  << nsBuilder->value()
                << "::";
    }
    line()  << frm->setMethodName(pField)
            << "("
            << frm->cppVariableName(pField)
            << ");";
    eol(definitionStream);
    line() << "return *this;";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);
}

void CppGenerator::generateStructureIdentificationMethodsDefinition(
        const IdentificationSPtr& pIdentification)
{
    switch (pIdentification->type().value())
    {
        case Identification::EType::kRuntime:
            generateStructureRuntimeIdentificationMethodsDefinition(pIdentification);
            break;
        case Identification::EType::kInproc:
            generateStructureInprocIdentificationMethodsDefinition(pIdentification);
            break;
        default:
            assert(false);
    }
}

void CppGenerator::generateStructureRuntimeIdentificationMethodsDefinition(
                    const IdentificationSPtr& pIdentification)
{
    // do nothing - this method will be generated in the hierarchy factory class
}

void CppGenerator::generateStructureInprocIdentificationMethodsDefinition(
                    const IdentificationSPtr& pIdentification)
{
    StructureSPtr pStructure = pIdentification->structure().lock();

    std::vector<FactorySPtr> factories = mDocument->findPluginFactories(pStructure);
    if (!pStructure->abstract())
    {
        for (std::vector<FactorySPtr>::iterator it = factories.begin(); it != factories.end(); ++it)
        {
            const FactorySPtr& factory = *it;
            StructureSPtr pParameterType = Structure::downcast(factory->parameterType().lock());

            fdef()  << (cf::methodRef() << frm->cppRawPtrDecoratedType(pParameterType)
                                        << frm->cppAutoClassNamespace(pStructure)
                                        << fnClone
                                        << (cf::argumentRef() << impl->cppDecoratedType(pParameterType)
                                                              << object));
            openBlock(definitionStream);
            line()  << "return new "
                    << impl->cppType(pStructure)
                    << "(("
                    << impl->cppDecoratedType(pStructure)
                    << ")object);";
            eol(definitionStream);
            closeBlock(definitionStream);
            eol(definitionStream);
        }
    }

    bool first = true;
    for (std::vector<FactorySPtr>::iterator it = factories.begin(); it != factories.end(); ++it)
    {
        const FactorySPtr& factory = *it;
        addDependencies(impl->dependencies(factory));

        StructureSPtr pParameterType = Structure::downcast(factory->parameterType().lock());

        StructureSPtr base = pStructure->baseStructure().lock();

        if (first && (base || !pStructure->abstract()))
        {
            line()  << "bool g_init_"
                    << frm->cppMainClassType(pStructure)
                    << " =";
            eol(definitionStream);
        }

        if (!pStructure->abstract())
        {
            table() << TableAligner::row()
                    << (first ? "" : "&& ")
                    << TableAligner::col()
                    << impl->cppType(factory)
                    << "::"
                    << fnRegisterCloneFunction
                    << TableAligner::col()
                    << "("
                    << frm->cppMainClassType(pStructure)
                    << "::"
                    << impl->staticMethodName(fnInprocId->value())
                    << "(), "
                    << TableAligner::col()
                    << "&"
                    << frm->cppMainClassType(pStructure)
                    << "::"
                    << fnClone
                    << ")";
            first = false;
        }

        while (base)
        {
            table() << TableAligner::row()
                    << (first ? "" : "&& ")
                    << TableAligner::col()
                    << impl->cppType(factory)
                    << "::"
                    << fnRegisterRelationship
                    << TableAligner::col()
                    << "("
                    << frm->cppMainClassType(base)
                    << "::"
                    << impl->staticMethodName(fnInprocId->value())
                    << "(), "
                    << TableAligner::col()
                    << frm->cppMainClassType(pStructure)
                    << "::"
                    << impl->staticMethodName(fnInprocId->value())
                    << "())";

            first = false;

            if (base == pParameterType)
                break;

            base = base->baseStructure().lock();
        }
    }
    if (!first)
    {
        table()  << ";";

        eot(definitionStream, 1);
        eol(definitionStream);
    }

    fdef()  << (cf::methodRef() << st
                                << frm->cppAutoClassNamespace(pStructure)
                                << impl->staticMethodName(fnInprocId->value()));
    openBlock(definitionStream);
    line()  << "return (size_t)\"";
    if (pStructure->package())
    {
        const std::vector<PackageElementSPtr>& elements = pStructure->package()->levels();
        for(std::vector<PackageElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        {
            const PackageElementSPtr& element = *it;
            line()  << element->value()
                    << ".";
        }
    }
    line()  << pStructure->name()->value()
            << "\";";
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::methodRef() << st
                                << frm->cppAutoClassNamespace(pStructure)
                                << impl->runtimeMethodName(fnInprocId->value())
                                << cf::EMethodDeclaration::const_());
    openBlock(definitionStream);
    line()  << "return "
            << impl->staticMethodName(fnInprocId->value())
            << "();";
    closeBlock(definitionStream);
    eol(definitionStream);
}

std::string CppGenerator::computeStructureOperatorExpression(
                    const TypeSPtr& pType,
                    const EOperatorAction& action,
                    const EOperatorFlags& flags,
                    const EOperatorFlags& stopFlags,
                    const std::string& cast,
                    const std::string& method,
                    bool reverse)
{
    std::string native;
    cf::FunctionNameSPtr fnFunction;
    if (action == EOperatorAction::equalTo())
    {
        native = "==";
        fnFunction = fnFunctionalOperatorEq;
    }
    else
    if (action == EOperatorAction::notEqualTo())
    {
        native = "!=";
        fnFunction = fnFunctionalOperatorEq;
    }
    else
    if (action == EOperatorAction::lessThan())
    {
        native = "<";
        fnFunction = fnFunctionalOperatorLt;
    }
    else
    {
        assert(false && "unknown operator action");
    }

    std::string object1;
    std::string object2;
    if (flags.isClear(EOperatorFlags::member()) || flags.isSet(EOperatorFlags::functor()))
    {
        object1 = "object1";
        object2 = "object2";
    }
    else
    {
        if (flags.isSet(EOperatorFlags::object()))
            object1 = "*this";
        else
            object1 = "this";
        object2 = "object";
    }

    EOperatorFlags refflags;
    for (int l = 0; l < 3; ++l)
    {
        switch (l)
        {
            case 0: refflags.reset(EOperatorFlags::location(), EOperatorFlags::member()); break;
            case 1: refflags.reset(EOperatorFlags::location(), EOperatorFlags::internal()); break;
            case 2: refflags.reset(EOperatorFlags::location(), EOperatorFlags::external()); break;
        }
        for (int d = 0; d < 3; ++d)
        {
            switch (d)
            {
                case 0: refflags.reset(EOperatorFlags::declaration(), EOperatorFlags::native()); break;
                case 1: refflags.reset(EOperatorFlags::declaration(), EOperatorFlags::function()); break;
                case 2: refflags.reset(EOperatorFlags::declaration(), EOperatorFlags::functor()); break;
            }

            for (int p = 0; p < 2; ++p)
            {
                switch (p)
                {
                    case 0: refflags.reset(EOperatorFlags::parameter(), EOperatorFlags::object()); break;
                    case 1: refflags.reset(EOperatorFlags::parameter(), EOperatorFlags::reference()); break;
                }

                if (refflags == stopFlags)
                    return "";

                if (pType->hasOperator(action, refflags))
                {
                    if (refflags.isSet(EOperatorFlags::object()) && flags.isSet(EOperatorFlags::reference()))
                    {
                        object1 = "*" + object1;
                        object2 = "*" + object2;
                    }

                    if (reverse)
                    {
                        std::string object = object1;
                        object1 = object2;
                        object2 = object;
                    }

                    if (cast.empty())
                    {
                        if (!method.empty())
                        {
                            if (object1 == "*this")
                                object1 = method;
                            else
                                object1 += "." + method;

                            if (object2 == "*this")
                                object2 = method;
                            else
                                object2 += "." + method;
                        }
                    }
                    else
                    {
                        object1 = cast + object1;
                        object2 = cast + object2;
                    }

                    std::stringstream result;
                    if (refflags.isSet(EOperatorFlags::native()))
                    {
                        result  << object1
                                << " "
                                << native
                                << " "
                                << object2;
                    }
                    else
                    if (refflags.isSet(EOperatorFlags::member()) && flags.isSet(EOperatorFlags::member()))
                    {
                        if (!cast.empty())
                            result << "("
                                   << object1
                                   << ").";

                        result  << fnFunction->value()
                                << "("
                                << object2
                                << ")";
                    }
                    else
                    if (refflags.isSet(EOperatorFlags::functor()))
                    {
                        result  << fnFunction->value()
                                << "()("
                                << object1
                                << ", "
                                << object2
                                << ")";
                    }
                    return result.str();
                }
            }
        }
    }
    return "";
}

bool CppGenerator::generateStructureOperatorAction(
                    const TypeSPtr& pType,
                    const EOperatorAction& action,
                    const EOperatorFlags& flags,
                    const EOperatorFlags& stopFlags,
                    const std::string& cast,
                    const std::string& method,
                    bool silent)
{
    if (action == EOperatorAction::equalTo())
    {
        std::string expression =
                computeStructureOperatorExpression(pType,
                                                   EOperatorAction::equalTo(),
                                                   flags,
                                                   EOperatorFlags(),
                                                   "",
                                                   method);

        std::string nexpression =
            computeStructureOperatorExpression(pType,
                                               EOperatorAction::notEqualTo(),
                                               flags,
                                               EOperatorFlags(),
                                               "",
                                               method);

        if (expression.empty() && nexpression.empty())
        {
            if (!silent)
            {
                line()  << "// can not compare "
                        << pType->name()->value();
                eol(definitionStream);
            }
            return false;
        }

        if (expression.empty())
            expression = "!(" + nexpression + ")";

        if (nexpression.empty())
            nexpression = "!(" + expression + ")";

        *mStreams[definitionStream] << mStreams[cache1Stream]->str();
        mStreams[cache1Stream]->str("");

        line()  << "if ("
                << nexpression
                << ") return false;";
        eol(cache1Stream, mIndent[definitionStream]);

        mStreams[cache2Stream]->str("");
        line()  << "return "
                << expression
                << ";";
        eol(cache2Stream, mIndent[definitionStream]);
        return true;
    }
    else
    if (action == EOperatorAction::lessThan())
    {
        std::string expression =
            computeStructureOperatorExpression(pType,
                                               EOperatorAction::lessThan(),
                                               flags,
                                               EOperatorFlags(),
                                               "",
                                               method);

        if (expression.empty())
        {
            if (!silent)
            {
                line()  << "// can not compare "
                        << pType->name()->value();
                eol(definitionStream);
            }
            return false;
        }

        *mStreams[definitionStream] << mStreams[cache1Stream]->str();
        mStreams[cache1Stream]->str("");

        line()  << "if ("
                << expression
                << ") return true;";
        eol(cache1Stream, mIndent[definitionStream]);

        expression =
            computeStructureOperatorExpression(pType,
                                               EOperatorAction::lessThan(),
                                               flags,
                                               EOperatorFlags(),
                                               "",
                                               method,
                                               true);
        line()  << "if ("
                << expression
                << ") return false;";
        eol(cache1Stream, mIndent[definitionStream]);

        mStreams[cache2Stream]->str("");
        line()  << "return "
                << expression
                << ";";
        eol(cache2Stream, mIndent[definitionStream]);

        return true;
    }
    return false;
}

void CppGenerator::generateStructureOperatorObjects(
                    const StructureSPtr& pStructure,
                    const OperatorSPtr& pOperator,
                    const EOperatorFlags& flags)
{
    const std::vector<ObjectSPtr>& objects = pStructure->objects();
    std::vector<ObjectSPtr>::const_iterator it;

    for (it = objects.begin(); it != objects.end(); ++it)
    {
        FieldSPtr pField = ObjectFactory::downcastField(*it);
        if (!pField) continue;

        std::string method = frm->getMethodName(pField)->value() + "()";

        generateStructureOperatorAction(pField->type(),
                                        pOperator->action(),
                                        flags,
                                        EOperatorFlags(),
                                        "",
                                        method,
                                        false);
    }
}

void CppGenerator::generateStructureOperatorBaseStructure(
                    const StructureSPtr& pStructure,
                    const OperatorSPtr& pOperator,
                    const EOperatorFlags& flags)
{
    StructureSPtr pBaseStructure = pStructure->baseStructure().lock();
    if (!pBaseStructure)
        return;

    std::string cast = "(" + impl->cppType(pBaseStructure)->name()->value() + ")";

    if (generateStructureOperatorAction(pBaseStructure,
                                        pOperator->action(),
                                        flags,
                                        EOperatorFlags(),
                                        cast,
                                        "",
                                        true))
    {
        return;
    }

    generateStructureOperatorBaseStructure(pBaseStructure, pOperator, flags);
    generateStructureOperatorObjects(pBaseStructure, pOperator, flags);
}

void CppGenerator::generateStructureOperatorMethodsDefinition(
        const OperatorSPtr& pOperator,
        const EOperatorFlags& flags)
{
    if (!pOperator->flags().isSet(flags))
        return;

    cf::MethodNameSPtr fnOperator;
    cf::MethodNameSPtr fnFunction;
    if (pOperator->action() == EOperatorAction::equalTo())
    {
        fnOperator = fnOperatorEq;
        fnFunction = fnFunctionalOperatorEq;
    }
    else
    if (pOperator->action() == EOperatorAction::lessThan())
    {
        fnOperator = fnOperatorLt;
        fnFunction = fnFunctionalOperatorLt;
    }
    else
    {
        assert(false && "unknown operator action");
    }

    cf::MethodNameSPtr fnName;
    if (flags.isSet(EOperatorFlags::functor()))
    {
        fnName = fnOperatorFn;
    }
    else
    {
        if (flags.isSet(EOperatorFlags::native()))
            fnName = fnOperator;
        else
            fnName = fnFunction;
    }

    StructureSPtr pStructure = pOperator->structure().lock();

    cf::NamespaceSPtr nmspace = frm->cppAutoClassNamespace(pStructure);
    if (flags.isSet(EOperatorFlags::functor()))
        *nmspace << cf::namespaceNameRef(fnFunction->value());

    int arguments;
    if (flags.isClear(EOperatorFlags::member()) || flags.isSet(EOperatorFlags::functor()))
        arguments = 2;
    else
        arguments = 1;

    cf::TypeSPtr type;
    if (flags.isSet(EOperatorFlags::object()))
        type = impl->cppDecoratedType(pStructure);
    else
    if (flags.isSet(EOperatorFlags::reference()))
        type = impl->cppPtrDecoratedType(pStructure);
    else
        assert(false && "unknown operator parameter");

    cf::EMethodDeclaration declaration;
    if (flags.isSet(EOperatorFlags::member()) || flags.isSet(EOperatorFlags::functor()))
        declaration = cf::EMethodDeclaration::const_();

    if (arguments == 1)
    {
        fdef()  << (cf::methodRef() << bl
                                    << nmspace
                                    << fnName
                                    << (cf::argumentRef() << type
                                                          << object)
                                    << declaration);
    }
    else
    {
        fdef()  << (cf::methodRef() << bl
                                    << nmspace
                                    << fnName
                                    << (cf::argumentRef() << type
                                                          << object1)
                                    << (cf::argumentRef() << type
                                                          << object2)
                                    << declaration);
    }

    openBlock(definitionStream);

    std::string expression =
        computeStructureOperatorExpression(pStructure,
                                           pOperator->action(),
                                           flags,
                                           flags,
                                           "",
                                           "");

    if (expression.empty())
    {
        if (pOperator->action() == EOperatorAction::equalTo())
            line()  << "return true;";
        else
        if (pOperator->action() == EOperatorAction::lessThan())
            line()  << "return false;";
        eol(cache2Stream, mIndent[definitionStream]);

        generateStructureOperatorBaseStructure(pStructure, pOperator, flags);
        generateStructureOperatorObjects(pStructure, pOperator, flags);
        *mStreams[definitionStream] << mStreams[cache2Stream]->str();
        mStreams[cache1Stream]->str("");
        mStreams[cache2Stream]->str("");
    }
    else
    {
        line()  << "return "
                << expression
                << ";";
    }

    closeBlock(definitionStream);
    eol(definitionStream);
}

void CppGenerator::generateStructureOperatorMethodsDefinition(
        const OperatorSPtr& pOperator)
{
    EOperatorFlags flags;
    for (int l = 0; l < 3; ++l)
    {
        switch (l)
        {
            case 0: flags.reset(EOperatorFlags::location(), EOperatorFlags::member()); break;
            case 1: flags.reset(EOperatorFlags::location(), EOperatorFlags::internal()); break;
            case 2: flags.reset(EOperatorFlags::location(), EOperatorFlags::external()); break;
        }
        for (int d = 0; d < 3; ++d)
        {
            switch (d)
            {
                case 0: flags.reset(EOperatorFlags::declaration(), EOperatorFlags::native()); break;
                case 1: flags.reset(EOperatorFlags::declaration(), EOperatorFlags::function()); break;
                case 2: flags.reset(EOperatorFlags::declaration(), EOperatorFlags::functor()); break;
            }

            for (int p = 0; p < 2; ++p)
            {
                switch (p)
                {
                    case 0: flags.reset(EOperatorFlags::parameter(), EOperatorFlags::object()); break;
                    case 1: flags.reset(EOperatorFlags::parameter(), EOperatorFlags::reference()); break;
                }

                generateStructureOperatorMethodsDefinition(pOperator, flags);
            }
        }
    }
}

void CppGenerator::generateStructureObjectDefinition(const StructureSPtr& pStructure,
                                                     const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kField:
        {
            FieldSPtr pField = boost::static_pointer_cast<Field>(pObject);
            generateStructureFieldDefinition(pField);
            break;
        }
        case EObjectId::kFieldOverride:
        {
            FieldOverrideSPtr pFieldOverride = boost::static_pointer_cast<FieldOverride>(pObject);
            generateStructureFieldOverrideDefinition(pFieldOverride);
            break;
        }
        case EObjectId::kIdentification:
        {
            IdentificationSPtr pIdentification = boost::static_pointer_cast<Identification>(pObject);
            generateStructureIdentificationMethodsDefinition(pIdentification);
            break;
        }
        case EObjectId::kUpcopy:
        {
            //UpcopySPtr pUpcopy = boost::static_pointer_cast<Upcopy>(pObject);
            break;
        }
        case EObjectId::kOperator:
        {
            OperatorSPtr pOperator = boost::static_pointer_cast<Operator>(pObject);
            generateStructureOperatorMethodsDefinition(pOperator);
            break;
        }
        case EObjectId::kEnumeration:
        {
            EnumerationSPtr pEnumeration = boost::static_pointer_cast<Enumeration>(pObject);
            generateEnumerationDefinition(pEnumeration);
            break;
        }
        case EObjectId::kAlter:
        {
            AlterSPtr pAlter = boost::static_pointer_cast<Alter>(pObject);
            generateStructureFieldConstantDefinition(pStructure,
                                                     pAlter->field(),
                                                     pAlter->field()->type()->literal(),
                                                     pAlter->defaultValue());
            break;
        }
        default:
            assert(false);
    }
}

void CppGenerator::generateBaseStructureDefinition(const StructureSPtr& pStructure,
                                                   const StructureSPtr& pBaseStructure)
{
    if (!pBaseStructure) return;

    generateBaseStructureDefinition(pStructure, pBaseStructure->baseStructure().lock());

    const std::vector<ObjectSPtr>& objects = pBaseStructure->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        const ObjectSPtr& pObject = *it;
        switch (pObject->runtimeObjectId().value())
        {
            case EObjectId::kField:
            {
                FieldSPtr pField = boost::static_pointer_cast<Field>(pObject);
                generateStructureFieldWritingDefinition(pStructure, pField);
                break;
            }
            case EObjectId::kEnumeration:
            case EObjectId::kFieldOverride:
            case EObjectId::kIdentification:
            case EObjectId::kUpcopy:
            case EObjectId::kOperator:
                break;
            default:
                assert(false);
        }
    }
}

void CppGenerator::generateStructureDefinition(const StructureSPtr& pStructure)
{
    StructureSPtr pBaseStructure = pStructure->baseStructure().lock();

    const std::vector<ObjectSPtr>& objects = pStructure->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    if (pStructure->controlled())
    {
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            FieldSPtr pField = ObjectFactory::downcastField(*it);
            if (!pField) continue;

            fdef()  << (cf::methodRef() << integer
                                        << frm->cppAutoClassNamespace(pStructure)
                                        << frm->bitmaskMethodName(pField));
            openBlock(definitionStream);
            line()  << "return "
                    << frm->bitmask(pField->bitmask())
                    << ";";
            closeBlock(definitionStream);
            eol(definitionStream);
        }
    }

    cf::NamespaceSPtr structBuilderNamespace = frm->cppAutoClassNamespace(pStructure);
    *structBuilderNamespace << nsBuilder;

    if (pStructure->isBuildable())
    {
        if (!pStructure->abstract())
        {
            fdef()  << (cf::constructorRef() << structBuilderNamespace
                                             << builderConstructorName);
            eofd(definitionStream);

            std::string newObject = "new " + frm->cppMainClassType(pStructure)->name()->value() + "()";

            if (pBaseStructure)
            {
                table() << TableAligner::row()
                        << ": "
                        << (cf::functionCallRef() << frm->cppAutoClassNamespace(pBaseStructure)
                                                  << fnBuilder
                                                  << cf::parameterValueRef(newObject));
            }
            else
            {
                table() << TableAligner::row()
                        << ": "
                        << (cf::initializationRef() << frm->memberPtrVariableName(object)
                                                    << cf::parameterValueRef(newObject));
            }
            openBlock(definitionStream, 2);
            closeBlock(definitionStream);
            eol(definitionStream);

            fdef()  << (cf::constructorRef() << structBuilderNamespace
                                             << builderConstructorName
                                             << (cf::argumentRef() << impl->cppDecoratedType(pStructure)
                                                                   << object));
            eofd(definitionStream);

            std::vector<FactorySPtr> factories = mDocument->findPluginFactories(pStructure);
            if (!factories.empty())
            {
                addDependencies(impl->dependencies(factories[0]));
                line()  << impl->cppType(factories[0])
                        << "::clone<"
                        << impl->cppType(pStructure)->name()->value()
                        << ">(object)";
                newObject = boost::trim_right_copy(line().str(0));
                resetLine();
            }

            if (pBaseStructure)
            {
                table() << TableAligner::row()
                        << ": "
                        << (cf::functionCallRef() << frm->cppAutoClassNamespace(pBaseStructure)
                                                  << fnBuilder
                                                  << cf::parameterValueRef(newObject));
            }
            else
            {
                table() << TableAligner::row()
                        << ": "
                        << (cf::initializationRef() << frm->memberPtrVariableName(object)
                                                    << cf::parameterValueRef(newObject));
            }

            openBlock(definitionStream, 2);
            if (factories.empty())
            {
                line()  << "*("
                        << frm->cppMainClassType(pStructure)
                        << "*)"
                        << frm->memberPtrName("object")
                        << " = "
                        << object
                        << ";";
                eol(definitionStream);
            }

            closeBlock(definitionStream);
            eol(definitionStream);

            std::vector<ObjectSPtr>::const_iterator it;
            for (it = objects.begin(); it != objects.end(); ++it)
            {
                UpcopySPtr pUpcopy = ObjectFactory::downcastUpcopy(*it);
                if (!pUpcopy) continue;

                fdef()  << (cf::constructorRef() << structBuilderNamespace
                                                 << builderConstructorName
                                                 << (cf::argumentRef() << impl->cppDecoratedType(pUpcopy->baseStructure())
                                                                       << object));
                eofd(definitionStream);

                if (pBaseStructure)
                {
                    std::string value = "new " + frm->cppMainClassType(pStructure)->name()->value() + "()";
                    table() << TableAligner::row()
                            << ": "
                            << (cf::functionCallRef() << frm->cppAutoClassNamespace(pBaseStructure)
                                                      << fnBuilder
                                                      << cf::parameterValueRef(value));
                }
                else
                {
                    std::string value = "new " + frm->cppMainClassType(pStructure)->name()->value() + "()";
                    table() << TableAligner::row()
                            << ": "
                            << (cf::initializationRef() << frm->memberPtrVariableName(object)
                                                        << cf::parameterValueRef(value));
                }

                openBlock(definitionStream, 2);
                line()  << "*("
                        << frm->cppMainClassType(pUpcopy->baseStructure())
                        << "*)"
                        << frm->memberPtrName("object")
                        << " = "
                        << object
                        << ";";
                eol(definitionStream);

                closeBlock(definitionStream);
                eol(definitionStream);
            }
        }

        fdef()  << (cf::methodRef() << structBuilderNamespace
                                    << fnBuilder
                                    << (cf::argumentRef() << frm->cppRawPtrDecoratedType(pStructure)
                                                          << frm->ptrVariableName(object)));
        eofd(definitionStream);

        if (pBaseStructure)
        {
            table() << TableAligner::row()
                    << ": "
                    << (cf::functionCallRef() << frm->cppAutoClassNamespace(pBaseStructure)
                                              << fnBuilder
                                              << cf::parameterValueRef(frm->ptrVariableName(object)->value()));
        }
        else
        {
            table() << TableAligner::row()
                    << ": "
                    << (cf::initializationRef() << frm->memberPtrVariableName(object)
                                                << frm->parameterValue(frm->ptrVariableName(object)));
        }
        openBlock(definitionStream, 2);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::destructorRef() << structBuilderNamespace
                                        << cf::destructorNameRef("Builder"));
        openBlock(definitionStream);

        line()  << "delete ("
                << frm->cppRawPtrName(pStructure)
                << ")"
                << frm->memberPtrName("object")
                << ";";
        eol(definitionStream);

        addDependency(impl->nullDependency());
        line()  << frm->memberPtrName("object")
                << " = "
                << impl->null()
                << ";";
        eol(definitionStream);

        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << impl->cppDecoratedType(pStructure)
                                    << structBuilderNamespace
                                    << fnBuild
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);

        if (pStructure->isInitializable())
        {
            addDependency(impl->assert_dependency());
            line()  << impl->assert_method()
                    << "("
                    << frm->memberPtrName("object")
                    << "->"
                    << fnIsInitialized
                    << "());";
            eol(definitionStream);
        }

        line()  << "return *("
                << frm->cppRawPtrName(pStructure)
                << ")"
                << frm->memberPtrName("object")
                << ";";
        eol(definitionStream);

        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << (cf::methodRef() << impl->cppPtrType(pStructure)
                                    << structBuilderNamespace
                                    << fnFinalize);
        openBlock(definitionStream);

        if (pStructure->isInitializable())
        {
            addDependency(impl->assert_dependency());
            line()  << impl->assert_method()
                    << "("
                    << frm->memberPtrName("object")
                    << "->"
                    << fnIsInitialized
                    << "());";
            eol(definitionStream);
        }

        line()  << frm->cppRawPtrName(pStructure)
                << " "
                << frm->cppRawPtrName("object")
                << " = ("
                << frm->cppRawPtrName(pStructure)
                << ")" << frm->memberPtrName("object")
                << ";";
        eol(definitionStream);

        addDependency(impl->nullDependency());
        line()  << frm->memberPtrName("object")
                << " = "
                << impl->null()
                << ";";
        eol(definitionStream);

        line()  << "return "
                << impl->cppConvertRawPtr(pStructure, frm->cppRawPtrName("object"))
                << ";";
        eol(definitionStream);

        closeBlock(definitionStream);
        eol(definitionStream);
    }

    fdef()  << (cf::constructorRef() << frm->cppAutoClassNamespace(pStructure)
                                     << frm->cppAutoConstructorName(pStructure));

    if (pBaseStructure && pStructure->isBuildable())
    {
        std::stringstream init;
        init    << "*";
        std::vector<cf::NamespaceNameSPtr> names = frm->cppAutoClassNamespace(pBaseStructure)->names();
        for (size_t i = 0; i < names.size(); ++i)
            init    << names[i]->value() + "::";
        init    << "Builder()";

        bool alter = false;
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            AlterSPtr pAlter = ObjectFactory::downcastAlter(*it);
            if (!pAlter) continue;
            alter = true;

            init    << "."
                    << frm->setMethodName(pAlter->field())->value()
                    << "("
                    << frm->alterMethodName(pAlter->field())->value()
                    << "())";
        }

        if (alter)
        {
            init << ".finalize()";
            generateInitialization(
                cf::initializationRef() << frm->cppConstructorName(pBaseStructure)
                                        << cf::parameterValueRef(init.str()));
        }
    }

    if (pStructure->controlled() && pStructure->hasField())
        generateInitialization(
            cf::initializationRef() << frm->memberVariableName(bits)
                                    << cf::parameterValueRef("0"));

    for (it = objects.begin(); it != objects.end(); ++it)
    {
        generateStructureObjectMemberInitialization(*it);
    }

    bool bInitialization = !table().isEmpty();
    if (bInitialization)
        eofd(definitionStream);

    openBlock(definitionStream, bInitialization ? 2 : 0);

    if (pBaseStructure && !pStructure->immutable())
    {
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            AlterSPtr pAlter = ObjectFactory::downcastAlter(*it);
            if (!pAlter) continue;

            line()  << frm->setMethodName(pAlter->field())
                    << Aligner::FunctionSpace()
                    << "("
                    << frm->alterMethodName(pAlter->field())
                    << "());";
            eol(definitionStream);
        }
    }
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << (cf::destructorRef() << frm->cppAutoClassNamespace(pStructure)
                                    << frm->cppAutoDestructorName(pStructure));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    if (impl->mConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers)
    {
        StructureSPtr pRecursivelyBaseStructure = pStructure->recursivelyBaseStructure();
        if (pStructure != pRecursivelyBaseStructure)
        {
            cf::TypeSPtr type = frm->cppSharedPtrDecoratedType(pRecursivelyBaseStructure);
            fdef()  << (cf::methodRef() << frm->cppSharedPtrName(pStructure)
                                        << frm->cppAutoClassNamespace(pStructure)
                                        << fnDowncast
                                        << (cf::argumentRef() << type
                                                              << object));
            openBlock(definitionStream);

            std::vector<FactorySPtr> factories = mDocument->findPluginFactories(pStructure);

            for (std::vector<FactorySPtr>::iterator it = factories.begin(); it != factories.end(); ++it)
            {
                addDependency(impl->assert_dependency());
                addDependencies(impl->dependencies(*it));

                line()  << impl->assert_method()
                        << "(!"
                        << object
                        << " || "
                        << impl->cppType(*it)
                        << "::"
                        << fnIsDerivedFrom
                        << "<"
                        << frm->cppMainClassType(pStructure)
                        << ">("
                        << object
                        << "));";
                eol(definitionStream);
            }

            line()  << "return boost::static_pointer_cast<"
                    << frm->cppMainClassType(pStructure)
                    << ">("
                    << object
                    << ");";
            eol(definitionStream);
            closeBlock(definitionStream);
            eol(definitionStream);
        }

        if (pStructure->sharable())
        if (pStructure != pRecursivelyBaseStructure || pStructure->partial())
        {
            fdef()  << (cf::methodRef() << frm->cppSharedPtrName(pStructure)
                                        << frm->cppAutoClassNamespace(pStructure)
                                        << fnSharedFromThis);
            openBlock(definitionStream);
            line()  << "return boost::static_pointer_cast<"
                    << frm->cppMainClassType(pStructure)
                    << ">(";
            eol(definitionStream);
            line()  << "boost::enable_shared_from_this<"
                    << frm->cppAutoClassNamespace(pRecursivelyBaseStructure)
                    << ">::shared_from_this());";
            eol(definitionStream, 1);
            closeBlock(definitionStream);
            eol(definitionStream);

            fdef()  << (cf::methodRef() << frm->cppSharedConstPtrName(pStructure)
                                        << frm->cppAutoClassNamespace(pStructure)
                                        << fnSharedFromThis
                                        << cf::EMethodDeclaration::const_());
            openBlock(definitionStream);
            line()  << "return boost::static_pointer_cast<const "
                    << frm->cppMainClassType(pStructure)
                    << ">(";
            eol(definitionStream);
            line()  << "boost::enable_shared_from_this<"
                    << frm->cppAutoClassNamespace(pRecursivelyBaseStructure)
                    << ">::shared_from_this());";
            eol(definitionStream, 1);
            closeBlock(definitionStream);
            eol(definitionStream);
        }
    }

    if (pStructure->isInitializable())
    {
        fdef()  << (cf::methodRef() << bl
                                    << frm->cppAutoClassNamespace(pStructure)
                                    << fnIsInitialized
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);

        StructureSPtr pStruct = pBaseStructure;
        while (pStruct)
        {
            if (pStruct->controlled() && pStruct->hasField())
            {
                line()  << "if (!"
                        << (cf::functionCallRef() << frm->cppAutoClassNamespace(pStruct)
                                                  << fnIsInitialized)
                        << ") return false;";
                eol(definitionStream);
                break;
            }
            line()  << "// structure "
                    << pStruct->name()->value()
                    << " is not controlled. This function assume it is initilized";
            eol(definitionStream);

            pStruct = pStruct->baseStructure().lock();
        }

        for (it = objects.begin(); it != objects.end(); ++it)
        {
            FieldSPtr pField = ObjectFactory::downcastField(*it);
            if (!pField) continue;
            if (pField->defaultValue()) continue;

            line()  << "if (!"
                    << (cf::functionCallRef() << frm->validMethodName(pField))
                    << ") return false;";
            eol(definitionStream);
        }
        line()  << "return true;";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);
    }

    if (pStructure->isOptional())
    {
        fdef()  << (cf::methodRef() << bl
                                    << frm->cppAutoClassNamespace(pStructure)
                                    << fnIsVoid
                                    << cf::EMethodDeclaration::const_());
        openBlock(definitionStream);
        if (pBaseStructure)
        {
            line()  << "if (!"
                    << (cf::functionCallRef() << frm->cppAutoClassNamespace(pBaseStructure)
                                              << fnIsVoid)
                    << ") return false;";
            eol(definitionStream);
        }
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            FieldSPtr pField = ObjectFactory::downcastField(*it);
            if (!pField)
                continue;
            if (!pField->defaultValue())
                continue;

            if (pField->defaultValue()->optional())
            {
                line()  << "if ("
                        << (cf::functionCallRef() << frm->existMethodName(pField))
                        << ") return false;";
            }
            else
            {
                line()  << "if ("
                        << (cf::functionCallRef() << frm->changedMethodName(pField))
                        << ") return false;";
            }
            eol(definitionStream);
        }
        line()  << "return true;";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);
    }

    if (pStructure->immutable())
        generateBaseStructureDefinition(pStructure, pBaseStructure);

    for (it = objects.begin(); it != objects.end(); ++it)
    {
        generateStructureObjectDefinition(pStructure, *it);
    }

    if (!pStructure->immutable())
        generateBaseStructureDefinition(pStructure, pBaseStructure);
}

void CppGenerator::generateObjectDefinition(const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kImport:
            // do nothing
            break;
        case EObjectId::kEnumeration:
        {
            EnumerationSPtr pEnumeration = boost::static_pointer_cast<Enumeration>(pObject);
            generateEnumerationDefinition(pEnumeration);
            break;
        }
        case EObjectId::kSpecimen:
        {
            SpecimenSPtr pSpecimen = boost::static_pointer_cast<Specimen>(pObject);
            generateSpecimenDefinition(pSpecimen);
            break;
        }
        case EObjectId::kFactory:
        {
            FactorySPtr pFactory = boost::static_pointer_cast<Factory>(pObject);
            generateFactoryDefinition(pFactory);
            break;
        }
        case EObjectId::kIdentifier:
        {
            IdentifierSPtr pIdentifier = boost::static_pointer_cast<Identifier>(pObject);
            generateIdentifierDefinition(pIdentifier);
            break;
        }
        case EObjectId::kStructure:
        {
            StructureSPtr pStructure = boost::static_pointer_cast<Structure>(pObject);
            generateStructureDefinition(pStructure);
            break;
        }
        default:
            assert(false);
    }
}

bool CppGenerator::generate()
{
    addDependency(impl->cppHeaderFileDependency(mDocument->sourceId()->original(),
                                                mDocument->package()));

    addDependency(impl->cppPchDependency());

    openNamespace(definitionStream);

    const std::vector<ObjectSPtr>& objects = mDocument->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
		if ((*it)->sourceId() != mDocument->mainFile()->sourceId())
			continue;

		generateObjectDefinition(*it);
    }

    closeNamespace(definitionStream);

    includeHeaders(includeStream, Dependency::pch_section);
    includeHeaders(includeStream, Dependency::global_section);
    includeHeaders(includeStream, Dependency::private_section);

    return serializeStreams();
}

}