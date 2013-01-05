// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/primary_expression_postfix_expression.h"

namespace lang
{

namespace cpp
{

PrimaryExpressionPostfixExpression::PrimaryExpressionPostfixExpression()
{
}

PrimaryExpressionPostfixExpression::~PrimaryExpressionPostfixExpression()
{
}

PrimaryExpressionPostfixExpressionSPtr PrimaryExpressionPostfixExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<PrimaryExpressionPostfixExpression>(object);
}

const PrimaryExpressionSPtr& PrimaryExpressionPostfixExpression::expression() const
{
    return mExpression;
}

PrimaryExpressionPostfixExpression& PrimaryExpressionPostfixExpression::set_expression(const PrimaryExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

PrimaryExpressionPostfixExpression& PrimaryExpressionPostfixExpression::operator<<(const PrimaryExpressionSPtr& expression)
{
    return set_expression(expression);
}

const PrimaryExpressionPostfixExpressionSPtr& operator<<(const PrimaryExpressionPostfixExpressionSPtr& object,
                                                         const PrimaryExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

