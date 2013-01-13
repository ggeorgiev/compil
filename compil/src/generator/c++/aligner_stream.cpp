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

AlignerStream::AlignerStream(const AlignerConfigurationSPtr& configuration)
    : mConfiguration(configuration)
{
}

AlignerStream::~AlignerStream()
{
}

std::string AlignerStream::str()
{
    return stream.str();
}

AlignerStream& AlignerStream::operator<<(const ElementSPtr& element)
{
    if (element->runtimeElementId() == EndOfLine::staticElementId())
        return *this << (EndOfLine::downcast(element));
    if (element->runtimeElementId() == List::staticElementId())
        return *this << (List::downcast(element));
    if (element->runtimeElementId() == Passage::staticElementId())
        return *this << (Passage::downcast(element));
    if (element->runtimeElementId() == Scope::staticElementId())
        return *this << (Scope::downcast(element));
    if (element->runtimeElementId() == String::staticElementId())
        return *this << (String::downcast(element));
    return *this;
}

AlignerStream& AlignerStream::operator<<(const EndOfLineSPtr&)
{
    stream << std::endl;
    return *this;
}

AlignerStream& AlignerStream::operator<<(const ListSPtr& list)
{
    switch (list->squiggles().value())
    {
        case List::ESquiggles::kParentheses:
            stream << "(";
            break;
    }
    
    const std::vector<ElementSPtr>& elements = list->elements();
    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
    {
        const ElementSPtr& element = *it;
        
        if (it != elements.begin())
        {
            switch (list->delimiter().value())
            {
                case List::EDelimiter::kComma:
                    stream << ", ";
                    break;
            }
        }
        
        *this << element;
    }
    
    switch (list->squiggles().value())
    {
        case List::ESquiggles::kParentheses:
            stream << ")";
            break;
    }
    
    return *this;
}

AlignerStream& AlignerStream::operator<<(const PassageSPtr& passage)
{
    const std::vector<ElementSPtr>& elements = passage->elements();
    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        *this << *it;
    return *this;
}

AlignerStream& AlignerStream::operator<<(const ScopeSPtr& scope)
{
    stream << std::endl;
    stream << "{";
    stream << std::endl;
    
    const std::vector<ElementSPtr>& elements = scope->elements();
    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
    {
        *this << *it;
//        stream << indent() << line;
//        stream << std::endl;
    }
    
    stream << "}";
    stream << std::endl;
    return *this;
}

AlignerStream& AlignerStream::operator<<(const StringSPtr& string)
{
    stream << string->value();
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