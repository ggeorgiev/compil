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

#ifndef __GENERATOR_SELF_COMPILER_MODEL_OPERATOR_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_OPERATOR_COMPIL_H_

#include "comment.h"
#include "object.h"
#include "operator.h"
#include "structure.h"
// Compil C++ Template Library
#include "flags_enumeration.hpp"

namespace compil
{

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EOperatorAction
{
public:
    // Default constructor - sets the value to invalid
                         EOperatorAction();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EOperatorAction(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value          ()                              const;
    // Returns short name for a specified enum value
    static   const char* shortName      (long value);
    // Returns short name of the enum value
             const char* shortName      ()                              const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==     (const EOperatorAction& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=     (const EOperatorAction& rValue) const;

    // static methods for enum class objects
    static const EOperatorAction invalid    ();
    static const EOperatorAction equalTo    ();
    static const EOperatorAction notEqualTo ();
    static const EOperatorAction greaterThan();
    static const EOperatorAction lessThan   ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid     = 0,
        kEqualTo     = 1,
        kNotEqualTo  = 2,
        kGreaterThan = 3,
        kLessThan    = 4,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

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

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EOperatorParameter : public flags_enumeration<long, EOperatorParameter>
{
public:
    // Default constructor - sets the value to nil
                         EOperatorParameter();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EOperatorParameter(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value             ()                                 const;
    // Returns short name for a specified enum value
    static   const char* shortName         (long value);
    // Returns short name of the enum value
             const char* shortName         ()                                 const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==        (const EOperatorParameter& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=        (const EOperatorParameter& rValue) const;

    // static methods for enum class objects
    static const EOperatorParameter nil      ();
    static const EOperatorParameter object   ();
    static const EOperatorParameter reference();
    static const EOperatorParameter all      ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kNil       = 0,
        kObject    = 1 << 0,
        kReference = 1 << 1,
        kAll       = 0x3,
    };

};

class Operator : public Object
{
public:
    // Default constructor
                                   Operator         ();
    // Destructor
    virtual                        ~Operator        ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  OperatorSPtr           downcast         (const ObjectSPtr& object);

    // Identifier for the objects from Operator class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId              staticObjectId   ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId              runtimeObjectId  ()                               const;

    // Getter method for the data field action
            const EOperatorAction& action           ()                               const;
    // Setter method for the data field action
            Operator&              set_action       (const EOperatorAction& action);
    // Provides mutable access to field action
            EOperatorAction&       mutable_action   ();

    // Getter method for the data field flags
            const EOperatorFlags&  flags            ()                               const;
    // Setter method for the data field flags
            Operator&              set_flags        (const EOperatorFlags& flags);
    // Provides mutable access to field flags
            EOperatorFlags&        mutable_flags    ();

    // Getter method for the data field structure
            const StructureWPtr&   structure        ()                               const;
    // Returns the default value null of the field structure
    static  StructureWPtr          default_structure();
    // Setter method for the data field structure
            Operator&              set_structure    (const StructureSPtr& structure);

    // Getter method for the data field comment
            const CommentSPtr&     comment          ()                               const;
    // Setter method for the data field comment
            Operator&              set_comment      (const CommentSPtr& comment);

private:
    // variable for the data field action
    EOperatorAction mAction;
    // variable for the data field flags
    EOperatorFlags  mFlags;
    // variable for the data field structure
    StructureWPtr   mStructure;
    // variable for the data field comment
    CommentSPtr     mComment;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_OPERATOR_COMPIL_H_

namespace compil
{

// Forward declarations
class EOperatorAction;
typedef EOperatorAction*                         OperatorActionRPtr;
typedef boost::shared_ptr<EOperatorAction>       OperatorActionSPtr;
typedef boost::shared_ptr<const EOperatorAction> OperatorActionSCPtr;
typedef boost::weak_ptr<EOperatorAction>         OperatorActionWPtr;

class EOperatorFlags;
typedef EOperatorFlags*                         OperatorFlagsRPtr;
typedef boost::shared_ptr<EOperatorFlags>       OperatorFlagsSPtr;
typedef boost::shared_ptr<const EOperatorFlags> OperatorFlagsSCPtr;
typedef boost::weak_ptr<EOperatorFlags>         OperatorFlagsWPtr;

class EOperatorParameter;
typedef EOperatorParameter*                         OperatorParameterRPtr;
typedef boost::shared_ptr<EOperatorParameter>       OperatorParameterSPtr;
typedef boost::shared_ptr<const EOperatorParameter> OperatorParameterSCPtr;
typedef boost::weak_ptr<EOperatorParameter>         OperatorParameterWPtr;

class Operator;
typedef Operator*                         OperatorRPtr;
typedef boost::shared_ptr<Operator>       OperatorSPtr;
typedef boost::shared_ptr<const Operator> OperatorSCPtr;
typedef boost::weak_ptr<Operator>         OperatorWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_OPERATOR_COMPIL_H_

