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
#include "table_aligner.h"
#include "function_definition_aligner.h"

#include <boost/algorithm/string.hpp>

#include <assert.h>

namespace compil
{

FunctionDefinitionAligner::FunctionDefinitionAligner(const AlignerConfigurationSPtr& pConfig) 
        : TableAligner(pConfig)
{
}

FunctionDefinitionAligner::~FunctionDefinitionAligner()
{
}

FunctionDefinitionAligner& operator<<(FunctionDefinitionAligner& aligner, 
                                      const FunctionDefinitionAligner::col&)
{
    ((TableAligner&)aligner) << TableAligner::col();
    return aligner;
}

FunctionDefinitionAligner& operator<<(FunctionDefinitionAligner& aligner, 
                                      const FunctionDefinitionAligner::row&)
{
    ((TableAligner&)aligner) << TableAligner::row();
    return aligner;
}

FunctionDefinitionAligner& operator<<(FunctionDefinitionAligner& aligner,
                                      const Aligner::FunctionSpace&)
{
    if (aligner.mConfiguration->mFunctionSpace)
        aligner << ' ';
    return aligner;
}

FunctionDefinitionAligner& operator<<(FunctionDefinitionAligner& aligner, 
                                      const Aligner::FunctionDefinitionTypeSpace&)
{
    ((TableAligner&)aligner) << Aligner::FunctionDefinitionTypeSpace();
    return aligner;
}

FunctionDefinitionAligner& operator<<(FunctionDefinitionAligner& aligner, char ch)
{
    ((TableAligner&)aligner) << ch;
    return aligner;
}

FunctionDefinitionAligner& operator<<(FunctionDefinitionAligner& aligner, const std::string& str)
{
    ((TableAligner&)aligner) << str;
    return aligner;
}


}
