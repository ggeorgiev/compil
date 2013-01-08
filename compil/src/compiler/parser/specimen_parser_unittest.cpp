#include "compiler/parser_unittest.h"

#include <iostream>

class ParserSpecimenTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("specimen")
                 << compil::Message::Classifier("class parameter");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
    
    bool checkSpecimen(int sIndex, int line, int column,
                     const char* name, const char* comment = NULL)
    {
        bool result = true;
        HF_ASSERT_LT(sIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        HF_ASSERT_EQ(compil::EObjectId::specimen(), pObject->runtimeObjectId());
        compil::SpecimenSPtr pSpecimen = 
            boost::static_pointer_cast<compil::Specimen>(pObject);
        HF_EXPECT_STREQ(name, pSpecimen->name()->value().c_str());
        HF_EXPECT_EQ(line + 1, pSpecimen->line().value());
        HF_EXPECT_EQ(column, pSpecimen->column().value());
        if (comment)
        {
            HF_ASSERT_TRUE(pSpecimen->comment());
            HF_EXPECT_EQ(1U, pSpecimen->comment()->lines().size());
            HF_EXPECT_STREQ(comment, pSpecimen->comment()->lines()[0].c_str());
        }
        else
        {
            HF_ASSERT_FALSE(pSpecimen->comment());
        }
        return result;
    }
    
    bool checkSpecimenParameterType(int sIndex, const char* parameterType)
    {
        bool result = true;
        EXPECT_LT(sIndex, (int)mDocument->objects().size());
        if (sIndex >= (int)mDocument->objects().size()) return false;
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::specimen(), pObject->runtimeObjectId());
        compil::SpecimenSPtr pSpecimen = 
            boost::static_pointer_cast<compil::Specimen>(pObject);
        
        compil::TypeSPtr pParameterType = pSpecimen->parameterType().lock();
        HF_ASSERT_TRUE(pParameterType);
        EXPECT_STREQ(parameterType, pParameterType->name()->value().c_str());
        return result;
    }
    
    bool checkConstant(int sIndex, int cIndex,
                       int line, int column, 
                       const char* name, const char* value)
    {
        HF_ASSERT_LT(sIndex, (int)mDocument->objects().size());

        compil::ObjectSPtr sobject = mDocument->objects()[sIndex];
        HF_ASSERT_EQ(compil::EObjectId::specimen(), sobject->runtimeObjectId());
        
        compil::SpecimenSPtr specimen =
            boost::static_pointer_cast<compil::Specimen>(sobject);
        HF_ASSERT_LT(cIndex, (int)specimen->constants().size());
        
        compil::ConstantSPtr constant = specimen->constants()[cIndex];
        HF_ASSERT_EQ(line + 1, constant->line().value());
        HF_ASSERT_EQ(column, constant->column().value());
        HF_ASSERT_STREQ(name, constant->name()->value().c_str());
        HF_ASSERT_STREQ(value, constant->value().c_str());
        
        return true;
    }
    
protected:
};

/*
 
specimen<string> SourceId
{
}

*/

TEST_F(ParserSpecimenTests, specimen)
{
    ASSERT_FALSE( parseDocument(
        "specimen") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 9, compil::Message::p_expectStatementName));
}

TEST_F(ParserSpecimenTests, specimenComment)
{
    ASSERT_FALSE( parseDocument(
        "specimen //") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 10, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 12, compil::Message::p_expectStatementName));
}

TEST_F(ParserSpecimenTests, specimenCommentBaseTypeOpen)
{
    ASSERT_FALSE( parseDocument(
        "specimen /* */ <") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 10, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 17, compil::Message::p_expectType));
}

TEST_F(ParserSpecimenTests, specimenCommentBaseTypeOpenType)
{
    ASSERT_FALSE( parseDocument(
        "specimen < /* */ integer") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 12, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 25, compil::Message::p_expectClosingAngleBracket));
}

TEST_F(ParserSpecimenTests, specimenCommentBaseType)
{
    ASSERT_FALSE( parseDocument(
        "specimen < integer /* */ >") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 20, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 27, compil::Message::p_expectStatementName));
}

TEST_F(ParserSpecimenTests, specimenCommentName)
{
    ASSERT_FALSE( parseDocument(
        "specimen /* */ name") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 10, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 20, compil::Message::p_expectStatementBody));
}

TEST_F(ParserSpecimenTests, specimenName)
{
    ASSERT_FALSE( parseDocument(
        "specimen name") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 14, compil::Message::p_expectStatementBody));
}

TEST_F(ParserSpecimenTests, specimenNameInherit)
{
    ASSERT_FALSE( parseDocument(
        "specimen name inherit") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 22, compil::Message::p_expectClassifierStatementName,
                                            compil::Message::Classifier("base")));
}

TEST_F(ParserSpecimenTests, specimenNameOpen)
{
    ASSERT_FALSE( parseDocument(
        "specimen name {") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 16, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserSpecimenTests, specimenNameCommentOpen)
{
    ASSERT_FALSE( parseDocument(
        "specimen name /* */ {") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 15, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 22, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserSpecimenTests, specimenNameOpenClose)
{
    ASSERT_TRUE( parseDocument(
        "specimen name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkSpecimen(0, 1, 1, "name"));
    EXPECT_TRUE(checkSpecimenParameterType(0, "integer"));
}

TEST_F(ParserSpecimenTests, specimenNameParameterTypeOpenClose)
{
    ASSERT_TRUE( parseDocument(
        "specimen<small> name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkSpecimen(0, 1, 1, "name"));
    EXPECT_TRUE(checkSpecimenParameterType(0, "small"));
}

TEST_F(ParserSpecimenTests, specimenNameMissingParameterTypeOpenClose)
{
    ASSERT_FALSE( parseDocument(
        "specimen<blah> name {}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 10, compil::Message::p_unknownClassifierType,
                  compil::Message::Type("blah")));
}

TEST_F(ParserSpecimenTests, 2specimensWithComments)
{
    ASSERT_TRUE( parseDocument(
        "//comment1\n"
        "specimen name1 {}\n"
        "//comment2\n"
        "specimen name2 {}") );

    EXPECT_EQ(2U, mDocument->objects().size());
    
    EXPECT_TRUE(checkSpecimen(0, 2, 1, "name1", "comment1"));
    EXPECT_TRUE(checkSpecimen(1, 4, 1, "name2", "comment2"));
    
    EXPECT_EQ(0U, mpParser->messages().size());
}

TEST_F(ParserSpecimenTests, specimenNameOpenConstant)
{
    ASSERT_FALSE( parseDocument(
        "specimen name\n"
        "{\n"
        "  constant") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 11, compil::Message::p_expectStatementName,
                                            compil::Message::Statement("constant")));
    EXPECT_TRUE(checkErrorMessage(1, 3, 11, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserSpecimenTests, specimenNameOpenBlah)
{
    ASSERT_FALSE( parseDocument(
        "specimen name\n"
        "{\n"
        "  blah") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 3, compil::Message::p_unknownStatment,
                                           compil::Message::Context("specimen item"),
                                           compil::Message::Options("constant")));
}

TEST_F(ParserSpecimenTests, constant)
{
    ASSERT_FALSE( parseDocument(
        "specimen name\n"
        "{\n"
        "  constant\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectStatementName,
                                           compil::Message::Statement("constant")));
}

TEST_F(ParserSpecimenTests, specimenConstantName)
{
    ASSERT_FALSE( parseDocument(
        "specimen sname\n"
        "{\n"
        "  constant cname\n"
        "}"));
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectAssignmentOperator));
}

TEST_F(ParserSpecimenTests, specimenConstantNameGarbage)
{
    ASSERT_FALSE( parseDocument(
        "specimen sname\n"
        "{\n"
        "  constant cname blah\n"
        "}"));
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 18, compil::Message::p_expectAssignmentOperator));
}

TEST_F(ParserSpecimenTests, specimenConstantNameEqual)
{
    ASSERT_FALSE( parseDocument(
        "specimen sname\n"
        "{\n"
        "  constant cname =\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectValue,
                                           compil::Message::Statement("constant")));
}


TEST_F(ParserSpecimenTests, specimenConstantNameEqualSemicolon)
{
    ASSERT_FALSE( parseDocument(
        "specimen sname\n"
        "{\n"
        "  constant cname =;\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 19, compil::Message::p_expectValue,
                                            compil::Message::Statement("constant")));
}

TEST_F(ParserSpecimenTests, specimenConstantCommentNoValue)
{
    ASSERT_FALSE( parseDocument(
        "specimen sname\n"
        "{\n"
        "  constant cname = /*comment*/;\n"
        "}") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 20, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 3, 31, compil::Message::p_expectValue,
                                            compil::Message::Statement("constant")));
}

TEST_F(ParserSpecimenTests, specimenConstant)
{
    ASSERT_TRUE( parseDocument(
        "specimen sname\n"
        "{\n"
        "  constant cname = 123;\n"
        "}") );

    EXPECT_TRUE(checkSpecimen(0, 1, 1, "sname"));
    EXPECT_TRUE(checkConstant(0, 0, 3, 3, "cname", "123"));
}
