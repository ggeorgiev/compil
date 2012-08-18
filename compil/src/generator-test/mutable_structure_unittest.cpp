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

#include "mutable_structure.h"

#include "gtest/gtest.h"

TEST(MutableStructureTest, construct)
{
    MutableStructure1 mutableStructure;
}

TEST(MutableStructureTest, checkInitilization)
{
    MutableStructure1 mutableStructure;
    EXPECT_FALSE(mutableStructure.valid_r1());
    EXPECT_FALSE(mutableStructure.exist_o1());
    EXPECT_FALSE(mutableStructure.changed_d1());
    EXPECT_EQ(mutableStructure.default_d1(), mutableStructure.d1());
}

TEST(MutableStructureTest, setMethod)
{
    MutableStructure1 mutableStructure;
    mutableStructure.set_r1(11);
    mutableStructure.set_o1(12);
    mutableStructure.set_d1(13);
    
    EXPECT_EQ(11, mutableStructure.r1());
    EXPECT_EQ(12, mutableStructure.o1());
    EXPECT_EQ(13, mutableStructure.d1());
}

TEST(MutableStructureTest, mutableMethod)
{
    MutableStructure1 mutableStructure;
    mutableStructure.mutable_v1().push_back(11);
    
    EXPECT_EQ(1U, mutableStructure.v1().size());
    EXPECT_EQ(11, mutableStructure.v1()[0]);
    EXPECT_TRUE(mutableStructure.valid_v1());
}

TEST(MutableStructTest, availableMethod)
{
    MutableStructure1 mutableStructure;
    mutableStructure.set_r1(11);
    mutableStructure.set_o1(12);
    mutableStructure.set_d1(13);
    
    EXPECT_TRUE(mutableStructure.valid_r1());
    EXPECT_TRUE(mutableStructure.exist_o1());
    EXPECT_TRUE(mutableStructure.changed_d1());
}

TEST(MutableStructureTest, destroyMethod)
{
    MutableStructure1 mutableStructure;
    mutableStructure.set_r1(11);
    mutableStructure.set_o1(12);
    mutableStructure.set_d1(13);
    
    mutableStructure.erase_r1();
    mutableStructure.clear_o1();
    mutableStructure.reset_d1();
    
    EXPECT_FALSE(mutableStructure.valid_r1());
    EXPECT_FALSE(mutableStructure.exist_o1());
    EXPECT_FALSE(mutableStructure.changed_d1());
    EXPECT_EQ(mutableStructure.default_d1(), mutableStructure.d1());
}

TEST(MutableStructureTest, construct2)
{
    MutableStructure2 mutableStructure;
}

TEST(MutableStructureTest, checkInitilization2)
{
    MutableStructure2 mutableStructure;
    EXPECT_FALSE(mutableStructure.valid_r1());
    EXPECT_FALSE(mutableStructure.exist_o1());
    EXPECT_FALSE(mutableStructure.changed_d1());
    EXPECT_EQ(mutableStructure.default_d1(), mutableStructure.d1());

    EXPECT_FALSE(mutableStructure.valid_r2());
    EXPECT_FALSE(mutableStructure.exist_o2());
    EXPECT_FALSE(mutableStructure.changed_d2());
    EXPECT_EQ(mutableStructure.default_d2(), mutableStructure.d2());
}

TEST(MutableStructureTest, setMethod2)
{
    MutableStructure2 mutableStructure;
    mutableStructure.set_r1(11);
    mutableStructure.set_o1(12);
    mutableStructure.set_d1(13);
    
    EXPECT_EQ(11, mutableStructure.r1());
    EXPECT_EQ(12, mutableStructure.o1());
    EXPECT_EQ(13, mutableStructure.d1());
    
    mutableStructure.set_r2(21);
    mutableStructure.set_o2(22);
    mutableStructure.set_d2(23);
    
    EXPECT_EQ(21, mutableStructure.r2());
    EXPECT_EQ(22, mutableStructure.o2());
    EXPECT_EQ(23, mutableStructure.d2());
}

TEST(MutableStructureTest, mutableMethod2)
{
    MutableStructure2 mutableStructure;
    mutableStructure.mutable_v1().push_back(11);
    
    EXPECT_EQ(1U, mutableStructure.v1().size());
    EXPECT_EQ(11, mutableStructure.v1()[0]);
    EXPECT_TRUE(mutableStructure.valid_v1());
    
    mutableStructure.mutable_v2().push_back(21);
    
    EXPECT_EQ(1U, mutableStructure.v2().size());
    EXPECT_EQ(21, mutableStructure.v2()[0]);
    EXPECT_TRUE(mutableStructure.valid_v2());
}

TEST(MutableStructTest, availableMethod2)
{
    MutableStructure2 mutableStructure;
    mutableStructure.set_r1(11);
    mutableStructure.set_o1(12);
    mutableStructure.set_d1(13);
    
    EXPECT_TRUE(mutableStructure.valid_r1());
    EXPECT_TRUE(mutableStructure.exist_o1());
    EXPECT_TRUE(mutableStructure.changed_d1());
    EXPECT_FALSE(mutableStructure.valid_r2());
    EXPECT_FALSE(mutableStructure.exist_o2());
    EXPECT_FALSE(mutableStructure.changed_d2());
    
    mutableStructure.set_r2(21);
    mutableStructure.set_o2(22);
    mutableStructure.set_d2(23);
    
    EXPECT_TRUE(mutableStructure.valid_r2());
    EXPECT_TRUE(mutableStructure.exist_o2());
    EXPECT_TRUE(mutableStructure.changed_d2());
}

TEST(MutableStructureTest, destroyMethod2)
{
    MutableStructure2 mutableStructure;
    mutableStructure.set_r1(11);
    mutableStructure.set_o1(12);
    mutableStructure.set_d1(13);
    
    mutableStructure.erase_r1();
    mutableStructure.clear_o1();
    mutableStructure.reset_d1();
    
    EXPECT_FALSE(mutableStructure.valid_r1());
    EXPECT_FALSE(mutableStructure.exist_o1());
    EXPECT_FALSE(mutableStructure.changed_d1());
    EXPECT_EQ(mutableStructure.default_d1(), mutableStructure.d1());
    
    mutableStructure.set_r2(21);
    mutableStructure.set_o2(22);
    mutableStructure.set_d2(23);
    
    mutableStructure.erase_r2();
    mutableStructure.clear_o2();
    mutableStructure.reset_d2();
    
    EXPECT_FALSE(mutableStructure.valid_r2());
    EXPECT_FALSE(mutableStructure.exist_o2());
    EXPECT_FALSE(mutableStructure.changed_d2());
    EXPECT_EQ(mutableStructure.default_d2(), mutableStructure.d2());
}

TEST(MutableStructureTest, constructAggregate)
{
    MutableStructureAggregate aggregate;
}

TEST(MutableStructureTest, checkAggregate)
{
    MutableStructureAggregate aggregate;
    
    EXPECT_FALSE(aggregate.valid_rs());
    EXPECT_FALSE(aggregate.exist_os());
    
    EXPECT_FALSE(aggregate.valid_rrs());
    EXPECT_FALSE(aggregate.exist_ors());
    EXPECT_FALSE(aggregate.changed_rns());
    EXPECT_EQ(aggregate.default_rns(), aggregate.rns());
}

TEST(MutableStructureTest, setAggregate)
{
    MutableStructure1 rs;
    rs.set_r1(11);
    rs.set_o1(12);
    rs.set_d1(13);

    MutableStructure1 os;
    os.set_r1(21);
    os.set_o1(22);
    os.set_d1(23);
    
    MutableStructure1SPtr rrs(new MutableStructure1());
    MutableStructure1SPtr ors(new MutableStructure1());
    MutableStructure1SPtr rns(new MutableStructure1());
    
    MutableStructureAggregate aggregate;
    aggregate.set_rs(rs);
    aggregate.set_os(os);
            
    aggregate.set_rrs(rrs);
    aggregate.set_ors(ors);
    aggregate.set_rns(rns);
            
    EXPECT_EQ(11, aggregate.rs().r1());
    EXPECT_EQ(12, aggregate.rs().o1());
    EXPECT_EQ(13, aggregate.rs().d1());
    
    EXPECT_EQ(21, aggregate.os().r1());
    EXPECT_EQ(22, aggregate.os().o1());
    EXPECT_EQ(23, aggregate.os().d1());
    
    EXPECT_EQ(rrs, aggregate.rrs());
    EXPECT_EQ(ors, aggregate.ors());
    EXPECT_EQ(rns, aggregate.rns());
}

TEST(MutableStructureTest, availableAggregate)
{
    MutableStructure1 rs;
    rs.set_r1(11);
    rs.set_o1(12);
    rs.set_d1(13);

    MutableStructure1 os;
    os.set_r1(21);
    os.set_o1(22);
    os.set_d1(23);
    
    MutableStructure1SPtr rrs(new MutableStructure1());
    MutableStructure1SPtr ors(new MutableStructure1());
    MutableStructure1SPtr rns(new MutableStructure1());
    
    MutableStructureAggregate aggregate;
    aggregate.set_rs(rs);
    aggregate.set_os(os);
            
    aggregate.set_rrs(rrs);
    aggregate.set_ors(ors);
    aggregate.set_rns(rns);
    
    EXPECT_TRUE(aggregate.valid_rs());
    EXPECT_TRUE(aggregate.exist_os());
    
    EXPECT_TRUE(aggregate.valid_rrs());
    EXPECT_TRUE(aggregate.exist_ors());
    EXPECT_TRUE(aggregate.changed_rns());
}

TEST(MutableStructureTest, destroyAggregate)
{
    MutableStructure1 rs;
    rs.set_r1(11);
    rs.set_o1(12);
    rs.set_d1(13);

    MutableStructure1 os;
    os.set_r1(21);
    os.set_o1(22);
    os.set_d1(23);
    
    MutableStructure1SPtr rrs(new MutableStructure1());
    MutableStructure1SPtr ors(new MutableStructure1());
    MutableStructure1SPtr rns(new MutableStructure1());
    
    MutableStructureAggregate aggregate;
    aggregate.set_rs(rs);
    aggregate.set_os(os);
            
    aggregate.set_rrs(rrs);
    aggregate.set_ors(ors);
    aggregate.set_rns(rns);

    aggregate.erase_rs();
    aggregate.clear_os();

    aggregate.erase_rrs();
    aggregate.clear_ors();
    aggregate.reset_rns();
    
    EXPECT_FALSE(aggregate.valid_rs());
    EXPECT_FALSE(aggregate.exist_os());
    
    EXPECT_FALSE(aggregate.valid_rrs());
    EXPECT_FALSE(aggregate.exist_ors());
    EXPECT_FALSE(aggregate.changed_rns());
}



