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

#ifndef _COMPIL_STRING_H__
#define _COMPIL_STRING_H__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/home/support/iterators/line_pos_iterator.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

using namespace boost::spirit;

#include <boost/fusion/include/adapt_struct.hpp>

////////////////////////////////
// extra facilities
struct get_line_f
{
    template <typename> struct result { typedef size_t type; };
    template <typename It> size_t operator()(It const& pos_iter) const
    {
        return get_line(pos_iter);
    }
};

//
////////////////////////////////

struct RangePosition
{
    RangePosition()
        : beginLine(-1)
        , endLine(-1)
    {
    }

    size_t beginLine;
    size_t endLine;
};

struct String : public RangePosition
{
    String()
        : RangePosition()
        , value()
        , source()
    {
    }

    std::string value;
    std::string source;
};

BOOST_FUSION_ADAPT_STRUCT(String,
                            (std::string, value)
                            (std::string, source)
                            (size_t,      beginLine)
                            (size_t,      endLine)
                          )

template <typename Iterator>
struct source_string : qi::grammar<Iterator, String(), qi::space_type>
{
    struct escape_symbols : qi::symbols<char, char>
    {
        escape_symbols()
        {
            add
                ("\\\'"    , '\'')
                ("\\\""    , '\"')
                ("\\\?"    , '\?')
                ("\\\\"    , '\\')
                ("\\0"     , '\0')
                ("\\a"     , '\a')
                ("\\b"     , '\b')
                ("\\f"     , '\f')
                ("\\n"     , '\n')
                ("\\r"     , '\r')
                ("\\t"     , '\t')
                ("\\v"     , '\v')
            ;
        }

    } escape_symbol;

    source_string() : source_string::base_type(start)
    {
        using qi::char_;
        using qi::print;
        using qi::raw;
        using qi::_val;
        using qi::_1;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;

        escape %= escape_symbol;

        character %=   ("\\x" >> hex2)
                     | ("\\"  >> oct3)
                     | escape
                     | (print - '"');

        string %= '"' >> *(character) >> '"';

        start = raw[
                        string[at_c<0>(_val) = _1]
                   ]
                   [
                       at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                       at_c<2>(_val) = get_line_(begin(_1)),
                       at_c<3>(_val) = get_line_(end(_1))
                   ]
        ;
    }

    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, String(), qi::space_type> start;
    qi::rule<Iterator, std::string()> escape;
    qi::rule<Iterator, std::string()> character;
    qi::rule<Iterator, std::string()> string;
    qi::uint_parser<char, 16, 2, 2> hex2;
    qi::uint_parser<char,  8, 3, 3> oct3;

};

#endif
