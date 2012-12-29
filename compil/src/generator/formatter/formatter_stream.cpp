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

using namespace lang;
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

FormatterStream& FormatterStream::operator<<(const DeclarationStatementSPtr& statement)
{
    mAligner << statement->type()->value();
    mAligner << " ";
    mAligner << statement->identifier()->value();
    return *this << statement->close();
}

FormatterStream& FormatterStream::operator<<(const ExpressionSPtr& expression)
{
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
    if (expression->runtimeExpressionId() == MemberAccessPostfixExpression::staticExpressionId())
        return *this << MemberAccessPostfixExpression::downcast(expression);
    if (expression->runtimeExpressionId() == ParenthesesPostfixExpression::staticExpressionId())
        return *this << ParenthesesPostfixExpression::downcast(expression);
    if (expression->runtimeExpressionId() == PrimaryExpressionPostfixExpression::staticExpressionId())
        return *this << PrimaryExpressionPostfixExpression::downcast(expression);
    if (expression->runtimeExpressionId() == UnqualifiedIdExpression::staticExpressionId())
        return *this << UnqualifiedIdExpression::downcast(expression);
        
    return *this;
}

FormatterStream& FormatterStream::operator<<(const lang::cpp::ExpressionListSPtr& expressionList)
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

FormatterStream& FormatterStream::operator<<(const IdExpressionPrimaryExpressionSPtr& expression)
{
    return *this << expression->expression();
}

FormatterStream& FormatterStream::operator<<(const MacroStatementSPtr& macro)
{
    mAligner << macro->name().value();
    
    List list;
    list << List::ESquiggles::parentheses();
    list << List::EDelimiter::comma();
    
    const std::vector<MacroParameterSPtr>& parameters = macro->parameters();
    for (std::vector<MacroParameterSPtr>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
    {
        const MacroParameterSPtr& parameter = *it;
        FormatterStream formatter(mConfiguration, mAligner.mConfiguration);
        formatter << parameter->expression();
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

FormatterStream& FormatterStream::operator<<(const ParenthesesPostfixExpressionSPtr& expression)
{
    *this << expression->expression();
    mAligner << "(";
    if (expression->list())
        *this << expression->list();
    mAligner << ")";
    return *this;
}

FormatterStream& FormatterStream::operator<<(const PrimaryExpressionPostfixExpressionSPtr& expression)
{
    return *this << expression->expression();
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

FormatterStream& FormatterStream::operator<<(const UnqualifiedIdExpressionSPtr& expression)
{
    return *this << expression->unqualifiedId();
}

