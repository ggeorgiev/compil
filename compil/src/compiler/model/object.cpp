#include "object.h"

namespace compil
{

Object::Object()
        : mLine  (default_line())
        , mColumn(default_column())
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

long Object::line() const
{
    return mLine;
}

long Object::default_line()
{
    return -1;
}

Object& Object::set_line(long line)
{
    mLine = line;
    return *this;
}

long Object::column() const
{
    return mColumn;
}

long Object::default_column()
{
    return -1;
}

Object& Object::set_column(long column)
{
    mColumn = column;
    return *this;
}

}

