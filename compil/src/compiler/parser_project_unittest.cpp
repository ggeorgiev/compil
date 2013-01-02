#include "parser_unittest.h"

class ParserProjectTests : public BaseParserTests
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("section")
                 << compil::Message::Classifier("base")
                 << compil::Message::Type("name")
                 << compil::Message::Options("structure");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
    
    bool checkStructure(int sIndex, int line, int column, 
                     const char* name, const char* comment = NULL)
    {
        bool result = true;
        EXPECT_LT(sIndex, (int)mDocument->objects().size());

        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        EXPECT_STREQ(name, pStructure->name()->value().c_str());
        EXPECT_EQ(lang::compil::Line(line + 1), pStructure->line());
        HF_EXPECT_EQ(lang::compil::Column(column), pStructure->column());
        
        if (comment)
        {
            EXPECT_TRUE(pStructure->comment());
            EXPECT_EQ(1U, pStructure->comment()->lines().size());
            EXPECT_STREQ(comment, pStructure->comment()->lines()[0].c_str());
        }
        else
        {
            EXPECT_FALSE(pStructure->comment());
        }
        
        return result;
    }
    
};

/*
section main
{
    all/list.scompil;
    all/scope.scompil;
    
    c++/class/class.scompil;
    c++/class/class_name.scompil;
    c++/class/class_name_factory.scompil;
    c++/class/identifier_class_name.scompil;
    c++/class/method.scompil;
    c++/class/method_name.scompil;
}
*/

TEST_F(ParserProjectTests, section)
{
    ASSERT_FALSE( parseProject(
        "section") );

    ASSERT_EQ(1U, messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 8, compil::Message::p_expectStatementName));
}

TEST_F(ParserProjectTests, sectionComment)
{
    ASSERT_FALSE( parseProject(
        "section //") );

    ASSERT_EQ(2U, messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 9, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 11, compil::Message::p_expectStatementName));
}

TEST_F(ParserProjectTests, sectionCommentMain)
{
    ASSERT_FALSE( parseProject(
        "section /* */ main") );

    ASSERT_EQ(2U, messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 9, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 19, compil::Message::p_expectStatementBody));
}

TEST_F(ParserProjectTests, sectionMain)
{
    ASSERT_FALSE( parseProject(
        "section main") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 13, compil::Message::p_expectStatementBody));
}

TEST_F(ParserProjectTests, sectionMainComment)
{
    ASSERT_FALSE( parseProject(
        "section main /* */") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 14, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 19, compil::Message::p_expectStatementBody));
}

TEST_F(ParserProjectTests, sectionMainOpen)
{
    ASSERT_FALSE( parseProject(
        "section main {") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 15, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserProjectTests, sectionMainCommentOpen)
{
    ASSERT_FALSE( parseProject(
        "section main /* */ {") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 14, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 21, compil::Message::p_unexpectEOFInStatementBody));
}
