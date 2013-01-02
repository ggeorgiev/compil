#include "parser_unittest.h"

#include "parser.h"

#include "gtest/gtest.h"

#include <iostream>


class ParserTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Context("top");
        expected << compil::Message::Options("structure, interface, enum, specimen, identifier or factory");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
};

TEST_F(ParserTests, emptyStream)
{
    ASSERT_FALSE( parseRawDocument(
        "") );
    
    EXPECT_FALSE( mDocument->mainFile() );
}

TEST_F(ParserTests, whateverWrongStream)
{
    ASSERT_FALSE( parseDocument(
        "something") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 1, compil::Message::p_unknownStatment));
}

TEST_F(ParserTests, documentCommentInTheBeggining)
{
    ASSERT_TRUE( parseRawDocument(
        "/* comment */ compil {}") );

    ASSERT_TRUE( mDocument->mainFile() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments().size() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[0]->lines().size());
    ASSERT_EQ(lang::compil::Line(1), mDocument->mainFile()->comments()[0]->line());
    ASSERT_EQ(lang::compil::Column(1), mDocument->mainFile()->comments()[0]->column());
    EXPECT_STREQ("comment", mDocument->mainFile()->comments()[0]->lines()[0].c_str());
}

TEST_F(ParserTests, documentCommentAfterWhiteSpaces)
{
    ASSERT_TRUE( parseRawDocument(
        "  \n"
        "\n"
        "  /* comment */\n"
        "compil {}") );

    ASSERT_TRUE( mDocument->mainFile() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments().size() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[0]->lines().size());
    ASSERT_EQ(lang::compil::Line(3), mDocument->mainFile()->comments()[0]->line());
    ASSERT_EQ(lang::compil::Column(3), mDocument->mainFile()->comments()[0]->column());
    EXPECT_STREQ("comment", mDocument->mainFile()->comments()[0]->lines()[0].c_str());
}

TEST_F(ParserTests, documentCommentCStyleBlock)
{
    ASSERT_TRUE( parseRawDocument(
        "/* line1\n"
        "line2 \n"
        "\n"
        "line4 */\n"
        "compil {}") );

    ASSERT_TRUE( mDocument->mainFile() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments().size() );
    ASSERT_EQ(4U, mDocument->mainFile()->comments()[0]->lines().size());
    EXPECT_STREQ("line1", mDocument->mainFile()->comments()[0]->lines()[0].c_str());
    EXPECT_STREQ("line2", mDocument->mainFile()->comments()[0]->lines()[1].c_str());
    EXPECT_STREQ("", mDocument->mainFile()->comments()[0]->lines()[2].c_str());
    EXPECT_STREQ("line4", mDocument->mainFile()->comments()[0]->lines()[3].c_str());
}

TEST_F(ParserTests, documentCommentCStyleLineMultiple)
{
    ASSERT_TRUE( parseRawDocument(
        "// line1\n"
        "// line2 \n"
        "//\n"
        "//line4 \n"
        "compil {}") );

    ASSERT_TRUE( mDocument->mainFile() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments().size() );
    ASSERT_EQ(4U, mDocument->mainFile()->comments()[0]->lines().size());
    EXPECT_STREQ("line1", mDocument->mainFile()->comments()[0]->lines()[0].c_str());
    EXPECT_STREQ("line2", mDocument->mainFile()->comments()[0]->lines()[1].c_str());
    EXPECT_STREQ("", mDocument->mainFile()->comments()[0]->lines()[2].c_str());
    EXPECT_STREQ("line4", mDocument->mainFile()->comments()[0]->lines()[3].c_str());
}

TEST_F(ParserTests, documentCommentSecondCStyleBlock)
{
    ASSERT_TRUE( parseRawDocument(
        "/*comment1*/\n"
        "\n"
        "/*comment2*/\n"
        "compil {}") );

    ASSERT_TRUE( mDocument->mainFile() );
    ASSERT_EQ(2U, mDocument->mainFile()->comments().size() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[0]->lines().size());
    EXPECT_STREQ("comment1", mDocument->mainFile()->comments()[0]->lines()[0].c_str());
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[1]->lines().size());
    EXPECT_STREQ("comment2", mDocument->mainFile()->comments()[1]->lines()[0].c_str());
}

TEST_F(ParserTests, documentCommentSecondCStyleLine)
{
    ASSERT_TRUE( parseRawDocument(
        "//comment1\n"
        "\n"
        "//comment2\n"
        "compil {}") );

    ASSERT_TRUE( mDocument->mainFile() );
    ASSERT_EQ(2U, mDocument->mainFile()->comments().size() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[0]->lines().size());
    EXPECT_STREQ("comment1", mDocument->mainFile()->comments()[0]->lines()[0].c_str());
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[1]->lines().size());
    EXPECT_STREQ("comment2", mDocument->mainFile()->comments()[1]->lines()[0].c_str());
}

TEST_F(ParserTests, mispalcedCStyleBlockCommentInTheBegginingOfTheDocument)
{
    ASSERT_TRUE( parseRawDocument(
        "/*comment1*/\n"
        "\n"
        "//comment2\n"
        "\n"
        "//comment3\n"
        "compil {}") );

    ASSERT_TRUE( mDocument->mainFile() );
    ASSERT_EQ(3U, mDocument->mainFile()->comments().size() );
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[0]->lines().size());
    EXPECT_STREQ("comment1", mDocument->mainFile()->comments()[0]->lines()[0].c_str());
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[1]->lines().size());
    EXPECT_STREQ("comment2", mDocument->mainFile()->comments()[1]->lines()[0].c_str());
    ASSERT_EQ(1U, mDocument->mainFile()->comments()[2]->lines().size());
    EXPECT_STREQ("comment3", mDocument->mainFile()->comments()[2]->lines()[0].c_str());
}

TEST_F(ParserTests, lastComment0)
{
    StreamPtr pInput = getInput(
        "");

    mpParser->setDocumentInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_FALSE( pComment );
}

TEST_F(ParserTests, lastComment1EOF)
{
    StreamPtr pInput = getRawInput(
        "//comment1");

    mpParser->setDocumentInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_TRUE( pComment );
    EXPECT_STREQ(pComment->lines()[0].c_str(), "comment1");
}

TEST_F(ParserTests, lastComment1Something)
{
    StreamPtr pInput = getRawInput(
        "//comment1\n"
        "something");

    mpParser->setDocumentInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_TRUE( pComment );
    EXPECT_STREQ(pComment->lines()[0].c_str(), "comment1");
}

TEST_F(ParserTests, lastComment2EOF)
{
    StreamPtr pInput = getRawInput(
        "//comment1\n"
        "\n"
        "//comment2");

    mpParser->setDocumentInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_TRUE( pComment );
    EXPECT_STREQ(pComment->lines()[0].c_str(), "comment2");
}

TEST_F(ParserTests, lastComment2Something)
{
    StreamPtr pInput = getRawInput(
        "//comment1\n"
        "\n"
        "//comment2\n"
        "something");

    mpParser->setDocumentInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_TRUE( pComment );
    EXPECT_STREQ(pComment->lines()[0].c_str(), "comment2");
}

