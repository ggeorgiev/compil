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

#include <boost/shared_ptr.hpp>

#ifndef _IMPLEMENTER_CONFIGURATION_H__
#define _IMPLEMENTER_CONFIGURATION_H__

#include "configuration.h"

class ImplementerConfiguration : public compil::Configuration
{
public:
    ImplementerConfiguration();
    virtual ~ImplementerConfiguration();
    
    static std::string staticName();
    
    virtual std::string name();
    
    void addCommonOptions(bpo::options_description& options);
    virtual bpo::options_description commandLineOptions();
    virtual bpo::options_description configurationOptions();
    
    enum ECppExtension
    {
        invalid_cpp_extension = 0,
        use_cpp,
        use_cxx,
    };
    
    ECppExtension applicationCppExtension;
    ECppExtension coreCppExtension;

    enum ECppHeaderExtension
    {
        invalid_cpp_header_extension = 0,
        use_h,
        use_hpp,
    };
    
    ECppHeaderExtension applicationCppHeaderExtension;
    ECppHeaderExtension coreCppHeaderExtension;
    
    enum ECppIncludePath
    {
        invalid_cpp_include_path = 0,
        include_path_based_on_import,
        include_path_based_on_package,
    } mCppIncludePath;
    
    std::string corePackage;
    
    enum FlagsEnumeration
    {
        invalid_flags_enumeration = 0,
        flags_enumeration_inline_implementation,
        flags_enumeration_use_core_template,
    } mFlagsEnumeration;
    
    enum IntegerTypes
    {
        invalid_integer_types = 0,
        use_native,
        use_intnn_t,
        use_boost_intnn_t
    } mIntegerTypes;
    
    enum NULL_or_0
    {
        invalid_null_or_0 = 0,
        use_null,
        use_0
    } mNullOr0;
    
    enum String
    {
        ivalid_string = 0,
        use_char_pointer,
        use_stl_string
    } mString;
    
    enum Pointer
    {
        invalid_pointer = 0,
        use_raw_pointers,
        use_boost_pointers
    } mPointer;
    
    enum EAssert
    {
        invalid_assert = 0,
        use_std_assert,
        use_boost_assert
    } mAssert;
};

typedef boost::shared_ptr<ImplementerConfiguration> ImplementerConfigurationSPtr;
typedef boost::weak_ptr<ImplementerConfiguration> ImplementerConfigurationWPtr;

#else

class ImplementerConfiguration;
typedef boost::shared_ptr<ImplementerConfiguration> ImplementerConfigurationSPtr;
typedef boost::weak_ptr<ImplementerConfiguration> ImplementerConfigurationWPtr;

#endif

