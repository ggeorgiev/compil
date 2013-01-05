#include "language/c++/expression/shift_expression.h"

namespace lang
{

namespace cpp
{

ShiftExpression::ShiftExpression()
{
}

ShiftExpression::~ShiftExpression()
{
}

ShiftExpressionSPtr ShiftExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<ShiftExpression>(object);
}

}

}

