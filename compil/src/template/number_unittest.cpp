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

#include "template/number.h"

#include "gtest/gtest.h"

#include <iostream>

TEST(NumbersTests, integer)
{
    std::string str[] =
    {
        "\n\n\n1234",
        "\n\n-5",
        "\n-01234",
    };

    typedef line_pos_iterator<std::string::const_iterator> Iterator;

    std::ostringstream result;

    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); ++i)
    {
        source_integer<Iterator> g;
        Iterator iter(str[i].begin());
        Iterator end(str[i].end());

        IntegerNumber number;
        bool r = phrase_parse(iter, end, g, qi::space, number);
        if (r && iter == end)
            result << number.line << ": " << number.value << " // " << number.source << "\n";
        else
            result << "Parsing failed\n";
    }

    ASSERT_STREQ("4: 1234 // 1234\n"
                 "3: -5 // -5\n"
                 "Parsing failed\n", result.str().c_str());
}

TEST(NumbersTests, uinteger)
{
    std::string str[] =
    {
        "\n\n0x1234",
        "\n\n\n\n\n1234",
        "\n01234",
        "\nB011010101",
        "\n\n-5",
    };

    typedef line_pos_iterator<std::string::const_iterator> Iterator;

    std::ostringstream result;

    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); ++i)
    {
        source_uinteger<Iterator> g;
        Iterator iter(str[i].begin());
        Iterator end(str[i].end());

        UIntegerNumber number;
        bool r = phrase_parse(iter, end, g, qi::space, number);
        if (r && iter == end)
            result << number.line << ": 0x" << std::setw(8) << std::setfill('0') << std::hex << number.value << " // " << number.source << "\n";
        else
            result << "Parsing failed\n";
    }

    ASSERT_STREQ("3: 0x00001234 // 0x1234\n"
                 "6: 0x000004d2 // 1234\n"
                 "2: 0x0000029c // 01234\n"
                 "2: 0x000000d5 // B011010101\n"
                 "Parsing failed\n", result.str().c_str());
}

TEST(NumbersTests, double_)
{
    std::string str[] =
    {
        "\n\n0.0",
        "\n\n\n.1",
        "\n\n\n1",
        "\n\n\n1.",
    };

    typedef line_pos_iterator<std::string::const_iterator> Iterator;

    std::ostringstream result;

    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); ++i)
    {
        source_double<Iterator> g;
        Iterator iter(str[i].begin());
        Iterator end(str[i].end());

        DoubleNumber number;
        bool r = phrase_parse(iter, end, g, qi::space, number);
        if (r && iter == end)
            result << number.line << ": " << number.value << " // " << number.source << "\n";
        else
            result << "Parsing failed\n";
    }

    ASSERT_STREQ("3: 0 // 0.0\n"
                 "4: 0.1 // .1\n"
                 "Parsing failed\n"
                 "Parsing failed\n", result.str().c_str());
}