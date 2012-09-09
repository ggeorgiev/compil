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

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_CONSTRUCTOR_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_CONSTRUCTOR_COMPIL_H_

#include "argument.h"
#include "constructor.h"
#include "constructor_name.h"
#include "constructor_specifier.h"
#include "namespace.h"

class Constructor
{
public:
    // Default constructor
                                             Constructor      ();
    // Destructor
    /*lax*/                                  ~Constructor     ();

    // Getter method for the data field specifier
            const EConstructorSpecifier&     specifier        ()                                const;
    // Setter method for the data field specifier
            Constructor&                     set_specifier    (const EConstructorSpecifier&     specifier);
    // Provides mutable access to field specifier
            EConstructorSpecifier&           mutable_specifier();
    // Store operator for the data field specifier
            Constructor&                     operator<<       (const EConstructorSpecifier&     specifier);

    // Getter method for the data field namespace
            const NamespaceSPtr&             namespace_       ()                                const;
    // Setter method for the data field namespace
            Constructor&                     set_namespace    (const NamespaceSPtr&             namespace_);
    // Store operator for the data field namespace
            Constructor&                     operator<<       (const NamespaceSPtr&             namespace_);

    // Getter method for the data field name
            const ConstructorNameSPtr&       name             ()                                const;
    // Setter method for the data field name
            Constructor&                     set_name         (const ConstructorNameSPtr&       name);
    // Store operator for the data field name
            Constructor&                     operator<<       (const ConstructorNameSPtr&       name);

    // Getter method for the data field arguments
            const std::vector<ArgumentSPtr>& arguments        ()                                const;
    // Setter method for the data field arguments
            Constructor&                     set_arguments    (const std::vector<ArgumentSPtr>& arguments);
    // Provides mutable access to field arguments
            std::vector<ArgumentSPtr>&       mutable_arguments();
    // Store operator for the data field arguments
            Constructor&                     operator<<       (const std::vector<ArgumentSPtr>& arguments);
    // Store operator for an item of data field arguments
            Constructor&                     operator<<       (const ArgumentSPtr&              argumentsItem);

private:
    // variable for the data field specifier
    EConstructorSpecifier     mSpecifier;
    // variable for the data field namespace
    NamespaceSPtr             mNamespace;
    // variable for the data field name
    ConstructorNameSPtr       mName;
    // variable for the data field arguments
    std::vector<ArgumentSPtr> mArguments;
};

// Reference store operator for the data field specifier
const ConstructorSPtr& operator<<(const ConstructorSPtr& , const EConstructorSpecifier&     );
// Reference store operator for the data field namespace
const ConstructorSPtr& operator<<(const ConstructorSPtr& , const NamespaceSPtr&             );
// Reference store operator for the data field name
const ConstructorSPtr& operator<<(const ConstructorSPtr& , const ConstructorNameSPtr&       );
// Reference store operator for the data field arguments
const ConstructorSPtr& operator<<(const ConstructorSPtr& , const std::vector<ArgumentSPtr>& );
// Reference store operator for an item of data field arguments
const ConstructorSPtr& operator<<(const ConstructorSPtr& , const ArgumentSPtr&              );

inline ConstructorSPtr constructorRef()
{
    return boost::make_shared<Constructor>();
}

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_CONSTRUCTOR_COMPIL_H_

// Forward declarations
class Constructor;
typedef Constructor*                         ConstructorRPtr;
typedef boost::shared_ptr<Constructor>       ConstructorSPtr;
typedef boost::shared_ptr<const Constructor> ConstructorSCPtr;
typedef boost::weak_ptr<Constructor>         ConstructorWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_CONSTRUCTOR_COMPIL_H_

