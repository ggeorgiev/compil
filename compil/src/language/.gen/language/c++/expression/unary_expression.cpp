#include "language/c++/expression/unary_expression.h"

namespace lang
{

namespace cpp
{

UnaryExpression::UnaryExpression()
{
}

UnaryExpression::~UnaryExpression()
{
}

UnaryExpressionSPtr UnaryExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<UnaryExpression>(object);
}

}

}

