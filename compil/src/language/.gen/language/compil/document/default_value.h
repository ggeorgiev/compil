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
#include <string>

#ifndef __COMPIL_DOCUMENT_DEFAULT_VALUE_SCOMPIL_H_
#define __COMPIL_DOCUMENT_DEFAULT_VALUE_SCOMPIL_H_

#include "language/compil/all/object.h"
#include "language/compil/document/default_value.h"

namespace lang
{

namespace compil
{

class DefaultValue : public Object
{
public:
    // Default constructor
                               DefaultValue    ();
    // Destructor
    virtual                    ~DefaultValue   ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  DefaultValueSPtr   downcast        (const ObjectSPtr& object);

    // Identifier for the objects from DefaultValue class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId          staticObjectId  ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId          runtimeObjectId ()                             const;

    // Getter method for the data field optional
            bool               optional        ()                             const;
    // Returns the default value false of the field optional
    static  bool               default_optional();
    // Setter method for the data field optional
            DefaultValue&      set_optional    (bool optional);

    // Getter method for the data field value
            const std::string& value           ()                             const;
    // Setter method for the data field value
            DefaultValue&      set_value       (const std::string& value);
    // Provides mutable access to field value
            std::string&       mutable_value   ();

    // Setter method for the data field sourceId
            DefaultValue&      set_sourceId    (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            DefaultValue&      set_line        (const Line& line);

    // Setter method for the data field column
            DefaultValue&      set_column      (const Column& column);

private:
    // variable for the data field optional
    bool        mOptional;
    // variable for the data field value
    std::string mValue;
};

}

}

#else // __COMPIL_DOCUMENT_DEFAULT_VALUE_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class DefaultValue;
typedef DefaultValue*                         DefaultValueRPtr;
typedef boost::shared_ptr<DefaultValue>       DefaultValueSPtr;
typedef boost::shared_ptr<const DefaultValue> DefaultValueSCPtr;
typedef boost::weak_ptr<DefaultValue>         DefaultValueWPtr;

class EObjectId;

}

}

#endif // __COMPIL_DOCUMENT_DEFAULT_VALUE_SCOMPIL_H_

