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

#include "generator/project/hook_source_provider.h"

#include "boost/algorithm/string.hpp"
#include "boost/make_shared.hpp"

#include <sstream>

namespace compil
{

HookSourceProvider::HookSourceProvider(const ISourceProviderSPtr& sourceProvider, const std::time_t& initTime)
    : mUpdateTime(initTime)
    , mBecauseOf("the generator")
    , mSourceProvider(sourceProvider)
{
}

HookSourceProvider::~HookSourceProvider()
{
}

SourceIdSPtr HookSourceProvider::sourceId(const SourceIdSPtr& pCurrentSourceId, const std::string& source)
{
    return mSourceProvider->sourceId(pCurrentSourceId, source);
}

StreamPtr HookSourceProvider::openInputStream(const SourceIdSPtr& pSourceId)
{
    std::time_t sourceTime = fileTime(pSourceId->value());
    if (mUpdateTime < sourceTime)
    {
        mBecauseOf = pSourceId->original();
        mUpdateTime = sourceTime;
    }
    return mSourceProvider->openInputStream(pSourceId);
}

void HookSourceProvider::setImportDirectories(const std::vector<boost::filesystem::path>& importDirectories)
{
    mSourceProvider->setImportDirectories(importDirectories);
}

boost::filesystem::path HookSourceProvider::workingDirectory()
{
    return mSourceProvider->workingDirectory();
}

void HookSourceProvider::setWorkingDirectory(const boost::filesystem::path& directory)
{
    return mSourceProvider->setWorkingDirectory(directory);
}

bool HookSourceProvider::isAbsolute(const boost::filesystem::path& file)
{
    return mSourceProvider->isAbsolute(file);
}

bool HookSourceProvider::isExists(const boost::filesystem::path& file)
{
    return mSourceProvider->isExists(file);
}

std::time_t HookSourceProvider::fileTime(const boost::filesystem::path& file)
{
    return mSourceProvider->fileTime(file);
}

boost::filesystem::path HookSourceProvider::directory(const boost::filesystem::path& file)
{
    return mSourceProvider->directory(file);
}

boost::filesystem::path HookSourceProvider::absolute(const boost::filesystem::path& file)
{
    return mSourceProvider->absolute(file);
}

std::time_t HookSourceProvider::getUpdateTime()
{
    return mUpdateTime;
}

std::string HookSourceProvider::getBecauseOf()
{
    return mBecauseOf;
}

}

