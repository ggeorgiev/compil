// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/multiplicative_additive_expression.h"

namespace lang
{

namespace cpp
{

MultiplicativeAdditiveExpression::MultiplicativeAdditiveExpression()
{
}

MultiplicativeAdditiveExpression::~MultiplicativeAdditiveExpression()
{
}

MultiplicativeAdditiveExpressionSPtr MultiplicativeAdditiveExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<MultiplicativeAdditiveExpression>(object);
}

const MultiplicativeExpressionSPtr& MultiplicativeAdditiveExpression::expression() const
{
    return mExpression;
}

MultiplicativeAdditiveExpression& MultiplicativeAdditiveExpression::set_expression(const MultiplicativeExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

MultiplicativeAdditiveExpression& MultiplicativeAdditiveExpression::operator<<(const MultiplicativeExpressionSPtr& expression)
{
    return set_expression(expression);
}

const MultiplicativeAdditiveExpressionSPtr& operator<<(const MultiplicativeAdditiveExpressionSPtr& object,
                                                       const MultiplicativeExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

