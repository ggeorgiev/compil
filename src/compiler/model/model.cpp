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

#include "model.h"

#include <limits.h>

#include <set>

namespace compil
{

static bool bInit = false;
static TypeSPtr pBoolType(new CastableType());

static IntegerSPtr pSizeType(new Integer());

static IntegerSPtr pSmallType(new Integer());
static IntegerSPtr pShortType(new Integer());
static IntegerSPtr pIntegerType(new Integer());
static IntegerSPtr pLongType(new Integer());

static IntegerSPtr pByteType(new Integer());
static IntegerSPtr pWordType(new Integer());
static IntegerSPtr pDWordType(new Integer());
static IntegerSPtr pQWordType(new Integer());

static TypeSPtr pReal32Type(new CastableType());
static TypeSPtr pReal64Type(new CastableType());
static TypeSPtr pStringType(new CastableType());
static TypeSPtr pBinaryType(new CastableType());

static TypeSPtr pDateType(new Type());
static TypeSPtr pTimeType(new Type());
static TypeSPtr pDatetimeType(new Type());
static TypeSPtr pTimeDirationType(new Type());

static UnaryTemplateSPtr pReference(new Reference());
static UnaryTemplateSPtr pVector(new UnaryContainer());

EnumerationValueSPtr Model::invalidEnumerationValue(const EnumerationSPtr& pEnumeration)
{
    NameSPtr pInvalidName(new Name());
    pInvalidName->set_value("invalid");
    AbsoluteEnumerationValueSPtr pInvalidEnumerationValue(new AbsoluteEnumerationValue());
    pInvalidEnumerationValue->set_enumeration(pEnumeration);
    pInvalidEnumerationValue->set_name(pInvalidName);
    pInvalidEnumerationValue->set_value(0);
    return pInvalidEnumerationValue;
}

EnumerationValueSPtr Model::nilEnumerationValue(const EnumerationSPtr& pEnumeration)
{
    NameSPtr pNilName(new Name());
    pNilName->set_value("nil");
    AbsoluteEnumerationValueSPtr pNilEnumerationValue(new AbsoluteEnumerationValue());
    pNilEnumerationValue->set_enumeration(pEnumeration);
    pNilEnumerationValue->set_name(pNilName);
    pNilEnumerationValue->set_value(LONG_MIN);
    return pNilEnumerationValue;
}

EnumerationValueSPtr Model::allEnumerationValue(const EnumerationSPtr& pEnumeration)
{
    NameSPtr pAllName(new Name());
    pAllName->set_value("all");
    AbsoluteEnumerationValueSPtr pAllEnumerationValue(new AbsoluteEnumerationValue());
    pAllEnumerationValue->set_enumeration(pEnumeration);
    pAllEnumerationValue->set_name(pAllName);
    pAllEnumerationValue->set_value(LONG_MAX);
    return pAllEnumerationValue;
}

Model::Model()
{
    if (!bInit)
    {
        bInit = true;
        
        NameSPtr pName;
        
        pName.reset(new Name());
        pName->set_value("boolean");
        pBoolType->set_name(pName);
        pBoolType->set_literal(Type::ELiteral::boolean());
        pBoolType->set_kind(Type::EKind::builtin());
        //pBoolType->set_cast(CastableType::ECast::weak());
        
        pName.reset(new Name());
        pName->set_value("size");
        pSizeType->set_name(pName);
        pSizeType->set_min("−9223372036854775808");
        pSizeType->set_min("9223372036854775807");

        pName.reset(new Name());
        pName->set_value("small");
        pSmallType->set_name(pName);
        pSmallType->set_min("−128");
        pSmallType->set_min("127");

        pName.reset(new Name());
        pName->set_value("short");
        pShortType->set_name(pName);
        pShortType->set_min("−32768");
        pShortType->set_min("32767");

        pName.reset(new Name());
        pName->set_value("integer");
        pIntegerType->set_name(pName);
        pIntegerType->set_min("−2147483648");
        pIntegerType->set_min("2147483647");

        pName.reset(new Name());
        pName->set_value("long");
        pLongType->set_name(pName);
        pLongType->set_min("−9223372036854775808");
        pLongType->set_min("9223372036854775807");
        
        pName.reset(new Name());
        pName->set_value("byte");
        pByteType->set_name(pName);
        pByteType->set_min("0");
        pByteType->set_min("255");

        pName.reset(new Name());
        pName->set_value("word");
        pWordType->set_name(pName);
        pWordType->set_min("0");
        pWordType->set_min("65535");

        pName.reset(new Name());
        pName->set_value("dword");
        pDWordType->set_name(pName);
        pDWordType->set_min("0");
        pDWordType->set_min("4294967295");

        pName.reset(new Name());
        pName->set_value("qword");
        pQWordType->set_name(pName);
        pQWordType->set_min("0");
        pQWordType->set_min("18446744073709551615");

        pName.reset(new Name());
        pName->set_value("real32");
        pReal32Type->set_name(pName);
        pReal32Type->set_literal(Type::ELiteral::real());
        pReal32Type->set_kind(Type::EKind::builtin());
        //pReal32Type->set_cast(CastableType::ECast::weak());

        pName.reset(new Name());
        pName->set_value("real64");
        pReal64Type->set_name(pName);
        pReal64Type->set_literal(Type::ELiteral::real());
        pReal64Type->set_kind(Type::EKind::builtin());
        //pReal64Type->set_cast(CastableType::ECast::weak());

        pName.reset(new Name());
        pName->set_value("string");
        pStringType->set_name(pName);
        pStringType->set_literal(Type::ELiteral::string());
        pStringType->set_kind(Type::EKind::string());
        //pStringType->set_cast(CastableType::ECast::weak());

        pName.reset(new Name());
        pName->set_value("binary");
        pBinaryType->set_name(pName);
        pBinaryType->set_literal(Type::ELiteral::binary());
        pBinaryType->set_kind(Type::EKind::string());
        //pBinaryType->set_cast(CastableType::ECast::weak());
        
        PackageSPtr pPackage(new Package());
        std::vector<std::string> elements;
        elements.push_back("time");
        pPackage->set_elements(elements);
        
        pName.reset(new Name());
        pName->set_value("binary");
        pBinaryType->set_name(pName);
        pBinaryType->set_literal(Type::ELiteral::binary());
        pBinaryType->set_kind(Type::EKind::string());
        
        pName.reset(new Name());
        pName->set_value("date");
        pDateType->set_name(pName);
        pDateType->set_literal(Type::ELiteral::binary());
        pDateType->set_kind(Type::EKind::object());
        pDateType->set_package(pPackage);
        
        pName.reset(new Name());
        pName->set_value("time");
        pTimeType->set_name(pName);
        pTimeType->set_literal(Type::ELiteral::binary());
        pTimeType->set_kind(Type::EKind::object());
        pTimeType->set_package(pPackage);
        
        pName.reset(new Name());
        pName->set_value("datetime");
        pDatetimeType->set_name(pName);
        pDatetimeType->set_literal(Type::ELiteral::binary());
        pDatetimeType->set_kind(Type::EKind::object());
        pDatetimeType->set_package(pPackage);
        
        pName.reset(new Name());
        pName->set_value("duration");
        pTimeDirationType->set_name(pName);
        pTimeDirationType->set_literal(Type::ELiteral::binary());
        pTimeDirationType->set_kind(Type::EKind::object());
        pTimeDirationType->set_package(pPackage);
        
        pName.reset(new Name());
        pName->set_value("reference");
        pReference->set_name(pName);
        pReference->set_literal(Type::ELiteral::reference());
        pReference->set_kind(Type::EKind::object());
        pReference->set_cast(CastableType::ECast::weak());
        
        pName.reset(new Name());
        pName->set_value("vector");
        pVector->set_name(pName);
        pVector->set_literal(Type::ELiteral::binary());
        pVector->set_kind(Type::EKind::object());
        pVector->set_cast(CastableType::ECast::weak());
    }

    addType(pBoolType);
    
    addType(pSizeType);
    
    addType(pSmallType);
    addType(pShortType);
    addType(pIntegerType);
    addType(pLongType);
    
    addType(pByteType);
    addType(pWordType);
    addType(pDWordType);
    addType(pQWordType);
    
    addType(pReal32Type);
    addType(pReal64Type);
    addType(pStringType);
    addType(pBinaryType);


    addType(pDateType);
    addType(pTimeType);
    addType(pDatetimeType);
    addType(pTimeDirationType);    
    
    addUnfinishedUnaryTemplate(pReference);
    addUnfinishedUnaryTemplate(pVector);
}

Model::~Model()
{
}

DocumentSPtr Model::mainDocument() const
{
    return mpMainDocument;
}

void Model::setMainDocument(const DocumentSPtr& pMainDocument)
{
    mpMainDocument = pMainDocument;
}

NameSPtr Model::name() const
{
    return mpName;
}

void Model::setName(const NameSPtr& pName)
{
    mpName = pName;
}

PackageSPtr Model::package() const
{
    return mpPackage;
}

void Model::setPackage(const PackageSPtr& pPackage)
{
    mpPackage = pPackage;
}

bool Model::isVisible(const PackageSPtr& pTypePackage,
                      const PackageSPtr& pCurrentPackage,
                      const std::vector<std::string>& lookup_package_elements)
{
    std::vector<std::string> type_package_elements;
    if (pTypePackage) type_package_elements = pTypePackage->elements();

    std::vector<std::string> current_package_elements;
    if (pCurrentPackage) current_package_elements = pCurrentPackage->elements();

    if (type_package_elements == current_package_elements)
    if (lookup_package_elements.size() == 0)
        return true;
        
    if (type_package_elements == lookup_package_elements)
        return true;
        
    return false;
}
    
TypeSPtr Model::findType(const PackageSPtr& pPackage,
                         const std::vector<std::string>& package_elements, 
                         const std::string& name) const
{
    std::vector<TypeSPtr>::const_iterator it;
    for (it = mTypes.begin(); it != mTypes.end(); ++it)
    {
        const TypeSPtr& pType = *it;
        if ((*it)->name()->value() == name)
        if (isVisible(pType->package(), pPackage, package_elements))
            return *it;
    }
    return TypeSPtr();
}

TypeSPtr Model::findType(const PackageSPtr& pPackage,
                         const std::vector<std::string>& package_elements,
                         const std::vector<ObjectSPtr>& objects, const std::string& name) const
{
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if ((*it)->runtimeObjectId() == EObjectId::enumeration())
        {
            EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(*it);
            if (pEnumeration->name()->value() == name)
                return pEnumeration;
        }
    }
    
    return findType(pPackage, package_elements, name);
}

void Model::addType(const TypeSPtr& pType)
{
    mTypes.push_back(pType);
}

UnaryTemplateSPtr Model::findUnfinishedUnaryTemplate(const std::string& name)
{
    std::vector<UnaryTemplateSPtr>::const_iterator it;
    for (it = mUnfinishedUnaryTemplates.begin(); it != mUnfinishedUnaryTemplates.end(); ++it)
    {
        if ((*it)->name()->value() == name)
            return *it;
    }
    return UnaryTemplateSPtr();
}
 
void Model::addUnfinishedUnaryTemplate(const UnaryTemplateSPtr& pUnaryTemplate)
{
    mUnfinishedUnaryTemplates.push_back(pUnaryTemplate);
}

std::vector<ObjectSPtr> Model::objects() const
{
    return mObjects;
}

void Model::addImport(const ImportSPtr& pImport)
{
    mObjects.push_back(pImport);
}

void Model::addEnumeration(const EnumerationSPtr& pEnumeration)
{
    mObjects.push_back(pEnumeration);
    addType(pEnumeration);
}

void Model::addIdentifier(const IdentifierSPtr& pIdentifier)
{
    mObjects.push_back(pIdentifier);
    addType(pIdentifier);
}

void Model::addSpecimen(const SpecimenSPtr& pSpecimen)
{
    mObjects.push_back(pSpecimen);
    addType(pSpecimen);
}

std::vector<FactorySPtr> Model::findPluginFactories(const StructureSPtr& pStructure)
{
    std::set<TypeSPtr> set;
    
    StructureSPtr pBase = pStructure;
    while (pBase)
    {
        set.insert(pBase);
        pBase = pBase->baseStructure().lock();
    }

    std::vector<FactorySPtr> factories;
    
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = mObjects.begin(); it != mObjects.end(); ++it)
    {
        if ((*it)->runtimeObjectId() == EObjectId::factory())
        {
            FactorySPtr pFactory = ObjectFactory::downcastFactory(*it);
            if (pFactory->type() != Factory::EType::plugin())
                continue;
                
            if (set.find(pFactory->parameterType().lock()) == set.end())
                continue;
                
            factories.push_back(pFactory);
        }
    }
    
    return factories;
}

void Model::addFactory(const FactorySPtr& pFactory)
{
    mObjects.push_back(pFactory);
    addType(pFactory);
}

void Model::addStructure(const StructureSPtr& pStructure)
{
    mObjects.push_back(pStructure);
    addType(pStructure);
    
    const std::vector<ObjectSPtr>& objects = pStructure->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if ((*it)->runtimeObjectId() == EObjectId::enumeration())
        {
            EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(*it);
            addType(pEnumeration);
        }
    }
}

void Model::addInterface(const InterfaceSPtr& pInterface)
{
    mObjects.push_back(pInterface);
}

void Model::cache(const ObjectSPtr& pObject)
{
    mCache.push_back(pObject);
}

}
