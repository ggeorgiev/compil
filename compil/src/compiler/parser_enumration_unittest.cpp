#include "parser_unittest.h"

#include <iostream>

class ParserEnumerationTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("enumeration")
                 << compil::Message::Classifier("class parameter");
        return BaseParserTests::checkMessage(expected, mIndex);
    }

    void checkEnumeration(int eIndex, int line, int column, 
                     const char* name, const char* comment = NULL)
    {
        ASSERT_LT(eIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[eIndex];
        ASSERT_EQ(compil::EObjectId::enumeration(), pObject->runtimeObjectId());
        compil::EnumerationSPtr pEnumeration = 
            boost::static_pointer_cast<compil::Enumeration>(pObject);
        EXPECT_STREQ(name, pEnumeration->name()->value().c_str());
        EXPECT_EQ(lang::compil::Line(line + 1), pEnumeration->line());
        EXPECT_EQ(lang::compil::Column(column), pEnumeration->column());
        if (comment)
        {
            ASSERT_TRUE(pEnumeration->comment());
            EXPECT_EQ(1U, pEnumeration->comment()->lines().size());
            EXPECT_STREQ(comment, pEnumeration->comment()->lines()[0].c_str());
        }
        else
        {
            ASSERT_FALSE(pEnumeration->comment());
        }
    }
    
    void checkEnumerationCast(int eIndex, const compil::CastableType::ECast& cast)
    {
        ASSERT_LT(eIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[eIndex];
        ASSERT_EQ(compil::EObjectId::enumeration(), pObject->runtimeObjectId());
        compil::EnumerationSPtr pEnumerationt = 
            boost::static_pointer_cast<compil::Enumeration>(pObject);

        EXPECT_EQ(cast, pEnumerationt->cast());
    }
    
    void checkEnumerationFlags(int eIndex, bool flags)
    {
        ASSERT_LT(eIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[eIndex];
        ASSERT_EQ(compil::EObjectId::enumeration(), pObject->runtimeObjectId());
        compil::EnumerationSPtr pEnumerationt = 
            boost::static_pointer_cast<compil::Enumeration>(pObject);

        EXPECT_EQ(flags, pEnumerationt->flags());
    }
    
    bool checkEnumerationParameterType(int eIndex, const char* baseType)
    {
        bool result = true;
        EXPECT_LT(eIndex, (int)mDocument->objects().size());
        if (eIndex >= (int)mDocument->objects().size()) return false;
        
        compil::ObjectSPtr pObject = mDocument->objects()[eIndex];
        EXPECT_EQ(compil::EObjectId::enumeration(), pObject->runtimeObjectId());
        compil::EnumerationSPtr pEnumerationt = 
        boost::static_pointer_cast<compil::Enumeration>(pObject);
        
        compil::TypeSPtr pParameterType = pEnumerationt->parameterType().lock();
        HF_ASSERT_TRUE(pParameterType);
        EXPECT_STREQ(baseType, pParameterType->name()->value().c_str());
        return result;
    }
    
    bool checkEnumerationValue(int eIndex, int vIndex, 
                    int line, int column, 
                    const char* name, 
                    const char* comment = NULL)
    {
        bool result = true;
        HF_ASSERT_LT(eIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[eIndex];
        HF_ASSERT_EQ(compil::EObjectId::enumeration(), pObject->runtimeObjectId());
        compil::EnumerationSPtr pEnumeration = 
            boost::static_pointer_cast<compil::Enumeration>(pObject);
        
        HF_ASSERT_LT(vIndex, (int)pEnumeration->enumerationValues().size());
        compil::ObjectSPtr pVObject = pEnumeration->enumerationValues()[vIndex];
        compil::EnumerationValueSPtr pEnumerationValue = 
            boost::static_pointer_cast<compil::EnumerationValue>(pVObject);
        HF_EXPECT_EQ(lang::compil::Line(line + 1), pEnumerationValue->line());
        HF_EXPECT_EQ(lang::compil::Column(column), pEnumerationValue->column());
        HF_EXPECT_STREQ(name, pEnumerationValue->name()->value().c_str());
        if (comment)
        {
            HF_ASSERT_TRUE(pEnumerationValue->comment());
            HF_EXPECT_EQ(1U, pEnumerationValue->comment()->lines().size());
            HF_EXPECT_STREQ(comment, pEnumerationValue->comment()->lines()[0].c_str());
        }
        else
        {
            HF_ASSERT_FALSE(pEnumerationValue->comment());
        }
        return result;
    }
    
protected:
};

/*
 
enum Weekday
{
    sunday;
    monday;
    tuesday;
    wednesday;
    thursday;
    friday;
    saturday;
}

*/

TEST_F(ParserEnumerationTests, enum)
{
    ASSERT_FALSE( parse(
        "enum") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 5, compil::Message::p_expectStatementName));
}

TEST_F(ParserEnumerationTests, enumComment)
{
    ASSERT_FALSE( parse(
        "enum //") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 6, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 8, compil::Message::p_expectStatementName));
}

TEST_F(ParserEnumerationTests, enumCommentParameterTypeOpen)
{
    ASSERT_FALSE( parse(
        "enum /* */ <") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 6, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 13, compil::Message::p_expectType));
}

TEST_F(ParserEnumerationTests, enumCommentParameterTypeOpenType)
{
    ASSERT_FALSE( parse(
        "enum < /* */ integer") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 8, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 21, compil::Message::p_expectClosingAngleBracket));
}

TEST_F(ParserEnumerationTests, enumCommentParameterType)
{
    ASSERT_FALSE( parse(
        "enum < integer /* */ >") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 16, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 23, compil::Message::p_expectStatementName));
}

TEST_F(ParserEnumerationTests, enumCommentName)
{
    ASSERT_FALSE( parse(
        "enum /* */ name") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 6, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 16, compil::Message::p_expectStatementBody));
}

TEST_F(ParserEnumerationTests, enumName)
{
    ASSERT_FALSE( parse(
        "enum name") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 10, compil::Message::p_expectStatementBody));
}

TEST_F(ParserEnumerationTests, enumNameOpen)
{
    ASSERT_FALSE( parse(
        "enum name {") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 12, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserEnumerationTests, enumNameCommentOpen)
{
    ASSERT_FALSE( parse(
        "enum name /* */ {") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 11, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 18, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserEnumerationTests, enumNameOpenClose)
{
    ASSERT_TRUE( parse(
        "enum name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkEnumeration(0, 1, 1, "name");
    checkEnumerationCast(0, compil::CastableType::ECast::weak());
    checkEnumerationFlags(0, false);
    EXPECT_TRUE(checkEnumerationParameterType(0, "integer"));
}

TEST_F(ParserEnumerationTests, enumNameParameterTypeOpenClose)
{
    ASSERT_TRUE( parse(
        "enum<small> name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkEnumeration(0, 1, 1, "name");
    checkEnumerationCast(0, compil::CastableType::ECast::weak());
    checkEnumerationFlags(0, false);
    EXPECT_TRUE(checkEnumerationParameterType(0, "small"));
}

TEST_F(ParserEnumerationTests, enumNameWrongParameterTypeOpenClose)
{
    ASSERT_FALSE( parse(
        "enum<real32> name {}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 1, compil::Message::v_unacceptableParameterType,
                compil::Message::Options("small, short or integer")));
}

TEST_F(ParserEnumerationTests, enumNameMissingParameterTypeOpenClose)
{
    ASSERT_FALSE( parse(
        "enum<blah> name {}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 6, compil::Message::p_unknownClassifierType,
                  compil::Message::Type("blah")));
}

TEST_F(ParserEnumerationTests, weakEnumNameCommentOpenClose)
{
    ASSERT_TRUE( parse(
        "weak enum name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkEnumeration(0, 1, 1, "name");
    checkEnumerationFlags(0, false);
    checkEnumerationCast(0, compil::CastableType::ECast::weak());
}

TEST_F(ParserEnumerationTests, strongEnumNameCommentOpenClose)
{
    ASSERT_TRUE( parse(
        "strong enum name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkEnumeration(0, 1, 1, "name");
    checkEnumerationFlags(0, false);
    checkEnumerationCast(0, compil::CastableType::ECast::strong());
}

TEST_F(ParserEnumerationTests, flagsEnumNameCommentOpenClose)
{
    ASSERT_TRUE( parse(
        "flags enum name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkEnumeration(0, 1, 1, "name");
    checkEnumerationFlags(0, true);
    checkEnumerationCast(0, compil::CastableType::ECast::weak());
}

TEST_F(ParserEnumerationTests, 2enumsWithComments)
{
    ASSERT_TRUE( parse(
        "//comment1\n"
        "enum name1 {}\n"
        "//comment2\n"
        "enum name2 {}") );

    EXPECT_EQ(2U, mDocument->objects().size());
    
    checkEnumeration(0, 2, 1, "name1", "comment1");
    checkEnumeration(1, 4, 1, "name2", "comment2");
    
    EXPECT_EQ(0U, mpParser->messages().size());
}

TEST_F(ParserEnumerationTests, enumValue)
{
    ASSERT_FALSE( parse(
        "enum name\n"
        "{\n"
        "  value\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectSemicolon));
}

TEST_F(ParserEnumerationTests, enumValueSomething)
{
    ASSERT_FALSE( parse(
        "enum name\n"
        "{\n"
        "  value blah\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 9, compil::Message::p_expectSemicolon));
}

TEST_F(ParserEnumerationTests, enumValueEqual)
{
    ASSERT_FALSE( parse(
        "enum ename\n"
        "{\n"
        "  value =\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserEnumerationTests, enumValueEqualValue)
{
    ASSERT_FALSE( parse(
        "enum ename\n"
        "{\n"
        "  value = blah\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 11, compil::Message::p_expectStatementName,
                                  compil::Message::Statement("enumeration value")));
}

TEST_F(ParserEnumerationTests, enumValue1EqualValue2EqualValue1)
{
    ASSERT_FALSE( parse(
        "enum ename\n"
        "{\n"
        "  value1;\n"
        "  value2 = value1\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 1, compil::Message::p_expectSemicolon));
}

TEST_F(ParserEnumerationTests, enumValue1EqualValue2EqualValue1Or)
{
    ASSERT_FALSE( parse(
        "enum ename\n"
        "{\n"
        "  value1;\n"
        "  value2 = value1 |\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 5, 1, compil::Message::p_unexpectEOFInStatementBody));
}


TEST_F(ParserEnumerationTests, enumValue1EqualValue2EqualValue1OrSemicolon)
{
    ASSERT_FALSE( parse(
        "enum ename\n"
        "{\n"
        "  value1;\n"
        "  value2 = value1 |;\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 20, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserEnumerationTests, enum1Value)
{
    ASSERT_TRUE( parse(
        "enum name\n"
        "{\n"
        "  value;\n"
        "}") );

    checkEnumeration(0, 1, 1, "name");
    EXPECT_TRUE(checkEnumerationValue(0, 0, 3, 3, "value"));
}

TEST_F(ParserEnumerationTests, enum2Value)
{
    ASSERT_TRUE( parse(
        "enum name\n"
        "{\n"
        "  value1;\n"
        "  value2;\n"
        "}") );

    checkEnumeration(0, 1, 1, "name");
    EXPECT_TRUE(checkEnumerationValue(0, 0, 3, 3, "value1"));
    EXPECT_TRUE(checkEnumerationValue(0, 1, 4, 3, "value2"));
}

TEST_F(ParserEnumerationTests, enumComposedValue)
{
    ASSERT_TRUE( parse(
        "enum name\n"
        "{\n"
        "  value1;\n"
        "  value2;\n"
        "  value3 = value1 | value2;\n"
        "}") );

    checkEnumeration(0, 1, 1, "name");
    EXPECT_TRUE(checkEnumerationValue(0, 0, 3, 3, "value1"));
    EXPECT_TRUE(checkEnumerationValue(0, 1, 4, 3, "value2"));
    EXPECT_TRUE(checkEnumerationValue(0, 2, 5, 3, "value3"));
}


TEST_F(ParserEnumerationTests, enum2ValueWithComment)
{
    ASSERT_TRUE( parse(
        "enum name\n"
        "{\n"
        "  // comment\n"
        "  value;\n"
        "}") );

    checkEnumeration(0, 1, 1, "name");
    EXPECT_TRUE(checkEnumerationValue(0, 0, 4, 3, "value", "comment"));
}

