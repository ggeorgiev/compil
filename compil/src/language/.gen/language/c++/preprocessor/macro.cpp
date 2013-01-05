// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/preprocessor/macro.h"

namespace lang
{

namespace cpp
{

Macro::Macro()
{
}

Macro::~Macro()
{
}

const MacroNameSPtr& Macro::name() const
{
    return mName;
}

Macro& Macro::set_name(const MacroNameSPtr& name)
{
    mName = name;
    return *this;
}

Macro& Macro::operator<<(const MacroNameSPtr& name)
{
    return set_name(name);
}

const MacroSPtr& operator<<(const MacroSPtr& object, const MacroNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

}

}

