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

#include "library/c++/compil/specimen.h"
#include "library/c++/compil/namespace.h"
#include "library/c++/compil/declaration.h"
#include "library/c++/stl/string.h"

#include "language/c++/class/identifier_class_name.h"
#include "language/c++/declarator/declarator_factory.h"
#include "language/c++/declaration/declaration_factory.h"

#include "boost/unordered_map.hpp"

namespace lib
{

namespace cpp
{

ClassNameSPtr CppSpecimen::className(const SpecimenSPtr& specimen)
{
    static boost::unordered_map<SpecimenSPtr, ClassNameSPtr> map;
    boost::unordered_map<SpecimenSPtr, ClassNameSPtr>::iterator it = map.find(specimen);
    if (it != map.end())
        return it->second;

    ClassNameSPtr className = identifierClassNameRef() << (identifierRef() << specimen->name()->value());
    
    map[specimen] = className;
    return className;
}

ClassSPtr CppSpecimen::class_(const SpecimenSPtr& specimen)
{
    static boost::unordered_map<SpecimenSPtr, ClassSPtr> map;
    boost::unordered_map<SpecimenSPtr, ClassSPtr>::iterator it = map.find(specimen);
    if (it != map.end())
        return it->second;
        
    ClassNameSPtr name = className(specimen);
    
    ConstructorSPtr defaultConstructor = constructorRef()
        << EAccessSpecifier::public_()
        << name;
        
    PointerOperatorSPtr reference = referencePointerOperatorRef();

    ClassDeclarationSpecifierSPtr stdstring = classDeclarationSpecifierRef()
        << StlString::stringClass();
                    
    ArgumentNameDeclaratorSPtr argumentNameDeclarator = argumentNameDeclaratorRef()
        << "value";

    PointerDeclaratorSPtr pointerDeclarator = pointerDeclaratorRef()
        << reference
        << argumentNameDeclarator;
        
    DeclarationSpecifierSequenceSPtr declarationSpecifierSequence = declarationSpecifierSequenceRef()
        << (typeDeclarationSpecifierRef() << (cVQualifierTypeSpecifierRef() << ECVQualifier::const_()))
        << stdstring;
        
    DeclaratorParameterDeclarationSPtr declaratorParameterDeclaration = declaratorParameterDeclarationRef()
        << declarationSpecifierSequence
        << pointerDeclarator;

    ParameterDeclarationListSPtr list = parameterDeclarationListRef()
        << declaratorParameterDeclaration;

    ParameterDeclarationClauseSPtr clause = parameterDeclarationClauseRef()
        << list;

    ConstructorSPtr valueConstructor = constructorRef()
        << EAccessSpecifier::public_()
        << name
        << clause;

    DestructorSPtr destructor = destructorRef()
        << EAccessSpecifier::public_()
        << name;

    ClassSPtr class_ = classRef()
        << CppNamespace::namespace_(specimen->package())
        << EClassKey::class_()
        << name
        << defaultConstructor
        << valueConstructor
        << destructor;
        
    map[specimen] = class_;
    return class_;
}

}

}