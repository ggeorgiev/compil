#include "language/c++/expression/primary_expression.h"

namespace lang
{

namespace cpp
{

PrimaryExpression::PrimaryExpression()
{
}

PrimaryExpression::~PrimaryExpression()
{
}

PrimaryExpressionSPtr PrimaryExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<PrimaryExpression>(object);
}

}

}

