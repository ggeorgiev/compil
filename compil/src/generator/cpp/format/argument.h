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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_ARGUMENT_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_ARGUMENT_COMPIL_H_

#include "argument.h"
#include "decorated_type.h"
#include "variable_name.h"

namespace cpp
{

namespace frm
{

class Argument
{
public:
    // Default constructor
                                     Argument  ();
    // Destructor
    /*lax*/                          ~Argument ();

    // Getter method for the data field type
            const DecoratedTypeSPtr& type      ()                              const;
    // Setter method for the data field type
            Argument&                set_type  (const DecoratedTypeSPtr& type);
    // Store operator for the data field type
            Argument&                operator<<(const DecoratedTypeSPtr& type);

    // Getter method for the data field name
            const VariableNameSPtr&  name      ()                              const;
    // Setter method for the data field name
            Argument&                set_name  (const VariableNameSPtr& name);
    // Store operator for the data field name
            Argument&                operator<<(const VariableNameSPtr& name);

private:
    // variable for the data field type
    DecoratedTypeSPtr mType;
    // variable for the data field name
    VariableNameSPtr  mName;
};

// Reference store operator for the data field type
const ArgumentSPtr& operator<<(const ArgumentSPtr& , const DecoratedTypeSPtr& );
// Reference store operator for the data field name
const ArgumentSPtr& operator<<(const ArgumentSPtr& , const VariableNameSPtr& );

inline ArgumentSPtr argumentRef()
{
    return boost::make_shared<Argument>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_ARGUMENT_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class Argument;
typedef Argument*                         ArgumentRPtr;
typedef boost::shared_ptr<Argument>       ArgumentSPtr;
typedef boost::shared_ptr<const Argument> ArgumentSCPtr;
typedef boost::weak_ptr<Argument>         ArgumentWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_ARGUMENT_COMPIL_H_

