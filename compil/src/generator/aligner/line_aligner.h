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

#ifndef _LINE_ALIGNER_H__
#define _LINE_ALIGNER_H__

#include "aligner.h"
#include "generator/c++/aligner_configuration.h"

#include <boost/shared_ptr.hpp>

#include <sstream>
#include <vector>

namespace compil
{

class LineAligner : public Aligner
{
public:
    LineAligner(const AlignerConfigurationSPtr& pConfig);
    virtual ~LineAligner();

    bool isEmpty() const;

    virtual std::string str(int indent) const;
    virtual std::string comment(int indent, const std::string& comment) const;

    std::ostringstream& line() const;

private:
    void calcWhiteSpaces(int indent, int& nspaces, int& ntabs) const;

    OSStreamPtr pCurrent;
};

typedef boost::shared_ptr<LineAligner> LineAlignerPtr;

LineAligner& operator<<(LineAligner& aligner, const Aligner::FunctionSpace&);

LineAligner& operator<<(LineAligner& aligner, const cpp::frm::FunctionCallSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::FunctionNameSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::InitializationSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::NamespaceNameSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::NamespaceSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::ParameterValueSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::ETypeDeclaration&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::ETypeDecoration&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::TypeNameSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::TypeSPtr&);
LineAligner& operator<<(LineAligner& aligner, const cpp::frm::VariableNameSPtr&);

LineAligner& operator<<(LineAligner& aligner, char ch);
LineAligner& operator<<(LineAligner& aligner, const std::string& str);
  
// these can't be supported 
// LineAligner& operator<<(LineAligner& aligner, const Aligner::FunctionDefinitionTypeSpace&);


}

#endif
