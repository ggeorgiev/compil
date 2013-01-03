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


#ifndef _TEST_SOURCE_PROVIDER_H__
#define _TEST_SOURCE_PROVIDER_H__

#include "i_source_provider.h"

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

namespace compil
{

class TestSourceProvider : public ISourceProvider
{
public:
    TestSourceProvider();
    virtual ~TestSourceProvider();

    virtual SourceIdSPtr sourceId(const SourceIdSPtr& pCurrentSourceId, const std::string& source);
    virtual StreamPtr openInputStream(const SourceIdSPtr& pSourceId);
    virtual void setImportDirectories(const std::vector<std::string>& importDirectories);

    virtual std::string workingDirectory();
    virtual void setWorkingDirectory(const std::string& directory);

    virtual bool isAbsolute(const std::string& sourceFile);
    virtual bool isExists(const std::string& sourceFile);

    virtual std::string directory(const std::string& sourceFile);
    virtual std::string absolute(const std::string& sourceFile);
    
    void file(const std::string& path, const std::string& test);

private:
    std::string getUniquePresentationString(const std::string& source);
    std::vector<PackageElementSPtr> getExternalElements(const std::string& source);
    void fillSourceFields(const std::string& source, SourceId::Builder& builder);

    std::string mWorkingDirectory;
    std::vector<std::string> mImportDirectories;
    boost::unordered_map<std::string, std::string> mFilesystem;
};

typedef boost::shared_ptr<TestSourceProvider> TestSourceProviderSPtr;

}

#else

namespace compil
{

class TestSourceProvider;
typedef boost::shared_ptr<TestSourceProvider> TestSourceProviderSPtr;

}

#endif

