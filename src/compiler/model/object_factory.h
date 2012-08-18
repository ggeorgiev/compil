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

#ifndef __GENERATOR_SELF_COMPILER_MODEL_OBJECT_FACTORY_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_OBJECT_FACTORY_COMPIL_H_

#include "alter.h"
#include "comment.h"
#include "default_value.h"
#include "document.h"
#include "enumeration.h"
#include "enumeration_value.h"
#include "factory.h"
#include "field.h"
#include "field_override.h"
#include "filter.h"
#include "identification.h"
#include "identifier.h"
#include "import.h"
#include "integer.h"
#include "interface.h"
#include "method.h"
#include "name.h"
#include "object.h"
#include "object_factory.h"
#include "operator.h"
#include "package.h"
#include "parameter.h"
#include "reference.h"
#include "specimen.h"
#include "structure.h"
#include "type.h"
#include "unary_container.h"
#include "unary_template.h"
#include "upcopy.h"
#include "version.h"

namespace compil
{

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EObjectId
{
public:
    // Default constructor - sets the value to invalid
                         EObjectId ();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EObjectId (long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value     ()                        const;
    // Returns short name for a specified enum value
    static   const char* shortName (long value);
    // Returns short name of the enum value
             const char* shortName ()                        const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==(const EObjectId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=(const EObjectId& rValue) const;

    // static methods for enum class objects
    static const EObjectId invalid                 ();
    static const EObjectId absoluteEnumerationValue();
    static const EObjectId alter                   ();
    static const EObjectId comment                 ();
    static const EObjectId composedEnumerationValue();
    static const EObjectId defaultValue            ();
    static const EObjectId document                ();
    static const EObjectId enumeration             ();
    static const EObjectId enumerationValue        ();
    static const EObjectId factory                 ();
    static const EObjectId field                   ();
    static const EObjectId fieldOverride           ();
    static const EObjectId filter                  ();
    static const EObjectId identification          ();
    static const EObjectId identifier              ();
    static const EObjectId import                  ();
    static const EObjectId integer                 ();
    static const EObjectId interface_              ();
    static const EObjectId method                  ();
    static const EObjectId name                    ();
    static const EObjectId object                  ();
    static const EObjectId operator_               ();
    static const EObjectId package                 ();
    static const EObjectId parameter               ();
    static const EObjectId reference               ();
    static const EObjectId specimen                ();
    static const EObjectId structure               ();
    static const EObjectId type                    ();
    static const EObjectId unaryContainer          ();
    static const EObjectId unaryTemplate           ();
    static const EObjectId upcopy                  ();
    static const EObjectId version                 ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid                  = 0,
        kAbsoluteEnumerationValue = 1,
        kAlter                    = 2,
        kComment                  = 3,
        kComposedEnumerationValue = 4,
        kDefaultValue             = 5,
        kDocument                 = 6,
        kEnumeration              = 7,
        kEnumerationValue         = 8,
        kFactory                  = 9,
        kField                    = 10,
        kFieldOverride            = 11,
        kFilter                   = 12,
        kIdentification           = 13,
        kIdentifier               = 14,
        kImport                   = 15,
        kInteger                  = 16,
        kInterface                = 17,
        kMethod                   = 18,
        kName                     = 19,
        kObject                   = 20,
        kOperator                 = 21,
        kPackage                  = 22,
        kParameter                = 23,
        kReference                = 24,
        kSpecimen                 = 25,
        kStructure                = 26,
        kType                     = 27,
        kUnaryContainer           = 28,
        kUnaryTemplate            = 29,
        kUpcopy                   = 30,
        kVersion                  = 31,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class ObjectFactory
{
public:
    static ObjectSPtr                   clone                           (const ObjectSPtr& pObject);
    static AbsoluteEnumerationValueSPtr downcastAbsoluteEnumerationValue(const ObjectSPtr& pObject);
    static AlterSPtr                    downcastAlter                   (const ObjectSPtr& pObject);
    static CommentSPtr                  downcastComment                 (const ObjectSPtr& pObject);
    static ComposedEnumerationValueSPtr downcastComposedEnumerationValue(const ObjectSPtr& pObject);
    static DefaultValueSPtr             downcastDefaultValue            (const ObjectSPtr& pObject);
    static DocumentSPtr                 downcastDocument                (const ObjectSPtr& pObject);
    static EnumerationSPtr              downcastEnumeration             (const ObjectSPtr& pObject);
    static EnumerationValueSPtr         downcastEnumerationValue        (const ObjectSPtr& pObject);
    static FactorySPtr                  downcastFactory                 (const ObjectSPtr& pObject);
    static FieldSPtr                    downcastField                   (const ObjectSPtr& pObject);
    static FieldOverrideSPtr            downcastFieldOverride           (const ObjectSPtr& pObject);
    static FilterSPtr                   downcastFilter                  (const ObjectSPtr& pObject);
    static IdentificationSPtr           downcastIdentification          (const ObjectSPtr& pObject);
    static IdentifierSPtr               downcastIdentifier              (const ObjectSPtr& pObject);
    static ImportSPtr                   downcastImport                  (const ObjectSPtr& pObject);
    static IntegerSPtr                  downcastInteger                 (const ObjectSPtr& pObject);
    static InterfaceSPtr                downcastInterface               (const ObjectSPtr& pObject);
    static MethodSPtr                   downcastMethod                  (const ObjectSPtr& pObject);
    static NameSPtr                     downcastName                    (const ObjectSPtr& pObject);
    static OperatorSPtr                 downcastOperator                (const ObjectSPtr& pObject);
    static PackageSPtr                  downcastPackage                 (const ObjectSPtr& pObject);
    static ParameterSPtr                downcastParameter               (const ObjectSPtr& pObject);
    static ReferenceSPtr                downcastReference               (const ObjectSPtr& pObject);
    static SpecimenSPtr                 downcastSpecimen                (const ObjectSPtr& pObject);
    static StructureSPtr                downcastStructure               (const ObjectSPtr& pObject);
    static TypeSPtr                     downcastType                    (const ObjectSPtr& pObject);
    static UnaryContainerSPtr           downcastUnaryContainer          (const ObjectSPtr& pObject);
    static UnaryTemplateSPtr            downcastUnaryTemplate           (const ObjectSPtr& pObject);
    static UpcopySPtr                   downcastUpcopy                  (const ObjectSPtr& pObject);
    static VersionSPtr                  downcastVersion                 (const ObjectSPtr& pObject);
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_OBJECT_FACTORY_COMPIL_H_

namespace compil
{

// Forward declarations
class ObjectFactory;
typedef ObjectFactory*                         ObjectFactoryRPtr;
typedef boost::shared_ptr<ObjectFactory>       ObjectFactorySPtr;
typedef boost::shared_ptr<const ObjectFactory> ObjectFactorySCPtr;
typedef boost::weak_ptr<ObjectFactory>         ObjectFactoryWPtr;

class EObjectId;
typedef EObjectId*                         ObjectIdRPtr;
typedef boost::shared_ptr<EObjectId>       ObjectIdSPtr;
typedef boost::shared_ptr<const EObjectId> ObjectIdSCPtr;
typedef boost::weak_ptr<EObjectId>         ObjectIdWPtr;

class ObjectFactory;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_OBJECT_FACTORY_COMPIL_H_

