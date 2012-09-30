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
#include <string>

#ifndef __GENERATOR_SELF_COMPILER_MODEL_INTEGER_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_INTEGER_COMPIL_H_

#include "castable_type.h"
#include "integer.h"

namespace compil
{

class Integer : public CastableType
{
public:
    // Default constructor
                                  Integer        ();
    // Destructor
    virtual                       ~Integer       ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IntegerSPtr           downcast       (const ObjectSPtr& object);

    // Returns the alter value integer of the field literal
    static  TypePartial::ELiteral alter_literal  ();

    // Returns the alter value builtin of the field kind
    static  TypePartial::EKind    alter_kind     ();

    // Returns the alter value weak of the field cast
    static  CastableType::ECast   alter_cast     ();

    // Identifier for the objects from Integer class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId             staticObjectId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId             runtimeObjectId()                         const;

    // Getter method for the data field min
            const std::string&    min            ()                         const;
    // Setter method for the data field min
            Integer&              set_min        (const std::string& min);
    // Provides mutable access to field min
            std::string&          mutable_min    ();

    // Getter method for the data field max
            const std::string&    max            ()                         const;
    // Setter method for the data field max
            Integer&              set_max        (const std::string& max);
    // Provides mutable access to field max
            std::string&          mutable_max    ();

private:
    // variable for the data field min
    std::string mMin;
    // variable for the data field max
    std::string mMax;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_INTEGER_COMPIL_H_

namespace compil
{

// Forward declarations
class Integer;
typedef Integer*                         IntegerRPtr;
typedef boost::shared_ptr<Integer>       IntegerSPtr;
typedef boost::shared_ptr<const Integer> IntegerSCPtr;
typedef boost::weak_ptr<Integer>         IntegerWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_INTEGER_COMPIL_H_

