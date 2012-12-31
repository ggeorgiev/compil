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

#include "aligner_stream.h"

using namespace lang::all;

AlignerStream::AlignerStream(const AlignerConfigurationPtr& configuration)
    : mConfiguration(configuration)
{
}

AlignerStream::~AlignerStream()
{
}

std::string AlignerStream::str()
{
    return string.str();
}

AlignerStream& AlignerStream::operator<<(const std::string& str)
{
    string << str;
    return *this;
}

AlignerStream& AlignerStream::operator<<(const List& list)
{
    switch (list.squiggles().value())
    {
        case List::ESquiggles::kParentheses:
            string << "(";
            break;
    }
    
    const std::vector<std::string>& items = list.items();
    for (std::vector<std::string>::const_iterator it = items.begin(); it != items.end(); ++it)
    {
        const std::string& item = *it;
        
        if (it != items.begin())
        {
            switch (list.delimiter().value())
            {
                case List::EDelimiter::kComma:
                    string << ", ";
                    break;
            }
        }
        
        string << item;
    }
    
    switch (list.squiggles().value())
    {
        case List::ESquiggles::kParentheses:
            string << ")";
            break;
    }
    
    return *this;
}

AlignerStream& AlignerStream::operator<<(const Scope& scope)
{
    string << std::endl;
    string << "{";
    string << std::endl;
    
    const std::vector<std::string>& lines = scope.lines();
    for (std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        const std::string& line = *it;
        string << indent() << line;
        string << std::endl;
    }
    
    string << "}";
    string << std::endl;
    return *this;
}

std::string AlignerStream::indent() const
{
    switch (mConfiguration->mAlignment)
    {
        case AlignerConfiguration::tabs_only:
        case AlignerConfiguration::smart_tabs:
            return "\t";
        case AlignerConfiguration::spaces_only:
            return std::string(mConfiguration->mTabSize, ' ');
        default:
            break;
    }
    assert(false && "unknown alignment type");
    return "";
}