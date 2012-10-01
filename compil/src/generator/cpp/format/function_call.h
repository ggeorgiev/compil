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
#include <vector>

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_CALL_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_CALL_COMPIL_H_

#include "function_call.h"
#include "function_name.h"
#include "namespace.h"
#include "parameter_value.h"

namespace cpp
{

namespace frm
{

class FunctionCall
{
public:
    // Default constructor
                                                   FunctionCall      ();
    // Destructor
    /*lax*/                                        ~FunctionCall     ();

    // Getter method for the data field namespace
            const NamespaceSPtr&                   namespace_        ()                                                  const;
    // Setter method for the data field namespace
            FunctionCall&                          set_namespace     (const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            FunctionCall&                          operator<<        (const NamespaceSPtr& namespace_);

    // Getter method for the data field name
            const FunctionNameSPtr&                name              ()                                                  const;
    // Setter method for the data field name
            FunctionCall&                          set_name          (const FunctionNameSPtr& name);
    // Store operator for the data field name
            FunctionCall&                          operator<<        (const FunctionNameSPtr& name);

    // Getter method for the data field parameters
            const std::vector<ParameterValueSPtr>& parameters        ()                                                  const;
    // Setter method for the data field parameters
            FunctionCall&                          set_parameters    (const std::vector<ParameterValueSPtr>& parameters);
    // Provides mutable access to field parameters
            std::vector<ParameterValueSPtr>&       mutable_parameters();
    // Store operator for the data field parameters
            FunctionCall&                          operator<<        (const std::vector<ParameterValueSPtr>& parameters);
    // Store operator for an item of data field parameters
            FunctionCall&                          operator<<        (const ParameterValueSPtr& parametersItem);

private:
    // variable for the data field namespace
    NamespaceSPtr                   mNamespace;
    // variable for the data field name
    FunctionNameSPtr                mName;
    // variable for the data field parameters
    std::vector<ParameterValueSPtr> mParameters;
};

// Reference store operator for the data field namespace
const FunctionCallSPtr& operator<<(const FunctionCallSPtr& , const NamespaceSPtr& );
// Reference store operator for the data field name
const FunctionCallSPtr& operator<<(const FunctionCallSPtr& , const FunctionNameSPtr& );
// Reference store operator for the data field parameters
const FunctionCallSPtr& operator<<(const FunctionCallSPtr& , const std::vector<ParameterValueSPtr>& );
// Reference store operator for an item of data field parameters
const FunctionCallSPtr& operator<<(const FunctionCallSPtr& , const ParameterValueSPtr& );

inline FunctionCallSPtr functionCallRef()
{
    return boost::make_shared<FunctionCall>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_CALL_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class FunctionCall;
typedef FunctionCall*                         FunctionCallRPtr;
typedef boost::shared_ptr<FunctionCall>       FunctionCallSPtr;
typedef boost::shared_ptr<const FunctionCall> FunctionCallSCPtr;
typedef boost::weak_ptr<FunctionCall>         FunctionCallWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_CALL_COMPIL_H_

