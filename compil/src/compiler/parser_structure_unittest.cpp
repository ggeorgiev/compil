#include "parser_unittest.h"

class ParserStructureTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("structure")
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
    
    bool checkStructureAbstract(int sIndex, bool abstract)
    {
        bool result = true;
        
        EXPECT_LT(sIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        HF_EXPECT_EQ(abstract, pStructure->abstract());
        
        return result;
    }
    
    bool checkStructureControlled(int sIndex, bool controlled)
    {
        bool result = true;
        
        EXPECT_LT(sIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        HF_EXPECT_EQ(controlled, pStructure->controlled());
        
        return result;
    }
    
    bool checkStructureImmutable(int sIndex, bool immutable)
    {
        bool result = true;
        
        EXPECT_LT(sIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        HF_EXPECT_EQ(immutable, pStructure->immutable());
        
        return result;
    }
    
    bool checkStructurePartial(int sIndex, bool partial)
    {
        bool result = true;
        
        EXPECT_LT(sIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        HF_EXPECT_EQ(partial, pStructure->partial());
        
        return result;
    }
    
    bool checkStructureSharable(int sIndex, bool sharable)
    {
        bool result = true;
        
        EXPECT_LT(sIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        HF_EXPECT_EQ(sharable, pStructure->sharable());
        
        return result;
    }
    
    bool checkStructureStreamable(int sIndex, bool streamable)
    {
        bool result = true;
        
        EXPECT_LT(sIndex, (int)mDocument->objects().size());
        
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        EXPECT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        HF_EXPECT_EQ(streamable, pStructure->streamable());
        
        return result;
    }

protected:
};

/*
struct Person inherit Contactee
{
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

TEST_F(ParserStructureTests, structure)
{
    ASSERT_FALSE( parseDocument(
        "structure") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 10, compil::Message::p_expectStatementName));
}

TEST_F(ParserStructureTests, structureComment)
{
    ASSERT_FALSE( parseDocument(
        "structure //") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 11, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 13, compil::Message::p_expectStatementName));
}

TEST_F(ParserStructureTests, structureCommentName)
{
    ASSERT_FALSE( parseDocument(
        "structure /* */ name") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 11, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 21, compil::Message::p_expectStatementBody));
}

TEST_F(ParserStructureTests, structureName)
{
    ASSERT_FALSE( parseDocument(
        "structure name") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 15, compil::Message::p_expectStatementBody));
}

TEST_F(ParserStructureTests, structureNameComment)
{
    ASSERT_FALSE( parseDocument(
        "structure name /* */") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 16, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 21, compil::Message::p_expectStatementBody));
}

TEST_F(ParserStructureTests, structureNameInherit)
{
    ASSERT_FALSE( parseDocument(
        "structure name inherit") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 23, compil::Message::p_expectClassifierStatementName));
}

TEST_F(ParserStructureTests, structureNameInheritComment)
{
    ASSERT_FALSE( parseDocument(
        "structure name inherit /* */") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 24, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 29, compil::Message::p_expectClassifierStatementName));
}

TEST_F(ParserStructureTests, structureNameInheritName)
{
    ASSERT_FALSE( parseDocument(
        "structure name inherit name") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 24, compil::Message::p_unknownClassifierType));
}

TEST_F(ParserStructureTests, structureNameInheritInt32)
{
    ASSERT_FALSE( parseDocument(
        "structure name inherit integer") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 24, compil::Message::p_expectAppropriateType));
}

TEST_F(ParserStructureTests, structureNameNameAlter)
{
    ASSERT_FALSE( parseDocument(
        "structure base{} structure name inherit base alter") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 51, compil::Message::p_expectStatementName, 
                                  compil::Message::Statement("field")));
}

TEST_F(ParserStructureTests, structureNameNameAlterField)
{
    ASSERT_FALSE( parseDocument(
        "structure base {integer a;} structure name inherit base alter a") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 64, compil::Message::p_expectAssignmentOperator));
}

TEST_F(ParserStructureTests, structureNameNameAlterWrongField)
{
    ASSERT_FALSE( parseDocument(
        "structure base {integer a;} structure name inherit base alter b") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 63, compil::Message::p_expectBaseStructureFieldName));
}


TEST_F(ParserStructureTests, structureNameNameAlterFieldAssigment)
{
    ASSERT_FALSE( parseDocument(
        "structure base {integer a;} structure name inherit base alter a=") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 65, compil::Message::p_expectValue,
                                            compil::Message::Statement("field")));
}

TEST_F(ParserStructureTests, structureNameNameAlterFieldAssigmentValue)
{
    ASSERT_FALSE( parseDocument(
        "structure base {integer a;} structure name inherit base alter a=5") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 66, compil::Message::p_expectStatementBody));
}

TEST_F(ParserStructureTests, structureNameNameAlterFieldAssigmentValueDelimiter)
{
    ASSERT_FALSE( parseDocument(
        "structure base {integer a;} structure name inherit base alter a=5,") );

    ASSERT_LE(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 67, compil::Message::p_expectStatementName, 
                                  compil::Message::Statement("field")));}

TEST_F(ParserStructureTests, structureNameOpen)
{
    ASSERT_FALSE( parseDocument(
        "structure name {") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 17, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserStructureTests, structureNameCommentOpen)
{
    ASSERT_FALSE( parseDocument(
        "structure name /* */ {") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 1, 16, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 1, 23, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserStructureTests, structureNameCommentOpenClose)
{
    ASSERT_TRUE( parseDocument(
        "structure name {}") );
        
    EXPECT_EQ(1U, mDocument->objects().size());
    EXPECT_TRUE(checkStructure(0, 1, 1, "name"));
    EXPECT_TRUE(checkStructureControlled(0, false));
    EXPECT_TRUE(checkStructureImmutable(0, false));
    EXPECT_TRUE(checkStructurePartial(0, false));
    EXPECT_TRUE(checkStructureSharable(0, false));
    EXPECT_TRUE(checkStructureAbstract(0, false));
}

TEST_F(ParserStructureTests, structureAttributes)
{
    for (int a = 0; a < 2; ++a)
    {
        std::string aattributes;
        if (a)
            aattributes += "abstract ";
        for (int c = 0; c < 2; ++c)
        {
            std::string cattributes = aattributes;
            if (c)
                cattributes += "controlled ";
                
            for (int m = 0; m < 2; ++m)
            {
                std::string mattributes = cattributes;
                if (m)
                    mattributes += "immutable ";
            
                for (int p = 0; p < 2; ++p)
                {
                    std::string pattributes = mattributes;
                    if (p)
                        pattributes += "partial ";
                        
                    for (int sh = 0; sh < 2; ++sh)
                    {
                        std::string shattributes = pattributes;
                        if (sh)
                            shattributes += "sharable ";
                        
                        for (int st = 0; st < 2; ++st)
                        {
                            std::string stattributes = shattributes;
                            if (st)
                                stattributes += "streamable ";

                            mpParser.reset(new compil::Parser());
                            mDocument = lib::compil::CompilDocument::create();

                            ASSERT_TRUE( parseDocument(
                                (stattributes + "structure name {}").c_str()) ) << stattributes;
                                
                            EXPECT_EQ(1U, mDocument->objects().size());
                            EXPECT_TRUE(checkStructure(0, 1, 1, "name"));
                            EXPECT_TRUE(checkStructureAbstract(0, a != 0));
                            EXPECT_TRUE(checkStructureControlled(0, c != 0));
                            EXPECT_TRUE(checkStructureImmutable(0, m != 0));
                            EXPECT_TRUE(checkStructurePartial(0, p != 0));
                            EXPECT_TRUE(checkStructureSharable(0, sh != 0));
                            EXPECT_TRUE(checkStructureStreamable(0, st != 0));
                        }
                    }
                }
            }
        }
    }
}

TEST_F(ParserStructureTests, 2structuresWithComments)
{
    ASSERT_TRUE( parseDocument(
        "//comment1\n"
        "structure name1 {}\n"
        "//comment2\n"
        "structure name2 {}") );

    EXPECT_EQ(2U, mDocument->objects().size());

    EXPECT_TRUE(checkStructure(0, 2, 1, "name1", "comment1"));
    EXPECT_TRUE(checkStructure(1, 4, 1, "name2", "comment2"));

    EXPECT_EQ(0U, mpParser->messages().size());
}

