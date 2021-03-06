#include "parser.h"

#include "library/compil/document.h"

#include "language/compil/all/object.h"

#include "gtest/gtest.h"

#include "boost/make_shared.hpp"

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

#define HF_EXPECT_TRUE(a) \
    EXPECT_TRUE(a); \
    if (!(a)) result = false;

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
        mDocument = lib::compil::CompilDocument::create();
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

    virtual bool parseDocument(const char* text)
    {
        mProject.reset();

        lang::compil::PackageElementSPtr el1 = boost::make_shared<lang::compil::PackageElement>();
        el1->set_value("external1");
        lang::compil::PackageElementSPtr el2 = boost::make_shared<lang::compil::PackageElement>();
        el2->set_value("external2");

        std::vector<compil::PackageElementSPtr> externalElements;
        externalElements.push_back(el1);
        externalElements.push_back(el2);

        mpSourceId =
            compil::SourceId::Builder()
                .set_value("source_id")
                .set_externalElements(externalElements)
                .finalize();

        StreamPtr pInput = getInput(text);
        return mpParser->parseDocument(mpSourceId, pInput, mDocument);
    }

    virtual bool parseRawDocument(const char* text)
    {
        mProject.reset();

        mpSourceId =
            compil::SourceId::Builder()
                .set_value("source_id")
                .finalize();

        StreamPtr pInput = getRawInput(text);
        return mpParser->parseDocument(mpSourceId, pInput, mDocument);
    }

    virtual bool parseProject(const char* text)
    {
        mDocument.reset();

        lang::compil::PackageElementSPtr el1 = boost::make_shared<lang::compil::PackageElement>();
        el1->set_value("external1");
        lang::compil::PackageElementSPtr el2 = boost::make_shared<lang::compil::PackageElement>();
        el2->set_value("external2");

        std::vector<compil::PackageElementSPtr> externalElements;
        externalElements.push_back(el1);
        externalElements.push_back(el2);

        mpSourceId =
            compil::SourceId::Builder()
                .set_value("source_id")
                .set_externalElements(externalElements)
                .finalize();

        StreamPtr pInput = getInput(text);
        return mpParser->parseProject(mpSourceId, pInput, mProject);
    }

    virtual const std::vector<compil::Message> messages()
    {
        return mpParser->messages();
    }

    virtual bool checkMessage(compil::Message& expected, size_t mIndex)
    {
        EXPECT_LT(mIndex, messages().size());
        if (mIndex >= messages().size())
            return false;

        compil::Message message = messages()[mIndex];
        EXPECT_EQ(expected.severity(), message.severity());
        EXPECT_EQ(expected.sourceId(), message.sourceId());
        EXPECT_EQ(expected.line(), message.line());
        EXPECT_EQ(expected.column().value(), message.column().value());
        EXPECT_STREQ(expected.text().c_str(), message.text().c_str());
        return expected == message;
    }

    bool checkWarningMessage(size_t mIndex, int line, int column, const char* text)
    {
        compil::Message expected(compil::Message::SEVERITY_WARNING, text,
                                 mpSourceId, lang::compil::Line(line + 1), lang::compil::Column(column));
        return checkMessage(expected, mIndex);
    }

    bool checkErrorMessage(size_t mIndex, int line, int column, const char* text)
    {
        compil::Message expected(compil::Message::SEVERITY_ERROR, text,
                                 mpSourceId, lang::compil::Line(line + 1), lang::compil::Column(column));
        return checkMessage(expected, mIndex);
    }

    bool checkErrorMessage(size_t mIndex, int line, int column, const char* text,
                           const compil::Message::Argument& argument)
    {
        compil::Message expected(compil::Message::SEVERITY_ERROR, text,
                                 mpSourceId, lang::compil::Line(line + 1), lang::compil::Column(column));
        return checkMessage(expected << argument, mIndex);
    }

    bool checkErrorMessage(size_t mIndex, int line, int column, const char* text,
                           const compil::Message::Argument& argument1,
                           const compil::Message::Argument& argument2)
    {
        compil::Message expected(compil::Message::SEVERITY_ERROR, text,
                                 mpSourceId, lang::compil::Line(line + 1), lang::compil::Column(column));
        return checkMessage(expected << argument1 << argument2, mIndex);
    }

protected:
    compil::SourceIdSPtr mpSourceId;
    compil::DocumentSPtr mDocument;
    compil::ProjectSPtr mProject;
    compil::ParserPtr mpParser;
};
