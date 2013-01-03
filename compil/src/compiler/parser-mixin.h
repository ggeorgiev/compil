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

#ifndef _COMPIL_PARSER_MIXIN_H__
#define _COMPIL_PARSER_MIXIN_H__

#include "tokenizer.h"

#include "i_source_provider.h"

#include "compil/all/object_factory.h"

#include <map>

namespace compil
{

struct ParseContext
{
    typedef std::map<std::string, SourceIdSPtr> SourceMap;
    typedef boost::shared_ptr<SourceMap> SourceMapSPtr;

    ISourceProviderSPtr mSourceProvider;
    SourceMapSPtr       mSources;

    MessageCollectorPtr mMessageCollector;
    TokenizerPtr        mTokenizer;
    SourceIdSPtr        mSourceId;
};

typedef boost::shared_ptr<ParseContext> ParseContextSPtr;

class ParserMixin
{
public:
    static void initilizeObject(const ParseContextSPtr& context, ObjectSPtr object);
    static void initilizeObject(const ParseContextSPtr& context, const TokenPtr& token, ObjectSPtr object);

    static Message errorMessage(const ParseContextSPtr& context,
                                const char* message,
                                const Line& line = Line(-1),
                                const Column& column = Column(-1));
                                
    static Message warningMessage(const ParseContextSPtr& context,
                                 const char* message,
                                 const Line& line = Line(-1),
                                 const Column& column = Column(-1));
                                
    static CommentSPtr parseComment(const ParseContextSPtr& context);
    static void skipComments(const ParseContextSPtr& context, CommentSPtr pComment = CommentSPtr());
                      
private:
    static Message severityMessage(const ParseContextSPtr& context,
                                   const Message::Severity& severity,
                                   const char* message,
                                   const Line& line,
                                   const Column& column);
};

}

#endif // _COMPIL_PARSER_MIXIN_H__
