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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_NAME_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_NAME_COMPIL_H_

#include "destructor_name.h"
#include "method_name.h"

namespace cpp
{

namespace frm
{

class DestructorName : public MethodName
{
public:
                  DestructorName();
    explicit      DestructorName(const std::string& value);

    inline   bool operator==    (const DestructorName& rValue) const;
    inline   bool operator!=    (const DestructorName& rValue) const;
    inline   bool operator<     (const DestructorName& rValue) const;
};

inline DestructorNameSPtr destructorNameRef()
{
    return boost::make_shared<DestructorName>();
}

inline DestructorNameSPtr destructorNameRef(const std::string& value)
{
    return boost::make_shared<DestructorName>(value);
}

inline bool DestructorName::operator==(const DestructorName& rValue) const
{
    return value() == rValue.value();
}

inline bool DestructorName::operator!=(const DestructorName& rValue) const
{
    return value() != rValue.value();
}

inline bool DestructorName::operator<(const DestructorName& rValue) const
{
    return value() < rValue.value();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_NAME_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class DestructorName;
typedef DestructorName*                         DestructorNameRPtr;
typedef boost::shared_ptr<DestructorName>       DestructorNameSPtr;
typedef boost::shared_ptr<const DestructorName> DestructorNameSCPtr;
typedef boost::weak_ptr<DestructorName>         DestructorNameWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_NAME_COMPIL_H_

