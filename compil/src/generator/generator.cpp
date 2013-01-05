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

#include "generator.h"

namespace compil
{

Generator::Generator()
{
}

Generator::~Generator()
{
}

bool Generator::init(const std::string& type,
                     const AlignerConfigurationSPtr& pAlignerConfiguration,
                     const CppFormatterPtr& pFormatter,
                     const CppImplementerPtr& pImplementer,
                     const boost::shared_ptr<std::ostream>& pOutput,
                     const DocumentSPtr& document)
{
    mType = type;
    
    mpOutput = pOutput;
    mDocument = document;
    
    mpAlignerConfiguration = pAlignerConfiguration;

    mpLineAligner.reset(new LineAligner(mpAlignerConfiguration));
    mpTableAligner.reset(new TableAligner(mpAlignerConfiguration));
    mpFunctionDefinitionAligner.reset(new FunctionDefinitionAligner(mpAlignerConfiguration));
    
    frm = pFormatter;
    impl = pImplementer;
    
    return true;
}

LineAligner& Generator::line()
{
    return *mpLineAligner;
}

void Generator::eol(int streamIndex, int indentOffset)
{
    *mStreams[streamIndex] << line().str(indentOffset + mIndent[streamIndex]);
    resetLine();
}

void Generator::resetLine()
{
    mpLineAligner.reset(new LineAligner(mpAlignerConfiguration));
}

TableAligner& Generator::table()
{
    return *mpTableAligner;
}

void Generator::eot(int streamIndex, int indentOffset)
{
    *mStreams[streamIndex] << table().str(indentOffset + mIndent[streamIndex]);
    mpTableAligner.reset(new TableAligner(mpAlignerConfiguration));
}
    
FunctionDefinitionAligner& Generator::fdef()
{
    return *mpFunctionDefinitionAligner;
}
    
void Generator::eofd(int streamIndex, int indentOffset)
{
    *mStreams[streamIndex] << fdef().str(indentOffset + mIndent[streamIndex]);
    mpFunctionDefinitionAligner.reset(new FunctionDefinitionAligner(mpAlignerConfiguration));
}

void Generator::openBlock(int streamIndex, int indentOffset, const char* open)
{
    int count = 0;
    count += line().isEmpty() ? 0 : 1;
    count += table().isEmpty() ? 0 : 1;
    count += fdef().isEmpty() ? 0 : 1;
    assert(count == 1);
           
    if (!line().isEmpty())
    {
        if (mpAlignerConfiguration->mOpenBlockOnNewLine)
        {
            eol(streamIndex, indentOffset);
            line() << open;
            eol(streamIndex);
        }
        else
        {
            line() << " " << open;
            eol(indentOffset);
        }
    }
    else if (!table().isEmpty())
    {
        if (mpAlignerConfiguration->mOpenBlockOnNewLine)
        {
            eot(streamIndex, indentOffset);
            line() << open;
            eol(streamIndex);
        }
        else
        {
            table() << ' ' << open;
            eot(indentOffset);
        }
    }
    else if (!fdef().isEmpty())
    {
        if (mpAlignerConfiguration->mOpenBlockOnNewLine)
        {
            eofd(streamIndex, indentOffset);
            line() << open;
            eol(streamIndex);
        }
        else
        {
            fdef() << ' ' << open;
            eofd(indentOffset, streamIndex);
        }
    }
    
    ++mIndent[streamIndex];
}

void Generator::closeBlock(int streamIndex, const char* close)
{
    if (!line().isEmpty())
        eol(streamIndex);

    --mIndent[streamIndex];
    line() << close;
    eol(streamIndex);
}

    
void Generator::openNamespace(int streamIndex)
{
    if (mDocument->package())
    {
        const std::vector<PackageElementSPtr>& elements = mDocument->package()->short_();
        for(std::vector<PackageElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        {
            const PackageElementSPtr& element = *it;
            line() << "namespace " << element->value();
            openBlock(streamIndex, 0);
            --mIndent[streamIndex];
            eol(streamIndex);
        }
    }
}

void Generator::closeNamespace(int streamIndex)
{
    if (mDocument->package())
    {
        const std::vector<PackageElementSPtr>& elements = mDocument->package()->short_();
        for(std::vector<PackageElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        {
            ++mIndent[streamIndex];
            closeBlock(streamIndex);
            eol(streamIndex);
        }
    } 
}

void Generator::addDependency(const Dependency& dependency)
{
    if (!dependency) return;
    
    dependencies.push_back(dependency);
}

void Generator::addDependencies(const std::vector<Dependency>& dependencies)
{
    std::vector<Dependency>::const_iterator it;
    for (it = dependencies.begin(); it != dependencies.end(); ++it)
        addDependency(*it);
}

void Generator::includeHeaders(int streamIndex, Dependency::DependencySection section)
{
    std::sort(dependencies.begin(), dependencies.end(), Dependency::compare);

    bool bHasAny = false;
    std::string header;
    std::string library;
    std::vector<Dependency>::iterator it;
    for (it = dependencies.begin(); it != dependencies.end(); ++it)
    {
        const Dependency& dependency = *it;
        if (section != dependency.mSection)
            continue;
            
        std::string newHeader = dependency.mHeaderPackage.empty()
                              ? dependency.mHeaderName
                              : dependency.mHeaderPackage + "/" + dependency.mHeaderName;
        if (header == newHeader)
            continue;
        header = newHeader;
        
        if (library != dependency.mLibrary)
        {
            commentInLine(streamIndex, dependency.mLibrary);
            library = dependency.mLibrary;
        }
            
        bHasAny = true;
            
        line() << "#include ";
        if (dependency.mType == Dependency::system_type)
            line() << "<";
        else if (dependency.mType == Dependency::quote_type)
            line() << "\"";
        
        line() << newHeader;
        
        if (dependency.mType == Dependency::system_type)
            line() << ">";
        else if (dependency.mType == Dependency::quote_type)
            line() << "\"";
            
        eol(streamIndex);
    }
    if (bHasAny)
        eol(streamIndex);
}

void Generator::commentInLine(int streamIndex, const std::string& comment)
{
    *mStreams[streamIndex] << line().comment(mIndent[streamIndex], comment);
    mpLineAligner.reset(new LineAligner(mpAlignerConfiguration));
}

void Generator::commentInLine(int streamIndex, const CommentSPtr& pComment)
{
    std::vector<std::string> lines = pComment->lines();
    std::vector<std::string>::iterator it;
    for (it = lines.begin(); it != lines.end(); ++it)
        commentInLine(streamIndex, *it);
}

void Generator::commentInTable(const std::string& comment)
{
    table() << TableAligner::row_comment()
            << comment;
}

void Generator::commentInTable(const CommentSPtr& pComment)
{
    std::vector<std::string> lines = pComment->lines();
    std::vector<std::string>::iterator it;
    for (it = lines.begin(); it != lines.end(); ++it)
    {
        table() << TableAligner::row_line()
            << "// " << *it;
    }
}

bool Generator::serializeStreams()
{
    std::vector<boost::shared_ptr<std::stringstream> >::iterator it;
    for (it = mStreams.begin(); it != mStreams.end(); ++it)
        *mpOutput << (*it)->str();
    return true;
}

std::vector<Dependency> Generator::getCoreDependencies() const
{
    std::vector<Dependency> result;
    
    std::vector<Dependency>::const_iterator it;
    for (it = dependencies.begin(); it != dependencies.end(); ++it)
    {
        if (it->mLevel == Dependency::core_level)
            result.push_back(*it);
    }
    
    return result;
}


}

