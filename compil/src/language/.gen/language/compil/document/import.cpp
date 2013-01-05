#include "language/compil/document/import.h"

namespace lang
{

namespace compil
{

Import::Import()
{
}

Import::~Import()
{
}

ImportSPtr Import::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Import>(object);
}

const std::string& Import::source() const
{
    return mSource;
}

Import& Import::set_source(const std::string& source)
{
    mSource = source;
    return *this;
}

std::string& Import::mutable_source()
{
    return mSource;
}

Import& Import::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Import& Import::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Import& Import::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

