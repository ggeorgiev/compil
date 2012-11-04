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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_COMPIL_H_

#include "argument.h"
#include "function.h"
#include "function_name.h"
#include "type.h"

namespace cpp
{

namespace frm
{

class Function
{
public:
    // Default constructor
                                             Function         ();
    // Destructor
    /*lax*/                                  ~Function        ();

    // Getter method for the data field return
            const TypeSPtr&                  return_          ()                                           const;
    // Setter method for the data field return
            Function&                        set_return       (const TypeSPtr& return_);
    // Store operator for the data field return
            Function&                        operator<<       (const TypeSPtr& return_);

    // Getter method for the data field name
            const FunctionNameSPtr&          name             ()                                           const;
    // Setter method for the data field name
            Function&                        set_name         (const FunctionNameSPtr& name);
    // Store operator for the data field name
            Function&                        operator<<       (const FunctionNameSPtr& name);

    // Getter method for the data field arguments
            const std::vector<ArgumentSPtr>& arguments        ()                                           const;
    // Setter method for the data field arguments
            Function&                        set_arguments    (const std::vector<ArgumentSPtr>& arguments);
    // Provides mutable access to field arguments
            std::vector<ArgumentSPtr>&       mutable_arguments();
    // Store operator for the data field arguments
            Function&                        operator<<       (const std::vector<ArgumentSPtr>& arguments);
    // Store operator for an item of data field arguments
            Function&                        operator<<       (const ArgumentSPtr& argumentsItem);

private:
    // variable for the data field return
    TypeSPtr                  mReturn;
    // variable for the data field name
    FunctionNameSPtr          mName;
    // variable for the data field arguments
    std::vector<ArgumentSPtr> mArguments;
};

// Reference store operator for the data field return
const FunctionSPtr& operator<<(const FunctionSPtr& , const TypeSPtr& );
// Reference store operator for the data field name
const FunctionSPtr& operator<<(const FunctionSPtr& , const FunctionNameSPtr& );
// Reference store operator for the data field arguments
const FunctionSPtr& operator<<(const FunctionSPtr& , const std::vector<ArgumentSPtr>& );
// Reference store operator for an item of data field arguments
const FunctionSPtr& operator<<(const FunctionSPtr& , const ArgumentSPtr& );

inline FunctionSPtr functionRef()
{
    return boost::make_shared<Function>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class Function;
typedef Function*                         FunctionRPtr;
typedef boost::shared_ptr<Function>       FunctionSPtr;
typedef boost::shared_ptr<const Function> FunctionSCPtr;
typedef boost::weak_ptr<Function>         FunctionWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_FUNCTION_COMPIL_H_

