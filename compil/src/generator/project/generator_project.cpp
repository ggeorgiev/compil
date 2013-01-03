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

namespace compil
{

GeneratorProject::GeneratorProject(const ISourceProviderPtr& sourceProvider)
    : mSourceProvider(sourceProvider)
{
}

GeneratorProject::~GeneratorProject()
{
}

bool GeneratorProject::init(const std::string& projectFile,
                            const std::string& projectDirectory,
                            const string_vector& sourceFiles)
{
    if (!projectFile.empty())
    {
        if (sourceFiles.size() > 0)
        {
            std::cout << "the project file is specified the source files will be loaded from it" << std::endl
                      << "the provided source files will be ignored" << std::endl;
        }
    }

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
        
        mProjectPath = projectFile;
        return true;
    }

    std::string projectPath = projectDirectory + projectFile;
    if (mSourceProvider->isExists(projectPath))
    {
        mProjectPath = projectPath;
        return true;
    }
    
    return false;
}

const std::string& GeneratorProject::projectPath() const
{
    return mProjectPath;
}



}

