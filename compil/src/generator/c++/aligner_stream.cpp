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

#include "generator/c++/aligner_stream.h"

using namespace lang::all;

const AlignerStream::Endl* AlignerStream::endl = NULL;
const AlignerStream::ResetEndl* AlignerStream::resetEndl = NULL;

AlignerStream::AlignerStream(const AlignerConfigurationSPtr& configuration)
    : mConfiguration(configuration)
    , endlOn(false)
    , level(0)
    , forceLevel(0)
{
}

AlignerStream::~AlignerStream()
{
}

std::string AlignerStream::str()
{
    if (endlOn)
    {
        stream << std::endl;
        endlOn = false;
    }
    
    return stream.str();
}

AlignerStream& AlignerStream::operator<<(const PassageSPtr& passage)
{
    std::vector<ElementSPtr> elements = flatten(passage->elements());
    std::vector<MoldSPtr> molds = mold(elements);

    for (std::vector<MoldSPtr>::const_iterator it = molds.begin(); it != molds.end(); ++it)
        *this << *it;

    return *this;
}

AlignerStream& AlignerStream::operator<<(const MoldSPtr& mold)
{
    if (mold->runtimeElementId() == Level::staticElementId())
        return *this << (Level::downcast(mold));
    if (mold->runtimeElementId() == Line::staticElementId())
        return *this << (Line::downcast(mold));
    if (mold->runtimeElementId() == Scope::staticElementId())
        return *this << (Scope::downcast(mold));
        
    BOOST_ASSERT(false);
    return *this;
}

AlignerStream& AlignerStream::operator<<(const LevelSPtr& level)
{
    forceLevel = level->value();
    return *this;
}

AlignerStream& AlignerStream::operator<<(const LineSPtr& line)
{
    std::string text;
    const std::vector<ElementSPtr>& elements = line->elements();
    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        text += evaluate(*it);

    if (!text.empty())
    {
        *this << indent()
              << text;
    }
        
    *this << endl;
    return *this;
}

AlignerStream& AlignerStream::operator<<(const ScopeSPtr& scope)
{
    *this << resetEndl
          << endl
          << indent()
          << "{"
          << endl;
    
    std::vector<ElementSPtr> elements = flatten(scope->elements());
    std::vector<MoldSPtr> molds = mold(elements);

    {
        ScopeLevel scopeLevel(level);
        for (std::vector<MoldSPtr>::const_iterator it = molds.begin(); it != molds.end(); ++it)
            *this << *it;
    }
    
    *this << indent()
          << "}"
          << scope->close()
          << endl;
          
    return *this;
}

std::string AlignerStream::evaluate(const ElementSPtr& element)
{
    if (element->runtimeElementId() == List::staticElementId())
        return evaluate(List::downcast(element));
    if (element->runtimeElementId() == Passage::staticElementId())
        return evaluate(Passage::downcast(element));
    if (element->runtimeElementId() == String::staticElementId())
        return evaluate(String::downcast(element));
        
    BOOST_ASSERT(false);
    return "";
}

std::string AlignerStream::evaluate(const ListSPtr& list)
{
    std::string result;
    
    switch (list->squiggles().value())
    {
        case List::ESquiggles::kParentheses:
            result += "(";
            break;
    }
    
    std::vector<ElementSPtr> elements = list->elements();
    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
    {
        const ElementSPtr& element = *it;
        
        if (it != elements.begin())
        {
            switch (list->delimiter().value())
            {
                case List::EDelimiter::kComma:
                    result += ", ";
                    break;
            }
        }
        
        result += evaluate(element);
    }
    
    switch (list->squiggles().value())
    {
        case List::ESquiggles::kParentheses:
            result += ")";
            break;
    }
    
    return result;
}

std::string AlignerStream::evaluate(const PassageSPtr& passage)
{
    std::string result;
    
    std::vector<ElementSPtr> elements = flatten(passage->elements());
    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        result += evaluate(*it);

    return result;
}

std::string AlignerStream::evaluate(const StringSPtr& string)
{
    return string->value();
}

std::vector<ElementSPtr> AlignerStream::flatten(const std::vector<ElementSPtr>& elements)
{
    std::vector<ElementSPtr> result;

    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
    {
        PassageSPtr ps = ElementFactory::downcastPassage(*it);
        if (ps)
        {
            std::vector<ElementSPtr> pselements = flatten(ps->elements());
            result.insert(result.end(), pselements.begin(), pselements.end());
            continue;
        }
        
        result.push_back(*it);
    }

    return result;
}

std::vector<MoldSPtr> AlignerStream::mold(const std::vector<ElementSPtr>& elements)
{
    std::vector<MoldSPtr> result;
    
    for (std::vector<ElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
    {
        MoldSPtr mold = ElementFactory::downcastMold(*it);
        if (mold)
        {
            result.push_back(mold);
            continue;
        }
        
        std::vector<ElementSPtr>::const_iterator first = it;
        std::vector<ElementSPtr>::const_iterator last = it;
        while (last != elements.end())
        {
            const ElementSPtr& element = *last;
            if (element->runtimeElementId() == EndOfLine::staticElementId())
            {
                LineSPtr line = lineRef() << std::vector<ElementSPtr>(first, last);
                result.push_back(line);
                it = last;
                break;
            }
            ++last;
            
            BOOST_ASSERT(last != elements.end());
        }
    }
    
    return result;
}

std::string AlignerStream::indent()
{
    long lvl = level + forceLevel;
    BOOST_ASSERT(lvl >= 0);

    forceLevel = 0;

    switch (mConfiguration->mAlignment)
    {
        case AlignerConfiguration::tabs_only:
        case AlignerConfiguration::smart_tabs:
            return std::string(lvl, '\t');
        case AlignerConfiguration::spaces_only:
            return std::string(lvl * mConfiguration->mTabSize, ' ');
        default:
            break;
    }
    assert(false && "unknown alignment type");
    return "";
}

AlignerStream& AlignerStream::operator<<(const std::string& string)
{
    if (endlOn)
    {
        stream << std::endl;
        endlOn = false;
    }
    stream << string;
    return *this;
}

AlignerStream& AlignerStream::operator<<(const Endl* endl)
{
    if (endlOn)
        stream << std::endl;
    else
        endlOn = true;
    return *this;
}

AlignerStream& AlignerStream::operator<<(const ResetEndl* resetEndl)
{
    endlOn = false;
    return *this;
}
