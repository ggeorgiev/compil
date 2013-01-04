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

#include "project_parser-mixin.h"

namespace compil
{

FilePathSPtr ProjectParserMixin::parseFilePath(const ProjectParseContextSPtr& context)
{
    context->mTokenizer->shiftFilepath();

    FilePathSPtr filePath = boost::make_shared<FilePath>();
    initilizeObject(context, filePath);
    filePath << context->mTokenizer->current()->text();
    
    return filePath;
}

SectionSPtr ProjectParserMixin::parseSection(const ProjectParseContextSPtr& context, const CommentSPtr& comment)
{
    SectionSPtr section = boost::make_shared<Section>();
    initilizeObject(context, section);

    context->mTokenizer->shift();
    skipComments(context);
    if (!context->mTokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        context->mMessageCollector->addMessage(errorMessage(context, Message::p_expectStatementName)
                                               << Message::Statement("section"));
        return SectionSPtr();
    }
    
    NameSPtr name = boost::make_shared<Name>();
    initilizeObject(context, name);
    name << context->mTokenizer->current()->text();
    section << name;
    
    context->mTokenizer->shift();
    skipComments(context);
    
    if (!context->mTokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        context->mMessageCollector->addMessage(errorMessage(context, Message::p_expectStatementBody)
                                               << Message::Statement("section"));
        return SectionSPtr();
    }
    
    for (;;)
    {
        if (context->mTokenizer->eot())
        {
            context->mMessageCollector->addMessage(errorMessage(context, Message::p_unexpectEOFInStatementBody)
                                                   << Message::Statement("section"));
            return SectionSPtr();
        }
        
        FilePathSPtr filePath = parseFilePath(context);
        if (!filePath)
        {
            context->mMessageCollector->addMessage(errorMessage(context, Message::p_expectStatementName)
                                                   << Message::Statement("file path"));
            return SectionSPtr();
        }
        
        // ignore empty paths
        if (!filePath->path().empty())
            section << filePath;

        context->mTokenizer->shift();
        if (context->mTokenizer->check(Token::TYPE_BRACKET, "}"))
        if (filePath->path().empty())
            break;
        
        if (!context->mTokenizer->expect(Token::TYPE_DELIMITER, ";"))
        {
            if (filePath && !filePath->path().empty())
            {
                context->mMessageCollector->addMessage(errorMessage(context, Message::p_expectSemicolon));
                return SectionSPtr();
            }
        }
    }

    return section;
}

void ProjectParserMixin::parseProjectStatement(const ProjectParseContextSPtr& context, const CommentSPtr& comment)
{
    if (context->mTokenizer->check(Token::TYPE_IDENTIFIER, "section"))
    {
        SectionSPtr section = parseSection(context, comment);
        if (section)
        {
            context->mProject << section;
        }
    }
    else
    {
        context->mMessageCollector->addMessage(errorMessage(context, Message::p_unknownStatment)
                                               << Message::Context("top")
                                               << Message::Options("section"));
        context->mTokenizer->shift();
    }
}


ProjectSPtr ProjectParserMixin::parseProject(const ProjectParseContextSPtr& context)
{
    return ProjectSPtr();
}

}
