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

#ifndef __CPP_CLASS_CLASS_NAME_FACTORY_SCOMPIL_H_
#define __CPP_CLASS_CLASS_NAME_FACTORY_SCOMPIL_H_

#include "language/c++/class/class_name.h"
#include "language/c++/class/class_name_factory.h"
#include "language/c++/class/identifier_class_name.h"

namespace lang
{

namespace cpp
{

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EClassNameId
{
public:
    // Default constructor - sets the value to invalid
                         EClassNameId();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EClassNameId(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value       ()                           const;
    // Returns short name for a specified enum value
    static   const char* shortName   (long value);
    // Returns short name of the enum value
             const char* shortName   ()                           const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==  (const EClassNameId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=  (const EClassNameId& rValue) const;

    // static methods for enum class objects
    static const EClassNameId invalid            ();
    static const EClassNameId className          ();
    static const EClassNameId identifierClassName();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid             = 0,
        kClassName           = 1,
        kIdentifierClassName = 2,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class ClassNameFactory
{
public:
    static ClassNameSPtr           clone                      (const ClassNameSPtr& object);
    static IdentifierClassNameSPtr downcastIdentifierClassName(const ClassNameSPtr& object);
};

}

}

#else // __CPP_CLASS_CLASS_NAME_FACTORY_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class ClassNameFactory;
typedef ClassNameFactory*                         ClassNameFactoryRPtr;
typedef boost::shared_ptr<ClassNameFactory>       ClassNameFactorySPtr;
typedef boost::shared_ptr<const ClassNameFactory> ClassNameFactorySCPtr;
typedef boost::weak_ptr<ClassNameFactory>         ClassNameFactoryWPtr;

class EClassNameId;
typedef EClassNameId*                         EClassNameIdRPtr;
typedef boost::shared_ptr<EClassNameId>       EClassNameIdSPtr;
typedef boost::shared_ptr<const EClassNameId> EClassNameIdSCPtr;
typedef boost::weak_ptr<EClassNameId>         EClassNameIdWPtr;

class ClassNameFactory;

}

}

#endif // __CPP_CLASS_CLASS_NAME_FACTORY_SCOMPIL_H_

