// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/custom_postfix_expression.h"

namespace lang
{

namespace cpp
{

CustomPostfixExpression::CustomPostfixExpression()
{
}

CustomPostfixExpression::~CustomPostfixExpression()
{
}

CustomPostfixExpressionSPtr CustomPostfixExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<CustomPostfixExpression>(object);
}

const std::string& CustomPostfixExpression::value() const
{
    return mValue;
}

CustomPostfixExpression& CustomPostfixExpression::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& CustomPostfixExpression::mutable_value()
{
    return mValue;
}

CustomPostfixExpression& CustomPostfixExpression::operator<<(const std::string& value)
{
    return set_value(value);
}

const CustomPostfixExpressionSPtr& operator<<(const CustomPostfixExpressionSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

