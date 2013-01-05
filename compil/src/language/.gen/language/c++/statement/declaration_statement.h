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

#ifndef __CPP_STATEMENT_DECLARATION_STATEMENT_SCOMPIL_H_
#define __CPP_STATEMENT_DECLARATION_STATEMENT_SCOMPIL_H_

#include "language/c++/declaration/block_declaration.h"
#include "language/c++/statement/declaration_statement.h"
#include "language/c++/statement/statement.h"

namespace lang
{

namespace cpp
{

class DeclarationStatement : public Statement
{
public:
    // Default constructor
                                        DeclarationStatement ();
    // Destructor
    virtual                             ~DeclarationStatement();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  DeclarationStatementSPtr    downcast             (const StatementSPtr& object);
    // shared_from_this is a helper method that overrides the
    // shared_from_this method that is implemented in
    // boost::enable_shared_from_this base class. The only purpose of this
    // helper method is to eliminate the need of downcasting to shared_ptr
    // to this class.
            DeclarationStatementSPtr    shared_from_this     ();
    // This method is exactly the same as the previous one with exception
    // that it allows shared_from_this to be called from const methods.
            DeclarationStatementSCPtr   shared_from_this     ()                                        const;

    // Identifier for the objects from DeclarationStatement class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EStatementId                staticStatementId    ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EStatementId                runtimeStatementId   ()                                        const;

    // Getter method for the data field declaration
            const BlockDeclarationSPtr& declaration          ()                                        const;
    // Setter method for the data field declaration
            DeclarationStatement&       set_declaration      (const BlockDeclarationSPtr& declaration);
    // Store operator for the data field declaration
            DeclarationStatement&       operator<<           (const BlockDeclarationSPtr& declaration);

    // Setter method for the data field close
            DeclarationStatement&       set_close            (const EClose& close);
    // Store operator for the data field close
            DeclarationStatement&       operator<<           (const EClose& close);

private:
    // variable for the data field declaration
    BlockDeclarationSPtr mDeclaration;
};

// Reference store operator for the data field close
const DeclarationStatementSPtr& operator<<(const DeclarationStatementSPtr& , const Statement::EClose& );
// Reference store operator for the data field declaration
const DeclarationStatementSPtr& operator<<(const DeclarationStatementSPtr& , const BlockDeclarationSPtr& );

inline DeclarationStatementSPtr declarationStatementRef()
{
    return boost::make_shared<DeclarationStatement>();
}

}

}

#else // __CPP_STATEMENT_DECLARATION_STATEMENT_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class DeclarationStatement;
typedef DeclarationStatement*                         DeclarationStatementRPtr;
typedef boost::shared_ptr<DeclarationStatement>       DeclarationStatementSPtr;
typedef boost::shared_ptr<const DeclarationStatement> DeclarationStatementSCPtr;
typedef boost::weak_ptr<DeclarationStatement>         DeclarationStatementWPtr;

class EStatementId;

}

}

#endif // __CPP_STATEMENT_DECLARATION_STATEMENT_SCOMPIL_H_

