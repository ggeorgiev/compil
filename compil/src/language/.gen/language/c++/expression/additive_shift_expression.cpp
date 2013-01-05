// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/additive_shift_expression.h"

namespace lang
{

namespace cpp
{

AdditiveShiftExpression::AdditiveShiftExpression()
{
}

AdditiveShiftExpression::~AdditiveShiftExpression()
{
}

AdditiveShiftExpressionSPtr AdditiveShiftExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<AdditiveShiftExpression>(object);
}

const AdditiveExpressionSPtr& AdditiveShiftExpression::expression() const
{
    return mExpression;
}

AdditiveShiftExpression& AdditiveShiftExpression::set_expression(const AdditiveExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

AdditiveShiftExpression& AdditiveShiftExpression::operator<<(const AdditiveExpressionSPtr& expression)
{
    return set_expression(expression);
}

const AdditiveShiftExpressionSPtr& operator<<(const AdditiveShiftExpressionSPtr& object,
                                              const AdditiveExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

