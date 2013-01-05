// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/member_access_postfix_expression.h"

namespace lang
{

namespace cpp
{

MemberAccessPostfixExpression::MemberAccessPostfixExpression()
{
}

MemberAccessPostfixExpression::~MemberAccessPostfixExpression()
{
}

MemberAccessPostfixExpressionSPtr MemberAccessPostfixExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<MemberAccessPostfixExpression>(object);
}

MemberAccessPostfixExpression::EOperator::EOperator()
        : mValue(kInvalid)
{
}

MemberAccessPostfixExpression::EOperator::EOperator(long value)
        : mValue(value)
{
}

const MemberAccessPostfixExpression::EOperator MemberAccessPostfixExpression::EOperator::invalid()
{
    return EOperator(kInvalid);
}

const MemberAccessPostfixExpression::EOperator MemberAccessPostfixExpression::EOperator::dot()
{
    return EOperator(kDot);
}

const MemberAccessPostfixExpression::EOperator MemberAccessPostfixExpression::EOperator::arrow()
{
    return EOperator(kArrow);
}

long MemberAccessPostfixExpression::EOperator::value() const
{
    return mValue;
}

const char* MemberAccessPostfixExpression::EOperator::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "dot",
        "arrow",
    };
    return names[(size_t)value];
}

const char* MemberAccessPostfixExpression::EOperator::shortName() const
{
    return shortName(value());
}

bool MemberAccessPostfixExpression::EOperator::operator==(const EOperator& rValue) const
{
    return mValue == rValue.mValue;
}

bool MemberAccessPostfixExpression::EOperator::operator!=(const EOperator& rValue) const
{
    return mValue != rValue.mValue;
}

const MemberAccessPostfixExpression::EOperator& MemberAccessPostfixExpression::operator_() const
{
    return mOperator;
}

MemberAccessPostfixExpression& MemberAccessPostfixExpression::set_operator(const EOperator& operator_)
{
    mOperator = operator_;
    return *this;
}

MemberAccessPostfixExpression::EOperator& MemberAccessPostfixExpression::mutable_operator()
{
    return mOperator;
}

MemberAccessPostfixExpression& MemberAccessPostfixExpression::operator<<(const EOperator& operator_)
{
    return set_operator(operator_);
}

const MemberAccessPostfixExpressionSPtr& operator<<(const MemberAccessPostfixExpressionSPtr& object,
                                                    const MemberAccessPostfixExpression::EOperator& operator_)
{
    BOOST_ASSERT(object);
    *object << operator_;
    return object;
}

const PostfixExpressionSPtr& MemberAccessPostfixExpression::first() const
{
    return mFirst;
}

MemberAccessPostfixExpression& MemberAccessPostfixExpression::set_first(const PostfixExpressionSPtr& first)
{
    mFirst = first;
    return *this;
}

MemberAccessPostfixExpression& MemberAccessPostfixExpression::operator<<(const PostfixExpressionSPtr& first)
{
    return set_first(first);
}

const MemberAccessPostfixExpressionSPtr& operator<<(const MemberAccessPostfixExpressionSPtr& object,
                                                    const PostfixExpressionSPtr& first)
{
    BOOST_ASSERT(object);
    *object << first;
    return object;
}

const IdExpressionSPtr& MemberAccessPostfixExpression::second() const
{
    return mSecond;
}

MemberAccessPostfixExpression& MemberAccessPostfixExpression::set_second(const IdExpressionSPtr& second)
{
    mSecond = second;
    return *this;
}

MemberAccessPostfixExpression& MemberAccessPostfixExpression::operator<<(const IdExpressionSPtr& second)
{
    return set_second(second);
}

const MemberAccessPostfixExpressionSPtr& operator<<(const MemberAccessPostfixExpressionSPtr& object,
                                                    const IdExpressionSPtr& second)
{
    BOOST_ASSERT(object);
    *object << second;
    return object;
}

}

}

