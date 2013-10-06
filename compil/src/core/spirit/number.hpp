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

#ifndef __CORE_SPIRIT_NUMBER_HPP__
#define __CORE_SPIRIT_NUMBER_HPP__
#pragma once

#include "core/spirit/position.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/home/support/iterators/line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace compil
{

using namespace boost::spirit;

struct IntegerNumber : public Position
{
    IntegerNumber()
        : Position()
        , value(0)
        , source()
    {
    }

    int64_t value;
    std::string source;
};

template <typename Iterator>
struct source_integer : qi::grammar<Iterator, IntegerNumber(), qi::space_type>
{
    source_integer() : source_integer::base_type(start)
    {
        using qi::char_;
        using qi::long_long;
        using qi::raw;
        using qi::_val;
        using qi::_1;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;

        start = raw[ long_long [at_c<0>(_val) = _1]
                     - "-0" >> *char_
                   ]
                   [
                       at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                       at_c<2>(_val) = get_line_(begin(_1))
                   ]
        ;
    }

    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, IntegerNumber(), qi::space_type> start;
};

struct UIntegerNumber : public Position
{
    UIntegerNumber()
        : Position()
        , value(0)
        , source()
    {
    }

    uint64_t value;
    std::string source;
};

template <typename Iterator>
struct source_uinteger : qi::grammar<Iterator, UIntegerNumber(), qi::space_type>
{
    source_uinteger() : source_uinteger::base_type(start)
    {
        using qi::bin;
        using qi::oct;
        using qi::hex;
        using qi::ulong_long;
        using qi::raw;
        using qi::_val;
        using qi::_1;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;

        start = raw[
                       (qi::no_case["0x"] >> hex [at_c<0>(_val) = _1])
                     | ('0' >> oct [at_c<0>(_val) = _1])
                     | ulong_long [at_c<0>(_val) = _1]
                     | ('B' >> bin [at_c<0>(_val) = _1])
                   ]
                   [
                       at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                       at_c<2>(_val) = get_line_(begin(_1))
                   ]
        ;
    }

    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, UIntegerNumber(), qi::space_type> start;
};

struct DoubleNumber : public Position
{
    DoubleNumber()
        : Position()
        , value(0)
        , source()
    {
    }

    long double value;
    std::string source;
};

}

BOOST_FUSION_ADAPT_STRUCT(compil::IntegerNumber,
                            (int64_t,    value)
                            (std::string, source)
                            (size_t,      line)
                          )

BOOST_FUSION_ADAPT_STRUCT(compil::UIntegerNumber,
                            (uint64_t,    value)
                            (std::string, source)
                            (size_t,      line)
                          )

BOOST_FUSION_ADAPT_STRUCT(compil::DoubleNumber,
                            (long double, value)
                            (std::string, source)
                            (size_t,      line)
                          )

namespace compil
{

template <typename T>
struct strict_real_policies : qi::real_policies<T>
{
    static bool const allow_leading_dot = true;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot = true;
};

template <typename Iterator>
struct source_double : qi::grammar<Iterator, DoubleNumber(), qi::space_type>
{
    source_double() : source_double::base_type(start)
    {
        using qi::real_parser;
        real_parser<long double, strict_real_policies<long double> > long_double;

        using qi::raw;
        using qi::_val;
        using qi::_1;

        namespace phx = boost::phoenix;
        using phx::at_c;
        using phx::begin;
        using phx::end;
        using phx::construct;

        start = raw[ long_double [at_c<0>(_val) = _1] ]
                   [
                       at_c<1>(_val) = construct<std::string>(begin(_1), end(_1)),
                       at_c<2>(_val) = get_line_(begin(_1))
                   ]
        ;
    }

    boost::phoenix::function<get_line_f> get_line_;
    qi::rule<Iterator, DoubleNumber(), qi::space_type> start;
};

}

#endif // __CORE_SPIRIT_NUMBER_HPP__