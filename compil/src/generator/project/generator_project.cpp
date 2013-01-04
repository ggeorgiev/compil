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
#include "generator/project/hook_source_provider.h"
#include "generator/cpp/c++_generator.h"
#include "generator/cpp/c++_h_generator.h"
#include "generator/cpp/c++_test_generator.h"
#include "generator/implementer/c++_implementer.h"
#include "generator/formatter/c++_formatter.h"

#include "namespace_alias.h"

#include "compiler/parser.h"

#include "core/platform/application.h"

#include "boost/algorithm/string.hpp"
#include "boost/unordered_set.hpp"

#include <fstream>

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
                                            boost::filesystem::path& projectPath)
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

    projectPath = projectDirectory;
    projectPath /= projectFile;
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
    mInitTime = mSourceProvider->fileTime(plt::getApplicationPath().generic_string());

    std::vector<boost::filesystem::path> directories;
    for (string_vector::const_iterator it = importDirectories.begin(); it != importDirectories.end(); ++it)
    {
        boost::filesystem::path directory = mSourceProvider->absolute(*it);
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
        boost::filesystem::path projectPath;
        if (!determineProjectPath(projectFile, projectDirectory, projectPath))
            return false;
            
        projectPath = mSourceProvider->absolute(projectPath);
            
        if (sourceFiles.size() > 0)
        {
            std::cout << "WARNING: the project file is specified the source files will be loaded from it" << std::endl
                      << "         the provided source files will be ignored" << std::endl;
        }
        
        SourceId::Builder builder;
        builder.set_value(projectPath.generic_string());

        SourceIdSPtr sourceId = builder.finalize();
        StreamPtr pInput = mSourceProvider->openInputStream(sourceId);

        ParserPtr pParser = boost::make_shared<Parser>();
        if (!pParser->parseProject(sourceId, pInput, mProject))
            return false;
        
        mProjectDirectory = mSourceProvider->directory(projectPath);
        mSourceProvider->setWorkingDirectory(mProjectDirectory);
        return true;
    }
    
    mProjectDirectory = projectDirectory.empty()
                      ? mSourceProvider->workingDirectory()
                      : projectDirectory;
                      
    mProjectDirectory = mSourceProvider->absolute(mProjectDirectory);
    
    SectionSPtr section = (sectionRef() << (nameRef() << type));
    for (string_vector::const_iterator it = sourceFiles.begin(); it != sourceFiles.end(); ++it)
    {
        boost::filesystem::path file = mSourceProvider->absolute(*it);
        boost::filesystem::path relative = boost::filesystem::relative_path(mProjectDirectory, file);
        
        if (   mSourceProvider->isAbsolute(relative)
            || boost::starts_with(relative.generic_string(), ".."))
        {
            std::cout << "ERROR: the compil file: " << file << std::endl
                      << "       is not in the project directory: " << mProjectDirectory << std::endl;
            return false;
        }
        
        section << (filePathRef() << relative.generic_string());
    }
        
    mProject = (projectRef() << section);
    
    mSourceProvider->setWorkingDirectory(mProjectDirectory);
    return true;
}

const boost::filesystem::path& GeneratorProject::projectDirectory() const
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
    
    SourceIdSPtr parent;
    for (boost::unordered_set<std::string>::iterator it = files.begin(); it != files.end(); ++it)
    {
        const std::string& sourceFile = *it;
        ParserPtr parser = boost::make_shared<Parser>();
    
        DocumentSPtr document;
        SourceIdSPtr sourceId = mSourceProvider->sourceId(parent, sourceFile);
        if (!sourceId)
        {
            std::cout << "ERROR: the source compil file: " << sourceFile << std::endl;
            // TODO dump the list of the directories it looks into
            return false;
        }
        HookSourceProviderSPtr hook = boost::make_shared<HookSourceProvider>(mSourceProvider, mInitTime);
        
        if (!parser->parseDocument(hook, sourceId, document))
            return false;
            
        SourceData data;
        data.updateTime = hook->getUpdateTime();
        data.becauseOf = hook->getBecauseOf();
        data.document = document;
#if 0
        struct tm* ts = localtime(&data.updateTime);
        char cBuffer[128];
        strftime(cBuffer, sizeof(cBuffer), "%Y-%m-%d %H:%M:%S", ts);  
#endif
        mDocuments[sourceFile] = data;
    }
    return true;
}

static void closeStream(std::ofstream* pOutputStream)
{
    pOutputStream->flush();
    pOutputStream->close();
}

static boost::shared_ptr<std::ostream> openStream(const boost::filesystem::path& path)
{
    boost::filesystem::create_directories(path.parent_path());
    boost::shared_ptr<std::ofstream> pOutput(new std::ofstream(), &closeStream);
    pOutput->open(path.string().c_str());
    return pOutput;
}

static std::string getFileStem(const std::string& type, const std::string& documentName)
{
    if (type == "main")
        return documentName;
    return documentName + "-" + type;
}

bool GeneratorProject::generate(const boost::filesystem::path& outputDirectory,
                                const AlignerConfigurationSPtr& alignerConfiguration,
                                const FormatterConfigurationSPtr& formatterConfiguration,
                                const ImplementerConfigurationSPtr& implementerConfiguration)
{
    const std::vector<SectionSPtr>& sections = mProject->sections();
    for (std::vector<SectionSPtr>::const_iterator it = sections.begin(); it != sections.end(); ++it)
    {
        const SectionSPtr& section = *it;
        
        const std::string& type = section->name()->value();
        const std::vector<FilePathSPtr>& paths = section->paths();
        
        if (type == "main" || type == "partial")
        {
            for (std::vector<FilePathSPtr>::const_iterator pit = paths.begin(); pit != paths.end(); ++pit)
            {
                const FilePathSPtr& path = *pit;
                SourceData data = mDocuments[path->path()];
                
                {
                    CppFormatterPtr formatter = boost::make_shared<CppFormatter>
                        (formatterConfiguration, data.document->package());
                    CppImplementerPtr implementer = boost::make_shared<CppImplementer>
                        (implementerConfiguration, formatter);

                    boost::filesystem::path cppOutput = outputDirectory;
                    cppOutput /= getFileStem(type, data.document->name()->value()) + implementer->applicationExtension();
                    
                    if (   !mSourceProvider->isExists(cppOutput)
                        || (mSourceProvider->fileTime(cppOutput) <= data.updateTime))
                    {
                        std::cout << "#" << cppOutput.generic_string() << std::endl
                                  << "    because: " << data.becauseOf << std::endl;
                        boost::shared_ptr<std::ostream> outputStream = openStream(cppOutput);
                    
                        CppGenerator generator;
                        bool bResult = generator.init(type,
                                                      alignerConfiguration,
                                                      formatter,
                                                      implementer,
                                                      outputStream,
                                                      data.document);

                        if (bResult)
                            bResult = generator.generate();
                                                      
                        if (!bResult)
                        {
                            std::cout << "ERROR: the generation failed for: " << path->path() << std::endl;
                            return false;
                        }
                    }
                }
                
                {
                    CppFormatterPtr formatter = boost::make_shared<CppFormatter>
                        (formatterConfiguration, data.document->package());
                    CppImplementerPtr implementer = boost::make_shared<CppImplementer>
                        (implementerConfiguration, formatter);

                    boost::filesystem::path cppHeaderOutput = outputDirectory;
                    cppHeaderOutput /= getFileStem(type, data.document->name()->value()) + implementer->applicationHeaderExtension();
                    
                    if (   !mSourceProvider->isExists(cppHeaderOutput)
                        || (mSourceProvider->fileTime(cppHeaderOutput) <= data.updateTime))
                    {
                        std::cout << "#" << cppHeaderOutput.generic_string() << std::endl
                                  << "    because: " << data.becauseOf << std::endl;
                        boost::shared_ptr<std::ostream> outputStream = openStream(cppHeaderOutput);
                    
                        CppHeaderGenerator generator;
                        bool bResult = generator.init(type,
                                                      alignerConfiguration,
                                                      formatter,
                                                      implementer,
                                                      outputStream,
                                                      data.document);

                        if (bResult)
                            bResult = generator.generate();
                                                      
                        if (!bResult)
                        {
                            std::cout << "ERROR: the generation failed for: " << path->path() << std::endl;
                            return false;
                        }
                    }
                }
            }
        }
        
        if (type == "test")
        {
            for (std::vector<FilePathSPtr>::const_iterator pit = paths.begin(); pit != paths.end(); ++pit)
            {
                const FilePathSPtr& path = *pit;
                SourceData data = mDocuments[path->path()];

                CppFormatterPtr formatter = boost::make_shared<CppFormatter>
                    (formatterConfiguration, data.document->package());
                CppImplementerPtr implementer = boost::make_shared<CppImplementer>
                    (implementerConfiguration, formatter);

                boost::filesystem::path cppTestOutput = outputDirectory;
                cppTestOutput /= getFileStem(type, data.document->name()->value()) + implementer->applicationExtension();
                
                if (   !mSourceProvider->isExists(cppTestOutput)
                    || (mSourceProvider->fileTime(cppTestOutput) <= data.updateTime))
                {
                    std::cout << "#" << cppTestOutput.generic_string() << std::endl
                              << "    because: " << data.becauseOf << std::endl;
                    boost::shared_ptr<std::ostream> outputStream = openStream(cppTestOutput);
                
                    CppTestGenerator generator;
                    bool bResult = generator.init(type,
                                                  alignerConfiguration,
                                                  formatter,
                                                  implementer,
                                                  outputStream,
                                                  data.document);

                    if (bResult)
                        bResult = generator.generate();
                                                  
                    if (!bResult)
                    {
                        std::cout << "ERROR: the generation failed for: " << path->path() << std::endl;
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

}
