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
        
        IdentifierSPtr constructorIdentifier = identifierRef()
            << ccexpression->type()->value();
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
            newstatement << (macroParameterRef() << convertExpression((*it)->expression()));
        
        return newstatement;
    }
    
    if (statement->runtimeStatementId() == VariableDeclarationStatement::staticStatementId())
    {
        VariableDeclarationStatementSPtr vdstatment = VariableDeclarationStatement::downcast(statement);
            
        IdentifierClassNameSPtr identifierClassName1 = identifierClassNameRef()
            << (identifierRef() << vdstatment->type()->name()->value());
        ClassTypeNameSPtr classTypeName1 = classTypeNameRef()
            << identifierClassName1;
            
        NestedNameSpecifierSPtr nestedNameSpecifier;
        if (vdstatment->type()->containerClass())
        {
            IdentifierClassNameSPtr identifierClassName = identifierClassNameRef()
                << (identifierRef() << vdstatment->type()->containerClass()->name()->value());
            ClassNestedNameSPtr classNestedName = classNestedNameRef()
                << identifierClassName;
            nestedNameSpecifier = nestedNameSpecifierRef()
                << classNestedName;
        }
            
        TypeNameSimpleTypeSpecifierSPtr typeNameSimpleTypeSpecifier = typeNameSimpleTypeSpecifierRef()
            << nestedNameSpecifier
            << classTypeName1;
        TypeDeclarationSpecifierSPtr typeDeclarationSpecifier = typeDeclarationSpecifierRef()
            << typeNameSimpleTypeSpecifier;
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

