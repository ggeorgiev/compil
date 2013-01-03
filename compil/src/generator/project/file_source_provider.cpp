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

#include "file_source_provider.h"
#include <fstream>

#include "boost_path_resolve.h"

#include "boost/make_shared.hpp"

namespace compil
{

using namespace boost;
using namespace filesystem;

FileSourceProvider::FileSourceProvider()
    : mWorkingDirectory(current_path().generic_string())
{
}

FileSourceProvider::~FileSourceProvider()
{
}

SourceIdSPtr FileSourceProvider::sourceId(const SourceIdSPtr& pCurrentSourceId, const std::string& source)
{
    SourceId::Builder builder;
    builder.set_original(source)
           .set_parent(pCurrentSourceId);

    // first check the current source location
    if (pCurrentSourceId)
    {
        path current(pCurrentSourceId->value());
        path current_location = current.remove_filename();
        path source_location = current_location / source;
        if (exists(source_location))
        {
            fillSourceFields(source_location.generic_string(), builder);
            return builder.finalize();
        }
    }

    path source_location = source;
    if (exists(source_location))
    {
        fillSourceFields(source_location.generic_string(), builder);
        return builder.finalize();
    }

    std::vector<path>::const_iterator it;
    for (it = mImportDirectories.begin(); it != mImportDirectories.end(); ++it)
    {
        path source_location = *it / source;
        if (exists(source_location))
        {
            fillSourceFields(source_location.generic_string(), builder);
            return builder.finalize();
        }
    }

    return SourceIdSPtr();
}

StreamPtr FileSourceProvider::openInputStream(const SourceIdSPtr& pSourceId)
{
    boost::shared_ptr<std::ifstream> pInput(new std::ifstream());
    pInput->open(pSourceId->value().c_str());
    return pInput;
}

void FileSourceProvider::setImportDirectories(const std::vector<std::string>& importDirectories)
{
    // TODO: importDirectories must be already absolute - this could be optimized here
    std::vector<std::string>::const_iterator it;
    for (it = importDirectories.begin(); it != importDirectories.end(); ++it)
    {
        path absolute_path(absolute(*it));
        mImportDirectories.push_back(absolute_path);
    }
}

std::string FileSourceProvider::workingDirectory()
{
    return mWorkingDirectory;
}

void FileSourceProvider::setWorkingDirectory(const std::string& directory)
{
    mWorkingDirectory = directory;
}

bool FileSourceProvider::isAbsolute(const std::string& sourceFile)
{
    return path(sourceFile).is_absolute();
}

bool FileSourceProvider::isExists(const std::string& sourceFile)
{
    return exists(path(sourceFile));
}

std::string FileSourceProvider::directory(const std::string& sourceFile)
{
    return path(sourceFile).parent_path().generic_string();
}

std::string FileSourceProvider::absolute(const std::string& sourceFile)
{
    if (isAbsolute(sourceFile))
        return sourceFile;
    return workingDirectory() + sourceFile;
}

std::string FileSourceProvider::getUniquePresentationString(const std::string& source)
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

std::vector<PackageElementSPtr> FileSourceProvider::getExternalElements(const std::string& source)
{
    path src_path = resolve(absolute(source));
    if (!is_directory(src_path))
        src_path = src_path.parent_path();

    std::vector<PackageElementSPtr> result;
    while (src_path.has_parent_path())
    {
        PackageElementSPtr pe = boost::make_shared<PackageElement>();
        pe->set_value(src_path.filename().string());

        result.insert(result.begin(), pe);
        src_path = src_path.parent_path();
    }

    return result;
}

void FileSourceProvider::fillSourceFields(const std::string& source, SourceId::Builder& builder)
{
    builder.set_value(source)
           .set_uniquePresentation(getUniquePresentationString(source))
           .set_externalElements(getExternalElements(source));
}

}

