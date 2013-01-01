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

#include "compil/all/object_factory.h"

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

cpp::frm::MethodNameSPtr CppFormatter::methodName(const std::string& rawName)
{
    std::string result = rawName;
    std::transform(result.begin() + 0, result.begin() + 1, result.begin() + 0, tolower);
    result = mpKeyword->escapeKeyword(result);
    return cpp::frm::methodNameRef(result);
}

std::string CppFormatter::name(const std::string& rawName)
{
    return mpKeyword->escapeKeyword(rawName);
}

std::string CppFormatter::memberName(const std::string& rawName)
{
    std::string result = "m" + rawName;
    std::transform(result.begin() + 1, result.begin() + 2, result.begin() + 1, toupper);
    return result;
}

std::string CppFormatter::ptrName(const std::string& rawName)
{
    std::string result = "p" + rawName;
    std::transform(result.begin() + 1, result.begin() + 2, result.begin() + 1, toupper);
    return result;
}

std::string CppFormatter::memberPtrName(const std::string& rawName)
{
    std::string result = "mp" + rawName;
    std::transform(result.begin() + 2, result.begin() + 3, result.begin() + 2, toupper);
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

std::string CppFormatter::headerGuard(const FileSPtr& file, const std::string& type)
{
    return headerGuard(file->sourceId()->uniquePresentation(), type);
}

std::string CppFormatter::globalVariable(const std::string& variable)
{
    std::string result = "g" + variable;
    std::transform(result.begin(), result.end(), result.begin(), tolower);
    std::replace_if(result.begin(), result.end(), not_a_good_char, '_');
    return result;
}

cpp::frm::VariableNameSPtr CppFormatter::memberVariableName(const cpp::frm::VariableNameSPtr& name)
{
    return cpp::frm::variableNameRef(memberName(name->value()));
}

cpp::frm::VariableNameSPtr CppFormatter::ptrVariableName(const cpp::frm::VariableNameSPtr& name)
{
    return cpp::frm::variableNameRef(ptrName(name->value()));
}

cpp::frm::VariableNameSPtr CppFormatter::memberPtrVariableName(const cpp::frm::VariableNameSPtr& name)
{
    return cpp::frm::variableNameRef(memberPtrName(name->value()));
}

cpp::frm::ParameterValueSPtr CppFormatter::parameterValue(const cpp::frm::VariableNameSPtr& name)
{
    return cpp::frm::parameterValueRef(name->value());
}

cpp::frm::NamespaceSPtr getPackageNamespace(const PackageSPtr& pPackage)
{
    cpp::frm::NamespaceSPtr nmspace = cpp::frm::namespaceRef();

    const std::vector<PackageElement>& elements = pPackage->short_();

    std::vector<PackageElement>::const_iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
        *nmspace << cpp::frm::namespaceNameRef(it->value());

    return nmspace;
}

cpp::frm::NamespaceSPtr CppFormatter::cppPackageNamespace(const PackageSPtr& pPackage)
{
    cpp::frm::NamespaceSPtr nmspace = cpp::frm::namespaceRef();
    if (pPackage == mpCurrentPackage)
        return nmspace;

    if (!pPackage)
        return nmspace;

    cpp::frm::NamespaceSPtr packageNamespace = getPackageNamespace(pPackage);
    if (!mpCurrentPackage)
        return packageNamespace;

    cpp::frm::NamespaceSPtr currentNamespace = getPackageNamespace(mpCurrentPackage);
    std::vector<cpp::frm::NamespaceNameSPtr>::const_iterator cit = currentNamespace->names().begin();
    std::vector<cpp::frm::NamespaceNameSPtr>::const_iterator it = packageNamespace->names().begin();
    while (cit != currentNamespace->names().end() && it != packageNamespace->names().end())
    {
        if ((*cit)->value() != (*it)->value())
            break;
        cit++;
        it++;
    }

    for (; it != packageNamespace->names().end(); ++it)
        *nmspace << *it;

    return nmspace;
}

cpp::frm::TypeSPtr CppFormatter::constType(const cpp::frm::TypeSPtr& type) const
{
    return cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                               << type->namespace_()
                               << type->name();
}

cpp::frm::TypeSPtr CppFormatter::constTypeRef(const cpp::frm::TypeSPtr& type) const
{
    return cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                               << type->namespace_()
                               << type->name()
                               << cpp::frm::ETypeDecoration::reference();
}

cpp::frm::TypeSPtr CppFormatter::typeRef(const cpp::frm::TypeSPtr& type) const
{
    return cpp::frm::typeRef() << type->namespace_()
                               << type->name()
                               << cpp::frm::ETypeDecoration::reference();
}

cpp::frm::TypeSPtr CppFormatter::cppEnumType(const EnumerationSPtr& pEnumeration)
{
    StructureSPtr pStructure = pEnumeration->structure().lock();

    cpp::frm::NamespaceSPtr nmspace;
    if (pStructure)
        nmspace = cppAutoClassNamespace(pStructure);
    else
        nmspace = cpp::frm::namespaceRef();

    cpp::frm::NamespaceSPtr packageNamespace = cppPackageNamespace(pEnumeration->package());
    if (!packageNamespace->isVoid())
    {
        nmspace->mutable_names().insert(nmspace->mutable_names().end(),
                                        packageNamespace->names().begin(),
                                        packageNamespace->names().end());
    }
    return cpp::frm::typeRef() << nmspace
                               << cpp::frm::typeNameRef(enumName(pEnumeration->name()->value()));
}

cpp::frm::TypeSPtr CppFormatter::cppInnerEnumType(const EnumerationSPtr& pEnumeration,
                                                  const StructureSPtr& pStructure)
{
    cpp::frm::NamespaceSPtr nmspace;
    StructureSPtr pEnumStructure = pEnumeration->structure().lock();
    if (  !pStructure || !pEnumStructure
       || !pStructure->isRecursivelyInherit(pEnumStructure))
    {
        nmspace = cppPackageNamespace(pEnumeration->package());
    }
    else
    {
        nmspace = cpp::frm::namespaceRef();
    }

    return cpp::frm::typeRef() << nmspace
                               << cpp::frm::typeNameRef(enumName(pEnumeration->name()->value()));
}

cpp::frm::ConstructorNameSPtr CppFormatter::cppConstructorName(const EnumerationSPtr& pEnumeration)
{
    return cpp::frm::constructorNameRef(enumName(pEnumeration->name()->value()));
}

cpp::frm::NamespaceSPtr CppFormatter::cppEnumNamespace(const EnumerationSPtr& pEnumeration)
{
    cpp::frm::NamespaceSPtr nmspace;
    StructureSPtr pStructure = pEnumeration->structure().lock();
    if (pStructure)
        nmspace = cppAutoClassNamespace(pStructure);
    else
        nmspace = cpp::frm::namespaceRef();

    *nmspace << cpp::frm::namespaceNameRef(enumName(pEnumeration->name()->value()));

    return nmspace;
}

cpp::frm::TypeSPtr CppFormatter::cppClassType(const TypeSPtr& pType)
{
    EnumerationSPtr pEnumeration = ObjectFactory::downcastEnumeration(pType);
    if (pEnumeration)
        return cpp::frm::typeRef() << cpp::frm::typeNameRef(enumName(pType->name()->value()));
    return cpp::frm::typeRef() << cpp::frm::typeNameRef(cppClassName(pType->name()->value()));
}

cpp::frm::NamespaceSPtr CppFormatter::cppClassNamespace(const TypeSPtr& pType)
{
    cpp::frm::NamespaceSPtr nmspace = cpp::frm::namespaceRef();
    nmspace << cpp::frm::namespaceNameRef(cppClassName(pType->name()->value()));
    return nmspace;
}

cpp::frm::ConstructorNameSPtr CppFormatter::cppConstructorName(const TypeSPtr& pType)
{
    return cpp::frm::constructorNameRef(cppClassName(pType->name()->value()));
}

cpp::frm::DestructorNameSPtr CppFormatter::cppDestructorName(const TypeSPtr& pType)
{
    return cpp::frm::destructorNameRef(cppClassName(pType->name()->value()));
}

cpp::frm::TypeSPtr CppFormatter::cppAutoClassType(const StructureSPtr& pStructure)
{
    if (pStructure->partial())
        return cppPartialClassType(pStructure);
    else
        return cppMainClassType(pStructure);
}

cpp::frm::NamespaceSPtr CppFormatter::cppAutoClassNamespace(const StructureSPtr& pStructure)
{
    cpp::frm::NamespaceSPtr nmspace = cpp::frm::namespaceRef();
    nmspace << cpp::frm::namespaceNameRef(cppAutoClassType(pStructure)->name()->value());
    return nmspace;
}

cpp::frm::ConstructorNameSPtr CppFormatter::cppAutoConstructorName(const StructureSPtr& pStructure)
{
    return cpp::frm::constructorNameRef(cppAutoClassType(pStructure)->name()->value());
}

cpp::frm::DestructorNameSPtr CppFormatter::cppAutoDestructorName(const StructureSPtr& pStructure)
{
    return cpp::frm::destructorNameRef(cppAutoClassType(pStructure)->name()->value());
}

cpp::frm::TypeSPtr CppFormatter::cppMainClassType(const StructureSPtr& pStructure)
{
    return cpp::frm::typeRef() << cppPackageNamespace(pStructure->package())
                               << cpp::frm::typeNameRef(cppClassName(pStructure->name()->value()));
}

cpp::frm::NamespaceSPtr CppFormatter::cppMainClassNamespace(const StructureSPtr& pStructure)
{
    cpp::frm::NamespaceSPtr nmspace = cpp::frm::namespaceRef();
    nmspace << cpp::frm::namespaceNameRef(cppMainClassType(pStructure)->name()->value());
    return nmspace;
}

cpp::frm::TypeSPtr CppFormatter::cppPartialClassType(const StructureSPtr& pStructure)
{
    return cpp::frm::typeRef() << cpp::frm::typeNameRef(cppClassName(pStructure->name()->value() + "Partial"));
}

std::string CppFormatter::constValueName(const EnumerationValueSPtr& pEnumerationValue)
{
    return constName(pEnumerationValue->name()->value() + "_value");
}

std::string CppFormatter::enumValueName(const EnumerationValueSPtr& pEnumerationValue)
{
    return enumValueName(pEnumerationValue->name()->value());
}

cpp::frm::TypeSPtr CppFormatter::cppRawPtrName(const TypeSPtr& pType)
{
    return cpp::frm::typeRef() << cppPackageNamespace(pType->package())
                               << cpp::frm::typeNameRef(cppRawPtrName(cppClassType(pType)->name()->value()));
}

cpp::frm::TypeSPtr CppFormatter::cppSharedPtrName(const TypeSPtr& pType)
{
    return cpp::frm::typeRef() << cppPackageNamespace(pType->package())
                               << cpp::frm::typeNameRef(cppSharedPtrName(cppClassType(pType)->name()->value()));
}

cpp::frm::TypeSPtr CppFormatter::cppSharedConstPtrName(const TypeSPtr& pType)
{
    return cpp::frm::typeRef() << cppPackageNamespace(pType->package())
                               << cpp::frm::typeNameRef(cppSharedConstPtrName(cppClassType(pType)->name()->value()));
}

cpp::frm::TypeSPtr CppFormatter::cppWeakPtrName(const TypeSPtr& pType)
{
    return cpp::frm::typeRef() << cppPackageNamespace(pType->package())
                               << cpp::frm::typeNameRef(cppWeakPtrName(cppClassType(pType)->name()->value()));
}

cpp::frm::TypeSPtr CppFormatter::cppRawPtrDecoratedType(const TypeSPtr& pType)
{
    return cppRawPtrName(pType);
}

cpp::frm::TypeSPtr CppFormatter::cppSharedPtrDecoratedType(const TypeSPtr& pType)
{
    cpp::frm::TypeSPtr type = cppSharedPtrName(pType);

    return cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                               << type->namespace_()
                               << type->name()
                               << cpp::frm::ETypeDecoration::reference();
}

std::string CppFormatter::cppMemberName(const FieldSPtr& pField)
{
    return memberName(pField->name()->value());
}

cpp::frm::VariableNameSPtr CppFormatter::cppVariableName(const FieldSPtr& pField)
{
    return cpp::frm::variableNameRef(name(pField->name()->value()));
}

cpp::frm::VariableNameSPtr CppFormatter::cppItemVariableName(const FieldSPtr& pField)
{
    return cpp::frm::variableNameRef(name(pField->name()->value() + "Item"));
}

cpp::frm::ParameterValueSPtr CppFormatter::cppVariableNameAsParameter(const FieldSPtr& pField)
{
    return cpp::frm::parameterValueRef(name(pField->name()->value()));
}

cpp::frm::MethodNameSPtr CppFormatter::getMethodName(const FieldSPtr& pField)
{
    return methodName(pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::setMethodName(const FieldSPtr& pField)
{
    return methodName("set_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::mutableMethodName(const FieldSPtr& pField)
{
    return methodName("mutable_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::updateMethodName(const FieldSPtr& pField)
{
    return methodName("update_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::constantMethodName(const StructureSPtr& pStructure,
                                                          const FieldSPtr& pField)
{
    if (pField->structure().lock() == pStructure)
        return defaultMethodName(pField);
    else
        return alterMethodName(pField);
}


cpp::frm::MethodNameSPtr CppFormatter::defaultMethodName(const FieldSPtr& pField)
{
    return methodName("default_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::alterMethodName(const FieldSPtr& pField)
{
    return methodName("alter_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::destroyMethodName(const FieldSPtr& pField)
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

cpp::frm::MethodNameSPtr CppFormatter::clearMethodName(const FieldSPtr& pField)
{
    return methodName("clear_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::resetMethodName(const FieldSPtr& pField)
{
    return methodName("reset_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::eraseMethodName(const FieldSPtr& pField)
{
    return methodName("erase_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::availableMethodName(const FieldSPtr& pField)
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


cpp::frm::MethodNameSPtr CppFormatter::existMethodName(const FieldSPtr& pField)
{
    return methodName("exist_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::changedMethodName(const FieldSPtr& pField)
{
    return methodName("changed_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::validMethodName(const FieldSPtr& pField)
{
    return methodName("valid_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::bitmaskMethodName(const FieldSPtr& pField)
{
    return methodName("bitmask_" + pField->name()->value());
}

cpp::frm::MethodNameSPtr CppFormatter::downcastMethodName(const StructureSPtr& pStructure)
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

