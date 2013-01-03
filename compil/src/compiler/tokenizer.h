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

#ifndef _COMPIL_TOKENIZER_H__
#define _COMPIL_TOKENIZER_H__

#include "token.h"
#include "message_collector.h"

#include <boost/shared_ptr.hpp>

#include <iostream>
#include <memory>

namespace compil
{

class Tokenizer
{
public:
    Tokenizer(const MessageCollectorPtr& pMessageCollector);
    Tokenizer(const MessageCollectorPtr& pMessageCollector,
              const SourceIdSPtr& pSourceId, 
              const boost::shared_ptr<std::istream>& pInput);
    ~Tokenizer();

    void tokenize(const SourceIdSPtr& pSourceId, const boost::shared_ptr<std::istream>& pInput);

    // shifts the tokenizer to the next token
    void shift();
    void shiftFilepath();
    bool eof() const;
    bool eot() const;

    static const int nTabSize = 4;
    Line line() const;
    Column column() const;

    void absorbed(int ch);

    const TokenPtr& current() const;

    // skips white spaces
    void skipWhiteSpaces();

    // skips EOL
    void skipEOL();

    void consumeCStyleLineComment();
    void consumeCStyleBlockComment();
    bool consumeComment(int ch);
    bool consumeDot(int ch);
    bool consumeArrow(int ch);
    bool consumeNumber(int ch);
    bool consumeString(int ch);
    bool consumeEqualOperator(int ch);
    void consumeIdentifier(int ch);
    
    bool check(const Token::Type type);
    bool check(const Token::Type type, const char* text);
    
    bool expect(Token::Type type);
    bool expect(Token::Type type, const char* text);
    
private:
    MessageCollectorPtr mpMessageCollector;

    TokenPtr mpCurrent;
    SourceIdSPtr mpSourceId;
    boost::shared_ptr<std::istream> mpInput;

    int mCurrentLine;
    int mCurrentColumn;

    bool mBlockComment;
};

typedef boost::shared_ptr<Tokenizer> TokenizerPtr;

}

#else

namespace compil
{

class Tokenizer;

}

#endif
