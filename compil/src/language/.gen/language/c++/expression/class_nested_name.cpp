// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/class_nested_name.h"

namespace lang
{

namespace cpp
{

ClassNestedName::ClassNestedName()
{
}

ClassNestedName::~ClassNestedName()
{
}

ClassNestedNameSPtr ClassNestedName::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<ClassNestedName>(object);
}

const IdentifierClassNameSPtr& ClassNestedName::name() const
{
    return mName;
}

ClassNestedName& ClassNestedName::set_name(const IdentifierClassNameSPtr& name)
{
    mName = name;
    return *this;
}

ClassNestedName& ClassNestedName::operator<<(const IdentifierClassNameSPtr& name)
{
    return set_name(name);
}

const ClassNestedNameSPtr& operator<<(const ClassNestedNameSPtr& object, const IdentifierClassNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

}

}

