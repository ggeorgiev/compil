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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_TYPE_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_TYPE_COMPIL_H_

#include "namespace.h"
#include "type.h"
#include "type_declaration.h"
#include "type_decoration.h"
#include "type_name.h"

namespace cpp
{

namespace frm
{

class Type
{
public:
    // Default constructor
                                    Type               ();
    // Destructor
    /*lax*/                         ~Type              ();

    // Getter method for the data field declaration
            const ETypeDeclaration& declaration        ()                                    const;
    // Returns the default value invalid of the field declaration
    static  ETypeDeclaration        default_declaration();
    // Setter method for the data field declaration
            Type&                   set_declaration    (const ETypeDeclaration& declaration);
    // Provides mutable access to field declaration
            ETypeDeclaration&       mutable_declaration();
    // Store operator for the data field declaration
            Type&                   operator<<         (const ETypeDeclaration& declaration);

    // Getter method for the data field namespace
            const NamespaceSPtr&    namespace_         ()                                    const;
    // Setter method for the data field namespace
            Type&                   set_namespace      (const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            Type&                   operator<<         (const NamespaceSPtr& namespace_);

    // Getter method for the data field name
            const TypeNameSPtr&     name               ()                                    const;
    // Setter method for the data field name
            Type&                   set_name           (const TypeNameSPtr& name);
    // Store operator for the data field name
            Type&                   operator<<         (const TypeNameSPtr& name);

    // Getter method for the data field decoration
            const ETypeDecoration&  decoration         ()                                    const;
    // Returns the default value invalid of the field decoration
    static  ETypeDecoration         default_decoration ();
    // Setter method for the data field decoration
            Type&                   set_decoration     (const ETypeDecoration& decoration);
    // Provides mutable access to field decoration
            ETypeDecoration&        mutable_decoration ();
    // Store operator for the data field decoration
            Type&                   operator<<         (const ETypeDecoration& decoration);

private:
    // variable for the data field declaration
    ETypeDeclaration mDeclaration;
    // variable for the data field namespace
    NamespaceSPtr    mNamespace;
    // variable for the data field name
    TypeNameSPtr     mName;
    // variable for the data field decoration
    ETypeDecoration  mDecoration;
};

// Reference store operator for the data field declaration
const TypeSPtr& operator<<(const TypeSPtr& , const ETypeDeclaration& );
// Reference store operator for the data field namespace
const TypeSPtr& operator<<(const TypeSPtr& , const NamespaceSPtr& );
// Reference store operator for the data field name
const TypeSPtr& operator<<(const TypeSPtr& , const TypeNameSPtr& );
// Reference store operator for the data field decoration
const TypeSPtr& operator<<(const TypeSPtr& , const ETypeDecoration& );

inline TypeSPtr typeRef()
{
    return boost::make_shared<Type>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_TYPE_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class Type;
typedef Type*                         TypeRPtr;
typedef boost::shared_ptr<Type>       TypeSPtr;
typedef boost::shared_ptr<const Type> TypeSCPtr;
typedef boost::weak_ptr<Type>         TypeWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_TYPE_COMPIL_H_

