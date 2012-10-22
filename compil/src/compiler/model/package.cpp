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

const std::vector<PackageElement>& Package::short_() const
{
    return mShort;
}

Package& Package::set_short(const std::vector<PackageElement>& short_)
{
    mShort = short_;
    return *this;
}

std::vector<PackageElement>& Package::mutable_short()
{
    return mShort;
}

const std::vector<PackageElement>& Package::levels() const
{
    return mLevels;
}

Package& Package::set_levels(const std::vector<PackageElement>& levels)
{
    mLevels = levels;
    return *this;
}

std::vector<PackageElement>& Package::mutable_levels()
{
    return mLevels;
}

}

