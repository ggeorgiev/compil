#include "language/c++/expression/relational_expression.h"

namespace lang
{

namespace cpp
{

RelationalExpression::RelationalExpression()
{
}

RelationalExpression::~RelationalExpression()
{
}

RelationalExpressionSPtr RelationalExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<RelationalExpression>(object);
}

}

}

