#include "language/c++/expression/pm_expression.h"

namespace lang
{

namespace cpp
{

PmExpression::PmExpression()
{
}

PmExpression::~PmExpression()
{
}

PmExpressionSPtr PmExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<PmExpression>(object);
}

}

}

