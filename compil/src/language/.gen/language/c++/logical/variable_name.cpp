// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/logical/variable_name.h"

namespace lang
{

namespace cpp
{

VariableName::VariableName()
{
}

VariableName::~VariableName()
{
}

const std::string& VariableName::value() const
{
    return mValue;
}

VariableName& VariableName::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& VariableName::mutable_value()
{
    return mValue;
}

VariableName& VariableName::operator<<(const std::string& value)
{
    return set_value(value);
}

const VariableNameSPtr& operator<<(const VariableNameSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

