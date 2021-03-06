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

#include "c++_keyword.h"

namespace compil
{

CppKeyword::CppKeyword(const FormatterConfigurationSPtr& pConfig)
        : mConfiguration(pConfig)
{
}

CppKeyword::~CppKeyword()
{
}

bool CppKeyword::isKeyword(const std::string& word)
{
    if (word == "bool")         return true;
    if (word == "case")         return true;
    if (word == "class")        return true;
    if (word == "const")        return true;
    if (word == "enum")         return true;
    if (word == "explicit")     return true;
    if (word == "default")      return true;
    if (word == "delete")       return true;
    if (word == "inline")       return true;
    if (word == "namespace")    return true;
    if (word == "new")          return true;
    if (word == "operator")     return true;
    if (word == "private")      return true;
    if (word == "protected")    return true;
    if (word == "public")       return true;
    if (word == "return")       return true;
    if (word == "short")        return true;
    if (word == "static")       return true;
    if (word == "struct")       return true;
    if (word == "switch")       return true;
    if (word == "template")     return true;
    if (word == "union")        return true;
    if (word == "virtual")      return true;
    if (word == "volatile")     return true;
    
// MSVC
    if (word == "interface") return true;
    
    return false;
}

std::string CppKeyword::escapeKeyword(const std::string& word)
{
    if (isKeyword(word))
        return word + "_";
    return word;
}

}

