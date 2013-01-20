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

#include "library/c++/compil/type.h"

namespace lib
{

namespace cpp
{

lang::cpp::TypeKind CppType::kind(const lang::compil::TypeSPtr& type)
{
    lang::cpp::TypeKind kind;

    lang::compil::IntegerSPtr integer = lang::compil::ObjectFactory::downcastInteger(type);
    if (integer)
    {
        kind.set_kind(lang::cpp::EKind::builtin());
    }
    else
    {
        kind.set_kind(lang::cpp::EKind::generic());
        kind.set_generic(lang::cpp::EGeneric::string());
    }

    return kind;
}

lang::cpp::BuiltinSimpleTypeSpecifierSPtr CppType::builtinSpecifier(const lang::compil::TypeSPtr& type)
{
    std::string name = type->name()->value();
    lang::compil::IntegerSPtr integer = lang::compil::ObjectFactory::downcastInteger(type);
    if (integer)
    {
        lang::cpp::BuiltinSimpleTypeSpecifier::EType type;
    
        if (name == "size")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::size();
        else
        if (name == "small")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::signedChar();
        else
        if (name == "short")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::signedShort();
        else
        if (name == "integer")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::signedLong();
        else
        if (name == "long")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::signedLongLong();
        else
        if (name == "byte")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::unsignedChar();
        else
        if (name == "word")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::unsignedShort();
        else
        if (name == "dword")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::unsignedLong();
        else
        if (name == "qword")
            type = lang::cpp::BuiltinSimpleTypeSpecifier::EType::unsignedLongLong();
        else
            BOOST_ASSERT(false);
            
        return lang::cpp::builtinSimpleTypeSpecifierRef() << type;

    }

    return lang::cpp::BuiltinSimpleTypeSpecifierSPtr();
}

}

}