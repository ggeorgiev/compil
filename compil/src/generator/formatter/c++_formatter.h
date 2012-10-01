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

#include "formatter_configuration.h"
#include "c++_keyword.h"

#include "cpp/format/constructor_name.h"
#include "cpp/format/decorated_type.h"
#include "cpp/format/destructor_name.h"
#include "cpp/format/variable_name.h"

#include "alter.h"
#include "field.h"
#include "enumeration.h"
#include "specimen.h"
#include "identifier.h"
#include "structure.h"
#include "factory.h"
#include "interface.h"
#include "document.h"

#include "namespace.h"
#include "method_name.h"

#include "parameter_value.h"

#include <boost/shared_ptr.hpp>

#include <string>

namespace compil
{

class CppFormatter
{
public:
    CppFormatter(const FormatterConfigurationPtr& pFormatterConfiguration,
                 const PackageSPtr& pCurrentPackage);
    virtual ~CppFormatter();
    
    virtual std::string cppClassName(const std::string& rawName);
    virtual std::string cppPrivateClassName(const std::string& rawName);
    
    virtual std::string cppRawPtrName(const std::string& rawName);
    virtual std::string cppSharedPtrName(const std::string& rawName);
    virtual std::string cppSharedConstPtrName(const std::string& rawName);
    virtual std::string cppWeakPtrName(const std::string& rawName);
    
    virtual std::string cppRefName(const std::string& rawName);
    
    virtual MethodNameSPtr methodName(const std::string& rawName);
    
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
    virtual std::string headerGuard(const DocumentSPtr& pDocument, const std::string& type);
    
    virtual std::string globalVariable(const std::string& variable);
    
    virtual cpp::frm::VariableNameSPtr memberVariableName(const cpp::frm::VariableNameSPtr& name);
    virtual cpp::frm::VariableNameSPtr ptrVariableName(const cpp::frm::VariableNameSPtr& name);
    virtual cpp::frm::VariableNameSPtr memberPtrVariableName(const cpp::frm::VariableNameSPtr& name);
    
    virtual ParameterValueSPtr parameterValue(const cpp::frm::VariableNameSPtr& name);
    
    virtual NamespaceSPtr cppPackageNamespace(const PackageSPtr& pPackage);

    virtual cpp::frm::SimpleTypeSPtr cppEnumType(const EnumerationSPtr& pEnumeration);
    virtual cpp::frm::SimpleTypeSPtr cppInnerEnumType(const EnumerationSPtr& pEnumeration,
                                                      const StructureSPtr& pStructure);
    virtual cpp::frm::ConstructorNameSPtr cppConstructorName(const EnumerationSPtr& pEnumeration);
    virtual NamespaceSPtr cppEnumNamespace(const EnumerationSPtr& pEnumeration);
    
    virtual cpp::frm::SimpleTypeSPtr cppClassType(const TypeSPtr& pType);
    virtual NamespaceSPtr cppClassNamespace(const TypeSPtr& pType);
    virtual cpp::frm::ConstructorNameSPtr cppConstructorName(const TypeSPtr& pType);
    virtual cpp::frm::DestructorNameSPtr cppDestructorName(const TypeSPtr& pType);
    
    virtual cpp::frm::SimpleTypeSPtr cppAutoClassType(const StructureSPtr& pStructure);
    virtual NamespaceSPtr cppAutoClassNamespace(const StructureSPtr& pStructure);
    virtual cpp::frm::ConstructorNameSPtr cppAutoConstructorName(const StructureSPtr& pStructure);
    virtual cpp::frm::DestructorNameSPtr cppAutoDestructorName(const StructureSPtr& pStructure);
    
    virtual cpp::frm::SimpleTypeSPtr cppMainClassType(const StructureSPtr& pStructure);
    virtual NamespaceSPtr cppMainClassNamespace(const StructureSPtr& pStructure);
    
    virtual cpp::frm::SimpleTypeSPtr cppPartialClassType(const StructureSPtr& pStructure);
    
    virtual std::string constValueName(const EnumerationValueSPtr& pEnumerationValue);
    virtual std::string enumValueName(const EnumerationValueSPtr& pEnumerationValue);
    
    virtual cpp::frm::SimpleTypeSPtr cppRawPtrName(const TypeSPtr& pType);
    virtual cpp::frm::SimpleTypeSPtr cppSharedPtrName(const TypeSPtr& pType);
    virtual cpp::frm::SimpleTypeSPtr cppSharedConstPtrName(const TypeSPtr& pType);
    virtual cpp::frm::SimpleTypeSPtr cppWeakPtrName(const TypeSPtr& pType);
    
    virtual cpp::frm::DecoratedTypeSPtr cppRawPtrDecoratedType(const TypeSPtr& pType);
    virtual cpp::frm::DecoratedTypeSPtr cppSharedPtrDecoratedType(const TypeSPtr& pType);
        
    virtual std::string cppMemberName(const FieldSPtr& pField);
    virtual cpp::frm::VariableNameSPtr cppVariableName(const FieldSPtr& pField);
    virtual cpp::frm::VariableNameSPtr cppItemVariableName(const FieldSPtr& pField);
    virtual ParameterValueSPtr cppVariableNameAsParameter(const FieldSPtr& pField);
    
    virtual MethodNameSPtr getMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr setMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr mutableMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr updateMethodName(const FieldSPtr& pField);
    
    virtual MethodNameSPtr constantMethodName(const StructureSPtr& pStructure,
                                            const FieldSPtr& pField);
    virtual MethodNameSPtr defaultMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr alterMethodName(const FieldSPtr& pField);

    virtual MethodNameSPtr destroyMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr clearMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr eraseMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr resetMethodName(const FieldSPtr& pField);
    
    virtual MethodNameSPtr availableMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr existMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr validMethodName(const FieldSPtr& pField);
    virtual MethodNameSPtr changedMethodName(const FieldSPtr& pField);
    
    virtual MethodNameSPtr bitmaskMethodName(const FieldSPtr& pField);
    
    virtual MethodNameSPtr downcastMethodName(const StructureSPtr& pStructure);
    
    virtual std::string defaultValue(const Type::ELiteral literal, const std::string& value) const;
    virtual std::string defaultValue(const AlterSPtr& pAlter) const;
    virtual std::string defaultValue(const FieldSPtr& pField) const;
    
protected:
    FormatterConfigurationPtr mpFormatterConfiguration;
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

