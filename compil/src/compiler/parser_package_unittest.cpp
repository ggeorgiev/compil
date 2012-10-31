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
    ASSERT_FALSE( parse(
        "package") );

    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 8, compil::Message::p_expectStatementName));
}

TEST_F(ParserPackageTests, packageName)
{
    ASSERT_FALSE( parse(
        "package pname") );

    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 14, compil::Message::p_expectSemicolon));
}

TEST_F(ParserPackageTests, packageNameSemicolon)
{
    ASSERT_TRUE( parse(
        "package pname;") );
        
    ASSERT_TRUE(mpModel->package());
    EXPECT_EQ(1U, mpModel->package()->short_().size());
    EXPECT_STREQ("pname", mpModel->package()->short_()[0].value().c_str());

    EXPECT_EQ(mpModel->package()->short_(), mpModel->package()->levels());
}

TEST_F(ParserPackageTests, packageNameDot)
{
    ASSERT_FALSE( parse(
        "package pname.") );
        
    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 15, compil::Message::p_expectStatementName));
}

TEST_F(ParserPackageTests, packageNameDotName)
{
    ASSERT_FALSE( parse(
        "package pname.pname") );
        
    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 20, compil::Message::p_expectSemicolon));
}

TEST_F(ParserPackageTests, packageNameDotNameSemicolon)
{
    ASSERT_TRUE( parse(
        "package pname1.pname2;") );
        
    ASSERT_TRUE(mpModel->package());
    EXPECT_EQ(2U, mpModel->package()->short_().size());
    EXPECT_STREQ("pname1", mpModel->package()->short_()[0].value().c_str());
    EXPECT_STREQ("pname2", mpModel->package()->short_()[1].value().c_str());

    EXPECT_EQ(mpModel->package()->short_(), mpModel->package()->levels());
}

TEST_F(ParserPackageTests, packageAsterisk)
{
    ASSERT_TRUE( parse(
        "package *;") );
        
    ASSERT_TRUE(mpModel->package());

    EXPECT_EQ(1U, mpModel->package()->short_().size());
    EXPECT_STREQ("external2", mpModel->package()->short_()[0].value().c_str());

    EXPECT_EQ(1U, mpModel->package()->levels().size());
    EXPECT_STREQ("external2", mpModel->package()->levels()[0].value().c_str());
}

TEST_F(ParserPackageTests, packageAsteriskDotAsterisk)
{
    ASSERT_TRUE( parse(
        "package *.*;") );
        
    ASSERT_TRUE(mpModel->package());

    EXPECT_EQ(2U, mpModel->package()->short_().size());
    EXPECT_STREQ("external1", mpModel->package()->short_()[0].value().c_str());
    EXPECT_STREQ("external2", mpModel->package()->short_()[1].value().c_str());
    
    EXPECT_EQ(2U, mpModel->package()->levels().size());
    EXPECT_STREQ("external1", mpModel->package()->levels()[0].value().c_str());
    EXPECT_STREQ("external2", mpModel->package()->levels()[1].value().c_str());
}

TEST_F(ParserPackageTests, packageAsteriskDotAsteriskDotName)
{
    ASSERT_TRUE( parse(
        "package *.*.pname;") );
        
    ASSERT_TRUE(mpModel->package());
    
    EXPECT_EQ(3U, mpModel->package()->short_().size());
    EXPECT_STREQ("external1", mpModel->package()->short_()[0].value().c_str());
    EXPECT_STREQ("external2", mpModel->package()->short_()[1].value().c_str());
    EXPECT_STREQ("pname", mpModel->package()->short_()[2].value().c_str());
    
    EXPECT_EQ(3U, mpModel->package()->levels().size());
    EXPECT_STREQ("external1", mpModel->package()->levels()[0].value().c_str());
    EXPECT_STREQ("external2", mpModel->package()->levels()[1].value().c_str());
    EXPECT_STREQ("pname", mpModel->package()->levels()[2].value().c_str());
}

TEST_F(ParserPackageTests, packageDifferntShortAndLevels)
{
    ASSERT_TRUE( parse(
        "package * | *.pname;") );
        
    ASSERT_TRUE(mpModel->package());
    
    EXPECT_EQ(1U, mpModel->package()->short_().size());
    EXPECT_STREQ("external2", mpModel->package()->short_()[0].value().c_str());
    
    EXPECT_EQ(2U, mpModel->package()->levels().size());
    EXPECT_STREQ("external2", mpModel->package()->levels()[0].value().c_str());
    EXPECT_STREQ("pname", mpModel->package()->levels()[1].value().c_str());
}
