// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * The name of George Georgiev can not be used to endorse or 
// promote products derived from this software without specific prior 
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: george.georgiev@hotmail.com (George Georgiev)
//
#include "compil_generator.h"
#include "parser.h"

#include "configuration_manager.h"

#include "library/compil/document.h"

#include "gtest/gtest.h"

#include "boost/make_shared.hpp"

#include <iostream>

class CompilGeneratorTests : public ::testing::Test 
{
public:
    virtual void SetUp() 
    {
        mpParser.reset(new compil::Parser());
        mConfigurationManager.reset(new compil::ConfigurationManager());
        mpCompilGenerator.reset(new compil::CompilGenerator());

        AlignerConfigurationSPtr pAlignerConfiguration(new AlignerConfiguration());
        mConfigurationManager->registerConfiguration(pAlignerConfiguration);
        
        mpFormatter = boost::make_shared<compil::CppFormatter>
            (mConfigurationManager->getConfiguration<FormatterConfiguration>(), compil::PackageSPtr());
        mpImplementer = boost::make_shared<compil::CppImplementer>
            (mpFormatter);
            
        mpImplementer->init(compil::PackageSPtr(), mConfigurationManager->getConfiguration<ImplementerConfiguration>());
    }

    bool checkGeneration(const char* input, const char* output)
    {
        std::string prefix = "compil {}\n";
        boost::shared_ptr<std::istringstream> pInput(new std::istringstream(prefix + input));
        bool result = mpParser->parseDocument(pInput, mDocument);
        EXPECT_TRUE(result);
        if (!result) return false;

        boost::shared_ptr<std::ostringstream> pOutput(new std::ostringstream());
        EXPECT_TRUE( mpCompilGenerator->init("main",
                                             mConfigurationManager->getConfiguration<AlignerConfiguration>(),
                                             mpFormatter,
                                             mpImplementer, 
                                             pOutput, 
                                             mDocument) );
        EXPECT_TRUE( mpCompilGenerator->generate() );

        std::string compil = pOutput->str();
        EXPECT_STREQ((prefix + output).c_str(), compil.c_str());
        return (prefix + output) == pOutput->str();
    }

protected:
    compil::DocumentSPtr mDocument;
    compil::ParserPtr mpParser;
    compil::ConfigurationManagerPtr mConfigurationManager;
    
    compil::CppFormatterPtr mpFormatter;
    compil::CppImplementerPtr mpImplementer;
    compil::CompilGeneratorPtr mpCompilGenerator;
};

TEST_F(CompilGeneratorTests, empty)
{
    EXPECT_TRUE(checkGeneration("", ""));
}

TEST_F(CompilGeneratorTests, import)
{
    EXPECT_TRUE(checkGeneration(
        "import \"blah\" ;", 
        "import \"blah\";\n"));
}

TEST_F(CompilGeneratorTests, enum)
{
    EXPECT_TRUE(checkGeneration(
        "enum ename{}", 
        "weak enum<integer> ename\n{\n}\n"));
}

TEST_F(CompilGeneratorTests, weakEnum)
{
    EXPECT_TRUE(checkGeneration(
        "weak enum ename{}", 
        "weak enum<integer> ename\n{\n}\n"));
}
    
TEST_F(CompilGeneratorTests, strongEnum)
{
    EXPECT_TRUE(checkGeneration(
        "strong enum ename{}", 
        "strong enum<integer> ename\n{\n}\n"));
}

TEST_F(CompilGeneratorTests, enumWithBase)
{
    EXPECT_TRUE(checkGeneration(
        "enum<short> ename{}", 
        "weak enum<short> ename\n{\n}\n"));
}

TEST_F(CompilGeneratorTests, enumValues)
{
    EXPECT_TRUE(checkGeneration(
        "enum ename{value1;value2;value3;}", 
        "weak enum<integer> ename\n"
        "{\n"
        "    value1;\n"
        "    value2;\n"
        "    value3;\n"
        "}\n"));
}

TEST_F(CompilGeneratorTests, innerEnum)
{
    EXPECT_TRUE(checkGeneration(
        "structure sname { enum ename{value;} }",
        "structure sname\n"
        "{\n"
        "    weak enum<integer> ename\n"
        "    {\n"
        "        value;\n"
        "    }\n"
        "}\n"
        "\n"));
}

TEST_F(CompilGeneratorTests, innerEnumField)
{
    EXPECT_TRUE(checkGeneration(
        "structure sname { enum ename{value;} integer b; }",
        "structure sname\n"
        "{\n"
        "    weak enum<integer> ename\n"
        "    {\n"
        "        value;\n"
        "    }\n"
        "\n"
        "    integer b;\n"
        "}\n"
        "\n"));
}

TEST_F(CompilGeneratorTests, innerFieldEnum)
{
    EXPECT_TRUE(checkGeneration(
        "structure sname { integer a; enum ename{value;} }",
        "structure sname\n"
        "{\n"
        "    integer a;\n"
        "\n"
        "    weak enum<integer> ename\n"
        "    {\n"
        "        value;\n"
        "    }\n"
        "}\n"
        "\n"));
}

TEST_F(CompilGeneratorTests, innerFieldEnumField)
{
    EXPECT_TRUE(checkGeneration(
        "structure sname { integer a; enum ename{value;} integer b; }",
        "structure sname\n"
        "{\n"
        "    integer a;\n"
        "\n"
        "    weak enum<integer> ename\n"
        "    {\n"
        "        value;\n"
        "    }\n"
        "\n"
        "    integer b;\n"
        "}\n"
        "\n"));
}

TEST_F(CompilGeneratorTests, specimen)
{
    EXPECT_TRUE(checkGeneration(
        "specimen sname{}", 
        "specimen<integer> sname\n{\n}\n"));
}

TEST_F(CompilGeneratorTests, factory)
{
    EXPECT_TRUE(checkGeneration(
        "hierarchy factory<integer> fname{}", 
        "hierarchy factory<integer> fname\n{\n}\n"));
}

TEST_F(CompilGeneratorTests, structure)
{
    EXPECT_TRUE(checkGeneration(
        "structure sname{}", 
        "structure sname\n{\n}\n\n"));
}

TEST_F(CompilGeneratorTests, controlledStructure)
{
    EXPECT_TRUE(checkGeneration(
        "controlled structure sname{}", 
        "controlled structure sname\n{\n}\n\n"));
}

TEST_F(CompilGeneratorTests, immutableStructure)
{
    EXPECT_TRUE(checkGeneration(
        "immutable structure sname{}", 
        "immutable structure sname\n{\n}\n\n"));
}

TEST_F(CompilGeneratorTests, controlledImmutableStructure)
{
    EXPECT_TRUE(checkGeneration(
        "controlled immutable structure sname{}", 
        "controlled immutable structure sname\n{\n}\n\n"));
}

TEST_F(CompilGeneratorTests, immutablePartialStructure)
{
    EXPECT_TRUE(checkGeneration(
        "immutable partial structure sname{}", 
        "immutable partial structure sname\n{\n}\n\n"));
}

TEST_F(CompilGeneratorTests, controlledImmutablePartialStructure)
{
    EXPECT_TRUE(checkGeneration(
        "controlled immutable partial structure sname{}", 
        "controlled immutable partial structure sname\n{\n}\n\n"));
}

TEST_F(CompilGeneratorTests, structureFields)
{
    EXPECT_TRUE(checkGeneration(
        "structure sname{integer a;integer b=optional; integer c=123; string s='text';"
        "reference<string> rs; vector<string> vs; reference<vector<string> > rvs;"
        "vector<reference<string> > vrs;}", 
        
        "structure sname\n"
        "{\n"
        "    integer                     a;\n"
        "    integer                     b   = optional;\n"
        "    integer                     c   = 123;\n"
        "    string                      s   = 'text';\n"
        "    reference<string>           rs;\n"
        "    vector<string>              vs;\n"
        "    reference< vector<string> > rvs;\n"
        "    vector< reference<string> > vrs;\n"
        "}\n"
        "\n"));
}

TEST_F(CompilGeneratorTests, structureIdentifications)
{
    EXPECT_TRUE(checkGeneration(
        "structure sname{runtime identification;}", 
        "structure sname\n"
        "{\n"
        "    runtime identification;\n"
        "}\n"
        "\n"));
}

TEST_F(CompilGeneratorTests, structureInherit)
{
    EXPECT_TRUE(checkGeneration(
        "structure sbase {} structure sname inherit sbase {}", 
        "structure sbase\n"
        "{\n"
        "}\n"
        "\n"
        "structure sname\n"
        "    inherit sbase\n"
        "{\n"
        "}\n"
        "\n"));
}


TEST_F(CompilGeneratorTests, OverrideDefaultValue)
{
    EXPECT_TRUE(checkGeneration(
        "structure base { integer a; integer foo; } structure sname inherit base alter a = 5,foo=10 {}",
        "structure base\n"
        "{\n"
        "    integer a;\n"
        "    integer foo;\n"
        "}\n"
        "\n"
        "structure sname\n"
        "    inherit base\n"
        "        alter a   = 5,\n"
        "              foo = 10\n"
        "{\n"
        "}\n"
        "\n"));
}

TEST_F(CompilGeneratorTests, inteface)
{
    EXPECT_TRUE(checkGeneration(
        "interface iname{}", 
        "interface iname\n{\n}\n"));
}

TEST_F(CompilGeneratorTests, intefaceMethod)
{
    EXPECT_TRUE(checkGeneration(
        "interface iname{method mname{}}", 
        "interface iname\n{\n    method mname\n    {\n    }\n}\n"));
}

TEST_F(CompilGeneratorTests, intefaceMethodParameter)
{
    EXPECT_TRUE(checkGeneration(
        "interface iname{method mname{-->integer pname;}}", 
        "interface iname\n{\n    method mname\n    {\n        --> integer pname;\n    }\n}\n"));
}
