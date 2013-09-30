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

#ifndef _GENERATOR_PROJECT_H__
#define _GENERATOR_PROJECT_H__

#include "generator/c++/configuration/implementer_configuration.h"
#include "generator/c++/configuration/formatter_configuration.h"
#include "generator/c++/configuration/aligner_configuration.h"
#include "generator/generator.h"

#include "compiler/i_source_provider.h"

#include "language/compil/project/project.h"
#include "language/compil/document/document.h"

#include "core/boost/boost_path.h"

#include "boost/unordered_map.hpp"
#include "boost/unordered_set.hpp"
#include "boost/filesystem.hpp"

#include <vector>

namespace compil
{

struct SourceData
{
    std::time_t updateTime;
    std::string becauseOf;
    DocumentSPtr document;
};

typedef std::vector<std::string> string_vector;

class GeneratorProject
{
public:
    GeneratorProject(const ISourceProviderSPtr& sourceProvider);
    virtual ~GeneratorProject();

    bool init(const bool forceGeneration,
              const bool ignoreTheGenerator,
              const std::string& projectFile,
              const std::string& projectDirectory,
              const std::string& type,
              const string_vector& sourceFiles,
              const string_vector& importDirectories);

    bool parseDocuments();

    bool generate(const boost::filesystem::path& outputDirectory,
                  const bool flatOutput,
                  const boost::filesystem::path& outputCoreDirectory,
                  const bool flatCoreOutput,
                  const AlignerConfigurationSPtr& alignerConfiguration,
                  const FormatterConfigurationSPtr& formatterConfiguration,
                  const ImplementerConfigurationSPtr& implementerConfiguration);

    const boost::filesystem::path& projectDirectory() const;

private:
    bool executeGenerator(const std::string& type,
                          const FilePathSPtr& path,
                          const CppImplementer::EExtensionType& extensionType,
                          const boost::filesystem::path& outputDirectory,
                          const bool flatOutput,
                          const AlignerConfigurationSPtr& alignerConfiguration,
                          const FormatterConfigurationSPtr& formatterConfiguration,
                          const ImplementerConfigurationSPtr& implementerConfiguration,
                          Generator& generator);

    bool executeCoreGenerator(const std::string& name,
                              const CppImplementer::EExtensionType& extensionType,
                              const boost::filesystem::path& outputDirectory,
                              const bool flatCoreOutput,
                              const AlignerConfigurationSPtr& alignerConfiguration,
                              const FormatterConfigurationSPtr& formatterConfiguration,
                              const ImplementerConfigurationSPtr& implementerConfiguration,
                              Generator& generator);

    bool determineProjectPath(const std::string& projectFile,
                              const std::string& projectDirectory,
                              boost::filesystem::path& projectPath);

    ISourceProviderSPtr mSourceProvider;
    boost::filesystem::path mProjectDirectory;
    ProjectSPtr mProject;
    PackageSPtr mCorePackage;

    // this time is used as minimum modification time for all documents.
    // It is based on the time of the generator itself as well as the time
    // of config and other project initialization involved resources
    std::time_t mInitTime;

    // if true generates the files ignoring any logic for not to
    bool mForceGeneration;

    boost::unordered_map<boost::filesystem::path, SourceData> mDocuments;

    boost::unordered_set<std::string> mCoreDependencies;
};

}

#endif
