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

#include "generator/c++/configuration/implementer_configuration.h"

#include "boost/algorithm/string.hpp"

ImplementerConfiguration::ImplementerConfiguration()
    : applicationCppExtension(use_cpp)
    , applicationCppHeaderExtension(use_h)
    , mCppIncludePath(include_path_based_on_import)
    , mFlagsEnumeration(flags_enumeration_use_core_template)
    , mIntegerTypes(use_native)
    , mNullOr0(use_null)
    , mString(use_stl_string)
    , mPointer(use_boost_pointers)
    , mAssert(use_boost_assert)
{
}

ImplementerConfiguration::~ImplementerConfiguration()
{
}

std::string ImplementerConfiguration::staticName()
{
    return "Implementer";
}
    
std::string ImplementerConfiguration::name()
{
    return staticName();
}

void validate(boost::any& v, 
              const std::vector<std::string>& values,
              ImplementerConfiguration::ECppIncludePath* target_type, int)
{
    // Make sure no previous assignment to 'a' was made.
    boost::program_options::validators::check_first_occurrence(v);
    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    const std::string& s = boost::program_options::validators::get_single_string(values);
    
    if (boost::iequals(s, "include_path_based_on_import"))
    {
        v = boost::any(ImplementerConfiguration::include_path_based_on_import);
    }
    else if (boost::iequals(s, "include_path_based_on_package"))
    {
        v = boost::any(ImplementerConfiguration::include_path_based_on_package);
    }
    else
    {
        throw boost::program_options::validation_error(
                  boost::program_options::validation_error::invalid_option_value);
    }
}

void ImplementerConfiguration::addCommonOptions(bpo::options_description& options)
{
    options.add_options()
        
        ("core_package",     bpo::value<std::string>(&corePackage),
                             "package of the core")
        ("cpp.include_path", bpo::value<ECppIncludePath>(&mCppIncludePath),
                             "how to form cpp include paths")
        ;
}

bpo::options_description ImplementerConfiguration::commandLineOptions()
{
    bpo::options_description options("Implementer Configuration");
    addCommonOptions(options);
    return options;
}

bpo::options_description ImplementerConfiguration::configurationOptions()
{
    bpo::options_description options("Implementer Configuration");
    addCommonOptions(options);
    return options;
}