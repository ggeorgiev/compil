#include "parser_unittest.h"

class ParserStructureIdentificationTests : public BaseParserTests
{
public:
    virtual bool checkMessage(compil::Message& expected, size_t mIndex)
    {
        expected << compil::Message::Statement("identification");
        return BaseParserTests::checkMessage(expected, mIndex);
    }

    bool checkIdentification(size_t sIndex, size_t iIndex, int line, int column,
                             compil::Identification::EType type, const char* comment = NULL)
    {
        bool result = true;

        HF_ASSERT_LT(sIndex, mDocument->objects().size());
        compil::ObjectSPtr pSObject = mDocument->objects()[sIndex];

        HF_ASSERT_EQ(compil::EObjectId::structure(), pSObject->runtimeObjectId());
        compil::StructureSPtr pStructure =
            boost::static_pointer_cast<compil::Structure>(pSObject);

        HF_ASSERT_LT(iIndex, pStructure->objects().size());
        compil::ObjectSPtr pIObject = pStructure->objects()[iIndex];

        HF_ASSERT_EQ(compil::EObjectId::identification(), pIObject->runtimeObjectId());
        compil::IdentificationSPtr pIdentification =
            boost::static_pointer_cast<compil::Identification>(pIObject);

        HF_EXPECT_EQ(lang::compil::Line(line + 1), pIdentification->line());
        HF_EXPECT_EQ(lang::compil::Column(column), pIdentification->column());
        if (comment)
        {
            HF_ASSERT_TRUE(pIdentification->comment());
            HF_EXPECT_EQ(1U, pIdentification->comment()->lines().size());
            HF_EXPECT_STREQ(comment, pIdentification->comment()->lines()[0].c_str());
        }
        else
        {
            HF_ASSERT_FALSE(pIdentification->comment());
        }

        HF_EXPECT_EQ(type, pIdentification->type())

        return result;
    }
protected:
};

/*
struct Person
{
    runtime identification;

    int32  id;
    string name;
    string email = optional;

    enum Sex
    {
       Unknown,
       Male,
       Female
    };

    Sex sex = Unknown;

struct Person#1
{
    -- name;
    ++ string firstName;
    ++ string lastName;
}
*/

TEST_F(ParserStructureIdentificationTests, identification)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  identification\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 3, compil::Message::p_expectAppropriateType,
                                  compil::Message::Classifier("identification"),
                                  compil::Message::Options("runtime or inproc")));
}

TEST_F(ParserStructureIdentificationTests, runtimeIdentification_unclosed)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  runtime identification\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectSemicolon));
}

TEST_F(ParserStructureIdentificationTests, runtimeIdentification)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  runtime identification;\n"
        "}") );
    EXPECT_TRUE(checkIdentification(0, 0, 3, 3, compil::Identification::EType::runtime()));
}

TEST_F(ParserStructureIdentificationTests, inprocIdentification)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  inproc identification;\n"
        "}") );
    EXPECT_TRUE(checkIdentification(0, 0, 3, 3, compil::Identification::EType::inproc()));
}