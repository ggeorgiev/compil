#include "package_element.h"

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
    return value() == object.value();
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

}

