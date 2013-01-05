// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/class/identifier_class_name.h"

namespace lang
{

namespace cpp
{

IdentifierClassName::IdentifierClassName()
{
}

IdentifierClassName::~IdentifierClassName()
{
}

IdentifierClassNameSPtr IdentifierClassName::downcast(const ClassNameSPtr& object)
{
    return boost::static_pointer_cast<IdentifierClassName>(object);
}

const IdentifierSPtr& IdentifierClassName::identifier() const
{
    return mIdentifier;
}

IdentifierClassName& IdentifierClassName::set_identifier(const IdentifierSPtr& identifier)
{
    mIdentifier = identifier;
    return *this;
}

IdentifierClassName& IdentifierClassName::operator<<(const IdentifierSPtr& identifier)
{
    return set_identifier(identifier);
}

const IdentifierClassNameSPtr& operator<<(const IdentifierClassNameSPtr& object, const IdentifierSPtr& identifier)
{
    BOOST_ASSERT(object);
    *object << identifier;
    return object;
}

}

}

