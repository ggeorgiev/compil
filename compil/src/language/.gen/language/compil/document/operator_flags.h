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

#ifndef __COMPIL_DOCUMENT_OPERATOR_FLAGS_SCOMPIL_H_
#define __COMPIL_DOCUMENT_OPERATOR_FLAGS_SCOMPIL_H_

#include "language/compil/document/operator_flags.h"
// Compil C++ Template Library
#include "core/compil/flags_enumeration.hpp"

namespace lang
{

namespace compil
{

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EOperatorFlags : public flags_enumeration<long, EOperatorFlags>
{
public:
    // Default constructor - sets the value to nil
                         EOperatorFlags();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EOperatorFlags(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value         ()                             const;
    // Returns short name for a specified enum value
    static   const char* shortName     (long value);
    // Returns short name of the enum value
             const char* shortName     ()                             const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==    (const EOperatorFlags& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=    (const EOperatorFlags& rValue) const;

    // static methods for enum class objects
    static const EOperatorFlags nil        ();
    static const EOperatorFlags native     ();
    static const EOperatorFlags function   ();
    static const EOperatorFlags functor    ();
    static const EOperatorFlags declaration();
    static const EOperatorFlags object     ();
    static const EOperatorFlags reference  ();
    static const EOperatorFlags parameter  ();
    static const EOperatorFlags member     ();
    static const EOperatorFlags internal   ();
    static const EOperatorFlags external   ();
    static const EOperatorFlags location   ();
    static const EOperatorFlags all        ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kNil         = 0,
        kNative      = 1 << 0,
        kFunction    = 1 << 1,
        kFunctor     = 1 << 2,
        kDeclaration = kNative | kFunction  | kFunctor,
        kObject      = 1 << 3,
        kReference   = 1 << 4,
        kParameter   = kObject | kReference,
        kMember      = 1 << 5,
        kInternal    = 1 << 6,
        kExternal    = 1 << 7,
        kLocation    = kMember | kInternal  | kExternal,
        kAll         = 0xff,
    };

};

}

}

#else // __COMPIL_DOCUMENT_OPERATOR_FLAGS_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class EOperatorFlags;
typedef EOperatorFlags*                         EOperatorFlagsRPtr;
typedef boost::shared_ptr<EOperatorFlags>       EOperatorFlagsSPtr;
typedef boost::shared_ptr<const EOperatorFlags> EOperatorFlagsSCPtr;
typedef boost::weak_ptr<EOperatorFlags>         EOperatorFlagsWPtr;

}

}

#endif // __COMPIL_DOCUMENT_OPERATOR_FLAGS_SCOMPIL_H_

