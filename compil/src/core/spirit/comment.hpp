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

#ifndef _COMPIL_COMMENTS_H__
#define _COMPIL_COMMENTS_H__

#include "core/spirit/position.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/home/support/iterators/line_pos_iterator.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace compil
{

using namespace boost::spirit;

////////////////////////////////
// extra facilities

struct Comment : public RangePosition
{
    Comment()
        : RangePosition()
        , text()
    {
    }

    std::vector<std::string> text;
    std::string source;
};

}

BOOST_FUSION_ADAPT_STRUCT(compil::Comment,
                            (std::vector<std::string>, text)
                            (std::string, source)
                            (size_t,      beginLine)
                            (size_t,      endLine)
                          )

//
////////////////////////////////

namespace compil
{

template <typename Iterator>
struct source_comment : qi::grammar<Iterator, Comment(), qi::space_type>
{
    source_comment() : source_comment::base_type(start)
    {
        using qi::char_;
        using qi::raw;
        using qi::_val;
        using qi::_1;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;

        c_comment %= repository::confix("/*", "*/")[*(char_ - "*/")];

        cpp_comment %= repository::confix("//", eol | eoi)[*(char_ - eol)];

        comments %= c_comment | *(cpp_comment);

        start = raw[ comments[at_c<0>(_val) = _1] ]
                    [
                        at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                        at_c<2>(_val) = get_line_(begin(_1)),
                        at_c<3>(_val) = get_line_(end(_1))
                    ]
        ;
    }

    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, Comment(), qi::space_type> start;
    qi::rule<Iterator, std::string()> c_comment;
    qi::rule<Iterator, std::string()> cpp_comment;
    qi::rule<Iterator, std::vector<std::string>()> comments;
};

}

#endif