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

#ifndef _NAMER_STREAM_H__
#define _NAMER_STREAM_H__

#include "generator/c++/namer_configuration.h"

#include "generator/c++/formatter_stream.h"

#include "language/c++/class/class_specifier.h"
#include "language/c++/class/class_name_factory.h"
#include "language/c++/namespace/namespace_name_factory.h"
#include "language/c++/declaration/declaration_factory.h"
#include "language/c++/declarator/declarator_factory.h"

namespace nmr
{

using namespace lang::cpp;

class NamerStream
{
public:
    NamerStream(const NamerConfigurationSPtr& namerConfiguration,
                const FormatterConfigurationSPtr& formatterConfiguration,
                const AlignerConfigurationSPtr& alignerConfiguration);
    virtual ~NamerStream();
    
    std::string str();
    
    NamerStream& operator<<(const lang::cpp::StatementSPtr& statement);
    NamerStream& operator<<(const lang::cpp::ClassSpecifierSPtr& specifier);

private:
    static BodyFunctionDefinitionSPtr       convertBodyFunctionDefinition(const BodyFunctionDefinitionSPtr& definition);
    static ClassSpecifierSPtr               convertClassSpecifier(const ClassSpecifierSPtr& specifier);
    static ClassHeadSPtr                    convertClassHead(const ClassHeadSPtr& head);
    static DeclarationSPtr                  convertDeclaration(const DeclarationSPtr& declaration);
    static DeclaratorSPtr                   convertDeclarator(const DeclaratorSPtr& declarator);
    static DeclaratorIdSPtr                 convertDeclaratorId(const DeclaratorIdSPtr& declarator);
    static DeclaratorIdDirectDeclaratorSPtr convertDeclaratorIdDirectDeclarator(const DeclaratorIdDirectDeclaratorSPtr& declarator);
    static DirectDeclaratorSPtr             convertDirectDeclarator(const DirectDeclaratorSPtr& declarator);
    static EqualityExpressionSPtr           convertEqualityExpression(const ExpressionSPtr& expression);
    static ExpressionListSPtr               convertExpressionList(const ExpressionListSPtr& list);
    static ExpressionSPtr                   convertExpression(const ExpressionSPtr& expression);
    static FunctionDefinitionSPtr           convertFunctionDefinition(const FunctionDefinitionSPtr& definition);
    static FunctionDefinitionMemberDeclarationSPtr convertFunctionDefinitionMemberDeclaration(const FunctionDefinitionMemberDeclarationSPtr& declaration);
    static FunctionNameSPtr                 convertFunctionName(const FunctionNameSPtr& name);
    static IdentifierSPtr                   convertIdentifier(const ClassNameSPtr& name);
    static FunctionNameDeclaratorIdSPtr     convertFunctionNameDeclaratorId(const FunctionNameDeclaratorIdSPtr& declarator);
    static IdentifierClassNameSPtr          convertIdentifierClassName(const ClassNameSPtr& name);
    static IdentifierMethodNameSPtr         convertIdentifierMethodName(const MethodNameSPtr& name);
    static IdentifierNamespaceNameSPtr      convertIdentifierNamespaceName(const NamespaceNameSPtr& name);
    static MacroParameterSPtr               convertMacroParameter(const MacroParameterSPtr& parameter);
    static MemberDeclarationSPtr            convertMemberDeclaration(const MemberDeclarationSPtr& declaration);
    static MemberDeclaratorSPtr             convertMemberDeclarator(const MemberDeclaratorSPtr& declarator);
    static MemberSpecificationSPtr          convertMemberSpecification(const MemberSpecificationSPtr& specification);
    static MemberSpecificationSectionSPtr   convertMemberSpecificationSection(const MemberSpecificationSectionSPtr& section);
    static ParametersDirectDeclaratorSPtr   convertParametersDirectDeclarator(const ParametersDirectDeclaratorSPtr& declarator);
    static PostfixExpressionSPtr            convertPostfixExpression(const ExpressionSPtr& expression);
    static PureMemberDeclaratorSPtr         convertPureMemberDeclarator(const PureMemberDeclaratorSPtr& declarator);
    static RelationalExpressionSPtr         convertRelationalExpression(const ExpressionSPtr& expression);
    static StatementSPtr                    convertStatement(const StatementSPtr& statement);
    static TypeNameSimpleTypeSpecifierSPtr  convertTypeNameSimpleTypeSpecifier(const ClassSPtr& class_);

    FormatterStream mFormatter;
    NamerConfigurationSPtr mConfiguration;
};

typedef boost::shared_ptr<NamerStream> NamerStreamSPtr;
typedef boost::weak_ptr<NamerStream> NamerStreamWPtr;

}

#endif

