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

#ifndef __CPP_DECLARATION_DECLARATION_FACTORY_SCOMPIL_H_
#define __CPP_DECLARATION_DECLARATION_FACTORY_SCOMPIL_H_

#include "language/c++/declaration/block_declaration.h"
#include "language/c++/declaration/class_declaration.h"
#include "language/c++/declaration/class_type_name.h"
#include "language/c++/declaration/declaration.h"
#include "language/c++/declaration/declaration_factory.h"
#include "language/c++/declaration/declaration_specifier.h"
#include "language/c++/declaration/declaration_specifier_sequence.h"
#include "language/c++/declaration/simple_block_declaration.h"
#include "language/c++/declaration/simple_declaration.h"
#include "language/c++/declaration/simple_type_specifier.h"
#include "language/c++/declaration/type_declaration_specifier.h"
#include "language/c++/declaration/type_name.h"
#include "language/c++/declaration/type_name_simple_type_specifier.h"
#include "language/c++/declaration/type_specifier.h"

namespace lang
{

namespace cpp
{

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EDeclarationId
{
public:
    // Default constructor - sets the value to invalid
                         EDeclarationId();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EDeclarationId(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value         ()                             const;
    // Returns short name for a specified enum value
    static   const char* shortName     (long value);
    // Returns short name of the enum value
             const char* shortName     ()                             const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==    (const EDeclarationId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=    (const EDeclarationId& rValue) const;

    // static methods for enum class objects
    static const EDeclarationId invalid                     ();
    static const EDeclarationId blockDeclaration            ();
    static const EDeclarationId classDeclaration            ();
    static const EDeclarationId classTypeName               ();
    static const EDeclarationId declaration                 ();
    static const EDeclarationId declarationSpecifier        ();
    static const EDeclarationId declarationSpecifierSequence();
    static const EDeclarationId simpleBlockDeclaration      ();
    static const EDeclarationId simpleDeclaration           ();
    static const EDeclarationId simpleTypeSpecifier         ();
    static const EDeclarationId typeDeclarationSpecifier    ();
    static const EDeclarationId typeName                    ();
    static const EDeclarationId typeNameSimpleTypeSpecifier ();
    static const EDeclarationId typeSpecifier               ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid                      = 0,
        kBlockDeclaration             = 1,
        kClassDeclaration             = 2,
        kClassTypeName                = 3,
        kDeclaration                  = 4,
        kDeclarationSpecifier         = 5,
        kDeclarationSpecifierSequence = 6,
        kSimpleBlockDeclaration       = 7,
        kSimpleDeclaration            = 8,
        kSimpleTypeSpecifier          = 9,
        kTypeDeclarationSpecifier     = 10,
        kTypeName                     = 11,
        kTypeNameSimpleTypeSpecifier  = 12,
        kTypeSpecifier                = 13,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class DeclarationFactory
{
public:
    static DeclarationSPtr                  clone                               (const DeclarationSPtr& object);
    static BlockDeclarationSPtr             downcastBlockDeclaration            (const DeclarationSPtr& object);
    static ClassDeclarationSPtr             downcastClassDeclaration            (const DeclarationSPtr& object);
    static ClassTypeNameSPtr                downcastClassTypeName               (const DeclarationSPtr& object);
    static DeclarationSpecifierSPtr         downcastDeclarationSpecifier        (const DeclarationSPtr& object);
    static DeclarationSpecifierSequenceSPtr downcastDeclarationSpecifierSequence(const DeclarationSPtr& object);
    static SimpleBlockDeclarationSPtr       downcastSimpleBlockDeclaration      (const DeclarationSPtr& object);
    static SimpleDeclarationSPtr            downcastSimpleDeclaration           (const DeclarationSPtr& object);
    static SimpleTypeSpecifierSPtr          downcastSimpleTypeSpecifier         (const DeclarationSPtr& object);
    static TypeDeclarationSpecifierSPtr     downcastTypeDeclarationSpecifier    (const DeclarationSPtr& object);
    static TypeNameSPtr                     downcastTypeName                    (const DeclarationSPtr& object);
    static TypeNameSimpleTypeSpecifierSPtr  downcastTypeNameSimpleTypeSpecifier (const DeclarationSPtr& object);
    static TypeSpecifierSPtr                downcastTypeSpecifier               (const DeclarationSPtr& object);
};

}

}

#else // __CPP_DECLARATION_DECLARATION_FACTORY_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class DeclarationFactory;
typedef DeclarationFactory*                         DeclarationFactoryRPtr;
typedef boost::shared_ptr<DeclarationFactory>       DeclarationFactorySPtr;
typedef boost::shared_ptr<const DeclarationFactory> DeclarationFactorySCPtr;
typedef boost::weak_ptr<DeclarationFactory>         DeclarationFactoryWPtr;

class EDeclarationId;
typedef EDeclarationId*                         EDeclarationIdRPtr;
typedef boost::shared_ptr<EDeclarationId>       EDeclarationIdSPtr;
typedef boost::shared_ptr<const EDeclarationId> EDeclarationIdSCPtr;
typedef boost::weak_ptr<EDeclarationId>         EDeclarationIdWPtr;

class DeclarationFactory;

}

}

#endif // __CPP_DECLARATION_DECLARATION_FACTORY_SCOMPIL_H_

