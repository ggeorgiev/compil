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

#ifndef __COMPIL_DOCUMENT_SPECIMEN_SCOMPIL__PARTIAL_H_
#define __COMPIL_DOCUMENT_SPECIMEN_SCOMPIL__PARTIAL_H_

#include "language/compil/document/specimen-partial.h"
#include "language/compil/document/specimen.h"
#include "language/compil/document/unary_template.h"

namespace lang
{

namespace compil
{

// This is a partial class (similar to partial classes in C#). Makes sense
// only in the context of its derived class. Since in C++ there are no
// partial classes, the pattern is implemented with inheritance -
// SpecimenPartial being the base class and Specimen being its derived
// class.

// SpecimenPartial provides the operational functionality for getting and
// setting the data. Refer to the derived Specimen class for more details
// about business related functionality.

class SpecimenPartial : public UnaryTemplate
{
protected:
    // Default constructor
                                SpecimenPartial     ();
    // Destructor
    virtual                     ~SpecimenPartial    ();
public:

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  SpecimenSPtr        downcast            (const ObjectSPtr& object);

    // Returns the alter value object of the field kind
    static  TypePartial::EKind  alter_kind          ();

    // Identifier for the objects from Specimen class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId           staticObjectId      ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId           runtimeObjectId     ()                                 const;

    // Getter method for the data field baseSpecimen
            const SpecimenWPtr& baseSpecimen        ()                                 const;
    // Returns the default value null of the field baseSpecimen
    static  SpecimenWPtr        default_baseSpecimen();
    // Setter method for the data field baseSpecimen
            Specimen&           set_baseSpecimen    (const SpecimenSPtr& baseSpecimen);

    // Setter method for the data field sourceId
            Specimen&           set_sourceId        (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            Specimen&           set_line            (const Line& line);

    // Setter method for the data field column
            Specimen&           set_column          (const Column& column);

    // Setter method for the data field package
            Specimen&           set_package         (const PackageSPtr& package);

    // Setter method for the data field comment
            Specimen&           set_comment         (const CommentSPtr& comment);

    // Setter method for the data field name
            Specimen&           set_name            (const NameSPtr& name);

    // Setter method for the data field literal
            Specimen&           set_literal         (const ELiteral& literal);

    // Setter method for the data field kind
            Specimen&           set_kind            (const EKind& kind);

    // Setter method for the data field cast
            Specimen&           set_cast            (const ECast& cast);

    // Setter method for the data field parameterType
            Specimen&           set_parameterType   (const TypeSPtr& parameterType);

private:
    // variable for the data field baseSpecimen
    SpecimenWPtr mBaseSpecimen;
};

}

}

#else // __COMPIL_DOCUMENT_SPECIMEN_SCOMPIL__PARTIAL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class Specimen;
typedef Specimen*                         SpecimenRPtr;
typedef boost::shared_ptr<Specimen>       SpecimenSPtr;
typedef boost::shared_ptr<const Specimen> SpecimenSCPtr;
typedef boost::weak_ptr<Specimen>         SpecimenWPtr;

class EObjectId;

}

}

#endif // __COMPIL_DOCUMENT_SPECIMEN_SCOMPIL__PARTIAL_H_
