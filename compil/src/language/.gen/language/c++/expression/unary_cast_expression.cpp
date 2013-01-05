// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/unary_cast_expression.h"

namespace lang
{

namespace cpp
{

UnaryCastExpression::UnaryCastExpression()
{
}

UnaryCastExpression::~UnaryCastExpression()
{
}

UnaryCastExpressionSPtr UnaryCastExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<UnaryCastExpression>(object);
}

const UnaryExpressionSPtr& UnaryCastExpression::expression() const
{
    return mExpression;
}

UnaryCastExpression& UnaryCastExpression::set_expression(const UnaryExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

UnaryCastExpression& UnaryCastExpression::operator<<(const UnaryExpressionSPtr& expression)
{
    return set_expression(expression);
}

const UnaryCastExpressionSPtr& operator<<(const UnaryCastExpressionSPtr& object, const UnaryExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

