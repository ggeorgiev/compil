// Boost C++ Utility
#include <boost/assert.hpp>

#include "initialization.h"

namespace cpp
{

namespace frm
{

Initialization::Initialization()
{
}

Initialization::~Initialization()
{
}

const ConstructorNameSPtr& Initialization::constructorName() const
{
    return mConstructorName;
}

Initialization& Initialization::set_constructorName(const ConstructorNameSPtr& constructorName)
{
    mConstructorName = constructorName;
    return *this;
}

Initialization& Initialization::operator<<(const ConstructorNameSPtr& constructorName)
{
    return set_constructorName(constructorName);
}

const InitializationSPtr& operator<<(const InitializationSPtr& object, const ConstructorNameSPtr& constructorName)
{
    BOOST_ASSERT(object);
    *object << constructorName;
    return object;
}

const VariableNameSPtr& Initialization::variableName() const
{
    return mVariableName;
}

Initialization& Initialization::set_variableName(const VariableNameSPtr& variableName)
{
    mVariableName = variableName;
    return *this;
}

Initialization& Initialization::operator<<(const VariableNameSPtr& variableName)
{
    return set_variableName(variableName);
}

const InitializationSPtr& operator<<(const InitializationSPtr& object, const VariableNameSPtr& variableName)
{
    BOOST_ASSERT(object);
    *object << variableName;
    return object;
}

const ParameterValueSPtr& Initialization::parameter() const
{
    return mParameter;
}

Initialization& Initialization::set_parameter(const ParameterValueSPtr& parameter)
{
    mParameter = parameter;
    return *this;
}

Initialization& Initialization::operator<<(const ParameterValueSPtr& parameter)
{
    return set_parameter(parameter);
}

const InitializationSPtr& operator<<(const InitializationSPtr& object, const ParameterValueSPtr& parameter)
{
    BOOST_ASSERT(object);
    *object << parameter;
    return object;
}

}

}

