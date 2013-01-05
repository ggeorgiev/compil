// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/variable_expression.h"

namespace lang
{

namespace cpp
{

VariableExpression::VariableExpression()
{
}

VariableExpression::~VariableExpression()
{
}

VariableExpressionSPtr VariableExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<VariableExpression>(object);
}

const VariableSPtr& VariableExpression::variable() const
{
    return mVariable;
}

VariableExpression& VariableExpression::set_variable(const VariableSPtr& variable)
{
    mVariable = variable;
    return *this;
}

VariableExpression& VariableExpression::operator<<(const VariableSPtr& variable)
{
    return set_variable(variable);
}

const VariableExpressionSPtr& operator<<(const VariableExpressionSPtr& object, const VariableSPtr& variable)
{
    BOOST_ASSERT(object);
    *object << variable;
    return object;
}

}

}

