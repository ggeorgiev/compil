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

#include "parser-mixin.h"

#include <boost/algorithm/string.hpp>

namespace compil
{

void ParserMixin::initilizeObject(const ParseContextSPtr& context, ObjectSPtr object)
{
    initilizeObject(context, context->mTokenizer->current(), object);
}

void ParserMixin::initilizeObject(const ParseContextSPtr& context, const TokenPtr& token, ObjectSPtr object)
{
    if (!token)
    {
        initilizeObject(context, object);
        return;
    }
    object->set_sourceId(context->mSourceId);
    object->set_line(token->line());
    object->set_column(token->beginColumn());
}

Message ParserMixin::errorMessage(const ParseContextSPtr& context,
                                  const char* message,
                                  const Line& line,
                                  const Column& column)
{
    return severityMessage(context, Message::SEVERITY_ERROR, message, line, column);
}

Message ParserMixin::warningMessage(const ParseContextSPtr& context,
                                  const char* message,
                                  const Line& line,
                                  const Column& column)
{
    return severityMessage(context, Message::SEVERITY_WARNING, message, line, column);
}

Message ParserMixin::severityMessage(const ParseContextSPtr& context,
                                     const Message::Severity& severity,
                                     const char* message,
                                     const Line& line,
                                     const Column& column)
{
    Line theLine = line;
    if (theLine == Line(-1))
    {
        theLine = context->mTokenizer->current()
                ? context->mTokenizer->current()->line()
                : context->mTokenizer->line();
    }

    Column theColumn = column;
    if (theColumn == Column(-1))
    {
        theColumn = context->mTokenizer->current()
                  ? context->mTokenizer->current()->beginColumn()
                  : context->mTokenizer->column();
    }

    return Message(severity, message, context->mSourceId, theLine, theColumn);
}

CommentSPtr ParserMixin::parseComment(const ParseContextSPtr& context)
{
    CommentSPtr pComment;
    Line lastCommentLine(-1);
    for (;;)
    {
        if (!context->mTokenizer->current())
            break;
        if (context->mTokenizer->current()->type() != Token::TYPE_COMMENT)
            break;
        if (    (lastCommentLine != Line(-1))
             && (Line(1) < context->mTokenizer->current()->line() - lastCommentLine))
            {
            break;
        }
        if (!pComment)
        {
            pComment.reset(new Comment());
            initilizeObject(context, pComment);
        }
        lastCommentLine = context->mTokenizer->current()->line();
        std::string comment_line = context->mTokenizer->current()->text();
        boost::trim(comment_line);
        pComment->mutable_lines().push_back(comment_line);
        context->mTokenizer->shift();
    }
    return pComment;
}

void ParserMixin::skipComments(const ParseContextSPtr& context, CommentSPtr pComment)
{
    if (!pComment)
        pComment = parseComment(context);
    while (pComment)
    {
        context->mMessageCollector->addMessage(
            warningMessage(context, Message::p_misplacedComment,
                           pComment->line(), pComment->column()));
        pComment = parseComment(context);
    }
}

}
