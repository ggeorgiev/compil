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

#include "tokenizer.h"

#include <sstream>

namespace compil
{

Tokenizer::Tokenizer(const MessageCollectorPtr& pMessageCollector)
        : mpMessageCollector(pMessageCollector)
        , mCurrentLine(0)
        , mCurrentColumn(0)
        , mBlockComment(false)
{
}

Tokenizer::Tokenizer(const MessageCollectorPtr& pMessageCollector,
                     const SourceIdSPtr& pSourceId, 
                     const boost::shared_ptr<std::istream>& pInput)
        : mpMessageCollector(pMessageCollector)
        , mCurrentLine(0)
        , mCurrentColumn(0)
        , mBlockComment(false)
{
    tokenize(pSourceId, pInput);
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::tokenize(const SourceIdSPtr& pSourceId, const boost::shared_ptr<std::istream>& pInput)
{
    BOOST_ASSERT(!mpInput);
    mpSourceId = pSourceId;
    mpInput = pInput;
    shift();
}

static bool isEOL(int ch)
{
    return 
           (ch == '\n')
        || (ch == '\r');
}

static bool isTab(int ch)
{
    return (ch == '\t');
}

static bool isWhitespace(int ch)
{
    return 
           (ch == ' ') 
        || (ch == '\n')
        || (ch == '\t')
        || (ch == '\r')
        || (ch == '\v')
        || (ch == '\f');
}

static bool isLetter(int ch)
{
    return
           ((ch >= 'a') && (ch <= 'z'))
        || ((ch >= 'A' ) && (ch <= 'Z'));
}

static bool isUnderscore(int ch)
{
    return (ch == '_');
}

static bool isDecimalDigit(int ch)
{
    return ((ch >= '0') && (ch <= '9'));
}

static bool isHexicalDigit(int ch)
{
    return 
           ((ch >= '0') && (ch <= '9'))
        || ((ch >= 'a') && (ch <= 'f'))
        || ((ch >= 'A') && (ch <= 'F'));
}

static bool isNonHexicalLetter(int ch)
{
    return 
           ((ch > 'f') && (ch <= 'z'))
        || ((ch > 'F') && (ch <= 'Z'));
}

static bool isOctalDigit(int ch)
{
    return ((ch >= '0') && (ch <= '7'));
}

static bool isNonOctalDecimalDigit(int ch)
{
    return 
           (ch == '8') 
        || (ch == '9');
}

static bool isZero(int ch)
{
    return 
           (ch == '0');
}

static bool isDot(int ch)
{
    return 
           (ch == '.');
}

static bool isHexIndicator(int ch)
{
    return 
           (ch == 'x')
        || (ch == 'X');
}

static bool isExponent(int ch)
{
    return 
           (ch == 'e')
        || (ch == 'E');
}

static bool isSign(int ch)
{
    return 
           (ch == '-')
        || (ch == '+');
}

static bool isBiwiseOperatorSymbol(int ch)
{
    return 
           (ch == '|')
        || (ch == '&');
}

static bool isArrowSymbol(int ch)
{
    return 
           (ch == '-')
        || (ch == '<')
        || (ch == '>');
}

static bool isBracket(int ch)
{
    return 
           (ch == '{') 
        || (ch == '}');
}

static bool isAngleBracket(int ch)
{
    return 
           (ch == '<')
        || (ch == '>');
}

static bool isQuotationMark(int ch)
{
    return
           (ch == '"')
        || (ch == '\'');
}

static bool isEscape(int ch)
{
    return (ch == '\\');
}

static bool isEscapee(int ch)
{
    return 
           (ch == 'a')
        || (ch == 'b')
        || (ch == 'f')
        || (ch == 'n')
        || (ch == 'r')
        || (ch == 't')
        || (ch == 'v')
        || (ch == '\\')
        || (ch == '?')
        || (ch == '\'')
        || (ch == '\"');
}

static bool isDelimiter(int ch)
{
    return 
           (ch == ';') 
        || (ch == ',');
}

static bool isOperator(int ch)
{
    return 
           (ch == '=');
}

static bool isAsterisk(int ch)
{
    return (ch == '*');
}

static bool isCStyleInitialCommentChar(int ch)
{
    return (ch == '/'); // C style line and block comment initial character
}

static bool isCStyleLineCommentSecondChar(int ch)
{
    return (ch == '/'); // C style line comment second character
}

static bool isCStyleBlockCommentSecondChar(int ch)
{
    return (ch == '*'); // C style block comment second character
}

void Tokenizer::skipWhiteSpaces()
{
    while (!eof())
    {
        int ch = mpInput->get();
        if (!isWhitespace(ch))
		{
            mpInput->clear();
		    mpInput->unget();
			break;
		}
		absorbed(ch);
    }
}

void Tokenizer::skipEOL()
{
    if (eof())
        return;
  
    int ch = mpInput->get();
    if (isEOL(ch))
    {
        absorbed(ch);
    }
    else
    {
        mpInput->clear();
        mpInput->unget();
    }
}

void Tokenizer::consumeCStyleLineComment()
{
    mpCurrent->setType(Token::TYPE_COMMENT);

    while (!eof())
    {
        int ch = mpInput->get();
        if (isEOL(ch))
        {
            mpInput->clear();
            mpInput->unget();
            break;
        }
        absorbed(ch);
        mpCurrent->addChar(ch);
    }
    mpCurrent->setEndColumn(column());
}

void Tokenizer::consumeCStyleBlockComment()
{
    mpCurrent->setType(Token::TYPE_COMMENT);
    for(;;)
    {
        if (eof())
        {
            mpMessageCollector->addMessage(
                Message::SEVERITY_ERROR, Message::t_unterminatedComment,
                mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
            mpCurrent.reset();
            return;
        }
        int ch = mpInput->get();
        if (isEOL(ch))
        {
            mBlockComment = true;
            mpInput->clear();
            mpInput->unget();
            break;
        }
        if (isCStyleBlockCommentSecondChar(ch))
        {       
            if (eof())
            {
                mpMessageCollector->addMessage(
                    Message::SEVERITY_ERROR, Message::t_unterminatedComment,
                    mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
                mpCurrent.reset();
                return;
            }
            int nch = mpInput->get();
            if (isCStyleInitialCommentChar(nch))
            {
                absorbed(ch);
                absorbed(nch);
                mBlockComment = false;
                break;
            }
            mpInput->clear();
            mpInput->unget();
        }
        absorbed(ch);
        mpCurrent->addChar(ch);
    }
    mpCurrent->setEndColumn(column());
}

bool Tokenizer::consumeComment(int ch)
{
    if (eof()) 
    {
        return false;
    }

    int nch = mpInput->get();
    if (isCStyleLineCommentSecondChar(nch))
    {
        absorbed(ch);
        absorbed(nch);
        consumeCStyleLineComment();
    } 
    else if (isCStyleBlockCommentSecondChar(nch)) 
    {
        absorbed(ch);
        absorbed(nch);
        consumeCStyleBlockComment();
    }
    else
    {
        mpInput->clear();
        mpInput->unget();
        return false;
    }
    return true;
}

bool Tokenizer::consumeDot(int ch)
{
    mpCurrent.reset(new Token);
    mpCurrent->setLine(line());
    mpCurrent->setBeginColumn(column());
    mpCurrent->setType(Token::TYPE_DOT);
    if (!eof()) 
    {
        int nch = mpInput->get();
        mpInput->clear();
        mpInput->unget();
        
        if (isDecimalDigit(nch)) 
        {
            return false;
        }
    }

    absorbed(ch);
    mpCurrent->addChar(ch);
    return true;
}

bool Tokenizer::consumeArrow(int ch)
{
    mpCurrent.reset(new Token);
    mpCurrent->setLine(line());
    mpCurrent->setBeginColumn(column());
    mpCurrent->setType(Token::TYPE_OPERATOR_ARROW);

    if (eof()) 
    {
        return false;
    }

    int nch = mpInput->get();
    if (eof() || !isArrowSymbol(nch) || (nch != '-')) 
    {
        mpInput->clear();
        mpInput->unget();
        return false;
    }

    int nnch = mpInput->get();
    if (!isArrowSymbol(nnch) 
	|| !(   (ch == '-' && nnch == '>')
	     || (ch == '<' && nnch == '-')
	     || (ch == '<' && nnch == '>')))
    {
        mpInput->clear();
        mpInput->unget();
        mpInput->unget();
        return false;
    }

    if (!eof())
    {
        int nnnch = mpInput->get();
        mpInput->unget();
        if (isArrowSymbol(nnnch))
        {
            mpInput->clear();
            mpInput->unget();
            mpInput->unget();
            return false;
        }
    }

    absorbed(ch);
    mpCurrent->addChar(ch);
    absorbed(nch);
    mpCurrent->addChar(nch);
    absorbed(nnch);
    mpCurrent->addChar(nnch);

    mpCurrent->setEndColumn(column());
    return true;
}

bool Tokenizer::consumeNumber(int ch)
{
    int count = 0;
    if (isSign(ch))
    {
        bool number = false;
        while (!eof())
        {
            ++count;
            char nch = mpInput->get();
            if (isWhitespace(nch)) 
                continue;
                
            number = isDecimalDigit(nch);
            break;
        }
        if (count)
            mpInput->clear();
        for (int i = 0; i < count; ++i) 
            mpInput->unget();
        
        if (!number)
            return false;
    }
    
    absorbed(ch);
    mpCurrent->addChar(ch);

    for (int i = 0; i < count; ++i)
    {
        char nch = mpInput->get();
        absorbed(nch);
        mpCurrent->addChar(nch);
    }

    bool bDot = false;
    if (isDot(ch))
    {
        bDot = true;
        mpCurrent->setType(Token::TYPE_REAL_LITERAL);
    }
    else
    {
        mpCurrent->setType(Token::TYPE_INTEGER_LITERAL);      
        if (!eof() && isZero(ch))
        {
            ch = mpInput->get();
            if (isHexIndicator(ch))
            {
                if (eof())
                {
                    mpMessageCollector->addMessage(
                            Message::SEVERITY_ERROR, Message::t_invalidIntegerLiteral,
                            mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
                    mpCurrent.reset();
                    return false;
                }

                mpCurrent->addChar(ch);
                absorbed(ch);

                while (!eof())
                {
                    ch = mpInput->get();
                    if (isNonHexicalLetter(ch) || isUnderscore(ch) || isDot(ch))
                    {
                        mpMessageCollector->addMessage(Message::SEVERITY_ERROR, 
                                Message::t_invalidIntegerLiteral,
                                mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
                        mpCurrent.reset();
                        return false;
                    }

                    if (!isHexicalDigit(ch))
                    {
                        mpInput->clear();
                        mpInput->unget();
                        break;
                    }

                    absorbed(ch);
                    mpCurrent->addChar(ch);
                }

                mpCurrent->setEndColumn(column());
                return true;
            }

            for (;;)
            {
                if (   isLetter(ch) 
                    || isDot(ch)
                    || isNonOctalDecimalDigit(ch)
                    || isUnderscore(ch))
                {
                    mpMessageCollector->addMessage(
                            Message::SEVERITY_ERROR, Message::t_invalidIntegerLiteral,
                            mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
                    mpCurrent.reset();
                    return false;
                }

                if (!isOctalDigit(ch))
                {
                    mpInput->clear();
                    mpInput->unget();
                    break;
                }

                absorbed(ch);
                mpCurrent->addChar(ch);
                
                if (eof())
                {
                    break;
                }
                ch = mpInput->get();
            }

            mpCurrent->setEndColumn(column());
            return true;
        }
    }

    bool bExponent = false;
    while (!eof())
    {
        ch = mpInput->get();

        if (isExponent(ch))
        {
            if (bExponent)
            {
                mpMessageCollector->addMessage(
                        Message::SEVERITY_ERROR, Message::t_invalidIntegerLiteral,
                        mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
                mpCurrent.reset();
                return false;	      
            }
            bExponent = true;
            mpCurrent->setType(Token::TYPE_REAL_LITERAL);
            absorbed(ch);
            mpCurrent->addChar(ch);
            
            ch = mpInput->get();
            if (isSign(ch))
            {
                mpCurrent->setType(Token::TYPE_REAL_LITERAL);
                absorbed(ch);
                mpCurrent->addChar(ch);
            }
            else
            {
                mpInput->clear();
                mpInput->unget();
            }
            continue;
        }

        if (isLetter(ch) || isUnderscore(ch))
        {
            mpMessageCollector->addMessage(
                    Message::SEVERITY_ERROR, Message::t_invalidIntegerLiteral,
                    mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
            mpCurrent.reset();
            return false;
        }
     
        if (isDot(ch))
        {
            if (bExponent || bDot)
            {
                mpMessageCollector->addMessage(
                        Message::SEVERITY_ERROR, Message::t_invalidIntegerLiteral,
                        mpSourceId, mpCurrent->line(), mpCurrent->beginColumn());
                mpCurrent.reset();
                return false;	      
            }
            bDot = true;
            mpCurrent->setType(Token::TYPE_REAL_LITERAL);
            absorbed(ch);
            mpCurrent->addChar(ch);
            continue;
        }

        if (!isDecimalDigit(ch))
        {
            mpInput->clear();
            mpInput->unget();
            break;
        }

        absorbed(ch);
        mpCurrent->addChar(ch);
    }

    mpCurrent->setEndColumn(column());
    return true;
}

// TODO: number escape sequence
bool Tokenizer::consumeString(int ch)
{
    mpCurrent.reset(new Token);
    mpCurrent->setLine(line());
    mpCurrent->setBeginColumn(column());
    mpCurrent->setType(Token::TYPE_STRING_LITERAL);

    absorbed(ch);

    int openQuotationMark = ch;
    for (;;)
    {
        if (eof())
        {
            mpMessageCollector->addMessage(
                    Message::SEVERITY_ERROR, Message::t_missingTerminatingQuotationMark,
                    mpSourceId, line(), column());
            mpCurrent.reset();
            return false;
        }

        ch = mpInput->get();
        if (isEOL(ch))
        {
            mpMessageCollector->addMessage(
                    Message::SEVERITY_ERROR, Message::t_missingTerminatingQuotationMark,
                    mpSourceId, line(), column());
            mpCurrent.reset();
            return false;
        }
        
        absorbed(ch);
        if (ch == openQuotationMark)
        {
            break;
        }

        if (isEscape(ch))
        {
            if (eof())
            {
                mpMessageCollector->addMessage(
                        Message::SEVERITY_ERROR, Message::t_unknownEscapeSequence,
                        mpSourceId, line(), column());
                mpCurrent.reset();
                return false;
            }
            int nch = mpInput->get();
            if (!isEscapee(nch))
            {
                mpMessageCollector->addMessage(
                        Message::SEVERITY_ERROR, Message::t_unknownEscapeSequence,
                        mpSourceId, line(), column());
                mpCurrent.reset();
                return false;	        
            }
            mpCurrent->addChar(ch);
            absorbed(nch);
            ch = nch;
        }

        mpCurrent->addChar(ch);
    }

    mpCurrent->setEndColumn(column());
    return true;
}

bool Tokenizer::consumeEqualOperator(int ch)
{
    if (eof()) 
    {
        return false;
    }
    
    mpCurrent.reset(new Token);
    mpCurrent->setLine(line());
    mpCurrent->setBeginColumn(column());
    mpCurrent->setType(Token::TYPE_RELATIONAL_OPERATOR1);

    int nch = mpInput->get();
    if (!isOperator(nch)) 
    {
        mpInput->clear();
        mpInput->unget();
        return false;
    }

    absorbed(ch);
    mpCurrent->addChar(ch);
    absorbed(nch);
    mpCurrent->addChar(nch);

    mpCurrent->setEndColumn(column());
    return true;

}

void Tokenizer::consumeIdentifier(int ch)
{
    mpCurrent.reset(new Token);
    mpCurrent->setLine(line());
    mpCurrent->setBeginColumn(column());
    mpCurrent->setType(Token::TYPE_IDENTIFIER);

    absorbed(ch);
    mpCurrent->addChar(ch);
    while (!eof())
    {
        ch = mpInput->get();
        if (!isLetter(ch) && !isDecimalDigit(ch) && !isUnderscore(ch))
        {
            mpInput->clear();
            mpInput->unget();
            break;
        }
        absorbed(ch);
        mpCurrent->addChar(ch);
    }
    mpCurrent->setEndColumn(column());
}

void Tokenizer::shift()
{
    mpCurrent.reset();

    if (mBlockComment)
    {
        skipEOL();
    }
    else
    {
        skipWhiteSpaces();
        if (mpInput->eof())
            return;
    }

    mpCurrent.reset(new Token);
    mpCurrent->setLine(line());
    mpCurrent->setBeginColumn(column());

    if (mBlockComment)
    {
        consumeCStyleBlockComment();
        return;
    }

    int ch = mpInput->get();
    if (isLetter(ch) || isUnderscore(ch))
    {
        consumeIdentifier(ch);
    }
    else if (isBiwiseOperatorSymbol(ch))
    {
        mpCurrent->setType(Token::TYPE_BITWISE_OPERATOR);
        absorbed(ch);
        mpCurrent->addChar(ch);
        mpCurrent->setEndColumn(column());
    }
    else if (isDot(ch) && consumeDot(ch))
    {
        // nothing
    }
    else if ((isDecimalDigit(ch) || isDot(ch) || isSign(ch)) && consumeNumber(ch))
    {
        // nothing
    }
    else if (isQuotationMark(ch))
    {
        if (!consumeString(ch))
            shift();
    }
    else if (isCStyleInitialCommentChar(ch))
    {
        consumeComment(ch);
    }
    else if (isArrowSymbol(ch) && consumeArrow(ch))
    {
        // nothing
    }
    else if (isBracket(ch))
    {
        mpCurrent->setType(Token::TYPE_BRACKET);
        absorbed(ch);
        mpCurrent->addChar(ch);
        mpCurrent->setEndColumn(column());
    }
    else if (isAngleBracket(ch))
    {
        mpCurrent->setType(Token::TYPE_ANGLE_BRACKET);
        absorbed(ch);
        mpCurrent->addChar(ch);
        mpCurrent->setEndColumn(column());
    }
    else if (isDelimiter(ch))
    {
        mpCurrent->setType(Token::TYPE_DELIMITER);
        absorbed(ch);
        mpCurrent->addChar(ch);
        mpCurrent->setEndColumn(column());
    }
    else if (isOperator(ch) && consumeEqualOperator(ch))
    {
        // nothing
    }
    else if (isOperator(ch))
    {
        mpCurrent->setType(Token::TYPE_OPERATOR);
        absorbed(ch);
        mpCurrent->addChar(ch);
        mpCurrent->setEndColumn(column());
    }
    else if (isAsterisk(ch))
    {
        mpCurrent->setType(Token::TYPE_ASTERISK);
        absorbed(ch);
        mpCurrent->addChar(ch);
        mpCurrent->setEndColumn(column());
    }
    else
    {
        mpCurrent.reset();
    }
}

bool Tokenizer::eof() const
{
    if (mpInput->bad())
        return true;
    if (mpInput->peek() == -1)
        return true;
    return false;
}

void Tokenizer::absorbed(int ch)
{
    if (isTab(ch))
    {
        mCurrentColumn += nTabSize - mCurrentColumn % nTabSize; 
    }
    else if (isEOL(ch))
    {
        ++mCurrentLine;
        mCurrentColumn = 0;
        if (!eof())
        {
            int nch = mpInput->peek();
            if (isEOL(nch) && (nch != ch))
                mpInput->get();
        }
    } 
    else
    {
        ++mCurrentColumn;
    }
}

int Tokenizer::line() const
{
    return mCurrentLine + 1;
}

int Tokenizer::column() const
{
    return mCurrentColumn + 1;
}

TokenPtr Tokenizer::current()
{
    return mpCurrent;
}

bool Tokenizer::check(Token::Type type)
{
    return check(type, NULL);
}

bool Tokenizer::check(Token::Type type, const char* text)
{
    const TokenPtr& pToken = current();
    if (!pToken)
        return false;
    if (pToken->type() != type)
        return false;
    if ((text != NULL) && (pToken->text() != text))
        return false;
    return true;
}

}
