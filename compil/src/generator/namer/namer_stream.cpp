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

static StatementSPtr convertVariableDeclarationStatement(const VariableDeclarationStatementSPtr& statement)
{
    IdentifierSPtr identifier = (identifierRef() << statement->variable()->name()->value());

    return declarationStatementRef() << statement->type()
                                     << identifier;
}

NamerStream& operator<<(NamerStream& stream, const CompoundStatementSPtr& compoundStatement)
{
    CompoundStatementSPtr newstatement = compoundStatementRef();

    const std::vector<StatementSPtr>& statements = compoundStatement->statements();
    for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
    {
        StatementSPtr statement = *it;
        if (statement->runtimeStatementId() == VariableDeclarationStatement::staticStatementId())
            statement = convertVariableDeclarationStatement(VariableDeclarationStatement::downcast(statement));
        
        newstatement << statement;
    }
    
    stream.mFormatter << newstatement;
    return stream;
}

NamerStream& operator<<(NamerStream& stream, const MacroStatementSPtr& statement)
{
    stream.mFormatter << statement;
    return stream;
}

NamerStream& operator<<(NamerStream& stream, const StatementSPtr& statement)
{
    stream.mFormatter << statement;
    return stream;
}

NamerStream& operator<<(NamerStream& stream, const VariableDeclarationStatementSPtr& statement)
{
    return stream << convertVariableDeclarationStatement(statement);
}
