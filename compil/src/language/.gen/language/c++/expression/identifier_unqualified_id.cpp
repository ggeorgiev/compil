// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/identifier_unqualified_id.h"

namespace lang
{

namespace cpp
{

IdentifierUnqualifiedId::IdentifierUnqualifiedId()
{
}

IdentifierUnqualifiedId::~IdentifierUnqualifiedId()
{
}

IdentifierUnqualifiedIdSPtr IdentifierUnqualifiedId::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<IdentifierUnqualifiedId>(object);
}

const IdentifierSPtr& IdentifierUnqualifiedId::identifier() const
{
    return mIdentifier;
}

IdentifierUnqualifiedId& IdentifierUnqualifiedId::set_identifier(const IdentifierSPtr& identifier)
{
    mIdentifier = identifier;
    return *this;
}

IdentifierUnqualifiedId& IdentifierUnqualifiedId::operator<<(const IdentifierSPtr& identifier)
{
    return set_identifier(identifier);
}

const IdentifierUnqualifiedIdSPtr& operator<<(const IdentifierUnqualifiedIdSPtr& object,
                                              const IdentifierSPtr& identifier)
{
    BOOST_ASSERT(object);
    *object << identifier;
    return object;
}

}

}

