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

#include "generator/c++/implementer_stream.h"
#include "library/c++/compil/declarator.h"
#include "library/c++/compil/method.h"
#include "library/c++/stl/string.h"
#include "language/c++/class/member_variable.h"

using namespace lang;
using namespace lang::cpp;
using namespace lang::all;
using namespace lib::cpp;

ImplementerStream::ImplementerStream(const ImplementerConfigurationSPtr& implementerConfiguration,
                                     const NamerConfigurationSPtr& namerConfiguration,
                                     const FormatterConfigurationSPtr& formatterConfiguration,
                                     const AlignerConfigurationSPtr& alignerConfiguration)
    : mNamer(namerConfiguration, formatterConfiguration, alignerConfiguration)
    , mConfiguration(implementerConfiguration)
{
}

ImplementerStream::~ImplementerStream()
{
}

std::string ImplementerStream::str()
{
    return mNamer.str();
}

static StatementSPtr convertStatement(const StatementSPtr& statement)
{
    if (statement->runtimeStatementId() == ThrowTestStatement::staticStatementId())
    {
        ThrowTestStatementSPtr teststatement = ThrowTestStatement::downcast(statement);
        MacroStatementSPtr macro = macroStatementRef()
            << (macroNameRef() << "ASSERT_THROW");

        macro << (expressionMacroArgumentRef() << teststatement->expression());
        macro << (declarationMacroArgumentRef() << (classDeclarationSpecifierRef() << teststatement->class_()));
        return macro;
    }

    if (statement->runtimeStatementId() == UnaryTestStatement::staticStatementId())
    {
        UnaryTestStatementSPtr teststatement = UnaryTestStatement::downcast(statement);
        MacroStatementSPtr macro = macroStatementRef();
        switch (teststatement->type().value())
        {
            case UnaryTestStatement::EType::kIsTrue:
                macro << (macroNameRef() << "ASSERT_TRUE");
                break;
            case UnaryTestStatement::EType::kIsFalse:
                macro << (macroNameRef() << "ASSERT_FALSE");
                break;
            default:
                assert(false);
        }
        
        macro << (expressionMacroArgumentRef() << teststatement->expression());
        return macro;
    }
    
    return statement;
}

ImplementerStream& ImplementerStream::operator<<(const TestSuite& suite)
{
    const std::vector<lang::cpp::TestSPtr>& tests = suite.tests();
    
    for (std::vector<TestSPtr>::const_iterator it = tests.begin(); it != tests.end(); ++it)
    {
        const TestSPtr& test = *it;

        MacroStatementSPtr macro = macroStatementRef();
        macro << (macroNameRef() << "TEST");
        
        macro << (expressionMacroArgumentRef() << (customExpressionRef() << suite.name().value()));
        macro << (expressionMacroArgumentRef() << (customExpressionRef() << test->name().value()));
        macro << Statement::EClose::no();
        
        CompoundStatementSPtr compoundStatement = compoundStatementRef();
        
        const std::vector<StatementSPtr>& statements = test->statements();
        for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
            compoundStatement << convertStatement(*it);
        
        mNamer << macro
               << compoundStatement
               << lineDelimiterRef();
    }

    return *this;
}

BodyFunctionDefinitionSPtr ImplementerStream::methodBodyDefinition(const DeclarationSpecifierSequenceSPtr& specifier,
                                                                   const MethodNameSPtr& methodName,
                                                                   const ParameterDeclarationClauseSPtr& parameters,
                                                                   const CVQualifierSequenceSPtr& qualifier)
{
    FunctionNameDeclaratorIdSPtr functionNameDeclaratorId = functionNameDeclaratorIdRef()
        << methodName;
        
    DeclaratorIdDirectDeclaratorSPtr declaratorIdDirectDeclarator = declaratorIdDirectDeclaratorRef()
        << functionNameDeclaratorId;
        
    ParametersDirectDeclaratorSPtr parametersDirectDeclarator = parametersDirectDeclaratorRef()
        << declaratorIdDirectDeclarator;
        
    if (parameters)
    {
        ParameterDeclarationListSPtr list = parameterDeclarationListRef();
        const std::vector<ParameterDeclarationSPtr>& declarators = parameters->list()->declarators();
        for (std::vector<ParameterDeclarationSPtr>::const_iterator it = declarators.begin(); it != declarators.end(); ++it)
        {
            const ParameterDeclarationSPtr& declarator = *it;
            if (declarator->runtimeDeclaratorId() != DeclaratorParameterDeclaration::staticDeclaratorId())
            {
                list << declarator;
                continue;
            }
            
            DeclaratorParameterDeclarationSPtr dpd = DeclaratorParameterDeclaration::downcast(declarator);
            if (dpd->declaration()->declarations().size() > 1)
            {
                list << declarator;
                continue;
            }

            list << (declaratorParameterDeclarationRef()
                    << (declarationSpecifierSequenceRef()
                        << convert(dpd->declaration()->declarations()[0]))
                    << dpd->declarator());
        }
        
        parametersDirectDeclarator
            << (parameterDeclarationClauseRef()
                << list);
    }

    if (qualifier)
        parametersDirectDeclarator << qualifier;

    BodyFunctionDefinitionSPtr bodyFunctionDefinition = bodyFunctionDefinitionRef()
        << parametersDirectDeclarator;
        
    if (specifier)
        bodyFunctionDefinition << specifier;

    return bodyFunctionDefinition;
}

FunctionDefinitionMemberDeclarationSPtr ImplementerStream::methodDefinition(const DeclarationSpecifierSequenceSPtr& specifier,
                                                                            const MethodNameSPtr& methodName,
                                                                            const ParameterDeclarationClauseSPtr& parameters,
                                                                            const CVQualifierSequenceSPtr& qualifier)
{

    FunctionDefinitionMemberDeclarationSPtr functionDefinitionMemberDeclaration = functionDefinitionMemberDeclarationRef()
        << methodBodyDefinition(specifier, methodName, parameters, qualifier);
    
    return functionDefinitionMemberDeclaration;
}

void ImplementerStream::convert(const lang::cpp::MemberSpecificationSectionSPtr& section, const std::vector<ConstructorSPtr>& constructors)
{
    for (std::vector<ConstructorSPtr>::const_iterator it = constructors.begin(); it != constructors.end(); ++it)
    {
        const ConstructorSPtr& constructor = *it;
        if (constructor->accessSpecifier() != section->accessSpecifier())
            continue;
            
        ConstructorMethodNameSPtr constructorMethodName = constructorMethodNameRef()
            << constructor->class_().lock()->name();
            
        FunctionDefinitionMemberDeclarationSPtr method = methodDefinition(CppMethod::specifier(constructor->specifier()),
                                                                          constructorMethodName,
                                                                          constructor->parameters(),
                                                                          CVQualifierSequenceSPtr());
        section << method;
    }
}

void ImplementerStream::convert(const lang::cpp::MemberSpecificationSectionSPtr& section, const DestructorSPtr& destructor)
{
    if (!destructor)
        return;

    if (destructor->accessSpecifier() != section->accessSpecifier())
        return;
        
    DestructorMethodNameSPtr destructorMethodName = destructorMethodNameRef()
        << destructor->class_().lock()->name();
    
    section << methodDefinition(DeclarationSpecifierSequenceSPtr(),
                                destructorMethodName,
                                ParameterDeclarationClauseSPtr(),
                                CVQualifierSequenceSPtr());
}


void ImplementerStream::convert(const lang::cpp::MemberSpecificationSectionSPtr& section, const std::vector<MethodSPtr>& methods)
{
    for (std::vector<MethodSPtr>::const_iterator it = methods.begin(); it != methods.end(); ++it)
    {
        const MethodSPtr& method = *it;
        if (method->accessSpecifier() != section->accessSpecifier())
            continue;
        
        DeclarationSpecifierSequenceSPtr specifier = CppMethod::specifier(method->methodSpecifier(),
                                                                          convert(method->returnType()));

        FunctionDefinitionMemberDeclarationSPtr methodDef = methodDefinition(specifier,
                                                                             method->name(),
                                                                             method->parameters(),
                                                                             method->qualifier());
        section << methodDef;
    }
}

void ImplementerStream::convert(const lang::cpp::MemberSpecificationSectionSPtr& section,
                                const std::vector<MemberVariableSPtr>& members)
{
    for (std::vector<MemberVariableSPtr>::const_iterator it = members.begin(); it != members.end(); ++it)
    {
        const MemberVariableSPtr& member = *it;
        if (member->accessSpecifier() != section->accessSpecifier())
            continue;
        
        DeclarationSpecifierSequenceSPtr specifier = declarationSpecifierSequenceRef()
            << convert(member->type());
        
        section << (specifierMemberDeclarationRef()
                    << specifier
                    << (declaratorMemberDeclaratorRef()
                        << (variableNameDeclaratorRef()
                            << member->name())));
    }
}

ImplementerStream& ImplementerStream::operator<<(const ClassSPtr& class_)
{
    MemberSpecificationSectionSPtr publicSection = memberSpecificationSectionRef()
        << EAccessSpecifier::public_();

    convert(publicSection, class_->constructors());
    convert(publicSection, class_->destructor());
    convert(publicSection, class_->methods());
    convert(publicSection, class_->members());
    
    MemberSpecificationSectionSPtr protectedSection = memberSpecificationSectionRef()
        << EAccessSpecifier::protected_();

    convert(protectedSection, class_->constructors());
    convert(protectedSection, class_->destructor());
    convert(protectedSection, class_->methods());
    convert(protectedSection, class_->members());

    MemberSpecificationSectionSPtr privateSection = memberSpecificationSectionRef()
        << EAccessSpecifier::private_();

    convert(privateSection, class_->constructors());
    convert(privateSection, class_->destructor());
    convert(privateSection, class_->methods());
    convert(privateSection, class_->members());

    MemberSpecificationSPtr specification = memberSpecificationRef();
    if (publicSection->declarations().size() > 0)
        specification << publicSection;
    if (protectedSection->declarations().size() > 0)
        specification << protectedSection;
    if (privateSection->declarations().size() > 0)
        specification << privateSection;

    ClassSpecifierSPtr specifier = classSpecifierRef()
        << (classHeadRef() << class_->classKey()
                           << class_->name())
        << specification;

    mNamer << specifier;
    
    const std::vector<MethodSPtr>& methods = class_->methods();
    for (std::vector<MethodSPtr>::const_iterator it = methods.begin(); it != methods.end(); ++it)
    {
        const MethodSPtr& method = *it;
        if (!method->methodSpecifier().isSet(EMethodSpecifier::inline_()))
            continue;
            
        DeclarationSpecifierSequenceSPtr sequence = convert(CppMethod::specifier(method->methodSpecifier(), method->returnType()));
            
        BodyFunctionDefinitionSPtr bodyFunctionDefinition = methodBodyDefinition(sequence,
                                                                                 method->name(),
                                                                                 method->parameters(),
                                                                                 method->qualifier());
            
        if (method->body())
            bodyFunctionDefinition << method->body();
            
        mNamer << bodyFunctionDefinition;
    }
    
    return *this;
}

DeclarationSpecifierSequenceSPtr ImplementerStream::convert(const DeclarationSpecifierSequenceSPtr& sequence)
{
    DeclarationSpecifierSequenceSPtr newdeclaration = declarationSpecifierSequenceRef();
    
    const std::vector<DeclarationSpecifierSPtr>& declarations = sequence->declarations();
    for (std::vector<DeclarationSpecifierSPtr>::const_iterator it = declarations.begin(); it != declarations.end(); ++it)
        newdeclaration << convert(*it);

    return newdeclaration;
}

DeclarationSpecifierSPtr ImplementerStream::convert(const DeclarationSpecifierSPtr& specifier)
{
    if (!specifier)
        return specifier;
        
    if (specifier->runtimeDeclarationId() == GenericDeclarationSpecifier::staticDeclarationId())
    {
        GenericDeclarationSpecifierSPtr gds = GenericDeclarationSpecifier::downcast(specifier);
        if (gds->generic() == EGeneric::string())
            return classDeclarationSpecifierRef() << lib::cpp::StlString::class_();
    }
    
    return specifier;
}
