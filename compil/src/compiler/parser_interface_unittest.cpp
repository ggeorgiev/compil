#include "parser_unittest.h"

#include <iostream>

class ParserInterfaceTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("interface");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
    
    void checkInterface(int iIndex, int line, int column, const char* name)
    {
        ASSERT_LT(iIndex, (int)mDocument->objects().size());

        compil::ObjectSPtr pObject = mDocument->objects()[iIndex];
        ASSERT_EQ(compil::EObjectId::interface_(), pObject->runtimeObjectId());
        compil::InterfaceSPtr pInterface = 
            boost::static_pointer_cast<compil::Interface>(pObject);
        EXPECT_STREQ(name, pInterface->name()->value().c_str());
        EXPECT_EQ(lang::compil::Line(line + 1), pInterface->line());
        EXPECT_EQ(lang::compil::Column(column), pInterface->column());
    }

protected:
};

/*
interface name
{
    method change
    {
        --> int32 a;
	<-- int32 b;
	<-> real32 r1;
        <-> real32 r2;
    }

    method change#1
    {
        - a;
	> int32 b;
    }
}
*/

TEST_F(ParserInterfaceTests, interface)
{
    ASSERT_FALSE( parse(
        "interface") );

    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 10, compil::Message::p_expectStatementName));
}

TEST_F(ParserInterfaceTests, interfaceComment)
{
    ASSERT_FALSE( parse(
        "interface //") );

    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 11, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 13, compil::Message::p_expectStatementName));
}

TEST_F(ParserInterfaceTests, interfaceCommentName)
{
    ASSERT_FALSE( parse(
        "interface /* */ name") );

    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 11, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 21, compil::Message::p_expectStatementBody));
}

TEST_F(ParserInterfaceTests, interfaceName)
{
    ASSERT_FALSE( parse(
        "interface name") );

    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 15, compil::Message::p_expectStatementBody));
}

TEST_F(ParserInterfaceTests, interfaceNameOpen)
{
    ASSERT_FALSE( parse(
        "interface name {") );

    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 17, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserInterfaceTests, interfaceNameCommentOpen)
{
    ASSERT_FALSE( parse(
        "interface name /* */ {") );

    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 16, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 23, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserInterfaceTests, interfaceNameOpenClose)
{
    ASSERT_TRUE( parse(
        "interface name {}") );

    ASSERT_EQ(1U, mDocument->objects().size());
    checkInterface(0, 1, 1, "name");
}

TEST_F(ParserInterfaceTests, strongInterfaceNameCommentOpen)
{
    ASSERT_FALSE( parse(
        "strong interface name {}") );
    
    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 1, compil::Message::p_unexpectedStatmentModificator, 
                                  compil::Message::Modificator("strong")));
}

TEST_F(ParserInterfaceTests, 2interfaceNameOpenClose)
{
    ASSERT_TRUE( parse(
        "interface name1 {}\n"
        "interface name2 {}") );

    ASSERT_EQ(2U, mDocument->objects().size());
    checkInterface(0, 1, 1, "name1");
    checkInterface(1, 2, 1, "name2");
}
