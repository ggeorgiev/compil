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
#include <string>

#ifndef __GENERATOR_SELF_GENERATOR_CPP_FORMAT_SIMPLE_TYPE_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_CPP_FORMAT_SIMPLE_TYPE_COMPIL_H_

#include "namespace.h"
#include "simple_type.h"

namespace cpp
{

namespace frm
{

class SimpleType
{
public:
    // Default constructor
                                 SimpleType   ();
    // Destructor
    /*lax*/                      ~SimpleType  ();

    // Getter method for the data field namespace
            const NamespaceSPtr& namespace_   ()                                const;
    // Setter method for the data field namespace
            SimpleType&          set_namespace(const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            SimpleType&          operator<<   (const NamespaceSPtr& namespace_);

    // Getter method for the data field value
            const std::string&   value        ()                                const;
    // Setter method for the data field value
            SimpleType&          set_value    (const std::string& value);
    // Provides mutable access to field value
            std::string&         mutable_value();
    // Store operator for the data field value
            SimpleType&          operator<<   (const std::string& value);

private:
    // variable for the data field namespace
    NamespaceSPtr mNamespace;
    // variable for the data field value
    std::string   mValue;
};

// Reference store operator for the data field namespace
const SimpleTypeSPtr& operator<<(const SimpleTypeSPtr& , const NamespaceSPtr& );
// Reference store operator for the data field value
const SimpleTypeSPtr& operator<<(const SimpleTypeSPtr& , const std::string& );

inline SimpleTypeSPtr simpleTypeRef()
{
    return boost::make_shared<SimpleType>();
}

}

}

#else // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_SIMPLE_TYPE_COMPIL_H_

namespace cpp
{

namespace frm
{

// Forward declarations
class SimpleType;
typedef SimpleType*                         SimpleTypeRPtr;
typedef boost::shared_ptr<SimpleType>       SimpleTypeSPtr;
typedef boost::shared_ptr<const SimpleType> SimpleTypeSCPtr;
typedef boost::weak_ptr<SimpleType>         SimpleTypeWPtr;

}

}

#endif // __GENERATOR_SELF_GENERATOR_CPP_FORMAT_SIMPLE_TYPE_COMPIL_H_

