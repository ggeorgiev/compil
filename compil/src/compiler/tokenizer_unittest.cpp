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

#include "parser_unittest.h"
#include "tokenizer.h"

#include "gtest/gtest.h"

#include <iostream>

class TokenizerTests : public BaseParserTests 
{
public:
	virtual void SetUp() 
	{
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
	}

	// virtual void TearDown() {}
    
    virtual const std::vector<compil::Message> messages()
    {
        return mMessageCollector->messages();
    }

protected:
	void testWhitespace(const char* str, int line, int column)
	{
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));

		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(str));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(lang::compil::Line(line), mpTokenizer->line()) << str;
		EXPECT_EQ(lang::compil::Column(column), mpTokenizer->column()) << str;
		EXPECT_TRUE( mpTokenizer->eof() ) << str;
		EXPECT_EQ(0U, mMessageCollector->messages().size()) << str;
	}

	compil::TokenizerPtr mpTokenizer;
    compil::MessageCollectorPtr mMessageCollector;
};

TEST_F(TokenizerTests, empty)
{
	testWhitespace("", 1, 1);
}

TEST_F(TokenizerTests, skipWhiteSpace)
{
	testWhitespace(" ", 1, 2);
}

TEST_F(TokenizerTests, skipTab)
{
	testWhitespace("\t", 1, 5);
	testWhitespace(" \t", 1, 5);
	testWhitespace("  \t", 1, 5);
	testWhitespace("   \t", 1, 5);
	testWhitespace("    \t", 1, 9);
}

TEST_F(TokenizerTests, skipNewLine)
{
	testWhitespace("\n", 2, 1);
	testWhitespace("\n\r", 2, 1);
	testWhitespace("\r", 2, 1);
	testWhitespace("\r\n", 2, 1);

	testWhitespace("\n\n", 3, 1);
	testWhitespace("\n\r\n\r", 3, 1);
	testWhitespace("\r\r", 3, 1);
	testWhitespace("\r\n\r\n", 3, 1);
	testWhitespace("\n\n", 3, 1);
}

TEST_F(TokenizerTests, IncorrectBlockCStyleComment)
{
	const char* invalid_comments[] = 
	{ 
		"/*", "/**", "/*/"
	};

	for (size_t i = 0; i < sizeof(invalid_comments) / sizeof(invalid_comments[0]); ++i)
	{
		const char* str = invalid_comments[i];
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));

		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(str));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_FALSE(mpTokenizer->current()) << str;
		EXPECT_TRUE(mpTokenizer->eof()) << str;
		ASSERT_EQ(1U, mMessageCollector->messages().size()) << str;
		EXPECT_TRUE(checkErrorMessage(0, 0, 1, compil::Message::t_unterminatedComment));
	}
}

TEST_F(TokenizerTests, commentBlockCStyleOpenSpaceClose)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"/* */"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	ASSERT_TRUE(mpTokenizer);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ(" ", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(6), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}


TEST_F(TokenizerTests, commentBlockCStyleOpenStarClose)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"/***/"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	ASSERT_TRUE(mpTokenizer);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("*", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(6), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentBlockCStyleOpenSlashClose)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"/*/*/"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	ASSERT_TRUE(mpTokenizer);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("/", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(6), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentBlockCStyleOpen2SlashesClose)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"/*//*/"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	ASSERT_TRUE(mpTokenizer);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("//", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(7), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentBlockCStyleOpenNClose)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"/*\n*/"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(3), mpTokenizer->current()->endColumn());
	EXPECT_FALSE( mpTokenizer->eof() );

	mpTokenizer->shift();
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(2), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(3), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );

	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentBlockCStyleOpenN2SlashesClose)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"/*\n//*/"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(3), mpTokenizer->current()->endColumn());
	EXPECT_FALSE( mpTokenizer->eof() );

	mpTokenizer->shift();
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("//", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(2), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(5), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );

	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentBlockCStyleOpenSpaceNSpaceClose)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"/* \n */"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ(" ", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn());
	EXPECT_FALSE( mpTokenizer->eof() );

	mpTokenizer->shift();
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ(" ", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(2), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );

	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentLineCStyle)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"//"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(3), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentLineCStyleSpace)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"// "));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ(" ", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentLineCStyleSpaceNSpace)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"// \n "));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ(" ", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn());
	EXPECT_FALSE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentLineCStyleSpaceRSpace)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"// \n "));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ(" ", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn());
	EXPECT_FALSE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentLineCStyleSlash)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"///"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("/", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, commentLineCStyle2StarsSlash)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"//**/"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_COMMENT, mpTokenizer->current()->type());
	EXPECT_STREQ("**/", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(6), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, 1DecimalDigit)
{
	char str[] = "#";
	for (char n = '0'; n < '9'; ++n)
	{
		str[0] = n;
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type());
		EXPECT_STREQ(str, mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << str;
		EXPECT_EQ(lang::compil::Column(2), mpTokenizer->current()->endColumn()) << str;
		EXPECT_TRUE( mpTokenizer->eof() );
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, integerDecimalNumber)
{
	const char* integers[] = 
	{ 
		"1", "100000", "1234567890",
        "+123", "+ 123", "+    123",
        "-123", "- 123", "-    123" 
	};
    
	for (size_t i = 0; i < sizeof(integers) / sizeof(integers[0]); ++i)
	{
		std::cout << "    " << integers[i] << "\n";
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			integers[i]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type()) << integers[i];
		EXPECT_STREQ(integers[i], mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << integers[i];
		EXPECT_EQ(lang::compil::Column((int)strlen(integers[i]) + 1), mpTokenizer->current()->endColumn());
		EXPECT_TRUE( mpTokenizer->eof() ) << integers[i];
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, nonIntegerDecimalNumber)
{
	const char* non_integers[] = 
	{ 
		"abc", "abc123",
		"--1", "-  -1", "-  +1",
        "++1", "+  +1", "+  -1",
	};

	for (size_t i = 0; i < sizeof(non_integers) / sizeof(non_integers[0]); ++i)
	{
		std::cout << "    " << non_integers[i] << "\n";
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			non_integers[i]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		if (mpTokenizer->current())
			EXPECT_NE(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type()) << non_integers[i];
	}
}

TEST_F(TokenizerTests, wrongDecimal)
{
	char wrong_decimal[] = 
	{ 
		'_',
		'a', 'b', 'c', 'd',/*'e'*/'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r',  's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D',/*'E'*/'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R',  'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	char str[] = "1#";
	for (size_t w = 0; w < sizeof(wrong_decimal); ++w)
	{
		str[1] = wrong_decimal[w];
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		ASSERT_FALSE(mpTokenizer->current()) << str;

		EXPECT_TRUE( mpTokenizer->eof() );
		EXPECT_EQ(1U, mMessageCollector->messages().size());
		EXPECT_TRUE(checkErrorMessage(0, 0, 1, compil::Message::t_invalidIntegerLiteral));
	}
}

TEST_F(TokenizerTests, delimitedDecimal)
{
	char delimiters[] = 
	{ 
		' ', '/', '=', ';', ',', '\n', '+', '-',
	};

	char str[] = "1#";
	for (size_t d = 0; d < sizeof(delimiters); ++d)
	{
		str[1] = delimiters[d];
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		str[1] = '\0';
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type());
		EXPECT_STREQ(str, mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << str;
		EXPECT_EQ(lang::compil::Column(2), mpTokenizer->current()->endColumn()) << str;
		EXPECT_FALSE( mpTokenizer->eof() );
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, 1HexicalDigit)
{
	char hex_digit[] = 
	{ 
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f',
		'A', 'B', 'C', 'D', 'E', 'F',
	};

	char str[] = "0x#";
	for (size_t h = 0; h < sizeof(hex_digit); ++h)
	{
		str[2] = (char)hex_digit[h];
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		ASSERT_TRUE(mpTokenizer->current());
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type());
		EXPECT_STREQ(str, mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << str;
		EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn()) << str;
		EXPECT_TRUE( mpTokenizer->eof() );
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, integerHexicalNumber)
{
	boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
		"0x1234567890abcdefABCDEF"));
	mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
	EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
		mpTokenizer->current()->type());
	EXPECT_STREQ("0x1234567890abcdefABCDEF", mpTokenizer->current()->text().c_str());
	EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
	EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
	EXPECT_EQ(lang::compil::Column(25), mpTokenizer->current()->endColumn());
	EXPECT_TRUE( mpTokenizer->eof() );
	EXPECT_EQ(0U, mMessageCollector->messages().size());
}

TEST_F(TokenizerTests, nonIntegerHexicalNumber)
{
	const char* non_integers[] = 
	{ 
		"0xx", "0xy", "0XX", "0XY",
		"+0x1234", "-0x1234",
        "0x.1234", "0x1234.1234",
	};

	for (size_t i = 0; i < sizeof(non_integers) / sizeof(non_integers[0]); ++i)
	{
		std::cout << "    " << non_integers[i] << "\n";
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			non_integers[i]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		if (mpTokenizer->current())
			EXPECT_NE(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type()) << non_integers[i];
	}
}

TEST_F(TokenizerTests, wrongHexical)
{
	char wrong_hexical[] = 
	{ 
		'_', '.',
		/*'a', 'b', 'c', 'd', 'e', 'f',*/ 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's',   't', 'u', 'v', 'w', 'x', 'y', 'z',
		/*'A', 'B', 'C', 'D', 'E', 'F',*/ 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S',   'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	char str[] = "0x#";
	for (size_t w = 0; w < sizeof(wrong_hexical); ++w)
	{
		str[2] = wrong_hexical[w];
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		ASSERT_FALSE(mpTokenizer->current());

		EXPECT_TRUE(mpTokenizer->eof());
		EXPECT_EQ(1U, mMessageCollector->messages().size());
		EXPECT_TRUE(checkErrorMessage(0, 0, 1, compil::Message::t_invalidIntegerLiteral));
	}
}

TEST_F(TokenizerTests, delimitedHexical)
{
	char delimiters[] = 
	{ 
		' ', '/', '=', ';', ',', '\n', '+', '-'
        // not delimiter: '.'
	};

	char str[] = "0x1#";
	for (size_t d = 0; d < sizeof(delimiters); ++d)
	{
		str[3] = delimiters[d];
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		str[3] = '\0';
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type());
		EXPECT_STREQ(str, mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << str;
		EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn()) << str;
		EXPECT_FALSE( mpTokenizer->eof() );
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, 1OctalDigit)
{
	char str[] = "0#";
	for (char n = '0'; n < '7'; ++n)
	{
		str[1] = n;
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		ASSERT_TRUE(mpTokenizer->current());
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type());
		EXPECT_STREQ(str, mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << str;
		EXPECT_EQ(lang::compil::Column(3), mpTokenizer->current()->endColumn()) << str;
		EXPECT_TRUE( mpTokenizer->eof() );
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, integerOctalNumber)
{
	const char* integers[] = 
	{ 
		"01", "0100000", "012345670",
        "+0123", "+ 0123", "+    0123",
        "-0123", "- 0123", "-    0123" 
	};
    
	for (size_t i = 0; i < sizeof(integers) / sizeof(integers[0]); ++i)
	{
		std::cout << "    " << integers[i] << "\n";
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			integers[i]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type()) << integers[i];
		EXPECT_STREQ(integers[i], mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << integers[i];
		EXPECT_EQ(lang::compil::Column((int)strlen(integers[i]) + 1), mpTokenizer->current()->endColumn());
		EXPECT_TRUE( mpTokenizer->eof() ) << integers[i];
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, wrongOctalDigit)
{
	char wrong_octal[] = 
	{ 
		'8', '9',
		'_', '.',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',/*x*/ 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',/*X*/ 'Y', 'Z'
	};

	char str[] = "0#";
	for (size_t w = 0; w < sizeof(wrong_octal); ++w)
	{
		str[1] = wrong_octal[w];
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		ASSERT_FALSE(mpTokenizer->current()) << str;

		EXPECT_TRUE( mpTokenizer->eof() );
		EXPECT_EQ(1U, mMessageCollector->messages().size());
		EXPECT_TRUE(checkErrorMessage(0, 0, 1, compil::Message::t_invalidIntegerLiteral));
	}
}

TEST_F(TokenizerTests, delimitedOctal)
{
	char delimiters[] = 
	{ 
		' ', '/', '=', ';', ',', '\n', '+', '-',
	};

	char str[] = "01#";
	for (size_t d = 0; d < sizeof(delimiters); ++d)
	{
		str[2] = delimiters[d];
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			str));
		str[2] = '\0';
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_INTEGER_LITERAL, 
			mpTokenizer->current()->type());
		EXPECT_STREQ(str, mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) << str;
		EXPECT_EQ(lang::compil::Column(3), mpTokenizer->current()->endColumn()) << str;
		EXPECT_FALSE( mpTokenizer->eof() );
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, floats)
{
	const char* floats[] = 
	{ 
		"1.1", "12.12",	"1.", "12.",
		"1e1","1E1", "12e12","12E12", 
		"1e-1", "1e+1", "12e-12", "12e+12",
		"1.e1", "12.e12",
		"1.1e1", "12.12e12",
		".1", ".12", ".1e1", ".12e12",
		".1e-1", ".1e+1", ".12e-12", ".12e+12",
	};
    
	for (size_t f = 0; f < sizeof(floats) / sizeof(floats[0]); ++f)
	{
		std::cout << "    " << floats[f] << "\n";
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			floats[f]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_REAL_LITERAL, 
			mpTokenizer->current()->type()) << floats[f];
		EXPECT_STREQ(floats[f], mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) 
			<< floats[f];
		EXPECT_EQ(lang::compil::Column((int)strlen(floats[f]) + 1), mpTokenizer->current()->endColumn())
			<< floats[f];
		EXPECT_TRUE( mpTokenizer->eof() )
			<< floats[f];
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, nonFloats)
{
	const char* non_floats[] = 
	{ 
		"e1.1", "1e.1",
		"1e1e", "11ee",
		"..", "..1",
        ".e1", ".e-1", ".e+1", ".e12", ".e-12", ".e+12"
	};

	for (size_t f = 0; f < sizeof(non_floats) / sizeof(non_floats[0]); ++f)
	{
		std::cout << "    " << non_floats[f] << "\n";
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			non_floats[f]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		if (mpTokenizer->current())
			EXPECT_NE(compil::Token::TYPE_REAL_LITERAL, 
			mpTokenizer->current()->type()) << non_floats[f];
	}
}

TEST_F(TokenizerTests, strings)
{
	const char* strings[] = 
	{ 
		"\"\"", "''",
		"\"whatever text\"", "'whatever text'",
		"\"'\"", "'\"'",
		"\"\\\\\"", "'\\\\'",
		"\"\\a\\b\\f\\n\\r\\t\\v\\\\\\?\\'\\\"\"", 
		"'\\a\\b\\f\\n\\r\\t\\v\\\\\\?\\'\\\"'",
	};

	for (size_t s = 0; s < sizeof(strings) / sizeof(strings[0]); ++s)
	{
		std::cout << "    " << strings[s] << "\n";
		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			strings[s]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		EXPECT_EQ(compil::Token::TYPE_STRING_LITERAL, 
			mpTokenizer->current()->type()) << strings[s];

		std::string result = strings[s] + 1;
		result.erase(result.length() - 1);

		EXPECT_STREQ(result.c_str(), mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn()) 
			<< strings[s];

		EXPECT_EQ(lang::compil::Column((int)strlen(strings[s]) + 1), mpTokenizer->current()->endColumn())
			<< strings[s];
		EXPECT_TRUE( mpTokenizer->eof() )
			<< strings[s];
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, notTerminatedStrings)
{
	const char* strings[] = 
	{ 
		"\"", "'",
		"\"\n", "'\n", "\"\n\"", "'\n'",
		"\"\\\"", "'\\'",
	};
	const int column[] =
	{
		2, 2,
		2, 2, 2, 2,
		4, 4,
	};
	for (size_t s = 0; s < sizeof(strings) / sizeof(strings[0]); ++s)
	{
		std::cout << "    " << strings[s] << "\n";

		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));

		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			strings[s]));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);

		compil::TokenPtr pToken = mpTokenizer->current();
		if (pToken)
			EXPECT_NE(compil::Token::TYPE_STRING_LITERAL, pToken->type());

		EXPECT_LE(1U, mMessageCollector->messages().size());
		EXPECT_TRUE(checkErrorMessage(0, 0, column[s], compil::Message::t_missingTerminatingQuotationMark));
	}
}

TEST_F(TokenizerTests, wrongEscapee)
{
	const char* strings[] = 
	{ 
		"\"\\y\"", "'\\y'",
	};
	const int column[] =
	{
		3, 3,
	};
	for (size_t s = 0; s < sizeof(strings) / sizeof(strings[0]); ++s)
	{
		std::cout << "    " << strings[s] << "\n";

		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));

		boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
			strings[s]));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);

		compil::TokenPtr pToken = mpTokenizer->current();
		if (pToken)
			EXPECT_NE(compil::Token::TYPE_STRING_LITERAL, pToken->type());

		EXPECT_LE(1, (int)mMessageCollector->messages().size());
		EXPECT_TRUE(checkErrorMessage(0, 0, column[s], compil::Message::t_unknownEscapeSequence));
	}
}

TEST_F(TokenizerTests, identifier)
{
	char first[] = 
	{ 
		'_',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	char next[] = 
	{ 
		'_',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};

	char delimiter[] =
	{
		'\0',
		' ', '\n', '\t', '\r', '\v', '\f',
		'/'
	};

	char str[] = "fnd";
	for (size_t f = 0; f < sizeof(first); ++f)
	{
		str[0] = first[f];
		for (size_t n = 0; n < sizeof(next); ++n)
		{
			str[1] = next[n];
			for (size_t d = 0; d < sizeof(delimiter); ++d)
			{
				str[2] = delimiter[d];
				boost::shared_ptr<std::stringstream> pInput(new std::stringstream(
					str));
				mMessageCollector.reset(new compil::MessageCollector());
				mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
				mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
				str[2] = '\0';
				EXPECT_STREQ(str, mpTokenizer->current()->text().c_str());
				EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
				EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
				EXPECT_EQ(lang::compil::Column(3), mpTokenizer->current()->endColumn());
				EXPECT_EQ(0U, mMessageCollector->messages().size());
			}
		}
	}
}

TEST_F(TokenizerTests, arrow)
{
	const char* arrows[] = 
	{ 
		"-->", "<--", "<->",
		"-->O", "<--O", "<->O",
	};

	for (size_t a = 0; a < sizeof(arrows) / sizeof(arrows[0]); ++a)
	{
		std::cout << "    " << arrows[a] << "\n";
		boost::shared_ptr<std::stringstream> 
			pInput(new std::stringstream(arrows[a]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		compil::TokenPtr pToken = mpTokenizer->current();
		ASSERT_TRUE(pToken);
		EXPECT_EQ(compil::Token::TYPE_OPERATOR_ARROW, pToken->type());
		EXPECT_STREQ(std::string(arrows[a]).substr(0,3).c_str(), 
			mpTokenizer->current()->text().c_str());
		EXPECT_EQ(lang::compil::Line(1), mpTokenizer->current()->line());
		EXPECT_EQ(lang::compil::Column(1), mpTokenizer->current()->beginColumn());
		EXPECT_EQ(lang::compil::Column(4), mpTokenizer->current()->endColumn());
		EXPECT_EQ(0U, mMessageCollector->messages().size());
	}
}

TEST_F(TokenizerTests, bitwise_operator)
{
	const char* bitwise_operators[] = 
	{ 
		"|", "&"
	};

	for (size_t b = 0; b < sizeof(bitwise_operators) / sizeof(bitwise_operators[0]); ++b)
	{
		std::cout << "    " << bitwise_operators[b] << "\n";
		boost::shared_ptr<std::stringstream> 
			pInput(new std::stringstream(bitwise_operators[b]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		compil::TokenPtr pToken = mpTokenizer->current();
		EXPECT_EQ(compil::Token::TYPE_BITWISE_OPERATOR, pToken->type());
	}
}

TEST_F(TokenizerTests, relational_operator1)
{
	const char* relational_operators[] = 
	{ 
		"=="
	};

	for (size_t a = 0; a < sizeof(relational_operators) / sizeof(relational_operators[0]); ++a)
	{
		std::cout << "    " << relational_operators[a] << "\n";
		boost::shared_ptr<std::stringstream> 
			pInput(new std::stringstream(relational_operators[a]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		compil::TokenPtr pToken = mpTokenizer->current();
        EXPECT_EQ(compil::Token::TYPE_RELATIONAL_OPERATOR1, pToken->type());
	}
}

TEST_F(TokenizerTests, relational_operator2)
{
	const char* relational_operators[] = 
	{ 
		"<", ">"
	};

	for (size_t a = 0; a < sizeof(relational_operators) / sizeof(relational_operators[0]); ++a)
	{
		std::cout << "    " << relational_operators[a] << "\n";
		boost::shared_ptr<std::stringstream> 
			pInput(new std::stringstream(relational_operators[a]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		compil::TokenPtr pToken = mpTokenizer->current();
        EXPECT_EQ(compil::Token::TYPE_RELATIONAL_OPERATOR2, pToken->type());
	}
}

TEST_F(TokenizerTests, non_arrow)
{
	const char* non_arrows[] = 
	{ 
		"-", "<", ">",
		"--", "<<", ">>",
		"-<", "<-", "->", ">-", "<>", "><",
		"--<", ">--", "><>", "<><",
		"-->>", "<---"
	};

	for (size_t a = 0; a < sizeof(non_arrows) / sizeof(non_arrows[0]); ++a)
	{
		std::cout << "    " << non_arrows[a] << "\n";
		boost::shared_ptr<std::stringstream> 
			pInput(new std::stringstream(non_arrows[a]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		compil::TokenPtr pToken = mpTokenizer->current();
		if (pToken)
			EXPECT_NE(compil::Token::TYPE_OPERATOR_ARROW, pToken->type());
	}
}

TEST_F(TokenizerTests, angle_brackets)
{
	const char* brackets[] = 
	{ 
		"<", ">",
		"< < > >",
        "<< >>",
	};

	for (size_t b = 0; b < sizeof(brackets) / sizeof(brackets[0]); ++b)
	{
		std::cout << "    " << brackets[b] << "\n";
		boost::shared_ptr<std::stringstream> 
			pInput(new std::stringstream(brackets[b]));
		mMessageCollector.reset(new compil::MessageCollector());
		mpTokenizer.reset(new compil::Tokenizer(mMessageCollector));
		mpTokenizer->tokenize(compil::SourceIdSPtr(), pInput);
		compil::TokenPtr pToken = mpTokenizer->current();
		while (pToken)
		{
			EXPECT_NE(compil::Token::TYPE_OPERATOR_ARROW, pToken->type());
			EXPECT_EQ(compil::Token::TYPE_ANGLE_BRACKET, pToken->type());
			mpTokenizer->shift();
			pToken = mpTokenizer->current();
		}
	}
}
