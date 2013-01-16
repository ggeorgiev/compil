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
// based on code from Adam Bowen posted on stackoverflow.com

#include "specimen/specimens.h"

#include "gtest/gtest.h"

TEST(SpecimenTest, construct)
{
    specimen::StringSpecimen specimen;
    specimen::StringSpecimen specimenValue("");
}

TEST(SpecimenTest, compare)
{
    specimen::StringSpecimen specimen1a("text1");
    specimen::StringSpecimen specimen1b("text1");
    specimen::StringSpecimen specimen2("text2");

    EXPECT_EQ(specimen1a, specimen1b);
    EXPECT_NE(specimen1a, specimen2);
 
    EXPECT_TRUE(specimen1a == specimen1b);
    EXPECT_FALSE(specimen1a == specimen2);
    
    EXPECT_FALSE(specimen1a != specimen1b);
    EXPECT_TRUE(specimen1a != specimen2);
    
    EXPECT_FALSE(specimen1a < specimen1b);
    EXPECT_TRUE(specimen1a < specimen2);
    EXPECT_FALSE(specimen2 < specimen1a);
}
