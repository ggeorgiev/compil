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


#ifndef _CPP_IMPLEMENTER_H__
#define _CPP_IMPLEMENTER_H__

#include "implementer/implementer_configuration.h"
#include "implementer/dependency.h"

#include "cpp/format/destructor_specifier.h"
#include "cpp/format/method_specifier.h"

#include "c++_formatter.h"

#include "language/compil/all/object_factory.h"

namespace compil
{

extern cpp::frm::NamespaceSPtr nsStd;
extern cpp::frm::NamespaceSPtr nsBoost;
extern cpp::frm::NamespaceSPtr nsBoostPosixTime;

class CppImplementer
{
public:
    CppImplementer(const CppFormatterPtr& pFrm);
    virtual ~CppImplementer();
    
    virtual bool init(const PackageSPtr& corePackage,
                      const ImplementerConfigurationSPtr& pConfig);
    
    virtual bool needMutableMethod(const FieldSPtr& pField, const StructureSPtr& pCurrentStructure);
    virtual bool needConstructorInitialization(const FieldSPtr& pField);
    
    virtual cpp::frm::TypeSPtr cppType(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppInnerType(const TypeSPtr& pType,
                                            const StructureSPtr& pStructure);
    
    virtual cpp::frm::TypeSPtr cppDecoratedType(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppSetDecoratedType(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppInnerDecoratedType(const TypeSPtr& pType,
                                                     const StructureSPtr& pStructure);
    virtual cpp::frm::TypeSPtr cppInnerSetDecoratedType(const TypeSPtr& pType,
                                                        const StructureSPtr& pStructure);
    
    virtual std::string cppGetReturn(const FieldSPtr& pField);
    
    virtual std::vector<Dependency> classPointerDependencies();
    virtual std::vector<Dependency> classReferenceDependencies();
    
    virtual std::vector<Dependency> dependencies(const TypeSPtr& pType);
    virtual std::vector<Dependency> dependencies(const FieldSPtr& pField);
    
    virtual cpp::frm::TypeSPtr cppPtrType(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppPtrDecoratedType(const TypeSPtr& pType);
    
    virtual std::string cppNullPtr(const TypeSPtr& pType);
    virtual std::string cppConvertRawPtr(const TypeSPtr& pType, const std::string& variable);
    
    virtual std::string null();
    virtual Dependency nullDependency();
    
    virtual std::string assert_method();
    virtual Dependency assert_dependency();
    
    virtual Dependency unordered_set_dependency();
    virtual Dependency unordered_map_dependency();
    
    static bool alphabeticByName(const StructureSPtr& pStructure1, const StructureSPtr& pStructure2);
    
    typedef bool (*if_predicate)(const StructureSPtr& pStructure);
    typedef bool (*less_predicate)(const StructureSPtr& pStructure1, const StructureSPtr& pStructure2);
    virtual std::vector<StructureSPtr> hierarchie(const DocumentSPtr& document,
                                                  const StructureSPtr& pBaseStructure,
                                                  if_predicate if_pred = NULL,
                                                  less_predicate less_pred = alphabeticByName);
                                                 
    virtual cpp::frm::MethodNameSPtr staticMethodName(const std::string& name);
    virtual cpp::frm::MethodNameSPtr runtimeMethodName(const std::string& name);
    
    virtual std::string identificationName(const StructureSPtr& pStructure);
    virtual cpp::frm::TypeSPtr identificationEnum(const StructureSPtr& pStructure);
    virtual cpp::frm::MethodNameSPtr staticIdentificationMethodName(const StructureSPtr& pStructure);
    virtual cpp::frm::MethodNameSPtr runtimeIdentificationMethodName(const StructureSPtr& pStructure);
    
    virtual EnumerationSPtr objectEnumeration(const DocumentSPtr& document, const FactorySPtr& pFactory);
    virtual EnumerationSPtr objectEnumeration(const DocumentSPtr& document,
                                              const std::vector<StructureSPtr>& structs,
                                              const FactorySPtr& pFactory);
  
    virtual cpp::frm::EMethodSpecifier methodSpecifier(const StructureSPtr& pStructure);
    virtual cpp::frm::EDestructorSpecifier destructorSpecifier(const StructureSPtr& pStructure);
                                     
    cpp::frm::ConstructorNameSPtr inheritClass(const EnumerationSPtr& pEnumeration,
                                               const StructureSPtr& pStructure);
    virtual bool implementEnumerationMethods(const EnumerationSPtr& pEnumeration);
    virtual bool implementFlagsEnumerationMethods(const EnumerationSPtr& pEnumeration);
                             
    virtual bool boost_smart_ptr_needed();
    virtual cpp::frm::TypeSPtr boost_shared_ptr(const cpp::frm::TypeSPtr& type);
    virtual cpp::frm::TypeSPtr boost_shared_const_ptr(const cpp::frm::TypeSPtr& type);
    virtual cpp::frm::TypeSPtr boost_weak_ptr(const cpp::frm::TypeSPtr& type);
    virtual cpp::frm::TypeSPtr boost_enable_shared_from_this(const cpp::frm::TypeSPtr& type);
    
    enum EExtensionType
    {
        declaration,
        definition
    };
    
    virtual std::string applicationExtension(const EExtensionType type);

    virtual std::string cppFilepath(const PackageSPtr& package,
                                    const std::string filename);

    virtual std::string cppHeaderFilepath(const std::string filename,
                                          const PackageSPtr& package);
    virtual Dependency cppHeaderFileDependency(const std::string filename,
                                               const PackageSPtr& package);
    virtual Dependency cppHeaderFileDependency(const TypeSPtr& type);
    
    ImplementerConfigurationSPtr mConfiguration;
    
private:
    PackageSPtr mCorePackage;
    CppFormatterPtr mpFrm;
};

typedef boost::shared_ptr<CppImplementer> CppImplementerPtr;

}

#else

namespace compil
{

class CppImplementer;
typedef boost::shared_ptr<CppImplementer> CppImplementerPtr;

}

#endif

