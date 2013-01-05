#include "language/compil/all/package.h"

namespace lang
{

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

const std::vector<PackageElementSPtr>& Package::short_() const
{
    return mShort;
}

Package& Package::set_short(const std::vector<PackageElementSPtr>& short_)
{
    mShort = short_;
    return *this;
}

std::vector<PackageElementSPtr>& Package::mutable_short()
{
    return mShort;
}

const std::vector<PackageElementSPtr>& Package::levels() const
{
    return mLevels;
}

Package& Package::set_levels(const std::vector<PackageElementSPtr>& levels)
{
    mLevels = levels;
    return *this;
}

std::vector<PackageElementSPtr>& Package::mutable_levels()
{
    return mLevels;
}

Package& Package::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Package& Package::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Package& Package::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

