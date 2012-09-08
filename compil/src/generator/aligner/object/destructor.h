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

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DESTRUCTOR_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DESTRUCTOR_COMPIL_H_

#include "destructor.h"
#include "destructor_name.h"
#include "destructor_specifier.h"
#include "namespace.h"

class Destructor
{
public:
    // Default constructor
                                        Destructor       ();
    // Destructor
    /*lax*/                             ~Destructor      ();

    // Getter method for the data field specifier
            const EDestructorSpecifier& specifier        ()                                      const;
    // Setter method for the data field specifier
            Destructor&                 set_specifier    (const EDestructorSpecifier& specifier);
    // Provides mutable access to field specifier
            EDestructorSpecifier&       mutable_specifier();
    // Store operator for the data field specifier
            Destructor&                 operator<<       (const EDestructorSpecifier& specifier);

    // Getter method for the data field name
            const DestructorNameSPtr&   name             ()                                      const;
    // Setter method for the data field name
            Destructor&                 set_name         (const DestructorNameSPtr& name);
    // Store operator for the data field name
            Destructor&                 operator<<       (const DestructorNameSPtr& name);

    // Getter method for the data field namespace
            const NamespaceSPtr&        namespace_       ()                                      const;
    // Setter method for the data field namespace
            Destructor&                 set_namespace    (const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            Destructor&                 operator<<       (const NamespaceSPtr& namespace_);

private:
    // variable for the data field specifier
    EDestructorSpecifier mSpecifier;
    // variable for the data field name
    DestructorNameSPtr   mName;
    // variable for the data field namespace
    NamespaceSPtr        mNamespace;
};

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DESTRUCTOR_COMPIL_H_

// Forward declarations
class Destructor;
typedef Destructor*                         DestructorRPtr;
typedef boost::shared_ptr<Destructor>       DestructorSPtr;
typedef boost::shared_ptr<const Destructor> DestructorSCPtr;
typedef boost::weak_ptr<Destructor>         DestructorWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DESTRUCTOR_COMPIL_H_

