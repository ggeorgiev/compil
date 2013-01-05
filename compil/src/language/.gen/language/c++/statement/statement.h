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

#ifndef __CPP_STATEMENT_STATEMENT_SCOMPIL_H_
#define __CPP_STATEMENT_STATEMENT_SCOMPIL_H_

#include "language/c++/statement/statement.h"
// Boost C++ Smart Pointers
#include <boost/enable_shared_from_this.hpp>

namespace lang
{

namespace cpp
{

class Statement : public boost::enable_shared_from_this<Statement>
{
public:
    // Default constructor
                         Statement         ();
    // Destructor
    virtual              ~Statement        ();

    // Identifier for the objects from Statement class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EStatementId staticStatementId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EStatementId runtimeStatementId() const;

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EClose
    {
    public:
        // Default constructor - sets the value to invalid
                             EClose    ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EClose    (long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                     const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                     const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const EClose& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EClose& rValue) const;

        // static methods for enum class objects
        static const EClose invalid();
        static const EClose yes    ();
        static const EClose no     ();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
            kYes     = 1,
            kNo      = 2,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field close
           const EClose&     close        ()                    const;
    // Returns the default value yes of the field close
    static Statement::EClose default_close();
    // Setter method for the data field close
           Statement&        set_close    (const EClose& close);
    // Provides mutable access to field close
           EClose&           mutable_close();
    // Store operator for the data field close
           Statement&        operator<<   (const EClose& close);

private:
    // variable for the data field close
    EClose mClose;
};

// Reference store operator for the data field close
const StatementSPtr& operator<<(const StatementSPtr& , const Statement::EClose& );

inline StatementSPtr statementRef()
{
    return boost::make_shared<Statement>();
}

}

}

#else // __CPP_STATEMENT_STATEMENT_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class Statement;
typedef Statement*                         StatementRPtr;
typedef boost::shared_ptr<Statement>       StatementSPtr;
typedef boost::shared_ptr<const Statement> StatementSCPtr;
typedef boost::weak_ptr<Statement>         StatementWPtr;

class EStatementId;

}

}

#endif // __CPP_STATEMENT_STATEMENT_SCOMPIL_H_
