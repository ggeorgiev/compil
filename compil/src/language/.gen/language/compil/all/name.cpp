// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/compil/all/name.h"

namespace lang
{

namespace compil
{

Name::Name()
{
}

Name::~Name()
{
}

NameSPtr Name::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Name>(object);
}

const std::string& Name::value() const
{
    return mValue;
}

Name& Name::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& Name::mutable_value()
{
    return mValue;
}

Name& Name::operator<<(const std::string& value)
{
    return set_value(value);
}

const NameSPtr& operator<<(const NameSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

Name& Name::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Name& Name::operator<<(const SourceIdSPtr& sourceId)
{
    *(Object*)this << sourceId;
    return *this;
}

const NameSPtr& operator<<(const NameSPtr& object, const SourceIdSPtr& sourceId)
{
    BOOST_ASSERT(object);
    *object << sourceId;
    return object;
}

Name& Name::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Name& Name::operator<<(const Line& line)
{
    *(Object*)this << line;
    return *this;
}

const NameSPtr& operator<<(const NameSPtr& object, const Line& line)
{
    BOOST_ASSERT(object);
    *object << line;
    return object;
}

Name& Name::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

Name& Name::operator<<(const Column& column)
{
    *(Object*)this << column;
    return *this;
}

const NameSPtr& operator<<(const NameSPtr& object, const Column& column)
{
    BOOST_ASSERT(object);
    *object << column;
    return object;
}

}

}

