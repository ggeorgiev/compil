// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/custom_expression.h"

namespace lang
{

namespace cpp
{

CustomExpression::CustomExpression()
{
}

CustomExpression::~CustomExpression()
{
}

CustomExpressionSPtr CustomExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<CustomExpression>(object);
}

const std::string& CustomExpression::value() const
{
    return mValue;
}

CustomExpression& CustomExpression::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& CustomExpression::mutable_value()
{
    return mValue;
}

CustomExpression& CustomExpression::operator<<(const std::string& value)
{
    return set_value(value);
}

const CustomExpressionSPtr& operator<<(const CustomExpressionSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

