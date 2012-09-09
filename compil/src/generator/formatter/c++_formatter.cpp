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

#include "c++_formatter.h"

#include "aligner.h"

#include "object_factory.h"

#include <sstream>

namespace compil
{

CppFormatter::CppFormatter(const FormatterConfigurationPtr& pFormatterConfiguration,
                           const PackageSPtr& pCurrentPackage)
    : mpFormatterConfiguration(pFormatterConfiguration)
    , mpCurrentPackage(pCurrentPackage)
    , mpKeyword(new CppKeyword(pFormatterConfiguration))
{
}

CppFormatter::~CppFormatter()
{
}

std::string CppFormatter::cppClassName(const std::string& rawName)
{
    return mpKeyword->escapeKeyword(mpFormatterConfiguration->mClassNamePrefix + rawName);
}

std::string CppFormatter::cppPrivateClassName(const std::string& rawName)
{
    return mpKeyword->escapeKeyword(mpFormatterConfiguration->mClassNamePrefix + rawName + "_");
}

std::string CppFormatter::cppRawPtrName(const std::string& rawName)
{
    return rawName + "RPtr";
}

std::string CppFormatter::cppSharedPtrName(const std::string& rawName)
{
    return rawName + "SPtr";
}


std::string CppFormatter::cppSharedConstPtrName(const std::string& rawName)
{
    return rawName + "SCPtr";
}

std::string CppFormatter::cppWeakPtrName(const std::string& rawName)
{
    return rawName + "WPtr";
}

std::string CppFormatter::cppRefName(const std::string& rawName)
{
    return rawName + "Ref";
}

MethodNameSPtr CppFormatter::methodName(const std::string& rawName)
{
    std::string result = rawName;
    std::transform(result.begin() + 0, result.begin() + 1, result.begin() + 0, tolower);
    result = mpKeyword->escapeKeyword(result);
    return methodNameRef(result);
}    

std::string CppFormatter::memberName(const std::string& rawName)
{
    std::string result = "m" + rawName;
    std::transform(result.begin() + 1, result.begin() + 2, result.begin() + 1, toupper);
    return result;
}

std::string CppFormatter::variableName(const std::string& rawName)
{
    return mpKeyword->escapeKeyword(rawName);
}

std::string CppFormatter::memberPtrName(const std::string& rawName)
{
    std::string result = "mp" + rawName;
    std::transform(result.begin() + 2, result.begin() + 3, result.begin() + 2, toupper);
    return result;
}

std::string CppFormatter::variablePtrName(const std::string& rawName)
{
    std::string result = "p" + rawName;
    std::transform(result.begin() + 1, result.begin() + 2, result.begin() + 1, toupper);
    return result;
}

std::string CppFormatter::enumName(const std::string& rawName)
{
    return "E" + rawName;
}

std::string CppFormatter::enumValueName(const std::string& rawName)
{
    std::string result = "k" + rawName;
    std::transform(result.begin() + 1, result.begin() + 2, result.begin() + 1, toupper);
    result = mpKeyword->escapeKeyword(result);
    return result;
}

std::string CppFormatter::constName(const std::string& rawName)
{
    return rawName;
}

std::string CppFormatter::value(int value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}
    
std::string CppFormatter::bitmask(int bitmask)
{
    std::stringstream stream;
    stream << "0x" << std::hex << (1 << bitmask);
    return stream.str();
}

std::string CppFormatter::all_bitmask(int bits)
{
    std::stringstream stream;
    stream << "0x" << std::hex << ((1 << bits) - 1);
    return stream.str();
}

static bool plus_char(int ch)
{
    return ch == '+';
}

static bool not_a_good_char(int ch)
{
    return !(
           ((ch >= '0') && (ch <= '9'))
        || ((ch >= 'a') && (ch <= 'z'))
        || ((ch >= 'A') && (ch <= 'Z')));
}

std::string CppFormatter::headerGuard(const std::string& location, const std::string& type)
{
    std::string guard = "__" + location + "_";
    if ((type != "main") && !type.empty())
        guard += "_" + type + "_";
    guard +=  + "H_";

    std::replace_if( guard.begin(), guard.end(), plus_char, 'p');
    std::replace_if( guard.begin(), guard.end(), not_a_good_char, '_');
    std::transform(guard.begin(), guard.end(), guard.begin(), toupper);
    
    return guard;
}
    
std::string CppFormatter::headerGuard(const DocumentSPtr& pDocument, const std::string& type)
{
    return headerGuard(pDocument->sourceId()->uniquePresentation(), type);
}

std::string CppFormatter::globalVariable(const std::string& variable)
{
    std::string result = "g_" + variable;
    std::transform(result.begin(), result.end(), result.begin(), tolower);
    std::replace_if(result.begin(), result.end(), not_a_good_char, '_');
    return result;
}

NamespaceSPtr CppFormatter::cppPackageNamespace(const PackageSPtr& pPackage)
{
    NamespaceSPtr nmspace = boost::make_shared<Namespace>();
    if (pPackage == mpCurrentPackage)
        return nmspace;
        
    if (!pPackage)
        return nmspace;
        
    if (mpCurrentPackage && (mpCurrentPackage->elements() == pPackage->elements()))
        return nmspace;
        
    const std::vector<std::string>& elements = pPackage->elements();
    std::vector<std::string>::const_iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
        *nmspace << namespaceNameRef(*it);

    return nmspace;
}
    
SimpleTypeSPtr CppFormatter::cppEnumType(const EnumerationSPtr& pEnumeration)
{
    StructureSPtr pStructure = pEnumeration->structure().lock();
    
    NamespaceSPtr nmspace;
    if (pStructure)
        nmspace = cppAutoClassNamespace(pStructure);
    else
        nmspace = boost::make_shared<Namespace>();
        
    NamespaceSPtr packageNamespace = cppPackageNamespace(pEnumeration->package());
    if (!packageNamespace->isVoid())
    {
        nmspace->mutable_names().insert(nmspace->mutable_names().end(),
                                        packageNamespace->names().begin(),
                                        packageNamespace->names().end());
    }
    return CreateSimpleType(nmspace, enumName(pEnumeration->name()->value()));
}

SimpleTypeSPtr CppFormatter::cppInnerEnumType(const EnumerationSPtr& pEnumeration,
                                              const StructureSPtr& pStructure)
{
    NamespaceSPtr nmspace;
    StructureSPtr pEnumStructure = pEnumeration->structure().lock();
    if (  !pStructure || !pEnumStructure
       || !pStructure->isRecursivelyInherit(pEnumStructure))
    {
        nmspace = cppPackageNamespace(pEnumeration->package());
    }
    else
    {
        nmspace = boost::make_shared<Namespace>();
    }

    return CreateSimpleType(nmspace, enumName(pEnumeration->name()->value()));    
}

ConstructorNameSPtr CppFormatter::cppConstructorName(const EnumerationSPtr& pEnumeration)
{
    return constructorNameRef(enumName(pEnumeration->name()->value()));
}

NamespaceSPtr CppFormatter::cppEnumNamespace(const EnumerationSPtr& pEnumeration)
{
    NamespaceSPtr nmspace;
    StructureSPtr pStructure = pEnumeration->structure().lock();
    if (pStructure)
        nmspace = cppAutoClassNamespace(pStructure);
    else
        nmspace = boost::make_shared<Namespace>();

    *nmspace << namespaceNameRef(enumName(pEnumeration->name()->value()));
        
    return nmspace;
}

SimpleTypeSPtr CppFormatter::cppClassType(const TypeSPtr& pType)
{
    EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pType);
    if (pEnumeration)
        return CreateSimpleType(enumName(pType->name()->value()));
    return CreateSimpleType(cppClassName(pType->name()->value()));
}
    
NamespaceSPtr CppFormatter::cppClassNamespace(const TypeSPtr& pType)
{
    NamespaceSPtr nmspace = boost::make_shared<Namespace>();
    *nmspace << namespaceNameRef(cppClassName(pType->name()->value()));
    return nmspace;
}

ConstructorNameSPtr CppFormatter::cppConstructorName(const TypeSPtr& pType)
{
    return constructorNameRef(cppClassName(pType->name()->value()));
}

DestructorNameSPtr CppFormatter::cppDestructorName(const TypeSPtr& pType)
{
    return destructorNameRef(cppClassName(pType->name()->value()));
}

SimpleTypeSPtr CppFormatter::cppAutoClassType(const StructureSPtr& pStructure)
{
    if (pStructure->partial())
        return cppPartialClassType(pStructure);
    else
        return cppMainClassType(pStructure);
}

NamespaceSPtr CppFormatter::cppAutoClassNamespace(const StructureSPtr& pStructure)
{
    NamespaceSPtr nmspace = boost::make_shared<Namespace>();
    *nmspace << namespaceNameRef(cppAutoClassType(pStructure)->value());
    return nmspace;
}

ConstructorNameSPtr CppFormatter::cppAutoConstructorName(const StructureSPtr& pStructure)
{
    return constructorNameRef(cppAutoClassType(pStructure)->value());
}

DestructorNameSPtr CppFormatter::cppAutoDestructorName(const StructureSPtr& pStructure)
{
    return destructorNameRef(cppAutoClassType(pStructure)->value());
}

SimpleTypeSPtr CppFormatter::cppMainClassType(const StructureSPtr& pStructure)
{
    return CreateSimpleType(cppPackageNamespace(pStructure->package()),
                            cppClassName(pStructure->name()->value()));
}
    
NamespaceSPtr CppFormatter::cppMainClassNamespace(const StructureSPtr& pStructure)
{
    NamespaceSPtr nmspace = boost::make_shared<Namespace>();
    *nmspace << namespaceNameRef(cppMainClassType(pStructure)->value());
    return nmspace;
}

SimpleTypeSPtr CppFormatter::cppPartialClassType(const StructureSPtr& pStructure)
{
    return CreateSimpleType(cppClassName(pStructure->name()->value() + "Partial"));
}

std::string CppFormatter::constValueName(const EnumerationValueSPtr& pEnumerationValue)
{
    return constName(pEnumerationValue->name()->value() + "_value");
}

std::string CppFormatter::enumValueName(const EnumerationValueSPtr& pEnumerationValue)
{
    return enumValueName(pEnumerationValue->name()->value());
}

SimpleTypeSPtr CppFormatter::cppRawPtrName(const TypeSPtr& pType)
{
    return CreateSimpleType(cppPackageNamespace(pType->package()),
                            cppRawPtrName(pType->name()->value()));
}

SimpleTypeSPtr CppFormatter::cppSharedPtrName(const TypeSPtr& pType)
{
    return CreateSimpleType(cppPackageNamespace(pType->package()),
                            cppSharedPtrName(pType->name()->value()));
}

SimpleTypeSPtr CppFormatter::cppSharedConstPtrName(const TypeSPtr& pType)
{
    return CreateSimpleType(cppPackageNamespace(pType->package()),
                            cppSharedConstPtrName(pType->name()->value()));
}

SimpleTypeSPtr CppFormatter::cppWeakPtrName(const TypeSPtr& pType)
{
    return CreateSimpleType(cppPackageNamespace(pType->package()),
                            cppWeakPtrName(pType->name()->value()));
}

DecoratedTypeSPtr CppFormatter::cppRawPtrDecoratedType(const TypeSPtr& pType)
{
    return CreateDecoratedType(cppRawPtrName(pType));
}

DecoratedTypeSPtr CppFormatter::cppSharedPtrDecoratedType(const TypeSPtr& pType)
{
    return CreateDecoratedType(ETypeDeclaration::const_(),
                               cppSharedPtrName(pType),
                               ETypeDecoration::reference());
}

std::string CppFormatter::cppMemberName(const FieldSPtr& pField)
{
    return memberName(pField->name()->value());
}

std::string CppFormatter::cppVariableName(const FieldSPtr& pField)
{
    return variableName(pField->name()->value());
}

MethodNameSPtr CppFormatter::getMethodName(const FieldSPtr& pField)
{
    return methodName(pField->name()->value());
}
    
MethodNameSPtr CppFormatter::setMethodName(const FieldSPtr& pField)
{
    return methodName("set_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::mutableMethodName(const FieldSPtr& pField)
{
    return methodName("mutable_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::updateMethodName(const FieldSPtr& pField)
{
    return methodName("update_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::constantMethodName(const StructureSPtr& pStructure,
                                                const FieldSPtr& pField)
{
    if (pField->structure().lock() == pStructure)
        return defaultMethodName(pField);
    else
        return alterMethodName(pField);
}
    

MethodNameSPtr CppFormatter::defaultMethodName(const FieldSPtr& pField)
{
    return methodName("default_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::alterMethodName(const FieldSPtr& pField)
{
    return methodName("alter_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::destroyMethodName(const FieldSPtr& pField)
{
    if (pField->defaultValue())
    {
        if (pField->defaultValue()->optional())
        {
            return clearMethodName(pField);
        }
        else
        {
            return resetMethodName(pField);
        }
    } 
    return eraseMethodName(pField);
}

MethodNameSPtr CppFormatter::clearMethodName(const FieldSPtr& pField)
{
    return methodName("clear_" + pField->name()->value());
}
    
MethodNameSPtr CppFormatter::resetMethodName(const FieldSPtr& pField)
{
    return methodName("reset_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::eraseMethodName(const FieldSPtr& pField)
{
    return methodName("erase_" + pField->name()->value());
}
    
MethodNameSPtr CppFormatter::availableMethodName(const FieldSPtr& pField)
{
    if (pField->defaultValue())
    {
        if (pField->defaultValue()->optional())
        {
            return existMethodName(pField);
        }
        else
        {
            return changedMethodName(pField);
        }
    } 
    return validMethodName(pField);
}


MethodNameSPtr CppFormatter::existMethodName(const FieldSPtr& pField)
{
    return methodName("exist_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::changedMethodName(const FieldSPtr& pField)
{
    return methodName("changed_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::validMethodName(const FieldSPtr& pField)
{
    return methodName("valid_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::bitmaskMethodName(const FieldSPtr& pField)
{
    return methodName("bitmask_" + pField->name()->value());
}

MethodNameSPtr CppFormatter::downcastMethodName(const StructureSPtr& pStructure)
{
    return methodName("downcast" + pStructure->name()->value());
}

std::string CppFormatter::defaultValue(const Type::ELiteral literal, const std::string& value) const
{
    switch (literal.value())
    {
        case Type::ELiteral::kString: 
            return "\"" + value + "\"";
        default:
            break;
    }
    return value;
}

std::string CppFormatter::defaultValue(const AlterSPtr& pAlter) const
{
    return defaultValue(pAlter->field()->type()->literal(), pAlter->defaultValue()->value());
}

std::string CppFormatter::defaultValue(const FieldSPtr& pField) const
{
    return defaultValue(pField->type()->literal(), pField->defaultValue()->value());   
}

}

