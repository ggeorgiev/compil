#include "parser_unittest.h"

#include <iostream>

class ParserInterfaceMethodParameterTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("parameter")
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

    void checkParameter(int iIndex, int mIndex, int pIndex, 
			int line, int column, 
			const char* name, const char* type)
    {
        ASSERT_LT(iIndex, (int)mDocument->objects().size());
        compil::ObjectSPtr pObject = mDocument->objects()[iIndex];

        ASSERT_EQ(compil::EObjectId::interface_(), pObject->runtimeObjectId());
        compil::InterfaceSPtr pInterface = 
            boost::static_pointer_cast<compil::Interface>(pObject);

        ASSERT_LT(mIndex, (int)pInterface->objects().size());
        compil::ObjectSPtr pMObject = pInterface->objects()[mIndex];
        ASSERT_EQ(compil::EObjectId::method(), pMObject->runtimeObjectId());
        compil::MethodSPtr pMethod = 
            boost::static_pointer_cast<compil::Method>(pMObject);

        ASSERT_LT(pIndex, (int)pMethod->objects().size());
        compil::ObjectSPtr pPObject = pMethod->objects()[pIndex];
        ASSERT_EQ(compil::EObjectId::parameter(), pPObject->runtimeObjectId());
        compil::ParameterSPtr pParameter =
            boost::static_pointer_cast<compil::Parameter>(pPObject);

        EXPECT_STREQ(name, pParameter->name()->value().c_str());
        EXPECT_EQ(lang::compil::Line(line + 1), pParameter->line());
        EXPECT_EQ(lang::compil::Column(column), pParameter->column());
        ASSERT_TRUE(pParameter->type());
        EXPECT_STREQ(type, pParameter->type()->name()->value().c_str());
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

TEST_F(ParserInterfaceMethodParameterTests, interfaceMethodArrowClosed)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
            "  {\n"
        "    -->\n"
        "  }\n"
        "}") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 6, 3, compil::Message::p_expectType));
}

TEST_F(ParserInterfaceMethodParameterTests, interfaceMethodArrowSomethingClosed)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
            "  {\n"
        "    -->blah\n"
        "  }\n"
        "}") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 8, compil::Message::p_unknownClassifierType,
                compil::Message::Type("blah")));
}

TEST_F(ParserInterfaceMethodParameterTests, interfaceMethodArrowTypeClosed)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
            "  {\n"
        "    --> integer\n"
        "  }\n"
        "}") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 6, 3, compil::Message::p_expectStatementName));
}

TEST_F(ParserInterfaceMethodParameterTests, interfaceMethodArrowTypeNameClosed)
{
    ASSERT_FALSE( parse(
        "interface name\n"
        "{\n"
        "  method name\n"
            "  {\n"
        "    --> integer name\n"
        "  }\n"
        "}") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 6, 3, compil::Message::p_expectSemicolon));
}

TEST_F(ParserInterfaceMethodParameterTests, interfaceMethodParameterClosed)
{
    ASSERT_TRUE( parse(
        "interface iname\n"
        "{\n"
        "  method mname\n"
            "  {\n"
        "    --> integer pname;\n"
        "  }\n"
        "}") );

    checkInterface(0, 1, 1, "iname");
    checkMethod(0, 0, 3, 3, "mname");
    checkParameter(0, 0, 0, 5, 5, "pname", "integer");

    ASSERT_EQ(0U, mpParser->messages().size());
}

TEST_F(ParserInterfaceMethodParameterTests, interfaceMethod2ParametersClosed)
{
    ASSERT_TRUE( parse(
        "interface iname\n"
        "{\n"
        "  method mname\n"
            "  {\n"
        "    --> integer pname1;\n"
        "    --> integer pname2;\n"
        "  }\n"
        "}") );

    checkInterface(0, 1, 1, "iname");
    checkMethod(0, 0, 3, 3, "mname");
    checkParameter(0, 0, 0, 5, 5, "pname1", "integer");
    checkParameter(0, 0, 1, 6, 5, "pname2", "integer");

    ASSERT_EQ(0U, mpParser->messages().size());
}
