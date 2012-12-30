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

#include <boost/shared_ptr.hpp>

#ifndef _FORMATTER_STREAM_H__
#define _FORMATTER_STREAM_H__

#include "formatter_configuration.h"
#include "aligner_stream.h"

#include "c++/expression/expression_factory.h"
#include "c++/statement/statement_factory.h"
#include "c++/declaration/declaration_factory.h"
#include "c++/declarator/declarator_factory.h"
#include "c++/preprocessor/macro_parameter_factory.h"
#include "c++/namespace/identifier_namespace_name.h"

class FormatterStream
{
public:
    FormatterStream(const FormatterConfigurationPtr& formatterConfiguration,
                    const AlignerConfigurationPtr& alignerConfiguration);
    virtual ~FormatterStream();
    
    std::string str();
    
    FormatterStream& operator<<(const lang::cpp::CompoundStatementSPtr& statement);
    FormatterStream& operator<<(const lang::cpp::ClassNestedNameSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::ClassTypeNameSPtr& declaration);
    FormatterStream& operator<<(const lang::cpp::CustomExpressionSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::CustomIdExpressionSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::DeclarationSPtr& declaration);
    FormatterStream& operator<<(const lang::cpp::DeclarationSpecifierSequenceSPtr& declaration);
    FormatterStream& operator<<(const lang::cpp::DeclarationStatementSPtr& statement);
    FormatterStream& operator<<(const lang::cpp::DeclaratorSPtr& declarator);
    FormatterStream& operator<<(const lang::cpp::DeclaratorIdSPtr& declarator);
    FormatterStream& operator<<(const lang::cpp::DeclaratorIdDirectDeclaratorSPtr& declarator);
    FormatterStream& operator<<(const lang::cpp::ExpressionSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::ExpressionListSPtr& expressionList);
    FormatterStream& operator<<(const lang::cpp::ExpressionStatementSPtr& statement);
    FormatterStream& operator<<(const lang::cpp::MacroStatementSPtr& statement);
    FormatterStream& operator<<(const lang::cpp::MemberAccessPostfixExpressionSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::NamespaceNestedNameSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::NestedNameSpecifierSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::IdentifierSPtr& identifier);
    FormatterStream& operator<<(const lang::cpp::IdentifierClassNameSPtr& name);
    FormatterStream& operator<<(const lang::cpp::IdentifierNamespaceNameSPtr& name);
    FormatterStream& operator<<(const lang::cpp::IdentifierUnqualifiedIdSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::IdExpressionPrimaryExpressionSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::InitDeclaratorSPtr& declarator);
    FormatterStream& operator<<(const lang::cpp::ParenthesesPostfixExpressionSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::PrimaryExpressionPostfixExpressionSPtr& expression);
    FormatterStream& operator<<(const lang::cpp::SimpleBlockDeclarationSPtr& declaration);
    FormatterStream& operator<<(const lang::cpp::SimpleDeclarationSPtr& declaration);
    FormatterStream& operator<<(const lang::cpp::StatementSPtr& statement);
    FormatterStream& operator<<(const lang::cpp::Statement::EClose& close);
    FormatterStream& operator<<(const lang::cpp::TypeDeclarationSpecifierSPtr& declaration);
    FormatterStream& operator<<(const lang::cpp::TypeNameSimpleTypeSpecifierSPtr& declaration);
    FormatterStream& operator<<(const lang::cpp::UnqualifiedIdExpressionSPtr& expression);

private:
    AlignerStream mAligner;
    FormatterConfigurationPtr mConfiguration;
};

typedef boost::shared_ptr<FormatterStream> FormatterStreamSPtr;
typedef boost::weak_ptr<FormatterStream> FormatterStreamWPtr;

#endif

