#include "parser_unittest.h"

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
    
    void checkSpecimen(int sIndex, int line, int column, 
                     const char* name, const char* comment = NULL)
    {
        ASSERT_LT(sIndex, (int)mpModel->objects().size());
        
        compil::ObjectSPtr pObject = mpModel->objects()[sIndex];
        ASSERT_EQ(compil::EObjectId::specimen(), pObject->runtimeObjectId());
        compil::SpecimenSPtr pSpecimen = 
            boost::static_pointer_cast<compil::Specimen>(pObject);
        EXPECT_STREQ(name, pSpecimen->name()->value().c_str());
        EXPECT_EQ(line + 1, pSpecimen->line());
        EXPECT_EQ(column, pSpecimen->column());
        if (comment)
        {
            ASSERT_TRUE(pSpecimen->comment());
            EXPECT_EQ(1U, pSpecimen->comment()->lines().size());
            EXPECT_STREQ(comment, pSpecimen->comment()->lines()[0].c_str());
        }
        else
        {
            ASSERT_FALSE(pSpecimen->comment());
        }
    }
    
    bool checkSpecimenParameterType(int sIndex, const char* parameterType)
    {
        bool result = true;
        EXPECT_LT(sIndex, (int)mpModel->objects().size());
        if (sIndex >= (int)mpModel->objects().size()) return false;
        
        compil::ObjectSPtr pObject = mpModel->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::specimen(), pObject->runtimeObjectId());
        compil::SpecimenSPtr pSpecimen = 
            boost::static_pointer_cast<compil::Specimen>(pObject);
        
        compil::TypeSPtr pParameterType = pSpecimen->parameterType().lock();
        HF_ASSERT_TRUE(pParameterType);
        EXPECT_STREQ(parameterType, pParameterType->name()->value().c_str());
        return result;
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
    ASSERT_FALSE( parse(
        "specimen") );

    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 9, compil::Message::p_expectStatementName));
}

TEST_F(ParserSpecimenTests, specimenComment)
{
    ASSERT_FALSE( parse(
        "specimen //") );
    
    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 10, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 12, compil::Message::p_expectStatementName));
}

TEST_F(ParserSpecimenTests, specimenCommentBaseTypeOpen)
{
    ASSERT_FALSE( parse(
        "specimen /* */ <") );
    
    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 10, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 17, compil::Message::p_expectType));
}

TEST_F(ParserSpecimenTests, specimenCommentBaseTypeOpenType)
{
    ASSERT_FALSE( parse(
        "specimen < /* */ integer") );
    
    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 12, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 25, compil::Message::p_expectClosingAngleBracket));
}

TEST_F(ParserSpecimenTests, specimenCommentBaseType)
{
    ASSERT_FALSE( parse(
        "specimen < integer /* */ >") );
    
    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 20, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 27, compil::Message::p_expectStatementName));
}

TEST_F(ParserSpecimenTests, specimenCommentName)
{
    ASSERT_FALSE( parse(
        "specimen /* */ name") );
    
    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 10, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 20, compil::Message::p_expectStatementBody));
}

TEST_F(ParserSpecimenTests, specimenName)
{
    ASSERT_FALSE( parse(
        "specimen name") );
    
    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 14, compil::Message::p_expectStatementBody));
}

TEST_F(ParserSpecimenTests, specimenNameInherit)
{
    ASSERT_FALSE( parse(
        "specimen name inherit") );
    
    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 22, compil::Message::p_expectClassifierStatementName,
                                            compil::Message::Classifier("base")));
}

TEST_F(ParserSpecimenTests, specimenNameOpen)
{
    ASSERT_FALSE( parse(
        "specimen name {") );
    
    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 16, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserSpecimenTests, specimenNameCommentOpen)
{
    ASSERT_FALSE( parse(
        "specimen name /* */ {") );
    
    ASSERT_EQ(2U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 15, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 22, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserSpecimenTests, specimenNameOpenClose)
{
    ASSERT_TRUE( parse(
        "specimen name {}") );
    
    EXPECT_EQ(1U, mpModel->objects().size());
    checkSpecimen(0, 1, 1, "name");
    EXPECT_TRUE(checkSpecimenParameterType(0, "integer"));
}

TEST_F(ParserSpecimenTests, specimenNameParameterTypeOpenClose)
{
    ASSERT_TRUE( parse(
        "specimen<small> name {}") );
    
    EXPECT_EQ(1U, mpModel->objects().size());
    checkSpecimen(0, 1, 1, "name");
    EXPECT_TRUE(checkSpecimenParameterType(0, "small"));
}

TEST_F(ParserSpecimenTests, specimenNameMissingParameterTypeOpenClose)
{
    ASSERT_FALSE( parse(
        "specimen<blah> name {}") );
    
    ASSERT_EQ(1U, mpParser->mpMessageCollector->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 10, compil::Message::p_unknownClassifierType,
                  compil::Message::Type("blah")));
}

TEST_F(ParserSpecimenTests, 2specimensWithComments)
{
    ASSERT_TRUE( parse(
        "//comment1\n"
        "specimen name1 {}\n"
        "//comment2\n"
        "specimen name2 {}") );

    EXPECT_EQ(2U, mpModel->objects().size());
    
    checkSpecimen(0, 2, 1, "name1", "comment1");
    checkSpecimen(1, 4, 1, "name2", "comment2");
    
    EXPECT_EQ(0U, mpParser->mpMessageCollector->messages().size());
}