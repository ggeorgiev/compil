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
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#ifndef __CPP_EXPRESSION_EQUALITY_EXPRESSION_SCOMPIL_H_
#define __CPP_EXPRESSION_EQUALITY_EXPRESSION_SCOMPIL_H_

#include "language/c++/expression/equality_expression.h"
#include "language/c++/expression/expression.h"

namespace lang
{

namespace cpp
{

class EqualityExpression : public Expression
{
public:
    // Default constructor
                                   EqualityExpression ();
    // Destructor
    virtual                        ~EqualityExpression();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  EqualityExpressionSPtr downcast           (const ExpressionSPtr& object);

    // Identifier for the objects from EqualityExpression class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EExpressionId          staticExpressionId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EExpressionId          runtimeExpressionId()                             const;

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EType
    {
    public:
        // Default constructor - sets the value to invalid
                             EType     ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EType     (long value);

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
                 bool        operator==(const EType& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EType& rValue) const;

        // static methods for enum class objects
        static const EType invalid   ();
        static const EType equalTo   ();
        static const EType notEqualTo();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid    = 0,
            kEqualTo    = 1,
            kNotEqualTo = 2,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field type
    const EType&        type        ()                  const;
    // Setter method for the data field type
    EqualityExpression& set_type    (const EType& type);
    // Provides mutable access to field type
    EType&              mutable_type();
    // Store operator for the data field type
    EqualityExpression& operator<<  (const EType& type);

private:
    // variable for the data field type
    EType mType;
};

// Reference store operator for the data field type
const EqualityExpressionSPtr& operator<<(const EqualityExpressionSPtr& , const EqualityExpression::EType& );

inline EqualityExpressionSPtr equalityExpressionRef()
{
    return boost::make_shared<EqualityExpression>();
}

}

}

#else // __CPP_EXPRESSION_EQUALITY_EXPRESSION_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class EqualityExpression;
typedef EqualityExpression*                         EqualityExpressionRPtr;
typedef boost::shared_ptr<EqualityExpression>       EqualityExpressionSPtr;
typedef boost::shared_ptr<const EqualityExpression> EqualityExpressionSCPtr;
typedef boost::weak_ptr<EqualityExpression>         EqualityExpressionWPtr;

class EExpressionId;

}

}

#endif // __CPP_EXPRESSION_EQUALITY_EXPRESSION_SCOMPIL_H_

