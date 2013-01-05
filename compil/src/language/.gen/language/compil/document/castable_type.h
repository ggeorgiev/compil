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

#ifndef __COMPIL_DOCUMENT_CASTABLE_TYPE_SCOMPIL_H_
#define __COMPIL_DOCUMENT_CASTABLE_TYPE_SCOMPIL_H_

#include "language/compil/document/castable_type.h"
#include "language/compil/document/type.h"

namespace lang
{

namespace compil
{

class CastableType : public Type
{
public:
    // Default constructor
                             CastableType ();
    // Destructor
    virtual                  ~CastableType();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  CastableTypeSPtr downcast     (const ObjectSPtr& object);

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class ECast
    {
    public:
        // Default constructor - sets the value to invalid
                             ECast     ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             ECast     (long value);

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
                 bool        operator==(const ECast& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const ECast& rValue) const;

        // static methods for enum class objects
        static const ECast invalid();
        static const ECast weak   ();
        static const ECast strong ();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
            kWeak    = 1,
            kStrong  = 2,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field cast
    const ECast&  cast        ()                             const;
    // Setter method for the data field cast
    CastableType& set_cast    (const ECast& cast);
    // Provides mutable access to field cast
    ECast&        mutable_cast();

    // Setter method for the data field sourceId
    CastableType& set_sourceId(const SourceIdSPtr& sourceId);

    // Setter method for the data field line
    CastableType& set_line    (const Line& line);

    // Setter method for the data field column
    CastableType& set_column  (const Column& column);

    // Setter method for the data field package
    CastableType& set_package (const PackageSPtr& package);

    // Setter method for the data field comment
    CastableType& set_comment (const CommentSPtr& comment);

    // Setter method for the data field name
    CastableType& set_name    (const NameSPtr& name);

    // Setter method for the data field literal
    CastableType& set_literal (const ELiteral& literal);

    // Setter method for the data field kind
    CastableType& set_kind    (const EKind& kind);

private:
    // variable for the data field cast
    ECast mCast;
};

}

}

#else // __COMPIL_DOCUMENT_CASTABLE_TYPE_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class CastableType;
typedef CastableType*                         CastableTypeRPtr;
typedef boost::shared_ptr<CastableType>       CastableTypeSPtr;
typedef boost::shared_ptr<const CastableType> CastableTypeSCPtr;
typedef boost::weak_ptr<CastableType>         CastableTypeWPtr;

}

}

#endif // __COMPIL_DOCUMENT_CASTABLE_TYPE_SCOMPIL_H_

