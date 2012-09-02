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
#ifndef _TABLE_ALIGNER_H__
#define _TABLE_ALIGNER_H__

#include "aligner.h"
#include "aligner_configuration.h"

#include <vector>

namespace compil
{


class TableCeil : public std::ostringstream
{
public:
    TableCeil();
    ~TableCeil();
    
    std::vector<size_t> mOptionalNewLineColumns;
};

typedef boost::shared_ptr<TableCeil> TableCeilSPtr;

class TableAligner : public Aligner
{
public:
    class col {};
    class row {};
    class row_line { public: row_line(int indent = 0) : mIndent(indent) {} int mIndent; };
    class row_comment {};
    class optional_new_line {};

    class Row : public std::vector<TableCeilSPtr>
    {
    public:
        enum Type
        {
            invalid = 0,
            normal,
            line,
            comment
        };
        
        Row(Type type = normal, int indent = 0) : mType(type), mIndent(indent)
        {
        }
        
        Type mType;
        int mIndent;
    };


    TableAligner(const AlignerConfigurationPtr& pConfig);
    virtual ~TableAligner();

    bool isEmpty() const;

    virtual std::string str(int indent) const;

    TableCeil& ceil();

    void newColumn();
    void newRow(Row::Type type = Row::normal, int indent = 0);

private:
    std::vector<Row> mTable;

    TableCeilSPtr pCurrent;
};

typedef boost::shared_ptr<TableAligner> TableAlignerPtr;

TableAligner& operator<<(TableAligner& aligner, const Aligner::FunctionSpace&);
TableAligner& operator<<(TableAligner& aligner, const Aligner::FunctionDefinitionTypeSpace&);
TableAligner& operator<<(TableAligner& aligner, const Declaration&);
TableAligner& operator<<(TableAligner& aligner, const DecoratedType&);
TableAligner& operator<<(TableAligner& aligner, const Decoration&);
TableAligner& operator<<(TableAligner& aligner, const Argument&);
TableAligner& operator<<(TableAligner& aligner, const Function&);
TableAligner& operator<<(TableAligner& aligner, const FunctionName&);
TableAligner& operator<<(TableAligner& aligner, const FunctionNameSPtr&);
TableAligner& operator<<(TableAligner& aligner, const Constructor&);
TableAligner& operator<<(TableAligner& aligner, const Destructor&);
TableAligner& operator<<(TableAligner& aligner, const NamespaceSPtr&);
TableAligner& operator<<(TableAligner& aligner, const EMethodSpecifier&);
TableAligner& operator<<(TableAligner& aligner, const FunctionCall&);
TableAligner& operator<<(TableAligner& aligner, const Initialization&);
TableAligner& operator<<(TableAligner& aligner, const SimpleType&);
TableAligner& operator<<(TableAligner& aligner, const TableAligner::col&);
TableAligner& operator<<(TableAligner& aligner, const TableAligner::row&);
TableAligner& operator<<(TableAligner& aligner, const TableAligner::row_line&);
TableAligner& operator<<(TableAligner& aligner, const TableAligner::row_comment&);
TableAligner& operator<<(TableAligner& aligner, const TableAligner::optional_new_line&);

TableAligner& operator<<(TableAligner& aligner, char ch);
TableAligner& operator<<(TableAligner& aligner, const std::string& str);

}
#endif
