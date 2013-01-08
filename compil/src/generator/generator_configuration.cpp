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

#include "generator/generator_configuration.h"


GeneratorConfiguration::GeneratorConfiguration()
{
}

GeneratorConfiguration::~GeneratorConfiguration()
{
}

std::string GeneratorConfiguration::staticName()
{
    return "Generator";
}
    
std::string GeneratorConfiguration::name()
{
    return staticName();
}

void GeneratorConfiguration::addCommonOptions(bpo::options_description& options)
{
    options.add_options()
        ("output-directory,o", bpo::value<std::string>(&outputDirectory), "output directory")
        ("core-output-directory", bpo::value<std::string>(&coreOutputDirectory), "core output directory")
        ("project-file", bpo::value<std::string>(&projectFile), "project file")
        ("project-directory", bpo::value<std::string>(&projectDirectory), "project directory")
        ("import-path,I", bpo::value<string_vector>(&importDirectories)->composing(), "import compil path")
        ;
}

bpo::options_description GeneratorConfiguration::commandLineOptions()
{
    bpo::options_description options("Generation Configuration");
    options.add_options()
        ("type,t", bpo::value<std::string>(&type), "output type")
        ("source-file", bpo::value(&sourceFiles), "source compil file")
        ;
    addCommonOptions(options);
    return options;
}

std::string GeneratorConfiguration::commandLineExtraPositionalOptions()
{
    return "source-file";
}

bpo::options_description GeneratorConfiguration::configurationOptions()
{
    bpo::options_description options("Generation Configuration");
    addCommonOptions(options);
    return options;
}