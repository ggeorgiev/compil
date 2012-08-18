#include "version.h"

namespace compil
{

Version::Version()
{
}

Version::~Version()
{
}

VersionSPtr Version::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Version>(pObject);
}

long Version::number() const
{
    return mNumber;
}

void Version::set_number(long number)
{
    mNumber = number;
}

}

