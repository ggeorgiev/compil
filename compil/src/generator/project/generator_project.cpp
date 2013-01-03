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

#include "generator/project/generator_project.h"
#include "namespace_alias.h"

#include "compiler/parser.h"

#include "boost/algorithm/string.hpp"
#include "boost/unordered_set.hpp"

namespace compil
{

GeneratorProject::GeneratorProject(const ISourceProviderSPtr& sourceProvider)
    : mSourceProvider(sourceProvider)
{
}

GeneratorProject::~GeneratorProject()
{
}

bool GeneratorProject::determineProjectPath(const std::string& projectFile,
                                            const std::string& projectDirectory,
                                            std::string& projectPath)
{
    if (mSourceProvider->isAbsolute(projectFile))
    {
        if (!mSourceProvider->isExists(projectFile))
        {
            std::cout << "the project file not found: " << projectFile << std::endl;
            return false;
        }
        
        if (!projectDirectory.empty())
        {
            std::cout << "the project directory will be based on the project file" << std::endl
                      << "the specified oriject directory will be ignored" << std::endl;
        }
        
        projectPath = projectFile;
        return true;
    }

    projectPath = projectDirectory + projectFile;
    if (mSourceProvider->isExists(projectPath))
        return true;

    return false;
}

bool GeneratorProject::init(const std::string& projectFile,
                            const std::string& projectDirectory,
                            const std::string& type,
                            const string_vector& sourceFiles,
                            const string_vector& importDirectories)
{
    string_vector directories;
    for (string_vector::const_iterator it = importDirectories.begin(); it != importDirectories.end(); ++it)
    {
        std::string directory = mSourceProvider->absolute(*it);
        if (!mSourceProvider->isExists(directory))
        {
            std::cout << "WARNING: the import directory: " << *it << std::endl
                      << "         does not exist" << std::endl;
            continue;
        }
        directories.push_back(directory);
    }
    mSourceProvider->setImportDirectories(directories);

    if (!projectFile.empty())
    {
        std::string projectPath;
        if (!determineProjectPath(projectFile, projectDirectory, projectPath))
            return false;
            
        projectPath = mSourceProvider->absolute(projectPath);
            
        if (sourceFiles.size() > 0)
        {
            std::cout << "WARNING: the project file is specified the source files will be loaded from it" << std::endl
                      << "         the provided source files will be ignored" << std::endl;
        }
        
        SourceId::Builder builder;
        builder.set_value(projectPath);

        SourceIdSPtr sourceId = builder.finalize();
        StreamPtr pInput = mSourceProvider->openInputStream(sourceId);

        ParserPtr pParser = boost::make_shared<Parser>();
        if (!pParser->parseProject(sourceId, pInput, mProject))
            return false;
        
        mProjectDirectory = mSourceProvider->directory(projectPath);
        return true;
    }
    
    mProjectDirectory = projectDirectory.empty()
                      ? mSourceProvider->workingDirectory()
                      : projectDirectory;
                      
    mProjectDirectory = mSourceProvider->absolute(mProjectDirectory);
    
    SectionSPtr section = (sectionRef() << (nameRef() << type));
    for (string_vector::const_iterator it = sourceFiles.begin(); it != sourceFiles.end(); ++it)
    {
        std::string file = mSourceProvider->absolute(*it);
        if (!boost::starts_with(file, mProjectDirectory))
        {
            std::cout << "the compil file: " << file << std::endl
                      << "is not in the project directory: " << mProjectDirectory << std::endl;
            return false;
        }
        
        section << (filePathRef() << file.substr(mProjectDirectory.length() + 1));
    }
        
    mProject = (projectRef() << section);
    return true;
}

const std::string& GeneratorProject::projectDirectory() const
{
    return mProjectDirectory;
}

bool GeneratorProject::parseDocuments()
{
    boost::unordered_set<std::string> files;
    
    const std::vector<SectionSPtr>& sections = mProject->sections();
    for (std::vector<SectionSPtr>::const_iterator it = sections.begin(); it != sections.end(); ++it)
    {
        const SectionSPtr& section = *it;
        const std::vector<FilePathSPtr>& paths = section->paths();
        
        for (std::vector<FilePathSPtr>::const_iterator pit = paths.begin(); pit != paths.end(); ++pit)
        {
            const FilePathSPtr& path = *pit;
            files.insert(path->path());
        }
    }
    
    for (boost::unordered_set<std::string>::iterator it = files.begin(); it != files.end(); ++it)
    {
        
        
        
    }
    return true;
}

}
