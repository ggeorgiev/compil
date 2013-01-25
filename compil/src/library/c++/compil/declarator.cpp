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
#include "library/c++/compil/declarator.h"
#include "library/c++/stl/string.h"

namespace lib
{

namespace cpp
{

DeclarationSpecifierSPtr CppDeclarator::declarationSpecifier(const lang::compil::TypeSPtr& type)
{
    TypeKind kind = CppType::kind(type);
    
    switch (kind.kind().value())
    {
        case EKind::kBuiltin:
            return typeDeclarationSpecifierRef() << CppType::builtinSpecifier(type);
        case EKind::kClass:
            return CppType::classSpecifier(type);
        case EKind::kGeneric:
            return (genericDeclarationSpecifierRef() << kind.generic());
    }

    BOOST_ASSERT(false);
    return DeclarationSpecifierSPtr();
}


DeclaratorParameterDeclarationSPtr CppDeclarator::constArgument(const TypeSpecifierSPtr& specifier,
                                                                const DeclaratorSPtr& declarator)
{
    DeclarationSpecifierSequenceSPtr declarationSpecifierSequence = declarationSpecifierSequenceRef()
        << (typeDeclarationSpecifierRef() << (cVQualifierTypeSpecifierRef() << ECVQualifier::const_()))
        << (typeDeclarationSpecifierRef() << specifier);

    DeclaratorParameterDeclarationSPtr declaratorParameterDeclaration = declaratorParameterDeclarationRef()
        << declarationSpecifierSequence
        << declarator;
        
    return declaratorParameterDeclaration; 
}

DeclaratorParameterDeclarationSPtr CppDeclarator::constReferenceArgument(const ClassSPtr& class_,
                                                                         const DeclaratorSPtr& declarator)
{
    ClassDeclarationSpecifierSPtr classSpecifier = classDeclarationSpecifierRef()
        << class_;
                    
    PointerDeclaratorSPtr pointerDeclarator = pointerDeclaratorRef()
        << reference()
        << declarator;
        
    DeclarationSpecifierSequenceSPtr declarationSpecifierSequence = declarationSpecifierSequenceRef()
        << (typeDeclarationSpecifierRef() << (cVQualifierTypeSpecifierRef() << ECVQualifier::const_()))
        << classSpecifier;
        
    DeclaratorParameterDeclarationSPtr declaratorParameterDeclaration = declaratorParameterDeclarationRef()
        << declarationSpecifierSequence
        << pointerDeclarator;
        
    return declaratorParameterDeclaration;
}

DeclaratorParameterDeclarationSPtr CppDeclarator::inputArgument(const lang::compil::TypeSPtr& type,
                                                                const DeclaratorSPtr& declarator)
{
    TypeKind kind = CppType::kind(type);
    
    switch (kind.kind().value())
    {
        case EKind::kBuiltin:
            return constArgument(CppType::builtinSpecifier(type), declarator);
        case EKind::kClass:
            return constReferenceArgument(CppType::class_(type), declarator);
        case EKind::kGeneric:
            return declaratorParameterDeclarationRef()
                << (declarationSpecifierSequenceRef()
                        << (genericDeclarationSpecifierRef() << kind.generic()))
                << declarator;
    }

    BOOST_ASSERT(false);
    return DeclaratorParameterDeclarationSPtr();
}

PointerOperatorSPtr CppDeclarator::reference()
{
    static PointerOperatorSPtr reference = referencePointerOperatorRef();
    return reference;
}


}

}