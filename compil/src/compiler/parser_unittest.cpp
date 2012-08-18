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
    ASSERT_FALSE( parseRaw(
        "") );
    
    EXPECT_FALSE( mpModel->mainDocument() );
}

TEST_F(ParserTests, whateverWrongStream)
{
    ASSERT_FALSE( parse(
        "something") );

    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 1, compil::Message::p_unknownStatment));
}

TEST_F(ParserTests, documentCommentInTheBeggining)
{
    ASSERT_TRUE( parseRaw(
        "/* comment */ compil {}") );

    ASSERT_TRUE( mpModel->mainDocument() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments().size() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[0]->lines().size());
    ASSERT_EQ(1, mpModel->mainDocument()->comments()[0]->line());
    ASSERT_EQ(1, mpModel->mainDocument()->comments()[0]->column());
    EXPECT_STREQ("comment", mpModel->mainDocument()->comments()[0]->lines()[0].c_str());
}

TEST_F(ParserTests, documentCommentAfterWhiteSpaces)
{
    ASSERT_TRUE( parseRaw(
        "  \n"
        "\n"
        "  /* comment */\n"
        "compil {}") );

    ASSERT_TRUE( mpModel->mainDocument() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments().size() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[0]->lines().size());
    ASSERT_EQ(3, mpModel->mainDocument()->comments()[0]->line());
    ASSERT_EQ(3, mpModel->mainDocument()->comments()[0]->column());
    EXPECT_STREQ("comment", mpModel->mainDocument()->comments()[0]->lines()[0].c_str());
}

TEST_F(ParserTests, documentCommentCStyleBlock)
{
    ASSERT_TRUE( parseRaw(
        "/* line1\n"
        "line2 \n"
        "\n"
        "line4 */\n"
        "compil {}") );

    ASSERT_TRUE( mpModel->mainDocument() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments().size() );
    ASSERT_EQ(4U, mpModel->mainDocument()->comments()[0]->lines().size());
    EXPECT_STREQ("line1", mpModel->mainDocument()->comments()[0]->lines()[0].c_str());
    EXPECT_STREQ("line2", mpModel->mainDocument()->comments()[0]->lines()[1].c_str());
    EXPECT_STREQ("", mpModel->mainDocument()->comments()[0]->lines()[2].c_str());
    EXPECT_STREQ("line4", mpModel->mainDocument()->comments()[0]->lines()[3].c_str());
}

TEST_F(ParserTests, documentCommentCStyleLineMultiple)
{
    ASSERT_TRUE( parseRaw(
        "// line1\n"
        "// line2 \n"
        "//\n"
        "//line4 \n"
        "compil {}") );

    ASSERT_TRUE( mpModel->mainDocument() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments().size() );
    ASSERT_EQ(4U, mpModel->mainDocument()->comments()[0]->lines().size());
    EXPECT_STREQ("line1", mpModel->mainDocument()->comments()[0]->lines()[0].c_str());
    EXPECT_STREQ("line2", mpModel->mainDocument()->comments()[0]->lines()[1].c_str());
    EXPECT_STREQ("", mpModel->mainDocument()->comments()[0]->lines()[2].c_str());
    EXPECT_STREQ("line4", mpModel->mainDocument()->comments()[0]->lines()[3].c_str());
}

TEST_F(ParserTests, documentCommentSecondCStyleBlock)
{
    ASSERT_TRUE( parseRaw(
        "/*comment1*/\n"
        "\n"
        "/*comment2*/\n"
        "compil {}") );

    ASSERT_TRUE( mpModel->mainDocument() );
    ASSERT_EQ(2U, mpModel->mainDocument()->comments().size() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[0]->lines().size());
    EXPECT_STREQ("comment1", mpModel->mainDocument()->comments()[0]->lines()[0].c_str());
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[1]->lines().size());
    EXPECT_STREQ("comment2", mpModel->mainDocument()->comments()[1]->lines()[0].c_str());
}

TEST_F(ParserTests, documentCommentSecondCStyleLine)
{
    ASSERT_TRUE( parseRaw(
        "//comment1\n"
        "\n"
        "//comment2\n"
        "compil {}") );

    ASSERT_TRUE( mpModel->mainDocument() );
    ASSERT_EQ(2U, mpModel->mainDocument()->comments().size() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[0]->lines().size());
    EXPECT_STREQ("comment1", mpModel->mainDocument()->comments()[0]->lines()[0].c_str());
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[1]->lines().size());
    EXPECT_STREQ("comment2", mpModel->mainDocument()->comments()[1]->lines()[0].c_str());
}

TEST_F(ParserTests, mispalcedCStyleBlockCommentInTheBegginingOfTheDocument)
{
    ASSERT_TRUE( parseRaw(
        "/*comment1*/\n"
        "\n"
        "//comment2\n"
        "\n"
        "//comment3\n"
        "compil {}") );

    ASSERT_TRUE( mpModel->mainDocument() );
    ASSERT_EQ(3U, mpModel->mainDocument()->comments().size() );
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[0]->lines().size());
    EXPECT_STREQ("comment1", mpModel->mainDocument()->comments()[0]->lines()[0].c_str());
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[1]->lines().size());
    EXPECT_STREQ("comment2", mpModel->mainDocument()->comments()[1]->lines()[0].c_str());
    ASSERT_EQ(1U, mpModel->mainDocument()->comments()[2]->lines().size());
    EXPECT_STREQ("comment3", mpModel->mainDocument()->comments()[2]->lines()[0].c_str());
}

TEST_F(ParserTests, lastComment0)
{
    StreamPtr pInput = getInput(
        "");

    mpParser->setInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_FALSE( pComment );
}

TEST_F(ParserTests, lastComment1EOF)
{
    StreamPtr pInput = getRawInput(
        "//comment1");

    mpParser->setInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_TRUE( pComment );
    EXPECT_STREQ(pComment->lines()[0].c_str(), "comment1");
}

TEST_F(ParserTests, lastComment1Something)
{
    StreamPtr pInput = getRawInput(
        "//comment1\n"
        "something");

    mpParser->setInput(pInput);
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

    mpParser->setInput(pInput);
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

    mpParser->setInput(pInput);
    compil::CommentSPtr pComment = mpParser->lastComment();

    ASSERT_TRUE( pComment );
    EXPECT_STREQ(pComment->lines()[0].c_str(), "comment2");
}

