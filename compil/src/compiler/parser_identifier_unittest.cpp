#include "parser_unittest.h"

#include <iostream>

class ParserIdentifierTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("identifier")
                 << compil::Message::Classifier("class parameter");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
    
    void checkIdentifier(int iIndex, int line, int column, 
                     const char* name, const char* comment = NULL)
    {
        ASSERT_LT(iIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[iIndex];
        ASSERT_EQ(compil::EObjectId::identifier(), pObject->runtimeObjectId());
        compil::IdentifierSPtr pIdentifier = 
            boost::static_pointer_cast<compil::Identifier>(pObject);
        EXPECT_STREQ(name, pIdentifier->name()->value().c_str());
        EXPECT_EQ(lang::compil::Line(line + 1), pIdentifier->line());
        EXPECT_EQ(lang::compil::Column(column), pIdentifier->column());
        if (comment)
        {
            ASSERT_TRUE(pIdentifier->comment());
            EXPECT_EQ(1U, pIdentifier->comment()->lines().size());
            EXPECT_STREQ(comment, pIdentifier->comment()->lines()[0].c_str());
        }
        else
        {
            ASSERT_FALSE(pIdentifier->comment());
        }
    }
    
    void checkIdentifierCast(int iIndex, const compil::CastableType::ECast& cast)
    {
        ASSERT_LT(iIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[iIndex];
        ASSERT_EQ(compil::EObjectId::identifier(), pObject->runtimeObjectId());
        compil::IdentifierSPtr pIdentifier = 
            boost::static_pointer_cast<compil::Identifier>(pObject);

        EXPECT_EQ(cast, pIdentifier->cast());
    }
    
    bool checkIdentifierBase(int iIndex, const char* baseType)
    {
        bool result = true;
        EXPECT_LT(iIndex, (int)mDocument->objects().size());
        if (iIndex >= (int)mDocument->objects().size()) return false;
        
        compil::ObjectSPtr pObject = mDocument->objects()[iIndex];
        EXPECT_EQ(compil::EObjectId::identifier(), pObject->runtimeObjectId());
        compil::IdentifierSPtr pIdentifier = 
            boost::static_pointer_cast<compil::Identifier>(pObject);
        
        compil::TypeSPtr pParameterType = pIdentifier->parameterType().lock();
        HF_ASSERT_TRUE(pParameterType);
        EXPECT_STREQ(baseType, pParameterType->name()->value().c_str());
        if (pParameterType->name()->value() != baseType) return false;
        return result;
    }
};

TEST_F(ParserIdentifierTests, identifier)
{
    ASSERT_FALSE( parseDocument(
        "identifier") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 11, compil::Message::p_expectStatementName));
}

TEST_F(ParserIdentifierTests, identifierComment)
{
    ASSERT_FALSE( parseDocument(
        "identifier //") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 12, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 14, compil::Message::p_expectStatementName));
}

TEST_F(ParserIdentifierTests, identifierCommentBaseTypeOpen)
{
    ASSERT_FALSE( parseDocument(
        "identifier /* */ <") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 12, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 19, compil::Message::p_expectType));
}

TEST_F(ParserIdentifierTests, identifierCommentBaseTypeOpenType)
{
    ASSERT_FALSE( parseDocument(
        "identifier < /* */ integer") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 14, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 27, compil::Message::p_expectClosingAngleBracket));
}

TEST_F(ParserIdentifierTests, identifierCommentBaseType)
{
    ASSERT_FALSE( parseDocument(
        "identifier < integer /* */ >") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 22, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 29, compil::Message::p_expectStatementName));
}

TEST_F(ParserIdentifierTests, identifierCommentName)
{
    ASSERT_FALSE( parseDocument(
        "identifier /* */ name") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 12, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 22, compil::Message::p_expectStatementBody));
}

TEST_F(ParserIdentifierTests, identifierName)
{
    ASSERT_FALSE( parseDocument(
        "identifier name") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 16, compil::Message::p_expectStatementBody));
}

TEST_F(ParserIdentifierTests, identifierNameOpen)
{
    ASSERT_FALSE( parseDocument(
        "identifier name {") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 18, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserIdentifierTests, identifierNameCommentOpen)
{
    ASSERT_FALSE( parseDocument(
        "identifier name /* */ {") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 17, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 24, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserIdentifierTests, identifierNameOpenClose)
{
    ASSERT_TRUE( parseDocument(
        "identifier name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkIdentifier(0, 1, 1, "name");
    checkIdentifierCast(0, compil::CastableType::ECast::weak());
    EXPECT_TRUE(checkIdentifierBase(0, "integer"));
}

TEST_F(ParserIdentifierTests, identifierNameBaseOpenClose)
{
    ASSERT_TRUE( parseDocument(
        "identifier<small> name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkIdentifier(0, 1, 1, "name");
    checkIdentifierCast(0, compil::CastableType::ECast::weak());
    EXPECT_TRUE(checkIdentifierBase(0, "small"));
}

TEST_F(ParserIdentifierTests, identifierNameWrongBaseOpenClose)
{
    ASSERT_FALSE( parseDocument(
        "identifier<real32> name {}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 1, compil::Message::v_unacceptableParameterType,
                compil::Message::Options("small, short, integer, long, byte, word, dword or qword")));
}

TEST_F(ParserIdentifierTests, identifierNameMissingBaseOpenClose)
{
    ASSERT_FALSE( parseDocument(
        "identifier<blah> name {}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 12, compil::Message::p_unknownClassifierType,
                  compil::Message::Type("blah")));
}

TEST_F(ParserIdentifierTests, weakIdentifierNameCommentOpenClose)
{
    ASSERT_TRUE( parseDocument(
        "weak identifier name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkIdentifier(0, 1, 1, "name");
    checkIdentifierCast(0, compil::CastableType::ECast::weak());
}

TEST_F(ParserIdentifierTests, strongIdentifierNameCommentOpenClose)
{
    ASSERT_TRUE( parseDocument(
        "strong identifier name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    checkIdentifier(0, 1, 1, "name");
    checkIdentifierCast(0, compil::CastableType::ECast::strong());
}

TEST_F(ParserIdentifierTests, 2identifiersWithComments)
{
    ASSERT_TRUE( parseDocument(
        "//comment1\n"
        "identifier name1 {}\n"
        "//comment2\n"
        "identifier name2 {}") );
    EXPECT_EQ(2U, mDocument->objects().size());
    
    checkIdentifier(0, 2, 1, "name1", "comment1");
    checkIdentifier(1, 4, 1, "name2", "comment2");
    
    EXPECT_EQ(0U, mpParser->messages().size());
}

