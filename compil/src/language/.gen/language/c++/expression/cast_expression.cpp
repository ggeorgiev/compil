#include "language/c++/expression/cast_expression.h"

namespace lang
{

namespace cpp
{

CastExpression::CastExpression()
{
}

CastExpression::~CastExpression()
{
}

CastExpressionSPtr CastExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<CastExpression>(object);
}

}

}

