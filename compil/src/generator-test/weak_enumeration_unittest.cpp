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

#include "weak_enumeration.h"

#include "gtest/gtest.h"

TEST(WeakEnumerationTest, construct)
{
    EMonth month;
    EXPECT_EQ(EMonth::invalid(), month);
}

TEST(WeakEnumerationTest, compare)
{
    EMonth month = EMonth::january();
    EMonth month2 = EMonth::february();    
    EMonth month3 = EMonth::january();
    
    EXPECT_EQ(EMonth::january(), month);
    EXPECT_NE(month2, month);
    
    EXPECT_TRUE(EMonth::january() == month);
    EXPECT_FALSE(EMonth::february() == month);
    EXPECT_FALSE(month2 == month);
    EXPECT_TRUE(month3 == month);
    
    EXPECT_FALSE(EMonth::january() != month);
    EXPECT_TRUE(EMonth::february() != month);
    EXPECT_TRUE(month2 != month);
    EXPECT_FALSE(month3 != month);
}

TEST(WeakEnumerationTest, switch)
{
    EMonth month = EMonth::january();
    switch (month.value())
    {
        case EMonth::kJanuary:
            break;
        default:
            assert(false);
    }
}

TEST(WeakEnumerationTest, fromValue)
{
    EMonth month(EMonth::january());
    EXPECT_EQ(EMonth::january(), month);
}

TEST(WeakEnumerationTest, assignValue)
{
    EMonth month(EMonth::january());
    EMonth month1 = month;
    EXPECT_EQ(month1, month);
    
    EMonth month2;
    month2 = month;
    EXPECT_EQ(month2, month);
}

TEST(WeakEnumerationTest, evil_implicit_castings)
{
    EMonth month = 1;
    EXPECT_TRUE(month == 1);
    EXPECT_TRUE(month != 2);

    month = 2;
    month = month + 1;
}

TEST(WeakEnumerationTest, shortNames)
{
    EXPECT_STREQ("january", EMonth(EMonth::january()).shortName());
    EXPECT_STREQ("december", EMonth(EMonth::december()).shortName());
    
    EXPECT_STREQ("january", EMonth::shortName(EMonth::january()));
    EXPECT_STREQ("december", EMonth::shortName(EMonth::december()));
}

TEST(WeakEnumerationTest, flagsReset)
{
    EMonthFlags test = EMonthFlags::year();
    test.reset(EMonthFlags::quarter_1(), EMonthFlags::january());
    EXPECT_TRUE(test.isSet(EMonthFlags::january()));
    EXPECT_TRUE(test.isClear(EMonthFlags::february()));
    EXPECT_TRUE(test.isClear(EMonthFlags::march()));
}

TEST(WeakEnumerationTest, flagsSet)
{
    EMonthFlags test = EMonthFlags::nil();
    test.set(EMonthFlags::semi_year_1());
    EXPECT_TRUE(test.test(EMonthFlags::year(), EMonthFlags::semi_year_1()));
}

TEST(WeakEnumerationTest, flagsClear)
{
    EMonthFlags test = EMonthFlags::year();
    test.clear(EMonthFlags::semi_year_1());
    EXPECT_TRUE(test.test(EMonthFlags::year(), EMonthFlags::semi_year_2()));
}

TEST(WeakEnumerationTest, flagsFlip)
{
    EMonthFlags test = EMonthFlags::year();
    test = test.flip(EMonthFlags::semi_year_1());
    EXPECT_TRUE(test.test(EMonthFlags::year(), EMonthFlags::semi_year_2()));
    test = test.flip(EMonthFlags::semi_year_1());
    EXPECT_TRUE(test.test(EMonthFlags::year(), EMonthFlags::year()));
    test = test.flip(test);
    EXPECT_TRUE(test.isClear(EMonthFlags::year()));
}
