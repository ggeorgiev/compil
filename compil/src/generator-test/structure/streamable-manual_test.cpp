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

#include "structure/streamable.h"

#include "gtest/gtest.h"

namespace streamable
{

TEST(StructureStreamableTest, init)
{
    Item1 item1;
    Item1 item2;
    
    Item1SPtr refItem1;
    Item2SPtr refItem2;

    Structure1 structure1;
    structure1 << 1
               << Structure1::EWeak(1) 
               << Structure1::EStrong(1)
               << item1
               << item2
               << refItem1
               << refItem2
               << EEnum(1)
               << EEnum(2);
               
    Structure1SPtr refStructure1 = structure1Ref();
    refStructure1 << 1
                  << Structure1::EWeak(1) 
                  << Structure1::EStrong(1)
                  << item1
                  << item2
                  << refItem1
                  << refItem2
                  << EEnum(1)
                  << EEnum(2);
}

TEST(StructureStreamableTest, initInherit)
{
    Item1 item1;
    Item1 item2;
    
    Item1SPtr refItem1;
    Item2SPtr refItem2;

    Structure2 structure2;
    structure2 << 1
               << Structure1::EWeak(1) 
               << Structure1::EStrong(1)
               << item1
               << item2
               << refItem1
               << refItem2
               << EEnum(1)
               << EEnum(2);
               
    Structure2SPtr refstructure2 = structure2Ref();
    refstructure2 << 1
                  << Structure1::EWeak(1) 
                  << Structure1::EStrong(1)
                  << item1
                  << item2
                  << refItem1
                  << refItem2
                  << EEnum(1)
                  << EEnum(2);
}

TEST(StructureStreamableTest, immutableInit)
{
    Item1 item1;
    Item1 item2;
    
    Item1SPtr refItem1;
    Item2SPtr refItem2;
    
    IStructure1::Builder builder;
    builder << 1 
            << IStructure1::EWeak(1) 
            << IStructure1::EStrong(1)
            << item1
            << item2
            << refItem1
            << refItem2
            << EEnum(1)
            << EEnum(2);
}

TEST(StructureStreamableTest, immutableInitInherit)
{
    Item1 item1;
    Item1 item2;
    
    Item1SPtr refItem1;
    Item2SPtr refItem2;
    
    IStructure2::Builder builder;
    builder << 1 
            << IStructure1::EWeak(1) 
            << IStructure1::EStrong(1)
            << item1
            << item2
            << refItem1
            << refItem2
            << EEnum(1)
            << EEnum(2);
}

}
