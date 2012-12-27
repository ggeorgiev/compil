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

#include "implementer_stream.h"

#include "c++/expression/custom_expression.h"
#include "c++/statement/compound_statement.h"
#include "c++/statement/macro_statement.h"
#include "c++/statement/statement_factory.h"
#include "c++/statement/test_statement.h"

using namespace lang;
using namespace lang::cpp;

ImplementerStream::ImplementerStream(const ImplementerConfigurationPtr& implementerConfiguration,
                                     const FormatterConfigurationPtr& formatterConfiguration,
                                     const AlignerConfigurationPtr& alignerConfiguration)
    : mFormatter(formatterConfiguration, alignerConfiguration)
    , mConfiguration(implementerConfiguration)
{
}

ImplementerStream::~ImplementerStream()
{
}

std::string ImplementerStream::str()
{
    return mFormatter.str();
}

ImplementerStream& operator<<(ImplementerStream& stream, const TestSuite& suite)
{
    const std::vector<lang::cpp::TestSPtr>& tests = suite.tests();
    
    for (std::vector<TestSPtr>::const_iterator it = tests.begin(); it != tests.end(); ++it)
    {
        const TestSPtr& test = *it;

        MacroStatementSPtr macro = macroStatementRef();
        macro << MacroName("TEST");
        
        macro << (macroParameterRef() << (customExpressionRef() << suite.name().value()));
        macro << (macroParameterRef() << (customExpressionRef() << test->name().value()));
        macro << Statement::EClose::no();
        
        stream.mFormatter << macro;
        
        CompoundStatementSPtr compoundStatement = compoundStatementRef();
        
        const std::vector<StatementSPtr>& statements = test->statements();
        for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
        {
            StatementSPtr statement = *it;
        
            if (statement->runtimeStatementId() == UnaryTestStatement::staticStatementId())
            {
                UnaryTestStatementSPtr teststatement = UnaryTestStatement::downcast(statement);
                MacroStatementSPtr macro = macroStatementRef();
                switch (teststatement->type().value())
                {
                    case UnaryTestStatement::EType::kIsTrue:
                        macro << MacroName("EXPECT_TRUE");
                        break;
                    case UnaryTestStatement::EType::kIsFalse:
                        macro << MacroName("EXPECT_FALSE");
                        break;
                    default:
                        assert(false);
                }
                
                macro << (macroParameterRef() << teststatement->expression());
                statement = macro;
            }
                
            compoundStatement << statement;
        }
        
        stream.mFormatter << compoundStatement;
    }

    return stream;
}