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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_METHOD_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_METHOD_COMPIL_H_

#include "argument.h"
#include "comment.h"
#include "decorated_type.h"
#include "method.h"
#include "method_declaration.h"
#include "method_name.h"
#include "method_specifier.h"
#include "namespace.h"

namespace cpp
{

namespace frm
{

class Method
{
public:
    // Default constructor
                                             Method             ();
    // Destructor
    /*lax*/                                  ~Method            ();

    // Getter method for the data field comment
            const CommentSPtr&               comment            ()                                           const;
    // Setter method for the data field comment
            Method&                          set_comment        (const CommentSPtr& comment);
    // Store operator for the data field comment
            Method&                          operator<<         (const CommentSPtr& comment);

    // Getter method for the data field specifier
            const EMethodSpecifier&          specifier          ()                                           const;
    // Setter method for the data field specifier
            Method&                          set_specifier      (const EMethodSpecifier& specifier);
    // Provides mutable access to field specifier
            EMethodSpecifier&                mutable_specifier  ();
    // Store operator for the data field specifier
            Method&                          operator<<         (const EMethodSpecifier& specifier);

    // Getter method for the data field return
            const DecoratedTypeSPtr&         return_            ()                                           const;
    // Setter method for the data field return
            Method&                          set_return         (const DecoratedTypeSPtr& return_);
    // Store operator for the data field return
            Method&                          operator<<         (const DecoratedTypeSPtr& return_);

    // Getter method for the data field namespace
            const NamespaceSPtr&             namespace_         ()                                           const;
    // Setter method for the data field namespace
            Method&                          set_namespace      (const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            Method&                          operator<<         (const NamespaceSPtr& namespace_);

    // Getter method for the data field name
            const MethodNameSPtr&            name               ()                                           const;
    // Setter method for the data field name
            Method&                          set_name           (const MethodNameSPtr& name);
    // Store operator for the data field name
            Method&                          operator<<         (const MethodNameSPtr& name);

    // Getter method for the data field arguments
            const std::vector<ArgumentSPtr>& arguments          ()                                           const;
    // Setter method for the data field arguments
            Method&                          set_arguments      (const std::vector<ArgumentSPtr>& arguments);
    // Provides mutable access to field arguments
            std::vector<ArgumentSPtr>&       mutable_arguments  ();
    // Store operator for the data field arguments
            Method&                          operator<<         (const std::vector<ArgumentSPtr>& arguments);
    // Store operator for an item of data field arguments
            Method&                          operator<<         (const ArgumentSPtr& argumentsItem);

    // Getter method for the data field declaration
            const EMethodDeclaration&        declaration        ()                                           const;
    // Setter method for the data field declaration
            Method&                          set_declaration    (const EMethodDeclaration& declaration);
    // Provides mutable access to field declaration
            EMethodDeclaration&              mutable_declaration();
    // Store operator for the data field declaration
            Method&                          operator<<         (const EMethodDeclaration& declaration);

private:
    // variable for the data field comment
    CommentSPtr               mComment;
    // variable for the data field specifier
    EMethodSpecifier          mSpecifier;
    // variable for the data field return
    DecoratedTypeSPtr         mReturn;
    // variable for the data field namespace
    NamespaceSPtr             mNamespace;
    // variable for the data field name
    MethodNameSPtr            mName;
    // variable for the data field arguments
    std::vector<ArgumentSPtr> mArguments;
    // variable for the data field declaration
    EMethodDeclaration        mDeclaration;
};

// Reference store operator for the data field comment
const MethodSPtr& operator<<(const MethodSPtr& , const CommentSPtr& );
// Reference store operator for the data field specifier
const MethodSPtr& operator<<(const MethodSPtr& , const EMethodSpecifier& );
// Reference store operator for the data field return
const MethodSPtr& operator<<(const MethodSPtr& , const DecoratedTypeSPtr& );
// Reference store operator for the data field namespace
const MethodSPtr& operator<<(const MethodSPtr& , const NamespaceSPtr& );
// Reference store operator for the data field name
const MethodSPtr& operator<<(const MethodSPtr& , const MethodNameSPtr& );
// Reference store operator for the data field arguments
const MethodSPtr& operator<<(const MethodSPtr& , const std::vector<ArgumentSPtr>& );
// Reference store operator for an item of data field arguments
const MethodSPtr& operator<<(const MethodSPtr& , const ArgumentSPtr& );
// Reference store operator for the data field declaration
const MethodSPtr& operator<<(const MethodSPtr& , const EMethodDeclaration& );

inline MethodSPtr methodRef()
{
    return boost::make_shared<Method>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_METHOD_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class Method;
typedef Method*                         MethodRPtr;
typedef boost::shared_ptr<Method>       MethodSPtr;
typedef boost::shared_ptr<const Method> MethodSCPtr;
typedef boost::weak_ptr<Method>         MethodWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_METHOD_COMPIL_H_

