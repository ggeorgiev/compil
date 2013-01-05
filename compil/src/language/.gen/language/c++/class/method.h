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

#ifndef __CPP_CLASS_METHOD_SCOMPIL_H_
#define __CPP_CLASS_METHOD_SCOMPIL_H_

#include "language/c++/class/class.h"
#include "language/c++/class/method.h"
#include "language/c++/class/method_name.h"

namespace lang
{

namespace cpp
{

class Method
{
public:
    // Default constructor
                                  Method    ();
    // Destructor
    /*lax*/                       ~Method   ();

    // Getter method for the data field name
            const MethodNameSPtr& name      ()                           const;
    // Setter method for the data field name
            Method&               set_name  (const MethodNameSPtr& name);
    // Store operator for the data field name
            Method&               operator<<(const MethodNameSPtr& name);

    // Getter method for the data field class
            const ClassWPtr&      class_    ()                           const;
    // Setter method for the data field class
            Method&               set_class (const ClassSPtr& class_);
    // Store operator for the data field class
            Method&               operator<<(const ClassSPtr& class_);

private:
    // variable for the data field name
    MethodNameSPtr mName;
    // variable for the data field class
    ClassWPtr      mClass;
};

// Reference store operator for the data field name
const MethodSPtr& operator<<(const MethodSPtr& , const MethodNameSPtr& );
// Reference store operator for the data field class
const MethodSPtr& operator<<(const MethodSPtr& , const ClassSPtr& );

inline MethodSPtr methodRef()
{
    return boost::make_shared<Method>();
}

}

}

#else // __CPP_CLASS_METHOD_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class Method;
typedef Method*                         MethodRPtr;
typedef boost::shared_ptr<Method>       MethodSPtr;
typedef boost::shared_ptr<const Method> MethodSCPtr;
typedef boost::weak_ptr<Method>         MethodWPtr;

}

}

#endif // __CPP_CLASS_METHOD_SCOMPIL_H_

