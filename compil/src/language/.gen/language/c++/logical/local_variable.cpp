// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/logical/local_variable.h"

namespace lang
{

namespace cpp
{

LocalVariable::LocalVariable()
{
}

LocalVariable::~LocalVariable()
{
}

LocalVariableSPtr LocalVariable::downcast(const VariableSPtr& object)
{
    return boost::static_pointer_cast<LocalVariable>(object);
}

LocalVariable& LocalVariable::set_name(const VariableNameSPtr& name)
{
    Variable::set_name(name);
    return *this;
}

LocalVariable& LocalVariable::operator<<(const VariableNameSPtr& name)
{
    *(Variable*)this << name;
    return *this;
}

const LocalVariableSPtr& operator<<(const LocalVariableSPtr& object, const VariableNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

}

}

