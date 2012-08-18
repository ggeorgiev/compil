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

void Object::set_sourceId(const SourceIdSPtr& sourceId)
{
    mSourceId = sourceId;
}

long Object::line() const
{
    return mLine;
}

long Object::default_line()
{
    return -1;
}

void Object::set_line(long line)
{
    mLine = line;
}

long Object::column() const
{
    return mColumn;
}

long Object::default_column()
{
    return -1;
}

void Object::set_column(long column)
{
    mColumn = column;
}

}

