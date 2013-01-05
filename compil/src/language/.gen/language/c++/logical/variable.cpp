// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/logical/variable.h"

namespace lang
{

namespace cpp
{

Variable::Variable()
{
}

Variable::~Variable()
{
}

const VariableNameSPtr& Variable::name() const
{
    return mName;
}

Variable& Variable::set_name(const VariableNameSPtr& name)
{
    mName = name;
    return *this;
}

Variable& Variable::operator<<(const VariableNameSPtr& name)
{
    return set_name(name);
}

const VariableSPtr& operator<<(const VariableSPtr& object, const VariableNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

}

}

