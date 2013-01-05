#include "language/c++/expression/id_expression.h"

namespace lang
{

namespace cpp
{

IdExpression::IdExpression()
{
}

IdExpression::~IdExpression()
{
}

IdExpressionSPtr IdExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<IdExpression>(object);
}

}

}

