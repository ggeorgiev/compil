// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/compil/all/package_element.h"

namespace lang
{

namespace compil
{

PackageElement::PackageElement()
{
}

PackageElement::~PackageElement()
{
}

bool PackageElement::operator==(const PackageElement& object) const
{
    // can not compare string
    return true;
}

bool PackageElement::operator==(const PackageElementSPtr& object) const
{
    return *this == *object;
}

const std::string& PackageElement::value() const
{
    return mValue;
}

PackageElement& PackageElement::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& PackageElement::mutable_value()
{
    return mValue;
}

PackageElement& PackageElement::operator<<(const std::string& value)
{
    return set_value(value);
}

const PackageElementSPtr& operator<<(const PackageElementSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

