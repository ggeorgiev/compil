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


#ifndef _CPP_FORMATTER_H__
#define _CPP_FORMATTER_H__

#include "compiler/namespace_alias.h"

#include "generator/c++/configuration/formatter_configuration.h"
#include "c++_keyword.h"

#include "generator/cpp/format/constructor_name.h"
#include "generator/cpp/format/destructor_name.h"
#include "generator/cpp/format/method_name.h"
#include "generator/cpp/format/namespace.h"
#include "generator/cpp/format/parameter_value.h"
#include "generator/cpp/format/type.h"
#include "generator/cpp/format/variable_name.h"

#include "language/compil/all/object_factory.h"

#include <boost/shared_ptr.hpp>

#include <string>

namespace compil
{

class CppFormatter
{
public:
    CppFormatter(const FormatterConfigurationSPtr& pFormatterConfiguration,
                 const PackageSPtr& pCurrentPackage);
    virtual ~CppFormatter();
    
    virtual std::string cppClassName(const std::string& rawName);
    virtual std::string cppPrivateClassName(const std::string& rawName);
    
    virtual std::string cppRawPtrName(const std::string& rawName);
    virtual std::string cppSharedPtrName(const std::string& rawName);
    virtual std::string cppSharedConstPtrName(const std::string& rawName);
    virtual std::string cppWeakPtrName(const std::string& rawName);
    
    virtual std::string cppRefName(const std::string& rawName);
    
    virtual cpp::frm::MethodNameSPtr methodName(const std::string& rawName);
    
    virtual std::string name(const std::string& rawName);
    virtual std::string memberName(const std::string& rawName);
    virtual std::string ptrName(const std::string& rawName);
    virtual std::string memberPtrName(const std::string& rawName);
    
    virtual std::string enumName(const std::string& rawName);
    virtual std::string enumValueName(const std::string& rawName);
    virtual std::string constName(const std::string& rawName);
    
    virtual std::string value(int value);
    virtual std::string bitmask(int bitmask);
    virtual std::string all_bitmask(int bits);
    
    virtual std::string headerGuard(const std::string& location, const std::string& type = "");
    virtual std::string headerGuard(const FileSPtr& file, const std::string& type);
    
    virtual std::string globalVariable(const std::string& variable);
    
    virtual cpp::frm::VariableNameSPtr memberVariableName(const cpp::frm::VariableNameSPtr& name);
    virtual cpp::frm::VariableNameSPtr ptrVariableName(const cpp::frm::VariableNameSPtr& name);
    virtual cpp::frm::VariableNameSPtr memberPtrVariableName(const cpp::frm::VariableNameSPtr& name);
    
    virtual cpp::frm::ParameterValueSPtr parameterValue(const cpp::frm::VariableNameSPtr& name);
    
    virtual cpp::frm::NamespaceSPtr cppPackageNamespace(const PackageSPtr& pPackage);
    
    virtual cpp::frm::TypeSPtr constType(const cpp::frm::TypeSPtr& type) const;
    virtual cpp::frm::TypeSPtr constTypeRef(const cpp::frm::TypeSPtr& type) const;
    virtual cpp::frm::TypeSPtr typeRef(const cpp::frm::TypeSPtr& type) const;
    

    virtual cpp::frm::TypeSPtr cppEnumType(const EnumerationSPtr& pEnumeration);
    virtual cpp::frm::TypeSPtr cppInnerEnumType(const EnumerationSPtr& pEnumeration,
                                                const StructureSPtr& pStructure);
    virtual cpp::frm::ConstructorNameSPtr cppConstructorName(const EnumerationSPtr& pEnumeration);
    virtual cpp::frm::NamespaceSPtr cppEnumNamespace(const EnumerationSPtr& pEnumeration);
    
    virtual cpp::frm::TypeSPtr cppClassType(const TypeSPtr& pType);
    virtual cpp::frm::NamespaceSPtr cppClassNamespace(const TypeSPtr& pType);
    virtual cpp::frm::ConstructorNameSPtr cppConstructorName(const TypeSPtr& pType);
    virtual cpp::frm::DestructorNameSPtr cppDestructorName(const TypeSPtr& pType);
    
    virtual cpp::frm::TypeSPtr cppAutoClassType(const StructureSPtr& pStructure);
    virtual cpp::frm::NamespaceSPtr cppAutoClassNamespace(const StructureSPtr& pStructure);
    virtual cpp::frm::ConstructorNameSPtr cppAutoConstructorName(const StructureSPtr& pStructure);
    virtual cpp::frm::DestructorNameSPtr cppAutoDestructorName(const StructureSPtr& pStructure);
    
    virtual cpp::frm::TypeSPtr cppMainClassType(const StructureSPtr& pStructure);
    virtual cpp::frm::NamespaceSPtr cppMainClassNamespace(const StructureSPtr& pStructure);
    
    virtual cpp::frm::TypeSPtr cppPartialClassType(const StructureSPtr& pStructure);
    
    virtual std::string constValueName(const EnumerationValueSPtr& pEnumerationValue);
    virtual std::string enumValueName(const EnumerationValueSPtr& pEnumerationValue);
    
    virtual cpp::frm::TypeSPtr cppRawPtrName(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppSharedPtrName(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppSharedConstPtrName(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppWeakPtrName(const TypeSPtr& pType);
    
    virtual cpp::frm::TypeSPtr cppRawPtrDecoratedType(const TypeSPtr& pType);
    virtual cpp::frm::TypeSPtr cppSharedPtrDecoratedType(const TypeSPtr& pType);
        
    virtual std::string cppMemberName(const FieldSPtr& pField);
    virtual cpp::frm::VariableNameSPtr cppVariableName(const FieldSPtr& pField);
    virtual cpp::frm::VariableNameSPtr cppItemVariableName(const FieldSPtr& pField);
    virtual cpp::frm::ParameterValueSPtr cppVariableNameAsParameter(const FieldSPtr& pField);
    
    virtual cpp::frm::MethodNameSPtr getMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr setMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr mutableMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr updateMethodName(const FieldSPtr& pField);
    
    virtual cpp::frm::MethodNameSPtr constantMethodName(const StructureSPtr& pStructure,
                                            const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr defaultMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr alterMethodName(const FieldSPtr& pField);

    virtual cpp::frm::MethodNameSPtr destroyMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr clearMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr eraseMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr resetMethodName(const FieldSPtr& pField);
    
    virtual cpp::frm::MethodNameSPtr availableMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr existMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr validMethodName(const FieldSPtr& pField);
    virtual cpp::frm::MethodNameSPtr changedMethodName(const FieldSPtr& pField);
    
    virtual cpp::frm::MethodNameSPtr bitmaskMethodName(const FieldSPtr& pField);
    
    virtual cpp::frm::MethodNameSPtr downcastMethodName(const StructureSPtr& pStructure);
    
    virtual std::string defaultValue(const Type::ELiteral literal, const std::string& value) const;
    virtual std::string defaultValue(const AlterSPtr& pAlter) const;
    virtual std::string defaultValue(const FieldSPtr& pField) const;
    
    FormatterConfigurationSPtr mpFormatterConfiguration;

protected:
    PackageSPtr mpCurrentPackage;
    CppKeywordPtr mpKeyword;
};

typedef boost::shared_ptr<CppFormatter> CppFormatterPtr;

}

#else

namespace compil
{

class CppFormatter;
typedef boost::shared_ptr<CppFormatter> CppFormatterPtr;

}

#endif

