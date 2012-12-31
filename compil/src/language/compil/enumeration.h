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
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// Standard Template Library
#include <vector>

#ifndef __LANGUAGE_COMPIL_ENUMERATION_COMPIL_H_
#define __LANGUAGE_COMPIL_ENUMERATION_COMPIL_H_

#include "compil/enumeration-partial.h"

namespace lang
{

namespace compil
{

class Enumeration : public EnumerationPartial
{
public:
    long getMinValue() const;
    long getMaxValue() const;

    virtual bool hasOperator(const EOperatorAction& action,
                             const EOperatorFlags& flags) const;
};

}

}

#else // __LANGUAGE_COMPIL_ENUMERATION_COMPIL_H_

namespace lang
{

namespace compil
{

class Enumeration;
typedef Enumeration*                         EnumerationRPtr;
typedef boost::shared_ptr<Enumeration>       EnumerationSPtr;
typedef boost::shared_ptr<const Enumeration> EnumerationSCPtr;
typedef boost::weak_ptr<Enumeration>         EnumerationWPtr;

}

}

#endif // __LANGUAGE_COMPIL_ENUMERATION_COMPIL_H_

