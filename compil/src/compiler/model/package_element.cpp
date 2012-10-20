#include "package_element.h"

namespace compil
{

PackageElement::PackageElement()
        : mExternal(default_external())
{
}

PackageElement::~PackageElement()
{
}

bool PackageElement::operator==(const PackageElement& object) const
{
    if (external() != object.external()) return false;
    return value() == object.value();
}

bool PackageElement::operator==(const PackageElementSPtr& object) const
{
    return *this == *object;
}

bool PackageElement::external() const
{
    return mExternal;
}

bool PackageElement::default_external()
{
    return false;
}

PackageElement& PackageElement::set_external(bool external)
{
    mExternal = external;
    return *this;
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

}

