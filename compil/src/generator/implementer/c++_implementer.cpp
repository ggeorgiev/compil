// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * The name of George Georgiev can not be used to endorse or
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

#include "implementer/c++_implementer.h"
#include "aligner.h"

#include "library/compil/package.h"

#include "language/compil/all/object_factory.h"

#include "boost/filesystem.hpp"

#include <sstream>

namespace compil
{

cpp::frm::NamespaceSPtr nsStd = cpp::frm::namespaceRef() << cpp::frm::namespaceNameRef("std");
cpp::frm::NamespaceSPtr nsBoost = cpp::frm::namespaceRef() << cpp::frm::namespaceNameRef("boost");
cpp::frm::NamespaceSPtr nsBoostPosixTime = cpp::frm::namespaceRef() << cpp::frm::namespaceNameRef("boost")
                                                                    << cpp::frm::namespaceNameRef("posix_time");

CppImplementer::CppImplementer(const ImplementerConfigurationSPtr& config,
                               const CppFormatterPtr& pFrm,
                               const PackageSPtr& corePackage)
        : mConfiguration(config)
        , mpFrm(pFrm)
        , mCorePackage(corePackage)
{
}

CppImplementer::~CppImplementer()
{
}

bool CppImplementer::needMutableMethod(const FieldSPtr& pField, const StructureSPtr& pCurrentStructure)
{
    TypeSPtr pType = pField->type();

    if (pField->structure().lock() != pCurrentStructure)
        return false;

    switch (pType->kind().value())
    {
        case Type::EKind::kBuiltin:
            return false;
        case Type::EKind::kObject:
            if (ObjectFactory::downcastReference(pType))
                return false;
            return true;
        case Type::EKind::kString:
            switch (mConfiguration->mString)
            {
                case ImplementerConfiguration::use_char_pointer:
                    return false;
                case ImplementerConfiguration::use_stl_string:
                    return true;
                default: assert(false && "unknown string implementation type");
            }
            break;
        case Type::EKind::kInvalid:
        default:
            assert(false && "unknown kind");
    }
    return false;
}

bool CppImplementer::needConstructorInitialization(const FieldSPtr& pField)
{
    if (!pField->defaultValue())
        return false;
    if (pField->defaultValue()->optional())
        return false;
    if (pField->defaultValue()->value() == "null")
    if (mConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers)
        return false;
    return true;
}

cpp::frm::TypeSPtr CppImplementer::cppDecoratedType(const TypeSPtr& pType)
{
    switch (pType->kind().value())
    {
        case Type::EKind::kBuiltin:
            return cppType(pType);
        case Type::EKind::kObject:
            return mpFrm->constTypeRef(cppType(pType));
        case Type::EKind::kString:
            switch (mConfiguration->mString)
            {
                case ImplementerConfiguration::use_char_pointer:
                    return const_char_ptr;
                case ImplementerConfiguration::use_stl_string:
                    return cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                                               << nsStd
                                               << cpp::frm::typeNameRef("string")
                                               << cpp::frm::ETypeDecoration::reference();
                default: assert(false && "unknown string implementation type");
            }
            break;
        case Type::EKind::kInvalid:
        default:
            assert(false && "unknown kind");
    }
	return cpp::frm::TypeSPtr();
}

cpp::frm::TypeSPtr CppImplementer::cppSetDecoratedType(const TypeSPtr& pType)
{
    ReferenceSPtr pReference = ObjectFactory::downcastReference(pType);
    if (pReference)
        return mpFrm->constTypeRef(mpFrm->cppSharedPtrName(pReference->parameterType().lock()));
    return cppDecoratedType(pType);
}

cpp::frm::TypeSPtr CppImplementer::cppInnerDecoratedType(const TypeSPtr& pType,
                                                                  const StructureSPtr& pStructure)
{
    if (pType->runtimeObjectId() == EObjectId::enumeration())
    {
        EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pType);
        return mpFrm->constTypeRef(mpFrm->cppInnerEnumType(pEnumeration, pStructure));
    }
    return cppDecoratedType(pType);
}

cpp::frm::TypeSPtr CppImplementer::cppInnerSetDecoratedType(const TypeSPtr& pType,
                                                                     const StructureSPtr& pStructure)
{
    ReferenceSPtr pReference = ObjectFactory::downcastReference(pType);
    if (pReference)
        return mpFrm->constTypeRef(mpFrm->cppSharedPtrName(pReference->parameterType().lock()));
    return cppInnerDecoratedType(pType, pStructure);
}

std::string CppImplementer::cppGetReturn(const FieldSPtr& pField)
{
    ReferenceSPtr pReference = ObjectFactory::downcastReference(pField->type());
    return mpFrm->cppMemberName(pField);
}

cpp::frm::TypeSPtr CppImplementer::cppType(const TypeSPtr& pType)
{
    ReferenceSPtr pReference = ObjectFactory::downcastReference(pType);
    if (pReference)
    {
        if (pReference->weak())
            return mpFrm->cppWeakPtrName(pReference->parameterType().lock());
        else
            return mpFrm->cppSharedPtrName(pReference->parameterType().lock());
    }

    std::string name = pType->name()->value();
    if (!pType->package())
    {
        if (name == "boolean")
            return cpp::frm::typeRef() << cpp::frm::typeNameRef("bool");

        switch (mConfiguration->mIntegerTypes)
        {
            case ImplementerConfiguration::use_native:
                if (name == "size")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("size_t");
                if (name == "small")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("char");
                if (name == "short")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("short");
                if (name == "integer")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("long");
                if (name == "long")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("long long");
                if (name == "byte")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("unsigned char");
                if (name == "word")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("unsigned short");
                if (name == "dword")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("unsigned long");
                if (name == "qword")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("unsigned long long");
                break;
            case ImplementerConfiguration::use_intnn_t:
                if (name == "size")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("size_t");
                if (name == "small")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("int8_t");
                if (name == "short")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("int16_t");
                if (name == "integer")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("int32_t");
                if (name == "long")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("int64_t");
                if (name == "byte")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("uint8_t");
                if (name == "word")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("uint16_t");
                if (name == "dword")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("uint32_t");
                if (name == "qword")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("uint64_t");
                break;
            case ImplementerConfiguration::use_boost_intnn_t:
                if (name == "size")
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("size_t");
                if (name == "small")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("int8_t");
                if (name == "short")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("int16_t");
                if (name == "integer")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("int32_t");
                if (name == "long")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("int64_t");
                if (name == "byte")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("uint8_t");
                if (name == "word")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("uint16_t");
                if (name == "dword")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("uint32_t");
                if (name == "qword")
                    return cpp::frm::typeRef() << nsBoost
                                               << cpp::frm::typeNameRef("uint64_t");
                break;
            default:
                break;
        }
        if (name == "string")
        {
            switch (mConfiguration->mString)
            {
                case ImplementerConfiguration::use_char_pointer:
                    return cpp::frm::typeRef() << cpp::frm::typeNameRef("const char*");
                case ImplementerConfiguration::use_stl_string:
                    return cpp::frm::typeRef() << nsStd
                                               << cpp::frm::typeNameRef("string");
                default: assert(false && "unknown string implementation type");
            }
        }
        if (name == "vector")
        {
            UnaryContainerSPtr pUnaryContainer = boost::static_pointer_cast<UnaryContainer>(pType);
            cpp::frm::TypeSPtr simpleType = cppType(pUnaryContainer->parameterType().lock());
            std::string result = "vector<";
            if (simpleType->namespace_())
            if (!simpleType->namespace_()->isVoid())
            {
                const std::vector<cpp::frm::NamespaceNameSPtr>& names = simpleType->namespace_()->names();
                for (size_t i = 0; i < names.size(); ++i)
                    result += names[i]->value() + "::";
            }
            result += simpleType->name()->value() + ">";
            return cpp::frm::typeRef() << nsStd
                                       << cpp::frm::typeNameRef(result);
        }
    }

    if (pType->package())
    {
        if (name == "datetime")
        {
            if (pType->package() == lib::compil::CompilPackage::time())
            {
                return cpp::frm::typeRef() << nsBoostPosixTime
                                           << cpp::frm::typeNameRef("ptime");
            }
        }
    }

    if (pType->runtimeObjectId() == EObjectId::structure())
        return cpp::frm::typeRef() << mpFrm->cppPackageNamespace(pType->package())
                                   << cpp::frm::typeNameRef(mpFrm->cppClassName(name));
    if (pType->runtimeObjectId() == EObjectId::enumeration())
        return mpFrm->cppEnumType(ObjectFactory::downcastEnumeration(pType));
    if (pType->runtimeObjectId() == EObjectId::specimen())
        return cpp::frm::typeRef() << cpp::frm::typeNameRef(mpFrm->cppClassName(name));
    if (pType->runtimeObjectId() == EObjectId::identifier())
        return cpp::frm::typeRef() << cpp::frm::typeNameRef(mpFrm->cppClassName(name));

    return cpp::frm::typeRef() << mpFrm->cppPackageNamespace(pType->package())
                               << cpp::frm::typeNameRef(name);
}

cpp::frm::TypeSPtr CppImplementer::cppInnerType(const TypeSPtr& pType,
                                                const StructureSPtr& pStructure)
{
    if (pType->runtimeObjectId() == EObjectId::enumeration())
    {
        EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pType);
        return mpFrm->cppInnerEnumType(pEnumeration, pStructure);
    }
    return cppType(pType);
}

std::vector<Dependency> CppImplementer::classPointerDependencies()
{
    std::vector<Dependency> dep;

    if (mConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers)
    {
        dep.push_back(
            Dependency("boost",
                       "shared_ptr.hpp",
                       Dependency::system_type,
                       Dependency::thirdparty_level,
                       Dependency::global_section,
                       "Boost C++ Smart Pointers"));

        dep.push_back(
            Dependency("boost",
                       "weak_ptr.hpp",
                       Dependency::system_type,
                       Dependency::thirdparty_level,
                       Dependency::global_section,
                       "Boost C++ Smart Pointers"));
    }

    return dep;
}

std::vector<Dependency> CppImplementer::classReferenceDependencies()
{
    std::vector<Dependency> dep;

    if (mConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers)
    {
        dep.push_back(
            Dependency("boost",
                       "make_shared.hpp",
                       Dependency::system_type,
                       Dependency::thirdparty_level,
                       Dependency::global_section,
                       "Boost C++ Smart Pointers"));
    }

    return dep;
}

std::vector<Dependency> CppImplementer::dependencies(const TypeSPtr& pType)
{
    std::vector<Dependency> dep;

    dep.push_back(cppHeaderFileDependency(pType));

    UnaryTemplateSPtr pUnaryTemplate = ObjectFactory::downcastUnaryTemplate(pType);
    if (pUnaryTemplate)
        dep.push_back(cppHeaderFileDependency(pUnaryTemplate->parameterType().lock()));

    IntegerSPtr pInteger = ObjectFactory::downcastInteger(pType);

    if (pInteger)
    {
        if (mConfiguration->mIntegerTypes == ImplementerConfiguration::use_intnn_t)
        {
            dep.push_back(
                Dependency("sys",
                           "types.h",
                           Dependency::system_type,
                           Dependency::system_level,
                           Dependency::private_section,
                           "Standard C Library"));
        }
        else
        if (mConfiguration->mIntegerTypes == ImplementerConfiguration::use_boost_intnn_t)
        {
            dep.push_back(
                Dependency("boost",
                           "cstdint.hpp",
                           Dependency::system_type,
                           Dependency::thirdparty_level,
                           Dependency::global_section,
                           "Boost C++ Smart Pointers"));
        }
    }

    EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pType);
    if (pEnumeration)
    {
        if (pEnumeration->flags())
        if (mConfiguration->mFlagsEnumeration == ImplementerConfiguration::flags_enumeration_use_core_template)
        {
            // todo: we should report an error here mCorePackage is null
                
            dep.push_back(
                Dependency(cppFilepath(mCorePackage),
                           "flags_enumeration" + applicationExtension(declaration),
                           Dependency::quote_type,
                           Dependency::core_level,
                           Dependency::private_section,
                           "Compil C++ Template Library"));
        }
    }

    std::string name = pType->name()->value();
    if (!pType->package())
    {
        if (name == "string")
        {
            if (mConfiguration->mString == ImplementerConfiguration::use_stl_string)
            {
                dep.push_back(
                    Dependency("",
                               "string",
                               Dependency::system_type,
                               Dependency::stl_level,
                               Dependency::global_section,
                               "Standard Template Library"));
            }
        }

        else
        if (name == "vector")
        {
            dep.push_back(
                Dependency("",
                           "vector",
                           Dependency::system_type,
                           Dependency::stl_level,
                           Dependency::global_section,
                           "Standard Template Library"));

            UnaryContainerSPtr pUnaryContainer = boost::static_pointer_cast<UnaryContainer>(pType);
            std::vector<Dependency> subdep = dependencies(pUnaryContainer->parameterType().lock());

            dep.insert(dep.begin(), subdep.begin(), subdep.end());
        }
    }

    if (pType->package())
    {
        if (pType->package() == lib::compil::CompilPackage::time())
        {
            dep.push_back(
                Dependency("boost/date_time",
                           "posix_time/posix_time.hpp",
                           Dependency::system_type,
                           Dependency::thirdparty_level,
                           Dependency::private_section,
                           "Boost Posix Time System"));
        }
    }
    return dep;
}

std::vector<Dependency> CppImplementer::dependencies(const FieldSPtr& pField)
{
    return dependencies(pField->type());
}

cpp::frm::TypeSPtr CppImplementer::cppPtrType(const TypeSPtr& pType)
{
    switch (mConfiguration->mPointer)
    {
        case ImplementerConfiguration::use_raw_pointers:
            return mpFrm->cppRawPtrName(pType);
        case ImplementerConfiguration::use_boost_pointers:
            return mpFrm->cppSharedPtrName(pType);
        default: assert(false && "unknown pointer type"); break;
    }
    return cpp::frm::TypeSPtr();
}

cpp::frm::TypeSPtr CppImplementer::cppPtrDecoratedType(const TypeSPtr& pType)
{
    switch (mConfiguration->mPointer)
    {
        case ImplementerConfiguration::use_raw_pointers:
            return mpFrm->cppRawPtrDecoratedType(pType);
        case ImplementerConfiguration::use_boost_pointers:
            return mpFrm->cppSharedPtrDecoratedType(pType);
        default: assert(false && "unknown pointer type"); break;
    }
    return cpp::frm::TypeSPtr();
}

std::string CppImplementer::cppNullPtr(const TypeSPtr& pType)
{
    switch (mConfiguration->mPointer)
    {
        case ImplementerConfiguration::use_raw_pointers:
            return null();
        case ImplementerConfiguration::use_boost_pointers:
            return mpFrm->cppSharedPtrName(pType)->name()->value() + "()";
        default: assert(false && "unknown pointer type"); break;
    }
    return "";
}

std::string CppImplementer::cppConvertRawPtr(const TypeSPtr& pType, const std::string& variable)
{
    switch (mConfiguration->mPointer)
    {
        case ImplementerConfiguration::use_raw_pointers:
            return variable;
        case ImplementerConfiguration::use_boost_pointers:
            return mpFrm->cppSharedPtrName(pType)->name()->value() + "(" + variable + ")";
        default: assert(false && "unknown pointer type"); break;
    }
    return "";
}

std::string CppImplementer::null()
{
    switch (mConfiguration->mNullOr0)
    {
        case ImplementerConfiguration::use_null: return "NULL";
        case ImplementerConfiguration::use_0: return "0";
        default: assert(false && "unknown Null or 0 type"); break;
    }
    return "";
}

Dependency CppImplementer::nullDependency()
{
    if (mConfiguration->mNullOr0 == ImplementerConfiguration::use_null)
    {
        return Dependency("",
                          "stddef.h",
                          Dependency::system_type,
                          Dependency::system_level,
                          Dependency::private_section,
                          "Standard C Library");
    }
    return Dependency();
}


std::string CppImplementer::assert_method()
{
    switch (mConfiguration->mAssert)
    {
        case ImplementerConfiguration::use_std_assert: return "assert";
        case ImplementerConfiguration::use_boost_assert: return "BOOST_ASSERT";
        default: assert(false && "unknown assert type"); break;
    }
    return "";
}

Dependency CppImplementer::assert_dependency()
{
    switch (mConfiguration->mAssert)
    {
        case ImplementerConfiguration::use_std_assert:
            return Dependency("",
                              "assert.h",
                              Dependency::system_type,
                              Dependency::system_level,
                              Dependency::private_section,
                              "Standard C library");
        case ImplementerConfiguration::use_boost_assert:
            return Dependency("boost",
                              "assert.hpp",
                              Dependency::system_type,
                              Dependency::thirdparty_level,
                              Dependency::global_section,
                              "Boost C++ Utility");
        default: assert(false && "unknown assert type"); break;
    }
    return Dependency();
}

Dependency CppImplementer::unordered_set_dependency()
{
    return Dependency("boost",
                      "unordered_set.hpp",
                      Dependency::system_type,
                      Dependency::thirdparty_level,
                      Dependency::private_section,
                      "Boost C++ Unordered");
}
Dependency CppImplementer::unordered_map_dependency()
{
    return Dependency("boost",
                      "unordered_map.hpp",
                      Dependency::system_type,
                      Dependency::thirdparty_level,
                      Dependency::private_section,
                      "Boost C++ Unordered");
}

bool CppImplementer::alphabeticByName(const StructureSPtr& pStructure1, const StructureSPtr& pStructure2)
{
    return pStructure1->name()->value() < pStructure2->name()->value();
}

std::vector<StructureSPtr> CppImplementer::hierarchie(const DocumentSPtr& document,
                                                      const StructureSPtr& pBaseStructure,
                                                      if_predicate if_pred,
                                                      less_predicate less_pred)
{
    std::vector<StructureSPtr> hierarchie;
    const std::vector<ObjectSPtr>& objects = document->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        StructureSPtr pStructure = ObjectFactory::downcastStructure(*it);
        if (!pStructure)
            continue;

        if (pStructure != pBaseStructure)
        if (!pStructure->isRecursivelyInherit(pBaseStructure))
            continue;

        if (if_pred)
        if (!if_pred(pStructure))
            continue;

        hierarchie.push_back(pStructure);
    }

    if (less_pred)
        std::sort(hierarchie.begin(), hierarchie.end(), less_pred);

    return hierarchie;
}

cpp::frm::MethodNameSPtr CppImplementer::staticMethodName(const std::string& name)
{
    std::string uname = name;
    std::transform(uname.begin(), uname.begin() + 1, uname.begin(), toupper);
    return mpFrm->methodName("static" + uname);
}

cpp::frm::MethodNameSPtr CppImplementer::runtimeMethodName(const std::string& name)
{
    std::string uname = name;
    std::transform(uname.begin(), uname.begin() + 1, uname.begin(), toupper);
    return mpFrm->methodName("runtime" + uname);
}

std::string CppImplementer::identificationName(const StructureSPtr& pStructure)
{
    return pStructure->name()->value() + "Id";
}

cpp::frm::TypeSPtr CppImplementer::identificationEnum(const StructureSPtr& pStructure)
{
    return cpp::frm::typeRef() << cpp::frm::typeNameRef(mpFrm->enumName(identificationName(pStructure)));
}

cpp::frm::MethodNameSPtr CppImplementer::staticIdentificationMethodName(const StructureSPtr& pStructure)
{
    return staticMethodName(identificationName(pStructure));
}

cpp::frm::MethodNameSPtr CppImplementer::runtimeIdentificationMethodName(const StructureSPtr& pStructure)
{
    return runtimeMethodName(identificationName(pStructure));
}

EnumerationSPtr CppImplementer::objectEnumeration(const DocumentSPtr& document, const FactorySPtr& pFactory)
{
    std::vector<StructureSPtr> structs =
        hierarchie(document,
                   ObjectFactory::downcastStructure(pFactory->parameterType().lock()),
                   &Structure::hasRuntimeIdentification);
    return objectEnumeration(document, structs, pFactory);
}

EnumerationSPtr CppImplementer::objectEnumeration(const DocumentSPtr& document,
                                                  const std::vector<StructureSPtr>& structs,
                                                  const FactorySPtr& pFactory)
{
    SourceIdSPtr pSourceId(new SourceId());

    EnumerationSPtr pEnumeration(new Enumeration());
    //pEnumeration->setComment(pComment);

    pEnumeration->set_sourceId(pSourceId);
    pEnumeration->set_line(Line(-1));
    pEnumeration->set_column(Column(-1));
    pEnumeration->set_cast(CastableType::ECast::strong());
    pEnumeration->set_flags(false);

    std::vector<PackageElementSPtr> package_elements;
    pEnumeration->set_parameterType(document->findType(PackageSPtr(), package_elements, "integer"));

    NameSPtr pName(new Name());
    pName->set_sourceId(pSourceId);
    pName->set_line(Line(-1));
    pName->set_column(Column(-1));
    pName->set_value(identificationName(ObjectFactory::downcastStructure(pFactory->parameterType().lock())));
    pEnumeration->set_name(pName);

    int mEnumValue = 1; // 0 reserved for invalid

    std::vector<EnumerationValueSPtr> enumerationValues;

    std::vector<StructureSPtr>::const_iterator it;
    for (it = structs.begin(); it != structs.end(); ++it)
    {
        StructureSPtr pStructure = *it;

        AbsoluteEnumerationValueSPtr pEnumerationValue(new AbsoluteEnumerationValue());
        //pEnumerationValue->setComment(pComment);

        pEnumerationValue->set_sourceId(pSourceId);
        pEnumerationValue->set_line(Line(-1));
        pEnumerationValue->set_column(Column(-1));

        NameSPtr pName(new Name());
        pName->set_sourceId(pSourceId);
        pName->set_line(Line(-1));
        pName->set_column(Column(-1));
        pName->set_value(pStructure->name()->value());

        pEnumerationValue->set_name(pName);
        pEnumerationValue->set_value(mEnumValue++);
        pEnumerationValue->set_enumeration(pEnumeration);

        enumerationValues.push_back(pEnumerationValue);
    }

    pEnumeration->set_enumerationValues(enumerationValues);

    return pEnumeration;
}


cpp::frm::EMethodSpecifier CppImplementer::methodSpecifier(const StructureSPtr& pStructure)
{
    StructureSPtr pStruct = pStructure;
    while (pStruct)
    {
        if (pStruct->hasRuntimeIdentification())
            return cpp::frm::EMethodSpecifier::virtual_();

        pStruct = pStruct->baseStructure().lock();
    }

    return cpp::frm::EMethodSpecifier::invalid();
}

cpp::frm::EDestructorSpecifier CppImplementer::destructorSpecifier(const StructureSPtr& pStructure)
{
    StructureSPtr pStruct = pStructure;
    while (pStruct)
    {
        if (pStruct->hasRuntimeIdentification())
            return cpp::frm::EDestructorSpecifier::virtual_();

        pStruct = pStruct->baseStructure().lock();
    }

    return cpp::frm::EDestructorSpecifier::lax();
}


cpp::frm::ConstructorNameSPtr CppImplementer::inheritClass(const EnumerationSPtr& pEnumeration,
                                                           const StructureSPtr& pStructure)
{
    TypeSPtr pParameterType = pEnumeration->parameterType().lock();

    if (pEnumeration->flags())
    if (mConfiguration->mFlagsEnumeration == ImplementerConfiguration::flags_enumeration_use_core_template)
    {
        return cpp::frm::constructorNameRef("flags_enumeration<" +
               cppType(pParameterType)->name()->value() +
               ", " +
               mpFrm->cppInnerEnumType(pEnumeration, pStructure)->name()->value() +
               ">");
    }
    return cpp::frm::ConstructorNameSPtr();
}

bool CppImplementer::implementEnumerationMethods(const EnumerationSPtr& pEnumeration)
{
    if (pEnumeration->flags())
    if (mConfiguration->mFlagsEnumeration == ImplementerConfiguration::flags_enumeration_use_core_template)
        return false;

    return true;
}

bool CppImplementer::implementFlagsEnumerationMethods(const EnumerationSPtr& pEnumeration)
{
    if (!pEnumeration->flags())
        return false;

    if (mConfiguration->mFlagsEnumeration != ImplementerConfiguration::flags_enumeration_inline_implementation)
        return false;

    return true;
}

bool CppImplementer::boost_smart_ptr_needed()
{
    return mConfiguration->mPointer == ImplementerConfiguration::use_boost_pointers;
}

cpp::frm::TypeSPtr CppImplementer::boost_shared_ptr(const cpp::frm::TypeSPtr& type)
{
    return cpp::frm::typeRef() << nsBoost
                               << cpp::frm::typeNameRef("shared_ptr<" + type->name()->value() + ">");
}

cpp::frm::TypeSPtr CppImplementer::boost_shared_const_ptr(const cpp::frm::TypeSPtr& type)
{
    return cpp::frm::typeRef() << nsBoost
                               << cpp::frm::typeNameRef("shared_ptr<const " + type->name()->value() + ">");
}

cpp::frm::TypeSPtr CppImplementer::boost_weak_ptr(const cpp::frm::TypeSPtr& type)
{
    return cpp::frm::typeRef() << nsBoost
                               << cpp::frm::typeNameRef("weak_ptr<" + type->name()->value() + ">");
}

cpp::frm::TypeSPtr CppImplementer::boost_enable_shared_from_this(const cpp::frm::TypeSPtr& type)
{
    return cpp::frm::typeRef() << nsBoost
                               << cpp::frm::typeNameRef("enable_shared_from_this<" + type->name()->value() + ">");
}

std::string CppImplementer::applicationExtension(const EExtensionType type)
{
    switch (type)
    {
        case definition:
            switch (mConfiguration->applicationCppExtension)
            {
                case ImplementerConfiguration::use_cpp: return ".cpp";
                case ImplementerConfiguration::use_cxx: return ".cxx";
                default : assert(false && "unknown applicationCppExtension");
            }
        case declaration:
            switch (mConfiguration->applicationCppHeaderExtension)
            {
                case ImplementerConfiguration::use_h: return ".h";
                case ImplementerConfiguration::use_hpp: return ".hpp";
                default : assert(false && "unknown applicationCppHeaderExtension");
            }
        default : assert(false && "unknown extension type");
    }
    return "";
}

std::string CppImplementer::cppFilepath(const PackageSPtr& package)
{
    boost::filesystem::path result;
    if (package)
    {
        const std::vector<PackageElementSPtr>& elements = package->levels();
        for (std::vector<PackageElementSPtr>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        {
            const PackageElementSPtr& element = *it;
            result /= element->value();
        }
    }
    return result.generic_string();
}

PackageSPtr CppImplementer::cppHeaderPackage(const PackageSPtr& package)
{
    if (mConfiguration->mCppIncludePath == ImplementerConfiguration::include_path_based_on_import)
        return PackageSPtr();

    if (mConfiguration->mCppIncludePath == ImplementerConfiguration::include_path_based_on_package)
        return package;
    
    assert(false && "unknown mCppIncludePath");
    return PackageSPtr();
}

Dependency CppImplementer::cppHeaderFileDependency(const std::string filename,
                                                   const PackageSPtr& package)
{
    PackageSPtr headerPackage = cppHeaderPackage(package);

    boost::filesystem::path path(filename);
    if (!path.has_stem())
        return Dependency();

    return Dependency(headerPackage ? cppFilepath(headerPackage) : "",
                      path.stem().generic_string() + applicationExtension(declaration),
                      Dependency::quote_type,
                      Dependency::application_level);
}

Dependency CppImplementer::cppHeaderFileDependency(const TypeSPtr& type)
{
    if (!type)
        return Dependency();

    SourceIdSPtr sourceId = type->sourceId();
    if (!sourceId)
        return Dependency();

    std::string source = sourceId->original();
    return cppHeaderFileDependency(source, type->package());
}

}

