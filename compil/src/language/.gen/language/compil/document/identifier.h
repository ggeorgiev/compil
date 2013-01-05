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

#ifndef __COMPIL_DOCUMENT_IDENTIFIER_SCOMPIL_H_
#define __COMPIL_DOCUMENT_IDENTIFIER_SCOMPIL_H_

#include "language/compil/document/identifier.h"
#include "language/compil/document/unary_template.h"

namespace lang
{

namespace compil
{

class Identifier : public UnaryTemplate
{
public:
    // Default constructor
                               Identifier       ();
    // Destructor
    virtual                    ~Identifier      ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IdentifierSPtr     downcast         (const ObjectSPtr& object);

    // Returns the alter value object of the field kind
    static  TypePartial::EKind alter_kind       ();

    // Identifier for the objects from Identifier class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId          staticObjectId   ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId          runtimeObjectId  ()                              const;

    // Setter method for the data field sourceId
            Identifier&        set_sourceId     (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            Identifier&        set_line         (const Line& line);

    // Setter method for the data field column
            Identifier&        set_column       (const Column& column);

    // Setter method for the data field package
            Identifier&        set_package      (const PackageSPtr& package);

    // Setter method for the data field comment
            Identifier&        set_comment      (const CommentSPtr& comment);

    // Setter method for the data field name
            Identifier&        set_name         (const NameSPtr& name);

    // Setter method for the data field literal
            Identifier&        set_literal      (const ELiteral& literal);

    // Setter method for the data field kind
            Identifier&        set_kind         (const EKind& kind);

    // Setter method for the data field cast
            Identifier&        set_cast         (const ECast& cast);

    // Setter method for the data field parameterType
            Identifier&        set_parameterType(const TypeSPtr& parameterType);
};

}

}

#else // __COMPIL_DOCUMENT_IDENTIFIER_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class Identifier;
typedef Identifier*                         IdentifierRPtr;
typedef boost::shared_ptr<Identifier>       IdentifierSPtr;
typedef boost::shared_ptr<const Identifier> IdentifierSCPtr;
typedef boost::weak_ptr<Identifier>         IdentifierWPtr;

class EObjectId;

}

}

#endif // __COMPIL_DOCUMENT_IDENTIFIER_SCOMPIL_H_

