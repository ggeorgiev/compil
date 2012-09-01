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

FunctionName CppFormatter::methodName(const std::string& rawName)
{
    std::string result = rawName;
    std::transform(result.begin() + 0, result.begin() + 1, result.begin() + 0, tolower);
    result = mpKeyword->escapeKeyword(result);
    return *CreateFunctionName(result);
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

Namespace CppFormatter::cppPackageNamespace(const PackageSPtr& pPackage)
{
    Namespace nmspace;
    if (pPackage == mpCurrentPackage)
        return nmspace;
        
    if (!pPackage)
        return nmspace;
        
    if (mpCurrentPackage && (mpCurrentPackage->elements() == pPackage->elements()))
        return nmspace;
        
    const std::vector<std::string>& elements = pPackage->elements();
    std::vector<std::string>::const_iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
    {
        nmspace = nmspace + lang::cpp::namespaceNameRef(*it);
    }
    return nmspace;
}
    
SimpleType CppFormatter::cppEnumType(const EnumerationSPtr& pEnumeration)
{
    StructureSPtr pStructure = pEnumeration->structure().lock();
    Namespace nmspace;
    if (pStructure)
        nmspace = cppAutoClassNamespace(pStructure);
    return *CreateSimpleType(nmspace + cppPackageNamespace(pEnumeration->package()), 
                                       enumName(pEnumeration->name()->value()));    
}

SimpleType CppFormatter::cppInnerEnumType(const EnumerationSPtr& pEnumeration,
                                          const StructureSPtr& pStructure)
{
    Namespace nmspace;
    StructureSPtr pEnumStructure = pEnumeration->structure().lock();
    if (  !pStructure || !pEnumStructure
       || !pStructure->isRecursivelyInherit(pEnumStructure))
        nmspace = cppPackageNamespace(pEnumeration->package());

    return *CreateSimpleType(nmspace, enumName(pEnumeration->name()->value()));    
}

Namespace CppFormatter::cppEnumNamespace(const EnumerationSPtr& pEnumeration)
{
    StructureSPtr pStructure = pEnumeration->structure().lock();
    if (pStructure)
        return cppAutoClassNamespace(pStructure) + 
               lang::cpp::namespaceNameRef(enumName(pEnumeration->name()->value()));
        
    return *CreateNamespace(enumName(pEnumeration->name()->value()));
}

SimpleType CppFormatter::cppClassType(const TypeSPtr& pType)
{
    EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pType);
    if (pEnumeration)
        return *CreateSimpleType(enumName(pType->name()->value()));
    return *CreateSimpleType(cppClassName(pType->name()->value()));
}
    
Namespace CppFormatter::cppClassNamespace(const TypeSPtr& pType)
{
    return *CreateNamespace(cppClassName(pType->name()->value()));
}

SimpleType CppFormatter::cppAutoClassType(const StructureSPtr& pStructure)
{
    if (pStructure->partial())
        return cppPartialClassType(pStructure);
    else
        return cppMainClassType(pStructure);
}

Namespace CppFormatter::cppAutoClassNamespace(const StructureSPtr& pStructure)
{
    return *CreateNamespace(cppAutoClassType(pStructure).value());
}
    
SimpleType CppFormatter::cppMainClassType(const StructureSPtr& pStructure)
{
    return *CreateSimpleType(cppPackageNamespace(pStructure->package()),
                                      cppClassName(pStructure->name()->value()));
}

Namespace CppFormatter::cppMainClassNamespace(const StructureSPtr& pStructure)
{
    return *CreateNamespace(cppMainClassType(pStructure).value());
}

SimpleType CppFormatter::cppPartialClassType(const StructureSPtr& pStructure)
{
    return *CreateSimpleType(cppClassName(pStructure->name()->value() + "Partial"));
}

Namespace CppFormatter::cppPartialClassNamespace(const StructureSPtr& pStructure)
{
    return *CreateNamespace(cppPartialClassType(pStructure).value());
}

std::string CppFormatter::constValueName(const EnumerationValueSPtr& pEnumerationValue)
{
    return constName(pEnumerationValue->name()->value() + "_value");
}

std::string CppFormatter::enumValueName(const EnumerationValueSPtr& pEnumerationValue)
{
    return enumValueName(pEnumerationValue->name()->value());
}

SimpleType CppFormatter::cppRawPtrName(const TypeSPtr& pType)
{
    return *CreateSimpleType(cppPackageNamespace(pType->package()),
                                      cppRawPtrName(pType->name()->value()));
}

SimpleType CppFormatter::cppSharedPtrName(const TypeSPtr& pType)
{
    return *CreateSimpleType(cppPackageNamespace(pType->package()),
                                      cppSharedPtrName(pType->name()->value()));
}

SimpleType CppFormatter::cppSharedConstPtrName(const TypeSPtr& pType)
{
    return *CreateSimpleType(cppPackageNamespace(pType->package()),
                                      cppSharedConstPtrName(pType->name()->value()));
}

SimpleType CppFormatter::cppWeakPtrName(const TypeSPtr& pType)
{
    return *CreateSimpleType(cppPackageNamespace(pType->package()),
                                      cppWeakPtrName(pType->name()->value()));
}

DecoratedType CppFormatter::cppRawPtrDecoratedType(const TypeSPtr& pType)
{
    return *CreateDecoratedType(cppRawPtrName(pType));
}

DecoratedType CppFormatter::cppSharedPtrDecoratedType(const TypeSPtr& pType)
{
    return *CreateDecoratedType(cst, cppSharedPtrName(pType), ref);
}

std::string CppFormatter::cppMemberName(const FieldSPtr& pField)
{
    return memberName(pField->name()->value());
}

std::string CppFormatter::cppVariableName(const FieldSPtr& pField)
{
    return variableName(pField->name()->value());
}

FunctionName CppFormatter::getMethodName(const FieldSPtr& pField)
{
    return methodName(pField->name()->value());
}
    
FunctionName CppFormatter::setMethodName(const FieldSPtr& pField)
{
    return methodName("set_" + pField->name()->value());
}

FunctionName CppFormatter::mutableMethodName(const FieldSPtr& pField)
{
    return methodName("mutable_" + pField->name()->value());
}


FunctionName CppFormatter::constantMethodName(const StructureSPtr& pStructure,
                                              const FieldSPtr& pField)
{
    if (pField->structure().lock() == pStructure)
        return defaultMethodName(pField);
    else
        return alterMethodName(pField);
}
    

FunctionName CppFormatter::defaultMethodName(const FieldSPtr& pField)
{
    return methodName("default_" + pField->name()->value());
}

FunctionName CppFormatter::alterMethodName(const FieldSPtr& pField)
{
    return methodName("alter_" + pField->name()->value());
}

FunctionName CppFormatter::destroyMethodName(const FieldSPtr& pField)
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

FunctionName CppFormatter::clearMethodName(const FieldSPtr& pField)
{
    return methodName("clear_" + pField->name()->value());
}
    
FunctionName CppFormatter::resetMethodName(const FieldSPtr& pField)
{
    return methodName("reset_" + pField->name()->value());
}

FunctionName CppFormatter::eraseMethodName(const FieldSPtr& pField)
{
    return methodName("erase_" + pField->name()->value());
}
    
FunctionName CppFormatter::availableMethodName(const FieldSPtr& pField)
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


FunctionName CppFormatter::existMethodName(const FieldSPtr& pField)
{
    return methodName("exist_" + pField->name()->value());
}

FunctionName CppFormatter::changedMethodName(const FieldSPtr& pField)
{
    return methodName("changed_" + pField->name()->value());
}

FunctionName CppFormatter::validMethodName(const FieldSPtr& pField)
{
    return methodName("valid_" + pField->name()->value());
}

FunctionName CppFormatter::bitmaskMethodName(const FieldSPtr& pField)
{
    return methodName("bitmask_" + pField->name()->value());
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

