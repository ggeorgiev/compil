#include "language/c++/expression/postfix_expression.h"

namespace lang
{

namespace cpp
{

PostfixExpression::PostfixExpression()
{
}

PostfixExpression::~PostfixExpression()
{
}

PostfixExpressionSPtr PostfixExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<PostfixExpression>(object);
}

}

}

