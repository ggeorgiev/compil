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

#include "boost/algorithm/string.hpp"

namespace compil
{

TestSourceProvider::TestSourceProvider()
{
}

TestSourceProvider::~TestSourceProvider()
{
}

SourceIdSPtr TestSourceProvider::sourceId(const SourceIdSPtr& pCurrentSourceId, const std::string& source)
{
    return SourceIdSPtr();
}

StreamPtr TestSourceProvider::openInputStream(const SourceIdSPtr& pSourceId)
{
    return StreamPtr();
}

bool TestSourceProvider::isAbsolute(const std::string& sourceLocation)
{
    return boost::starts_with(sourceLocation, "/");
}

bool TestSourceProvider::isExists(const std::string& sourceLocation)
{
    return mFilesystem.count(sourceLocation) != 0;
}

std::string TestSourceProvider::currentLocation()
{
    return mCurrentLocation;
}

void TestSourceProvider::setCurrentLocation(const std::string& currentLocation)
{
    mCurrentLocation = currentLocation;
}

void TestSourceProvider::addFile(const std::string& path, const std::string& test)
{
    mFilesystem[path] = test;
}

}

