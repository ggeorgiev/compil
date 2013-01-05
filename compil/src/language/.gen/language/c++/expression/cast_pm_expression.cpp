// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/cast_pm_expression.h"

namespace lang
{

namespace cpp
{

CastPmExpression::CastPmExpression()
{
}

CastPmExpression::~CastPmExpression()
{
}

CastPmExpressionSPtr CastPmExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<CastPmExpression>(object);
}

const CastExpressionSPtr& CastPmExpression::expression() const
{
    return mExpression;
}

CastPmExpression& CastPmExpression::set_expression(const CastExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

CastPmExpression& CastPmExpression::operator<<(const CastExpressionSPtr& expression)
{
    return set_expression(expression);
}

const CastPmExpressionSPtr& operator<<(const CastPmExpressionSPtr& object, const CastExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

