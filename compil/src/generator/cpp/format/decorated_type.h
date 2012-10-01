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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DECORATED_TYPE_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DECORATED_TYPE_COMPIL_H_

#include "decorated_type.h"
#include "simple_type.h"
#include "type_declaration.h"
#include "type_decoration.h"

namespace cpp
{

namespace frm
{

class DecoratedType
{
public:
    // Default constructor
                                    DecoratedType      ();
    // Destructor
    /*lax*/                         ~DecoratedType     ();

    // Getter method for the data field declaration
            const ETypeDeclaration& declaration        ()                                    const;
    // Returns the default value invalid of the field declaration
    static  ETypeDeclaration        default_declaration();
    // Setter method for the data field declaration
            DecoratedType&          set_declaration    (const ETypeDeclaration& declaration);
    // Provides mutable access to field declaration
            ETypeDeclaration&       mutable_declaration();
    // Store operator for the data field declaration
            DecoratedType&          operator<<         (const ETypeDeclaration& declaration);

    // Getter method for the data field type
            const SimpleTypeSPtr&   type               ()                                    const;
    // Setter method for the data field type
            DecoratedType&          set_type           (const SimpleTypeSPtr& type);
    // Store operator for the data field type
            DecoratedType&          operator<<         (const SimpleTypeSPtr& type);

    // Getter method for the data field decoration
            const ETypeDecoration&  decoration         ()                                    const;
    // Returns the default value invalid of the field decoration
    static  ETypeDecoration         default_decoration ();
    // Setter method for the data field decoration
            DecoratedType&          set_decoration     (const ETypeDecoration& decoration);
    // Provides mutable access to field decoration
            ETypeDecoration&        mutable_decoration ();
    // Store operator for the data field decoration
            DecoratedType&          operator<<         (const ETypeDecoration& decoration);

private:
    // variable for the data field declaration
    ETypeDeclaration mDeclaration;
    // variable for the data field type
    SimpleTypeSPtr   mType;
    // variable for the data field decoration
    ETypeDecoration  mDecoration;
};

// Reference store operator for the data field declaration
const DecoratedTypeSPtr& operator<<(const DecoratedTypeSPtr& , const ETypeDeclaration& );
// Reference store operator for the data field type
const DecoratedTypeSPtr& operator<<(const DecoratedTypeSPtr& , const SimpleTypeSPtr& );
// Reference store operator for the data field decoration
const DecoratedTypeSPtr& operator<<(const DecoratedTypeSPtr& , const ETypeDecoration& );

inline DecoratedTypeSPtr decoratedTypeRef()
{
    return boost::make_shared<DecoratedType>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DECORATED_TYPE_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class DecoratedType;
typedef DecoratedType*                         DecoratedTypeRPtr;
typedef boost::shared_ptr<DecoratedType>       DecoratedTypeSPtr;
typedef boost::shared_ptr<const DecoratedType> DecoratedTypeSCPtr;
typedef boost::weak_ptr<DecoratedType>         DecoratedTypeWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_DECORATED_TYPE_COMPIL_H_

