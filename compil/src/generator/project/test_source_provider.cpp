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

#include "test_source_provider.h"

#include <boost/filesystem.hpp>
#include "boost/algorithm/string.hpp"
#include "boost/make_shared.hpp"

#include <sstream>

namespace compil
{

TestSourceProvider::TestSourceProvider()
    : mWorkingDirectory("/")
{
}

TestSourceProvider::~TestSourceProvider()
{
}

SourceIdSPtr TestSourceProvider::sourceId(const SourceIdSPtr& pCurrentSourceId, const std::string& source)
{
    SourceId::Builder builder;
    builder.set_original(source)
           .set_parent(pCurrentSourceId);

    // first check the current source location
    if (pCurrentSourceId)
    {
        std::string current_location = directory(pCurrentSourceId->value());
        std::string source_location = current_location + source;
        if (isExists(source_location))
        {
            fillSourceFields(source_location, builder);
            return builder.finalize();
        }
    }
    
    std::string source_location = mWorkingDirectory + source;
    if (isExists(source_location))
    {
        fillSourceFields(source_location, builder);
        return builder.finalize();
    }

    std::vector<std::string>::const_iterator it;
    for (it = mImportDirectories.begin(); it != mImportDirectories.end(); ++it)
    {
        std::string source_location = *it + source;
        if (isExists(source_location))
        {
            fillSourceFields(source_location, builder);
            return builder.finalize();
        }
    }

    return SourceIdSPtr();
}

StreamPtr TestSourceProvider::openInputStream(const SourceIdSPtr& pSourceId)
{
    boost::shared_ptr<std::istringstream> pInput =
        boost::make_shared<std::istringstream>(mFilesystem[pSourceId->value()]);
    return pInput;
}

void TestSourceProvider::setImportDirectories(const std::vector<std::string>& importDirectories)
{
    mImportDirectories = importDirectories;
}

std::string TestSourceProvider::workingDirectory()
{
    return mWorkingDirectory;
}

void TestSourceProvider::setWorkingDirectory(const std::string& directory)
{
    mWorkingDirectory = directory;
}

bool TestSourceProvider::isAbsolute(const std::string& sourceFile)
{
    return boost::starts_with(sourceFile, "/");
}

bool TestSourceProvider::isExists(const std::string& sourceFile)
{
    return mFilesystem.count(sourceFile) != 0;
}

std::time_t TestSourceProvider::fileTime(const std::string& sourceFile)
{
    return 0;
}

std::string TestSourceProvider::directory(const std::string& sourceFile)
{
    size_t slashIdx = sourceFile.find_last_of("/");
    if (slashIdx == std::string::npos)
        return "";

    return sourceFile.substr(0, slashIdx + 1);
}

std::string TestSourceProvider::absolute(const std::string& sourceFile)
{
    if (isAbsolute(sourceFile))
        return sourceFile;
    return workingDirectory() + sourceFile;
}

void TestSourceProvider::file(const std::string& path, const std::string& test)
{
    mFilesystem[path] = test;
}

using namespace boost;
using namespace filesystem;

std::string TestSourceProvider::getUniquePresentationString(const std::string& source)
{
    path src_path = absolute(source);
    path root = workingDirectory();

    path::iterator i = src_path.begin();
    for (path::iterator it = root.begin(); it != root.end(); ++it)
    {
        if (*i != *it)
            break;

        ++i;
        if (i == src_path.end())
            break;
    }

    std::string result;
    while (i != src_path.end())
    {
        if (!result.empty())
            result += "_";
        result += i->string();
        ++i;
    }
    return result;
}

std::vector<PackageElementSPtr> TestSourceProvider::getExternalElements(const std::string& source)
{
    std::vector<PackageElementSPtr> result;
    return result;
}

void TestSourceProvider::fillSourceFields(const std::string& source, SourceId::Builder& builder)
{
    builder.set_value(source)
           .set_uniquePresentation(getUniquePresentationString(source))
           .set_externalElements(getExternalElements(source));
}

}

