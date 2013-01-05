// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/postfix_unary_expression.h"

namespace lang
{

namespace cpp
{

PostfixUnaryExpression::PostfixUnaryExpression()
{
}

PostfixUnaryExpression::~PostfixUnaryExpression()
{
}

PostfixUnaryExpressionSPtr PostfixUnaryExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<PostfixUnaryExpression>(object);
}

const PostfixExpressionSPtr& PostfixUnaryExpression::expression() const
{
    return mExpression;
}

PostfixUnaryExpression& PostfixUnaryExpression::set_expression(const PostfixExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

PostfixUnaryExpression& PostfixUnaryExpression::operator<<(const PostfixExpressionSPtr& expression)
{
    return set_expression(expression);
}

const PostfixUnaryExpressionSPtr& operator<<(const PostfixUnaryExpressionSPtr& object,
                                             const PostfixExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

