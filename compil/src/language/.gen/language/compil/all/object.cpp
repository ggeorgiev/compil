// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/compil/all/object.h"

namespace lang
{

namespace compil
{

Line::Line()
: mValue()
{
}

Line::Line(long value)
        : mValue(value)
{
}

Column::Column()
: mValue()
{
}

Column::Column(long value)
        : mValue(value)
{
}

Object::Object()
{
}

Object::~Object()
{
}

const SourceIdSPtr& Object::sourceId() const
{
    return mSourceId;
}

Object& Object::set_sourceId(const SourceIdSPtr& sourceId)
{
    mSourceId = sourceId;
    return *this;
}

Object& Object::operator<<(const SourceIdSPtr& sourceId)
{
    return set_sourceId(sourceId);
}

const ObjectSPtr& operator<<(const ObjectSPtr& object, const SourceIdSPtr& sourceId)
{
    BOOST_ASSERT(object);
    *object << sourceId;
    return object;
}

const Line& Object::line() const
{
    return mLine;
}

Object& Object::set_line(const Line& line)
{
    mLine = line;
    return *this;
}

Line& Object::mutable_line()
{
    return mLine;
}

Object& Object::operator<<(const Line& line)
{
    return set_line(line);
}

const ObjectSPtr& operator<<(const ObjectSPtr& object, const Line& line)
{
    BOOST_ASSERT(object);
    *object << line;
    return object;
}

const Column& Object::column() const
{
    return mColumn;
}

Object& Object::set_column(const Column& column)
{
    mColumn = column;
    return *this;
}

Column& Object::mutable_column()
{
    return mColumn;
}

Object& Object::operator<<(const Column& column)
{
    return set_column(column);
}

const ObjectSPtr& operator<<(const ObjectSPtr& object, const Column& column)
{
    BOOST_ASSERT(object);
    *object << column;
    return object;
}

}

}

