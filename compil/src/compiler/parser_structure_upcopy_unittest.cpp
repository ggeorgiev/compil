#include "parser_unittest.h"

class ParserStructureUpcopyTests : public BaseParserTests 
{
public:
    bool checkUpcopy(int sIndex, int uIndex, int line, int column, 
                     const compil::ObjectSPtr& base, const char* comment = NULL)
    {
        bool result = true;
        
        HF_ASSERT_LT(sIndex, (int)mDocument->objects().size());
        compil::ObjectSPtr pSObject = mDocument->objects()[sIndex];
        
        HF_ASSERT_EQ(compil::EObjectId::structure(), pSObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pSObject);

        HF_ASSERT_LT(uIndex, (int)pStructure->objects().size());
        compil::ObjectSPtr pIObject = pStructure->objects()[uIndex];
        
        HF_ASSERT_EQ(compil::EObjectId::upcopy(), pIObject->runtimeObjectId());
        compil::UpcopySPtr pUpcopy = 
            boost::static_pointer_cast<compil::Upcopy>(pIObject);

        HF_EXPECT_EQ(lang::compil::Line(line + 1), pUpcopy->line());
        HF_EXPECT_EQ(lang::compil::Column(column), pUpcopy->column());
        if (comment)
        {
            HF_ASSERT_TRUE(pUpcopy->comment());
            HF_EXPECT_EQ(1U, pUpcopy->comment()->lines().size());
            HF_EXPECT_STREQ(comment, pUpcopy->comment()->lines()[0].c_str());
        }
        else
        {
            HF_ASSERT_FALSE(pUpcopy->comment());
        }
        
        HF_EXPECT_EQ(base, pUpcopy->baseStructure());
        
        return result;
    }
protected:
};

/*
structure LiveForm
{
    runtime identification;
    int32  id;

    enum Sex
    {
       Unknown,
       Male,
       Female
    }

    Sex sex = Unknown;
}

structure Person inherit LiveForm
{
    runtime identification;
    upcopy from LiveForm;
    
    string name;
    string email = optional;
}

struct Person#1
{
    -- name;
    ++ string firstName;
    ++ string lastName;
}
*/

TEST_F(ParserStructureUpcopyTests, upcopy)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  upcopy\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectKeyword,
                    compil::Message::Keyword("from")));
}

TEST_F(ParserStructureUpcopyTests, upcopyFrom)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  upcopy from\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectClassifierStatementName,
                                  compil::Message::Classifier("upcopy"),
                                  compil::Message::Statement("structure")));
}

TEST_F(ParserStructureUpcopyTests, upcopyFromBlah)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  upcopy from blah\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 15, compil::Message::p_unknownClassifierType,
                                  compil::Message::Classifier("upcopy"),
                                  compil::Message::Type("blah")));
}

TEST_F(ParserStructureUpcopyTests, upcopyFromInteger)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  upcopy from integer\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 15, compil::Message::p_expectAppropriateType,
                                  compil::Message::Classifier("upcopy"),
                                  compil::Message::Options("structure")));
}

TEST_F(ParserStructureUpcopyTests, upcopyFromStruct)
{
    ASSERT_FALSE( parseDocument(
        "structure struct {}\n"
        "structure name\n"
        "{\n"
        "  upcopy from struct\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 15, compil::Message::p_expectAppropriateType,
                                  compil::Message::Classifier("upcopy"),
                                  compil::Message::Options("base structure")));
}


TEST_F(ParserStructureUpcopyTests, inheritUpcopyFromStruct)
{
    ASSERT_FALSE( parseDocument(
        "structure struct {}\n"
        "structure name inherit struct\n"
        "{\n"
        "  upcopy from struct\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 1, compil::Message::p_expectSemicolon));
}

TEST_F(ParserStructureUpcopyTests, inheritUpcopyFromStructSemicolon)
{
    ASSERT_TRUE( parseDocument(
        "structure struct {}\n"
        "structure name inherit struct\n"
        "{\n"
        "  upcopy from struct;\n"
        "}") );

    EXPECT_EQ(2U, mDocument->objects().size());
    EXPECT_TRUE(checkUpcopy(1, 0, 4, 3, mDocument->objects()[0]));
}
