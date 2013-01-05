// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/namespace/identifier_namespace_name.h"

namespace lang
{

namespace cpp
{

IdentifierNamespaceName::IdentifierNamespaceName()
{
}

IdentifierNamespaceName::~IdentifierNamespaceName()
{
}

IdentifierNamespaceNameSPtr IdentifierNamespaceName::downcast(const NamespaceNameSPtr& object)
{
    return boost::static_pointer_cast<IdentifierNamespaceName>(object);
}

const IdentifierSPtr& IdentifierNamespaceName::identifier() const
{
    return mIdentifier;
}

IdentifierNamespaceName& IdentifierNamespaceName::set_identifier(const IdentifierSPtr& identifier)
{
    mIdentifier = identifier;
    return *this;
}

IdentifierNamespaceName& IdentifierNamespaceName::operator<<(const IdentifierSPtr& identifier)
{
    return set_identifier(identifier);
}

const IdentifierNamespaceNameSPtr& operator<<(const IdentifierNamespaceNameSPtr& object,
                                              const IdentifierSPtr& identifier)
{
    BOOST_ASSERT(object);
    *object << identifier;
    return object;
}

}

}

