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

#ifndef __COMPIL_ALL_OBJECT_FACTORY_SCOMPIL_H_
#define __COMPIL_ALL_OBJECT_FACTORY_SCOMPIL_H_

#include "language/compil/all/comment.h"
#include "language/compil/all/file.h"
#include "language/compil/all/name.h"
#include "language/compil/all/object.h"
#include "language/compil/all/object_factory.h"
#include "language/compil/all/package.h"
#include "language/compil/all/version.h"
#include "language/compil/document/alter.h"
#include "language/compil/document/default_value.h"
#include "language/compil/document/document.h"
#include "language/compil/document/enumeration.h"
#include "language/compil/document/enumeration_value.h"
#include "language/compil/document/factory.h"
#include "language/compil/document/field.h"
#include "language/compil/document/field_override.h"
#include "language/compil/document/filter.h"
#include "language/compil/document/identification.h"
#include "language/compil/document/identifier.h"
#include "language/compil/document/import.h"
#include "language/compil/document/integer.h"
#include "language/compil/document/interface.h"
#include "language/compil/document/method.h"
#include "language/compil/document/operator.h"
#include "language/compil/document/parameter.h"
#include "language/compil/document/reference.h"
#include "language/compil/document/specimen.h"
#include "language/compil/document/structure.h"
#include "language/compil/document/type.h"
#include "language/compil/document/unary_container.h"
#include "language/compil/document/unary_template.h"
#include "language/compil/document/upcopy.h"
#include "language/compil/project/file_path.h"
#include "language/compil/project/project.h"
#include "language/compil/project/section.h"

namespace lang
{

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
    static const EObjectId file                    ();
    static const EObjectId filePath                ();
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
    static const EObjectId project                 ();
    static const EObjectId reference               ();
    static const EObjectId section                 ();
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
        kFile                     = 12,
        kFilePath                 = 13,
        kFilter                   = 14,
        kIdentification           = 15,
        kIdentifier               = 16,
        kImport                   = 17,
        kInteger                  = 18,
        kInterface                = 19,
        kMethod                   = 20,
        kName                     = 21,
        kObject                   = 22,
        kOperator                 = 23,
        kPackage                  = 24,
        kParameter                = 25,
        kProject                  = 26,
        kReference                = 27,
        kSection                  = 28,
        kSpecimen                 = 29,
        kStructure                = 30,
        kType                     = 31,
        kUnaryContainer           = 32,
        kUnaryTemplate            = 33,
        kUpcopy                   = 34,
        kVersion                  = 35,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class ObjectFactory
{
public:
    static ObjectSPtr                   clone                           (const ObjectSPtr& object);
    static AbsoluteEnumerationValueSPtr downcastAbsoluteEnumerationValue(const ObjectSPtr& object);
    static AlterSPtr                    downcastAlter                   (const ObjectSPtr& object);
    static CommentSPtr                  downcastComment                 (const ObjectSPtr& object);
    static ComposedEnumerationValueSPtr downcastComposedEnumerationValue(const ObjectSPtr& object);
    static DefaultValueSPtr             downcastDefaultValue            (const ObjectSPtr& object);
    static DocumentSPtr                 downcastDocument                (const ObjectSPtr& object);
    static EnumerationSPtr              downcastEnumeration             (const ObjectSPtr& object);
    static EnumerationValueSPtr         downcastEnumerationValue        (const ObjectSPtr& object);
    static FactorySPtr                  downcastFactory                 (const ObjectSPtr& object);
    static FieldSPtr                    downcastField                   (const ObjectSPtr& object);
    static FieldOverrideSPtr            downcastFieldOverride           (const ObjectSPtr& object);
    static FileSPtr                     downcastFile                    (const ObjectSPtr& object);
    static FilePathSPtr                 downcastFilePath                (const ObjectSPtr& object);
    static FilterSPtr                   downcastFilter                  (const ObjectSPtr& object);
    static IdentificationSPtr           downcastIdentification          (const ObjectSPtr& object);
    static IdentifierSPtr               downcastIdentifier              (const ObjectSPtr& object);
    static ImportSPtr                   downcastImport                  (const ObjectSPtr& object);
    static IntegerSPtr                  downcastInteger                 (const ObjectSPtr& object);
    static InterfaceSPtr                downcastInterface               (const ObjectSPtr& object);
    static MethodSPtr                   downcastMethod                  (const ObjectSPtr& object);
    static NameSPtr                     downcastName                    (const ObjectSPtr& object);
    static OperatorSPtr                 downcastOperator                (const ObjectSPtr& object);
    static PackageSPtr                  downcastPackage                 (const ObjectSPtr& object);
    static ParameterSPtr                downcastParameter               (const ObjectSPtr& object);
    static ProjectSPtr                  downcastProject                 (const ObjectSPtr& object);
    static ReferenceSPtr                downcastReference               (const ObjectSPtr& object);
    static SectionSPtr                  downcastSection                 (const ObjectSPtr& object);
    static SpecimenSPtr                 downcastSpecimen                (const ObjectSPtr& object);
    static StructureSPtr                downcastStructure               (const ObjectSPtr& object);
    static TypeSPtr                     downcastType                    (const ObjectSPtr& object);
    static UnaryContainerSPtr           downcastUnaryContainer          (const ObjectSPtr& object);
    static UnaryTemplateSPtr            downcastUnaryTemplate           (const ObjectSPtr& object);
    static UpcopySPtr                   downcastUpcopy                  (const ObjectSPtr& object);
    static VersionSPtr                  downcastVersion                 (const ObjectSPtr& object);
};

}

}

#else // __COMPIL_ALL_OBJECT_FACTORY_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class ObjectFactory;
typedef ObjectFactory*                         ObjectFactoryRPtr;
typedef boost::shared_ptr<ObjectFactory>       ObjectFactorySPtr;
typedef boost::shared_ptr<const ObjectFactory> ObjectFactorySCPtr;
typedef boost::weak_ptr<ObjectFactory>         ObjectFactoryWPtr;

class EObjectId;
typedef EObjectId*                         EObjectIdRPtr;
typedef boost::shared_ptr<EObjectId>       EObjectIdSPtr;
typedef boost::shared_ptr<const EObjectId> EObjectIdSCPtr;
typedef boost::weak_ptr<EObjectId>         EObjectIdWPtr;

class ObjectFactory;

}

}

#endif // __COMPIL_ALL_OBJECT_FACTORY_SCOMPIL_H_

