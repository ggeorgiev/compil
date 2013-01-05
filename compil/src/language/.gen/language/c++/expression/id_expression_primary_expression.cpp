// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/id_expression_primary_expression.h"

namespace lang
{

namespace cpp
{

IdExpressionPrimaryExpression::IdExpressionPrimaryExpression()
{
}

IdExpressionPrimaryExpression::~IdExpressionPrimaryExpression()
{
}

IdExpressionPrimaryExpressionSPtr IdExpressionPrimaryExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<IdExpressionPrimaryExpression>(object);
}

const IdExpressionSPtr& IdExpressionPrimaryExpression::expression() const
{
    return mExpression;
}

IdExpressionPrimaryExpression& IdExpressionPrimaryExpression::set_expression(const IdExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

IdExpressionPrimaryExpression& IdExpressionPrimaryExpression::operator<<(const IdExpressionSPtr& expression)
{
    return set_expression(expression);
}

const IdExpressionPrimaryExpressionSPtr& operator<<(const IdExpressionPrimaryExpressionSPtr& object,
                                                    const IdExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

