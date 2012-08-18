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

#ifndef _COMPIL_ISOURCEPROVIDER_H__
#define _COMPIL_ISOURCEPROVIDER_H__

#include "source_id.h"

#include <boost/shared_ptr.hpp>

#include <iostream>

typedef boost::shared_ptr<std::istream> StreamPtr;

namespace compil
{

class ISourceProvider
{
public:
    virtual ~ISourceProvider() {}
    
    // Determine unique source id. In the context of file system the
    // source provider will resolve the import source to absolute
    // path. Depending on the location of the file importing another
    // different source string could be resolved as the same source
    // and vise verse.
    virtual SourceIdSPtr sourceId(const SourceIdSPtr& pCurrentSourceId, const std::string& source) = 0;
    
    virtual StreamPtr openInputStream(const SourceIdSPtr& pSourceId) = 0;
    virtual std::string getUniquePresentationString(const std::string& source) = 0;
};

typedef boost::shared_ptr<ISourceProvider> ISourceProviderPtr;

}

#else

typedef boost::shared_ptr<std::istream> StreamPtr;

namespace compil
{

class ISourceProvider;
typedef boost::shared_ptr<ISourceProvider> ISourceProviderPtr;

}

#endif
