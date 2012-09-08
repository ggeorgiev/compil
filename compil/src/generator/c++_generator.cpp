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

#include "c++_generator.h"
#include "object_factory.h"

#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"

namespace compil
{

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

    SimpleType type;
    if (pEnumeration->cast() == CastableType::ECast::weak())
        type = impl->cppType(pParameterType);
    else if (pEnumeration->cast() == CastableType::ECast::strong())
        type = frm->cppEnumType(pEnumeration);
    else
        assert(false && "unknown enumeration cast");

    fdef()  << TableAligner::row()
            << Function(*CreateDecoratedType(ETypeDeclaration::const_(), type),
                        frm->cppEnumNamespace(pEnumeration),
                        frm->methodName(pEnumerationValue->name()->value()));
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

    DecoratedType outerType = *CreateDecoratedType(impl->cppType(pEnumeration));
    DecoratedType innerDecoratedType = impl->cppInnerDecoratedType(pEnumeration, pStructure);


    fdef()  << TableAligner::row()
            << Constructor(frm->cppEnumNamespace(pEnumeration),
                           frm->cppInnerEnumType(pEnumeration, pStructure));
    eofd(definitionStream);

    line()  << ": ";


    std::string initMethod = impl->inheritClass(pEnumeration, pStructure);
    if (initMethod.empty())
        initMethod = frm->memberName("value");

    if (pEnumeration->flags())
    {
        line()  << *CreateInitialization(initMethod, "0");
    }
    else
    {
        line()  << *CreateInitialization(
                        initMethod,
                        frm->enumValueName(Model::invalidEnumerationValue(pEnumeration)));
    }
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Constructor(frm->cppEnumNamespace(pEnumeration),
                           frm->cppInnerEnumType(pEnumeration, pStructure),
                           Argument(impl->cppDecoratedType(pParameterType),
                                    "value"));
    eofd(definitionStream);

    line()  << ": "
            << *CreateInitialization(initMethod, "value");
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);

    if (pEnumeration->flags())
        generateEnumerationValueDefinition(Model::nilEnumerationValue(pEnumeration));
    else
        generateEnumerationValueDefinition(Model::invalidEnumerationValue(pEnumeration));

    const std::vector<EnumerationValueSPtr>& enumerationValues = pEnumeration->enumerationValues();
    std::vector<EnumerationValueSPtr>::const_iterator it;
    for (it = enumerationValues.begin(); it != enumerationValues.end(); ++it)
        generateEnumerationValueDefinition(*it);

    if (pEnumeration->flags())
        generateEnumerationValueDefinition(Model::allEnumerationValue(pEnumeration));

    fdef()  << TableAligner::row()
            << Function(impl->cppDecoratedType(pParameterType),
                        frm->cppEnumNamespace(pEnumeration), fnValue, EMethodDeclaration::const_());
    openBlock(definitionStream);
    line()  << "return "
            << frm->memberName("value")
            << ";";
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Function(const_char_ptr, frm->cppEnumNamespace(pEnumeration), fnShortName,
                        Argument(impl->cppDecoratedType(pParameterType), "value"));
    openBlock(definitionStream);

    long min = pEnumeration->getMinValue();
    long max = pEnumeration->getMaxValue();
    if (!pEnumeration->flags() && (max - min < (long)enumerationValues.size() + 10))
    {
        line()  << "static const char* names[] = ";
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


    fdef()  << TableAligner::row()
            << Function(const_char_ptr, frm->cppEnumNamespace(pEnumeration),
                        fnShortName, EMethodDeclaration::const_());
    openBlock(definitionStream);
    line()  << "return "
            << FunctionCall(fnShortName, Argument("value()"))
            << ";";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    if (pEnumeration->cast() == CastableType::ECast::strong())
    {
        fdef()  << TableAligner::row()
                << Function(bl, frm->cppEnumNamespace(pEnumeration), fnOperatorEq,
                            Argument(innerDecoratedType, "rValue"), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << " == rValue."
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(bl, frm->cppEnumNamespace(pEnumeration), fnOperatorNe,
                            Argument(innerDecoratedType, "rValue"), EMethodDeclaration::const_());
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
        fdef()  << TableAligner::row()
                << Function(frm->cppEnumNamespace(pEnumeration),
                            CastOperator(impl->cppDecoratedType(pParameterType)), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);
    }

    if (impl->implementFlagsEnumerationMethods(pEnumeration))
    {
        fdef()  << TableAligner::row()
                << Function(vd, frm->cppEnumNamespace(pEnumeration), fnReset,
                            Argument(innerDecoratedType, "mask"),
                            Argument(innerDecoratedType, "value"));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " = value.value() | (this->value() & ~mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(vd, frm->cppEnumNamespace(pEnumeration), fnSet,
                            Argument(innerDecoratedType, "mask"));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " |= mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(vd, frm->cppEnumNamespace(pEnumeration), fnClear,
                            Argument(innerDecoratedType, "mask"));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " &= ~mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(vd, frm->cppEnumNamespace(pEnumeration), fnTurn,
                            Argument(innerDecoratedType, "mask"));
        openBlock(definitionStream);
        line()  << frm->memberName("value")
                << " ^= mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(outerType, frm->cppEnumNamespace(pEnumeration), fnAssemble,
                            Argument(innerDecoratedType, "mask"),
                            Argument(innerDecoratedType, "value"), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "("
                << " value.value() | (this->value() & ~mask.value()));";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(outerType, frm->cppEnumNamespace(pEnumeration), fnCombine,
                            Argument(innerDecoratedType, "mask"), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "(value() | mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(outerType, frm->cppEnumNamespace(pEnumeration), fnIntersect,
                            Argument(innerDecoratedType, "mask"), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "(value() & ~mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(outerType, frm->cppEnumNamespace(pEnumeration), fnFlip,
                            Argument(innerDecoratedType, "mask"), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << outerType
                << "(value() ^ mask.value());";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(bl, frm->cppEnumNamespace(pEnumeration), fnTest,
                            Argument(innerDecoratedType, "mask"),
                            Argument(innerDecoratedType, "value"),
                            EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return (this->value() & mask.value()) == value.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(bl, frm->cppEnumNamespace(pEnumeration), fnIsSet,
                            Argument(innerDecoratedType, "mask"),
                            EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return (value() & mask.value()) == mask.value();";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(bl, frm->cppEnumNamespace(pEnumeration), fnIsClear,
                            Argument(innerDecoratedType, "mask"),
                            EMethodDeclaration::const_());
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

    fdef()  << TableAligner::row()
            << Constructor(frm->cppClassNamespace(pSpecimen), frm->cppClassType(pSpecimen));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Constructor(frm->cppClassNamespace(pSpecimen), frm->cppClassType(pSpecimen),
                           Argument(impl->cppDecoratedType(pSpecimen->parameterType().lock()), "value"));
    eofd(definitionStream);

    line()  << ": ";
    if (pBaseSpecimen)
        line()  << *CreateInitialization(frm->cppClassType(pBaseSpecimen).value(), "value");
    else
        line()  << *CreateInitialization(frm->memberName("value"), "value");
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);
}

void CppGenerator::generateHierarchyFactoryDefinition(const FactorySPtr& pFactory)
{
    TypeSPtr pParameterType = pFactory->parameterType().lock();
    StructureSPtr pParameterStructure = ObjectFactory::downcastStructure(pParameterType);
    std::vector<StructureSPtr> structs = impl->hierarchie(mpModel,
                                                          pParameterStructure,
                                                          &Structure::hasRuntimeIdentification);
    EnumerationSPtr pEnumeration = impl->objectEnumeration(mpModel, structs, pFactory);
    generateEnumerationDefinition(pEnumeration);

    std::vector<StructureSPtr>::const_iterator it;
    for (it = structs.begin(); it != structs.end(); ++it)
    {
        StructureSPtr pStructure = *it;

        fdef()  << TableAligner::row()
                << Function(*CreateDecoratedType(impl->identificationEnum(pParameterStructure)),
                            frm->cppAutoClassNamespace(pStructure),
                            impl->staticIdentificationMethodName(pParameterStructure));
        openBlock(definitionStream);
        line()  << "return "
                << frm->cppEnumNamespace(pEnumeration)
                << "::"
                << frm->methodName(pStructure->name()->value())
                << "();";
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(*CreateDecoratedType(impl->identificationEnum(pParameterStructure)),
                            frm->cppAutoClassNamespace(pStructure),
                            impl->runtimeIdentificationMethodName(pParameterStructure),
                            EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << impl->staticIdentificationMethodName(pParameterStructure)
                << "();";
        closeBlock(definitionStream);
        eol(definitionStream);
    }

    fdef()  << TableAligner::row()
            << Function(*CreateDecoratedType(impl->cppPtrType(pParameterType)),
                        frm->cppClassNamespace(pFactory), fnClone,
                        Argument(impl->cppPtrDecoratedType(pParameterType), "pObject"));
    openBlock(definitionStream);
    line()  << "switch (pObject->"
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
                    << "(pObject);";
        }
        else
        {
            line()  << "*pClone = *"
                    << "pObject;";
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

        fdef()  << TableAligner::row()
                << Function(*CreateDecoratedType(impl->cppPtrType(pStructure)),
                            frm->cppClassNamespace(pFactory),
                            frm->downcastMethodName(pStructure),
                            Argument(impl->cppPtrDecoratedType(pParameterStructure), "pObject"));
        openBlock(definitionStream);
        line()  << "bool b = "
                << "(pObject->"
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
            line()  << "      || "
                    << "(pObject->"
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
                << ">(pObject);";
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

    NamespaceSPtr nmspace;
    MethodNameSPtr methodName;
    if (pFactory->function())
    {
        methodName = methodNameRef(pFactory->name()->value());
    }
    else
    {
        nmspace = frm->cppClassNamespace(pFactory);
        methodName = fnCreate;
    }

    std::vector<compil::FieldSPtr> iteration;
    while (pParameterStructure->fieldIterate(iteration))
    {
        Function function(*CreateDecoratedType(impl->cppPtrType(pParameterType)),
                          nmspace, methodName);

        std::vector<compil::FieldSPtr>::iterator it;
        for (it = iteration.begin(); it != iteration.end(); ++it)
            function << Argument(impl->cppSetDecoratedType((*it)->type()),
                                 frm->cppVariableName(*it));

        fdef()  << TableAligner::row()
                << function;
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
                            << FunctionCall(frm->setMethodName(*it), Argument(frm->cppVariableName(*it)))
                            << ";";
                }
                else
                {
                    line()  << "builder."
                            << frm->setMethodName(*it)
                            << "("
                            << FunctionCall(frm->cppMainClassNamespace(pParameterStructure),
                                            functionNameRef(pFilter->method()),
                                            Argument(frm->cppVariableName(*it)))
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
    fdef()  << TableAligner::row()
            << Constructor(frm->cppClassNamespace(pFactory),
                           frm->cppClassType(pFactory));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << (Destructor() << frm->cppClassNamespace(pFactory)
                             << frm->cppDestructorName(pFactory));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);


    fdef()  << TableAligner::row()
            << Function(bl, frm->cppClassNamespace(pFactory), fnRegisterCloneFunction,
                        Argument(st, "object"), Argument(cloneFunction, "function"));
    openBlock(definitionStream);
    line()  << "get().cloneFunctions[object] = function;";
    eol(definitionStream);
    line()  << "return true;";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Function(bl, frm->cppClassNamespace(pFactory), fnRegisterRelationship,
                        Argument(st, "parent"), Argument(st, "child"));
    openBlock(definitionStream);
    line()  << "get().relationships.insert(Pair(parent, child));";
    eol(definitionStream);
    line()  << "return true;";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Function(bl, frm->cppClassNamespace(pFactory), fnIsParent,
                        Argument(st, "parent"), Argument(st, "child"));
    openBlock(definitionStream);
    line()  << "return get().relationships.find(Pair(parent, child)) != get().relationships.end();";
    eol(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Function(*CreateDecoratedType(frm->cppClassType(pFactory), ETypeDecoration::reference()),
                        frm->cppClassNamespace(pFactory), fnGet);
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

    fdef()  << TableAligner::row()
            << Constructor(frm->cppClassNamespace(pIdentifier), frm->cppClassType(pIdentifier));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Constructor(frm->cppClassNamespace(pIdentifier),
                           frm->cppClassType(pIdentifier),
                           Argument(impl->cppDecoratedType(pParameterType),
                                    "value"));
    eofd(definitionStream);

    line()  << ": "
            << *CreateInitialization(frm->memberName("value"), "value");
    openBlock(definitionStream, 2);
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Function(impl->cppDecoratedType(pParameterType),
                        frm->cppClassNamespace(pIdentifier), fnValue, EMethodDeclaration::const_());
    openBlock(definitionStream);
    line()  << "return "
            << frm->memberName("value")
            << ";";
    closeBlock(definitionStream);
    eol(definitionStream);

    if (pIdentifier->cast() == CastableType::ECast::strong())
    {
        fdef()  << TableAligner::row()
                << Function(bl, frm->cppClassNamespace(pIdentifier), fnOperatorEq,
                            Argument(impl->cppDecoratedType(pIdentifier), "rValue"), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << " == rValue."
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << Function(bl, frm->cppClassNamespace(pIdentifier), fnOperatorNe,
                            Argument(impl->cppDecoratedType(pIdentifier), "rValue"), EMethodDeclaration::const_());
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
        fdef()  << TableAligner::row()
                << Function(frm->cppClassNamespace(pIdentifier),
                            CastOperator(impl->cppDecoratedType(pParameterType)), EMethodDeclaration::const_());
        openBlock(definitionStream);
        line()  << "return "
                << frm->memberName("value")
                << ";";
        closeBlock(definitionStream);
        eol(definitionStream);
    }
}

void CppGenerator::generateInitialization(const Initialization& initialization)
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
        generateInitialization(*CreateInitialization(
            frm->cppMemberName(pField), frm->defaultMethodName(pField)->value() + "()"));
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

    NamespaceSPtr classNamesp = frm->cppAutoClassNamespace(pStructure);
    NamespaceSPtr namesp = boost::make_shared<Namespace>(*classNamesp);
    
    NamespaceSPtr belongClassBuilderNamesp = frm->cppAutoClassNamespace(pBelongStructure);
    *belongClassBuilderNamesp << nsBuilder;

    std::string accessObject;
    DecoratedType resultType = *CreateDecoratedType(impl->cppType(pStructure), ETypeDecoration::reference());

    if (pStructure->immutable())
    {
        *namesp << nsBuilder;
        if (pBelongStructure->baseStructure().lock())
            accessObject = "((" + frm->cppAutoClassType(pStructure).value() + "*)"
                           + frm->memberPtrName("object") + ")->";
        else
            accessObject = frm->memberPtrName("object") + "->";

        resultType = *CreateDecoratedType(*CreateSimpleType(classNamesp,
                                                            builder.value()),
                                                            ETypeDecoration::reference());
    }


    if ((!pStructure->immutable() || pStructure->isBuildable()) && !pStructure->isOverriden(pField))
    {
        fdef()  << TableAligner::row()
                << Function(resultType,
                            namesp, frm->setMethodName(pField),
                            Argument(impl->cppInnerSetDecoratedType(pField->type(), pStructure),
                                     frm->cppVariableName(pField)));
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
                        << FunctionCall(frm->bitmaskMethodName(pField))
                        << ";";
            }
            eot(definitionStream);
            
            if (!pStructure->immutable() && pStructure->partial())
            {
                line()  << "return *("
                        << frm->cppClassType(pStructure).value()
                        << "*)this;";
            }
            else
            {
                line() << "return *this;";
            }
            eol(definitionStream);
        }
        else
        {
            line()  << "return ("
                    << *CreateDecoratedType(
                            *CreateSimpleType(classNamesp, builder.value()), ETypeDecoration::reference())
                    << ")"
                    << FunctionCall(belongClassBuilderNamesp,
                                    frm->setMethodName(pField), Argument(frm->cppVariableName(pField)))
                    << ";";
            eol(definitionStream);
        }
        closeBlock(definitionStream);
        eol(definitionStream);
        
        
        if (impl->needMutableMethod(pField, pStructure))
        {
            fdef()  << TableAligner::row()
                    << Function(*CreateDecoratedType(impl->cppType(pField->type()), ETypeDecoration::reference()),
                                namesp, frm->mutableMethodName(pField));
            openBlock(definitionStream);
            
            if (pStructure->controlled())
            {
                line()  << accessObject
                        << frm->memberName("bits")
                        << " |= "
                        << FunctionCall(frm->bitmaskMethodName(pField))
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
            fdef()  << TableAligner::row()
                    << Function(resultType,
                                namesp, fnOperatorStore,
                                Argument(impl->cppInnerSetDecoratedType(pField->type(), pStructure),
                                         frm->cppVariableName(pField)));
            openBlock(definitionStream);
            
            line()  << "return "
                    << frm->setMethodName(pField)
                    << "("
                    << frm->cppVariableName(pField)
                    << ");";
            eol(definitionStream);

            closeBlock(definitionStream);
            eol(definitionStream);
            
            UnaryContainerSPtr pUnaryContainer = ObjectFactory::downcastUnaryContainer(pField->type());
            if (pUnaryContainer)
            {
                fdef()  << TableAligner::row()
                        << Function(resultType,
                                    namesp, fnOperatorStore,
                                    Argument(impl->cppInnerSetDecoratedType(pUnaryContainer->parameterType().lock(),
                                             pStructure), frm->cppVariableName(pField) + "Item"));
                openBlock(definitionStream);

                if (pStructure->controlled())
                {
                    line()  << accessObject
                            << frm->memberName("bits")
                            << " |= "
                            << FunctionCall(frm->bitmaskMethodName(pField))
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
                
                if (!pStructure->immutable() && pStructure->partial())
                {
                    line()  << "return *("
                            << frm->cppClassType(pStructure).value()
                            << "*)this;";
                }
                else
                {
                    line() << "return *this;";
                }
                eol(definitionStream);

                closeBlock(definitionStream);
                eol(definitionStream);
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
                fdef()  << TableAligner::row()
                        << Function(resultType,
                                    namesp, frm->updateMethodName(pField),
                                    Argument(impl->cppInnerSetDecoratedType(pField->type(), pStructure),
                                             frm->cppVariableName(pField)));
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
                            << frm->updateMethodName(pField)
                            << "("
                            << frm->cppVariableName(pField)
                            << ");";
                    eol(definitionStream, 1);

                    eol(definitionStream);
                    
                    line()  << frm->resetMethodName(pField)
                            << "();";
                    eol(definitionStream);

                    if (!pStructure->immutable() && pStructure->partial())
                    {
                        line()  << "return *("
                                << frm->cppClassType(pStructure).value()
                                << "*)this;";
                    }
                    else
                    {
                        line() << "return *this;";
                    }
                    eol(definitionStream);
                }
                else
                {
                    line()  << "return ("
                            << *CreateDecoratedType(
                                    *CreateSimpleType(classNamesp, builder.value()), ETypeDecoration::reference())
                            << ")"
                            << FunctionCall(belongClassBuilderNamesp,
                                            frm->updateMethodName(pField), Argument(frm->cppVariableName(pField)))
                            << ";";
                    eol(definitionStream);
                }
                closeBlock(definitionStream);
                eol(definitionStream);
            }

            fdef()  << TableAligner::row()
                    << Function(vd, namesp, frm->destroyMethodName(pField));
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
                        << FunctionCall(frm->defaultMethodName(pField))
                        << ";";
            }
            else
            {
                switch (pField->type()->runtimeObjectId().value())
                {
                    case EObjectId::kType:
                        if (pField->type()->name()->value() == "string")
                        {
                            switch (impl->mpConfiguration->mString)
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
                                std::vector<std::string> elements;
                                elements.push_back("time");

                                if (pField->type()->package()->elements() == elements)
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
                        switch (impl->mpConfiguration->mPointer)
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
                    << FunctionCall(frm->bitmaskMethodName(pField))
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
    fdef()  << TableAligner::row()
            << Function(*CreateDecoratedType(impl->cppType(pField->type())),
                        frm->cppAutoClassNamespace(pStructure),
                        frm->constantMethodName(pStructure, pField));

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
    else if (pField->type()->runtimeObjectId() == EObjectId::enumeration())
    {
        EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pField->type());
        line() << "return "
               << frm->cppEnumNamespace(pEnumeration)
               << "::"
               << pDefaultValue->value()
               << "();";
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

    fdef()  << TableAligner::row()
            << Function(impl->cppDecoratedType(pField->type()),
                        frm->cppAutoClassNamespace(pStructure), frm->getMethodName(pField), EMethodDeclaration::const_());

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
        fdef()  << TableAligner::row()
                << Function(bl, frm->cppAutoClassNamespace(pStructure),
                            frm->availableMethodName(pField), EMethodDeclaration::const_());

        openBlock(definitionStream);

        line()  << "return ("
                << frm->memberName("bits")
                << " & "
                << FunctionCall(frm->bitmaskMethodName(pField))
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

    fdef()  << TableAligner::row()
            << Function(*CreateDecoratedType(impl->cppType(pField->type())),
                        frm->cppAutoClassNamespace(pStructure), frm->getMethodName(pField), EMethodDeclaration::const_());

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

    NamespaceSPtr classNamesp = frm->cppAutoClassNamespace(pStructure);
    NamespaceSPtr namesp = boost::make_shared<Namespace>(*classNamesp);
    *namesp << nsBuilder;

    fdef()  << TableAligner::row()
            << Function(*CreateDecoratedType(*CreateSimpleType(classNamesp,
                                                               builder.value()),
                                                               ETypeDecoration::reference()),
                        namesp, frm->setMethodName(pField),
                        Argument(impl->cppInnerSetDecoratedType(pField->type(), pStructure),
                                 frm->cppVariableName(pField)));

    openBlock(definitionStream);
    line() << frm->cppAutoClassNamespace(pFieldOverride->overriddenField()->structure().lock())
           << "::"
           << nsBuilder->value()
           << "::"
           << frm->setMethodName(pField)
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

    std::vector<FactorySPtr> factories = mpModel->findPluginFactories(pStructure);
    if (!pStructure->abstract())
    {
        for (std::vector<FactorySPtr>::iterator it = factories.begin(); it != factories.end(); ++it)
        {
            const FactorySPtr& factory = *it;
            StructureSPtr pParameterType = Structure::downcast(factory->parameterType().lock());


            fdef()  << TableAligner::row()
                    << Function(frm->cppRawPtrDecoratedType(pParameterType),
                                frm->cppAutoClassNamespace(pStructure), fnClone,
                                Argument(impl->cppDecoratedType(pParameterType), "object"));
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

        if (first)
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

        StructureSPtr pBase = pStructure->baseStructure().lock();
        while (pBase)
        {
            table() << TableAligner::row()
                    << (first ? "" : "&& ")
                    << TableAligner::col()
                    << impl->cppType(factory)
                    << "::"
                    << fnRegisterRelationship
                    << TableAligner::col()
                    << "("
                    << frm->cppMainClassType(pBase)
                    << "::"
                    << impl->staticMethodName(fnInprocId->value())
                    << "(), "
                    << TableAligner::col()
                    << frm->cppMainClassType(pStructure)
                    << "::"
                    << impl->staticMethodName(fnInprocId->value())
                    << "())";

            if (pBase == pParameterType)
                break;

            first = false;
            pBase = pBase->baseStructure().lock();
        }
    }
    if (!first)
    {
        table()  << ";";

        eot(definitionStream, 1);
        eol(definitionStream);
    }

    fdef()  << TableAligner::row()
            << Function(st, frm->cppAutoClassNamespace(pStructure),
                        impl->staticMethodName(fnInprocId->value()));
    openBlock(definitionStream);
    line()  << "return (size_t)\"";
    if (pStructure->package())
    {
        std::vector<std::string> elements = pStructure->package()->elements();
        for(std::vector<std::string>::iterator it = elements.begin(); it != elements.end(); ++it)
        {
            line()  << *it
                    << ".";
        }
    }
    line()  << pStructure->name()->value()
            << "\";";
    closeBlock(definitionStream);
    eol(definitionStream);

    fdef()  << TableAligner::row()
            << Function(st, frm->cppAutoClassNamespace(pStructure),
                        impl->runtimeMethodName(fnInprocId->value()), EMethodDeclaration::const_());
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
    FunctionNameSPtr fnFunction;
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

                if (impl->hasOperator(pType, action, refflags))
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

    std::string cast = "(" + impl->cppType(pBaseStructure).value() + ")";

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

    FunctionNameSPtr fnOperator;
    FunctionNameSPtr fnFunction;
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

    FunctionNameSPtr fnName;
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

    NamespaceSPtr nmspace = frm->cppAutoClassNamespace(pStructure);
    if (flags.isSet(EOperatorFlags::functor()))
        *nmspace << namespaceNameRef(fnFunction->value());

    int arguments;
    if (flags.isClear(EOperatorFlags::member()) || flags.isSet(EOperatorFlags::functor()))
        arguments = 2;
    else
        arguments = 1;

    DecoratedType type;
    if (flags.isSet(EOperatorFlags::object()))
        type = impl->cppDecoratedType(pStructure);
    else
    if (flags.isSet(EOperatorFlags::reference()))
        type = impl->cppPtrDecoratedType(pStructure);
    else
        assert(false && "unknown operator parameter");

    EMethodDeclaration declaration;
    if (flags.isSet(EOperatorFlags::member()) || flags.isSet(EOperatorFlags::functor()))
        declaration = EMethodDeclaration::const_();

    if (arguments == 1)
    {
        fdef()  << TableAligner::row()
                << Function(bl,
                            nmspace,
                            fnName,
                            Argument(type, "object"),
                            declaration);
    }
    else
    {
        fdef()  << TableAligner::row()
                << Function(bl,
                            nmspace,
                            fnName,
                            Argument(type, "object1"),
                            Argument(type, "object2"),
                            declaration);
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

void CppGenerator::generateImmutableBaseStructureBuilderDefinition(const StructureSPtr& pStructure,
                                                                   const StructureSPtr& pBaseStructure)
{
    if (!pBaseStructure) return;

    generateImmutableBaseStructureBuilderDefinition(pStructure, pBaseStructure->baseStructure().lock());

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

            fdef()  << TableAligner::row()
                    << Function(*CreateDecoratedType(*CreateSimpleType("int")),
                                frm->cppAutoClassNamespace(pStructure), frm->bitmaskMethodName(pField));
            openBlock(definitionStream);
            line()  << "return "
                    << frm->bitmask(pField->bitmask())
                    << ";";
            closeBlock(definitionStream);
            eol(definitionStream);
        }
    }
    
    NamespaceSPtr structBuilderNamespace = frm->cppAutoClassNamespace(pStructure);
    *structBuilderNamespace << nsBuilder;

    if (pStructure->isBuildable())
    {
        if (!pStructure->abstract())
        {
            fdef()  << TableAligner::row()
                    << Constructor(structBuilderNamespace, builder);
            eofd(definitionStream);

            std::string object = "new " + frm->cppMainClassType(pStructure).value() + "()";

            if (pBaseStructure)
            {
                table() << TableAligner::row()
                        << ": "
                        << FunctionCall(frm->cppAutoClassNamespace(pBaseStructure), fnBuilder,
                                        Argument(object));
            }
            else
            {
                table() << TableAligner::row()
                        << ": "
                        << *CreateInitialization(frm->memberPtrName("object"), object);
            }
            openBlock(definitionStream, 2);
            closeBlock(definitionStream);
            eol(definitionStream);

            fdef()  << TableAligner::row()
                    << Constructor(structBuilderNamespace, builder,
                                   Argument(impl->cppDecoratedType(pStructure),
                                            frm->variableName("object")));
            eofd(definitionStream);

            std::vector<FactorySPtr> factories = mpModel->findPluginFactories(pStructure);
            if (!factories.empty())
            {
                addDependencies(impl->dependencies(factories[0]));
                line()  << impl->cppType(factories[0])
                        << "::clone<"
                        << impl->cppType(pStructure).value()
                        << ">(object)";
                object = boost::trim_right_copy(line().str(0));
                resetLine();
            }

            if (pBaseStructure)
            {
                table() << TableAligner::row()
                        << ": "
                        << FunctionCall(frm->cppAutoClassNamespace(pBaseStructure), fnBuilder,
                                        Argument(object));
            }
            else
            {
                table() << TableAligner::row()
                        << ": "
                        << *CreateInitialization(frm->memberPtrName("object"), object);
            }

            openBlock(definitionStream, 2);
            if (factories.empty())
            {
                line()  << "*("
                        << frm->cppMainClassType(pStructure)
                        << "*)"
                        << frm->memberPtrName("object")
                        << " = "
                        << frm->variableName("object")
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

                fdef()  << TableAligner::row()
                        << Constructor(structBuilderNamespace, builder,
                                       Argument(impl->cppDecoratedType(pUpcopy->baseStructure()),
                                                frm->variableName("object")));
                eofd(definitionStream);

                if (pBaseStructure)
                {
                    table() << TableAligner::row()
                            << ": "
                            << FunctionCall(frm->cppAutoClassNamespace(pBaseStructure), fnBuilder,
                                            Argument("new " + frm->cppMainClassType(pStructure).value() + "()"));
                }
                else
                {
                    table() << TableAligner::row()
                            << ": "
                            << *CreateInitialization(frm->memberPtrName("object"),
                                                     "new " + frm->cppMainClassType(pStructure).value() + "()");
                }

                openBlock(definitionStream, 2);
                line()  << "*("
                        << frm->cppMainClassType(pUpcopy->baseStructure())
                        << "*)"
                        << frm->memberPtrName("object")
                        << " = "
                        << frm->variableName("object")
                        << ";";
                eol(definitionStream);

                closeBlock(definitionStream);
                eol(definitionStream);
            }
        }

        fdef()  << TableAligner::row()
                << Function(structBuilderNamespace, fnBuilder,
                            Argument(frm->cppRawPtrDecoratedType(pStructure),
                                     frm->variablePtrName("object")));
        eofd(definitionStream);

        if (pBaseStructure)
        {
            table() << TableAligner::row()
                    << ": "
                    << FunctionCall(frm->cppAutoClassNamespace(pBaseStructure), fnBuilder,
                                    Argument(frm->variablePtrName("object")));
        }
        else
        {
            table() << TableAligner::row()
                    << ": "
                    << *CreateInitialization(frm->memberPtrName("object"),
                                             frm->variablePtrName("object"));
        }
        openBlock(definitionStream, 2);
        closeBlock(definitionStream);
        eol(definitionStream);

        fdef()  << TableAligner::row()
                << (Destructor() << structBuilderNamespace
                                 << destructorNameRef("Builder"));
        openBlock(definitionStream);

        line()  << "delete ("
                << *CreateDecoratedType(frm->cppRawPtrName(pStructure))
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


        fdef()  << TableAligner::row()
                << Function(impl->cppDecoratedType(pStructure),
                            structBuilderNamespace, fnBuild, EMethodDeclaration::const_());
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


        fdef()  << TableAligner::row()
                << Function(*CreateDecoratedType(impl->cppPtrType(pStructure)),
                            structBuilderNamespace, fnFinalize);
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

    fdef()  << TableAligner::row()
            << Constructor(frm->cppAutoClassNamespace(pStructure),
                           frm->cppAutoClassType(pStructure));

    if (pBaseStructure && pStructure->isBuildable())
    {
        std::stringstream init;
        init    << "*";
        std::vector<NamespaceNameSPtr> names = frm->cppAutoClassNamespace(pBaseStructure)->names();
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
            generateInitialization(*CreateInitialization(
                                   frm->cppAutoClassType(pBaseStructure).value(), init.str()));
        }
    }

    if (pStructure->controlled() && pStructure->hasField())
        generateInitialization(*CreateInitialization(frm->memberName("bits"), "0"));

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


    fdef()  << TableAligner::row()
            << (Destructor() << frm->cppAutoClassNamespace(pStructure)
                             << frm->cppAutoDestructorName(pStructure));
    openBlock(definitionStream);
    closeBlock(definitionStream);
    eol(definitionStream);

    if (impl->mpConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers)
    {
        StructureSPtr pRecursivelyBaseStructure = pStructure->recursivelyBaseStructure();
        if (pStructure != pRecursivelyBaseStructure)
        {
            fdef()  << TableAligner::row()
                    << Function(*CreateDecoratedType(frm->cppSharedPtrName(pStructure)),
                                frm->cppAutoClassNamespace(pStructure), fnDowncast,
                                Argument(frm->cppSharedPtrDecoratedType(pRecursivelyBaseStructure),
                                         frm->variablePtrName("object")));
            openBlock(definitionStream);
            line()  << "return boost::static_pointer_cast<"
                    << frm->cppMainClassType(pStructure)
                    << ">("
                    << frm->variablePtrName("object")
                    << ");";
            eol(definitionStream);
            closeBlock(definitionStream);
            eol(definitionStream);
        }

        if (pStructure->sharable())
        if (pStructure != pRecursivelyBaseStructure || pStructure->partial())
        {
            fdef()  << TableAligner::row()
                    << Function(*CreateDecoratedType(frm->cppSharedPtrName(pStructure)),
                                frm->cppAutoClassNamespace(pStructure), fnSharedFromThis);
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

            fdef()  << TableAligner::row()
                    << Function(*CreateDecoratedType(frm->cppSharedConstPtrName(pStructure)),
                                frm->cppAutoClassNamespace(pStructure), fnSharedFromThis, EMethodDeclaration::const_());
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
        fdef()  << TableAligner::row()
                << Function(bl, frm->cppAutoClassNamespace(pStructure), fnIsInitialized, EMethodDeclaration::const_());
        openBlock(definitionStream);

        StructureSPtr pStruct = pBaseStructure;
        while (pStruct)
        {
            if (pStruct->controlled() && pStruct->hasField())
            {
                line()  << "if (!"
                        << FunctionCall(frm->cppAutoClassNamespace(pStruct),
                                        fnIsInitialized)
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
                    << FunctionCall(frm->validMethodName(pField))
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
        fdef()  << TableAligner::row()
                << Function(bl, frm->cppAutoClassNamespace(pStructure), fnIsVoid, EMethodDeclaration::const_());
        openBlock(definitionStream);
        if (pBaseStructure)
        {
            line()  << "if (!"
                    << FunctionCall(frm->cppAutoClassNamespace(pBaseStructure),
                                    fnIsVoid)
                    << ") return false;";
            eol(definitionStream);
        }
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            FieldSPtr pField = ObjectFactory::downcastField(*it);
            if (!pField) continue;
            if (!pField->defaultValue()) continue;
            if (!pField->defaultValue()->optional()) continue;

            line()  << "if ("
                    << FunctionCall(frm->existMethodName(pField))
                    << ") return false;";
            eol(definitionStream);
        }
        line()  << "return true;";
        eol(definitionStream);
        closeBlock(definitionStream);
        eol(definitionStream);
    }

    if (pStructure->immutable())
    {
        generateImmutableBaseStructureBuilderDefinition(pStructure, pBaseStructure);
    }

    for (it = objects.begin(); it != objects.end(); ++it)
    {
        generateStructureObjectDefinition(pStructure, *it);
    }
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
    addDependency(Dependency(mpModel->name()->value() + ".h", Dependency::quote_type));

    openNamespace(definitionStream);

    const std::vector<ObjectSPtr>& objects = mpModel->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
		if ((*it)->sourceId() != mpModel->mainDocument()->sourceId())
			continue;

		generateObjectDefinition(*it);
    }

    closeNamespace(definitionStream);

    includeHeaders(includeStream, Dependency::global_section);
    includeHeaders(includeStream, Dependency::private_section);

    return serializeStreams();
}

}

