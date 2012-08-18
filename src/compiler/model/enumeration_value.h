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
// Standard Template Library
#include <vector>

#ifndef __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_VALUE_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_VALUE_COMPIL_H_

#include "comment.h"
#include "enumeration.h"
#include "enumeration_value.h"
#include "name.h"
#include "object.h"

namespace compil
{

class EnumerationValue : public Object
{
public:
    // Default constructor
                                   EnumerationValue ();
    // Destructor
    virtual                        ~EnumerationValue();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  EnumerationValueSPtr   downcast         (const ObjectSPtr& pObject);

    // Identifier for the objects from EnumerationValue class.
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
    virtual EObjectId              runtimeObjectId  ()                                   const;

    // Getter method for the data field enumeration
            const EnumerationWPtr& enumeration      ()                                   const;
    // Setter method for the data field enumeration
            void                   set_enumeration  (const EnumerationSPtr& enumeration);

    // Getter method for the data field comment
            const CommentSPtr&     comment          ()                                   const;
    // Setter method for the data field comment
            void                   set_comment      (const CommentSPtr& comment);

    // Getter method for the data field name
            const NameSPtr&        name             ()                                   const;
    // Setter method for the data field name
            void                   set_name         (const NameSPtr& name);

private:
    // variable for the data field enumeration
    EnumerationWPtr mEnumeration;
    // variable for the data field comment
    CommentSPtr     mComment;
    // variable for the data field name
    NameSPtr        mName;
};

class AbsoluteEnumerationValue : public EnumerationValue
{
public:
    // Default constructor
                                         AbsoluteEnumerationValue ();
    // Destructor
    virtual                              ~AbsoluteEnumerationValue();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  AbsoluteEnumerationValueSPtr downcast                 (const ObjectSPtr& pObject);

    // Identifier for the objects from AbsoluteEnumerationValue class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId                    staticObjectId           ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId                    runtimeObjectId          ()                          const;

    // Getter method for the data field value
            long                         value                    ()                          const;
    // Setter method for the data field value
            void                         set_value                (long value);

private:
    // variable for the data field value
    long mValue;
};

class ComposedEnumerationValue : public EnumerationValue
{
public:
    // Default constructor
                                                     ComposedEnumerationValue ();
    // Destructor
    virtual                                          ~ComposedEnumerationValue();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ComposedEnumerationValueSPtr             downcast                 (const ObjectSPtr& pObject);

    // Identifier for the objects from ComposedEnumerationValue class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId                                staticObjectId           ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId                                runtimeObjectId          ()                                                const;

    // Getter method for the data field values
            const std::vector<EnumerationValueSPtr>& values                   ()                                                const;
    // Setter method for the data field values
            void                                     set_values               (const std::vector<EnumerationValueSPtr>& values);

private:
    // variable for the data field values
    std::vector<EnumerationValueSPtr> mValues;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_VALUE_COMPIL_H_

namespace compil
{

// Forward declarations
class EnumerationValue;
typedef EnumerationValue*                         EnumerationValueRPtr;
typedef boost::shared_ptr<EnumerationValue>       EnumerationValueSPtr;
typedef boost::shared_ptr<const EnumerationValue> EnumerationValueSCPtr;
typedef boost::weak_ptr<EnumerationValue>         EnumerationValueWPtr;

class EObjectId;

class AbsoluteEnumerationValue;
typedef AbsoluteEnumerationValue*                         AbsoluteEnumerationValueRPtr;
typedef boost::shared_ptr<AbsoluteEnumerationValue>       AbsoluteEnumerationValueSPtr;
typedef boost::shared_ptr<const AbsoluteEnumerationValue> AbsoluteEnumerationValueSCPtr;
typedef boost::weak_ptr<AbsoluteEnumerationValue>         AbsoluteEnumerationValueWPtr;

class EObjectId;

class ComposedEnumerationValue;
typedef ComposedEnumerationValue*                         ComposedEnumerationValueRPtr;
typedef boost::shared_ptr<ComposedEnumerationValue>       ComposedEnumerationValueSPtr;
typedef boost::shared_ptr<const ComposedEnumerationValue> ComposedEnumerationValueSCPtr;
typedef boost::weak_ptr<ComposedEnumerationValue>         ComposedEnumerationValueWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_ENUMERATION_VALUE_COMPIL_H_

