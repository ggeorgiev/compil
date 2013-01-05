// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/constructor_call_expression.h"

namespace lang
{

namespace cpp
{

ConstructorCallExpression::ConstructorCallExpression()
{
}

ConstructorCallExpression::~ConstructorCallExpression()
{
}

ConstructorCallExpressionSPtr ConstructorCallExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<ConstructorCallExpression>(object);
}

const ClassNameSPtr& ConstructorCallExpression::type() const
{
    return mType;
}

ConstructorCallExpression& ConstructorCallExpression::set_type(const ClassNameSPtr& type)
{
    mType = type;
    return *this;
}

ConstructorCallExpression& ConstructorCallExpression::operator<<(const ClassNameSPtr& type)
{
    return set_type(type);
}

const ConstructorCallExpressionSPtr& operator<<(const ConstructorCallExpressionSPtr& object, const ClassNameSPtr& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

const std::vector<ExpressionSPtr>& ConstructorCallExpression::expressions() const
{
    return mExpressions;
}

ConstructorCallExpression& ConstructorCallExpression::set_expressions(const std::vector<ExpressionSPtr>& expressions)
{
    mExpressions = expressions;
    return *this;
}

std::vector<ExpressionSPtr>& ConstructorCallExpression::mutable_expressions()
{
    return mExpressions;
}

ConstructorCallExpression& ConstructorCallExpression::operator<<(const std::vector<ExpressionSPtr>& expressions)
{
    return set_expressions(expressions);
}

const ConstructorCallExpressionSPtr& operator<<(const ConstructorCallExpressionSPtr& object,
                                                const std::vector<ExpressionSPtr>& expressions)
{
    BOOST_ASSERT(object);
    *object << expressions;
    return object;
}

ConstructorCallExpression& ConstructorCallExpression::operator<<(const ExpressionSPtr& expressionsItem)
{
    mExpressions.push_back(expressionsItem);
    return *this;
}

const ConstructorCallExpressionSPtr& operator<<(const ConstructorCallExpressionSPtr& object,
                                                const ExpressionSPtr& expressionsItem)
{
    BOOST_ASSERT(object);
    *object << expressionsItem;
    return object;
}

}

}

