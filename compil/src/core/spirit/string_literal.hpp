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

#ifndef __CORE_SPIRIT_STRING_LITERAL_HPP__
#define __CORE_SPIRIT_STRING_LITERAL_HPP__
#pragma once

#include "core/spirit/position.h"

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

struct utf8_f
{
    template <typename> struct result { typedef std::string type; };

    template <typename INT>
    std::string operator()(INT in) const
    {
        std::string to;
        auto out = std::back_inserter(to);
        boost::utf8_output_iterator<decltype(out)> convert(out);
        *convert++ = in;
        return to;
    }
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

}

BOOST_FUSION_ADAPT_STRUCT(compil::String,
                            (std::string, value)
                            (std::string, source)
                            (size_t,      beginLine)
                            (size_t,      endLine)
                          )

namespace compil
{

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
        using qi::raw;
        using qi::_val;
        using qi::_1;
        using qi::space;
        using qi::omit;
        using qi::no_case;
        using qi::print;
        using qi::attr_cast;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;
        using phx::ref;

        escape %= escape_symbol;

        character %=   (no_case["\\x"] >> hex12)
                     | ("\\"  >> oct123)
                     | escape
                     | (print - (lit('"') | '\\'));

        unicode =   ("\\u" >> hex4[_val += utf8(_1)])
                  | ("\\U" >> hex8[_val += utf8(_1)]);

        string_section %= '"' >> *(unicode | character) >> '"';

        string %= string_section % omit[*space];

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

    boost::phoenix::function<utf8_f> utf8;
    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, String(), qi::space_type> start;
    qi::rule<Iterator, std::string()> escape;
    qi::uint_parser<char, 16, 1, 2> hex12;
    qi::uint_parser<uint16_t, 16, 4, 4> hex4;
    qi::uint_parser<uint32_t, 16, 8, 8> hex8;
    qi::uint_parser<char,  8, 1, 3> oct123;
    qi::rule<Iterator, std::string()> character;
    qi::rule<Iterator, std::string()> unicode;
    qi::rule<Iterator, std::string()> string_section;
    qi::rule<Iterator, std::string()> string;
};

}

#endif // __CORE_SPIRIT_STRING_LITERAL_HPP__