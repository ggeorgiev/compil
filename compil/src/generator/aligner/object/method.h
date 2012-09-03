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

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_METHOD_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_METHOD_COMPIL_H_

#include "method.h"
#include "method_name.h"
#include "method_specifier.h"
#include "namespace.h"

class Method
{
public:
    // Default constructor
                                    Method       ();
    // Destructor
    /*lax*/                         ~Method      ();

    // Getter method for the data field specifier
            const EMethodSpecifier& specifier    ()                                  const;
    // Setter method for the data field specifier
            Method&                 set_specifier(const EMethodSpecifier& specifier);
    // Store operator for the data field specifier
            Method&                 operator<<   (const EMethodSpecifier& specifier);

    // Getter method for the data field name
            const MethodNameSPtr&   name         ()                                  const;
    // Setter method for the data field name
            Method&                 set_name     (const MethodNameSPtr& name);
    // Store operator for the data field name
            Method&                 operator<<   (const MethodNameSPtr& name);

    // Getter method for the data field namespace
            const NamespaceSPtr&    namespace_   ()                                  const;
    // Setter method for the data field namespace
            Method&                 set_namespace(const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            Method&                 operator<<   (const NamespaceSPtr& namespace_);

private:
    // variable for the data field specifier
    EMethodSpecifier mSpecifier;
    // variable for the data field name
    MethodNameSPtr   mName;
    // variable for the data field namespace
    NamespaceSPtr    mNamespace;
};

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_METHOD_COMPIL_H_

// Forward declarations
class Method;
typedef Method*                         MethodRPtr;
typedef boost::shared_ptr<Method>       MethodSPtr;
typedef boost::shared_ptr<const Method> MethodSCPtr;
typedef boost::weak_ptr<Method>         MethodWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_METHOD_COMPIL_H_
