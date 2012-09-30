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

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_CAST_OPERATOR_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_CAST_OPERATOR_COMPIL_H_

#include "cast_operator.h"
#include "comment.h"
#include "decorated_type.h"
#include "method_declaration.h"
#include "namespace.h"

namespace cpp
{

namespace frm
{

class CastOperator
{
public:
    // Default constructor
                                      CastOperator       ();
    // Destructor
    /*lax*/                           ~CastOperator      ();

    // Getter method for the data field comment
            const CommentSPtr&        comment            ()                                      const;
    // Setter method for the data field comment
            CastOperator&             set_comment        (const CommentSPtr& comment);
    // Store operator for the data field comment
            CastOperator&             operator<<         (const CommentSPtr& comment);

    // Getter method for the data field type
            const DecoratedTypeSPtr&  type               ()                                      const;
    // Setter method for the data field type
            CastOperator&             set_type           (const DecoratedTypeSPtr& type);
    // Store operator for the data field type
            CastOperator&             operator<<         (const DecoratedTypeSPtr& type);

    // Getter method for the data field namespace
            const NamespaceSPtr&      namespace_         ()                                      const;
    // Setter method for the data field namespace
            CastOperator&             set_namespace      (const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            CastOperator&             operator<<         (const NamespaceSPtr& namespace_);

    // Getter method for the data field declaration
            const EMethodDeclaration& declaration        ()                                      const;
    // Setter method for the data field declaration
            CastOperator&             set_declaration    (const EMethodDeclaration& declaration);
    // Provides mutable access to field declaration
            EMethodDeclaration&       mutable_declaration();
    // Store operator for the data field declaration
            CastOperator&             operator<<         (const EMethodDeclaration& declaration);

private:
    // variable for the data field comment
    CommentSPtr        mComment;
    // variable for the data field type
    DecoratedTypeSPtr  mType;
    // variable for the data field namespace
    NamespaceSPtr      mNamespace;
    // variable for the data field declaration
    EMethodDeclaration mDeclaration;
};

// Reference store operator for the data field comment
const CastOperatorSPtr& operator<<(const CastOperatorSPtr& , const CommentSPtr& );
// Reference store operator for the data field type
const CastOperatorSPtr& operator<<(const CastOperatorSPtr& , const DecoratedTypeSPtr& );
// Reference store operator for the data field namespace
const CastOperatorSPtr& operator<<(const CastOperatorSPtr& , const NamespaceSPtr& );
// Reference store operator for the data field declaration
const CastOperatorSPtr& operator<<(const CastOperatorSPtr& , const EMethodDeclaration& );

inline CastOperatorSPtr castOperatorRef()
{
    return boost::make_shared<CastOperator>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_CAST_OPERATOR_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class CastOperator;
typedef CastOperator*                         CastOperatorRPtr;
typedef boost::shared_ptr<CastOperator>       CastOperatorSPtr;
typedef boost::shared_ptr<const CastOperator> CastOperatorSCPtr;
typedef boost::weak_ptr<CastOperator>         CastOperatorWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_CAST_OPERATOR_COMPIL_H_

