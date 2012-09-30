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
#include "line_aligner.h"

#include <boost/algorithm/string.hpp> 

#include <assert.h>

namespace compil
{

LineAligner::LineAligner(const AlignerConfigurationPtr& pConfig)
        : Aligner(pConfig)
{
    pCurrent.reset(new std::ostringstream());
}

LineAligner::~LineAligner()
{
}

bool LineAligner::isEmpty() const
{
    if (line().tellp() == std::ostringstream::pos_type(0))
        return true;
        
#if _MSC_VER >= 1400 && _MSC_VER <= 1500
    if (line().tellp() == std::ostringstream::pos_type(std::_BADOFF))
        return true;
#endif
        
    return false;
}

void LineAligner::calcWhiteSpaces(int indent, int& nspaces, int& ntabs) const
{
	nspaces = ntabs = 0;
    switch (mpConfiguration->mAlignment)
    {
    case AlignerConfiguration::tabs_only:
    case AlignerConfiguration::smart_tabs:
        ntabs = indent;
        break;
    case AlignerConfiguration::spaces_only:
        nspaces = indent * mpConfiguration->mTabSize;
        break;
    default:
        assert(false && "unknown alignment type");
    }
}

std::string LineAligner::str(int indent) const
{
    std::ostringstream out;

	int nspaces = 0;
	int ntabs = 0;
    if (!isEmpty())
        calcWhiteSpaces(indent, nspaces, ntabs);

    out << std::string(ntabs, '\t') 
        << std::string(nspaces, ' ');
    out << line().str() << '\n';
    return out.str();
}

static bool is_space(char ch)
{
    return ch == ' ';
}

std::string LineAligner::comment(int indent, const std::string& comment) const
{
    std::ostringstream out;

	int nspaces = 0;
	int ntabs = 0;
    if (!isEmpty() || !comment.empty())
        calcWhiteSpaces(indent, nspaces, ntabs);

    out << std::string(ntabs, '\t') << std::string(nspaces, ' ');
    out << line().str();
    
    size_t length = line().str().size();
    if (!isEmpty())
    {
        out << " ";
        ++length;
    }
        
    size_t size = mpConfiguration->mCommentColumnWidthLimit - 
                  (ntabs * mpConfiguration->mTabSize + nspaces + length) - 3;
    
    std::vector<std::string> words;
    boost::split(words, comment, is_space);
    
    size_t current = 0;
    for (std::vector<std::string>::iterator it = words.begin(); it != words.end();)
    {
        if (current == 0)
        {
            out << "// " << *it;
            current += it->size();
            ++it;
        }
        else
        {
            if (current + it->size() + 1 <= size)
            {
                out << " " << *it;
                current += 1 + it->size();
                ++it;
            }
            else
            {
                out << "\n"
                    << std::string(ntabs, '\t') 
                    << std::string(nspaces + length, ' ');
                current = 0;
            }
        }
    }
    
    out << "\n";

    return out.str();
}

std::ostringstream& LineAligner::line() const
{
    assert(pCurrent);
    return *pCurrent;
}

LineAligner& operator<<(LineAligner& aligner, const Aligner::FunctionSpace&)
{
    if (aligner.mpConfiguration->mFunctionSpace)
        aligner << ' ';
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const DecoratedType& decoratedType)
{
    if (decoratedType.declaration() != ETypeDeclaration::invalid())
        aligner << decoratedType.declaration() << ' ';
    aligner << decoratedType.type();
    if (decoratedType.decoration() != ETypeDecoration::invalid())
    {
        if (aligner.mpConfiguration->mDecoration == AlignerConfiguration::part_of_the_type)
            aligner << decoratedType.decoration();
        else if (aligner.mpConfiguration->mDecoration == AlignerConfiguration::part_of_the_name)
            aligner << ' ' << decoratedType.decoration();
        else if (aligner.mpConfiguration->mDecoration == AlignerConfiguration::next_to_the_name)
            aligner << ' ' << decoratedType.decoration();
        else
            assert(false && "unknown decoration type");
    }

    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const DecoratedTypeSPtr& decoratedType)
{
    return aligner << *decoratedType;
}

LineAligner& operator<<(LineAligner& aligner, const FunctionCallSPtr& function)
{
    if (function->namespace_())
        aligner << function->namespace_() << "::";
    aligner << function->name() << Aligner::FunctionSpace();
    aligner << "(";
    if (function->parameters().size() > 0)
        aligner << function->parameters()[0];
    for (size_t i = 1; i < function->parameters().size(); ++i)
        aligner << ", " << function->parameters()[i];
    aligner << ")";
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const FunctionName& functionName)
{
    aligner.line() << functionName.value();
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const FunctionNameSPtr& functionName)
{
    aligner.line() << functionName->value();
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const InitializationSPtr& initialization)
{
    BOOST_ASSERT(!initialization->variableName() != !initialization->constructorName());

    if (initialization->variableName())
        aligner << initialization->variableName();
    else
        aligner << initialization->constructorName();

    aligner << Aligner::FunctionSpace()
            << "("
            << initialization->parameter()
            << ")";
            
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const NamespaceSPtr& namespace_)
{
    if (namespace_)
    {
        const std::vector<NamespaceNameSPtr>& names = namespace_->names();
        for (size_t i = 0; i < names.size(); ++i)
        {
            if (i > 0)
                aligner << "::";
            aligner << names[i]->value();
        }
    }
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const ParameterValueSPtr& parameter)
{
    aligner << parameter->value();
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const ETypeDeclaration& declaration)
{
    if (declaration != ETypeDeclaration::invalid())
        aligner.line() << declaration.shortName();
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const ETypeDecoration& decoration)
{
    switch (decoration.value())
    {
        case ETypeDecoration::kPointer:
            aligner << '*';
            break;
        case ETypeDecoration::kReference:
            aligner << '&';
            break;
        default:
            BOOST_ASSERT(false && "unknown type decoration");
    }

    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const SimpleType& type)
{
    if (type.namespace_())
    if (!type.namespace_()->isVoid())
        aligner << type.namespace_() << "::";
        
    aligner << type.value();
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const SimpleTypeSPtr& type)
{
    if (type->namespace_())
    if (!type->namespace_()->isVoid())
        aligner << type->namespace_() << "::";
    
    aligner << type->value();
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const VariableNameSPtr& name)
{
    aligner << name->value();
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, char ch)
{
    aligner.line() << ch;
    return aligner;
}

LineAligner& operator<<(LineAligner& aligner, const std::string& str)
{
    aligner.line() << str;
    return aligner;
}

}
