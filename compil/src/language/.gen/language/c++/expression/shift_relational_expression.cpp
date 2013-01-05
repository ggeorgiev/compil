// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/shift_relational_expression.h"

namespace lang
{

namespace cpp
{

ShiftRelationalExpression::ShiftRelationalExpression()
{
}

ShiftRelationalExpression::~ShiftRelationalExpression()
{
}

ShiftRelationalExpressionSPtr ShiftRelationalExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<ShiftRelationalExpression>(object);
}

const ShiftExpressionSPtr& ShiftRelationalExpression::expression() const
{
    return mExpression;
}

ShiftRelationalExpression& ShiftRelationalExpression::set_expression(const ShiftExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

ShiftRelationalExpression& ShiftRelationalExpression::operator<<(const ShiftExpressionSPtr& expression)
{
    return set_expression(expression);
}

const ShiftRelationalExpressionSPtr& operator<<(const ShiftRelationalExpressionSPtr& object,
                                                const ShiftExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

