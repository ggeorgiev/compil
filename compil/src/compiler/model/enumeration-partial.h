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
// Standard Template Library
#include <vector>

#ifndef __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_COMPIL__PARTIAL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_COMPIL__PARTIAL_H_

#include "enumeration-partial.h"
#include "enumeration_value.h"
#include "structure.h"
#include "unary_template.h"

namespace compil
{

// This is a partial class (similar to partial classes in C#). Makes sense
// only in the context of its derived class. Since in C++ there are no
// partial classes, the pattern is implemented with inheritance -
// EnumerationPartial being the base class and Enumeration being its
// derived class.

// EnumerationPartial provides the operational functionality for getting
// and setting the data. Refer to the derived Enumeration class for more
// details about business related functionality.

class EnumerationPartial : public UnaryTemplate
{
protected:
    // Default constructor
                                                     EnumerationPartial       ();
    // Destructor
    virtual                                          ~EnumerationPartial      ();
public:

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  EnumerationSPtr                          downcast                 (const ObjectSPtr& object);

    // Returns the alter value identifier of the field literal
    static  Type::ELiteral                           alter_literal            ();

    // Returns the alter value object of the field kind
    static  Type::EKind                              alter_kind               ();

    // Identifier for the objects from Enumeration class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId                                staticObjectId           ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId                                runtimeObjectId          ()                                                           const;

    // Getter method for the data field flags
            bool                                     flags                    ()                                                           const;
    // Setter method for the data field flags
            Enumeration&                             set_flags                (bool flags);

    // Getter method for the data field enumerationValues
            const std::vector<EnumerationValueSPtr>& enumerationValues        ()                                                           const;
    // Setter method for the data field enumerationValues
            Enumeration&                             set_enumerationValues    (const std::vector<EnumerationValueSPtr>& enumerationValues);
    // Provides mutable access to field enumerationValues
            std::vector<EnumerationValueSPtr>&       mutable_enumerationValues();

    // Getter method for the data field structure
            const StructureWPtr&                     structure                ()                                                           const;
    // Returns the default value null of the field structure
    static  StructureWPtr                            default_structure        ();
    // Setter method for the data field structure
            Enumeration&                             set_structure            (const StructureSPtr& structure);

private:
    // variable for the data field flags
    bool                              mFlags;
    // variable for the data field enumerationValues
    std::vector<EnumerationValueSPtr> mEnumerationValues;
    // variable for the data field structure
    StructureWPtr                     mStructure;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_COMPIL__PARTIAL_H_

namespace compil
{

// Forward declarations
class Enumeration;
typedef Enumeration*                         EnumerationRPtr;
typedef boost::shared_ptr<Enumeration>       EnumerationSPtr;
typedef boost::shared_ptr<const Enumeration> EnumerationSCPtr;
typedef boost::weak_ptr<Enumeration>         EnumerationWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_COMPIL__PARTIAL_H_

