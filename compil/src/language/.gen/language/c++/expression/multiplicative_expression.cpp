#include "language/c++/expression/multiplicative_expression.h"

namespace lang
{

namespace cpp
{

MultiplicativeExpression::MultiplicativeExpression()
{
}

MultiplicativeExpression::~MultiplicativeExpression()
{
}

MultiplicativeExpressionSPtr MultiplicativeExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<MultiplicativeExpression>(object);
}

}

}

