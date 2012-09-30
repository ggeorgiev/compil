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

#ifndef __GENERATOR_SELF_COMPILER_MODEL_STRUCTURE_COMPIL__PARTIAL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_STRUCTURE_COMPIL__PARTIAL_H_

#include "object.h"
#include "structure-partial.h"
#include "type.h"

namespace compil
{

// This is a partial class (similar to partial classes in C#). Makes sense
// only in the context of its derived class. Since in C++ there are no
// partial classes, the pattern is implemented with inheritance -
// StructurePartial being the base class and Structure being its derived
// class.

// StructurePartial provides the operational functionality for getting and
// setting the data. Refer to the derived Structure class for more details
// about business related functionality.

class StructurePartial : public Type
{
protected:
    // Default constructor
                                           StructurePartial     ();
    // Destructor
    virtual                                ~StructurePartial    ();
public:

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureSPtr                  downcast             (const ObjectSPtr& object);
    // shared_from_this is a helper method that overrides the
    // shared_from_this method that is implemented in
    // boost::enable_shared_from_this base class. The only purpose of this
    // helper method is to eliminate the need of downcasting to shared_ptr
    // to this class.
            StructureSPtr                  shared_from_this     ();
    // This method is exactly the same as the previous one with exception
    // that it allows shared_from_this to be called from const methods.
            StructureSCPtr                 shared_from_this     ()                                       const;

    // Returns the alter value structure of the field literal
    static  TypePartial::ELiteral          alter_literal        ();

    // Returns the alter value object of the field kind
    static  TypePartial::EKind             alter_kind           ();

    // Identifier for the objects from Structure class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId                      staticObjectId       ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId                      runtimeObjectId      ()                                       const;

    // This flag indicates whether the structure need to provide
    // control methods - availability and destroy
    // Getter method for the data field abstract
            bool                           abstract             ()                                       const;
    // Setter method for the data field abstract
            Structure&                     set_abstract         (bool abstract);

    // Getter method for the data field controlled
            bool                           controlled           ()                                       const;
    // Setter method for the data field controlled
            Structure&                     set_controlled       (bool controlled);

    // Getter method for the data field immutable
            bool                           immutable            ()                                       const;
    // Setter method for the data field immutable
            Structure&                     set_immutable        (bool immutable);

    // Getter method for the data field partial
            bool                           partial              ()                                       const;
    // Setter method for the data field partial
            Structure&                     set_partial          (bool partial);

    // Getter method for the data field sharable
            bool                           sharable             ()                                       const;
    // Setter method for the data field sharable
            Structure&                     set_sharable         (bool sharable);

    // Getter method for the data field streamable
            bool                           streamable           ()                                       const;
    // Setter method for the data field streamable
            Structure&                     set_streamable       (bool streamable);

    // Getter method for the data field objects
            const std::vector<ObjectSPtr>& objects              ()                                       const;
    // Setter method for the data field objects
            Structure&                     set_objects          (const std::vector<ObjectSPtr>& objects);
    // Provides mutable access to field objects
            std::vector<ObjectSPtr>&       mutable_objects      ();

    // Getter method for the data field baseStructure
            const StructureWPtr&           baseStructure        ()                                       const;
    // Returns the default value null of the field baseStructure
    static  StructureWPtr                  default_baseStructure();
    // Setter method for the data field baseStructure
            Structure&                     set_baseStructure    (const StructureSPtr& baseStructure);

private:
    // variable for the data field abstract
    bool                    mAbstract;
    // variable for the data field controlled
    bool                    mControlled;
    // variable for the data field immutable
    bool                    mImmutable;
    // variable for the data field partial
    bool                    mPartial;
    // variable for the data field sharable
    bool                    mSharable;
    // variable for the data field streamable
    bool                    mStreamable;
    // variable for the data field objects
    std::vector<ObjectSPtr> mObjects;
    // variable for the data field baseStructure
    StructureWPtr           mBaseStructure;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_STRUCTURE_COMPIL__PARTIAL_H_

namespace compil
{

// Forward declarations
class Structure;
typedef Structure*                         StructureRPtr;
typedef boost::shared_ptr<Structure>       StructureSPtr;
typedef boost::shared_ptr<const Structure> StructureSCPtr;
typedef boost::weak_ptr<Structure>         StructureWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_STRUCTURE_COMPIL__PARTIAL_H_

