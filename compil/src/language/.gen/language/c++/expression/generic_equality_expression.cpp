#include "language/c++/expression/generic_equality_expression.h"

namespace lang
{

namespace cpp
{

GenericEqualityExpression::GenericEqualityExpression()
{
}

GenericEqualityExpression::~GenericEqualityExpression()
{
}

GenericEqualityExpressionSPtr GenericEqualityExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<GenericEqualityExpression>(object);
}

const ExpressionSPtr& GenericEqualityExpression::first() const
{
    return mFirst;
}

GenericEqualityExpression& GenericEqualityExpression::set_first(const ExpressionSPtr& first)
{
    mFirst = first;
    return *this;
}

const ExpressionSPtr& GenericEqualityExpression::second() const
{
    return mSecond;
}

GenericEqualityExpression& GenericEqualityExpression::set_second(const ExpressionSPtr& second)
{
    mSecond = second;
    return *this;
}

GenericEqualityExpression& GenericEqualityExpression::set_type(const EType& type)
{
    EqualityExpression::set_type(type);
    return *this;
}

}

}

