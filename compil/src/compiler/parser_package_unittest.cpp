#include "parser_unittest.h"

#include <iostream>

class ParserPackageTests : public BaseParserTests 
{
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("package");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
};

/*
 
package a.b.c;

*/

TEST_F(ParserPackageTests, package)
{
    ASSERT_FALSE( parseDocument(
        "package") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 8, compil::Message::p_expectStatementName));
}

TEST_F(ParserPackageTests, packageName)
{
    ASSERT_FALSE( parseDocument(
        "package pname") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 14, compil::Message::p_expectSemicolon));
}

TEST_F(ParserPackageTests, packageNameSemicolon)
{
    ASSERT_TRUE( parseDocument(
        "package pname;") );
        
    ASSERT_TRUE(mDocument->package());
    EXPECT_EQ(1U, mDocument->package()->short_().size());
    EXPECT_STREQ("pname", mDocument->package()->short_()[0]->value().c_str());

    EXPECT_TRUE(compil::Document::compareElementValues(mDocument->package()->short_(),
                                                       mDocument->package()->levels()));
}

TEST_F(ParserPackageTests, packageNameDot)
{
    ASSERT_FALSE( parseDocument(
        "package pname.") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 15, compil::Message::p_expectStatementName));
}

TEST_F(ParserPackageTests, packageNameDotName)
{
    ASSERT_FALSE( parseDocument(
        "package pname.pname") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 20, compil::Message::p_expectSemicolon));
}

TEST_F(ParserPackageTests, packageNameDotNameSemicolon)
{
    ASSERT_TRUE( parseDocument(
        "package pname1.pname2;") );
        
    ASSERT_TRUE(mDocument->package());
    EXPECT_EQ(2U, mDocument->package()->short_().size());
    EXPECT_STREQ("pname1", mDocument->package()->short_()[0]->value().c_str());
    EXPECT_STREQ("pname2", mDocument->package()->short_()[1]->value().c_str());

    EXPECT_TRUE(compil::Document::compareElementValues(mDocument->package()->short_(),
                                                       mDocument->package()->levels()));
}

TEST_F(ParserPackageTests, packageAsterisk)
{
    ASSERT_TRUE( parseDocument(
        "package *;") );
        
    ASSERT_TRUE(mDocument->package());

    EXPECT_EQ(1U, mDocument->package()->short_().size());
    EXPECT_STREQ("external2", mDocument->package()->short_()[0]->value().c_str());

    EXPECT_EQ(1U, mDocument->package()->levels().size());
    EXPECT_STREQ("external2", mDocument->package()->levels()[0]->value().c_str());
}

TEST_F(ParserPackageTests, packageAsteriskDotAsterisk)
{
    ASSERT_TRUE( parseDocument(
        "package *.*;") );
        
    ASSERT_TRUE(mDocument->package());

    EXPECT_EQ(2U, mDocument->package()->short_().size());
    EXPECT_STREQ("external1", mDocument->package()->short_()[0]->value().c_str());
    EXPECT_STREQ("external2", mDocument->package()->short_()[1]->value().c_str());
    
    EXPECT_EQ(2U, mDocument->package()->levels().size());
    EXPECT_STREQ("external1", mDocument->package()->levels()[0]->value().c_str());
    EXPECT_STREQ("external2", mDocument->package()->levels()[1]->value().c_str());
}

TEST_F(ParserPackageTests, packageAsteriskDotAsteriskDotName)
{
    ASSERT_TRUE( parseDocument(
        "package *.*.pname;") );
        
    ASSERT_TRUE(mDocument->package());
    
    EXPECT_EQ(3U, mDocument->package()->short_().size());
    EXPECT_STREQ("external1", mDocument->package()->short_()[0]->value().c_str());
    EXPECT_STREQ("external2", mDocument->package()->short_()[1]->value().c_str());
    EXPECT_STREQ("pname", mDocument->package()->short_()[2]->value().c_str());
    
    EXPECT_EQ(3U, mDocument->package()->levels().size());
    EXPECT_STREQ("external1", mDocument->package()->levels()[0]->value().c_str());
    EXPECT_STREQ("external2", mDocument->package()->levels()[1]->value().c_str());
    EXPECT_STREQ("pname", mDocument->package()->levels()[2]->value().c_str());
}

TEST_F(ParserPackageTests, packageDifferntShortAndLevels)
{
    ASSERT_TRUE( parseDocument(
        "package * | *.pname;") );
        
    ASSERT_TRUE(mDocument->package());
    
    EXPECT_EQ(1U, mDocument->package()->short_().size());
    EXPECT_STREQ("external2", mDocument->package()->short_()[0]->value().c_str());
    
    EXPECT_EQ(2U, mDocument->package()->levels().size());
    EXPECT_STREQ("external2", mDocument->package()->levels()[0]->value().c_str());
    EXPECT_STREQ("pname", mDocument->package()->levels()[1]->value().c_str());
}
