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

#ifndef __COMPIL_DOCUMENT_REFERENCE_SCOMPIL_H_
#define __COMPIL_DOCUMENT_REFERENCE_SCOMPIL_H_

#include "language/compil/document/reference.h"
#include "language/compil/document/unary_template.h"

namespace lang
{

namespace compil
{

class Reference : public UnaryTemplate
{
public:
    // Default constructor
                          Reference        ();
    // Destructor
    virtual               ~Reference       ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ReferenceSPtr downcast         (const ObjectSPtr& object);

    // Identifier for the objects from Reference class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId     staticObjectId   ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId     runtimeObjectId  ()                              const;

    // Getter method for the data field weak
            bool          weak             ()                              const;
    // Setter method for the data field weak
            Reference&    set_weak         (bool weak);

    // Setter method for the data field sourceId
            Reference&    set_sourceId     (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            Reference&    set_line         (const Line& line);

    // Setter method for the data field column
            Reference&    set_column       (const Column& column);

    // Setter method for the data field package
            Reference&    set_package      (const PackageSPtr& package);

    // Setter method for the data field comment
            Reference&    set_comment      (const CommentSPtr& comment);

    // Setter method for the data field name
            Reference&    set_name         (const NameSPtr& name);

    // Setter method for the data field literal
            Reference&    set_literal      (const ELiteral& literal);

    // Setter method for the data field kind
            Reference&    set_kind         (const EKind& kind);

    // Setter method for the data field cast
            Reference&    set_cast         (const ECast& cast);

    // Setter method for the data field parameterType
            Reference&    set_parameterType(const TypeSPtr& parameterType);

private:
    // variable for the data field weak
    bool mWeak;
};

}

}

#else // __COMPIL_DOCUMENT_REFERENCE_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class Reference;
typedef Reference*                         ReferenceRPtr;
typedef boost::shared_ptr<Reference>       ReferenceSPtr;
typedef boost::shared_ptr<const Reference> ReferenceSCPtr;
typedef boost::weak_ptr<Reference>         ReferenceWPtr;

class EObjectId;

}

}

#endif // __COMPIL_DOCUMENT_REFERENCE_SCOMPIL_H_

