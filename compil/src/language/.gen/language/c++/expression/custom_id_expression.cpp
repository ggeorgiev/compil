// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/custom_id_expression.h"

namespace lang
{

namespace cpp
{

CustomIdExpression::CustomIdExpression()
{
}

CustomIdExpression::~CustomIdExpression()
{
}

CustomIdExpressionSPtr CustomIdExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<CustomIdExpression>(object);
}

const std::string& CustomIdExpression::value() const
{
    return mValue;
}

CustomIdExpression& CustomIdExpression::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& CustomIdExpression::mutable_value()
{
    return mValue;
}

CustomIdExpression& CustomIdExpression::operator<<(const std::string& value)
{
    return set_value(value);
}

const CustomIdExpressionSPtr& operator<<(const CustomIdExpressionSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

