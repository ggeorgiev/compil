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

#include "namer_stream.h"

#include "c++/class/class_name_factory.h"
#include "c++/namespace/namespace_name_factory.h"

#include "boost/unordered_map.hpp"

using namespace lang::cpp;

NamerStream::NamerStream(const NamerConfigurationSPtr& namerConfiguration,
                const FormatterConfigurationPtr& formatterConfiguration,
                const AlignerConfigurationPtr& alignerConfiguration)
    : mFormatter(formatterConfiguration, alignerConfiguration)
    , mConfiguration(namerConfiguration)
{
}

NamerStream::~NamerStream()
{
}

std::string NamerStream::str()
{
    return mFormatter.str();
}

static IdentifierSPtr convertClassName(const ClassNameSPtr& name)
{
    if (name->runtimeClassNameId() == IdentifierClassName::staticClassNameId())
        return IdentifierClassName::downcast(name)->identifier();
        
    BOOST_ASSERT(false);
    return IdentifierSPtr();
}

static IdentifierClassNameSPtr convertIdentifierClassName(const ClassNameSPtr& name)
{
    if (name->runtimeClassNameId() == IdentifierClassName::staticClassNameId())
        return IdentifierClassName::downcast(name);
        
    BOOST_ASSERT(false);
    return IdentifierClassNameSPtr();
}

static IdentifierNamespaceNameSPtr convertIdentifierNamespaceName(const NamespaceNameSPtr& name)
{
    if (name->runtimeNamespaceNameId() == IdentifierNamespaceName::staticNamespaceNameId())
        return IdentifierNamespaceName::downcast(name);
        
    BOOST_ASSERT(false);
    return IdentifierNamespaceNameSPtr();
}


static TypeNameSimpleTypeSpecifierSPtr convertTypeNameSimpleTypeSpecifier(const ClassSPtr& class_)
{
    ClassTypeNameSPtr classTypeName1 = classTypeNameRef()
        << convertIdentifierClassName(class_->name());
        
    NestedNameSpecifierSPtr nestedNameSpecifier;
    
    for (ClassSPtr nested = class_; nested->containerClass(); nested = nested->containerClass())
    {
        ClassNestedNameSPtr classNestedName = classNestedNameRef()
            << convertIdentifierClassName(nested->containerClass()->name());
        
        NestedNameSpecifierSPtr thisNestedNameSpecifier = nestedNameSpecifierRef()
            << classNestedName;
            
        if (nestedNameSpecifier)
            thisNestedNameSpecifier << nestedNameSpecifier;
            
        nestedNameSpecifier = thisNestedNameSpecifier;
    }
    
    if (class_->namespace_())
    {
        const std::vector<NamespaceNameSPtr>& names = class_->namespace_()->names();
        for (std::vector<NamespaceNameSPtr>::const_reverse_iterator it = names.rbegin(); it != names.rend(); ++it)
        {
            NamespaceNestedNameSPtr namespaceNestedName = namespaceNestedNameRef()
                << convertIdentifierNamespaceName(*it);
        
            NestedNameSpecifierSPtr thisNestedNameSpecifier = nestedNameSpecifierRef()
                << namespaceNestedName;

            if (nestedNameSpecifier)
                thisNestedNameSpecifier << nestedNameSpecifier;

            nestedNameSpecifier = thisNestedNameSpecifier;
        }
    }
        
    TypeNameSimpleTypeSpecifierSPtr typeNameSimpleTypeSpecifier = typeNameSimpleTypeSpecifierRef()
        << nestedNameSpecifier
        << classTypeName1;
        
    return typeNameSimpleTypeSpecifier;
}

static DeclarationSPtr convertDeclaration(const DeclarationSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == ClassDeclaration::staticDeclarationId())
    {
        ClassDeclarationSPtr cdeclaration = ClassDeclaration::downcast(declaration);
        return convertTypeNameSimpleTypeSpecifier(cdeclaration->class_());
    }
    
    return declaration;
}

static ExpressionSPtr convertExpression(const ExpressionSPtr& expression);

static ExpressionSPtr doConvertExpression(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == MethodCallExpression::staticExpressionId())
    {
        MethodCallExpressionSPtr mcexpression = MethodCallExpression::downcast(expression);

        IdentifierSPtr variableIdentifier = identifierRef()
            << mcexpression->variable()->name()->value();

        IdentifierUnqualifiedIdSPtr variableUnqualifiedId = identifierUnqualifiedIdRef()
            << variableIdentifier;
        UnqualifiedIdExpressionSPtr variableUnqualifiedIdExpression = unqualifiedIdExpressionRef()
            << variableUnqualifiedId;
        IdExpressionPrimaryExpressionSPtr variablePrimaryExpression = idExpressionPrimaryExpressionRef()
            << variableUnqualifiedIdExpression;
        PrimaryExpressionPostfixExpressionSPtr variablePostfixExpression = primaryExpressionPostfixExpressionRef()
            << variablePrimaryExpression;

        IdentifierSPtr methodIdentifier = identifierRef()
            << mcexpression->method()->value();
        IdentifierUnqualifiedIdSPtr methodUnqualifiedId = identifierUnqualifiedIdRef()
            << methodIdentifier;
        UnqualifiedIdExpressionSPtr methodExpression = unqualifiedIdExpressionRef()
            << methodUnqualifiedId;
        
        MemberAccessPostfixExpressionSPtr memberAccessExpression = memberAccessPostfixExpressionRef()
            << variablePostfixExpression
            << methodExpression;
            
        ExpressionListSPtr list = expressionListRef();
        const std::vector<ExpressionSPtr>& expressions = mcexpression->expressions();
        for (std::vector<ExpressionSPtr>::const_iterator it = expressions.begin(); it != expressions.end(); ++it)
            list << convertExpression(*it);
            
        ParenthesesPostfixExpressionSPtr parenthesesExpression = parenthesesPostfixExpressionRef()
            << memberAccessExpression
            << list;
        
        return parenthesesExpression;
    }
    
    if (expression->runtimeExpressionId() == ConstructorCallExpression::staticExpressionId())
    {
        ConstructorCallExpressionSPtr ccexpression = ConstructorCallExpression::downcast(expression);
        
        IdentifierSPtr constructorIdentifier = convertClassName(ccexpression->type());
        IdentifierUnqualifiedIdSPtr constructorUnqualifiedId = identifierUnqualifiedIdRef()
            << constructorIdentifier;
        UnqualifiedIdExpressionSPtr constructorUnqualifiedIdExpression = unqualifiedIdExpressionRef()
            << constructorUnqualifiedId;
        IdExpressionPrimaryExpressionSPtr constructorPrimaryExpression = idExpressionPrimaryExpressionRef()
            << constructorUnqualifiedIdExpression;
        PrimaryExpressionPostfixExpressionSPtr constructorPostfixExpression = primaryExpressionPostfixExpressionRef()
            << constructorPrimaryExpression;
            
        ParenthesesPostfixExpressionSPtr parenthesesExpression = parenthesesPostfixExpressionRef()
            << constructorPostfixExpression;
            
        return parenthesesExpression;
    }

    return expression;
}

static ExpressionSPtr convertExpression(const ExpressionSPtr& expression)
{
    static boost::unordered_map<ExpressionSPtr, ExpressionSPtr> map;
    boost::unordered_map<ExpressionSPtr, ExpressionSPtr>::iterator it = map.find(expression);
    if (it != map.end())
        return it->second;

    ExpressionSPtr newexpression = doConvertExpression(expression);
    map[expression] = newexpression;
    return newexpression;
}

static MacroParameterSPtr convertMacroParameter(const MacroParameterSPtr& parameter)
{
    if (parameter->runtimeMacroParameterId() == ExpressionMacroParameter::staticMacroParameterId())
        return expressionMacroParameterRef() << convertExpression(ExpressionMacroParameter::downcast(parameter)->expression());
    if (parameter->runtimeMacroParameterId() == DeclarationMacroParameter::staticMacroParameterId())
        return declarationMacroParameterRef() << convertDeclaration(DeclarationMacroParameter::downcast(parameter)->declaration());

    return parameter;
}

static StatementSPtr convertStatement(const StatementSPtr& statement)
{
    if (statement->runtimeStatementId() == CompoundStatement::staticStatementId())
    {
        CompoundStatementSPtr cstatment = CompoundStatement::downcast(statement);

        CompoundStatementSPtr newstatement = compoundStatementRef();
        const std::vector<StatementSPtr>& statements = cstatment->statements();
        for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
            newstatement << convertStatement(*it);
            
        return newstatement;
    }
    
    if (statement->runtimeStatementId() == ExpressionStatement::staticStatementId())
    {
        ExpressionStatementSPtr estatement = ExpressionStatement::downcast(statement);
        ExpressionStatementSPtr newstatement = expressionStatementRef()
            << convertExpression(estatement->expression());
        return newstatement;
    }
    
    if (statement->runtimeStatementId() == MacroStatement::staticStatementId())
    {
        MacroStatementSPtr mstatement = MacroStatement::downcast(statement);
        MacroStatementSPtr newstatement = macroStatementRef()
            << mstatement->name()
            << mstatement->close();
            
        const std::vector<MacroParameterSPtr>& parameters = mstatement->parameters();
        for (std::vector<MacroParameterSPtr>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
            newstatement << convertMacroParameter(*it);
        
        return newstatement;
    }
    
    if (statement->runtimeStatementId() == VariableDeclarationStatement::staticStatementId())
    {
        VariableDeclarationStatementSPtr vdstatment = VariableDeclarationStatement::downcast(statement);
            
        TypeDeclarationSpecifierSPtr typeDeclarationSpecifier = typeDeclarationSpecifierRef()
            << convertTypeNameSimpleTypeSpecifier(vdstatment->type());
        DeclarationSpecifierSequenceSPtr declarationSpecifierSequence = declarationSpecifierSequenceRef()
            << typeDeclarationSpecifier;
            
        IdentifierClassNameSPtr identifierClassName2 = identifierClassNameRef()
            << (identifierRef() << vdstatment->variable()->name()->value());
        ClassTypeNameSPtr classTypeName2 = classTypeNameRef()
            << identifierClassName2;
        DeclaratorIdSPtr declaratorId = declaratorIdRef()
            << classTypeName2;
        DeclaratorIdDirectDeclaratorSPtr directDeclarator = declaratorIdDirectDeclaratorRef()
            << declaratorId;
        InitDeclaratorSPtr initDeclarator = initDeclaratorRef()
            << directDeclarator;
            
        SimpleDeclarationSPtr simpleDeclaration = simpleDeclarationRef()
            << initDeclarator
            << declarationSpecifierSequence;
        SimpleBlockDeclarationSPtr blockDeclaration = simpleBlockDeclarationRef()
            << simpleDeclaration;
            
        return declarationStatementRef() << blockDeclaration;
    }
    
    return statement;
}

NamerStream& NamerStream::operator<<(const StatementSPtr& statement)
{
    mFormatter << convertStatement(statement);
    return *this;
}

