// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/class/identifier_method_name.h"

namespace lang
{

namespace cpp
{

IdentifierMethodName::IdentifierMethodName()
{
}

IdentifierMethodName::~IdentifierMethodName()
{
}

IdentifierMethodNameSPtr IdentifierMethodName::downcast(const MethodNameSPtr& object)
{
    return boost::static_pointer_cast<IdentifierMethodName>(object);
}

const IdentifierSPtr& IdentifierMethodName::identifier() const
{
    return mIdentifier;
}

IdentifierMethodName& IdentifierMethodName::set_identifier(const IdentifierSPtr& identifier)
{
    mIdentifier = identifier;
    return *this;
}

IdentifierMethodName& IdentifierMethodName::operator<<(const IdentifierSPtr& identifier)
{
    return set_identifier(identifier);
}

const IdentifierMethodNameSPtr& operator<<(const IdentifierMethodNameSPtr& object, const IdentifierSPtr& identifier)
{
    BOOST_ASSERT(object);
    *object << identifier;
    return object;
}

}

}

