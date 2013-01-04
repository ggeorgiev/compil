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
    
    bool checkSection(int sIndex, int line, int column, 
                      const char* name, const char* comment = NULL)
    {
        bool result = true;

        HF_ASSERT_LT(sIndex, (int)mProject->sections().size());
        compil::SectionSPtr section = mProject->sections()[sIndex];
            
        HF_EXPECT_STREQ(name, section->name()->value().c_str());
        HF_EXPECT_EQ(lang::compil::Line(line + 1), section->line());
        HF_EXPECT_EQ(lang::compil::Column(column), section->column());
       
        return result;
    }
    
    bool checkSectionFilePath(int sIndex, int fIndex,
                              int line, int column, const char* filepath)
    {
        bool result = true;

        HF_ASSERT_LT(sIndex, (int)mProject->sections().size());
        compil::SectionSPtr section = mProject->sections()[sIndex];
            
        HF_ASSERT_LT(fIndex, (int)section->paths().size());
        compil::FilePathSPtr filePath = section->paths()[fIndex];

        HF_EXPECT_STREQ(filepath, filePath->path().c_str());
        HF_EXPECT_EQ(line + 1, filePath->line().value());
        HF_EXPECT_EQ(column, filePath->column().value());
       
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

TEST_F(ParserProjectTests, sectionMainOpenClose)
{
    ASSERT_TRUE( parseProject(
        "section main {}") );
        
    EXPECT_TRUE(checkSection(0, 1, 1, "main"));
}

TEST_F(ParserProjectTests, sectionMainOpenFile)
{
    ASSERT_FALSE( parseProject(
        "section main { file ") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 21, compil::Message::p_expectSemicolon));
}

TEST_F(ParserProjectTests, sectionMainOpenFileSemicolon)
{
    ASSERT_FALSE( parseProject(
        "section main { file; ") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 22, compil::Message::p_unexpectEOFInStatementBody));
}

TEST_F(ParserProjectTests, sectionMainOpenFileClose)
{
    ASSERT_FALSE( parseProject(
        "section main { file }") );
        
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 21, compil::Message::p_expectSemicolon));
}

TEST_F(ParserProjectTests, sectionMainOpenFileFileClose)
{
    ASSERT_FALSE( parseProject(
        "section main { file file }") );
        
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 1, 21, compil::Message::p_expectSemicolon));
}

TEST_F(ParserProjectTests, sectionMainOpenFileSemicolonClose)
{
    ASSERT_TRUE( parseProject(
        "section main { file; }") );
        
    ASSERT_EQ(0U, mpParser->messages().size());
    EXPECT_TRUE(checkSection(0, 1, 1, "main"));
    EXPECT_TRUE(checkSectionFilePath(0, 0, 1, 16, "file"));
}

TEST_F(ParserProjectTests, sectionMainOpenFilesClose)
{
    ASSERT_TRUE( parseProject(
        "section main { file1; file2;}") );
        
    ASSERT_EQ(0U, mpParser->messages().size());
    EXPECT_TRUE(checkSection(0, 1, 1, "main"));
    EXPECT_TRUE(checkSectionFilePath(0, 0, 1, 16, "file1"));
    EXPECT_TRUE(checkSectionFilePath(0, 1, 1, 23, "file2"));
}

TEST_F(ParserProjectTests, sections)
{
    ASSERT_TRUE( parseProject(
        "section main { file1; file2;}\n"
        "section test { test1;\n"
        "               test2;}") );
        
    ASSERT_EQ(0U, mpParser->messages().size());
    EXPECT_TRUE(checkSection(0, 1, 1, "main"));
    EXPECT_TRUE(checkSectionFilePath(0, 0, 1, 16, "file1"));
    EXPECT_TRUE(checkSectionFilePath(0, 1, 1, 23, "file2"));

    EXPECT_TRUE(checkSection(1, 2, 1, "test"));
    EXPECT_TRUE(checkSectionFilePath(1, 0, 2, 16, "test1"));
    EXPECT_TRUE(checkSectionFilePath(1, 1, 3, 16, "test2"));
}
