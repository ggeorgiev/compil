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

#ifndef _HOOK_SOURCE_PROVIDER_H__
#define _HOOK_SOURCE_PROVIDER_H__

#include "compiler/i_source_provider.h"

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

namespace compil
{

class HookSourceProvider : public ISourceProvider
{
public:
    HookSourceProvider(const ISourceProviderSPtr& sourceProvider, const std::time_t& initTime);
    virtual ~HookSourceProvider();

    virtual SourceIdSPtr sourceId(const SourceIdSPtr& pCurrentSourceId, const std::string& source);
    virtual StreamPtr openInputStream(const SourceIdSPtr& pSourceId);
    virtual void setImportDirectories(const std::vector<boost::filesystem::path>& importDirectories);

    virtual boost::filesystem::path workingDirectory();
    virtual void setWorkingDirectory(const boost::filesystem::path& directory);

    virtual bool isAbsolute(const boost::filesystem::path& file);
    virtual bool isExists(const boost::filesystem::path& file);
    virtual std::time_t fileTime(const boost::filesystem::path& file);

    virtual boost::filesystem::path directory(const boost::filesystem::path& file);
    virtual boost::filesystem::path absolute(const boost::filesystem::path& file);
    
    std::time_t getUpdateTime();
    std::string getBecauseOf();

private:
    std::time_t mUpdateTime;
    std::string mBecauseOf;
    ISourceProviderSPtr mSourceProvider;
};

typedef boost::shared_ptr<HookSourceProvider> HookSourceProviderSPtr;

}

#endif
