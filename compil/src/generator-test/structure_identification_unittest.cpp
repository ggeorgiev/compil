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

#include "structure_identification.h"

#include "gtest/gtest.h"

namespace identification
{

TEST(StructureIdentificationTest, construct)
{
    Structure1 structure1;
    Structure2a structure2a;
    Structure2b structure2b;
    Structure3aa structure3aa;
    Structure3ab structure3ab;
    Structure3ba structure3ba;
    Structure3bb structure3bb;   
}

TEST(StructureIdentificationTest, static_values)
{
    EXPECT_EQ(EStructure1Id::structure1(), Structure1::staticStructure1Id());
    EXPECT_EQ(EStructure1Id::structure2a(), Structure2a::staticStructure1Id());
    EXPECT_EQ(EStructure1Id::structure3aa(), Structure3aa::staticStructure1Id());
    EXPECT_EQ(EStructure1Id::structure3ba(), Structure3ba::staticStructure1Id());
}

TEST(StructureIdentificationTest, runtime_values)
{
    Structure1 structure1;
    Structure2a structure2a;
    Structure3aa structure3aa;
    Structure3ba structure3ba;
    
    EXPECT_EQ(structure1.runtimeStructure1Id(), Structure1::staticStructure1Id());
    EXPECT_EQ(structure2a.runtimeStructure1Id(), Structure2a::staticStructure1Id());
    EXPECT_EQ(structure3aa.runtimeStructure1Id(), Structure3aa::staticStructure1Id());
    EXPECT_EQ(structure3ba.runtimeStructure1Id(), Structure3ba::staticStructure1Id());
}

}
