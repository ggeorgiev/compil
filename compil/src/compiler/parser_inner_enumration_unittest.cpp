#include "parser_unittest.h"

#include <iostream>

class ParserInnerEnumerationTests : public BaseParserTests 
{
public:
    bool checkEnumeration(int eIndex, int line, int column, 
                     const char* name, const char* comment = NULL)
    {
        bool result = true;
    
        HF_ASSERT_LT(0, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pSObject = mDocument->objects()[0];
        HF_EXPECT_EQ(compil::EObjectId::structure(), pSObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pSObject);
            
        HF_ASSERT_LT(eIndex, (int)pStructure->objects().size());
        compil::ObjectSPtr pEObject = pStructure->objects()[eIndex];
        HF_EXPECT_EQ(compil::EObjectId::enumeration(), pEObject->runtimeObjectId());
        compil::EnumerationSPtr pEnumeration = 
            boost::static_pointer_cast<compil::Enumeration>(pEObject);
            
        EXPECT_STREQ(name, pEnumeration->name()->value().c_str());
        HF_EXPECT_EQ(line + 1, pEnumeration->line());
        HF_EXPECT_EQ(column, pEnumeration->column());
        if (comment)
        {
            EXPECT_TRUE(pEnumeration->comment());
            EXPECT_EQ(1U, pEnumeration->comment()->lines().size());
            EXPECT_STREQ(comment, pEnumeration->comment()->lines()[0].c_str());
        }
        else
        {
            EXPECT_FALSE(pEnumeration->comment());
        }

        return result;
    }
    
protected:
};

TEST_F(ParserInnerEnumerationTests, enum)
{
    ASSERT_TRUE( parse(
        "structure sname { enum ename {} }") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkEnumeration(0, 1, 19, "ename"));
}

TEST_F(ParserInnerEnumerationTests, strongEnum)
{
    ASSERT_TRUE( parse(
        "structure sname { strong enum ename {} }") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkEnumeration(0, 1, 19, "ename"));
}

TEST_F(ParserInnerEnumerationTests, weakEnum)
{
    ASSERT_TRUE( parse(
        "structure sname { weak enum ename {} }") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkEnumeration(0, 1, 19, "ename"));
}

TEST_F(ParserInnerEnumerationTests, 2Enums)
{
    ASSERT_TRUE( parse(
        "structure sname { enum ename1 {} enum ename2 {} }") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkEnumeration(0, 1, 19, "ename1"));
    EXPECT_TRUE(checkEnumeration(1, 1, 34, "ename2"));
}


TEST_F(ParserInnerEnumerationTests, 2EnumsWithComments)
{
    ASSERT_TRUE( parse(
        "structure sname { /*comment 1*/ enum ename1 {} /*comment 2*/ enum ename2 {} }") );
    
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkEnumeration(0, 1, 33, "ename1", "comment 1"));
    EXPECT_TRUE(checkEnumeration(1, 1, 62, "ename2", "comment 2"));
}

