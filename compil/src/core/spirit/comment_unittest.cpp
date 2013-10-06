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

#include "core/spirit/comment.hpp"

#include "gtest/gtest.h"

#include <boost/algorithm/string/join.hpp>

#include <iostream>

namespace compil
{

TEST(CommentsTests, main)
{
    std::string str[] =
    {
        "/*1234*/\n\n// test",
        "/*1234*/",
        "\n\n/*1234*/",
        "// foo bar\n",
        "// foo bar",
        "\n\n    // foo bar\n",
        "/*1234\n5678*/",
        "// comment\nnot a comment",
    };

    typedef line_pos_iterator<std::string::const_iterator> Iterator;

    std::ostringstream result;

    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); ++i)
    {
        source_comment<Iterator> g;
        Iterator iter(str[i].begin());
        Iterator end(str[i].end());

        Comment comment;
        bool r = phrase_parse(iter, end, g, qi::space, comment);
        if (r)
        {
            std::string text = boost::algorithm::join(comment.text, "\n");
            result << comment.beginLine << "-" << comment.endLine << ": " << text << "\n";
        }
        else
            result << "Parsing failed\n";
    }

    ASSERT_STREQ("1-1: 1234\n"
                 "1-1: 1234\n"
                 "3-3: 1234\n"
                 "1-2:  foo bar\n"
                 "1-1:  foo bar\n"
                 "3-4:  foo bar\n"
                 "1-2: 1234\n5678\n"
                 "1-2:  comment\n", result.str().c_str());
}

}