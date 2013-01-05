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

#ifndef __CPP_CLASS_OPERATOR_METHOD_NAME_SCOMPIL_H_
#define __CPP_CLASS_OPERATOR_METHOD_NAME_SCOMPIL_H_

#include "language/c++/class/method_name.h"
#include "language/c++/class/operator_method_name.h"
#include "language/c++/overloading/operator_function_id.h"

namespace lang
{

namespace cpp
{

class OperatorMethodName : public MethodName
{
public:
    // Default constructor
                                          OperatorMethodName ();
    // Destructor
    virtual                               ~OperatorMethodName();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  OperatorMethodNameSPtr        downcast           (const MethodNameSPtr& object);

    // Identifier for the objects from OperatorMethodName class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EMethodNameId                 staticMethodNameId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EMethodNameId                 runtimeMethodNameId()                                        const;

    // Getter method for the data field operator
            const OperatorFunctionIdSPtr& operator_          ()                                        const;
    // Setter method for the data field operator
            OperatorMethodName&           set_operator       (const OperatorFunctionIdSPtr& operator_);
    // Store operator for the data field operator
            OperatorMethodName&           operator<<         (const OperatorFunctionIdSPtr& operator_);

private:
    // variable for the data field operator
    OperatorFunctionIdSPtr mOperator;
};

// Reference store operator for the data field operator
const OperatorMethodNameSPtr& operator<<(const OperatorMethodNameSPtr& , const OperatorFunctionIdSPtr& );

inline OperatorMethodNameSPtr operatorMethodNameRef()
{
    return boost::make_shared<OperatorMethodName>();
}

}

}

#else // __CPP_CLASS_OPERATOR_METHOD_NAME_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class OperatorMethodName;
typedef OperatorMethodName*                         OperatorMethodNameRPtr;
typedef boost::shared_ptr<OperatorMethodName>       OperatorMethodNameSPtr;
typedef boost::shared_ptr<const OperatorMethodName> OperatorMethodNameSCPtr;
typedef boost::weak_ptr<OperatorMethodName>         OperatorMethodNameWPtr;

class EMethodNameId;

}

}

#endif // __CPP_CLASS_OPERATOR_METHOD_NAME_SCOMPIL_H_

