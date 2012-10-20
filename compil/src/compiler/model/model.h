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

#ifndef _COMPIL_MODEL_H__
#define _COMPIL_MODEL_H__

#include "object_factory.h"

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace compil
{

class Model
{
public:
    static EnumerationValueSPtr invalidEnumerationValue(const EnumerationSPtr& pEnumeration);
    static EnumerationValueSPtr nilEnumerationValue(const EnumerationSPtr& pEnumeration);
    static EnumerationValueSPtr allEnumerationValue(const EnumerationSPtr& pEnumeration);
    
    Model();
    virtual ~Model();
    
    DocumentSPtr mainDocument() const;
    void setMainDocument(const DocumentSPtr& pMainDocument);
    
    NameSPtr name() const;
    void setName(const NameSPtr& pName);
    
    PackageSPtr package() const;
    void setPackage(const PackageSPtr& pPackage);

    static bool isVisible(const PackageSPtr& pTypePackage,
                          const PackageSPtr& pCurrentPackage,
                          const std::vector<PackageElement>& lookup_package_elements);
                     
    TypeSPtr findType(const PackageSPtr& pPackage,
                      const std::vector<PackageElement>& package_elements, 
                      const std::string& name) const;
    TypeSPtr findType(const PackageSPtr& pPackage,
                      const std::vector<PackageElement>& package_elements, 
                      const std::vector<ObjectSPtr>& objects, 
                      const std::string& name) const;
    void addType(const TypeSPtr& pType);
    
    UnaryTemplateSPtr findUnfinishedUnaryTemplate(const std::string& name);
    void addUnfinishedUnaryTemplate(const UnaryTemplateSPtr& pUnaryTemplate);

    std::vector<ObjectSPtr> objects() const;
    void addImport(const ImportSPtr& pImport);
    void addEnumeration(const EnumerationSPtr& pEnumeration);
    void addIdentifier(const IdentifierSPtr& pIdentifier);
    void addSpecimen(const SpecimenSPtr& pSpecimen);
    
    std::vector<FactorySPtr> findPluginFactories(const StructureSPtr& pStructure);
    void addFactory(const FactorySPtr& pFactory);
    
    void addStructure(const StructureSPtr& pStructure);
    void addInterface(const InterfaceSPtr& pInterface);
    
    void cache(const ObjectSPtr& pObject);
    
private:
    PackageSPtr mpPackage;
    DocumentSPtr mpMainDocument;
    NameSPtr mpName;
    
    std::vector<TypeSPtr> mTypes;
    std::vector<ObjectSPtr> mObjects;
    
    std::vector<UnaryTemplateSPtr> mUnfinishedUnaryTemplates;
    
    std::vector<ObjectSPtr> mCache;
};

typedef boost::shared_ptr<Model> ModelPtr;
typedef boost::weak_ptr<Model> ModelWPtr;

}

#else

namespace compil
{

class Model;
typedef boost::shared_ptr<Model> ModelPtr;
typedef boost::weak_ptr<Model> ModelWPtr;

}

#endif
