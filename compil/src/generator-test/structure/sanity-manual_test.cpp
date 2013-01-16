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

#include "structure/sanity.h"

#include "gtest/gtest.h"

namespace sanity
{

TEST(StructuresTest, isInitialize)
{
    StructureIsInitialize structure;
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r(5);
    EXPECT_TRUE(structure.isInitialized());
    
    structure.erase_r();
    EXPECT_FALSE(structure.isInitialized());
}

TEST(StructuresTest, inherit1IsInitialize)
{
    StructureIsInitialize1 structure;
    EXPECT_TRUE(structure.isInitialized());
    
    structure.erase_r();
    EXPECT_FALSE(structure.isInitialized());
}


TEST(StructuresTest, inherit2IsInitialize)
{
    StructureIsInitialize2 structure;
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r(5);
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r2(5);
    EXPECT_TRUE(structure.isInitialized());
    
    structure.erase_r();
    EXPECT_FALSE(structure.isInitialized());
}

TEST(StructuresTest, inherit3IsInitialize)
{
    StructureIsInitialize3 structure;
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r(5);
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r3(5);
    EXPECT_TRUE(structure.isInitialized());
    
    structure.erase_r();
    EXPECT_FALSE(structure.isInitialized());
}

TEST(StructuresTest, inherit4IsInitialize)
{
    StructureIsInitialize4 structure;
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r(5);
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r4(5);
    EXPECT_TRUE(structure.isInitialized());
    
    structure.erase_r();
    EXPECT_FALSE(structure.isInitialized());
}

TEST(StructuresTest, inherit5IsInitialize)
{
    StructureIsInitialize5 structure;
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r(5);
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r5(5);
    EXPECT_TRUE(structure.isInitialized());
    
    structure.erase_r();
    EXPECT_FALSE(structure.isInitialized());
}

TEST(StructuresTest, inherit6IsInitialize)
{
    StructureIsInitialize6 structure;
    EXPECT_FALSE(structure.isInitialized());
    
    structure.set_r6(5);
    EXPECT_TRUE(structure.isInitialized());
}

TEST(StructuresTest, isVoid)
{
    StructureIsVoid structure;
    EXPECT_TRUE(structure.isVoid());
    
    structure.set_o(5);
    EXPECT_FALSE(structure.isVoid());
}

TEST(StructuresTest, inherit1isVoid)
{
    StructureIsVoid1 structure;
    EXPECT_TRUE(structure.isVoid());
    
    structure.set_o(5);
    EXPECT_FALSE(structure.isVoid());
    
    structure.clear_o();
    EXPECT_TRUE(structure.isVoid());
    
    structure.set_o1(5);
    EXPECT_FALSE(structure.isVoid());
    
    structure.set_o(5);
    EXPECT_FALSE(structure.isVoid());
}

TEST(StructuresTest, downcast)
{
    StructureIsInitialize3SPtr structure3(new StructureIsInitialize3());
    
    StructureIsInitializeSPtr structure = structure3;
    
    StructureIsInitialize3SPtr structure3Downcast = StructureIsInitialize3::downcast(structure);
    EXPECT_EQ(structure3, structure3Downcast);

}

TEST(StructuresTest, shared_from_this)
{
    StructureIsInitialize3SPtr structure3(new StructureIsInitialize3());
    StructureIsInitialize3SPtr structure = structure3->shared_from_this();
    EXPECT_EQ(structure3, structure);
}

TEST(StructuresTest, const_shared_from_this)
{
    StructureIsInitialize3SPtr structure3(new StructureIsInitialize3());
    StructureIsInitialize3SCPtr cstructure3 = structure3;
    StructureIsInitialize3SCPtr structure = cstructure3->shared_from_this();
    EXPECT_EQ(structure3, structure);
}

}