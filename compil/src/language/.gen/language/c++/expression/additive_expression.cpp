#include "language/c++/expression/additive_expression.h"

namespace lang
{

namespace cpp
{

AdditiveExpression::AdditiveExpression()
{
}

AdditiveExpression::~AdditiveExpression()
{
}

AdditiveExpressionSPtr AdditiveExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<AdditiveExpression>(object);
}

}

}

