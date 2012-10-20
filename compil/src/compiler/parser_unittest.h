#include "parser.h"

#include "gtest/gtest.h"

#include <iostream>

#define HF_ASSERT_TRUE(a) \
    EXPECT_TRUE(a); \
    if (!(a)) return false;
    
#define HF_ASSERT_FALSE(a) \
    EXPECT_FALSE(a); \
    if (a) return false;

#define HF_ASSERT_LT(a, b) \
    EXPECT_LT(a, b); \
    if ((a) >= (b)) return false;

#define HF_ASSERT_EQ(a, b) \
    EXPECT_EQ(a, b); \
    if ((a) != (b)) return false;
    
#define HF_ASSERT_STREQ(a, b) \
    EXPECT_STREQ(a, b); \
    if (strcmp((a), (b)) != 0) return false;

#define HF_EXPECT_EQ(a, b) \
    EXPECT_EQ(a, b); \
    if ((a) != (b)) result = false;

#define HF_EXPECT_STREQ(a, b) \
    EXPECT_STREQ(a, b); \
    if (strcmp((a), (b)) != 0) result = false;

class BaseParserTests : public ::testing::Test 
{
public:
    virtual void SetUp() 
    {
        mpParser.reset(new compil::Parser());
        mpMessageCollector = mpParser->mpMessageCollector;
        mpModel.reset(new compil::Model());
    }
    
    static StreamPtr getRawInput(const char* text)
    {
        return StreamPtr(new std::stringstream(text));
    }
    
    static StreamPtr getInput(const char* text)
    {
        std::string prefix = "compil {}\n";
        return StreamPtr(new std::stringstream(prefix + text));
    }
    
    virtual bool parse(const char* text)
    {
        compil::PackageElement el1;
        el1.set_value("external1")
           .set_external(true);

        compil::PackageElement el2;
        el2.set_value("external2")
           .set_external(true);

        std::vector<compil::PackageElement> externalElements;
        externalElements.push_back(el1);
        externalElements.push_back(el2);
        
        mpSourceId =
            compil::SourceId::Builder()
                .set_value("source_id")
                .set_externalElements(externalElements)
                .finalize();    
    
        StreamPtr pInput = getInput(text);
        return mpParser->parse(mpSourceId, pInput, mpModel);
    }
    
    virtual bool parseRaw(const char* text)
    {
        mpSourceId =
            compil::SourceId::Builder()
                .set_value("source_id")
                .finalize();  
                
        StreamPtr pInput = getRawInput(text);
        return mpParser->parse(mpSourceId, pInput, mpModel);
    }

    virtual bool checkMessage(compil::Message& expected, int mIndex)
    {
        EXPECT_LT(mIndex, (int)mpMessageCollector->messages().size());
        if (mIndex >= (int)mpMessageCollector->messages().size())
            return false;
        
        compil::Message message = mpMessageCollector->messages()[mIndex];
        EXPECT_EQ(expected.severity(), message.severity());
        EXPECT_EQ(expected.sourceId(), message.sourceId());
        EXPECT_EQ(expected.line(), message.line());
        EXPECT_EQ(expected.column(), message.column());
        EXPECT_STREQ(expected.text().c_str(), message.text().c_str());
        return expected == message;
    }
    
    bool checkWarningMessage(int mIndex, int line, int column, const char* text)
    {
        compil::Message expected(compil::Message::SEVERITY_WARNING, text, 
                                 mpSourceId, line + 1, column);
        return checkMessage(expected, mIndex);
    }
    
    bool checkErrorMessage(int mIndex, int line, int column, const char* text)
    {
        compil::Message expected(compil::Message::SEVERITY_ERROR, text, 
                                 mpSourceId, line + 1, column);
        return checkMessage(expected, mIndex);
    }
    
    bool checkErrorMessage(int mIndex, int line, int column, const char* text, 
                           const compil::Message::Argument& argument)
    {
        compil::Message expected(compil::Message::SEVERITY_ERROR, text, 
                                 mpSourceId, line + 1, column);
        return checkMessage(expected << argument, mIndex);
    }
    
    bool checkErrorMessage(int mIndex, int line, int column, const char* text, 
                           const compil::Message::Argument& argument1,
                           const compil::Message::Argument& argument2)
    {
        compil::Message expected(compil::Message::SEVERITY_ERROR, text, 
                                 mpSourceId, line + 1, column);
        return checkMessage(expected << argument1 << argument2, mIndex);
    }

protected:
    compil::SourceIdSPtr mpSourceId;
    compil::ModelPtr mpModel;
    compil::ParserPtr mpParser;
    compil::MessageCollectorPtr mpMessageCollector;
};
