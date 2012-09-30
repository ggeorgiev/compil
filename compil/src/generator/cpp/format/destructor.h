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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_COMPIL_H_

#include "comment.h"
#include "destructor.h"
#include "destructor_name.h"
#include "destructor_specifier.h"
#include "namespace.h"

namespace cpp
{

namespace frm
{

class Destructor
{
public:
    // Default constructor
                                        Destructor       ();
    // Destructor
    /*lax*/                             ~Destructor      ();

    // Getter method for the data field comment
            const CommentSPtr&          comment          ()                                      const;
    // Setter method for the data field comment
            Destructor&                 set_comment      (const CommentSPtr& comment);
    // Store operator for the data field comment
            Destructor&                 operator<<       (const CommentSPtr& comment);

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
    // variable for the data field comment
    CommentSPtr          mComment;
    // variable for the data field specifier
    EDestructorSpecifier mSpecifier;
    // variable for the data field name
    DestructorNameSPtr   mName;
    // variable for the data field namespace
    NamespaceSPtr        mNamespace;
};

// Reference store operator for the data field comment
const DestructorSPtr& operator<<(const DestructorSPtr& , const CommentSPtr& );
// Reference store operator for the data field specifier
const DestructorSPtr& operator<<(const DestructorSPtr& , const EDestructorSpecifier& );
// Reference store operator for the data field name
const DestructorSPtr& operator<<(const DestructorSPtr& , const DestructorNameSPtr& );
// Reference store operator for the data field namespace
const DestructorSPtr& operator<<(const DestructorSPtr& , const NamespaceSPtr& );

inline DestructorSPtr destructorRef()
{
    return boost::make_shared<Destructor>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class Destructor;
typedef Destructor*                         DestructorRPtr;
typedef boost::shared_ptr<Destructor>       DestructorSPtr;
typedef boost::shared_ptr<const Destructor> DestructorSCPtr;
typedef boost::weak_ptr<Destructor>         DestructorWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DESTRUCTOR_COMPIL_H_

