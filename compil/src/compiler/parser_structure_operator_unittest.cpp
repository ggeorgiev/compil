#include "parser_unittest.h"

class ParserStructureOperationTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("identification");
        return BaseParserTests::checkMessage(expected, mIndex);
    }

protected:
};

/*
struct Person 
{
    operation == ;
}
*/

TEST_F(ParserStructureOperationTests, operator)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  operator\n"
        "}") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    //TODO: 
}

TEST_F(ParserStructureOperationTests, operatorEqualTo)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  operator ==\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    // TODO: 
}

TEST_F(ParserStructureOperationTests, operatorEqualToSemicolon)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  operator == ;\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    // TODO: 
}

TEST_F(ParserStructureOperationTests, nativeOperatorEqualToSemicolon)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  native operator == ;\n"
        "}") );
    // TODO: 
}

TEST_F(ParserStructureOperationTests, operatorLessThanSemicolon)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  native operator < ;\n"
        "}") );
    // TODO: 
}

TEST_F(ParserStructureOperationTests, functionOperatorEqualToSemicolon)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  function operator == ;\n"
        "}") );
    // TODO: 
}


TEST_F(ParserStructureOperationTests, functorOperatorEqualToSemicolon)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  functor operator == ;\n"
        "}") );
    // TODO: 
}
