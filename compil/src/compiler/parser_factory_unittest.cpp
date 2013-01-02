#include "parser_unittest.h"

#include <iostream>

class ParserFactoryTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("factory")
                 << compil::Message::Classifier("class parameter");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
    
    bool checkFactory(int fIndex, int line, int column, 
                      const char* name, compil::Factory::EType type, const char* comment = NULL)
    {
        bool result = true;
    
        EXPECT_LT(fIndex, (int)mDocument->objects().size());
        if (fIndex >= (int)mDocument->objects().size()) return false;
        
        compil::ObjectSPtr pObject = mDocument->objects()[fIndex];
        EXPECT_EQ(compil::EObjectId::factory(), pObject->runtimeObjectId());
        if (compil::EObjectId::factory() != pObject->runtimeObjectId()) return false;
        
        compil::FactorySPtr pFactory = 
            boost::static_pointer_cast<compil::Factory>(pObject);
        HF_EXPECT_STREQ(name, pFactory->name()->value().c_str());
        HF_EXPECT_EQ(type, pFactory->type());
        HF_EXPECT_EQ(lang::compil::Line(line + 1), pFactory->line());
        HF_EXPECT_EQ(lang::compil::Column(column), pFactory->column());
        if (comment)
        {
            EXPECT_TRUE(pFactory->comment());
            if (!pFactory->comment()) return false;
            EXPECT_EQ(1U, pFactory->comment()->lines().size());
            EXPECT_STREQ(comment, pFactory->comment()->lines()[0].c_str());
        }
        else
        {
            EXPECT_FALSE(pFactory->comment());
            if (pFactory->comment()) return false;
        }
        
        return result;
    }
    
    bool checkFactoryParameterType(int fIndex, const char* parameterType)
    {
        bool result = true;
        EXPECT_LT(fIndex, (int)mDocument->objects().size());
        if (fIndex >= (int)mDocument->objects().size()) return false;
        
        compil::ObjectSPtr pObject = mDocument->objects()[fIndex];
        EXPECT_EQ(compil::EObjectId::factory(), pObject->runtimeObjectId());
        compil::FactorySPtr pFactory = 
            boost::static_pointer_cast<compil::Factory>(pObject);
        
        compil::TypeSPtr pParameterType = pFactory->parameterType().lock();
        HF_ASSERT_TRUE(pParameterType);
        EXPECT_STREQ(parameterType, pParameterType->name()->value().c_str());
        return result;
    }
        
    bool checkFilter(int fIndex, int fiIndex, int line, int column,
                     const char* fieldName, const char* method)
    {
        bool result = true;
        
        HF_ASSERT_LT(fIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[fIndex];
        compil::FactorySPtr pFactory = compil::ObjectFactory::downcastFactory(pObject);
        HF_ASSERT_TRUE(pFactory);
        
        const std::vector<compil::FilterSPtr>& filters = pFactory->filters();
        HF_ASSERT_LT(fiIndex, (int)filters.size());
        
        compil::FilterSPtr pFilter = filters[fiIndex];
        HF_EXPECT_EQ(lang::compil::Line(line + 1), pFilter->line());
        HF_EXPECT_EQ(lang::compil::Column(column), pFilter->column());
        HF_EXPECT_STREQ(fieldName, pFilter->field()->name()->value().c_str());
        HF_EXPECT_STREQ(method, pFilter->method().c_str());
        return result;
    }
    
protected:
};

/*
 
hierarchy factory<Object> ObjectFactory
{
}

object factory<Object> ObjectFactory
{
}

*/

TEST_F(ParserFactoryTests, noTypeFactory)
{
    ASSERT_FALSE( parse(
        "factory") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 8, compil::Message::p_expectAppropriateType, 
                                  compil::Message::Classifier("factory"),
                                  compil::Message::Options("hierarchy, object or plugin")));
}

TEST_F(ParserFactoryTests, factory)
{
    ASSERT_FALSE( parse(
        "hierarchy factory") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 18, compil::Message::p_expectType));
}

TEST_F(ParserFactoryTests, factoryComment)
{
    ASSERT_FALSE( parse(
        "hierarchy factory //") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 19, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 21, compil::Message::p_expectType));
}

TEST_F(ParserFactoryTests, factoryCommentBaseTypeOpen)
{
    ASSERT_FALSE( parse(
        "hierarchy factory /* */ <") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 19, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 26, compil::Message::p_expectType));
}

TEST_F(ParserFactoryTests, factoryCommentBaseTypeOpenType)
{
    ASSERT_FALSE( parse(
        "hierarchy factory < /* */ integer") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 21, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 34, compil::Message::p_expectClosingAngleBracket));
}

TEST_F(ParserFactoryTests, factoryCommentBaseType)
{
    ASSERT_FALSE( parse(
        "hierarchy factory < integer /* */ >") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 29, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 36, compil::Message::p_expectStatementName));
}

TEST_F(ParserFactoryTests, factoryName)
{
    ASSERT_FALSE( parse(
        "hierarchy factory name") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 19, compil::Message::p_expectType));
}

TEST_F(ParserFactoryTests, factoryTypeCommentName)
{
    ASSERT_FALSE( parse(
        "hierarchy factory<integer> /* */ name") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 28, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 38, compil::Message::p_expectStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeName)
{
    ASSERT_FALSE( parse(
        "hierarchy factory<integer> name") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 32, compil::Message::p_expectStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameOpen)
{
    ASSERT_FALSE( parse(
        "hierarchy factory<integer> name {") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 34, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpen)
{
    ASSERT_FALSE( parse(
        "hierarchy factory<integer> name /* */ {") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 33, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 40, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, hierarchyFactoryTypeNameCommentOpenFilter)
{
    ASSERT_FALSE( parse(
        "hierarchy factory<integer> name { filter") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 35, compil::Message::p_filterInNonObjectFactory));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterWithNoStructureType)
{
    ASSERT_FALSE( parse(
        "object factory<integer> name { filter") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 32, compil::Message::p_filterInFactoryForNonStructure));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterWithUnknownField)
{
    ASSERT_FALSE( parse(
        "structure sname { integer i; }\n"
        "object factory<sname> name { filter unknown") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 2, 37, compil::Message::p_expectStatementName, 
                    compil::Message::Statement("field")));
    EXPECT_TRUE(checkErrorMessage(1, 2, 44, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterField)
{
    ASSERT_FALSE( parse(
        "structure sname { integer i; }\n"
        "object factory<sname> name { filter i") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 2, 38, compil::Message::p_expectKeyword,
                    compil::Message::Keyword("with")));
    EXPECT_TRUE(checkErrorMessage(1, 2, 38, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterFieldBlah)
{
    ASSERT_FALSE( parse(
        "structure sname { integer i; }\n"
        "object factory<sname> name { filter i blah") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 2, 39, compil::Message::p_expectKeyword,
                    compil::Message::Keyword("with")));
    EXPECT_TRUE(checkErrorMessage(1, 2, 43, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterFieldWith)
{
    ASSERT_FALSE( parse(
        "structure sname { integer i; }\n"
        "object factory<sname> name { filter i with") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 2, 43, compil::Message::p_expectStatementName, 
                    compil::Message::Statement("external method")));
    EXPECT_TRUE(checkErrorMessage(1, 2, 43, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterFieldWithMethod)
{
    ASSERT_FALSE( parse(
        "structure sname { integer i; }\n"
        "object factory<sname> name { filter i with blah") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 2, 48, compil::Message::p_expectSemicolon));
    EXPECT_TRUE(checkErrorMessage(1, 2, 48, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterFieldWithMethodSemicolon)
{
    ASSERT_FALSE( parse(
        "structure sname { integer i; }\n"
        "object factory<sname> name { filter i with blah;") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 2, 49, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserFactoryTests, factoryTypeNameCommentOpenFilterFieldWithMethodSemicolonClose)
{
    ASSERT_TRUE( parse(
        "structure sname { integer i; }\n"
        "object factory<sname> name { filter i with blah; }") );
    
    EXPECT_EQ(2U, mDocument->objects().size());
    EXPECT_TRUE(checkFactory(1, 2, 1, "name", compil::Factory::EType::object()));
    EXPECT_TRUE(checkFactoryParameterType(1, "sname"));
    EXPECT_TRUE(checkFilter(1, 0, 2, 30, "i", "blah"));
}

TEST_F(ParserFactoryTests, factory2Filters)
{
    ASSERT_TRUE( parse(
        "structure sname { integer i1;  integer i2; }\n"
        "object factory<sname> name { filter i1 with blah1; filter i2 with blah2; }") );
    
    EXPECT_EQ(2U, mDocument->objects().size());
    EXPECT_TRUE(checkFactory(1, 2, 1, "name", compil::Factory::EType::object()));
    EXPECT_TRUE(checkFactoryParameterType(1, "sname"));
    EXPECT_TRUE(checkFilter(1, 0, 2, 30, "i1", "blah1"));
    EXPECT_TRUE(checkFilter(1, 1, 2, 52, "i2", "blah2"));
}

TEST_F(ParserFactoryTests, hierarchyFactoryTypeNameOpenClose)
{
    ASSERT_TRUE( parse(
        "hierarchy factory<integer> name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkFactory(0, 1, 1, "name", compil::Factory::EType::hierarchy()));
    EXPECT_TRUE(checkFactoryParameterType(0, "integer"));
}

TEST_F(ParserFactoryTests, objectFactoryTypeNameOpenClose)
{
    ASSERT_TRUE( parse(
        "object factory<integer> name {}") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkFactory(0, 1, 1, "name", compil::Factory::EType::object()));
    EXPECT_TRUE(checkFactoryParameterType(0, "integer"));
}

TEST_F(ParserFactoryTests, factoryMissingParameterTypeNameOpenClose)
{
    ASSERT_FALSE( parse(
        "hierarchy factory<blah> name {}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 19, compil::Message::p_unknownClassifierType,
                  compil::Message::Type("blah")));
}

TEST_F(ParserFactoryTests, 2factoiesWithComments)
{
    ASSERT_TRUE( parse(
        "//comment1\n"
        "hierarchy factory<integer> name1 {}\n"
        "//comment2\n"
        "object factory<integer> name2 {}") );

    EXPECT_EQ(2U, mDocument->objects().size());
    
    EXPECT_TRUE(checkFactory(0, 2, 1, "name1", compil::Factory::EType::hierarchy(), "comment1"));
    EXPECT_TRUE(checkFactory(1, 4, 1, "name2", compil::Factory::EType::object(), "comment2"));
    
    EXPECT_EQ(0U, mpParser->messages().size());
}
