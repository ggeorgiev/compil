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

#include "compiler/parser/parser-mixin.h"

#include <boost/algorithm/string.hpp>

namespace compil
{

void ParseContext::operator<<=(const Message& message)
{
    mMessageCollector->addMessage(message);
}

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

void ParserMixin::initilizeType(const ParseContextSPtr& context, TypeSPtr type)
{
    initilizeObject(context, type);
    type->set_package(context->mPackage);
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

CommentSPtr ParserMixin::lastComment(const ParseContextSPtr& context)
{
    CommentSPtr comment = parseComment(context);
    while (comment)
    {
        if (!context->mTokenizer->current())
            break;
        if (context->mTokenizer->current()->type() != Token::TYPE_COMMENT)
            break;
        context->mMessageCollector->addMessage(Message::SEVERITY_WARNING, Message::p_misplacedComment,
                                               context->mSourceId, comment->line(), comment->column());
        comment = parseComment(context);
    }
    return comment;
}


FileSPtr ParserMixin::parseFile(const ParseContextSPtr& context)
{
    FileSPtr file = boost::make_shared<File>();

    CommentSPtr pComment = parseComment(context);
    while (pComment)
    {
        file->mutable_comments().push_back(pComment);
        pComment = parseComment(context);
    }

    if (!context->mTokenizer->check(Token::TYPE_IDENTIFIER, "compil"))
        return FileSPtr();

    initilizeObject(context, file);

    context->mTokenizer->shift();
    if (!context->mTokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *context <<= errorMessage(context, Message::p_expectStatementBody)
                     << Message::Statement("compil");
        return FileSPtr();
    }

    context->mTokenizer->shift();
    skipComments(context);

    if (!context->mTokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *context <<= errorMessage(context, Message::p_unexpectEOFInStatementBody)
                     << Message::Statement("compil");
        return FileSPtr();
    }

    context->mTokenizer->shift();

    return file;
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

PackageSPtr ParserMixin::parsePackage(const ParseContextSPtr& context)
{
    PackageSPtr pPackage = boost::make_shared<Package>();
    initilizeObject(context, pPackage);

    std::vector<std::string> short_elements;
    do
    {
        context->mTokenizer->shift();
        skipComments(context);

        if (   context->mTokenizer->expect(Token::TYPE_IDENTIFIER)
            || context->mTokenizer->expect(Token::TYPE_ASTERISK))
        {
            short_elements.push_back(context->mTokenizer->current()->text());
        }
        else
        {
            context->mMessageCollector->addMessage(errorMessage(context, Message::p_expectStatementName)
                                                   << Message::Statement("package"));
            return PackageSPtr();
        }

        context->mTokenizer->shift();
        skipComments(context);

    } while (context->mTokenizer->expect(Token::TYPE_DOT));
    
    std::vector<std::string> levels_elements;
    if (context->mTokenizer->check(Token::TYPE_BITWISE_OPERATOR, "|"))
    {
        do
        {
            context->mTokenizer->shift();
            skipComments(context);

            if (  context->mTokenizer->expect(Token::TYPE_IDENTIFIER)
               || context->mTokenizer->expect(Token::TYPE_ASTERISK))
            {
                levels_elements.push_back(context->mTokenizer->current()->text());
            }
            else
            {
                context->mMessageCollector->addMessage(errorMessage(context, Message::p_expectStatementName)
                                                       << Message::Statement("package"));
                return PackageSPtr();
            }

            context->mTokenizer->shift();
            skipComments(context);

        } while (context->mTokenizer->expect(Token::TYPE_DOT));
    }
    else
    {
        levels_elements = short_elements;
    }

    if (!context->mTokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        context->mMessageCollector->addMessage(errorMessage(context, Message::p_expectSemicolon));
        return PackageSPtr();
    }

    std::vector<PackageElementSPtr> short_;
    if (!convertStringElementsToPackageElements(context, short_elements, short_))
        return PackageSPtr();
        
    std::vector<PackageElementSPtr> levels;
    if (!convertStringElementsToPackageElements(context, levels_elements, levels))
        return PackageSPtr();
    

    pPackage->set_short(short_);
    pPackage->set_levels(levels);
    return pPackage;
}


bool ParserMixin::convertStringElementsToPackageElements(const ParseContextSPtr& context,
                                                         const std::vector<std::string>& string_elements,
                                                         std::vector<PackageElementSPtr>& package_elements)
{
    std::vector<PackageElementSPtr>::const_reverse_iterator eit = context->mSourceId->externalElements().rbegin();

    std::vector<std::string>::const_reverse_iterator it;
    for (it = string_elements.rbegin(); it != string_elements.rend(); ++it)
    {
        PackageElementSPtr pe;
        if (*it == "*")
        {
            if (eit == context->mSourceId->externalElements().rend())
            {
                context->mMessageCollector->addMessage(errorMessage(context, Message::p_asteriskPackageElement));
                return false;
            }
            pe = *eit;
            ++eit;
        }
        else
        {
            if (*eit && (*eit)->value() == *it)
                ++eit;

            pe = boost::make_shared<PackageElement>();
            pe->set_value(*it);
        }
        package_elements.insert(package_elements.begin(), pe);
    }
    return true;
}

void ParserMixin::recoverAfterError(const ParseContextSPtr& context)
{
    for (;;)
    {
        if (!context->mTokenizer->current())
            return;

        if (context->mTokenizer->check(Token::TYPE_BRACKET, "}"))
            break;

        context->mTokenizer->shift();
    }
}

Token::Type ParserMixin::getTokenType(const Type::ELiteral& literal)
{
    switch (literal.value())
    {
        case Type::ELiteral::kBoolean:
        case Type::ELiteral::kReference:
        case Type::ELiteral::kIdentifier:
            return Token::TYPE_IDENTIFIER;
        case Type::ELiteral::kInteger:
            return Token::TYPE_INTEGER_LITERAL;
        case Type::ELiteral::kReal:
            return Token::TYPE_REAL_LITERAL;
        case Type::ELiteral::kString:
            return Token::TYPE_STRING_LITERAL;
        case Type::ELiteral::kBinary:
            break;
        default:
            assert(false);
    }
    return Token::TYPE_INVALID;
}

}
