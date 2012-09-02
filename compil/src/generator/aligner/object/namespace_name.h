// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * The name of George Georgiev can not be used to endorse or
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

// Boost C++ Smart Pointers
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// Standard Template Library
#include <string>

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_NAME_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_NAME_COMPIL_H_

#include "namespace_name.h"

class NamespaceName
{
public:
                         NamespaceName();
    explicit             NamespaceName(const std::string& value);

    inline   std::string value        ()                            const;
    inline   bool        operator==   (const NamespaceName& rValue) const;
    inline   bool        operator!=   (const NamespaceName& rValue) const;
    inline   bool        operator<    (const NamespaceName& rValue) const;
private:
    std::string mValue;
};

inline NamespaceNameSPtr namespaceNameRef()
{
    return boost::make_shared<NamespaceName>();
}

inline NamespaceNameSPtr namespaceNameRef(const std::string& value)
{
    return boost::make_shared<NamespaceName>(value);
}

inline std::string NamespaceName::value() const
{
    return mValue;
}

inline bool NamespaceName::operator==(const NamespaceName& rValue) const
{
    return mValue == rValue.mValue;
}

inline bool NamespaceName::operator!=(const NamespaceName& rValue) const
{
    return mValue != rValue.mValue;
}

inline bool NamespaceName::operator<(const NamespaceName& rValue) const
{
    return mValue < rValue.mValue;
}

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_NAME_COMPIL_H_

// Forward declarations
class NamespaceName;
typedef NamespaceName*                         NamespaceNameRPtr;
typedef boost::shared_ptr<NamespaceName>       NamespaceNameSPtr;
typedef boost::shared_ptr<const NamespaceName> NamespaceNameSCPtr;
typedef boost::weak_ptr<NamespaceName>         NamespaceNameWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_NAME_COMPIL_H_

