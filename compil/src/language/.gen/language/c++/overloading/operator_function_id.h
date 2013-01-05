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

#ifndef __CPP_OVERLOADING_OPERATOR_FUNCTION_ID_SCOMPIL_H_
#define __CPP_OVERLOADING_OPERATOR_FUNCTION_ID_SCOMPIL_H_

#include "language/c++/overloading/operator.h"
#include "language/c++/overloading/operator_function_id.h"

namespace lang
{

namespace cpp
{

class OperatorFunctionId
{
public:
    // Default constructor
                                OperatorFunctionId ();
    // Destructor
    /*lax*/                     ~OperatorFunctionId();

    // Getter method for the data field operator
            const EOperator&    operator_          ()                           const;
    // Setter method for the data field operator
            OperatorFunctionId& set_operator       (const EOperator& operator_);
    // Provides mutable access to field operator
            EOperator&          mutable_operator   ();
    // Store operator for the data field operator
            OperatorFunctionId& operator<<         (const EOperator& operator_);

private:
    // variable for the data field operator
    EOperator mOperator;
};

// Reference store operator for the data field operator
const OperatorFunctionIdSPtr& operator<<(const OperatorFunctionIdSPtr& , const EOperator& );

inline OperatorFunctionIdSPtr operatorFunctionIdRef()
{
    return boost::make_shared<OperatorFunctionId>();
}

}

}

#else // __CPP_OVERLOADING_OPERATOR_FUNCTION_ID_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class OperatorFunctionId;
typedef OperatorFunctionId*                         OperatorFunctionIdRPtr;
typedef boost::shared_ptr<OperatorFunctionId>       OperatorFunctionIdSPtr;
typedef boost::shared_ptr<const OperatorFunctionId> OperatorFunctionIdSCPtr;
typedef boost::weak_ptr<OperatorFunctionId>         OperatorFunctionIdWPtr;

}

}

#endif // __CPP_OVERLOADING_OPERATOR_FUNCTION_ID_SCOMPIL_H_

