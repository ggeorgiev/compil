#include "parser_unittest.h"

#include <iostream>

class ParserInterfaceMethodTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("method")
                 << compil::Message::Context("method")
                 << compil::Message::Options("direction arrow (-->, <--, <->)")
                 << compil::Message::Classifier("parameter");
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

    void checkMethod(int iIndex, int mIndex, 
                     int line, int column, const char* name)
    {
        ASSERT_LT(iIndex, (int)mDocument->objects().size());
        compil::ObjectSPtr pIObject = mDocument->objects()[iIndex];
        ASSERT_EQ(compil::EObjectId::interface_(), pIObject->runtimeObjectId());
        compil::InterfaceSPtr pInterface = 
            boost::static_pointer_cast<compil::Interface>(pIObject);

        ASSERT_LT(mIndex, (int)pInterface->objects().size());
        compil::ObjectSPtr pMObject = pInterface->objects()[mIndex];
        ASSERT_EQ(compil::EObjectId::method(), pMObject->runtimeObjectId());
        compil::MethodSPtr pMethod = 
            boost::static_pointer_cast<compil::Method>(pMObject);

        EXPECT_STREQ(name, pMethod->name()->value().c_str());
        EXPECT_EQ(lang::compil::Line(line + 1), pMethod->line());
        EXPECT_EQ(lang::compil::Column(column), pMethod->column());
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

TEST_F(ParserInterfaceMethodTests, interfaceMethod)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectStatementName));
}

TEST_F(ParserInterfaceMethodTests, interfaceCommentMethod)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  // comment\n"
        "  method\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 1, compil::Message::p_expectStatementName));
}

TEST_F(ParserInterfaceMethodTests, interfaceMethodName)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
        "}") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectStatementBody));
}

TEST_F(ParserInterfaceMethodTests, interfaceMethodCommentName)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method /*comment*/ name") );

    ASSERT_EQ(3U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 10, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 3, 26, compil::Message::p_expectStatementBody));
    EXPECT_TRUE(checkErrorMessage(2, 3, 26, compil::Message::p_unexpectEOFInStatementBody,
                compil::Message::Statement("interface")));
}

TEST_F(ParserInterfaceMethodTests, interfaceMethodNameOpen)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
        "  {\n") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 1, compil::Message::p_unexpectEOFInStatementBody));
    EXPECT_TRUE(checkErrorMessage(1, 5, 1, compil::Message::p_unexpectEOFInStatementBody,
                compil::Message::Statement("interface")));

}

TEST_F(ParserInterfaceMethodTests, interfaceMethodNameOpenClose)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
        "  {}\n") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 1, compil::Message::p_unexpectEOFInStatementBody,
                compil::Message::Statement("interface")));

}

TEST_F(ParserInterfaceMethodTests, interfaceMethodClosed)
{
    ASSERT_TRUE( parse(
        "interface name\n"
        "{\n"
        "  method name {}\n"
        "}") );
        
    checkInterface(0, 1, 1, "name");
    checkMethod(0, 0, 3, 3, "name");
}

TEST_F(ParserInterfaceMethodTests, interface2MethodClosed)
{
    ASSERT_TRUE( parse(
        "interface name\n"
        "{\n"
        "  method name1 {}\n"
        "  method name2 {}\n"
        "}") );
        
    checkInterface(0, 1, 1, "name");
    checkMethod(0, 0, 3, 3, "name1");
    checkMethod(0, 1, 4, 3, "name2");
}

TEST_F(ParserInterfaceMethodTests, interfaceMethodSomething)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
        "  {\n"
        "    int") );
        
    ASSERT_EQ(3U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 5, compil::Message::p_unknownStatment));
    EXPECT_TRUE(checkErrorMessage(1, 5, 8, compil::Message::p_unexpectEOFInStatementBody));
    EXPECT_TRUE(checkErrorMessage(2, 5, 8, compil::Message::p_unexpectEOFInStatementBody,
                compil::Message::Statement("interface")));

}

TEST_F(ParserInterfaceMethodTests, interfaceMethodSomethingClosed)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
        "  {\n"
        "    int"
        "  }\n"
        "}") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 5, compil::Message::p_unknownStatment));
}

TEST_F(ParserInterfaceMethodTests, interfaceMethodArrow)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
            "  {\n"
        "    -->") );
        
    ASSERT_EQ(3U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 8, compil::Message::p_expectType));
    EXPECT_TRUE(checkErrorMessage(1, 5, 8, compil::Message::p_unexpectEOFInStatementBody));
    EXPECT_TRUE(checkErrorMessage(2, 5, 8, compil::Message::p_unexpectEOFInStatementBody,
                compil::Message::Statement("interface")));

}

