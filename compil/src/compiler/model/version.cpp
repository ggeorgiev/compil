#include "version.h"

namespace compil
{

Version::Version()
{
}

Version::~Version()
{
}

VersionSPtr Version::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Version>(object);
}

long Version::number() const
{
    return mNumber;
}

Version& Version::set_number(long number)
{
    mNumber = number;
    return *this;
}

}

