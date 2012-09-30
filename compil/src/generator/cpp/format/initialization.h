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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_INITIALIZATION_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_INITIALIZATION_COMPIL_H_

#include "constructor_name.h"
#include "initialization.h"
#include "parameter_value.h"
#include "variable_name.h"

namespace cpp
{

namespace frm
{

class Initialization
{
public:
    // Default constructor
                                       Initialization     ();
    // Destructor
    /*lax*/                            ~Initialization    ();

    // Getter method for the data field constructorName
            const ConstructorNameSPtr& constructorName    ()                                           const;
    // Setter method for the data field constructorName
            Initialization&            set_constructorName(const ConstructorNameSPtr& constructorName);
    // Store operator for the data field constructorName
            Initialization&            operator<<         (const ConstructorNameSPtr& constructorName);

    // Getter method for the data field variableName
            const VariableNameSPtr&    variableName       ()                                           const;
    // Setter method for the data field variableName
            Initialization&            set_variableName   (const VariableNameSPtr& variableName);
    // Store operator for the data field variableName
            Initialization&            operator<<         (const VariableNameSPtr& variableName);

    // Getter method for the data field parameter
            const ParameterValueSPtr&  parameter          ()                                           const;
    // Setter method for the data field parameter
            Initialization&            set_parameter      (const ParameterValueSPtr& parameter);
    // Store operator for the data field parameter
            Initialization&            operator<<         (const ParameterValueSPtr& parameter);

private:
    // variable for the data field constructorName
    ConstructorNameSPtr mConstructorName;
    // variable for the data field variableName
    VariableNameSPtr    mVariableName;
    // variable for the data field parameter
    ParameterValueSPtr  mParameter;
};

// Reference store operator for the data field constructorName
const InitializationSPtr& operator<<(const InitializationSPtr& , const ConstructorNameSPtr& );
// Reference store operator for the data field variableName
const InitializationSPtr& operator<<(const InitializationSPtr& , const VariableNameSPtr& );
// Reference store operator for the data field parameter
const InitializationSPtr& operator<<(const InitializationSPtr& , const ParameterValueSPtr& );

inline InitializationSPtr initializationRef()
{
    return boost::make_shared<Initialization>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_INITIALIZATION_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class Initialization;
typedef Initialization*                         InitializationRPtr;
typedef boost::shared_ptr<Initialization>       InitializationSPtr;
typedef boost::shared_ptr<const Initialization> InitializationSCPtr;
typedef boost::weak_ptr<Initialization>         InitializationWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_INITIALIZATION_COMPIL_H_

