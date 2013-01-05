// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/expression_factory.h"

namespace lang
{

namespace cpp
{

EExpressionId::EExpressionId()
        : mValue(kInvalid)
{
}

EExpressionId::EExpressionId(long value)
        : mValue(value)
{
}

const EExpressionId EExpressionId::invalid()
{
    return EExpressionId(kInvalid);
}

const EExpressionId EExpressionId::additiveExpression()
{
    return EExpressionId(kAdditiveExpression);
}

const EExpressionId EExpressionId::additiveShiftExpression()
{
    return EExpressionId(kAdditiveShiftExpression);
}

const EExpressionId EExpressionId::castExpression()
{
    return EExpressionId(kCastExpression);
}

const EExpressionId EExpressionId::castPmExpression()
{
    return EExpressionId(kCastPmExpression);
}

const EExpressionId EExpressionId::classNestedName()
{
    return EExpressionId(kClassNestedName);
}

const EExpressionId EExpressionId::constructorCallExpression()
{
    return EExpressionId(kConstructorCallExpression);
}

const EExpressionId EExpressionId::customExpression()
{
    return EExpressionId(kCustomExpression);
}

const EExpressionId EExpressionId::customIdExpression()
{
    return EExpressionId(kCustomIdExpression);
}

const EExpressionId EExpressionId::customPostfixExpression()
{
    return EExpressionId(kCustomPostfixExpression);
}

const EExpressionId EExpressionId::equalityExpression()
{
    return EExpressionId(kEqualityExpression);
}

const EExpressionId EExpressionId::expression()
{
    return EExpressionId(kExpression);
}

const EExpressionId EExpressionId::expressionList()
{
    return EExpressionId(kExpressionList);
}

const EExpressionId EExpressionId::genericEqualityExpression()
{
    return EExpressionId(kGenericEqualityExpression);
}

const EExpressionId EExpressionId::grammarEqualityExpression()
{
    return EExpressionId(kGrammarEqualityExpression);
}

const EExpressionId EExpressionId::idExpression()
{
    return EExpressionId(kIdExpression);
}

const EExpressionId EExpressionId::idExpressionPrimaryExpression()
{
    return EExpressionId(kIdExpressionPrimaryExpression);
}

const EExpressionId EExpressionId::identifierUnqualifiedId()
{
    return EExpressionId(kIdentifierUnqualifiedId);
}

const EExpressionId EExpressionId::memberAccessPostfixExpression()
{
    return EExpressionId(kMemberAccessPostfixExpression);
}

const EExpressionId EExpressionId::methodCallExpression()
{
    return EExpressionId(kMethodCallExpression);
}

const EExpressionId EExpressionId::multiplicativeAdditiveExpression()
{
    return EExpressionId(kMultiplicativeAdditiveExpression);
}

const EExpressionId EExpressionId::multiplicativeExpression()
{
    return EExpressionId(kMultiplicativeExpression);
}

const EExpressionId EExpressionId::namespaceNestedName()
{
    return EExpressionId(kNamespaceNestedName);
}

const EExpressionId EExpressionId::nestedName()
{
    return EExpressionId(kNestedName);
}

const EExpressionId EExpressionId::nestedNameSpecifier()
{
    return EExpressionId(kNestedNameSpecifier);
}

const EExpressionId EExpressionId::parenthesesPostfixExpression()
{
    return EExpressionId(kParenthesesPostfixExpression);
}

const EExpressionId EExpressionId::pmExpression()
{
    return EExpressionId(kPmExpression);
}

const EExpressionId EExpressionId::pmMultiplicativeExpression()
{
    return EExpressionId(kPmMultiplicativeExpression);
}

const EExpressionId EExpressionId::postfixExpression()
{
    return EExpressionId(kPostfixExpression);
}

const EExpressionId EExpressionId::postfixUnaryExpression()
{
    return EExpressionId(kPostfixUnaryExpression);
}

const EExpressionId EExpressionId::primaryExpression()
{
    return EExpressionId(kPrimaryExpression);
}

const EExpressionId EExpressionId::primaryExpressionPostfixExpression()
{
    return EExpressionId(kPrimaryExpressionPostfixExpression);
}

const EExpressionId EExpressionId::relationalEqualityExpression()
{
    return EExpressionId(kRelationalEqualityExpression);
}

const EExpressionId EExpressionId::relationalExpression()
{
    return EExpressionId(kRelationalExpression);
}

const EExpressionId EExpressionId::shiftExpression()
{
    return EExpressionId(kShiftExpression);
}

const EExpressionId EExpressionId::shiftRelationalExpression()
{
    return EExpressionId(kShiftRelationalExpression);
}

const EExpressionId EExpressionId::unaryCastExpression()
{
    return EExpressionId(kUnaryCastExpression);
}

const EExpressionId EExpressionId::unaryExpression()
{
    return EExpressionId(kUnaryExpression);
}

const EExpressionId EExpressionId::unqualifiedId()
{
    return EExpressionId(kUnqualifiedId);
}

const EExpressionId EExpressionId::unqualifiedIdExpression()
{
    return EExpressionId(kUnqualifiedIdExpression);
}

const EExpressionId EExpressionId::variableExpression()
{
    return EExpressionId(kVariableExpression);
}

long EExpressionId::value() const
{
    return mValue;
}

const char* EExpressionId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "AdditiveExpression",
        "AdditiveShiftExpression",
        "CastExpression",
        "CastPmExpression",
        "ClassNestedName",
        "ConstructorCallExpression",
        "CustomExpression",
        "CustomIdExpression",
        "CustomPostfixExpression",
        "EqualityExpression",
        "Expression",
        "ExpressionList",
        "GenericEqualityExpression",
        "GrammarEqualityExpression",
        "IdExpression",
        "IdExpressionPrimaryExpression",
        "IdentifierUnqualifiedId",
        "MemberAccessPostfixExpression",
        "MethodCallExpression",
        "MultiplicativeAdditiveExpression",
        "MultiplicativeExpression",
        "NamespaceNestedName",
        "NestedName",
        "NestedNameSpecifier",
        "ParenthesesPostfixExpression",
        "PmExpression",
        "PmMultiplicativeExpression",
        "PostfixExpression",
        "PostfixUnaryExpression",
        "PrimaryExpression",
        "PrimaryExpressionPostfixExpression",
        "RelationalEqualityExpression",
        "RelationalExpression",
        "ShiftExpression",
        "ShiftRelationalExpression",
        "UnaryCastExpression",
        "UnaryExpression",
        "UnqualifiedId",
        "UnqualifiedIdExpression",
        "VariableExpression",
    };
    return names[(size_t)value];
}

const char* EExpressionId::shortName() const
{
    return shortName(value());
}

bool EExpressionId::operator==(const EExpressionId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EExpressionId::operator!=(const EExpressionId& rValue) const
{
    return mValue != rValue.mValue;
}

EExpressionId AdditiveExpression::staticExpressionId()
{
    return EExpressionId::additiveExpression();
}

EExpressionId AdditiveExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId AdditiveShiftExpression::staticExpressionId()
{
    return EExpressionId::additiveShiftExpression();
}

EExpressionId AdditiveShiftExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId CastExpression::staticExpressionId()
{
    return EExpressionId::castExpression();
}

EExpressionId CastExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId CastPmExpression::staticExpressionId()
{
    return EExpressionId::castPmExpression();
}

EExpressionId CastPmExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId ClassNestedName::staticExpressionId()
{
    return EExpressionId::classNestedName();
}

EExpressionId ClassNestedName::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId ConstructorCallExpression::staticExpressionId()
{
    return EExpressionId::constructorCallExpression();
}

EExpressionId ConstructorCallExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId CustomExpression::staticExpressionId()
{
    return EExpressionId::customExpression();
}

EExpressionId CustomExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId CustomIdExpression::staticExpressionId()
{
    return EExpressionId::customIdExpression();
}

EExpressionId CustomIdExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId CustomPostfixExpression::staticExpressionId()
{
    return EExpressionId::customPostfixExpression();
}

EExpressionId CustomPostfixExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId EqualityExpression::staticExpressionId()
{
    return EExpressionId::equalityExpression();
}

EExpressionId EqualityExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId Expression::staticExpressionId()
{
    return EExpressionId::expression();
}

EExpressionId Expression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId ExpressionList::staticExpressionId()
{
    return EExpressionId::expressionList();
}

EExpressionId ExpressionList::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId GenericEqualityExpression::staticExpressionId()
{
    return EExpressionId::genericEqualityExpression();
}

EExpressionId GenericEqualityExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId GrammarEqualityExpression::staticExpressionId()
{
    return EExpressionId::grammarEqualityExpression();
}

EExpressionId GrammarEqualityExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId IdExpression::staticExpressionId()
{
    return EExpressionId::idExpression();
}

EExpressionId IdExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId IdExpressionPrimaryExpression::staticExpressionId()
{
    return EExpressionId::idExpressionPrimaryExpression();
}

EExpressionId IdExpressionPrimaryExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId IdentifierUnqualifiedId::staticExpressionId()
{
    return EExpressionId::identifierUnqualifiedId();
}

EExpressionId IdentifierUnqualifiedId::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId MemberAccessPostfixExpression::staticExpressionId()
{
    return EExpressionId::memberAccessPostfixExpression();
}

EExpressionId MemberAccessPostfixExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId MethodCallExpression::staticExpressionId()
{
    return EExpressionId::methodCallExpression();
}

EExpressionId MethodCallExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId MultiplicativeAdditiveExpression::staticExpressionId()
{
    return EExpressionId::multiplicativeAdditiveExpression();
}

EExpressionId MultiplicativeAdditiveExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId MultiplicativeExpression::staticExpressionId()
{
    return EExpressionId::multiplicativeExpression();
}

EExpressionId MultiplicativeExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId NamespaceNestedName::staticExpressionId()
{
    return EExpressionId::namespaceNestedName();
}

EExpressionId NamespaceNestedName::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId NestedName::staticExpressionId()
{
    return EExpressionId::nestedName();
}

EExpressionId NestedName::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId NestedNameSpecifier::staticExpressionId()
{
    return EExpressionId::nestedNameSpecifier();
}

EExpressionId NestedNameSpecifier::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId ParenthesesPostfixExpression::staticExpressionId()
{
    return EExpressionId::parenthesesPostfixExpression();
}

EExpressionId ParenthesesPostfixExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId PmExpression::staticExpressionId()
{
    return EExpressionId::pmExpression();
}

EExpressionId PmExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId PmMultiplicativeExpression::staticExpressionId()
{
    return EExpressionId::pmMultiplicativeExpression();
}

EExpressionId PmMultiplicativeExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId PostfixExpression::staticExpressionId()
{
    return EExpressionId::postfixExpression();
}

EExpressionId PostfixExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId PostfixUnaryExpression::staticExpressionId()
{
    return EExpressionId::postfixUnaryExpression();
}

EExpressionId PostfixUnaryExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId PrimaryExpression::staticExpressionId()
{
    return EExpressionId::primaryExpression();
}

EExpressionId PrimaryExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId PrimaryExpressionPostfixExpression::staticExpressionId()
{
    return EExpressionId::primaryExpressionPostfixExpression();
}

EExpressionId PrimaryExpressionPostfixExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId RelationalEqualityExpression::staticExpressionId()
{
    return EExpressionId::relationalEqualityExpression();
}

EExpressionId RelationalEqualityExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId RelationalExpression::staticExpressionId()
{
    return EExpressionId::relationalExpression();
}

EExpressionId RelationalExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId ShiftExpression::staticExpressionId()
{
    return EExpressionId::shiftExpression();
}

EExpressionId ShiftExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId ShiftRelationalExpression::staticExpressionId()
{
    return EExpressionId::shiftRelationalExpression();
}

EExpressionId ShiftRelationalExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId UnaryCastExpression::staticExpressionId()
{
    return EExpressionId::unaryCastExpression();
}

EExpressionId UnaryCastExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId UnaryExpression::staticExpressionId()
{
    return EExpressionId::unaryExpression();
}

EExpressionId UnaryExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId UnqualifiedId::staticExpressionId()
{
    return EExpressionId::unqualifiedId();
}

EExpressionId UnqualifiedId::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId UnqualifiedIdExpression::staticExpressionId()
{
    return EExpressionId::unqualifiedIdExpression();
}

EExpressionId UnqualifiedIdExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

EExpressionId VariableExpression::staticExpressionId()
{
    return EExpressionId::variableExpression();
}

EExpressionId VariableExpression::runtimeExpressionId() const
{
    return staticExpressionId();
}

ExpressionSPtr ExpressionFactory::clone(const ExpressionSPtr& pObject)
{
    switch (pObject->runtimeExpressionId().value())
    {
        case EExpressionId::kAdditiveExpression:
        {
            AdditiveExpressionSPtr pClone(new AdditiveExpression());
            *pClone = *downcastAdditiveExpression(pObject);
            return pClone;
        }
        case EExpressionId::kAdditiveShiftExpression:
        {
            AdditiveShiftExpressionSPtr pClone(new AdditiveShiftExpression());
            *pClone = *downcastAdditiveShiftExpression(pObject);
            return pClone;
        }
        case EExpressionId::kCastExpression:
        {
            CastExpressionSPtr pClone(new CastExpression());
            *pClone = *downcastCastExpression(pObject);
            return pClone;
        }
        case EExpressionId::kCastPmExpression:
        {
            CastPmExpressionSPtr pClone(new CastPmExpression());
            *pClone = *downcastCastPmExpression(pObject);
            return pClone;
        }
        case EExpressionId::kClassNestedName:
        {
            ClassNestedNameSPtr pClone(new ClassNestedName());
            *pClone = *downcastClassNestedName(pObject);
            return pClone;
        }
        case EExpressionId::kConstructorCallExpression:
        {
            ConstructorCallExpressionSPtr pClone(new ConstructorCallExpression());
            *pClone = *downcastConstructorCallExpression(pObject);
            return pClone;
        }
        case EExpressionId::kCustomExpression:
        {
            CustomExpressionSPtr pClone(new CustomExpression());
            *pClone = *downcastCustomExpression(pObject);
            return pClone;
        }
        case EExpressionId::kCustomIdExpression:
        {
            CustomIdExpressionSPtr pClone(new CustomIdExpression());
            *pClone = *downcastCustomIdExpression(pObject);
            return pClone;
        }
        case EExpressionId::kCustomPostfixExpression:
        {
            CustomPostfixExpressionSPtr pClone(new CustomPostfixExpression());
            *pClone = *downcastCustomPostfixExpression(pObject);
            return pClone;
        }
        case EExpressionId::kEqualityExpression:
        {
            EqualityExpressionSPtr pClone(new EqualityExpression());
            *pClone = *downcastEqualityExpression(pObject);
            return pClone;
        }
        case EExpressionId::kExpression:
        {
            ExpressionSPtr pClone(new Expression());
            *pClone = *pObject;
            return pClone;
        }
        case EExpressionId::kExpressionList:
        {
            ExpressionListSPtr pClone(new ExpressionList());
            *pClone = *downcastExpressionList(pObject);
            return pClone;
        }
        case EExpressionId::kGenericEqualityExpression:
        {
            GenericEqualityExpressionSPtr pClone(new GenericEqualityExpression());
            *pClone = *downcastGenericEqualityExpression(pObject);
            return pClone;
        }
        case EExpressionId::kGrammarEqualityExpression:
        {
            GrammarEqualityExpressionSPtr pClone(new GrammarEqualityExpression());
            *pClone = *downcastGrammarEqualityExpression(pObject);
            return pClone;
        }
        case EExpressionId::kIdExpression:
        {
            IdExpressionSPtr pClone(new IdExpression());
            *pClone = *downcastIdExpression(pObject);
            return pClone;
        }
        case EExpressionId::kIdExpressionPrimaryExpression:
        {
            IdExpressionPrimaryExpressionSPtr pClone(new IdExpressionPrimaryExpression());
            *pClone = *downcastIdExpressionPrimaryExpression(pObject);
            return pClone;
        }
        case EExpressionId::kIdentifierUnqualifiedId:
        {
            IdentifierUnqualifiedIdSPtr pClone(new IdentifierUnqualifiedId());
            *pClone = *downcastIdentifierUnqualifiedId(pObject);
            return pClone;
        }
        case EExpressionId::kMemberAccessPostfixExpression:
        {
            MemberAccessPostfixExpressionSPtr pClone(new MemberAccessPostfixExpression());
            *pClone = *downcastMemberAccessPostfixExpression(pObject);
            return pClone;
        }
        case EExpressionId::kMethodCallExpression:
        {
            MethodCallExpressionSPtr pClone(new MethodCallExpression());
            *pClone = *downcastMethodCallExpression(pObject);
            return pClone;
        }
        case EExpressionId::kMultiplicativeAdditiveExpression:
        {
            MultiplicativeAdditiveExpressionSPtr pClone(new MultiplicativeAdditiveExpression());
            *pClone = *downcastMultiplicativeAdditiveExpression(pObject);
            return pClone;
        }
        case EExpressionId::kMultiplicativeExpression:
        {
            MultiplicativeExpressionSPtr pClone(new MultiplicativeExpression());
            *pClone = *downcastMultiplicativeExpression(pObject);
            return pClone;
        }
        case EExpressionId::kNamespaceNestedName:
        {
            NamespaceNestedNameSPtr pClone(new NamespaceNestedName());
            *pClone = *downcastNamespaceNestedName(pObject);
            return pClone;
        }
        case EExpressionId::kNestedName:
        {
            NestedNameSPtr pClone(new NestedName());
            *pClone = *downcastNestedName(pObject);
            return pClone;
        }
        case EExpressionId::kNestedNameSpecifier:
        {
            NestedNameSpecifierSPtr pClone(new NestedNameSpecifier());
            *pClone = *downcastNestedNameSpecifier(pObject);
            return pClone;
        }
        case EExpressionId::kParenthesesPostfixExpression:
        {
            ParenthesesPostfixExpressionSPtr pClone(new ParenthesesPostfixExpression());
            *pClone = *downcastParenthesesPostfixExpression(pObject);
            return pClone;
        }
        case EExpressionId::kPmExpression:
        {
            PmExpressionSPtr pClone(new PmExpression());
            *pClone = *downcastPmExpression(pObject);
            return pClone;
        }
        case EExpressionId::kPmMultiplicativeExpression:
        {
            PmMultiplicativeExpressionSPtr pClone(new PmMultiplicativeExpression());
            *pClone = *downcastPmMultiplicativeExpression(pObject);
            return pClone;
        }
        case EExpressionId::kPostfixExpression:
        {
            PostfixExpressionSPtr pClone(new PostfixExpression());
            *pClone = *downcastPostfixExpression(pObject);
            return pClone;
        }
        case EExpressionId::kPostfixUnaryExpression:
        {
            PostfixUnaryExpressionSPtr pClone(new PostfixUnaryExpression());
            *pClone = *downcastPostfixUnaryExpression(pObject);
            return pClone;
        }
        case EExpressionId::kPrimaryExpression:
        {
            PrimaryExpressionSPtr pClone(new PrimaryExpression());
            *pClone = *downcastPrimaryExpression(pObject);
            return pClone;
        }
        case EExpressionId::kPrimaryExpressionPostfixExpression:
        {
            PrimaryExpressionPostfixExpressionSPtr pClone(new PrimaryExpressionPostfixExpression());
            *pClone = *downcastPrimaryExpressionPostfixExpression(pObject);
            return pClone;
        }
        case EExpressionId::kRelationalEqualityExpression:
        {
            RelationalEqualityExpressionSPtr pClone(new RelationalEqualityExpression());
            *pClone = *downcastRelationalEqualityExpression(pObject);
            return pClone;
        }
        case EExpressionId::kRelationalExpression:
        {
            RelationalExpressionSPtr pClone(new RelationalExpression());
            *pClone = *downcastRelationalExpression(pObject);
            return pClone;
        }
        case EExpressionId::kShiftExpression:
        {
            ShiftExpressionSPtr pClone(new ShiftExpression());
            *pClone = *downcastShiftExpression(pObject);
            return pClone;
        }
        case EExpressionId::kShiftRelationalExpression:
        {
            ShiftRelationalExpressionSPtr pClone(new ShiftRelationalExpression());
            *pClone = *downcastShiftRelationalExpression(pObject);
            return pClone;
        }
        case EExpressionId::kUnaryCastExpression:
        {
            UnaryCastExpressionSPtr pClone(new UnaryCastExpression());
            *pClone = *downcastUnaryCastExpression(pObject);
            return pClone;
        }
        case EExpressionId::kUnaryExpression:
        {
            UnaryExpressionSPtr pClone(new UnaryExpression());
            *pClone = *downcastUnaryExpression(pObject);
            return pClone;
        }
        case EExpressionId::kUnqualifiedId:
        {
            UnqualifiedIdSPtr pClone(new UnqualifiedId());
            *pClone = *downcastUnqualifiedId(pObject);
            return pClone;
        }
        case EExpressionId::kUnqualifiedIdExpression:
        {
            UnqualifiedIdExpressionSPtr pClone(new UnqualifiedIdExpression());
            *pClone = *downcastUnqualifiedIdExpression(pObject);
            return pClone;
        }
        case EExpressionId::kVariableExpression:
        {
            VariableExpressionSPtr pClone(new VariableExpression());
            *pClone = *downcastVariableExpression(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return ExpressionSPtr();
}

AdditiveExpressionSPtr ExpressionFactory::downcastAdditiveExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == AdditiveExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == MultiplicativeAdditiveExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<AdditiveExpression>(pObject);
    return AdditiveExpressionSPtr();
}

AdditiveShiftExpressionSPtr ExpressionFactory::downcastAdditiveShiftExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == AdditiveShiftExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<AdditiveShiftExpression>(pObject);
    return AdditiveShiftExpressionSPtr();
}

CastExpressionSPtr ExpressionFactory::downcastCastExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == CastExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == UnaryCastExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<CastExpression>(pObject);
    return CastExpressionSPtr();
}

CastPmExpressionSPtr ExpressionFactory::downcastCastPmExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == CastPmExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<CastPmExpression>(pObject);
    return CastPmExpressionSPtr();
}

ClassNestedNameSPtr ExpressionFactory::downcastClassNestedName(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == ClassNestedName::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<ClassNestedName>(pObject);
    return ClassNestedNameSPtr();
}

ConstructorCallExpressionSPtr ExpressionFactory::downcastConstructorCallExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == ConstructorCallExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<ConstructorCallExpression>(pObject);
    return ConstructorCallExpressionSPtr();
}

CustomExpressionSPtr ExpressionFactory::downcastCustomExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == CustomExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<CustomExpression>(pObject);
    return CustomExpressionSPtr();
}

CustomIdExpressionSPtr ExpressionFactory::downcastCustomIdExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == CustomIdExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<CustomIdExpression>(pObject);
    return CustomIdExpressionSPtr();
}

CustomPostfixExpressionSPtr ExpressionFactory::downcastCustomPostfixExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == CustomPostfixExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<CustomPostfixExpression>(pObject);
    return CustomPostfixExpressionSPtr();
}

EqualityExpressionSPtr ExpressionFactory::downcastEqualityExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == EqualityExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == GenericEqualityExpression::staticExpressionId())
          || (pObject->runtimeExpressionId() == GrammarEqualityExpression::staticExpressionId())
          || (pObject->runtimeExpressionId() == RelationalEqualityExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<EqualityExpression>(pObject);
    return EqualityExpressionSPtr();
}

ExpressionListSPtr ExpressionFactory::downcastExpressionList(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == ExpressionList::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<ExpressionList>(pObject);
    return ExpressionListSPtr();
}

GenericEqualityExpressionSPtr ExpressionFactory::downcastGenericEqualityExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == GenericEqualityExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<GenericEqualityExpression>(pObject);
    return GenericEqualityExpressionSPtr();
}

GrammarEqualityExpressionSPtr ExpressionFactory::downcastGrammarEqualityExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == GrammarEqualityExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<GrammarEqualityExpression>(pObject);
    return GrammarEqualityExpressionSPtr();
}

IdExpressionSPtr ExpressionFactory::downcastIdExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == IdExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == CustomIdExpression::staticExpressionId())
          || (pObject->runtimeExpressionId() == UnqualifiedIdExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<IdExpression>(pObject);
    return IdExpressionSPtr();
}

IdExpressionPrimaryExpressionSPtr ExpressionFactory::downcastIdExpressionPrimaryExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == IdExpressionPrimaryExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<IdExpressionPrimaryExpression>(pObject);
    return IdExpressionPrimaryExpressionSPtr();
}

IdentifierUnqualifiedIdSPtr ExpressionFactory::downcastIdentifierUnqualifiedId(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == IdentifierUnqualifiedId::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<IdentifierUnqualifiedId>(pObject);
    return IdentifierUnqualifiedIdSPtr();
}

MemberAccessPostfixExpressionSPtr ExpressionFactory::downcastMemberAccessPostfixExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == MemberAccessPostfixExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<MemberAccessPostfixExpression>(pObject);
    return MemberAccessPostfixExpressionSPtr();
}

MethodCallExpressionSPtr ExpressionFactory::downcastMethodCallExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == MethodCallExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<MethodCallExpression>(pObject);
    return MethodCallExpressionSPtr();
}

MultiplicativeAdditiveExpressionSPtr ExpressionFactory::downcastMultiplicativeAdditiveExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == MultiplicativeAdditiveExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<MultiplicativeAdditiveExpression>(pObject);
    return MultiplicativeAdditiveExpressionSPtr();
}

MultiplicativeExpressionSPtr ExpressionFactory::downcastMultiplicativeExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == MultiplicativeExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == PmMultiplicativeExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<MultiplicativeExpression>(pObject);
    return MultiplicativeExpressionSPtr();
}

NamespaceNestedNameSPtr ExpressionFactory::downcastNamespaceNestedName(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == NamespaceNestedName::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<NamespaceNestedName>(pObject);
    return NamespaceNestedNameSPtr();
}

NestedNameSPtr ExpressionFactory::downcastNestedName(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == NestedName::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == ClassNestedName::staticExpressionId())
          || (pObject->runtimeExpressionId() == NamespaceNestedName::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<NestedName>(pObject);
    return NestedNameSPtr();
}

NestedNameSpecifierSPtr ExpressionFactory::downcastNestedNameSpecifier(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == NestedNameSpecifier::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<NestedNameSpecifier>(pObject);
    return NestedNameSpecifierSPtr();
}

ParenthesesPostfixExpressionSPtr ExpressionFactory::downcastParenthesesPostfixExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == ParenthesesPostfixExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<ParenthesesPostfixExpression>(pObject);
    return ParenthesesPostfixExpressionSPtr();
}

PmExpressionSPtr ExpressionFactory::downcastPmExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == PmExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == CastPmExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<PmExpression>(pObject);
    return PmExpressionSPtr();
}

PmMultiplicativeExpressionSPtr ExpressionFactory::downcastPmMultiplicativeExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == PmMultiplicativeExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<PmMultiplicativeExpression>(pObject);
    return PmMultiplicativeExpressionSPtr();
}

PostfixExpressionSPtr ExpressionFactory::downcastPostfixExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == PostfixExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == CustomPostfixExpression::staticExpressionId())
          || (pObject->runtimeExpressionId() == MemberAccessPostfixExpression::staticExpressionId())
          || (pObject->runtimeExpressionId() == ParenthesesPostfixExpression::staticExpressionId())
          || (pObject->runtimeExpressionId() == PrimaryExpressionPostfixExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<PostfixExpression>(pObject);
    return PostfixExpressionSPtr();
}

PostfixUnaryExpressionSPtr ExpressionFactory::downcastPostfixUnaryExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == PostfixUnaryExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<PostfixUnaryExpression>(pObject);
    return PostfixUnaryExpressionSPtr();
}

PrimaryExpressionSPtr ExpressionFactory::downcastPrimaryExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == PrimaryExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == IdExpressionPrimaryExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<PrimaryExpression>(pObject);
    return PrimaryExpressionSPtr();
}

PrimaryExpressionPostfixExpressionSPtr ExpressionFactory::downcastPrimaryExpressionPostfixExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == PrimaryExpressionPostfixExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<PrimaryExpressionPostfixExpression>(pObject);
    return PrimaryExpressionPostfixExpressionSPtr();
}

RelationalEqualityExpressionSPtr ExpressionFactory::downcastRelationalEqualityExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == RelationalEqualityExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<RelationalEqualityExpression>(pObject);
    return RelationalEqualityExpressionSPtr();
}

RelationalExpressionSPtr ExpressionFactory::downcastRelationalExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == RelationalExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == ShiftRelationalExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<RelationalExpression>(pObject);
    return RelationalExpressionSPtr();
}

ShiftExpressionSPtr ExpressionFactory::downcastShiftExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == ShiftExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == AdditiveShiftExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<ShiftExpression>(pObject);
    return ShiftExpressionSPtr();
}

ShiftRelationalExpressionSPtr ExpressionFactory::downcastShiftRelationalExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == ShiftRelationalExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<ShiftRelationalExpression>(pObject);
    return ShiftRelationalExpressionSPtr();
}

UnaryCastExpressionSPtr ExpressionFactory::downcastUnaryCastExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == UnaryCastExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<UnaryCastExpression>(pObject);
    return UnaryCastExpressionSPtr();
}

UnaryExpressionSPtr ExpressionFactory::downcastUnaryExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == UnaryExpression::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == PostfixUnaryExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<UnaryExpression>(pObject);
    return UnaryExpressionSPtr();
}

UnqualifiedIdSPtr ExpressionFactory::downcastUnqualifiedId(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == UnqualifiedId::staticExpressionId())
          // or any of the derived classes
          || (pObject->runtimeExpressionId() == IdentifierUnqualifiedId::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<UnqualifiedId>(pObject);
    return UnqualifiedIdSPtr();
}

UnqualifiedIdExpressionSPtr ExpressionFactory::downcastUnqualifiedIdExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == UnqualifiedIdExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<UnqualifiedIdExpression>(pObject);
    return UnqualifiedIdExpressionSPtr();
}

VariableExpressionSPtr ExpressionFactory::downcastVariableExpression(const ExpressionSPtr& pObject)
{
    bool b = (pObject->runtimeExpressionId() == VariableExpression::staticExpressionId());

    if (b)
        return boost::static_pointer_cast<VariableExpression>(pObject);
    return VariableExpressionSPtr();
}

}

}

