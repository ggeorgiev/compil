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

#include "strong_enumeration.h"

#include "gtest/gtest.h"

TEST(StrongEnumerationTest, construct)
{
    EWeekday weekday;
    EXPECT_EQ(EWeekday::invalid(), weekday);
}

TEST(StrongEnumerationTest, compare)
{
    EWeekday weekday = EWeekday::sunday();
    EWeekday weekday2 = EWeekday::monday();
    EWeekday weekday3 = EWeekday::sunday();
    
    EXPECT_EQ(EWeekday::sunday(), weekday);
    EXPECT_NE(weekday2, weekday);
 
    EXPECT_TRUE(EWeekday::sunday() == weekday);
    EXPECT_FALSE(EWeekday::monday() == weekday);
    EXPECT_FALSE(weekday2 == weekday);
    EXPECT_TRUE(weekday3 == weekday);
    
    EXPECT_FALSE(EWeekday::sunday() != weekday);
    EXPECT_TRUE(EWeekday::monday() != weekday);
    EXPECT_TRUE(weekday2 != weekday);
    EXPECT_FALSE(weekday3 != weekday);
}

TEST(StrongEnumerationTest, switch)
{
    EWeekday weekday = EWeekday::sunday();
    switch (weekday.value())
    {
        case EWeekday::kSunday:
            break;
        default:
            assert(false);
    }
}

TEST(StrongEnumerationTest, fromValue)
{
    EWeekday weekday(EWeekday::kSunday);
    EXPECT_EQ(EWeekday::sunday(), weekday);
}

TEST(StrongEnumerationTest, assignValue)
{
    EWeekday weekday(EWeekday::kSunday);
    EWeekday weekday1 = weekday;
    EXPECT_EQ(weekday1, weekday);
    
    EWeekday weekday2;
    weekday2 = weekday;
    EXPECT_EQ(weekday2, weekday);
}

TEST(StrongEnumerationTest, shortNames)
{
    EXPECT_STREQ("sunday", EWeekday::sunday().shortName());
    EXPECT_STREQ("saturday", EWeekday::saturday().shortName());
    
    EXPECT_STREQ("sunday", EWeekday::shortName(EWeekday::kSunday));
    EXPECT_STREQ("saturday", EWeekday::shortName(EWeekday::kSaturday));
}

TEST(StrongEnumerationTest, flagsReset)
{
    EWeekdayFlags test = EWeekdayFlags::all();
    test.reset(EWeekdayFlags::weekend(), EWeekdayFlags::sunday());
    EXPECT_TRUE(test.isSet(EWeekdayFlags::sunday()));
    EXPECT_TRUE(test.isClear(EWeekdayFlags::saturday()));
}

TEST(StrongEnumerationTest, flagsSet)
{
    EWeekdayFlags test = EWeekdayFlags::nil();
    test.set(EWeekdayFlags::weekend());
    EXPECT_TRUE(test.test(EWeekdayFlags::all(), EWeekdayFlags::weekend()));
}

TEST(StrongEnumerationTest, flagsClear)
{
    EWeekdayFlags test = EWeekdayFlags::all();
    test.clear(EWeekdayFlags::weekend());
    EXPECT_TRUE(test.test(EWeekdayFlags::all(), EWeekdayFlags::weekday()));
}

TEST(StrongEnumerationTest, flagsFlip)
{
    EWeekdayFlags test = EWeekdayFlags::all();
    test = test.flip(EWeekdayFlags::weekday());
    EXPECT_TRUE(test.test(EWeekdayFlags::all(), EWeekdayFlags::weekend()));
    test = test.flip(EWeekdayFlags::weekday());
    EXPECT_TRUE(test.test(EWeekdayFlags::all(), EWeekdayFlags::all()));
    test = test.flip(test);
    EXPECT_TRUE(test.isClear(EWeekdayFlags::all()));
}

