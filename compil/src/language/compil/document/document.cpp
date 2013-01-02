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

#include "compil/document/document.h"
#include "compil/all/object_factory.h"

#include "boost/make_shared.hpp"

#include <set>

#include <limits.h>

namespace lang
{

namespace compil
{

EnumerationValueSPtr Document::invalidEnumerationValue(const EnumerationSPtr& pEnumeration)
{
    NameSPtr pInvalidName(new Name());
    pInvalidName->set_value("invalid");
    AbsoluteEnumerationValueSPtr pInvalidEnumerationValue(new AbsoluteEnumerationValue());
    pInvalidEnumerationValue->set_enumeration(pEnumeration);
    pInvalidEnumerationValue->set_name(pInvalidName);
    pInvalidEnumerationValue->set_value(0);
    return pInvalidEnumerationValue;
}

EnumerationValueSPtr Document::nilEnumerationValue(const EnumerationSPtr& pEnumeration)
{
    NameSPtr pNilName(new Name());
    pNilName->set_value("nil");
    AbsoluteEnumerationValueSPtr pNilEnumerationValue(new AbsoluteEnumerationValue());
    pNilEnumerationValue->set_enumeration(pEnumeration);
    pNilEnumerationValue->set_name(pNilName);
    pNilEnumerationValue->set_value(LONG_MIN);
    return pNilEnumerationValue;
}

EnumerationValueSPtr Document::allEnumerationValue(const EnumerationSPtr& pEnumeration)
{
    NameSPtr pAllName(new Name());
    pAllName->set_value("all");
    AbsoluteEnumerationValueSPtr pAllEnumerationValue(new AbsoluteEnumerationValue());
    pAllEnumerationValue->set_enumeration(pEnumeration);
    pAllEnumerationValue->set_name(pAllName);
    pAllEnumerationValue->set_value(LONG_MAX);
    return pAllEnumerationValue;
}

Document::Document()
{

}

Document::~Document()
{
}

NameSPtr Document::name() const
{
    return mpName;
}

void Document::setName(const NameSPtr& pName)
{
    mpName = pName;
}

PackageSPtr Document::package() const
{
    return mpPackage;
}

void Document::setPackage(const PackageSPtr& pPackage)
{
    mpPackage = pPackage;
}

bool Document::compareElementValues(const std::vector<PackageElementSPtr>& v1, const std::vector<PackageElementSPtr>& v2)
{
    if (v1.size() != v2.size())
        return false;
    for (size_t i = 0; i < v1.size(); ++i)
    {
        if (v1[i]->value() != v2[i]->value())
            return false;
    }
    return true;
}

bool Document::isVisible(const PackageSPtr& pTypePackage,
                         const PackageSPtr& pCurrentPackage,
                         const std::vector<PackageElementSPtr>& lookup_package_elements)
{
    std::vector<PackageElementSPtr> type_package_elements;
    if (pTypePackage)
        type_package_elements = pTypePackage->short_();

    std::vector<PackageElementSPtr> current_package_elements;
    if (pCurrentPackage)
        current_package_elements = pCurrentPackage->short_();

    if (compareElementValues(type_package_elements, current_package_elements))
    if (lookup_package_elements.size() == 0)
        return true;

    if (compareElementValues(type_package_elements, lookup_package_elements))
        return true;

    return false;
}

TypeSPtr Document::findType(const PackageSPtr& pPackage,
                            const std::vector<PackageElementSPtr>& package_elements,
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

TypeSPtr Document::findType(const PackageSPtr& pPackage,
                            const std::vector<PackageElementSPtr>& package_elements,
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

void Document::addType(const TypeSPtr& pType)
{
    mTypes.push_back(pType);
}

UnaryTemplateSPtr Document::findUnfinishedUnaryTemplate(const std::string& name)
{
    std::vector<UnaryTemplateSPtr>::const_iterator it;
    for (it = mUnfinishedUnaryTemplates.begin(); it != mUnfinishedUnaryTemplates.end(); ++it)
    {
        if ((*it)->name()->value() == name)
            return *it;
    }
    return UnaryTemplateSPtr();
}

void Document::addUnfinishedUnaryTemplate(const UnaryTemplateSPtr& pUnaryTemplate)
{
    mUnfinishedUnaryTemplates.push_back(pUnaryTemplate);
}

std::vector<ObjectSPtr> Document::objects() const
{
    return mObjects;
}

void Document::addImport(const ImportSPtr& pImport)
{
    mObjects.push_back(pImport);
}

void Document::addEnumeration(const EnumerationSPtr& pEnumeration)
{
    mObjects.push_back(pEnumeration);
    addType(pEnumeration);
}

void Document::addIdentifier(const IdentifierSPtr& pIdentifier)
{
    mObjects.push_back(pIdentifier);
    addType(pIdentifier);
}

void Document::addSpecimen(const SpecimenSPtr& pSpecimen)
{
    mObjects.push_back(pSpecimen);
    addType(pSpecimen);
}

std::vector<FactorySPtr> Document::findPluginFactories(const StructureSPtr& pStructure)
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

void Document::addFactory(const FactorySPtr& pFactory)
{
    mObjects.push_back(pFactory);
    addType(pFactory);
}

void Document::addStructure(const StructureSPtr& pStructure)
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

void Document::addInterface(const InterfaceSPtr& pInterface)
{
    mObjects.push_back(pInterface);
}

void Document::cache(const ObjectSPtr& pObject)
{
    mCache.push_back(pObject);
}

}

}
