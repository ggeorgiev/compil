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

#include "c++_test_generator.h"

namespace compil
{

const int CppTestGenerator::mainStream = 0;

CppTestGenerator::CppTestGenerator()
{
    for (int i = 0; i <= 0; ++i)
    {
        mStreams.push_back(boost::shared_ptr<std::stringstream>(new std::stringstream()));
        mIndent.push_back(0);
    }
}

CppTestGenerator::~CppTestGenerator()
{
}

bool CppTestGenerator::generate()
{
    addDependency(impl->cppHeaderFileDependency(mpModel->name()->value(),
                                                mpModel->package()));
                                                
    addDependency(Dependency("gtest/gtest.h",
                             Dependency::system_type,
                             Dependency::thirdparty_level,
                             Dependency::private_section,
                             "Google Test framework"));
                             
    includeHeaders(mainStream, Dependency::private_section);

    line()  << "TEST(StructuresTest, isInitialize)"
"{"
"    StructureIsInitialize structure;"
"    EXPECT_FALSE(structure.isInitialized());"
""
"    structure.set_r(5);"
"    EXPECT_TRUE(structure.isInitialized());"
""
"    structure.erase_r();"
"    EXPECT_FALSE(structure.isInitialized());"
"}";
    eol(mainStream);
    
    return serializeStreams();
}

}

