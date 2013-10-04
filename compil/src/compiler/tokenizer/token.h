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

#ifndef _COMPIL_TOKEN_H__
#define _COMPIL_TOKEN_H__

#include "compiler/namespace_alias.h"

#include "language/compil/all/object.h"

#include <boost/shared_ptr.hpp>

#include <memory>
#include <string>

namespace compil
{

class Token
{
public:
    Token();
    ~Token();

    enum Type
    {
        TYPE_INVALID,

        // Comment text. The line comment is returned as a single token.
        // Every line from the block comment is returned as a separate token.
        // If the block comment start from the middle of the line the end
        // of the line is the first token.
        // If the block comment finish in the middle of the line the begging
        // of the line is the last token.
        // If the block comment start and finish at the same line the whole
        // comment is return as a single token.
        // Currently only c style line and block comments are supported
        TYPE_COMMENT,

        // A sequence of letter or underscore, followed from letters, digits or
        // underscores.
        TYPE_IDENTIFIER,

        // A bracket - '{', '}'
        TYPE_BRACKET,

        // A operator - '==', '!='
        TYPE_RELATIONAL_OPERATOR1,

        // A operator - '<', '>'
        TYPE_RELATIONAL_OPERATOR2,

        // An angle bracket - '<', '>'
        TYPE_ANGLE_BRACKET = TYPE_RELATIONAL_OPERATOR2,

        // A delimiter - ';', ','
        TYPE_DELIMITER,

        // An asterisk - '*'
        TYPE_ASTERISK,

        // A dot - '.'
        TYPE_DOT,

        // A operator - '='
        TYPE_OPERATOR,

        // A operator - '|', '&'
        TYPE_BITWISE_OPERATOR,

        // arrow - '-->', '<--' or '<->'
        TYPE_OPERATOR_ARROW,

        // decimal, octal or hex integer literal
        TYPE_INTEGER_LITERAL,

        // real literal
        TYPE_REAL_LITERAL,

        // string literal
        TYPE_STRING_LITERAL,

        // special literals - you may receive some of this literals only with a special call

        // Filepath - you need to call shiftFilepath
        TYPE_FILEPATH,
    };

    Type type() const;
    void setType(Type type);

    std::string text() const;
    void addChar(int ch);

    const Line& line() const;
    void setLine(const Line& line);

    const Column& beginColumn() const;
    void setBeginColumn(const Column& column);

    const Column& endColumn() const;
    void setEndColumn(const Column& column);

private:
    Type mType;

    std::string mText;

    Line mLine;
    Column mBeginColumn;
    Column mEndColumn;
};

typedef boost::shared_ptr<Token> TokenPtr;

}

#else

namespace compil
{

class Token;
typedef boost::shared_ptr<Token> TokenPtr;

}

#endif
