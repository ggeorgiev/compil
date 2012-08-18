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

#include "strong_identifier.h"

#include "gtest/gtest.h"


TEST(StrongIdentifierTest, construct)
{
    CatalogId id;
}

TEST(StrongIdentifierTest, compare)
{
    CatalogId id(1);
    CatalogId id2(2);
    CatalogId id3(1);
    
    EXPECT_EQ(CatalogId(1), id);
    EXPECT_NE(id2, id);
    
    EXPECT_TRUE(CatalogId(1) == id);
    EXPECT_FALSE(CatalogId(2) == id);
    EXPECT_FALSE(id2 == id);
    EXPECT_TRUE(id3 == id);
    
    EXPECT_FALSE(CatalogId(1) != id);
    EXPECT_TRUE(CatalogId(2) != id);
    EXPECT_TRUE(id2 != id);
    EXPECT_FALSE(id3 != id);
}

TEST(StrongIdentifierTest, switch)
{
    CatalogId id(1);
    switch (id.value())
    {
        case 1:
            break;
        default:
            assert(false);
    }
}

TEST(StrongIdentifierTest, assignValue)
{
    CatalogId id(1);
    CatalogId id2 = id;
    EXPECT_EQ(id2, id);
}
