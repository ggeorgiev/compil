// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/lexical/identifier-cpp.h"

namespace lang
{

namespace cpp
{

Identifier::Identifier()
{
}

Identifier::~Identifier()
{
}

const std::string& Identifier::value() const
{
    return mValue;
}

Identifier& Identifier::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& Identifier::mutable_value()
{
    return mValue;
}

Identifier& Identifier::operator<<(const std::string& value)
{
    return set_value(value);
}

const IdentifierSPtr& operator<<(const IdentifierSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

