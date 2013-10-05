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

#include "template/string_literal.h"

#include "gtest/gtest.h"

#include <iostream>

namespace compil
{

TEST(StringTests, main)
{
    std::string str[] =
    {
        "\"\\u1234\\U00012345\"",
        "\"te\"\"st\"",
        "\"te\"  \"st\"",
        "\"te\" \n \"st\"",
        "\"\"",
        "\"\\\"\"",
        "\"test\"",
        "\"test\" something",
        "\"\\\'\\\"\\\?\\\\\\a\\b\\f\\n\\r\\t\\v\"",
        "\"\\x61cd\\X3012\\x7z\"",
        "\"\\141cd\\06012\\78\\778\"",
        "\"te",
        "\"te\nst\"",
        "\"test\\\"",
        "\"te\\st\"",
        //
    };

    typedef line_pos_iterator<std::string::const_iterator> Iterator;

    std::ostringstream result;

    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); ++i)
    {
        source_string<Iterator> g;
        Iterator iter(str[i].begin());
        Iterator end(str[i].end());

        String string;
        bool r = phrase_parse(iter, end, g, qi::space, string);
        if (r)
            result << string.beginLine << "-" << string.endLine << ": " << string.value << " === " << string.source << "\n";
        else
            result << "Parsing failed\n";
    }

    ASSERT_STREQ("1-1: \xE1\x88\xB4\xF0\x92\x8D\x85 === \"\\u1234\\U00012345\"\n"
                 "1-1: test === \"te\"\"st\"\n"
                 "1-1: test === \"te\"  \"st\"\n"
                 "1-2: test === \"te\" \n \"st\"\n"
                 "1-1:  === \"\"\n"
                 "1-1: \" === \"\\\"\"\n"
                 "1-1: test === \"test\"\n"
                 "1-1: test === \"test\"\n"
                 "1-1: '\"?\\\a\b\f\n\r\t\v === \"\\'\\\"\\?\\\\\\a\\b\\f\\n\\r\\t\\v\"\n"
                 "1-1: acd012\az === \"\\x61cd\\X3012\\x7z\"\n"
                 "1-1: acd012\a8?8 === \"\\141cd\\06012\\78\\778\"\n"
                 "Parsing failed\n"
                 "Parsing failed\n"
                 "Parsing failed\n"
                 "Parsing failed\n"
                 , result.str().c_str());
}

}