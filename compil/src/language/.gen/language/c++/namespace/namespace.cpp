// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/namespace/namespace.h"

namespace lang
{

namespace cpp
{

Namespace::Namespace()
{
}

Namespace::~Namespace()
{
}

const std::vector<NamespaceNameSPtr>& Namespace::names() const
{
    return mNames;
}

Namespace& Namespace::set_names(const std::vector<NamespaceNameSPtr>& names)
{
    mNames = names;
    return *this;
}

std::vector<NamespaceNameSPtr>& Namespace::mutable_names()
{
    return mNames;
}

Namespace& Namespace::operator<<(const std::vector<NamespaceNameSPtr>& names)
{
    return set_names(names);
}

const NamespaceSPtr& operator<<(const NamespaceSPtr& object, const std::vector<NamespaceNameSPtr>& names)
{
    BOOST_ASSERT(object);
    *object << names;
    return object;
}

Namespace& Namespace::operator<<(const NamespaceNameSPtr& namesItem)
{
    mNames.push_back(namesItem);
    return *this;
}

const NamespaceSPtr& operator<<(const NamespaceSPtr& object, const NamespaceNameSPtr& namesItem)
{
    BOOST_ASSERT(object);
    *object << namesItem;
    return object;
}

}

}

