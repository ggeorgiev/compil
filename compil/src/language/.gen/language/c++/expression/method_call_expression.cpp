// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/method_call_expression.h"

namespace lang
{

namespace cpp
{

MethodCallExpression::MethodCallExpression()
{
}

MethodCallExpression::~MethodCallExpression()
{
}

MethodCallExpressionSPtr MethodCallExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<MethodCallExpression>(object);
}

const ExpressionSPtr& MethodCallExpression::variable() const
{
    return mVariable;
}

MethodCallExpression& MethodCallExpression::set_variable(const ExpressionSPtr& variable)
{
    mVariable = variable;
    return *this;
}

MethodCallExpression& MethodCallExpression::operator<<(const ExpressionSPtr& variable)
{
    return set_variable(variable);
}

const MethodCallExpressionSPtr& operator<<(const MethodCallExpressionSPtr& object, const ExpressionSPtr& variable)
{
    BOOST_ASSERT(object);
    *object << variable;
    return object;
}

const MethodNameSPtr& MethodCallExpression::method() const
{
    return mMethod;
}

MethodCallExpression& MethodCallExpression::set_method(const MethodNameSPtr& method)
{
    mMethod = method;
    return *this;
}

MethodCallExpression& MethodCallExpression::operator<<(const MethodNameSPtr& method)
{
    return set_method(method);
}

const MethodCallExpressionSPtr& operator<<(const MethodCallExpressionSPtr& object, const MethodNameSPtr& method)
{
    BOOST_ASSERT(object);
    *object << method;
    return object;
}

const ExpressionListSPtr& MethodCallExpression::list() const
{
    return mList;
}

MethodCallExpression& MethodCallExpression::set_list(const ExpressionListSPtr& list)
{
    mList = list;
    return *this;
}

MethodCallExpression& MethodCallExpression::operator<<(const ExpressionListSPtr& list)
{
    return set_list(list);
}

const MethodCallExpressionSPtr& operator<<(const MethodCallExpressionSPtr& object, const ExpressionListSPtr& list)
{
    BOOST_ASSERT(object);
    *object << list;
    return object;
}

}

}

