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
// Standard Template Library
#include <vector>

#ifndef __CPP_STATEMENT_COMPOUND_STATEMENT_SCOMPIL_H_
#define __CPP_STATEMENT_COMPOUND_STATEMENT_SCOMPIL_H_

#include "language/c++/statement/compound_statement.h"
#include "language/c++/statement/statement.h"

namespace lang
{

namespace cpp
{

class CompoundStatement : public Statement
{
public:
    // Default constructor
                                              CompoundStatement ();
    // Destructor
    virtual                                   ~CompoundStatement();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  CompoundStatementSPtr             downcast          (const StatementSPtr& object);

    // Returns the alter value no of the field close
    static  Statement::EClose                 alter_close       ();

    // Identifier for the objects from CompoundStatement class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EStatementId                      staticStatementId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EStatementId                      runtimeStatementId()                                             const;

    // Getter method for the data field statements
            const std::vector<StatementSPtr>& statements        ()                                             const;
    // Setter method for the data field statements
            CompoundStatement&                set_statements    (const std::vector<StatementSPtr>& statements);
    // Provides mutable access to field statements
            std::vector<StatementSPtr>&       mutable_statements();
    // Store operator for the data field statements
            CompoundStatement&                operator<<        (const std::vector<StatementSPtr>& statements);
    // Store operator for an item of data field statements
            CompoundStatement&                operator<<        (const StatementSPtr& statementsItem);

    // Setter method for the data field close
            CompoundStatement&                set_close         (const EClose& close);
    // Store operator for the data field close
            CompoundStatement&                operator<<        (const EClose& close);

private:
    // variable for the data field statements
    std::vector<StatementSPtr> mStatements;
};

// Reference store operator for the data field close
const CompoundStatementSPtr& operator<<(const CompoundStatementSPtr& , const Statement::EClose& );
// Reference store operator for the data field statements
const CompoundStatementSPtr& operator<<(const CompoundStatementSPtr& , const std::vector<StatementSPtr>& );
// Reference store operator for an item of data field statements
const CompoundStatementSPtr& operator<<(const CompoundStatementSPtr& , const StatementSPtr& );

inline CompoundStatementSPtr compoundStatementRef()
{
    return boost::make_shared<CompoundStatement>();
}

}

}

#else // __CPP_STATEMENT_COMPOUND_STATEMENT_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class CompoundStatement;
typedef CompoundStatement*                         CompoundStatementRPtr;
typedef boost::shared_ptr<CompoundStatement>       CompoundStatementSPtr;
typedef boost::shared_ptr<const CompoundStatement> CompoundStatementSCPtr;
typedef boost::weak_ptr<CompoundStatement>         CompoundStatementWPtr;

class EStatementId;

}

}

#endif // __CPP_STATEMENT_COMPOUND_STATEMENT_SCOMPIL_H_

