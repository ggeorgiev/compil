// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/pm_multiplicative_expression.h"

namespace lang
{

namespace cpp
{

PmMultiplicativeExpression::PmMultiplicativeExpression()
{
}

PmMultiplicativeExpression::~PmMultiplicativeExpression()
{
}

PmMultiplicativeExpressionSPtr PmMultiplicativeExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<PmMultiplicativeExpression>(object);
}

const PmExpressionSPtr& PmMultiplicativeExpression::expression() const
{
    return mExpression;
}

PmMultiplicativeExpression& PmMultiplicativeExpression::set_expression(const PmExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

PmMultiplicativeExpression& PmMultiplicativeExpression::operator<<(const PmExpressionSPtr& expression)
{
    return set_expression(expression);
}

const PmMultiplicativeExpressionSPtr& operator<<(const PmMultiplicativeExpressionSPtr& object,
                                                 const PmExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

