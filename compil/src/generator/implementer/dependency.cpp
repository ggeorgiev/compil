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

#include "implementer/dependency.h"

namespace compil
{

Dependency::Dependency(const std::string& headerPackage,
                       const std::string& headerName,
                       DependencyType type, 
                       DependencyLevel level,
                       DependencySection section,
                       const std::string& library)
    : mHeaderPackage(headerPackage)
    , mHeaderName(headerName)
    , mType(type)
    , mLevel(level)
    , mSection(section)
    , mLibrary(library)
{
}

Dependency::operator bool() const
{
    return mType != invalid_type;
}

bool Dependency::compare(const Dependency& d1, const Dependency& d2)
{
    if (d1.mSection < d2.mSection)
        return true;
    if (d1.mSection > d2.mSection)
        return false;
        
    if (d1.mLevel < d2.mLevel)
        return true;
    if (d1.mLevel > d2.mLevel)
        return false;
        
    if (d1.mLibrary < d2.mLibrary)
        return true;
    if (d1.mLibrary > d2.mLibrary)
        return false;
        
    if (d1.mHeaderPackage < d2.mHeaderPackage)
        return true;
    if (d1.mHeaderPackage > d2.mHeaderPackage)
        return false;

    if (d1.mHeaderName < d2.mHeaderName)
        return true;
    if (d1.mHeaderName > d2.mHeaderName)
        return false;
        
    if (d1.mType < d2.mType)
        return true;
    if (d1.mType > d2.mType)
        return false;
        
    return false;
}

}

