#include "package.h"

namespace compil
{

Package::Package()
{
}

Package::~Package()
{
}

PackageSPtr Package::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Package>(object);
}

const std::vector<PackageElement>& Package::elements() const
{
    return mElements;
}

Package& Package::set_elements(const std::vector<PackageElement>& elements)
{
    mElements = elements;
    return *this;
}

std::vector<PackageElement>& Package::mutable_elements()
{
    return mElements;
}

}

