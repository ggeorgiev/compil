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

#include "library/compil/document.h"
#include "library/compil/package.h"

#include "language/c++/class/identifier_class_name.h"

#include "boost/unordered_map.hpp"

namespace lib
{

namespace compil
{

DocumentSPtr CompilDocument::create()
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

        pStringType->mOperatorSupport[EOperatorAction::equalTo()] = EOperatorFlags::natural();
        pStringType->mOperatorSupport[EOperatorAction::notEqualTo()] = EOperatorFlags::natural();
        pStringType->mOperatorSupport[EOperatorAction::lessThan()] = EOperatorFlags::natural();

        pName.reset(new Name());
        pName->set_value("binary");
        pBinaryType->set_name(pName);
        pBinaryType->set_literal(Type::ELiteral::binary());
        pBinaryType->set_kind(Type::EKind::string());
        //pBinaryType->set_cast(CastableType::ECast::weak());

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
        pDateType->set_package(CompilPackage::time());

        pName.reset(new Name());
        pName->set_value("time");
        pTimeType->set_name(pName);
        pTimeType->set_literal(Type::ELiteral::binary());
        pTimeType->set_kind(Type::EKind::object());
        pTimeType->set_package(CompilPackage::time());

        pName.reset(new Name());
        pName->set_value("datetime");
        pDatetimeType->set_name(pName);
        pDatetimeType->set_literal(Type::ELiteral::binary());
        pDatetimeType->set_kind(Type::EKind::object());
        pDatetimeType->set_package(CompilPackage::time());

        pName.reset(new Name());
        pName->set_value("duration");
        pTimeDirationType->set_name(pName);
        pTimeDirationType->set_literal(Type::ELiteral::binary());
        pTimeDirationType->set_kind(Type::EKind::object());
        pTimeDirationType->set_package(CompilPackage::time());

        pName.reset(new Name());
        pName->set_value("reference");
        pReference->set_name(pName);
        pReference->set_literal(Type::ELiteral::reference());
        pReference->set_kind(Type::EKind::object());
        pReference->set_cast(CastableType::ECast::weak());

        pName.reset(new Name());
        pName->set_value("vector");
        pVector->set_name(pName);
        pVector->set_literal(Type::ELiteral::container());
        pVector->set_kind(Type::EKind::object());
        pVector->set_cast(CastableType::ECast::weak());
    }

    DocumentSPtr document = boost::make_shared<Document>();
    document->addType(pBoolType);

    document->addType(pSizeType);

    document->addType(pSmallType);
    document->addType(pShortType);
    document->addType(pIntegerType);
    document->addType(pLongType);

    document->addType(pByteType);
    document->addType(pWordType);
    document->addType(pDWordType);
    document->addType(pQWordType);

    document->addType(pReal32Type);
    document->addType(pReal64Type);
    document->addType(pStringType);
    document->addType(pBinaryType);

    document->addType(pDateType);
    document->addType(pTimeType);
    document->addType(pDatetimeType);
    document->addType(pTimeDirationType);

    document->addUnfinishedUnaryTemplate(pReference);
    document->addUnfinishedUnaryTemplate(pVector);

    return document;
}

}

}