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

#include "immutable_structure.h"

#include "boost_assert_handler.h"

#include "gtest/gtest.h"

TEST(ImmutableStructureTest, construct)
{
    ImmutableStructure1::Builder builder;
    ImmutableStructure1 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    ASSERT_THROW(builder.finalize(), boost::assert_exception);
}

TEST(ImmutableStructureTest, checkInitilization)
{
    ImmutableStructure1 immutableStructure;
    EXPECT_FALSE(immutableStructure.valid_r1());
    EXPECT_FALSE(immutableStructure.exist_o1());
    EXPECT_FALSE(immutableStructure.changed_d1());
    EXPECT_EQ(immutableStructure.default_d1(), immutableStructure.d1());
}

TEST(ImmutableStructureTest, setMethod)
{
    ImmutableStructure1::Builder builder;
    builder.set_r1(11)
           .set_o1(12)
           .set_d1(13);
            
    builder.mutable_s1() = "s1";
            
    ImmutableStructure1 immutableStructure = builder.build();
    
    EXPECT_EQ(11, immutableStructure.r1());
    EXPECT_EQ(12, immutableStructure.o1());
    EXPECT_EQ(13, immutableStructure.d1());
    EXPECT_STREQ("s1", immutableStructure.s1().c_str());
    
    ImmutableStructure1 immutableStructureClone = ImmutableStructure1::Builder(immutableStructure).build();
    EXPECT_EQ(11, immutableStructureClone.r1());
    EXPECT_EQ(12, immutableStructureClone.o1());
    EXPECT_EQ(13, immutableStructureClone.d1());
    EXPECT_STREQ("s1", immutableStructureClone.s1().c_str());
}

TEST(ImmutableStructureTest, availableMethod)
{
    ImmutableStructure1::Builder builder;
    builder .set_r1(11)
            .set_o1(12)
            .set_d1(13);
            
    builder.mutable_s1() = "s1";
    
    ImmutableStructure1 immutableStructure = builder.build();
    EXPECT_TRUE(immutableStructure.valid_r1());
    EXPECT_TRUE(immutableStructure.exist_o1());
    EXPECT_TRUE(immutableStructure.changed_d1());
    EXPECT_TRUE(immutableStructure.valid_s1());
    
    ImmutableStructure1 immutableStructureClone = ImmutableStructure1::Builder(immutableStructure).build();
    EXPECT_TRUE(immutableStructureClone.valid_r1());
    EXPECT_TRUE(immutableStructureClone.exist_o1());
    EXPECT_TRUE(immutableStructureClone.changed_d1());
    EXPECT_TRUE(immutableStructureClone.valid_s1());
}

TEST(ImmutableStructureTest, destroyMethod)
{
    ImmutableStructure1::Builder builder;
    builder.set_r1(11);
    builder.set_o1(12);
    builder.set_d1(13);
    builder.mutable_s1() = "s1";
    
    builder.erase_r1();
    builder.clear_o1();
    builder.reset_d1();
    builder.erase_s1();
    
    ImmutableStructure1 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    EXPECT_FALSE(immutableStructure.valid_r1());
    EXPECT_FALSE(immutableStructure.exist_o1());
    EXPECT_FALSE(immutableStructure.changed_d1());
    EXPECT_EQ(immutableStructure.default_d1(), immutableStructure.d1());
    EXPECT_FALSE(immutableStructure.valid_s1());
    
    ImmutableStructure1 immutableStructureClone;
    ASSERT_THROW((immutableStructureClone = ImmutableStructure1::Builder(immutableStructure).build()), boost::assert_exception);
    EXPECT_FALSE(immutableStructureClone.valid_r1());
    EXPECT_FALSE(immutableStructureClone.exist_o1());
    EXPECT_FALSE(immutableStructureClone.changed_d1());
    EXPECT_EQ(immutableStructureClone.default_d1(), immutableStructureClone.d1());
    EXPECT_FALSE(immutableStructureClone.valid_s1());
}

TEST(ImmutableStructureTest, construct2)
{
    ImmutableStructure2::Builder builder;
    ImmutableStructure2 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    ASSERT_THROW(builder.finalize(), boost::assert_exception);
}

TEST(ImmutableStructureTest, checkInitilization2)
{
    ImmutableStructure2::Builder builder;
    
    ImmutableStructure2 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    EXPECT_FALSE(immutableStructure.valid_r1());
    EXPECT_FALSE(immutableStructure.exist_o1());
    EXPECT_FALSE(immutableStructure.changed_d1());
    EXPECT_EQ(immutableStructure.default_d1(), immutableStructure.d1());
    EXPECT_FALSE(immutableStructure.valid_s1());

    
    EXPECT_FALSE(immutableStructure.valid_r2());
    EXPECT_FALSE(immutableStructure.exist_o2());
    EXPECT_FALSE(immutableStructure.changed_d2());
    EXPECT_EQ(immutableStructure.default_d2(), immutableStructure.d2());
    EXPECT_FALSE(immutableStructure.valid_s2());
}

TEST(ImmutableStructureTest, setMethod2)
{
    ImmutableStructure2::Builder builder;
    builder.set_r1(11)
           .set_o1(12)
           .set_d1(13)
           .set_r2(21)
           .set_o2(22)
           .set_d2(23);
           
    builder.mutable_s1() = "s1";
    builder.mutable_s2() = "s2";
           
    ImmutableStructure2 immutableStructure = builder.build();
    
    EXPECT_EQ(11, immutableStructure.r1());
    EXPECT_EQ(12, immutableStructure.o1());
    EXPECT_EQ(13, immutableStructure.d1());
    EXPECT_STREQ("s1", immutableStructure.s1().c_str());
    
    EXPECT_EQ(21, immutableStructure.r2());
    EXPECT_EQ(22, immutableStructure.o2());
    EXPECT_EQ(23, immutableStructure.d2());
    EXPECT_STREQ("s2", immutableStructure.s2().c_str());
    
    ImmutableStructure2 immutableStructureClone = ImmutableStructure2::Builder(immutableStructure).build();
    EXPECT_EQ(11, immutableStructureClone.r1());
    EXPECT_EQ(12, immutableStructureClone.o1());
    EXPECT_EQ(13, immutableStructureClone.d1());
    EXPECT_STREQ("s1", immutableStructureClone.s1().c_str());
    
    EXPECT_EQ(21, immutableStructureClone.r2());
    EXPECT_EQ(22, immutableStructureClone.o2());
    EXPECT_EQ(23, immutableStructureClone.d2());
    EXPECT_STREQ("s2", immutableStructureClone.s2().c_str());
}

TEST(ImmutableStructureTest, availableMethod2)
{
    ImmutableStructure2::Builder builder;
    builder .set_r1(11)
            .set_o1(12)
            .set_d1(13)
            .set_r2(21)
            .set_o2(22)
            .set_d2(23);
            
    builder.mutable_s1() = "s1";
    builder.mutable_s2() = "s2";
    
    ImmutableStructure2 immutableStructure = builder.build();
    EXPECT_TRUE(immutableStructure.valid_r1());
    EXPECT_TRUE(immutableStructure.exist_o1());
    EXPECT_TRUE(immutableStructure.changed_d1());
    EXPECT_TRUE(immutableStructure.valid_s1());
        
    EXPECT_TRUE(immutableStructure.valid_r2());
    EXPECT_TRUE(immutableStructure.exist_o2());
    EXPECT_TRUE(immutableStructure.changed_d2());
    EXPECT_TRUE(immutableStructure.valid_s2());
    
    ImmutableStructure2 immutableStructureClone = ImmutableStructure2::Builder(immutableStructure).build();
    EXPECT_TRUE(immutableStructureClone.valid_r1());
    EXPECT_TRUE(immutableStructureClone.exist_o1());
    EXPECT_TRUE(immutableStructureClone.changed_d1());
    EXPECT_TRUE(immutableStructureClone.valid_s1());
    
    EXPECT_TRUE(immutableStructureClone.valid_r2());
    EXPECT_TRUE(immutableStructureClone.exist_o2());
    EXPECT_TRUE(immutableStructureClone.changed_d2());
    EXPECT_TRUE(immutableStructureClone.valid_s2());
}

TEST(ImmutableStructureTest, destroyMethod2)
{
    ImmutableStructure2::Builder builder;
    builder.set_r1(11);
    builder.set_o1(12);
    builder.set_d1(13);
    builder.mutable_s1() = "s1";
    
    builder.set_r2(21);
    builder.set_o2(22);
    builder.set_d2(23);
    builder.mutable_s2() = "s2";
        
    builder.erase_r1();
    builder.clear_o1();
    builder.reset_d1();
    builder.erase_s1();
    
    builder.erase_r2();
    builder.clear_o2();
    builder.reset_d2();
    builder.erase_s2();
    
    ImmutableStructure2 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    
    EXPECT_FALSE(immutableStructure.valid_r1());
    EXPECT_FALSE(immutableStructure.exist_o1());
    EXPECT_FALSE(immutableStructure.changed_d1());
    EXPECT_EQ(immutableStructure.default_d1(), immutableStructure.d1());
    EXPECT_FALSE(immutableStructure.valid_s1());
    
    EXPECT_FALSE(immutableStructure.valid_r2());
    EXPECT_FALSE(immutableStructure.exist_o2());
    EXPECT_FALSE(immutableStructure.changed_d2());
    EXPECT_EQ(immutableStructure.default_d2(), immutableStructure.d2());
    EXPECT_FALSE(immutableStructure.valid_s2());
    
    ImmutableStructure2 immutableStructureClone;
    ASSERT_THROW((immutableStructureClone = ImmutableStructure2::Builder(immutableStructure).build()), boost::assert_exception);
    
    EXPECT_FALSE(immutableStructureClone.valid_r1());
    EXPECT_FALSE(immutableStructureClone.exist_o1());
    EXPECT_FALSE(immutableStructureClone.changed_d1());
    EXPECT_EQ(immutableStructureClone.default_d1(), immutableStructureClone.d1());
    EXPECT_FALSE(immutableStructureClone.valid_s1());
    
    EXPECT_FALSE(immutableStructureClone.valid_r2());
    EXPECT_FALSE(immutableStructureClone.exist_o2());
    EXPECT_FALSE(immutableStructureClone.changed_d2());
    EXPECT_EQ(immutableStructureClone.default_d2(), immutableStructureClone.d2());
    EXPECT_FALSE(immutableStructureClone.valid_s2());
}

TEST(ImmutableStructureTest, construct3)
{
    ImmutableStructure3::Builder builder;
    ImmutableStructure3 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    ASSERT_THROW(builder.finalize(), boost::assert_exception);
}

TEST(ImmutableStructureTest, checkInitilization3)
{
    ImmutableStructure3::Builder builder;
    
    ImmutableStructure3 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    
    EXPECT_FALSE(immutableStructure.valid_r1());
    EXPECT_FALSE(immutableStructure.exist_o1());
    EXPECT_FALSE(immutableStructure.changed_d1());
    EXPECT_EQ(immutableStructure.default_d1(), immutableStructure.d1());
    EXPECT_FALSE(immutableStructure.valid_s1());
    
    EXPECT_FALSE(immutableStructure.valid_r2());
    EXPECT_FALSE(immutableStructure.exist_o2());
    EXPECT_FALSE(immutableStructure.changed_d2());
    EXPECT_EQ(immutableStructure.default_d2(), immutableStructure.d2());
    EXPECT_FALSE(immutableStructure.valid_s2());
    
    EXPECT_FALSE(immutableStructure.valid_r3());
    EXPECT_FALSE(immutableStructure.exist_o3());
    EXPECT_FALSE(immutableStructure.changed_d3());
    EXPECT_EQ(immutableStructure.default_d3(), immutableStructure.d3());
    EXPECT_FALSE(immutableStructure.valid_s3());
    
    ImmutableStructure3 immutableStructureClone;
    ASSERT_THROW((immutableStructureClone = ImmutableStructure3::Builder(immutableStructure).build()), boost::assert_exception);
    
    EXPECT_FALSE(immutableStructureClone.valid_r1());
    EXPECT_FALSE(immutableStructureClone.exist_o1());
    EXPECT_FALSE(immutableStructureClone.changed_d1());
    EXPECT_EQ(immutableStructureClone.default_d1(), immutableStructureClone.d1());
    EXPECT_FALSE(immutableStructureClone.valid_s1());
    
    EXPECT_FALSE(immutableStructureClone.valid_r2());
    EXPECT_FALSE(immutableStructureClone.exist_o2());
    EXPECT_FALSE(immutableStructureClone.changed_d2());
    EXPECT_EQ(immutableStructureClone.default_d2(), immutableStructureClone.d2());
    EXPECT_FALSE(immutableStructureClone.valid_s2());
    
    EXPECT_FALSE(immutableStructureClone.valid_r3());
    EXPECT_FALSE(immutableStructureClone.exist_o3());
    EXPECT_FALSE(immutableStructureClone.changed_d3());
    EXPECT_EQ(immutableStructureClone.default_d3(), immutableStructureClone.d3());
    EXPECT_FALSE(immutableStructureClone.valid_s3());
}

TEST(ImmutableStructureTest, setMethod3)
{
    ImmutableStructure3::Builder builder;
    builder.set_r1(11)
           .set_o1(12)
           .set_d1(13)
           .set_r2(21)
           .set_o2(22)
           .set_d2(23)
           .set_r3(31)
           .set_o3(32)
           .set_d3(33);
           
    builder.mutable_s1() = "s1";
    builder.mutable_s2() = "s2";
    builder.mutable_s3() = "s3";
           
    ImmutableStructure3 immutableStructure = builder.build();
    
    EXPECT_EQ(11, immutableStructure.r1());
    EXPECT_EQ(12, immutableStructure.o1());
    EXPECT_EQ(13, immutableStructure.d1());
    EXPECT_STREQ("s1", immutableStructure.s1().c_str());
    
    EXPECT_EQ(21, immutableStructure.r2());
    EXPECT_EQ(22, immutableStructure.o2());
    EXPECT_EQ(23, immutableStructure.d2());
    EXPECT_STREQ("s2", immutableStructure.s2().c_str());
    
    EXPECT_EQ(31, immutableStructure.r3());
    EXPECT_EQ(32, immutableStructure.o3());
    EXPECT_EQ(33, immutableStructure.d3());
    EXPECT_STREQ("s3", immutableStructure.s3().c_str());
    
    ImmutableStructure3 immutableStructureClone = ImmutableStructure3::Builder(immutableStructure).build();
    
    EXPECT_EQ(11, immutableStructureClone.r1());
    EXPECT_EQ(12, immutableStructureClone.o1());
    EXPECT_EQ(13, immutableStructureClone.d1());
    EXPECT_STREQ("s1", immutableStructureClone.s1().c_str());
    
    EXPECT_EQ(21, immutableStructureClone.r2());
    EXPECT_EQ(22, immutableStructureClone.o2());
    EXPECT_EQ(23, immutableStructureClone.d2());
    EXPECT_STREQ("s2", immutableStructureClone.s2().c_str());
    
    EXPECT_EQ(31, immutableStructureClone.r3());
    EXPECT_EQ(32, immutableStructureClone.o3());
    EXPECT_EQ(33, immutableStructureClone.d3());
    EXPECT_STREQ("s3", immutableStructureClone.s3().c_str());
}

TEST(ImmutableStructureTest, availableMethod3)
{
    ImmutableStructure3::Builder builder;
    builder.set_r1(11);
    builder.set_o1(12);
    builder.set_d1(13);
    builder.mutable_s1() = "s1";
    
    builder.set_r2(21);
    builder.set_o2(22);
    builder.set_d2(23);
    builder.mutable_s2() = "s2";
    
    builder.set_r3(31);
    builder.set_o3(32);
    builder.set_d3(33);
    builder.mutable_s3() = "s3";
    
    ImmutableStructure3 immutableStructure = builder.build();
    
    EXPECT_TRUE(immutableStructure.valid_r1());
    EXPECT_TRUE(immutableStructure.exist_o1());
    EXPECT_TRUE(immutableStructure.changed_d1());
    EXPECT_TRUE(immutableStructure.valid_s1());
    
    EXPECT_TRUE(immutableStructure.valid_r2());
    EXPECT_TRUE(immutableStructure.exist_o2());
    EXPECT_TRUE(immutableStructure.changed_d2());
    EXPECT_TRUE(immutableStructure.valid_s2());
    
    EXPECT_TRUE(immutableStructure.valid_r3());
    EXPECT_TRUE(immutableStructure.exist_o3());
    EXPECT_TRUE(immutableStructure.changed_d3());
    EXPECT_TRUE(immutableStructure.valid_s3());
    
    ImmutableStructure3 immutableStructureClone = ImmutableStructure3::Builder(immutableStructure).build();
    EXPECT_TRUE(immutableStructureClone.valid_r1());
    EXPECT_TRUE(immutableStructureClone.exist_o1());
    EXPECT_TRUE(immutableStructureClone.changed_d1());
    EXPECT_TRUE(immutableStructureClone.valid_s1());
    
    EXPECT_TRUE(immutableStructureClone.valid_r2());
    EXPECT_TRUE(immutableStructureClone.exist_o2());
    EXPECT_TRUE(immutableStructureClone.changed_d2());
    EXPECT_TRUE(immutableStructureClone.valid_s2());
    
    EXPECT_TRUE(immutableStructureClone.valid_r3());
    EXPECT_TRUE(immutableStructureClone.exist_o3());
    EXPECT_TRUE(immutableStructureClone.changed_d3());
    EXPECT_TRUE(immutableStructureClone.valid_s3());
}

TEST(ImmutableStructureTest, destroyMethod3)
{
    ImmutableStructure3::Builder builder;
    builder.set_r1(11);
    builder.set_o1(12);
    builder.set_d1(13);
    builder.mutable_s1() = "s1";
    
    builder.set_r2(21);
    builder.set_o2(22);
    builder.set_d2(23);
    builder.mutable_s2() = "s2";
    
    builder.set_r2(31);
    builder.set_o2(32);
    builder.set_d2(33);
    builder.mutable_s3() = "s3";
    
    builder.erase_r1();
    builder.clear_o1();
    builder.reset_d1();
    builder.erase_s1();
    
    builder.erase_r2();
    builder.clear_o2();
    builder.reset_d2();
    builder.erase_s2();
    
    builder.erase_r3();
    builder.clear_o3();
    builder.reset_d3();
    builder.erase_s3();
    
    ImmutableStructure3 immutableStructure;
    ASSERT_THROW((immutableStructure = builder.build()), boost::assert_exception);
    
    EXPECT_FALSE(immutableStructure.valid_r1());
    EXPECT_FALSE(immutableStructure.exist_o1());
    EXPECT_FALSE(immutableStructure.changed_d1());
    EXPECT_EQ(immutableStructure.default_d1(), immutableStructure.d1());
    EXPECT_FALSE(immutableStructure.valid_s1());
    
    EXPECT_FALSE(immutableStructure.valid_r2());
    EXPECT_FALSE(immutableStructure.exist_o2());
    EXPECT_FALSE(immutableStructure.changed_d2());
    EXPECT_EQ(immutableStructure.default_d2(), immutableStructure.d2());
    EXPECT_FALSE(immutableStructure.valid_s2());
    
    EXPECT_FALSE(immutableStructure.valid_r3());
    EXPECT_FALSE(immutableStructure.exist_o3());
    EXPECT_FALSE(immutableStructure.changed_d3());
    EXPECT_EQ(immutableStructure.default_d3(), immutableStructure.d3());
    EXPECT_FALSE(immutableStructure.valid_s3());
    
    ImmutableStructure3 immutableStructureClone;
    ASSERT_THROW((immutableStructureClone = ImmutableStructure3::Builder(immutableStructure).build()), boost::assert_exception);
    
    EXPECT_FALSE(immutableStructureClone.valid_r1());
    EXPECT_FALSE(immutableStructureClone.exist_o1());
    EXPECT_FALSE(immutableStructureClone.changed_d1());
    EXPECT_EQ(immutableStructureClone.default_d1(), immutableStructureClone.d1());
    EXPECT_FALSE(immutableStructureClone.valid_s1());
    
    EXPECT_FALSE(immutableStructureClone.valid_r2());
    EXPECT_FALSE(immutableStructureClone.exist_o2());
    EXPECT_FALSE(immutableStructureClone.changed_d2());
    EXPECT_EQ(immutableStructureClone.default_d2(), immutableStructureClone.d2());
    EXPECT_FALSE(immutableStructureClone.valid_s2());
    
    EXPECT_FALSE(immutableStructureClone.valid_r3());
    EXPECT_FALSE(immutableStructureClone.exist_o3());
    EXPECT_FALSE(immutableStructureClone.changed_d3());
    EXPECT_EQ(immutableStructureClone.default_d3(), immutableStructureClone.d3());
    EXPECT_FALSE(immutableStructureClone.valid_s3());
}

TEST(ImmutableStructureTest, constructAggregate)
{
    ImmutableStructureAggregate::Builder builder;
    ImmutableStructureAggregate immutableStructureAggregate;
    ASSERT_THROW((immutableStructureAggregate = builder.build()), boost::assert_exception);
    ASSERT_THROW(builder.finalize(), boost::assert_exception);
}

TEST(ImmutableStructureTest, checkAggregate)
{
    ImmutableStructureAggregate aggregate;
    
    EXPECT_FALSE(aggregate.valid_rs());
    EXPECT_FALSE(aggregate.exist_os());
    
    EXPECT_FALSE(aggregate.valid_rrs());
    EXPECT_FALSE(aggregate.exist_ors());
    EXPECT_FALSE(aggregate.changed_rns());
    EXPECT_EQ(aggregate.default_rns(), aggregate.rns());
}

TEST(ImmutableStructureTest, setAggregate)
{
    ImmutableStructure1 rs = ImmutableStructure1::Builder()
            .set_r1(11)
            .set_o1(12)
            .set_d1(13)
            .set_s1("")
            .build();

    ImmutableStructure1 os = ImmutableStructure1::Builder()
            .set_r1(21)
            .set_o1(22)
            .set_d1(23)
            .set_s1("")
            .build();
    
    ImmutableStructure1SPtr rrs;
    ASSERT_THROW((rrs = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    ImmutableStructure1SPtr ors;
    ASSERT_THROW((ors = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    ImmutableStructure1SPtr rns;
    ASSERT_THROW((rns = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    
    ImmutableStructureAggregate aggregate = ImmutableStructureAggregate::Builder()
            .set_rs(rs)
            .set_os(os)
            
            .set_rrs(rrs)
            .set_ors(ors)
            .set_rns(rns)

            .build();
            
            
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

TEST(ImmutableStructureTest, availableAggregate)
{
    ImmutableStructure1 rs = ImmutableStructure1::Builder()
            .set_r1(11)
            .set_o1(12)
            .set_d1(13)
            .set_s1("")
            .build();

    ImmutableStructure1 os = ImmutableStructure1::Builder()
            .set_r1(21)
            .set_o1(22)
            .set_d1(23)
            .set_s1("")
            .build();
    
    ImmutableStructure1SPtr rrs;
    ASSERT_THROW((rrs = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    ImmutableStructure1SPtr ors;
    ASSERT_THROW((ors = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    ImmutableStructure1SPtr rns;
    ASSERT_THROW((rns = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    
    ImmutableStructureAggregate aggregate = ImmutableStructureAggregate::Builder()
            .set_rs(rs)
            .set_os(os)
            
            .set_rrs(rrs)
            .set_ors(ors)
            .set_rns(rns)

            .build();
    
    EXPECT_TRUE(aggregate.valid_rs());
    EXPECT_TRUE(aggregate.exist_os());
    
    EXPECT_TRUE(aggregate.valid_rrs());
    EXPECT_TRUE(aggregate.exist_ors());
    EXPECT_TRUE(aggregate.changed_rns());
}

TEST(ImmutableStructureTest, destroyAggregate)
{
    ImmutableStructure1 rs = ImmutableStructure1::Builder()
            .set_r1(11)
            .set_o1(12)
            .set_d1(13)
            .set_s1("")
            .build();

    ImmutableStructure1 os = ImmutableStructure1::Builder()
            .set_r1(21)
            .set_o1(22)
            .set_d1(23)
            .set_s1("")
            .build();
    
    ImmutableStructure1SPtr rrs;
    ASSERT_THROW((rrs = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    ImmutableStructure1SPtr ors;
    ASSERT_THROW((ors = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    ImmutableStructure1SPtr rns;
    ASSERT_THROW((rns = ImmutableStructure1::Builder().finalize()), boost::assert_exception);
    
    ImmutableStructureAggregate::Builder builder;
    builder.set_rs(rs);
    builder.set_os(os);
            
    builder.set_rrs(rrs);
    builder.set_ors(ors);
    builder.set_rns(rns);

    builder.erase_rs();
    builder.clear_os();

    builder.erase_rrs();
    builder.clear_ors();
    builder.reset_rns();
    
    ImmutableStructureAggregate aggregate;
    ASSERT_THROW((aggregate = builder.build()), boost::assert_exception);
    
    EXPECT_FALSE(aggregate.valid_rs());
    EXPECT_FALSE(aggregate.exist_os());
    
    EXPECT_FALSE(aggregate.valid_rrs());
    EXPECT_FALSE(aggregate.exist_ors());
    EXPECT_FALSE(aggregate.changed_rns());
    EXPECT_EQ(aggregate.default_rns(), aggregate.rns());
}

