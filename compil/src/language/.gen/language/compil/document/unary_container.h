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

#ifndef __COMPIL_DOCUMENT_UNARY_CONTAINER_SCOMPIL_H_
#define __COMPIL_DOCUMENT_UNARY_CONTAINER_SCOMPIL_H_

#include "language/compil/document/unary_container.h"
#include "language/compil/document/unary_template.h"

namespace lang
{

namespace compil
{

class UnaryContainer : public UnaryTemplate
{
public:
    // Default constructor
                               UnaryContainer ();
    // Destructor
    virtual                    ~UnaryContainer();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  UnaryContainerSPtr downcast       (const ObjectSPtr& object);

    // Identifier for the objects from UnaryContainer class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId          staticObjectId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId          runtimeObjectId()                         const;

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class ESize
    {
    public:
        // Default constructor - sets the value to invalid
                             ESize     ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             ESize     (long value);

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
                 bool        operator==(const ESize& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const ESize& rValue) const;

        // static methods for enum class objects
        static const ESize invalid();
        static const ESize fixed  ();
        static const ESize dynamic();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
            kFixed   = 1,
            kDynamic = 2,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field size
    const ESize&    size             ()                              const;
    // Setter method for the data field size
    UnaryContainer& set_size         (const ESize& size);
    // Provides mutable access to field size
    ESize&          mutable_size     ();

    // Setter method for the data field sourceId
    UnaryContainer& set_sourceId     (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
    UnaryContainer& set_line         (const Line& line);

    // Setter method for the data field column
    UnaryContainer& set_column       (const Column& column);

    // Setter method for the data field package
    UnaryContainer& set_package      (const PackageSPtr& package);

    // Setter method for the data field comment
    UnaryContainer& set_comment      (const CommentSPtr& comment);

    // Setter method for the data field name
    UnaryContainer& set_name         (const NameSPtr& name);

    // Setter method for the data field literal
    UnaryContainer& set_literal      (const ELiteral& literal);

    // Setter method for the data field kind
    UnaryContainer& set_kind         (const EKind& kind);

    // Setter method for the data field cast
    UnaryContainer& set_cast         (const ECast& cast);

    // Setter method for the data field parameterType
    UnaryContainer& set_parameterType(const TypeSPtr& parameterType);

private:
    // variable for the data field size
    ESize mSize;
};

}

}

#else // __COMPIL_DOCUMENT_UNARY_CONTAINER_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class UnaryContainer;
typedef UnaryContainer*                         UnaryContainerRPtr;
typedef boost::shared_ptr<UnaryContainer>       UnaryContainerSPtr;
typedef boost::shared_ptr<const UnaryContainer> UnaryContainerSCPtr;
typedef boost::weak_ptr<UnaryContainer>         UnaryContainerWPtr;

class EObjectId;

}

}

#endif // __COMPIL_DOCUMENT_UNARY_CONTAINER_SCOMPIL_H_

