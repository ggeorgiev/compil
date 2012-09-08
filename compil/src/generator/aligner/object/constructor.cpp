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

#include "constructor.h"


namespace compil
{

Constructor::Constructor()
{
}

Constructor::Constructor(const SimpleTypeSPtr& type)
    : mType(type)
{
}

Constructor::Constructor(const EMethodSpecifier& specifier, const SimpleTypeSPtr& type, const Argument& argument)
    : mSpecifier(specifier)
    , mType(type)
{
    mvArgument.push_back(argument);
}

Constructor::Constructor(const NamespaceSPtr& namespace_, const SimpleTypeSPtr& type)
    : mNamespace(namespace_)
    , mType(type)
{
}

Constructor::Constructor(const SimpleTypeSPtr& type, const Argument& argument)
    : mType(type)
{
    mvArgument.push_back(argument);
}

Constructor::Constructor(const NamespaceSPtr& namespace_, const SimpleTypeSPtr& type, const Argument& argument)
    : mNamespace(namespace_)
    , mType(type)
{
    mvArgument.push_back(argument);
}

Constructor::Constructor(const EMethodSpecifier& specifier, const NamespaceSPtr& namespace_, 
                         const SimpleTypeSPtr& type, const Argument& argument)
    : mSpecifier(specifier)
    , mNamespace(namespace_)
    , mType(type)
{
    mvArgument.push_back(argument);
}

Constructor::operator bool() const
{
    return (mNamespace && !mNamespace->isVoid()) || !mType->isVoid();
}

}
