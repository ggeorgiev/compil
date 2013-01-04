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

#ifndef _ALIGNER_CONFIGURATION_H__
#define _ALIGNER_CONFIGURATION_H__

#include "configuration/configuration.h"

class AlignerConfiguration : public compil::Configuration
{
public:
    AlignerConfiguration();
    virtual ~AlignerConfiguration();
    
    static std::string staticName();
    
    virtual std::string name();
    
    void addCommonOptions(bpo::options_description& options);
    virtual bpo::options_description commandLineOptions();
    virtual bpo::options_description configurationOptions();


    enum EDecoration
    {
        invalid_decoration = 0,
        part_of_the_type,
        part_of_the_name,
        next_to_the_name
    };
    
    EDecoration mDecoration;
    
    enum EAlignment
    {
        invalid_alignment = 0,
        tabs_only,
        spaces_only,
        smart_tabs
    };

    EAlignment mAlignment;
    
    int mTabSize;

    bool mFunctionSpace;
    bool mFunctionTypeOnNewLine;
    bool mOpenBlockOnNewLine;
    
    int mColumnWidthLimit;
    int mCommentColumnWidthLimit;
};

typedef boost::shared_ptr<AlignerConfiguration> AlignerConfigurationSPtr;
typedef boost::weak_ptr<AlignerConfiguration> AlignerConfigurationWPtr;

#else

class AlignerConfiguration;
typedef boost::shared_ptr<AlignerConfiguration> AlignerConfigurationSPtr;
typedef boost::weak_ptr<AlignerConfiguration> AlignerConfigurationWPtr;

#endif

