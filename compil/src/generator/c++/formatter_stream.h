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

#include "generator/c++/configuration/formatter_configuration.h"
#include "generator/c++/aligner_stream.h"

#include "language/c++/class/class_specifier.h"
#include "language/c++/class/member_specification.h"
#include "language/c++/class/pure_member_declarator.h"
#include "language/c++/expression/expression_factory.h"
#include "language/c++/statement/statement_factory.h"
#include "language/c++/declaration/declaration_factory.h"
#include "language/c++/declarator/declarator_factory.h"
#include "language/c++/derieved_class/access_specifier.h"
#include "language/c++/preprocessor/macro_argument_factory.h"
#include "language/c++/namespace/identifier_namespace_name.h"

class FormatterStream
{
public:
    FormatterStream(const FormatterConfigurationSPtr& formatterConfiguration,
                    const AlignerConfigurationSPtr& alignerConfiguration);
    virtual ~FormatterStream();
    
    std::string str();
    
    FormatterStream& operator<<(const lang::cpp::StatementSPtr& statement);
    FormatterStream& operator<<(const lang::cpp::ClassSpecifierSPtr& specifier);
    FormatterStream& operator<<(const lang::all::EndOfLineSPtr& endl);
    
protected:
    lang::all::ElementSPtr convert(const lang::cpp::AdditiveShiftExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::BodyFunctionDefinitionSPtr& definition);
    lang::all::ElementSPtr convert(const lang::cpp::BuiltinSimpleTypeSpecifierSPtr& specifier);
    lang::all::ElementSPtr convert(const lang::cpp::CompoundStatementSPtr& statement);
    lang::all::ElementSPtr convert(const lang::cpp::CastPmExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::ClassHeadSPtr& head);
    lang::all::ElementSPtr convert(const lang::cpp::ClassNestedNameSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::ClassTypeNameSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::ClassSpecifierSPtr& specifier);
    lang::all::ElementSPtr convert(const lang::cpp::CVQualifierSequenceSPtr& qualifier);
    lang::all::ElementSPtr convert(const lang::cpp::CVQualifierTypeSpecifierSPtr& specifier);
    lang::all::ElementSPtr convert(const lang::cpp::CustomExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::CustomIdExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::DeclarationSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::DeclarationMacroArgumentSPtr& parameter);
    lang::all::ElementSPtr convert(const lang::cpp::DeclaratorMemberDeclaratorSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::DeclaratorParameterDeclarationSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::DeclarationSpecifierSequenceSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::DeclarationStatementSPtr& statement);
    lang::all::ElementSPtr convert(const lang::cpp::DeclaratorSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::DeclaratorIdDirectDeclaratorSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::EAccessSpecifier& specifier);
    lang::all::ElementSPtr convert(const lang::cpp::EClassKey& key);
    lang::all::ElementSPtr convert(const lang::cpp::ECVQualifier& qualifier);
    lang::all::ElementSPtr convert(const lang::cpp::EFunctionSpecifier& specifier);
    lang::all::ElementSPtr convert(const lang::cpp::EOperator& operator_);
    lang::all::ElementSPtr convert(const lang::cpp::ExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::ExpressionMacroArgumentSPtr& parameter);
    lang::all::ElementSPtr convert(const lang::cpp::ExpressionListSPtr& expressionList);
    lang::all::ElementSPtr convert(const lang::cpp::ExpressionStatementSPtr& statement);
    lang::all::ElementSPtr convert(const lang::cpp::FunctionDeclarationSpecifierSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::FunctionNameDeclaratorIdSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::FunctionDefinitionMemberDeclarationSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::GrammarEqualityExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::MacroNameSPtr& name);
    lang::all::ElementSPtr convert(const lang::cpp::MacroArgumentSPtr& parameter);
    lang::all::ElementSPtr convert(const lang::cpp::MacroStatementSPtr& statement);
    lang::all::ElementSPtr convert(const lang::cpp::MemberAccessPostfixExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::MemberSpecificationSPtr& specification);
    lang::all::ElementSPtr convert(const lang::cpp::MemberSpecificationSectionSPtr& section);
    lang::all::ElementSPtr convert(const lang::cpp::MultiplicativeAdditiveExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::NamespaceNestedNameSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::NestedNameSpecifierSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::IdentifierSPtr& identifier);
    lang::all::ElementSPtr convert(const lang::cpp::IdentifierClassNameSPtr& name);
    lang::all::ElementSPtr convert(const lang::cpp::IdentifierDestructorMethodNameSPtr& name);
    lang::all::ElementSPtr convert(const lang::cpp::IdentifierMethodNameSPtr& name);
    lang::all::ElementSPtr convert(const lang::cpp::IdentifierNamespaceNameSPtr& name);
    lang::all::ElementSPtr convert(const lang::cpp::IdentifierUnqualifiedIdSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::IdExpressionPrimaryExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::InitDeclaratorSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::OperatorFunctionIdSPtr& operator_);
    lang::all::ElementSPtr convert(const lang::cpp::OperatorMethodNameSPtr& name);
    lang::all::ElementSPtr convert(const lang::cpp::ParameterDeclarationListSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::ParameterDeclarationClauseSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::ParametersDirectDeclaratorSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::ParenthesesPostfixExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::PmMultiplicativeExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::PointerDeclaratorSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::PostfixUnaryExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::PrimaryExpressionPostfixExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::RelationalEqualityExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::ReferencePointerOperatorSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::ReturnJumpStatementSPtr& statement);
    lang::all::ElementSPtr convert(const lang::cpp::ShiftRelationalExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::SimpleBlockDeclarationSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::SimpleDeclarationSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::SpecifierMemberDeclarationSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::StatementSPtr& statement);
    lang::all::ElementSPtr convert(const lang::cpp::Statement::EClose& close);
    lang::all::ElementSPtr convert(const lang::cpp::TypeDeclarationSpecifierSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::TypeNameDeclaratorIdSPtr& declarator);
    lang::all::ElementSPtr convert(const lang::cpp::TypeNameSimpleTypeSpecifierSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::VariableExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::VariableNameSPtr& variable);
    lang::all::ElementSPtr convert(const lang::cpp::VariableNameDeclaratorSPtr& declaration);
    lang::all::ElementSPtr convert(const lang::cpp::UnaryCastExpressionSPtr& expression);
    lang::all::ElementSPtr convert(const lang::cpp::UnqualifiedIdExpressionSPtr& expression);
   
private:
    AlignerStream mAligner;
    FormatterConfigurationSPtr mConfiguration;
};

typedef boost::shared_ptr<FormatterStream> FormatterStreamSPtr;
typedef boost::weak_ptr<FormatterStream> FormatterStreamWPtr;

#endif

