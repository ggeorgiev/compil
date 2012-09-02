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

#include "c++_h_generator.h"
#include "object_factory.h"

#include <boost/foreach.hpp>

#include <algorithm>

namespace compil
{

const int CppHeaderGenerator::copyrightStream = 0;
const int CppHeaderGenerator::includeStream = 1;
const int CppHeaderGenerator::declarationStream = 2;
const int CppHeaderGenerator::inlineDefinitionStream = 3;
const int CppHeaderGenerator::forwardDeclarationStream = 4;

CppHeaderGenerator::CppHeaderGenerator()
{
    for (int i = 0; i <= 4; ++i)
    {
        mStreams.push_back(boost::shared_ptr<std::stringstream>(new std::stringstream()));
        mIndent.push_back(0);
    }
}

CppHeaderGenerator::~CppHeaderGenerator()
{
}

void CppHeaderGenerator::encapsulateInLine(int streamIndex, const std::string& encapsulation)
{
    if (mEncapsulation != encapsulation)
    {
        mEncapsulation = encapsulation;
        line()  << mEncapsulation
                << ":";
        eol(streamIndex, -1);
    }
}

void CppHeaderGenerator::encapsulateInTable(const std::string& encapsulation)
{
    if (mEncapsulation != encapsulation)
    {
        mEncapsulation = encapsulation;
        table() << TableAligner::row_line(-1)
                << mEncapsulation
                << ":";
    }
}

void CppHeaderGenerator::generateImport(const ImportSPtr& pImport)
{
}

void CppHeaderGenerator::generateForwardClassDeclarations(const TypeSPtr& pType)
{
    line()  << "class "
            << frm->cppClassType(pType)
            << ";";
    eol(forwardDeclarationStream);

    table() << TableAligner::row()
            << "typedef "
            << TableAligner::col()
            << *CreateDecoratedType(frm->cppClassType(pType), ptr)
            << TableAligner::col()
            << frm->cppRawPtrName(pType)
            << ";";

    addDependencies(impl->classPointerDependencies());

    if (impl->boost_smart_ptr_needed())
    {
        table() << TableAligner::row()
                << "typedef "
                << TableAligner::col()
                << *CreateDecoratedType(impl->boost_shared_ptr(frm->cppClassType(pType)))
                << TableAligner::col()
                << frm->cppSharedPtrName(pType)
                << ";";

        table() << TableAligner::row()
                << "typedef "
                << TableAligner::col()
                << *CreateDecoratedType(impl->boost_shared_const_ptr(frm->cppClassType(pType)))
                << TableAligner::col()
                << frm->cppSharedConstPtrName(pType)
                << ";";

        table() << TableAligner::row()
                << "typedef "
                << TableAligner::col()
                << *CreateDecoratedType(impl->boost_weak_ptr(frm->cppClassType(pType)))
                << TableAligner::col()
                << frm->cppWeakPtrName(pType)
                << ";";
    }
    eot(forwardDeclarationStream);
    eol(forwardDeclarationStream);
}

void CppHeaderGenerator::generateEnumerationValueConstDeclaration(const EnumerationValueSPtr& pEnumerationValue)
{
    EnumerationSPtr pEnumeration = pEnumerationValue->enumeration().lock();

    table() << TableAligner::row()
            << frm->enumValueName(pEnumerationValue)
            << ' '
            << TableAligner::col()
            << "= "
            << TableAligner::col();

    AbsoluteEnumerationValueSPtr pAbsoluteValue =
        ObjectFactory::downcastAbsoluteEnumerationValue(pEnumerationValue);
    if (pAbsoluteValue)
    {
        if (pAbsoluteValue->value() == LONG_MIN)
            table() << "0,";
        else
        if (pAbsoluteValue->value() == LONG_MAX)
        {
            table() << frm->all_bitmask(pEnumeration->getMaxValue() + 1)
                    << ",";
        }
        else
        {
            if (pEnumeration->flags())
                table() << "1 << ";

            table() << frm->value(pAbsoluteValue->value())
                    << ",";
        }
    }

    ComposedEnumerationValueSPtr pComposedValue =
        ObjectFactory::downcastComposedEnumerationValue(pEnumerationValue);
    if (pComposedValue)
    {
        bool bFirst = true;
        BOOST_FOREACH(EnumerationValueSPtr pValue, pComposedValue->values())
        {
            if (bFirst)
                bFirst = false;
            else
                table() << " "
                        << TableAligner::col()
                        << "| ";
            table() << frm->enumValueName(pValue);
        }
        table() << ",";
    }
}

void CppHeaderGenerator::generateEnumerationValueDeclaration(const EnumerationValueSPtr& pEnumerationValue)
{
    EnumerationSPtr pEnumeration = pEnumerationValue->enumeration().lock();
    StructureSPtr pStructure = pEnumeration->structure().lock();

    SimpleType type;
    if (pEnumeration->cast() == CastableType::ECast::weak())
        type = impl->cppType(pEnumeration->parameterType().lock());
    else if (pEnumeration->cast() == CastableType::ECast::strong())
        type = frm->cppInnerEnumType(pEnumeration, pStructure);
    else
        assert(false && "unknown enumeration cast");

    if (pEnumerationValue->comment())
        commentInTable(pEnumerationValue->comment());

    table() << TableAligner::row()
            << Function(sttc,
                        *CreateDecoratedType(cst, type),
                        frm->methodName(pEnumerationValue->name()->value()))
            << ";";
}

void CppHeaderGenerator::generateEnumerationDeclaration(const EnumerationSPtr& pEnumeration)
{
    TypeSPtr pParameterType = pEnumeration->parameterType().lock();
    StructureSPtr pStructure = pEnumeration->structure().lock();

    DecoratedType innerType = *CreateDecoratedType(impl->cppInnerType(pEnumeration, pStructure));
    DecoratedType innerDecoratedType = impl->cppInnerDecoratedType(pEnumeration, pStructure);

    addDependencies(impl->dependencies(pEnumeration));
    addDependencies(impl->dependencies(pParameterType));
    addDependencies(impl->classPointerDependencies());

    if (!pEnumeration->structure().lock())
    {
        generateForwardClassDeclarations(pEnumeration);
    }

    commentInLine(declarationStream,
        "This enumeration class provides namespaced set of constant values.");
    if (pEnumeration->cast() == CastableType::ECast::strong())
    {
        commentInLine(declarationStream,
            "It is designed to provide type control over operations with enum values without need "
            "to wait all compilers you are going to use for this project to support C++0x standard. "
            "The type control do not prevent the variables to be used in switch statements.");
    }

    line()  << "class "
            << frm->cppInnerEnumType(pEnumeration, pStructure);

    std::string inheritClass = impl->inheritClass(pEnumeration, pStructure);
    if (!inheritClass.empty())
    {
        line()  << " : public "
                << inheritClass;
    }

    openBlock(declarationStream);
    line()  << "public:";
    eol(declarationStream, -1);

    if (pEnumeration->flags())
        commentInTable("Default constructor - sets the value to nil");
    else
        commentInTable("Default constructor - sets the value to invalid");
    table() << TableAligner::row()
            << Constructor(frm->cppInnerEnumType(pEnumeration, pStructure))
            << ";";

    Modifier modifier;
    if (pEnumeration->cast() == CastableType::ECast::strong())
        modifier = expl;

    commentInTable("Constructor from an integer value.");
    if (pEnumeration->cast() == CastableType::ECast::strong())
    {
        commentInTable(
            "Note: Avoid using this constructor if possible. It is appropriate only in case of "
            "importing value from components that you do not have control over (such as "
            "3rd party libraries or serialization functionality).");
    }
    table() << TableAligner::row()
            << Constructor(modifier, frm->cppInnerEnumType(pEnumeration, pStructure),
                           Argument(impl->cppDecoratedType(pParameterType), "value"))
            << ";";

    table() << TableAligner::row();

    commentInTable("Returns the integer value of the enum.");
    if (pEnumeration->cast() == CastableType::ECast::strong())
    {
        commentInTable(
            "Note: Avoid using this method if possible. It is appropriate only in case of "
            "exporting value to components that you do not have control over (such as "
            "3rd party libraries or serialization functionality).");
    }

    table() << TableAligner::row()
            << Function(impl->cppDecoratedType(pParameterType), fnValue, cst)
            << ";";

    commentInTable("Returns short name for a specified enum value");
    table() << TableAligner::row()
            << Function(sttc, const_char_ptr, fnShortName,
                        Argument(impl->cppDecoratedType(pParameterType), "value"))
            << ";";

    commentInTable("Returns short name of the enum value");
    table() << TableAligner::row()
            << Function(const_char_ptr, fnShortName, cst)
            << ";";

    if (pEnumeration->cast() == CastableType::ECast::strong())
    {
        commentInTable("returns true if the value of the enum is equal to the value of the argument");
        table() << TableAligner::row()
                << Function(bl, fnOperatorEq,
                            Argument(innerDecoratedType, "rValue"), cst)
                << ";";

        commentInTable("returns true if the value of the enum is not equal to the value of the argument");
        table() << TableAligner::row()
                << Function(bl, fnOperatorNe,
                            Argument(innerDecoratedType, "rValue"), cst)
                << ";";
    }
    else if (pEnumeration->cast() == CastableType::ECast::weak())
    {
        commentInTable("Cast operator that casts the enum to its native type");
        table() << TableAligner::row()
                << Function(CastOperator(impl->cppDecoratedType(pParameterType)), cst)
                << ";";
    }

    if (impl->implementFlagsEnumerationMethods(pEnumeration))
    {
        commentInTable("Resets the flags included in the mask to the state in value");
        table() << TableAligner::row()
                << Function(vd, fnReset,
                            Argument(innerDecoratedType, "mask"),
                            Argument(innerDecoratedType, "value"))
                << ";";

        commentInTable("Sets the flags included in the mask. Equivalent to reset(mask, all).");
        table() << TableAligner::row()
                << Function(vd, fnSet,
                            Argument(innerDecoratedType, "mask"))
                << ";";

        commentInTable("Clears the flags included in the mask. Equivalent to reset(mask, nil).");
        table() << TableAligner::row()
                << Function(vd, fnClear,
                            Argument(innerDecoratedType, "mask"))
                << ";";

        commentInTable("Turns the flags included in the mask.");
        table() << TableAligner::row()
                << Function(vd, fnTurn,
                            Argument(innerDecoratedType, "mask"))
                << ";";


        commentInTable("Returns assemble of the current flags with the flags from the mask to "
                       "the state in value. This is immutable version of reset.");
        table() << TableAligner::row()
                << Function(innerType, fnAssemble,
                            Argument(innerDecoratedType, "mask"),
                            Argument(innerDecoratedType, "value"), cst)
                << ";";

        commentInTable("Returns combination of the flags included in the mask. "
                       "This is immutable version of set.");
        table() << TableAligner::row()
                << Function(innerType, fnCombine,
                            Argument(innerDecoratedType, "mask"), cst)
                << ";";

        commentInTable("Returns intersection of the flags included in the mask. "
                       "This is immutable version of clear.");
        table() << TableAligner::row()
                << Function(innerType, fnIntersect,
                            Argument(innerDecoratedType, "mask"), cst)
                << ";";

        commentInTable("Returns flipped the flags included in the mask. "
                       "This is immutable version of turn.");
        table() << TableAligner::row()
                << Function(innerType, fnFlip,
                            Argument(innerDecoratedType, "mask"), cst)
                << ";";

        commentInTable("Tests if the flags included in the mask are the same state as state in value");
        table() << TableAligner::row()
                << Function(bl, fnTest,
                            Argument(innerDecoratedType, "mask"),
                            Argument(innerDecoratedType, "value"), cst)
                << ";";

        commentInTable("Tests if the flags included in the mask are set. Equivalent to test(mask, all).");
        table() << TableAligner::row()
                << Function(bl, fnIsSet,
                            Argument(innerDecoratedType, "mask"), cst)
                << ";";

        commentInTable("Tests if the flags included in the mask are clear. Equivalent to test(mask, nil).");
        table() << TableAligner::row()
                << Function(bl, fnIsClear,
                            Argument(innerDecoratedType, "mask"), cst)
                << ";";
    }

    eot(declarationStream);
    eol(declarationStream);

    commentInTable("static methods for enum class objects");

    if (pEnumeration->flags())
        generateEnumerationValueDeclaration(Model::nilEnumerationValue(pEnumeration));
    else
        generateEnumerationValueDeclaration(Model::invalidEnumerationValue(pEnumeration));

    const std::vector<EnumerationValueSPtr>& enumerationValues = pEnumeration->enumerationValues();
    std::vector<EnumerationValueSPtr>::const_iterator it;
    for (it = enumerationValues.begin(); it != enumerationValues.end(); ++it)
    {
        generateEnumerationValueDeclaration(*it);
    }
    if (pEnumeration->flags())
        generateEnumerationValueDeclaration(Model::allEnumerationValue(pEnumeration));

    eot(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
            "This enum provides static constants that could be used in a switch statements");
    line() << "enum";
    openBlock(declarationStream);

    if (pEnumeration->flags())
        generateEnumerationValueConstDeclaration(Model::nilEnumerationValue(pEnumeration));
    else
        generateEnumerationValueConstDeclaration(Model::invalidEnumerationValue(pEnumeration));
    for (it = enumerationValues.begin(); it != enumerationValues.end(); ++it)
        generateEnumerationValueConstDeclaration(*it);
    if (pEnumeration->flags())
        generateEnumerationValueConstDeclaration(Model::allEnumerationValue(pEnumeration));

    eot(declarationStream);
    closeBlock(declarationStream, "};");
    eol(declarationStream);

    if (impl->implementEnumerationMethods(pEnumeration))
    {
        line()  << "private:";
        eol(declarationStream, -1);

        commentInTable("Member variable that holds the enum value");
        table() << TableAligner::row()
                << impl->cppDecoratedType(pParameterType)
                << TableAligner::col()
                << frm->memberName("value") << ";";
        eot(declarationStream);
    }

    closeBlock(declarationStream, "};");
    eol(declarationStream);
}

void CppHeaderGenerator::generateSpecimenDeclaration(const SpecimenSPtr& pSpecimen)
{
    TypeSPtr pParameterType = pSpecimen->parameterType().lock();

    addDependencies(impl->dependencies(pParameterType));
    addDependencies(impl->classReferenceDependencies());

    generateForwardClassDeclarations(pSpecimen);

    line()  << "class " << frm->cppClassType(pSpecimen);
    openBlock(declarationStream);
    line()  << "public:";
    eol(declarationStream, -1);

    table() << TableAligner::row()
            << Constructor(frm->cppClassType(pSpecimen))
            << ";";

    table() << TableAligner::row();
    table() << Constructor(expl, frm->cppClassType(pSpecimen),
                           Argument(impl->cppDecoratedType(pParameterType), "value"))
            << ";";

    table() << TableAligner::row()
            << TableAligner::row()
            << "inline "
            << Function(*CreateDecoratedType(impl->cppType(pParameterType)), fnValue, cst)
            << ";";

    table() << TableAligner::row()
            << "inline "
            << Function(bl, fnOperatorEq,
                        Argument(impl->cppDecoratedType(pSpecimen), "rValue"), cst)
            << ";";

    table() << TableAligner::row()
            << "inline "
            << Function(bl, fnOperatorNe,
                        Argument(impl->cppDecoratedType(pSpecimen), "rValue"), cst)
            << ";";

    table() << TableAligner::row()
            << "inline "
            << Function(bl, fnOperatorLt,
                        Argument(impl->cppDecoratedType(pSpecimen), "rValue"), cst)
            << ";";

    eot(declarationStream);
    
    fdef()  << TableAligner::row()
            << "inline "
            << Function(*CreateDecoratedType(frm->cppSharedPtrName(pSpecimen)),
                        frm->methodName(frm->cppRefName(pSpecimen->name()->value())));
    openBlock(inlineDefinitionStream);
    line()  << "return boost::make_shared<"
            << frm->cppClassType(pSpecimen)
            << ">();";
    closeBlock(inlineDefinitionStream);
    eol(inlineDefinitionStream);
    
    fdef()  << TableAligner::row()
            << "inline "
            << Function(*CreateDecoratedType(frm->cppSharedPtrName(pSpecimen)),
                        frm->methodName(frm->cppRefName(pSpecimen->name()->value())),
                        Argument(impl->cppDecoratedType(pParameterType), "value"));
    openBlock(inlineDefinitionStream);
    line()  << "return boost::make_shared<"
            << frm->cppClassType(pSpecimen)
            << ">(value);";
    closeBlock(inlineDefinitionStream);
    eol(inlineDefinitionStream);
    
    fdef()  << TableAligner::row()
            << "inline "
            << Function(*CreateDecoratedType(impl->cppType(pParameterType)),
                        frm->cppClassNamespace(pSpecimen), fnValue, cst);
    openBlock(inlineDefinitionStream);
    line()  << "return "
            << frm->memberName("value")
            << ";";
    closeBlock(inlineDefinitionStream);
    eol(inlineDefinitionStream);

    fdef()  << TableAligner::row()
            << "inline "
            << Function(bl, frm->cppClassNamespace(pSpecimen), fnOperatorEq,
                        Argument(impl->cppDecoratedType(pSpecimen), "rValue"), cst);
    openBlock(inlineDefinitionStream);
    line()  << "return "
            << frm->memberName("value")
            << " == rValue."
            << frm->memberName("value")
            << ";";
    closeBlock(inlineDefinitionStream);
    eol(inlineDefinitionStream);

    fdef()  << TableAligner::row()
            << "inline "
            << Function(bl, frm->cppClassNamespace(pSpecimen), fnOperatorNe,
                        Argument(impl->cppDecoratedType(pSpecimen), "rValue"), cst);
    openBlock(inlineDefinitionStream);
    line()  << "return "
            << frm->memberName("value")
            << " != rValue."
            << frm->memberName("value")
            << ";";
    closeBlock(inlineDefinitionStream);
    eol(inlineDefinitionStream);

    fdef()  << TableAligner::row()
            << "inline "
            << Function(bl, frm->cppClassNamespace(pSpecimen), fnOperatorLt,
                        Argument(impl->cppDecoratedType(pSpecimen), "rValue"), cst);
    openBlock(inlineDefinitionStream);
    line()  << "return "
            << frm->memberName("value")
            << " < rValue."
            << frm->memberName("value")
            << ";";
    closeBlock(inlineDefinitionStream);
    eol(inlineDefinitionStream);

    line()  << "private:";
    eol(declarationStream, -1);
    table() << TableAligner::row()
            << impl->cppType(pParameterType)
            << " "
            << TableAligner::col()
            << frm->memberName("value")
            << ";";
    eot(declarationStream);

    closeBlock(declarationStream, "};");
    eol(declarationStream);
}

void CppHeaderGenerator::generateHierarchyFactoryDeclaration(const FactorySPtr& pFactory)
{
    TypeSPtr pParameterType = pFactory->parameterType().lock();
    addDependencies(impl->dependencies(pParameterType));

    generateForwardClassDeclarations(pFactory);

    StructureSPtr pParameterStructure = ObjectFactory::downcastStructure(pParameterType);

    EnumerationSPtr pEnumeration = impl->objectEnumeration(mpModel, pFactory);
    generateEnumerationDeclaration(pEnumeration);

    line()  << "class "
            << frm->cppClassType(pFactory)
            << ";";
    eol(forwardDeclarationStream);
    eol(forwardDeclarationStream);

    line()  << "class "
            << frm->cppClassType(pFactory);
    openBlock(declarationStream);
    line()  << "public:";
    eol(declarationStream, -1);

    if (!pParameterStructure->abstract())
    {
        table() << TableAligner::row()
                << Function(sttc, *CreateDecoratedType(impl->cppPtrType(pParameterType)),
                            fnClone, Argument(impl->cppPtrDecoratedType(pParameterType), "pObject"))
                << ";";
    }

    std::vector<StructureSPtr> structs = impl->hierarchie(mpModel,
                                                          pParameterStructure,
                                                          &Structure::hasRuntimeIdentification);

    std::vector<StructureSPtr>::const_iterator it;
    for (it = structs.begin(); it != structs.end(); ++it)
    {
        StructureSPtr pStructure = *it;
        if (pParameterStructure == pStructure) continue;

        addDependencies(impl->dependencies(pStructure));

        table() << TableAligner::row()
                << Function(sttc, *CreateDecoratedType(impl->cppPtrType(pStructure)),
                            *functionNameRef(fnDowncast.value() + pStructure->name()->value()),
                            Argument(impl->cppPtrDecoratedType(pParameterStructure), "pObject"))
                << ";";
    }

    eot(declarationStream);

    closeBlock(declarationStream, "};");
    eol(declarationStream);
}

void CppHeaderGenerator::generateObjectFactoryDeclaration(const FactorySPtr& pFactory)
{
    StructureSPtr pParameterStructure = ObjectFactory::downcastStructure(pFactory->parameterType().lock());

    if (!pFactory->function())
    {
        line()  << "class "
                << frm->cppClassType(pFactory)
                << ";";
        eol(forwardDeclarationStream);
        eol(forwardDeclarationStream);

        line()  << "class "
                << frm->cppClassType(pFactory);

        openBlock(declarationStream);
        line()  << "public:";
        eol(declarationStream, -1);
    }

    Modifier modifier;
    FunctionName functionName;
    if (pFactory->function())
    {
        functionName = *functionNameRef(pFactory->name()->value());
    }
    else
    {
        modifier = sttc;
        functionName = fnCreate;
    }

    if (!pParameterStructure->abstract())
    {
        std::vector<compil::FieldSPtr> iteration;
        while (pParameterStructure->fieldIterate(iteration))
        {
            Function function(modifier,
                              *CreateDecoratedType(impl->cppPtrType(pParameterStructure)),
                              functionName);

            std::vector<compil::FieldSPtr>::iterator it;
            for (it = iteration.begin(); it != iteration.end(); ++it)
                function << Argument(impl->cppSetDecoratedType((*it)->type()),
                                     frm->cppVariableName(*it));

            table() << TableAligner::row()
                    << function
                    << ";";
        }
        eot(declarationStream);
    }

    if (!pFactory->function())
    {
        closeBlock(declarationStream, "};");
    }
    eol(declarationStream);
}

void CppHeaderGenerator::generatePluginFactoryDeclaration(const FactorySPtr& pFactory)
{
    StructureSPtr pParameterType = Structure::downcast(pFactory->parameterType().lock());
    addDependencies(impl->dependencies(pParameterType));

    generateForwardClassDeclarations(pFactory);

    commentInLine(declarationStream,
        "This class is a plugin object factory designed to provide functionality for objects"
        " from several layers without creating explicit dependency on all of them."
        " It is designed to be initialized from the CRT initialization process and used"
        " read only application runtime. This is why it does not provide any additional thread"
        " safety. If needed for other scenarios, the thread safety needs to be provided from"
        " outside." );
    line()  << "class "
            << frm->cppClassType(pFactory);
    openBlock(declarationStream);
    line()  << "public:";
    eol(declarationStream, -1);

    commentInLine(declarationStream,
        "Clone function pointer type");
    line()  << "typedef "
            << frm->cppRawPtrName(pParameterType)
            << " (*"
            << cloneFunction
            << ")("
            << impl->cppDecoratedType(pParameterType)
            << "object);";
    eol(declarationStream);

    addDependency(Dependency("utility",
                             Dependency::system_type,
                             Dependency::stl_level,
                             Dependency::private_section,
                             "Standard Template Library"));
    commentInLine(declarationStream,
        "Relationship pair<parent, child> type");
    line()  << "typedef std::pair<size_t, size_t> Pair;";
    eol(declarationStream);
    eol(declarationStream);

    commentInTable("Default constructor");
    table() << TableAligner::row()
            << Constructor(frm->cppClassType(pFactory))
            << ";";

    commentInTable("Destructor");
    table() << TableAligner::row()
            << Destructor(frm->cppClassType(pFactory))
            << ";";

    table() << TableAligner::row();

    commentInTable(
        "Register clone function method. Use to register objects that the factory"
        " needs to support");
    table() << TableAligner::row()
            << Function(sttc, bl, fnRegisterCloneFunction,
                        Argument(st, "object"), Argument(cloneFunction, "function"))
            << ";";

    table() << TableAligner::row();


    commentInTable(
        "Register relationship method. Use to register relationships between objects.");
    table() << TableAligner::row()
            << Function(sttc, bl, fnRegisterRelationship,
                        Argument(st, "parent"), Argument(st, "child"))
            << ";";

    commentInTable(
        "Returns is the parent/child pair is registered in the factory.");
    table() << TableAligner::row()
            << Function(sttc, bl, fnIsParent,
                        Argument(st, "parent"), Argument(st, "child"))
            << ";";

    table() << TableAligner::row();

    addDependency(impl->assert_dependency());
    commentInTable(
        "Clone template method based on already registered objects."
        " This allows objects from upper layer to be cloned correctly producing"
        " clone object from the same class as the original object without"
        " creating circular dependency.");
    table() << TableAligner::row_line()
            << "template<class T>";
    table() << TableAligner::row()
            << Function(sttc, TPtr, fnClone, Argument(cstTRef, "object"));
    table() << TableAligner::row_line()
            << "{";
    table() << TableAligner::row_line(1)
            << impl->assert_method()
            << "("
            << fnIsDerivedFrom
            << "<T>(object));";
    table() << TableAligner::row_line(1)
            << "  return (T*)get().cloneFunctions[object."
            << impl->runtimeMethodName(fnInprocId.value())
            << "()](object);";
    table() << TableAligner::row_line()
            << "}";

    table() << TableAligner::row();

    commentInTable(
        "IsDerivedFrom template method returns true based on already registered objects"
        " if the argument object is from the same class or a derived one from the argument class.");
    table() << TableAligner::row_line()
            << "template<class T>";
    table() << TableAligner::row()
            << Function(sttc, bl, fnIsDerivedFrom,
                        Argument(impl->cppDecoratedType(pParameterType), "object"));
    table() << TableAligner::row_line()
            << "{";
    table() << TableAligner::row_line(1)
            << "return (T::"
            << impl->staticMethodName(fnInprocId.value())
            << "() == object."
            << impl->runtimeMethodName(fnInprocId.value())
            << "())";
    table() << TableAligner::row_line(3)
            << "|| "
            << fnIsParent
            << "(T::"
            << impl->staticMethodName(fnInprocId.value())
            << "(), object."
            << impl->runtimeMethodName(fnInprocId.value())
            << "());";
    table() << TableAligner::row_line()
            << "}";

    commentInTable(
        "The same as previous one. Just a helper that accepts pointer instead of an object.");
    table() << TableAligner::row_line()
            << "template<class T>";
    table() << TableAligner::row()
            << Function(sttc, bl, fnIsDerivedFrom,
                        Argument(impl->cppPtrDecoratedType(pParameterType), "object"));
    table() << TableAligner::row_line()
            << "{";
    table() << TableAligner::row_line(1)
            << "return "
            << fnIsDerivedFrom
            << "<T>(*object);";
    table() << TableAligner::row_line()
            << "}";

    table() << TableAligner::row()
            << TableAligner::row_line(-1)
            << "protected:";

    commentInTable(
        "Global singleton accessor.");
    table() << TableAligner::row()
            << Function(sttc, *CreateDecoratedType(frm->cppClassType(pFactory), ref), fnGet)
            << ";";

    eot(declarationStream);

    addDependency(impl->unordered_map_dependency());

    commentInTable(
        "Member variable for clone functions.");
    table() << TableAligner::row()
            << "boost::unordered_map<size_t, "
            << cloneFunction.type()
            << "> "
            << TableAligner::col()
            << "cloneFunctions;";
    eol(declarationStream);

    addDependency(impl->unordered_set_dependency());
    commentInTable(
        "Member variable for relationship pairs.");
    table() << TableAligner::row()
            << "boost::unordered_set<Pair> "
            << TableAligner::col()
            << "relationships;";
    eot(declarationStream);

    closeBlock(declarationStream, "};");
    eol(declarationStream);
}

void CppHeaderGenerator::generateFactoryDeclaration(const FactorySPtr& pFactory)
{
    switch (pFactory->type().value())
    {
        case Factory::EType::kHierarchy:
            generateHierarchyFactoryDeclaration(pFactory);
            break;
        case Factory::EType::kObject:
            generateObjectFactoryDeclaration(pFactory);
            break;
        case Factory::EType::kPlugin:
            generatePluginFactoryDeclaration(pFactory);
            break;
        default:
            assert(false && "unknown factory type");
    }
}

void CppHeaderGenerator::generateIdentifierDeclaration(const IdentifierSPtr& pIdentifier)
{
    TypeSPtr pParameterType = pIdentifier->parameterType().lock();

    addDependencies(impl->dependencies(pParameterType));

    line()  << "class "
            << frm->cppClassType(pIdentifier)
            << ";";
    eol(forwardDeclarationStream);
    eol(forwardDeclarationStream);

    line()  << "class "
            << frm->cppClassType(pIdentifier);
    openBlock(declarationStream);
    line()  << "public:";
    eol(declarationStream, -1);

    table() << TableAligner::row()
            << Constructor(frm->cppClassType(pIdentifier))
            << ";";

    Modifier modifier;
    if (pIdentifier->cast() == CastableType::ECast::strong())
        modifier = expl;
    table() << TableAligner::row()
            << Constructor(modifier, frm->cppClassType(pIdentifier),
                           Argument(impl->cppDecoratedType(pParameterType), "value"))
            << ";";

    table() << TableAligner::row()
            << TableAligner::row()
            << Function(impl->cppDecoratedType(pParameterType), fnValue, cst)
            << ";";

    if (pIdentifier->cast() == CastableType::ECast::strong())
    {
        table() << TableAligner::row()
                << Function(bl, fnOperatorEq,
                            Argument(impl->cppDecoratedType(pIdentifier), "rValue"), cst)
                << ";";

        table() << TableAligner::row()
                << Function(bl, fnOperatorNe,
                            Argument(impl->cppDecoratedType(pIdentifier), "rValue"), cst)
                << ";";
    }
    else if (pIdentifier->cast() == CastableType::ECast::weak())
    {
        table() << TableAligner::row()
                << Function(CastOperator(impl->cppDecoratedType(pParameterType)), cst)
                << ";";
    }
    eot(declarationStream);

    line()  << "private:";
    eol(declarationStream, -1);
    table() << TableAligner::row()
            << impl->cppDecoratedType(pParameterType)
            << TableAligner::col()
            << frm->memberName("value")
            << ";";
    eot(declarationStream);

    closeBlock(declarationStream, "};");
    eol(declarationStream);
}

void CppHeaderGenerator::generateStructureIdentificationMethodsDeclaration(
        const IdentificationSPtr& pIdentification)
{
    switch (pIdentification->type().value())
    {
        case Identification::EType::kRuntime:
            generateStructureRuntimeIdentificationMethodsDeclaration(pIdentification);
            break;
        case Identification::EType::kInproc:
            generateStructureInprocIdentificationMethodsDeclaration(pIdentification);
            break;
        default:
            assert(false);
    }
}

void CppHeaderGenerator::generateStructureRuntimeIdentificationMethodsDeclaration(
        const IdentificationSPtr& pIdentification)
{
    StructureSPtr pStructure = pIdentification->structure().lock();
    StructureSPtr pBaseStructure = pStructure->recursivelyBaseStructure();

    line()  << "class "
            << impl->identificationEnum(pBaseStructure)
            << ";";
    eol(forwardDeclarationStream);
    eol(forwardDeclarationStream);

    table() << TableAligner::row();

    commentInTable(
            "Identifier for the objects from " + frm->cppMainClassType(pStructure).value() + " class.");
    commentInTable(
            "Note: it is not defined in the "
            "respective cpp file. Instead it is defined in the factory class together with "
            "all the other identifiers of the other class objects. This allows all identifiers "
            "to be maintained from a single place, which reduces the risk of value collisions");

    table() << TableAligner::row()
            << Function(sttc,
                        *CreateDecoratedType(impl->identificationEnum(pBaseStructure)),
                        impl->staticIdentificationMethodName(pBaseStructure))
            << ";";

    commentInTable(
            "This virtual method provides runtime object identification based on the polymorphic "
            "behavior of the virtual methods. Allows having a RTTI like mechanism significantly "
            "cheaper than the RTTI provided by the compilers themselves.");

    table() << TableAligner::row()
            << Function(vrtl,
                        *CreateDecoratedType(impl->identificationEnum(pBaseStructure)),
                        impl->runtimeIdentificationMethodName(pBaseStructure),
                        cst)
            << ";";
}

void CppHeaderGenerator::generateStructureInprocIdentificationMethodsDeclaration(
        const IdentificationSPtr& pIdentification)
{
    StructureSPtr pStructure = pIdentification->structure().lock();

    table() << TableAligner::row();

    if (!pStructure->abstract())
    {
        std::vector<FactorySPtr> factories = mpModel->findPluginFactories(pStructure);
        for (std::vector<FactorySPtr>::iterator it = factories.begin(); it != factories.end(); ++it)
        {
            const FactorySPtr& factory = *it;
            StructureSPtr pParameterType = Structure::downcast(factory->parameterType().lock());

            commentInTable(
                "Static clone method that implements the plugin factory " + factory->name()->value() +
                " clone function prototype. It will be registered in the factory for potential use from its"
                " clone method. Most likely you will never need to use this method from anywhere else.");
            table() << TableAligner::row()
                    << Function(sttc, frm->cppRawPtrDecoratedType(pParameterType), fnClone,
                                Argument(impl->cppDecoratedType(pParameterType), "object"))
                    << ";";
        }
    }

    commentInTable(
            "Inproc identifier for the objects from " +
            frm->cppMainClassType(pStructure).value() + " class.");
    commentInTable(
            "Note: this identificator is unique just for the process session. "
            "There is no guarantee that the id will be the same from session to session. "
            "Do not use for serialization.");

    table() << TableAligner::row()
            << Function(sttc, st, impl->staticMethodName(fnInprocId.value()))
            << ";";

    commentInTable(
            "This virtual method provides runtime inproc object identification based on the polymorphic "
            "behavior of the virtual methods. Allows having a RTTI like mechanism significantly "
            "cheaper than the RTTI provided by the compilers themselves.");
    table() << TableAligner::row()
            << Function(vrtl, st, impl->runtimeMethodName(fnInprocId.value()), cst)
            << ";";
}

void CppHeaderGenerator::generateStructureOperatorMethodsDeclaration(
                    const OperatorSPtr& pOperator,
                    const EOperatorFlags& flags,
                    bool& declaredFunctor)
{
    if (!pOperator->flags().isSet(flags))
        return;

    table() << TableAligner::row();

    FunctionName fnOperator;
    FunctionName fnFunction;
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

    FunctionName fnName;
    if (flags.isSet(EOperatorFlags::functor()))
    {
        fnName = fnOperatorFn;
        if (!declaredFunctor)
        {
            table() << TableAligner::row_line()
                    << "struct "
                    << fnFunction
                    << " {";
            declaredFunctor = true;
        }
    }
    else
    {
        if (flags.isSet(EOperatorFlags::native()))
            fnName = fnOperator;
        else
            fnName = fnFunction;
    }

    int arguments = 1;
    if (flags.isClear(EOperatorFlags::member()) || flags.isSet(EOperatorFlags::functor()))
        arguments = 2;

    Modifier modifier;
    if (flags.isSet(EOperatorFlags::internal()) && flags.isClear(EOperatorFlags::functor()))
        modifier = sttc;

    StructureSPtr pStructure = pOperator->structure().lock();

    DecoratedType type;
    if (flags.isSet(EOperatorFlags::object()))
        type = impl->cppDecoratedType(pStructure);
    else
    if (flags.isSet(EOperatorFlags::reference()))
        type = impl->cppPtrDecoratedType(pStructure);
    else
        assert(false && "unknown operator parameter");

    Declaration declaration;
    if (flags.isSet(EOperatorFlags::member()) || flags.isSet(EOperatorFlags::functor()))
        declaration = cst;

    if (arguments == 1)
    {
        table() << TableAligner::row()
                << Function(modifier, bl, fnName,
                            Argument(type, "object"), declaration)
                << ";";
    }
    else
    {
        table() << TableAligner::row()
                << Function(modifier, bl, fnName,
                            Argument(type, "object1"),
                            Argument(type, "object2"), declaration)
                << ";";
    }
}

void CppHeaderGenerator::generateStructureOperatorMethodsDeclaration(
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

            bool declaredFunctor = false;

            for (int p = 0; p < 2; ++p)
            {
                switch (p)
                {
                    case 0: flags.reset(EOperatorFlags::parameter(), EOperatorFlags::object()); break;
                    case 1: flags.reset(EOperatorFlags::parameter(), EOperatorFlags::reference()); break;
                }

                generateStructureOperatorMethodsDeclaration(pOperator, flags, declaredFunctor);
            }

            if (declaredFunctor)
            {
                table() << TableAligner::row_line()
                        << "};";
            }
        }
    }
}

void CppHeaderGenerator::generateStructureFieldMemberDeclaration(const FieldSPtr& pField)
{
    StructureSPtr pStructure = pField->structure().lock();

    addDependencies(impl->dependencies(pField));

    commentInTable("variable for the data field " + pField->name()->value());

    table() << TableAligner::row()
            << impl->cppInnerType(pField->type(), pStructure)
            << ' '
            << TableAligner::col()
            << frm->cppMemberName(pField)
            << ";";
}

void CppHeaderGenerator::generateStructureObjectMemberDeclaration(const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kField:
        {
            FieldSPtr pField = boost::static_pointer_cast<Field>(pObject);
            generateStructureFieldMemberDeclaration(pField);
            break;
        }
        case EObjectId::kOperator:
        case EObjectId::kIdentification:
        case EObjectId::kUpcopy:
        case EObjectId::kEnumeration:
        case EObjectId::kAlter:
        case EObjectId::kFieldOverride:
            break;
        default:
            assert(false);
    }
}

void CppHeaderGenerator::generateStructureFieldMethodsDeclaration(const StructureSPtr& pCurrStructure,
                                                                  const FieldSPtr& pField,
                                                                  StructureObjectType sot)
{
    StructureSPtr pStructure = pField->structure().lock();

    if (!table().isEmpty())
        table() << TableAligner::row();

    if (((sot & READING) != 0) && ((sot & SPECIFIC_RESULT_ONLY) == 0))
    {
        if (pField->comment())
            commentInTable(pField->comment());

        commentInTable("Getter method for the data field " + pField->name()->value());

        table() << TableAligner::row()
                << Function(impl->cppInnerDecoratedType(pField->type(), pCurrStructure),
                            frm->getMethodName(pField), cst)
                << ";";

        if (pStructure->controlled())
        {
            if (pField->defaultValue())
            {
                if (pField->defaultValue()->optional())
                    commentInTable("Checks if the optional field " + pField->name()->value() + " exists");
                else
                    commentInTable("Returns true if the data field value " + pField->name()->value() +
                                   " was changed from its default value " + frm->defaultValue(pField));
            }
            else
            {
                commentInTable(
                    "Returns true if the data field " + pField->name()->value() +
                    " was set and could be considered valid");

                if (pStructure->immutable())
                {
                    commentInTable(
                        "Note: If the class is used properly it should always return true. "
                        "It makes sense when it is called indirectly through " + fnIsInitialized.value() +
                        "() from the Builder class");
                }
            }
            table() << TableAligner::row()
                    << Function(bl, frm->availableMethodName(pField), cst)
                    << ";";
        }

        if (pField->defaultValue() && !pField->defaultValue()->optional())
        {
            commentInTable(
                "Returns the default value " + frm->defaultValue(pField) +
                " of the field " + pField->name()->value());

            table() << TableAligner::row()
                    << Function(sttc, *CreateDecoratedType(impl->cppType(pField->type())),
                                frm->defaultMethodName(pField))
                    << ";";
        }
    }

    DecoratedType resultType;
    if ((sot & BUILDER) == 0)
        resultType = *CreateDecoratedType(impl->cppType(pCurrStructure), ref);
    else
        resultType = *CreateDecoratedType(builder, ref);

    if ((sot & WRITING) != 0)
    {
        if ((sot & BUILDER) == 0)
        {
            commentInTable("Setter method for the data field " + pField->name()->value());
        }
        else
        {
            if ((sot & OVERRIDDEN) == 0)
                commentInTable("Setter method for the data field " + pField->name()->value());
            else
                commentInTable("Hide setter method for the data field " + pField->name()->value() +
                               ", no implementation");
        }
        
        table() << TableAligner::row()
                << Function(resultType, frm->setMethodName(pField),
                            Argument(impl->cppInnerSetDecoratedType(pField->type(), pCurrStructure),
                                     frm->cppVariableName(pField)))
                << ";";
                
        if (pCurrStructure->streamable())
        {
            commentInTable("Store operator for the data field " + pField->name()->value());
            table() << TableAligner::row()
                    << Function(resultType, fnOperatorStore,
                                Argument(impl->cppInnerSetDecoratedType(pField->type(), pCurrStructure),
                                         frm->cppVariableName(pField)))
                    << ";";
                    
            UnaryContainerSPtr pUnaryContainer = ObjectFactory::downcastUnaryContainer(pField->type());
            if (pUnaryContainer)
            {
                commentInTable("Store operator for an item of data field " + pField->name()->value());
                table() << TableAligner::row()
                        << Function(resultType, fnOperatorStore,
                                    Argument(impl->cppInnerSetDecoratedType(pUnaryContainer->parameterType().lock(), 
                                             pCurrStructure), frm->cppVariableName(pField)+ "Item"))
                        << ";";
            }
        }        
    }

    if (pStructure->controlled())
    {
        if (((sot & WRITING) != 0) && ((sot & SPECIFIC_RESULT_ONLY) == 0))
        {
            if (impl->needMutableMethod(pField->type()))
            {
                table() << TableAligner::row()
                        << Function(*CreateDecoratedType(
                                        impl->cppInnerType(pField->type(), pStructure), ref),
                                    frm->mutableMethodName(pField))
                        << ";";
            }
            
            if (   pField->defaultValue()
                && !pField->defaultValue()->optional())
            {
                commentInTable("Update method for the data field " + pField->name()->value() +
                               ". If the new value is equal to the default it clears the field. Else"
                               " it behaves is the same as set");
                table() << TableAligner::row()
                        << Function(resultType, frm->updateMethodName(pField),
                                    Argument(impl->cppInnerSetDecoratedType(pField->type(), pCurrStructure),
                                             frm->cppVariableName(pField)))
                        << ";";
            }

            if (pField->defaultValue())
            {
                if (pField->defaultValue()->optional())
                    commentInTable("Clears the optional data field " + pField->name()->value());
                else
                    commentInTable("Resets the data field " + pField->name()->value() +
                                   " to its default value " + frm->defaultValue(pField));
            }
            else
            {
                commentInTable(
                    "Erases the required data field " + pField->name()->value() + ". Object can "
                    "not be instantiated before the field data is set again");
            }

            table() << TableAligner::row()
                    << Function(vd, frm->destroyMethodName(pField))
                    << ";";
        }
    }
}

void CppHeaderGenerator::generateStructureFieldOverrideMethodsDeclaration(const FieldOverrideSPtr& pFieldOverride,
                                                                          StructureObjectType sot)
{
    const FieldSPtr& pField = pFieldOverride->field();
    StructureSPtr pStructure = pField->structure().lock();

    if (((sot & READING) != 0) && ((sot & SPECIFIC_RESULT_ONLY) == 0))
    {
        if (pField->comment())
            commentInTable(pField->comment());

        if (!table().isEmpty())
            table() << TableAligner::row();

        commentInTable("Override getter method for the data field " + pField->name()->value());
        table() << TableAligner::row()
                << Function(*CreateDecoratedType(impl->cppInnerType(pField->type(), pStructure)),
                            frm->getMethodName(pField), cst)
                << ";";
    }

    if ((sot & WRITING) != 0)
    {
        if ((sot & BUILDER) != 0)
        {
            if (!table().isEmpty())
                table() << TableAligner::row();

            commentInTable("Override setter method for the data field " + pField->name()->value());
            table() << TableAligner::row()
                    << Function(*CreateDecoratedType(builder, ref), frm->setMethodName(pField),
                                Argument(impl->cppInnerSetDecoratedType(pField->type(), pStructure),
                                         frm->cppVariableName(pField)))
                    << ";";
        }
    }
}

void CppHeaderGenerator::generateStructureObjectMethodsDeclaration(const ObjectSPtr& pObject,
                                                                   StructureObjectType sot)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kField:
        {
            FieldSPtr pField = boost::static_pointer_cast<Field>(pObject);
            StructureSPtr pStructure = pField->structure().lock();
            generateStructureFieldMethodsDeclaration(pStructure, pField, sot);
            break;
        }
        case EObjectId::kFieldOverride:
        {
            FieldOverrideSPtr pFieldOverride = boost::static_pointer_cast<FieldOverride>(pObject);
            generateStructureFieldOverrideMethodsDeclaration(pFieldOverride, sot);
            break;
        }
        case EObjectId::kIdentification:
        {
            if ((sot & BUILDER) != 0)
                break;
            IdentificationSPtr pIdentification = boost::static_pointer_cast<Identification>(pObject);
            generateStructureIdentificationMethodsDeclaration(pIdentification);
            break;
        }
        case EObjectId::kUpcopy:
        {
            // UpcopySPtr pUpcopy = boost::static_pointer_cast<Upcopy>(pObject);
            break;
        }
        case EObjectId::kOperator:
        {
            if ((sot & BUILDER) != 0)
                break;
            OperatorSPtr pOperator = boost::static_pointer_cast<Operator>(pObject);
            generateStructureOperatorMethodsDeclaration(pOperator);
            break;
        }
        case EObjectId::kEnumeration:
        {
            if ((sot & BUILDER) != 0)
                break;

            if (!table().isEmpty())
            {
                eot(declarationStream);
                eol(declarationStream);
            }

            EnumerationSPtr pEnumeration = boost::static_pointer_cast<Enumeration>(pObject);
            generateEnumerationDeclaration(pEnumeration);
            break;
        }
        case EObjectId::kAlter:
        {
            if (((sot & READING) != 0) && ((sot & SPECIFIC_RESULT_ONLY) == 0))
            {
                AlterSPtr pAlter = boost::static_pointer_cast<Alter>(pObject);
                table() << TableAligner::row();
                commentInTable(
                    "Returns the alter value " + frm->defaultValue(pAlter) +
                    " of the field " + pAlter->field()->name()->value());
                table() << TableAligner::row()
                        << Function(sttc, *CreateDecoratedType(impl->cppType(pAlter->field()->type())),
                                    frm->alterMethodName(pAlter->field()))
                        << ";";
            }
            break;
        }

        default:
            assert(false);
    }
}

void CppHeaderGenerator::generateImmutableBaseStructureBuilderDeclaration(const StructureSPtr& pCurrStructure,
                                                                          const StructureSPtr& pStructure,
                                                                          bool overriden)
{
    if (!pStructure) return;

    generateImmutableBaseStructureBuilderDeclaration(pCurrStructure, pStructure->baseStructure().lock(), overriden);

    const std::vector<ObjectSPtr>& objects = pStructure->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        const ObjectSPtr& pObject = *it;
        switch (pObject->runtimeObjectId().value())
        {
            case EObjectId::kField:
            {
                FieldSPtr pField = boost::static_pointer_cast<Field>(pObject);
                if (pCurrStructure->isOverriden(pField) != overriden) continue;

                generateStructureFieldMethodsDeclaration(pCurrStructure, pField,
                    (overriden ? BUILDER_WRITING_SPECIFIC_RESULT_ONLY_OVERRIDDEN
                               : BUILDER_WRITING_SPECIFIC_RESULT_ONLY));
                break;
            }
            case EObjectId::kIdentification:
            case EObjectId::kOperator:
            case EObjectId::kEnumeration:
                break;
            default:
                assert(false);
        }
    }
}

void CppHeaderGenerator::generateStructureDeclaration(const StructureSPtr& pStructure)
{
    StructureSPtr pBaseStructure = pStructure->baseStructure().lock();
    addDependency(impl->cppHeaderFileDependency(pBaseStructure));

    generateForwardClassDeclarations(pStructure);

    if (pStructure->partial())
    {
        commentInLine(declarationStream,
            "This is a partial class (similar to partial classes in C#). Makes sense "
            "only in the context of its derived class. Since in C++ there are no partial "
            "classes, the pattern is implemented with inheritance - " + frm->cppAutoClassType(pStructure).value() +
            " being the base class and " + frm->cppMainClassType(pStructure).value() + " being its derived class.");
        eol(declarationStream);
        commentInLine(declarationStream,
            frm->cppAutoClassType(pStructure).value() + " provides the operational functionality for getting and "
            "setting the data. Refer to the derived " + frm->cppMainClassType(pStructure).value() + " class for "
            "more details about business related functionality.");
        eol(declarationStream);
    }

    if (pStructure->immutable())
    {
        commentInLine(declarationStream,
            frm->cppAutoClassType(pStructure).value() + " is an immutable class - once instantiated none "
            "of the data fields can be changed. For the initial initialization and instantiation "
            "use the nested Builder class.");
        eol(declarationStream);
        commentInLine(declarationStream,
            "Immutability is useful in multi-thread and subject observer applications. "
            "It makes easy creation of models with object references.");
        eol(declarationStream);
    }

    line()  << "class "
            << frm->cppAutoClassType(pStructure);
    if (pBaseStructure)
    {
        line()  << " : public "
                << frm->cppMainClassType(pBaseStructure);
    }
    else
    {
        if (pStructure->sharable())
        if (impl->mpConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers)
        {
            addDependency(Dependency("boost/enable_shared_from_this.hpp",
                                     Dependency::system_type,
                                     Dependency::boost_level,
                                     Dependency::private_section,
                                     "Boost C++ Smart Pointers"));
            line()  << " : public "
                    << impl->boost_enable_shared_from_this(frm->cppAutoClassType(pStructure));
        }
    }

    openBlock(declarationStream);

    mEncapsulation.clear();

    const std::vector<ObjectSPtr>& objects = pStructure->objects();
    if (pStructure->isBuildable())
    {
        encapsulateInLine(declarationStream, "public");

        bool bLine = false;
        std::vector<ObjectSPtr>::const_iterator it;
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            if ((*it)->runtimeObjectId() == EObjectId::enumeration())
            {
                bLine = true;
                EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(*it);
                line()  << "class "
                        << frm->cppInnerEnumType(pEnumeration, pStructure)
                        << ";";
                eol(declarationStream);
            }
        }
        if (bLine)
            eol(declarationStream);

        commentInLine(declarationStream, "Use Builder to instantiate objects");

        line() << "class Builder";
        if (pBaseStructure)
            line()  << " : public "
                    << frm->cppAutoClassNamespace(pBaseStructure)
                    << "::Builder";
        openBlock(declarationStream);

        commentInTable(
            "hide evil auto created assignment operator, no implementation");
        table() << TableAligner::row()
                << Function(vd, fnOperatorE,
                            Argument(*CreateDecoratedType(cst, builder, ref)))
                << ";";

        if (pStructure->abstract())
        {
            commentInTable(
                "hide default constructor for abstract object, no implementation");

            table() << TableAligner::row()
                    << Constructor(builder)
                    << ";";
        }

        generateImmutableBaseStructureBuilderDeclaration(pStructure, pBaseStructure, true);


        table() << TableAligner::row_line(-1)
                << "public:";

        if (!pStructure->abstract())
        {
            commentInTable(
                "Default constructor. All fields without default values are left uninitialized. "
                "Make sure you initialize all the necessary fields before instantiating");

            table() << TableAligner::row()
                    << Constructor(builder)
                    << ";";

            commentInTable(
                "Use this constructor when you need to clone or create "
                "an object just slightly different from another object");

            table() << TableAligner::row()
                    << Constructor(builder,
                                   Argument(impl->cppDecoratedType(pStructure),
                                            frm->variableName("object")))
                    << ";";

            std::vector<ObjectSPtr>::const_iterator it;
            for (it = objects.begin(); it != objects.end(); ++it)
            {
                UpcopySPtr pUpcopy = ObjectFactory::downcastUpcopy(*it);
                if (!pUpcopy) continue;

                commentInTable(
                    "Use this constructor when you need to upcopy an object from " +
                     pUpcopy->baseStructure()->name()->value() + " type.");
                commentInTable(
                    "Note: Obviously upcopy constructor initializes only the inherited "
                    "fields from the base structure. All fields that are declared down "
                    "will have their default value or will be uninitialized.");

                table() << TableAligner::row()
                        << Constructor(builder,
                                       Argument(impl->cppDecoratedType(pUpcopy->baseStructure()),
                                                frm->variableName("object")))
                        << ";";
            }
        }

        commentInTable("Destructor of Builder");

        table() << TableAligner::row()
                << Destructor(non_vrtl, builder)
                << ";";

        table() << TableAligner::row();

        commentInTable(
            "Instantiates " + frm->cppMainClassType(pStructure).value() + " instance with the current "
            "initialization of the fields. "
            "After the instance is ready the builder could be reused to instantiate "
            "more objects. The data is not reset. Second call of " + fnBuild.value() + "() will instantiate "
            "object with the same data.");

        table() << TableAligner::row()
                << Function(impl->cppDecoratedType(pStructure), fnBuild, cst)
                << ";";

        table() << TableAligner::row();

        commentInTable(
            "Provides the internal instantiated builder object and invalidates "
            "the builder status. Once " + fnFinalize.value() + "() is called, the builder can not be used again. "
            "Use " + fnFinalize.value() + "() when you no longer are going to use this builder.");

        table() << TableAligner::row()
                << Function(*CreateDecoratedType(impl->cppPtrType(pStructure)), fnFinalize)
                << ";";

        table() << TableAligner::row();
        generateImmutableBaseStructureBuilderDeclaration(pStructure, pBaseStructure, false);

        for (it = objects.begin(); it != objects.end(); ++it)
        {
            generateStructureObjectMethodsDeclaration(*it, BUILDER_WRITING);
        }

        table() << TableAligner::row()
                << TableAligner::row_line(-1)
                << "protected:";

        commentInTable(
            "constructor needed from potential derived classes");

        table() << TableAligner::row()
                << Constructor(builder,
                               Argument(frm->cppRawPtrDecoratedType(pStructure), frm->variablePtrName("object")))
                << ";";
        eot(declarationStream);

        if (!pBaseStructure)
        {
            table() << TableAligner::row();
            table() << TableAligner::row()
                    << frm->cppRawPtrName(pStructure)
                    << ' '
                    << frm->memberPtrName("object")
                    << ";";
            eot(declarationStream);
        }

        closeBlock(declarationStream, "};");
        eol(declarationStream);
    }

    if (pStructure->partial())
        encapsulateInLine(declarationStream, "protected");
    else
        encapsulateInLine(declarationStream, "public");

    commentInTable("Default constructor");

    table() << TableAligner::row()
            << Constructor(frm->cppAutoClassType(pStructure))
            << ";";

    commentInTable("Destructor");

    Modifier modifier = impl->virtualModifier(pStructure, non_vrtl);
    table() << TableAligner::row()
            << Destructor(modifier, frm->cppAutoClassType(pStructure))
            << ";";

    if (impl->mpConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers)
    {
        StructureSPtr pRecursivelyBaseStructure = pStructure->recursivelyBaseStructure();
        if (pStructure != pRecursivelyBaseStructure)
        {
            encapsulateInTable("public");
            table() << TableAligner::row();

            commentInTable(
                "Downcast method is syntactic sugar for boost::static_pointer_cast.");

            commentInTable(
                "Note that it does not provide any type checks. Use it on your own risk.");

            table() << TableAligner::row()
                    << Function(sttc, *CreateDecoratedType(frm->cppSharedPtrName(pStructure)),
                                fnDowncast,
                                Argument(frm->cppSharedPtrDecoratedType(pRecursivelyBaseStructure),
                                         frm->variablePtrName("object")))
                    << ";";
        }

        if (pStructure->sharable())
        if (pStructure != pRecursivelyBaseStructure || pStructure->partial())
        {
            encapsulateInTable("public");
            commentInTable(
                "shared_from_this is a helper method that overrides the shared_from_this method that "
                "is implemented in "
                "boost::enable_shared_from_this base class. The only purpose of this helper method is to "
                "eliminate the need of downcasting to shared_ptr to this class.");
            table() << TableAligner::row()
                    << Function(*CreateDecoratedType(frm->cppSharedPtrName(pStructure)),
                                fnSharedFromThis)
                    << ";";

            commentInTable(
                "This method is exactly the same as the previous one with exception that it allows "
                "shared_from_this to be called from const methods.");
            table() << TableAligner::row()
                    << Function(*CreateDecoratedType(frm->cppSharedConstPtrName(pStructure)),
                                fnSharedFromThis, cst)
                    << ";";
        }
    }

    Modifier method_modifier = impl->virtualModifier(pStructure);
    if (pStructure->isInitializable())
    {
        encapsulateInTable("public");
        table() << TableAligner::row();

        commentInTable("Returns true if every required field is initialized.");

        if (pStructure->immutable())
        {
            commentInTable(
                "Note: If the class is used properly it should always return true, because "
                "the object could be instantiated only if it is already initialized and can "
                "not be changed. Called by the Builder class.");
        }

        table() << TableAligner::row()
                << Function(method_modifier, bl, fnIsInitialized, cst)
                << ";";
    }

    if (pStructure->isOptional())
    {
        encapsulateInTable("public");

        table() << TableAligner::row()
                << TableAligner::row()
                << Function(method_modifier, bl, fnIsVoid, cst)
                << ";";
    }

    encapsulateInTable("public");
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        generateStructureObjectMethodsDeclaration(*it, pStructure->immutable() ?
                                                       READING : READING_WRITING);
    }
    eot(declarationStream);

    if (pStructure->hasField())
    {
        eol(declarationStream);

        if (pStructure->controlled())
        {
            encapsulateInTable("private");
            for (it = objects.begin(); it != objects.end(); ++it)
            {
                FieldSPtr pField = ObjectFactory::downcastField(*it);
                if (!pField) continue;

                commentInTable("Returns unique bitmask value for the field " + pField->name()->value());

                table() << TableAligner::row()
                        << Function(sttc, *CreateDecoratedType(*CreateSimpleType("int")),
                                                               frm->bitmaskMethodName(pField))
                        << ";";
            }

            eot(declarationStream);
            eol(declarationStream);

            commentInTable("Stores availability information for the fields");

            table() << TableAligner::row()
                    <<  "int "
                    << TableAligner::col()
                    << frm->memberName("bits")
                    << ";";
            table() << TableAligner::row();
        }

        encapsulateInTable("private");
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            generateStructureObjectMemberDeclaration(*it);
        }
        eot(declarationStream);
    }

    closeBlock(declarationStream, "};");
    eol(declarationStream);
}

void CppHeaderGenerator::generateObjectDeclaration(const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kImport:
        {
            ImportSPtr pImport = boost::static_pointer_cast<Import>(pObject);
            generateImport(pImport);
            break;
        }
        case EObjectId::kEnumeration:
        {
            EnumerationSPtr pEnumeration = boost::static_pointer_cast<Enumeration>(pObject);
            generateEnumerationDeclaration(pEnumeration);
            break;
        }
        case EObjectId::kSpecimen:
        {
            SpecimenSPtr pSpecimen = boost::static_pointer_cast<Specimen>(pObject);
            generateSpecimenDeclaration(pSpecimen);
            break;
        }
        case EObjectId::kFactory:
        {
            FactorySPtr pFactory = boost::static_pointer_cast<Factory>(pObject);
            generateFactoryDeclaration(pFactory);
            break;
        }
        case EObjectId::kIdentifier:
        {
            IdentifierSPtr pIdentifier = boost::static_pointer_cast<Identifier>(pObject);
            generateIdentifierDeclaration(pIdentifier);
            break;
        }
        case EObjectId::kStructure:
        {
            StructureSPtr pStructure = boost::static_pointer_cast<Structure>(pObject);
            generateStructureDeclaration(pStructure);
            break;
        }
        default:
            assert(false);
    }
}

bool CppHeaderGenerator::generate()
{
    if (mpModel->mainDocument()->exist_comments())
    {
        std::vector<CommentSPtr> vComments = mpModel->mainDocument()->comments();
        std::vector<CommentSPtr>::iterator cit;
        for (cit = vComments.begin(); cit != vComments.end(); ++cit)
        {
            commentInLine(copyrightStream, *cit);
            eol(copyrightStream);
        }
    }

    std::string guard = frm->headerGuard(mpModel->mainDocument(), mType);
    line()  << "#else // "
            << guard;
    eol(forwardDeclarationStream);
    eol(forwardDeclarationStream);

    openNamespace(declarationStream);
    openNamespace(forwardDeclarationStream);

    commentInLine(forwardDeclarationStream, "Forward declarations");

    if (mType == "partial")
        addDependency(Dependency(mpModel->name()->value() +
                                 "-partial" +
                                 impl->applicationHeaderExtension(), Dependency::quote_type));
    else
        addDependency(Dependency(mpModel->name()->value() +
                                 impl->applicationHeaderExtension(), Dependency::quote_type));

    const std::vector<ObjectSPtr>& objects = mpModel->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
		if ((*it)->sourceId() != mpModel->mainDocument()->sourceId())
			continue;

        generateObjectDeclaration(*it);
    }

    closeNamespace(inlineDefinitionStream);
    closeNamespace(forwardDeclarationStream);


    includeHeaders(includeStream, Dependency::global_section);

    line()  << "#ifndef "
            << guard;
    eol(includeStream);
    line()  << "#define "
            << guard;
    eol(includeStream);
    eol(includeStream);

    includeHeaders(includeStream, Dependency::private_section);

    line()  << "#endif // "
            << guard;
    eol(forwardDeclarationStream);
    eol(forwardDeclarationStream);

	return serializeStreams();
}

}

