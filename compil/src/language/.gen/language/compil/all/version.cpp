#include "language/compil/all/version.h"

namespace lang
{

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

Version& Version::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Version& Version::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Version& Version::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

