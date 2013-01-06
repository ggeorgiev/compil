#include "parser_unittest.h"

class ParserStructureFieldTests : public BaseParserTests 
{
public:
    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        expected << compil::Message::Statement("field")
                 << compil::Message::Classifier("class parameter");
        return BaseParserTests::checkMessage(expected, mIndex);
    }
    
    void checkStructure(int sIndex, int line, int column, 
                        const char* name, const char* comment = NULL)
    {
        ASSERT_LT(sIndex, (int)mDocument->objects().size());

        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        ASSERT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);
        EXPECT_STREQ(name, pStructure->name()->value().c_str());
        EXPECT_EQ(lang::compil::Line(line + 1), pStructure->line());
        EXPECT_EQ(lang::compil::Column(column), pStructure->column());
        if (comment)
        {
            ASSERT_TRUE(pStructure->comment());
            EXPECT_EQ(1U, pStructure->comment()->lines().size());
            EXPECT_STREQ(comment, pStructure->comment()->lines()[0].c_str());
        }
        else
        {
            ASSERT_FALSE(pStructure->comment());
        }
    }

    bool checkField(int sIndex, int fIndex, 
                    int line, int column, 
                    const char* name, const char* type,
                    const char* comment = NULL)
    {
        HF_ASSERT_LT(sIndex, (int)mDocument->objects().size());

        compil::ObjectSPtr pSObject = mDocument->objects()[sIndex];
        HF_ASSERT_EQ(compil::EObjectId::structure(), pSObject->runtimeObjectId());
        
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pSObject);
        HF_ASSERT_LT(fIndex, (int)pStructure->objects().size());
        
        compil::ObjectSPtr pFObject = pStructure->objects()[fIndex];
        HF_ASSERT_EQ(compil::EObjectId::field(), pFObject->runtimeObjectId());
       
        compil::FieldSPtr pField = 
            boost::static_pointer_cast<compil::Field>(pFObject);
        HF_ASSERT_EQ(lang::compil::Line(line + 1), pField->line());
        HF_ASSERT_EQ(lang::compil::Column(column), pField->column());
        HF_ASSERT_STREQ(name, pField->name()->value().c_str());
        
        HF_ASSERT_TRUE(pField->type());
        
        HF_ASSERT_STREQ(type, pField->type()->name()->value().c_str());
        if (comment)
        {
            HF_ASSERT_TRUE(pField->comment());
            
            HF_ASSERT_EQ(1U, pField->comment()->lines().size());
            HF_ASSERT_STREQ(comment, pField->comment()->lines()[0].c_str());
        }
        else
        {
            HF_ASSERT_FALSE(pField->comment());
        }
        return true;
    }

    bool checkFieldDefault(int sIndex, int fIndex, 
                           int line, int column, 
                           bool bOptional, const char* text = "")
    {
        bool result = true;
        
        HF_ASSERT_LT(sIndex, (int)mDocument->objects().size());
        compil::ObjectSPtr pObject = mDocument->objects()[sIndex];
        HF_ASSERT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
        compil::StructureSPtr pStructure = 
            boost::static_pointer_cast<compil::Structure>(pObject);

        HF_ASSERT_LT(fIndex, (int)pStructure->objects().size());
            compil::ObjectSPtr pFObject = pStructure->objects()[fIndex];
        HF_ASSERT_EQ(compil::EObjectId::field(), pFObject->runtimeObjectId());
        compil::FieldSPtr pField = 
            boost::static_pointer_cast<compil::Field>(pFObject);

        HF_ASSERT_TRUE( pField->defaultValue() );
        HF_EXPECT_EQ(lang::compil::Line(line + 1), pField->defaultValue()->line());
        HF_EXPECT_EQ(lang::compil::Column(column), pField->defaultValue()->column());
        HF_EXPECT_EQ(bOptional, pField->defaultValue()->optional());

        if (!bOptional)
        {
            HF_EXPECT_STREQ(text, pField->defaultValue()->value().c_str());
        }
        else
        {
            HF_EXPECT_TRUE(pField->defaultValue());
        }
            
        return result;
    }

protected:
};

/*
struct Person 
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

TEST_F(ParserStructureFieldTests, structureType)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  integer\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectStatementName));
}

TEST_F(ParserStructureFieldTests, structureWrongType)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  blah\n"
        "}") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectStatementName));
    EXPECT_TRUE(checkErrorMessage(1, 3, 3, compil::Message::p_unknownClassifierType, 
                                  compil::Message::Classifier("field"),
                                  compil::Message::Type("blah")));
}

TEST_F(ParserStructureFieldTests, structureTypeName)
{
    ASSERT_FALSE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectSemicolonOrAssignmentOperator));
}

TEST_F(ParserStructureFieldTests, structure1Field)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "integer"));
}

TEST_F(ParserStructureFieldTests, structure2Fields)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname1;\n"
        "  long fname2;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname1", "integer"));
    EXPECT_TRUE(checkField(0, 1, 4, 3, "fname2", "long"));
}

TEST_F(ParserStructureFieldTests, structureFieldWithComment)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  // comment\n"
        "  integer fname;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 4, 3, "fname", "integer", "comment"));
}

TEST_F(ParserStructureFieldTests, structureFieldWith2Comments)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  // skip comment\n"
        "\n"
        "  // comment \n"
        "  integer fname;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 6, 3, "fname", "integer", "comment"));

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 3, compil::Message::p_misplacedComment));
}

TEST_F(ParserStructureFieldTests, structureFieldCommentedName)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer /* comment */ fname;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "integer"));

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 11, compil::Message::p_misplacedComment));
}

TEST_F(ParserStructureFieldTests, structureFieldCommentAtTheEnd)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname /* comment */ ;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "integer"));

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 17, compil::Message::p_misplacedComment));
}

TEST_F(ParserStructureFieldTests, structureFieldCommentAfterIt)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname ;\n"
        "/* comment */\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "integer"));

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 4, 1, compil::Message::p_misplacedComment));
}

TEST_F(ParserStructureFieldTests, structureFieldGarbageAfterTheName)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  integer a blah;\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 13, compil::Message::p_expectSemicolonOrAssignmentOperator));
}

TEST_F(ParserStructureFieldTests, structureFieldDefaultNoValue)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  integer a =;\n"
        "}") );

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 3, 14, compil::Message::p_expectFieldDefaultValue));
}

TEST_F(ParserStructureFieldTests, structureFieldDefaultCommentNoValue)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  integer a = /*comment*/;\n"
        "}") );

    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 15, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 3, 26, compil::Message::p_expectFieldDefaultValue));
}

TEST_F(ParserStructureFieldTests, structureFieldOptional)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname = optional;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "integer"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 19, true));
}

TEST_F(ParserStructureFieldTests, structureFieldDefaultLiteralValue)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname = 123;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "integer"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 19, false, "123"));
}

TEST_F(ParserStructureFieldTests, structureFieldDefaultIdentifierValue)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  boolean fname = true;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "boolean"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 19, false, "true"));
}

TEST_F(ParserStructureFieldTests, structureFieldDefaultComment)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  integer fname = optional /*comment*/;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "integer"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 19, true));

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 28, compil::Message::p_misplacedComment));
}

TEST_F(ParserStructureFieldTests, structureFieldReference)
{
    ASSERT_FALSE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectType));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceCommentParameterTypeOpen)
{
    ASSERT_FALSE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference /* */ <\n"
        "}") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 13, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 4, 1, compil::Message::p_expectType));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceCommentParameterType)
{
    ASSERT_FALSE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference < integer /* */ >\n"
        "}") );
    
    ASSERT_EQ(2U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 23, compil::Message::p_misplacedComment));
    EXPECT_TRUE(checkErrorMessage(1, 4, 1, compil::Message::p_expectStatementName));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceComment)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference<integer> fname /* */;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "reference"));

    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkWarningMessage(0, 3, 28, compil::Message::p_misplacedComment));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceParameterTypeNameEq)
{
    ASSERT_FALSE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference<integer> fname =\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectFieldDefaultValue));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceParameterTypeNameEqOptional)
{
    ASSERT_FALSE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference<integer> fname = optional\n"
        "}") );
    
    ASSERT_EQ(1U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 1, compil::Message::p_expectSemicolon));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceParameterTypeNameEqOptionalDone)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference<integer> fname = optional;\n"
        "}") );
    
    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "reference"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 30, true));
}

TEST_F(ParserStructureFieldTests, structureFieldWeakReferenceParameterTypeNameEqOptionalDone)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  weak reference<integer> fname = optional;\n"
        "}") );
    
    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "reference"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 35, true));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceNull)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference<integer> fname = null;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "reference"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 30, false, "null"));
}

TEST_F(ParserStructureFieldTests, structureFieldWeakReferenceNull)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  weak reference<integer> fname = null;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "reference"));
    EXPECT_TRUE(checkFieldDefault(0, 0, 3, 35, false, "null"));
}

TEST_F(ParserStructureFieldTests, structureFieldReferenceToItself)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  reference<sname> fname;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "reference"));
    EXPECT_EQ(0U, mpParser->messages().size());
}

TEST_F(ParserStructureFieldTests, structureFieldWeakReferenceToItself)
{
    ASSERT_TRUE( parseDocument(
        "structure sname\n"
        "{\n"
        "  weak reference<sname> fname;\n"
        "}") );

    checkStructure(0, 1, 1, "sname");
    EXPECT_TRUE(checkField(0, 0, 3, 3, "fname", "reference"));
    EXPECT_EQ(0U, mpParser->messages().size());
}

TEST_F(ParserStructureFieldTests, structureFieldsWithSameNames)
{
    ASSERT_FALSE( parseDocument(
        "structure name\n"
        "{\n"
        "  small name;\n"
        "  small name = optional;\n"
        "  small name = 123;\n"

        "  short name;\n"
        "  short name = optional;\n"
        "  short name = 123;\n"

        "}") );
    
    ASSERT_EQ(5U, mpParser->messages().size());
    EXPECT_TRUE(checkErrorMessage(0, 4, 9, compil::Message::v_notUnique, 
                compil::Message::Statement("name"), compil::Message::Classifier("field name")));
}

TEST_F(ParserStructureFieldTests, structureFields)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  boolean b;\n"
        "  boolean b_o = optional;\n"
        "  boolean b_v = true;\n"

        "  small i8;\n"
        "  small i8_o = optional;\n"
        "  small i8_v = 123;\n"

        "  short i16;\n"
        "  short i16_o = optional;\n"
        "  short i16_v = 123;\n"

        "  integer i32;\n"
        "  integer i32_o = optional;\n"
        "  integer i32_v = 123;\n"

        "  long i64;\n"
        "  long i64_o = optional;\n"
        "  long i64_v = 123;\n"

        "  real32 r32;\n"
        "  real32 r32_o = optional;\n"
        "  real32 r32_v = 123.45;\n"

        "  real64 r64;\n"
        "  real64 r64_o = optional;\n"
        "  real64 r64_v = 123.45;\n"

        "  string s;\n"
        "  string s_o = optional;\n"
        "  string s_v = 'text';\n"

        "  binary bin;\n"
        "  binary bin_o = optional;\n"
        "  //binary bin_v = [something];\n"

        "}") );

    EXPECT_EQ(1U, mDocument->objects().size());

    compil::ObjectSPtr pObject = mDocument->objects()[0];
    ASSERT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
    compil::StructureSPtr pStructure = boost::static_pointer_cast<compil::Structure>(pObject);
    ASSERT_TRUE(pStructure);
    EXPECT_STREQ("name", pStructure->name()->value().c_str());
    EXPECT_EQ(26U, pStructure->objects().size());
}

TEST_F(ParserStructureFieldTests, structureUnaryContainers)
{
    ASSERT_TRUE( parseDocument(
        "structure name\n"
        "{\n"
        "  vector<integer> v;\n"
        //"  vector< reference<integer> > vr;\n"
        "  reference< vector<integer> > rv;\n"
        "}") );

    EXPECT_EQ(1U, mDocument->objects().size());

    compil::ObjectSPtr pObject = mDocument->objects()[0];
    ASSERT_EQ(compil::EObjectId::structure(), pObject->runtimeObjectId());
    compil::StructureSPtr pStructure = boost::static_pointer_cast<compil::Structure>(pObject);
    ASSERT_TRUE(pStructure);
    EXPECT_STREQ("name", pStructure->name()->value().c_str());
    EXPECT_EQ(2U, pStructure->objects().size());
}
