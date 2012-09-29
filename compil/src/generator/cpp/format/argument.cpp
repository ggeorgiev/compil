// Boost C++ Utility
#include <boost/assert.hpp>

#include "argument.h"

namespace cpp
{

namespace frm
{

Argument::Argument()
{
}

Argument::~Argument()
{
}

const DecoratedTypeSPtr& Argument::type() const
{
    return mType;
}

Argument& Argument::set_type(const DecoratedTypeSPtr& type)
{
    mType = type;
    return *this;
}

Argument& Argument::operator<<(const DecoratedTypeSPtr& type)
{
    return set_type(type);
}

const ArgumentSPtr& operator<<(const ArgumentSPtr& object, const DecoratedTypeSPtr& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

const VariableNameSPtr& Argument::name() const
{
    return mName;
}

Argument& Argument::set_name(const VariableNameSPtr& name)
{
    mName = name;
    return *this;
}

Argument& Argument::operator<<(const VariableNameSPtr& name)
{
    return set_name(name);
}

const ArgumentSPtr& operator<<(const ArgumentSPtr& object, const VariableNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

}

}

