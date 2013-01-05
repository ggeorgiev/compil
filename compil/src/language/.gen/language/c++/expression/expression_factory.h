// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * The name of George Georgiev can not be used to endorse or
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

// Boost C++ Smart Pointers
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#ifndef __CPP_EXPRESSION_EXPRESSION_FACTORY_SCOMPIL_H_
#define __CPP_EXPRESSION_EXPRESSION_FACTORY_SCOMPIL_H_

#include "language/c++/expression/additive_expression.h"
#include "language/c++/expression/additive_shift_expression.h"
#include "language/c++/expression/cast_expression.h"
#include "language/c++/expression/cast_pm_expression.h"
#include "language/c++/expression/class_nested_name.h"
#include "language/c++/expression/constructor_call_expression.h"
#include "language/c++/expression/custom_expression.h"
#include "language/c++/expression/custom_id_expression.h"
#include "language/c++/expression/custom_postfix_expression.h"
#include "language/c++/expression/equality_expression.h"
#include "language/c++/expression/expression.h"
#include "language/c++/expression/expression_factory.h"
#include "language/c++/expression/expression_list.h"
#include "language/c++/expression/generic_equality_expression.h"
#include "language/c++/expression/grammar_equality_expression.h"
#include "language/c++/expression/id_expression.h"
#include "language/c++/expression/id_expression_primary_expression.h"
#include "language/c++/expression/identifier_unqualified_id.h"
#include "language/c++/expression/member_access_postfix_expression.h"
#include "language/c++/expression/method_call_expression.h"
#include "language/c++/expression/multiplicative_additive_expression.h"
#include "language/c++/expression/multiplicative_expression.h"
#include "language/c++/expression/namespace_nested_name.h"
#include "language/c++/expression/nested_name.h"
#include "language/c++/expression/nested_name_specifier.h"
#include "language/c++/expression/parentheses_postfix_expression.h"
#include "language/c++/expression/pm_expression.h"
#include "language/c++/expression/pm_multiplicative_expression.h"
#include "language/c++/expression/postfix_expression.h"
#include "language/c++/expression/postfix_unary_expression.h"
#include "language/c++/expression/primary_expression.h"
#include "language/c++/expression/primary_expression_postfix_expression.h"
#include "language/c++/expression/relational_equality_expression.h"
#include "language/c++/expression/relational_expression.h"
#include "language/c++/expression/shift_expression.h"
#include "language/c++/expression/shift_relational_expression.h"
#include "language/c++/expression/unary_cast_expression.h"
#include "language/c++/expression/unary_expression.h"
#include "language/c++/expression/unqualified_id.h"
#include "language/c++/expression/unqualified_id_expression.h"
#include "language/c++/expression/variable_expression.h"

namespace lang
{

namespace cpp
{

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EExpressionId
{
public:
    // Default constructor - sets the value to invalid
                         EExpressionId();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EExpressionId(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value        ()                            const;
    // Returns short name for a specified enum value
    static   const char* shortName    (long value);
    // Returns short name of the enum value
             const char* shortName    ()                            const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==   (const EExpressionId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=   (const EExpressionId& rValue) const;

    // static methods for enum class objects
    static const EExpressionId invalid                           ();
    static const EExpressionId additiveExpression                ();
    static const EExpressionId additiveShiftExpression           ();
    static const EExpressionId castExpression                    ();
    static const EExpressionId castPmExpression                  ();
    static const EExpressionId classNestedName                   ();
    static const EExpressionId constructorCallExpression         ();
    static const EExpressionId customExpression                  ();
    static const EExpressionId customIdExpression                ();
    static const EExpressionId customPostfixExpression           ();
    static const EExpressionId equalityExpression                ();
    static const EExpressionId expression                        ();
    static const EExpressionId expressionList                    ();
    static const EExpressionId genericEqualityExpression         ();
    static const EExpressionId grammarEqualityExpression         ();
    static const EExpressionId idExpression                      ();
    static const EExpressionId idExpressionPrimaryExpression     ();
    static const EExpressionId identifierUnqualifiedId           ();
    static const EExpressionId memberAccessPostfixExpression     ();
    static const EExpressionId methodCallExpression              ();
    static const EExpressionId multiplicativeAdditiveExpression  ();
    static const EExpressionId multiplicativeExpression          ();
    static const EExpressionId namespaceNestedName               ();
    static const EExpressionId nestedName                        ();
    static const EExpressionId nestedNameSpecifier               ();
    static const EExpressionId parenthesesPostfixExpression      ();
    static const EExpressionId pmExpression                      ();
    static const EExpressionId pmMultiplicativeExpression        ();
    static const EExpressionId postfixExpression                 ();
    static const EExpressionId postfixUnaryExpression            ();
    static const EExpressionId primaryExpression                 ();
    static const EExpressionId primaryExpressionPostfixExpression();
    static const EExpressionId relationalEqualityExpression      ();
    static const EExpressionId relationalExpression              ();
    static const EExpressionId shiftExpression                   ();
    static const EExpressionId shiftRelationalExpression         ();
    static const EExpressionId unaryCastExpression               ();
    static const EExpressionId unaryExpression                   ();
    static const EExpressionId unqualifiedId                     ();
    static const EExpressionId unqualifiedIdExpression           ();
    static const EExpressionId variableExpression                ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid                            = 0,
        kAdditiveExpression                 = 1,
        kAdditiveShiftExpression            = 2,
        kCastExpression                     = 3,
        kCastPmExpression                   = 4,
        kClassNestedName                    = 5,
        kConstructorCallExpression          = 6,
        kCustomExpression                   = 7,
        kCustomIdExpression                 = 8,
        kCustomPostfixExpression            = 9,
        kEqualityExpression                 = 10,
        kExpression                         = 11,
        kExpressionList                     = 12,
        kGenericEqualityExpression          = 13,
        kGrammarEqualityExpression          = 14,
        kIdExpression                       = 15,
        kIdExpressionPrimaryExpression      = 16,
        kIdentifierUnqualifiedId            = 17,
        kMemberAccessPostfixExpression      = 18,
        kMethodCallExpression               = 19,
        kMultiplicativeAdditiveExpression   = 20,
        kMultiplicativeExpression           = 21,
        kNamespaceNestedName                = 22,
        kNestedName                         = 23,
        kNestedNameSpecifier                = 24,
        kParenthesesPostfixExpression       = 25,
        kPmExpression                       = 26,
        kPmMultiplicativeExpression         = 27,
        kPostfixExpression                  = 28,
        kPostfixUnaryExpression             = 29,
        kPrimaryExpression                  = 30,
        kPrimaryExpressionPostfixExpression = 31,
        kRelationalEqualityExpression       = 32,
        kRelationalExpression               = 33,
        kShiftExpression                    = 34,
        kShiftRelationalExpression          = 35,
        kUnaryCastExpression                = 36,
        kUnaryExpression                    = 37,
        kUnqualifiedId                      = 38,
        kUnqualifiedIdExpression            = 39,
        kVariableExpression                 = 40,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class ExpressionFactory
{
public:
    static ExpressionSPtr                         clone                                     (const ExpressionSPtr& object);
    static AdditiveExpressionSPtr                 downcastAdditiveExpression                (const ExpressionSPtr& object);
    static AdditiveShiftExpressionSPtr            downcastAdditiveShiftExpression           (const ExpressionSPtr& object);
    static CastExpressionSPtr                     downcastCastExpression                    (const ExpressionSPtr& object);
    static CastPmExpressionSPtr                   downcastCastPmExpression                  (const ExpressionSPtr& object);
    static ClassNestedNameSPtr                    downcastClassNestedName                   (const ExpressionSPtr& object);
    static ConstructorCallExpressionSPtr          downcastConstructorCallExpression         (const ExpressionSPtr& object);
    static CustomExpressionSPtr                   downcastCustomExpression                  (const ExpressionSPtr& object);
    static CustomIdExpressionSPtr                 downcastCustomIdExpression                (const ExpressionSPtr& object);
    static CustomPostfixExpressionSPtr            downcastCustomPostfixExpression           (const ExpressionSPtr& object);
    static EqualityExpressionSPtr                 downcastEqualityExpression                (const ExpressionSPtr& object);
    static ExpressionListSPtr                     downcastExpressionList                    (const ExpressionSPtr& object);
    static GenericEqualityExpressionSPtr          downcastGenericEqualityExpression         (const ExpressionSPtr& object);
    static GrammarEqualityExpressionSPtr          downcastGrammarEqualityExpression         (const ExpressionSPtr& object);
    static IdExpressionSPtr                       downcastIdExpression                      (const ExpressionSPtr& object);
    static IdExpressionPrimaryExpressionSPtr      downcastIdExpressionPrimaryExpression     (const ExpressionSPtr& object);
    static IdentifierUnqualifiedIdSPtr            downcastIdentifierUnqualifiedId           (const ExpressionSPtr& object);
    static MemberAccessPostfixExpressionSPtr      downcastMemberAccessPostfixExpression     (const ExpressionSPtr& object);
    static MethodCallExpressionSPtr               downcastMethodCallExpression              (const ExpressionSPtr& object);
    static MultiplicativeAdditiveExpressionSPtr   downcastMultiplicativeAdditiveExpression  (const ExpressionSPtr& object);
    static MultiplicativeExpressionSPtr           downcastMultiplicativeExpression          (const ExpressionSPtr& object);
    static NamespaceNestedNameSPtr                downcastNamespaceNestedName               (const ExpressionSPtr& object);
    static NestedNameSPtr                         downcastNestedName                        (const ExpressionSPtr& object);
    static NestedNameSpecifierSPtr                downcastNestedNameSpecifier               (const ExpressionSPtr& object);
    static ParenthesesPostfixExpressionSPtr       downcastParenthesesPostfixExpression      (const ExpressionSPtr& object);
    static PmExpressionSPtr                       downcastPmExpression                      (const ExpressionSPtr& object);
    static PmMultiplicativeExpressionSPtr         downcastPmMultiplicativeExpression        (const ExpressionSPtr& object);
    static PostfixExpressionSPtr                  downcastPostfixExpression                 (const ExpressionSPtr& object);
    static PostfixUnaryExpressionSPtr             downcastPostfixUnaryExpression            (const ExpressionSPtr& object);
    static PrimaryExpressionSPtr                  downcastPrimaryExpression                 (const ExpressionSPtr& object);
    static PrimaryExpressionPostfixExpressionSPtr downcastPrimaryExpressionPostfixExpression(const ExpressionSPtr& object);
    static RelationalEqualityExpressionSPtr       downcastRelationalEqualityExpression      (const ExpressionSPtr& object);
    static RelationalExpressionSPtr               downcastRelationalExpression              (const ExpressionSPtr& object);
    static ShiftExpressionSPtr                    downcastShiftExpression                   (const ExpressionSPtr& object);
    static ShiftRelationalExpressionSPtr          downcastShiftRelationalExpression         (const ExpressionSPtr& object);
    static UnaryCastExpressionSPtr                downcastUnaryCastExpression               (const ExpressionSPtr& object);
    static UnaryExpressionSPtr                    downcastUnaryExpression                   (const ExpressionSPtr& object);
    static UnqualifiedIdSPtr                      downcastUnqualifiedId                     (const ExpressionSPtr& object);
    static UnqualifiedIdExpressionSPtr            downcastUnqualifiedIdExpression           (const ExpressionSPtr& object);
    static VariableExpressionSPtr                 downcastVariableExpression                (const ExpressionSPtr& object);
};

}

}

#else // __CPP_EXPRESSION_EXPRESSION_FACTORY_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class ExpressionFactory;
typedef ExpressionFactory*                         ExpressionFactoryRPtr;
typedef boost::shared_ptr<ExpressionFactory>       ExpressionFactorySPtr;
typedef boost::shared_ptr<const ExpressionFactory> ExpressionFactorySCPtr;
typedef boost::weak_ptr<ExpressionFactory>         ExpressionFactoryWPtr;

class EExpressionId;
typedef EExpressionId*                         EExpressionIdRPtr;
typedef boost::shared_ptr<EExpressionId>       EExpressionIdSPtr;
typedef boost::shared_ptr<const EExpressionId> EExpressionIdSCPtr;
typedef boost::weak_ptr<EExpressionId>         EExpressionIdWPtr;

class ExpressionFactory;

}

}

#endif // __CPP_EXPRESSION_EXPRESSION_FACTORY_SCOMPIL_H_

