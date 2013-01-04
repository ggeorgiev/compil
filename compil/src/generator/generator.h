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


#ifndef _GENERATOR_H__
#define _GENERATOR_H__

#include "implementer/dependency.h"
#include "implementer/c++_implementer.h"

#include "line_aligner.h"
#include "table_aligner.h"
#include "function_definition_aligner.h"

#include "c++_formatter.h"


#include "configuration_manager.h"

#include "language/compil/document/document.h"

#include <boost/shared_ptr.hpp>

#include <sstream>
#include <string>
#include <map>

namespace compil
{

class Generator
{
public:
    Generator();
    virtual ~Generator();

    virtual bool generate() = 0;
    
    bool init(const std::string& type,
              const AlignerConfigurationSPtr& pAlignerConfiguration,
              const CppFormatterPtr& pFormatter,
              const CppImplementerPtr& pImplementer,
		      const boost::shared_ptr<std::ostream>& pOutput,
		      const DocumentSPtr& document);
              
    std::vector<Dependency> getCoreDependencies() const;

protected:
    std::vector<int> mIndent;

    LineAligner& line();
    void eol(int streamIndex, int indentOffset = 0);
    void resetLine();
    
    TableAligner& table();
    void eot(int streamIndex, int indentOffset = 0);
    
    FunctionDefinitionAligner& fdef();
    void eofd(int streamIndex, int indentOffset = 0);

    void openBlock(int streamIndex, int indentOffset = 0, const char* open = "{");
    void closeBlock(int streamIndex, const char* close = "}");
    
    void openNamespace(int streamIndex);
    void closeNamespace(int streamIndex);
    
    void addDependency(const Dependency& dependency);
    void addDependencies(const std::vector<Dependency>& dependencies);
    
    void includeHeaders(int streamIndex, Dependency::DependencySection section);
    void commentInLine(int streamIndex, const std::string& comment);
    void commentInLine(int streamIndex, const CommentSPtr& pComment);
    void commentInTable(const std::string& comment);
    void commentInTable(const CommentSPtr& pComment);
    
    bool serializeStreams();
    
protected:
    std::string mType;
    
    CppFormatterPtr frm;
    CppImplementerPtr impl;
    AlignerConfigurationSPtr mpAlignerConfiguration;

    DocumentSPtr mDocument;
    std::vector<boost::shared_ptr<std::stringstream> > mStreams;
    
    std::vector<Dependency> dependencies;

private:
    boost::shared_ptr<std::ostream> mpOutput;

    LineAlignerPtr mpLineAligner;
    TableAlignerPtr mpTableAligner;
    FunctionDefinitionAlignerPtr mpFunctionDefinitionAligner;
};

typedef boost::shared_ptr<Generator> GeneratorPtr;

}

#else

namespace compil
{

class Generator;
typedef boost::shared_ptr<Generator> GeneratorPtr;

}

#endif

