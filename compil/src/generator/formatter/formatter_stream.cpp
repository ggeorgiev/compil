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

#include "formatter_stream.h"

#include "c++/expression/expression_factory.h"
#include "c++/statement/statement_factory.h"

#include "all/list.h"
#include "all/scope.h"

using namespace lang::all;
using namespace lang::cpp;

FormatterStream::FormatterStream(const FormatterConfigurationPtr& formatterConfiguration,
                                 const AlignerConfigurationPtr& alignerConfiguration)
    : mAligner(alignerConfiguration)
    , mConfiguration(formatterConfiguration)
{
}

FormatterStream::~FormatterStream()
{
}

std::string FormatterStream::str()
{
    return mAligner.str();
}

FormatterStream& FormatterStream::operator<<(const AdditiveShiftExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const CastPmExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const CompoundStatementSPtr& compoundStatement)
{
    Scope scope;
    scope << Scope::ESquiggles::brackets();
    
    const std::vector<StatementSPtr>& statements = compoundStatement->statements();
    for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
    {
        const StatementSPtr& statement = *it;
        
        FormatterStream formatter(mConfiguration, mAligner.mConfiguration);
        formatter << statement;
        scope << formatter.str();
    }
    
    mAligner << scope;
    return *this << compoundStatement->close();
}

FormatterStream& FormatterStream::operator<<(const ClassTypeNameSPtr& declaration)
{
    return *this << declaration->className();
}

FormatterStream& FormatterStream::operator<<(const ClassNestedNameSPtr& expression)
{
    return *this << expression->name();
}

FormatterStream& FormatterStream::operator<<(const CustomExpressionSPtr& expression)
{
    mAligner << expression->value();
    return *this;
}

FormatterStream& FormatterStream::operator<<(const CustomIdExpressionSPtr& expression)
{
    mAligner << expression->value();
    return *this;
}

FormatterStream& FormatterStream::operator<<(const DeclarationSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == ClassTypeName::staticDeclarationId())
        return *this << ClassTypeName::downcast(declaration);
    if (declaration->runtimeDeclarationId() == DeclarationSpecifierSequence::staticDeclarationId())
        return *this << DeclarationSpecifierSequence::downcast(declaration);
    if (declaration->runtimeDeclarationId() == SimpleBlockDeclaration::staticDeclarationId())
        return *this << SimpleBlockDeclaration::downcast(declaration);
    if (declaration->runtimeDeclarationId() == SimpleDeclaration::staticDeclarationId())
        return *this << SimpleDeclaration::downcast(declaration);
    if (declaration->runtimeDeclarationId() == TypeNameSimpleTypeSpecifier::staticDeclarationId())
        return *this << TypeNameSimpleTypeSpecifier::downcast(declaration);        
    if (declaration->runtimeDeclarationId() == TypeDeclarationSpecifier::staticDeclarationId())
        return *this << TypeDeclarationSpecifier::downcast(declaration);

    return *this;
}

FormatterStream& FormatterStream::operator<<(const DeclarationSpecifierSequenceSPtr& declaration)
{
    const std::vector<DeclarationSpecifierSPtr>& declarations = declaration->declarations();
    BOOST_ASSERT(declarations.size() >= 1);

    for (std::vector<DeclarationSpecifierSPtr>::const_iterator it = declarations.begin(); it != declarations.end(); ++it)
    {
        if (it != declarations.begin())
            mAligner << " ";
        *this << *it;
    }
    return *this;
}

FormatterStream& FormatterStream::operator<<(const DeclaratorSPtr& declarator)
{
    if (declarator->runtimeDeclaratorId() == InitDeclarator::staticDeclaratorId())
        return *this << InitDeclarator::downcast(declarator);
    if (declarator->runtimeDeclaratorId() == DeclaratorId::staticDeclaratorId())
        return *this << DeclaratorId::downcast(declarator);
    if (declarator->runtimeDeclaratorId() == DeclaratorIdDirectDeclarator::staticDeclaratorId())
        return *this << DeclaratorIdDirectDeclarator::downcast(declarator);

    return *this;
}

FormatterStream& FormatterStream::operator<<(const DeclarationStatementSPtr& statement)
{
    return *this << statement->declaration()
                 << statement->close();
}

FormatterStream& FormatterStream::operator<<(const DeclaratorIdSPtr& declarator)
{
    return *this << declarator->typeName();
}

FormatterStream& FormatterStream::operator<<(const DeclaratorIdDirectDeclaratorSPtr& declarator)
{
    return *this << declarator->declarator();
}

FormatterStream& FormatterStream::operator<<(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == AdditiveShiftExpression::staticExpressionId())
        return *this << AdditiveShiftExpression::downcast(expression);
    if (expression->runtimeExpressionId() == CastPmExpression::staticExpressionId())
        return *this << CastPmExpression::downcast(expression);
    if (expression->runtimeExpressionId() == ClassNestedName::staticExpressionId())
        return *this << ClassNestedName::downcast(expression);
    if (expression->runtimeExpressionId() == CustomExpression::staticExpressionId())
        return *this << CustomExpression::downcast(expression);
    if (expression->runtimeExpressionId() == CustomIdExpression::staticExpressionId())
        return *this << CustomIdExpression::downcast(expression);
    if (expression->runtimeExpressionId() == ExpressionList::staticExpressionId())
        return *this << ExpressionList::downcast(expression);
    if (expression->runtimeExpressionId() == IdentifierUnqualifiedId::staticExpressionId())
        return *this << IdentifierUnqualifiedId::downcast(expression);
    if (expression->runtimeExpressionId() == IdExpressionPrimaryExpression::staticExpressionId())
        return *this << IdExpressionPrimaryExpression::downcast(expression);
    if (expression->runtimeExpressionId() == GrammarEqualityExpression::staticExpressionId())
        return *this << GrammarEqualityExpression::downcast(expression);        
    if (expression->runtimeExpressionId() == MemberAccessPostfixExpression::staticExpressionId())
        return *this << MemberAccessPostfixExpression::downcast(expression);
    if (expression->runtimeExpressionId() == MultiplicativeAdditiveExpression::staticExpressionId())
        return *this << MultiplicativeAdditiveExpression::downcast(expression);
    if (expression->runtimeExpressionId() == NamespaceNestedName::staticExpressionId())
        return *this << NamespaceNestedName::downcast(expression);
    if (expression->runtimeExpressionId() == NestedNameSpecifier::staticExpressionId())
        return *this << NestedNameSpecifier::downcast(expression);
    if (expression->runtimeExpressionId() == ParenthesesPostfixExpression::staticExpressionId())
        return *this << ParenthesesPostfixExpression::downcast(expression);
    if (expression->runtimeExpressionId() == PmMultiplicativeExpression::staticExpressionId())
        return *this << PmMultiplicativeExpression::downcast(expression);
    if (expression->runtimeExpressionId() == PostfixUnaryExpression::staticExpressionId())
        return *this << PostfixUnaryExpression::downcast(expression);
    if (expression->runtimeExpressionId() == PrimaryExpressionPostfixExpression::staticExpressionId())
        return *this << PrimaryExpressionPostfixExpression::downcast(expression);
    if (expression->runtimeExpressionId() == RelationalEqualityExpression::staticExpressionId())
        return *this << RelationalEqualityExpression::downcast(expression);
    if (expression->runtimeExpressionId() == ShiftRelationalExpression::staticExpressionId())
        return *this << ShiftRelationalExpression::downcast(expression);
    if (expression->runtimeExpressionId() == UnaryCastExpression::staticExpressionId())
        return *this << UnaryCastExpression::downcast(expression);
    if (expression->runtimeExpressionId() == UnqualifiedIdExpression::staticExpressionId())
        return *this << UnqualifiedIdExpression::downcast(expression);
        
    return *this;
}

FormatterStream& FormatterStream::operator<<(const ExpressionListSPtr& expressionList)
{
    List list;
    list << List::ESquiggles::none();
    list << List::EDelimiter::comma();
    
    const std::vector<ExpressionSPtr>& expressions = expressionList->expressions();
    for (std::vector<ExpressionSPtr>::const_iterator it = expressions.begin(); it != expressions.end(); ++it)
    {
        const ExpressionSPtr& expression = *it;
        FormatterStream formatter(mConfiguration, mAligner.mConfiguration);
        formatter << expression;
        list << formatter.str();
    }
    
    mAligner << list;
    return *this;
}

FormatterStream& FormatterStream::operator<<(const ExpressionStatementSPtr& statement)
{
    *this << statement->expression();
    mAligner << ";";
    return *this;
}

FormatterStream& FormatterStream::operator<<(const IdentifierUnqualifiedIdSPtr& expression)
{
    mAligner << expression->identifier()->value();
    return *this;
}

FormatterStream& FormatterStream::operator<<(const IdentifierSPtr& identifier)
{
     mAligner << identifier->value();
     return *this;
}

FormatterStream& FormatterStream::operator<<(const IdentifierClassNameSPtr& name)
{
    return *this << name->identifier();
}

FormatterStream& FormatterStream::operator<<(const IdentifierNamespaceNameSPtr& name)
{
    return *this << name->identifier();
}

FormatterStream& FormatterStream::operator<<(const IdExpressionPrimaryExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const InitDeclaratorSPtr& declarator)
{
    return *this << declarator->declarator();
}

FormatterStream& FormatterStream::operator<<(const GrammarEqualityExpressionSPtr& expression)
{
    *this << expression->first();
    switch (expression->type().value())
    {
        case EqualityExpression::EType::kEqualTo:
            mAligner << " == ";
            break;
        case EqualityExpression::EType::kNotEqualTo:
            mAligner << " != ";
            break;
        default:
            BOOST_ASSERT(false);
    }
    return *this << expression->second();
}

FormatterStream& FormatterStream::operator<<(const MacroStatementSPtr& macro)
{
    mAligner << macro->name()->value();
    
    List list;
    list << List::ESquiggles::parentheses();
    list << List::EDelimiter::comma();
    
    const std::vector<MacroParameterSPtr>& parameters = macro->parameters();
    for (std::vector<MacroParameterSPtr>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
    {
        const MacroParameterSPtr& parameter = *it;
        FormatterStream formatter(mConfiguration, mAligner.mConfiguration);
        if (parameter->runtimeMacroParameterId() == ExpressionMacroParameter::staticMacroParameterId())
            formatter << ExpressionMacroParameter::downcast(parameter)->expression();
        if (parameter->runtimeMacroParameterId() == DeclarationMacroParameter::staticMacroParameterId())
            formatter << DeclarationMacroParameter::downcast(parameter)->declaration();

        list << formatter.str();
    }
    
    mAligner << list;
    return *this << macro->close();
}

FormatterStream& FormatterStream::operator<<(const MemberAccessPostfixExpressionSPtr& expression)
{
    *this << expression->first();
    mAligner << ".";
    *this << expression->second();
    return *this;
}

FormatterStream& FormatterStream::operator<<(const MultiplicativeAdditiveExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const NamespaceNestedNameSPtr& expression)
{
    return *this << expression->name();
}

FormatterStream& FormatterStream::operator<<(const NestedNameSpecifierSPtr& expression)
{
    *this << expression->name();
    mAligner << "::";
    return *this;
}

FormatterStream& FormatterStream::operator<<(const ParenthesesPostfixExpressionSPtr& expression)
{
    *this << expression->expression();
    mAligner << "(";
    if (expression->list())
        *this << expression->list();
    mAligner << ")";
    return *this;
}

FormatterStream& FormatterStream::operator<<(const PmMultiplicativeExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const PostfixUnaryExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const PrimaryExpressionPostfixExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const RelationalEqualityExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const ShiftRelationalExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const SimpleBlockDeclarationSPtr& declaration)
{
    return *this << declaration->declaration();
}

FormatterStream& FormatterStream::operator<<(const SimpleDeclarationSPtr& declaration)
{
    BOOST_ASSERT(declaration->declaration() || declaration->declarator());
    if (declaration->declaration())
    {
        *this << declaration->declaration();
        mAligner << " ";
    }
    if (declaration->declarator())
        *this << declaration->declarator();
    return *this;
}

FormatterStream& FormatterStream::operator<<(const StatementSPtr& statement)
{
    if (statement->runtimeStatementId() == CompoundStatement::staticStatementId())
        return *this << CompoundStatement::downcast(statement);
    if (statement->runtimeStatementId() == ExpressionStatement::staticStatementId())
        return *this << ExpressionStatement::downcast(statement);
    if (statement->runtimeStatementId() == DeclarationStatement::staticStatementId())
        return *this << DeclarationStatement::downcast(statement);
    if (statement->runtimeStatementId() == MacroStatement::staticStatementId())
        return *this << MacroStatement::downcast(statement);
         
    return *this;
}

FormatterStream& FormatterStream::operator<<(const Statement::EClose& close)
{
    if (close == Statement::EClose::yes())
        mAligner << ";";
    return *this;
}

FormatterStream& FormatterStream::operator<<(const TypeDeclarationSpecifierSPtr& declaration)
{
    return *this << declaration->declaration();
}

FormatterStream& FormatterStream::operator<<(const TypeNameSimpleTypeSpecifierSPtr& declaration)
{
    if (declaration->specifier())
        *this << declaration->specifier();
    return *this << declaration->typeName();
}

FormatterStream& FormatterStream::operator<<(const UnaryCastExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const UnqualifiedIdExpressionSPtr& expression)
{
    return *this << expression->unqualifiedId();
}

