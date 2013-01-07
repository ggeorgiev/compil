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

#include "generator/implementer/implementer_stream.h"

using namespace lang;
using namespace lang::cpp;

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

        macro << (expressionMacroParameterRef() << teststatement->expression());
        macro << (declarationMacroParameterRef() << (classDeclarationRef() << teststatement->class_()));
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
        
        macro << (expressionMacroParameterRef() << teststatement->expression());
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
        
        macro << (expressionMacroParameterRef() << (customExpressionRef() << suite.name().value()));
        macro << (expressionMacroParameterRef() << (customExpressionRef() << test->name().value()));
        macro << Statement::EClose::no();
        
        mNamer << macro;
        
        CompoundStatementSPtr compoundStatement = compoundStatementRef();
        
        const std::vector<StatementSPtr>& statements = test->statements();
        for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
            compoundStatement << convertStatement(*it);
        
        mNamer << compoundStatement;
    }

    return *this;
}