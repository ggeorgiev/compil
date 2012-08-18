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
#include "table_aligner.h"

#include "gtest/gtest.h"

#include <iostream>

class TableAlignerTests : public ::testing::Test 
{
public:
    virtual void SetUp() 
    {
        mpConfig.reset(new AlignerConfiguration());
        mpAligner.reset(new compil::TableAligner(mpConfig));
    }

protected:
    AlignerConfigurationPtr mpConfig;
    compil::TableAlignerPtr mpAligner;
};

TEST_F(TableAlignerTests, empty)
{
    *mpAligner << compil::TableAligner::row();
    *mpAligner << "";
}

TEST_F(TableAlignerTests, ceil)
{
    *mpAligner << compil::TableAligner::row();
    *mpAligner << "ceil0,0";
    ASSERT_STREQ(mpAligner->str(0).c_str(), "ceil0,0\n");
}

TEST_F(TableAlignerTests, 2columns)
{
    *mpAligner << compil::TableAligner::row();
    *mpAligner << "ceil0,0 " << compil::TableAligner::col() << "ceil0,1";
    ASSERT_STREQ(mpAligner->str(0).c_str(), "ceil0,0 ceil0,1\n");
}

TEST_F(TableAlignerTests, 2rows)
{
    *mpAligner << compil::TableAligner::row();
    *mpAligner << "ceil0,0" << compil::TableAligner::row() << "ceil1,0";
    ASSERT_STREQ(mpAligner->str(0).c_str(), "ceil0,0\nceil1,0\n");
}

TEST_F(TableAlignerTests, 2x2)
{
    *mpAligner << compil::TableAligner::row();
    *mpAligner << "ceil0,0 " << compil::TableAligner::col() << "ceil0,1";
    *mpAligner << compil::TableAligner::row();
    *mpAligner << "ceil1,0 " << compil::TableAligner::col() << "ceil1,1";
    ASSERT_STREQ(mpAligner->str(0).c_str(), "ceil0,0 ceil0,1\nceil1,0 ceil1,1\n");
}
