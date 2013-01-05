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

#ifndef __COMPIL_DOCUMENT_OPERATOR_SCOMPIL_H_
#define __COMPIL_DOCUMENT_OPERATOR_SCOMPIL_H_

#include "language/compil/all/comment.h"
#include "language/compil/all/object.h"
#include "language/compil/document/operator.h"
#include "language/compil/document/operator_action.h"
#include "language/compil/document/operator_flags.h"
#include "language/compil/document/structure.h"
// Compil C++ Template Library
#include "core/compil/flags_enumeration.hpp"

namespace lang
{

namespace compil
{

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

    // Setter method for the data field sourceId
            Operator&              set_sourceId     (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            Operator&              set_line         (const Line& line);

    // Setter method for the data field column
            Operator&              set_column       (const Column& column);

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

}

#else // __COMPIL_DOCUMENT_OPERATOR_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class Operator;
typedef Operator*                         OperatorRPtr;
typedef boost::shared_ptr<Operator>       OperatorSPtr;
typedef boost::shared_ptr<const Operator> OperatorSCPtr;
typedef boost::weak_ptr<Operator>         OperatorWPtr;

class EObjectId;

}

}

#endif // __COMPIL_DOCUMENT_OPERATOR_SCOMPIL_H_

