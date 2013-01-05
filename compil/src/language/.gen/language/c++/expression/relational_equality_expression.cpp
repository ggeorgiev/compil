// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/relational_equality_expression.h"

namespace lang
{

namespace cpp
{

RelationalEqualityExpression::RelationalEqualityExpression()
{
}

RelationalEqualityExpression::~RelationalEqualityExpression()
{
}

RelationalEqualityExpressionSPtr RelationalEqualityExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<RelationalEqualityExpression>(object);
}

const RelationalExpressionSPtr& RelationalEqualityExpression::expression() const
{
    return mExpression;
}

RelationalEqualityExpression& RelationalEqualityExpression::set_expression(const RelationalExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

RelationalEqualityExpression& RelationalEqualityExpression::operator<<(const RelationalExpressionSPtr& expression)
{
    return set_expression(expression);
}

const RelationalEqualityExpressionSPtr& operator<<(const RelationalEqualityExpressionSPtr& object,
                                                   const RelationalExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

RelationalEqualityExpression& RelationalEqualityExpression::set_type(const EType& type)
{
    EqualityExpression::set_type(type);
    return *this;
}

RelationalEqualityExpression& RelationalEqualityExpression::operator<<(const EType& type)
{
    *(EqualityExpression*)this << type;
    return *this;
}

const RelationalEqualityExpressionSPtr& operator<<(const RelationalEqualityExpressionSPtr& object,
                                                   const EqualityExpression::EType& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

}

}

