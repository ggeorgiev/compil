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

#ifndef __CPP_DECLARATOR_PARAMETER_DECLARATOIN_CLAUSE_SCOMPIL_H_
#define __CPP_DECLARATOR_PARAMETER_DECLARATOIN_CLAUSE_SCOMPIL_H_

#include "language/c++/declarator/declarator.h"
#include "language/c++/declarator/parameter_declaratoin_clause.h"
#include "language/c++/declarator/parameter_declaratoin_list.h"

namespace lang
{

namespace cpp
{

class ParameterDeclarationClause : public Declarator
{
public:
    // Default constructor
                                                ParameterDeclarationClause ();
    // Destructor
    virtual                                     ~ParameterDeclarationClause();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ParameterDeclarationClauseSPtr      downcast                   (const DeclaratorSPtr& object);

    // Getter method for the data field declarator
            const ParameterDeclarationListSPtr& declarator                 ()                                               const;
    // Setter method for the data field declarator
            ParameterDeclarationClause&         set_declarator             (const ParameterDeclarationListSPtr& declarator);
    // Store operator for the data field declarator
            ParameterDeclarationClause&         operator<<                 (const ParameterDeclarationListSPtr& declarator);

private:
    // variable for the data field declarator
    ParameterDeclarationListSPtr mDeclarator;
};

// Reference store operator for the data field declarator
const ParameterDeclarationClauseSPtr& operator<<(const ParameterDeclarationClauseSPtr& ,
                                                 const ParameterDeclarationListSPtr& );

inline ParameterDeclarationClauseSPtr parameterDeclarationClauseRef()
{
    return boost::make_shared<ParameterDeclarationClause>();
}

}

}

#else // __CPP_DECLARATOR_PARAMETER_DECLARATOIN_CLAUSE_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class ParameterDeclarationClause;
typedef ParameterDeclarationClause*                         ParameterDeclarationClauseRPtr;
typedef boost::shared_ptr<ParameterDeclarationClause>       ParameterDeclarationClauseSPtr;
typedef boost::shared_ptr<const ParameterDeclarationClause> ParameterDeclarationClauseSCPtr;
typedef boost::weak_ptr<ParameterDeclarationClause>         ParameterDeclarationClauseWPtr;

}

}

#endif // __CPP_DECLARATOR_PARAMETER_DECLARATOIN_CLAUSE_SCOMPIL_H_

