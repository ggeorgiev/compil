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

#include "generator/project/generator_project.h"
#include "generator/project/test_source_provider.h"

#include "gtest/gtest.h"

#include "boost/make_shared.hpp"

namespace compil
{

static std::string project1 =
"section main\n"
"{\n"
"    a.compil\n"
"    b.compil\n"
"}\n";

static std::string document1 =
"compil {}\n"
"import \"b.compil\";\n"
"\n";

static std::string document2 =
"compil {}\n"
"import \"a.compil\";\n"
"\n";



TEST(GeneratorProjectTests, init)
{
    TestSourceProviderSPtr provider = boost::make_shared<TestSourceProvider>();
    provider->addFile("/foo/a.compilprj", project1);
    string_vector sources;
    
    {
        GeneratorProject project(provider);
        EXPECT_TRUE(project.init("a.compilprj", "/foo/", sources));
        EXPECT_STREQ("/foo/a.compilprj", project.projectPath().c_str());
    }

    {
        GeneratorProject project(provider);
        EXPECT_TRUE(project.init("/foo/a.compilprj", "/foo/", sources));
        EXPECT_STREQ("/foo/a.compilprj", project.projectPath().c_str());
    }

    {
        GeneratorProject project(provider);
        EXPECT_TRUE(project.init("foo/a.compilprj", "/", sources));
        EXPECT_STREQ("/foo/a.compilprj", project.projectPath().c_str());
    }
}

TEST(GeneratorProjectTests, initNegative)
{
    TestSourceProviderSPtr provider = boost::make_shared<TestSourceProvider>();
    provider->addFile("/foo/b.compilprj", project1);
    string_vector sources;
    
    {
        GeneratorProject project(provider);
        EXPECT_FALSE(project.init("a.compilprj", "/foo/", sources));
    }

    {
        GeneratorProject project(provider);
        EXPECT_FALSE(project.init("/foo/a.compilprj", "/foo/", sources));
    }

    {
        GeneratorProject project(provider);
        EXPECT_FALSE(project.init("foo/a.compilprj", "/", sources));
    }
}

}

