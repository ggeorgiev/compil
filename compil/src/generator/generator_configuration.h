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

#ifndef _GENERATOR_CONFIGURATION_H__
#define _GENERATOR_CONFIGURATION_H__

#include "core/configuration/configuration.h"

class GeneratorConfiguration : public compil::Configuration
{
public:
    GeneratorConfiguration();
    virtual ~GeneratorConfiguration();

    static std::string staticName();

    virtual std::string name();

    void addCommonOptions(bpo::options_description& options);

    virtual bpo::options_description commandLineOptions();
    virtual std::string commandLineExtraPositionalOptions();

    virtual bpo::options_description configurationOptions();

    bool forceGeneration;
    bool ignoreTheGenerator;
    std::string doubleBufferDirectory;
    std::string type;
    std::string outputDirectory;
    bool flatOutput;
    std::string coreOutputDirectory;
    bool flatCoreOutput;
    std::string projectFile;
    std::string projectDirectory;
    string_vector importDirectories;

    string_vector sourceFiles;
};

typedef boost::shared_ptr<GeneratorConfiguration> GeneratorConfigurationPtr;
typedef boost::weak_ptr<GeneratorConfiguration> GeneratorConfigurationWPtr;

#else // _GENERATOR_CONFIGURATION_H__

class GeneratorConfiguration;
typedef boost::shared_ptr<GeneratorConfiguration> GeneratorConfigurationPtr;
typedef boost::weak_ptr<GeneratorConfiguration> GeneratorConfigurationWPtr;

#endif // _GENERATOR_CONFIGURATION_H__
