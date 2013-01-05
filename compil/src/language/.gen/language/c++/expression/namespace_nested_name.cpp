// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/namespace_nested_name.h"

namespace lang
{

namespace cpp
{

NamespaceNestedName::NamespaceNestedName()
{
}

NamespaceNestedName::~NamespaceNestedName()
{
}

NamespaceNestedNameSPtr NamespaceNestedName::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<NamespaceNestedName>(object);
}

const IdentifierNamespaceNameSPtr& NamespaceNestedName::name() const
{
    return mName;
}

NamespaceNestedName& NamespaceNestedName::set_name(const IdentifierNamespaceNameSPtr& name)
{
    mName = name;
    return *this;
}

NamespaceNestedName& NamespaceNestedName::operator<<(const IdentifierNamespaceNameSPtr& name)
{
    return set_name(name);
}

const NamespaceNestedNameSPtr& operator<<(const NamespaceNestedNameSPtr& object,
                                          const IdentifierNamespaceNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

}

}

