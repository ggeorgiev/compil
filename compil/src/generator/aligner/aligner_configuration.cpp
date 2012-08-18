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

#include "aligner_configuration.h"

AlignerConfiguration::AlignerConfiguration()
        : mDecoration(part_of_the_type)
        , mAlignment(spaces_only)
        , mTabSize(4)
        , mFunctionSpace(false)
        , mFunctionTypeOnNewLine(false)
        , mOpenBlockOnNewLine(true)
        , mColumnWidthLimit(120)
        , mCommentColumnWidthLimit(75)
{
}

AlignerConfiguration::~AlignerConfiguration()
{
}

std::string AlignerConfiguration::staticName()
{
    return "Aligner";
}
    
std::string AlignerConfiguration::name()
{
    return staticName();
}

static std::istream& operator>>(std::istream& in, AlignerConfiguration::EDecoration& decoration)
{
    std::string token;
    in >> token;
    if (token == "part_of_the_type")
        decoration = AlignerConfiguration::part_of_the_type;
    else if (token == "part_of_the_name")
        decoration = AlignerConfiguration::part_of_the_name;
    else if (token == "next_to_the_name")
        decoration = AlignerConfiguration::next_to_the_name;
    //else 
    //    throw boost::program_options::validation_error("Invalid unit");
    return in;
}

void AlignerConfiguration::addCommonOptions(bpo::options_description& options)
{
    options.add_options()
        ("aligner.decoration,v", bpo::value(&mDecoration)->default_value(part_of_the_type), "decoration")
        ;
}

bpo::options_description AlignerConfiguration::commandLineOptions()
{
    bpo::options_description options("General options");
    addCommonOptions(options);
    return options;
}

bpo::options_description AlignerConfiguration::configurationOptions()
{
    bpo::options_description options("Generation Configuration");
    addCommonOptions(options);
    return options;
}
