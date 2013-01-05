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

#ifndef __COMPIL_DOCUMENT_TYPE_SCOMPIL__PARTIAL_H_
#define __COMPIL_DOCUMENT_TYPE_SCOMPIL__PARTIAL_H_

#include "language/compil/all/comment.h"
#include "language/compil/all/name.h"
#include "language/compil/all/object.h"
#include "language/compil/all/package.h"
#include "language/compil/document/type-partial.h"
#include "language/compil/document/type.h"

namespace lang
{

namespace compil
{

// This is a partial class (similar to partial classes in C#). Makes sense
// only in the context of its derived class. Since in C++ there are no
// partial classes, the pattern is implemented with inheritance -
// TypePartial being the base class and Type being its derived class.

// TypePartial provides the operational functionality for getting and
// setting the data. Refer to the derived Type class for more details about
// business related functionality.

class TypePartial : public Object
{
protected:
    // Default constructor
                               TypePartial     ();
    // Destructor
    virtual                    ~TypePartial    ();
public:

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  TypeSPtr           downcast        (const ObjectSPtr& object);
    // shared_from_this is a helper method that overrides the
    // shared_from_this method that is implemented in
    // boost::enable_shared_from_this base class. The only purpose of this
    // helper method is to eliminate the need of downcasting to shared_ptr
    // to this class.
            TypeSPtr           shared_from_this();
    // This method is exactly the same as the previous one with exception
    // that it allows shared_from_this to be called from const methods.
            TypeSCPtr          shared_from_this()                           const;

    // Identifier for the objects from Type class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId          staticObjectId  ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId          runtimeObjectId ()                           const;

    // Getter method for the data field package
            const PackageSPtr& package         ()                           const;
    // Returns the default value null of the field package
    static  PackageSPtr        default_package ();
    // Setter method for the data field package
            Type&              set_package     (const PackageSPtr& package);

    // Getter method for the data field comment
            const CommentSPtr& comment         ()                           const;
    // Setter method for the data field comment
            Type&              set_comment     (const CommentSPtr& comment);

    // Getter method for the data field name
            const NameSPtr&    name            ()                           const;
    // Setter method for the data field name
            Type&              set_name        (const NameSPtr& name);

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class ELiteral
    {
    public:
        // Default constructor - sets the value to invalid
                             ELiteral  ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             ELiteral  (long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                       const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                       const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const ELiteral& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const ELiteral& rValue) const;

        // static methods for enum class objects
        static const ELiteral invalid   ();
        static const ELiteral boolean   ();
        static const ELiteral integer   ();
        static const ELiteral real      ();
        static const ELiteral string    ();
        static const ELiteral binary    ();
        static const ELiteral reference ();
        static const ELiteral identifier();
        static const ELiteral structure ();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid    = 0,
            kBoolean    = 1,
            kInteger    = 2,
            kReal       = 3,
            kString     = 4,
            kBinary     = 5,
            kReference  = 6,
            kIdentifier = 7,
            kStructure  = 8,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field literal
    const ELiteral& literal        ()                        const;
    // Setter method for the data field literal
    Type&           set_literal    (const ELiteral& literal);
    // Provides mutable access to field literal
    ELiteral&       mutable_literal();

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EKind
    {
    public:
        // Default constructor - sets the value to invalid
                             EKind     ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EKind     (long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                    const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                    const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const EKind& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EKind& rValue) const;

        // static methods for enum class objects
        static const EKind invalid();
        static const EKind builtin();
        static const EKind object ();
        static const EKind string ();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
            kBuiltin = 1,
            kObject  = 2,
            kString  = 3,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field kind
    const EKind& kind        ()                             const;
    // Setter method for the data field kind
    Type&        set_kind    (const EKind& kind);
    // Provides mutable access to field kind
    EKind&       mutable_kind();

    // Setter method for the data field sourceId
    Type&        set_sourceId(const SourceIdSPtr& sourceId);

    // Setter method for the data field line
    Type&        set_line    (const Line& line);

    // Setter method for the data field column
    Type&        set_column  (const Column& column);

private:
    // variable for the data field package
    PackageSPtr mPackage;
    // variable for the data field comment
    CommentSPtr mComment;
    // variable for the data field name
    NameSPtr    mName;
    // variable for the data field literal
    ELiteral    mLiteral;
    // variable for the data field kind
    EKind       mKind;
};

}

}

#else // __COMPIL_DOCUMENT_TYPE_SCOMPIL__PARTIAL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class Type;
typedef Type*                         TypeRPtr;
typedef boost::shared_ptr<Type>       TypeSPtr;
typedef boost::shared_ptr<const Type> TypeSCPtr;
typedef boost::weak_ptr<Type>         TypeWPtr;

class EObjectId;

}

}

#endif // __COMPIL_DOCUMENT_TYPE_SCOMPIL__PARTIAL_H_

