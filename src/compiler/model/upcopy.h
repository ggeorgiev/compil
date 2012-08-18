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

#ifndef __GENERATOR_SELF_COMPILER_MODEL_UPCOPY_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_UPCOPY_COMPIL_H_

#include "comment.h"
#include "object.h"
#include "structure.h"
#include "upcopy.h"

namespace compil
{

class Upcopy : public Object
{
public:
    // Default constructor
                                 Upcopy             ();
    // Destructor
    virtual                      ~Upcopy            ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  UpcopySPtr           downcast           (const ObjectSPtr& pObject);

    // Returns true if every required field is initialized.
    virtual bool                 isInitialized      ()                                   const;

    // Identifier for the objects from Upcopy class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId            staticObjectId     ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId            runtimeObjectId    ()                                   const;

    // Getter method for the data field comment
            const CommentSPtr&   comment            ()                                   const;
    // Returns true if the data field comment was set and could be
    // considered valid
            bool                 valid_comment      ()                                   const;
    // Setter method for the data field comment
            void                 set_comment        (const CommentSPtr& comment);
    // Erases the required data field comment. Object can not be
    // instantiated before the field data is set again
            void                 erase_comment      ();

    // Getter method for the data field structure
            const StructureWPtr& structure          ()                                   const;
    // Returns true if the data field structure was set and could be
    // considered valid
            bool                 valid_structure    ()                                   const;
    // Setter method for the data field structure
            void                 set_structure      (const StructureSPtr& structure);
    // Erases the required data field structure. Object can not be
    // instantiated before the field data is set again
            void                 erase_structure    ();

    // Getter method for the data field baseStructure
            const StructureSPtr& baseStructure      ()                                   const;
    // Returns true if the data field baseStructure was set and could be
    // considered valid
            bool                 valid_baseStructure()                                   const;
    // Setter method for the data field baseStructure
            void                 set_baseStructure  (const StructureSPtr& baseStructure);
    // Erases the required data field baseStructure. Object can not be
    // instantiated before the field data is set again
            void                 erase_baseStructure();

private:
    // Returns unique bitmask value for the field comment
    static int bitmask_comment      ();
    // Returns unique bitmask value for the field structure
    static int bitmask_structure    ();
    // Returns unique bitmask value for the field baseStructure
    static int bitmask_baseStructure();

    // Stores availability information for the fields
    int           mBits;

    // variable for the data field comment
    CommentSPtr   mComment;
    // variable for the data field structure
    StructureWPtr mStructure;
    // variable for the data field baseStructure
    StructureSPtr mBaseStructure;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_UPCOPY_COMPIL_H_

namespace compil
{

// Forward declarations
class Upcopy;
typedef Upcopy*                         UpcopyRPtr;
typedef boost::shared_ptr<Upcopy>       UpcopySPtr;
typedef boost::shared_ptr<const Upcopy> UpcopySCPtr;
typedef boost::weak_ptr<Upcopy>         UpcopyWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_UPCOPY_COMPIL_H_

