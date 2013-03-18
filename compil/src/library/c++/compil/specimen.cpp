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
#include "library/c++/compil/declarator.h"
#include "library/c++/compil/type.h"
#include "library/c++/stl/string.h"

#include "language/c++/class/identifier_class_name.h"
#include "language/c++/class/identifier_method_name.h"
#include "language/c++/declarator/declarator_factory.h"
#include "language/c++/declaration/declaration_factory.h"
#include "language/c++/expression/expression_factory.h"
#include "language/c++/statement/statement_factory.h"
#include "language/c++/logical/argument_variable_name.h"

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

    ClassNameSPtr className = identifierClassNameRef()
        << (identifierRef() << specimen->name()->value());
    
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

    ClassSPtr class_ = classRef()
        << CppNamespace::namespace_(specimen->package())
        << EClassKey::class_()
        << name;

    class_
        << (constructorRef()
            << class_
            << EAccessSpecifier::public_()
            << name);

    ArgumentVariableNameSPtr valueArgumentName = argumentVariableNameRef()
        << "value";
        
    MemberVariableNameSPtr valueMemberName = memberVariableNameRef()
        << "value";

    DeclaratorParameterDeclarationSPtr declaratorParameterDeclaration =
        CppDeclarator::inputArgument(specimen->parameterType().lock(), valueArgumentName);

    class_
        << (constructorRef()
            << class_
            << EAccessSpecifier::public_()
            << EMethodSpecifier::explicit_()
            << name
            << (parameterDeclarationClauseRef()
                << (parameterDeclarationListRef()
                    << declaratorParameterDeclaration)));

    class_
        << (destructorRef()
            << class_
            << EAccessSpecifier::public_()
            << name);

    lang::cpp::MethodSPtr valueMethod =
        (lang::cpp::methodRef()
            << class_
            << EAccessSpecifier::public_()
            << EMethodSpecifier::inline_()
            << CppDeclarator::declarationSpecifier(specimen->parameterType().lock())
            << (identifierMethodNameRef()
                << (identifierRef() << "value"))
            << (cVQualifierSequenceRef()
                << ECVQualifier::const_())
            << (functionBodyRef()
                << (compoundStatementRef()
                    << (returnJumpStatementRef()
                        << (variableExpressionRef()
                            << valueMemberName)))));
    class_ << valueMethod;
            
    ArgumentVariableNameSPtr specimenArgumentName = argumentVariableNameRef()
        << "specimen";
        
    DeclaratorParameterDeclarationSPtr specimenDeclaratorParameterDeclaration =
        CppDeclarator::constReferenceArgument(class_, specimenArgumentName);

    GenericEqualityExpressionSPtr genericEqualityExpression = boost::make_shared<GenericEqualityExpression>();
    genericEqualityExpression->set_type(EqualityExpression::EType::equalTo());
    genericEqualityExpression->set_first(methodCallExpressionRef() << valueMethod->name());
    genericEqualityExpression->set_second(methodCallExpressionRef() << (variableExpressionRef() << specimenArgumentName)
                                                                    << valueMethod->name());

    class_ <<
        (lang::cpp::methodRef()
            << class_
            << EAccessSpecifier::public_()
            << EMethodSpecifier::inline_()
            << CppDeclaration::bool_()
            << (operatorMethodNameRef() << (operatorFunctionIdRef() << EOperator::equalTo()))
            << (parameterDeclarationClauseRef() << (parameterDeclarationListRef() << specimenDeclaratorParameterDeclaration))
            << (cVQualifierSequenceRef() << ECVQualifier::const_())
            << (functionBodyRef()
                << (compoundStatementRef()
                    << (returnJumpStatementRef()
                        << (genericEqualityExpression)))));
                        
    GenericEqualityExpressionSPtr genericEqualityExpressionNotEqual = boost::make_shared<GenericEqualityExpression>();
    genericEqualityExpressionNotEqual->set_type(EqualityExpression::EType::notEqualTo());
    genericEqualityExpressionNotEqual->set_first(methodCallExpressionRef() << valueMethod->name());
    genericEqualityExpressionNotEqual->set_second(methodCallExpressionRef() << (variableExpressionRef() << specimenArgumentName)
                                                                            << valueMethod->name());


    class_ <<
        (lang::cpp::methodRef()
            << class_
            << EAccessSpecifier::public_()
            << EMethodSpecifier::inline_()
            << CppDeclaration::bool_()
            << (operatorMethodNameRef() << (operatorFunctionIdRef() << EOperator::notEqualTo()))
            << (parameterDeclarationClauseRef() << (parameterDeclarationListRef() << specimenDeclaratorParameterDeclaration))
            << (cVQualifierSequenceRef() << ECVQualifier::const_())
            << (functionBodyRef()
                << (compoundStatementRef()
                    << (returnJumpStatementRef()
                        << (genericEqualityExpressionNotEqual)))));
        

    GenericRelationalExpressionSPtr genericRelationalExpression = boost::make_shared<GenericRelationalExpression>();
    genericRelationalExpression->set_type(RelationalExpression::EType::lessThan());
    genericRelationalExpression->set_first(methodCallExpressionRef() << valueMethod->name());
    genericRelationalExpression->set_second(methodCallExpressionRef() << (variableExpressionRef() << specimenArgumentName)
                                                                      << valueMethod->name());

    class_ <<
        (lang::cpp::methodRef()
            << class_
            << EAccessSpecifier::public_()
            << EMethodSpecifier::inline_()
            << CppDeclaration::bool_()
            << (operatorMethodNameRef() << (operatorFunctionIdRef() << EOperator::lessThan()))
            << (parameterDeclarationClauseRef() << (parameterDeclarationListRef() << specimenDeclaratorParameterDeclaration))
            << (cVQualifierSequenceRef() << ECVQualifier::const_())
            << (functionBodyRef()
                << (compoundStatementRef()
                    << (returnJumpStatementRef()
                        << (genericRelationalExpression)))));

    GenericAdditiveExpressionSPtr genericAdditiveExpression = boost::make_shared<GenericAdditiveExpression>();
    genericAdditiveExpression->set_type(AdditiveExpression::EType::addition());
    genericAdditiveExpression->set_first(methodCallExpressionRef() << valueMethod->name());
    genericAdditiveExpression->set_second(methodCallExpressionRef() << (variableExpressionRef() << specimenArgumentName)
                                                                    << valueMethod->name());

    class_ <<
        (lang::cpp::methodRef()
            << class_
            << EAccessSpecifier::public_()
            << EMethodSpecifier::inline_()
            << (classDeclarationSpecifierRef() << class_)
            << (operatorMethodNameRef() << (operatorFunctionIdRef() << EOperator::addition()))
            << (parameterDeclarationClauseRef() << (parameterDeclarationListRef() << specimenDeclaratorParameterDeclaration))
            << (cVQualifierSequenceRef() << ECVQualifier::const_())
            << (functionBodyRef()
                << (compoundStatementRef()
                    << (returnJumpStatementRef()
                        << (genericAdditiveExpression)))));
            
    class_ <<
        (lang::cpp::memberVariableRef()
            << class_
            << EAccessSpecifier::private_()
            << CppDeclarator::declarationSpecifier(specimen->parameterType().lock())
            << valueMemberName);

    map[specimen] = class_;
    return class_;
}

}

}