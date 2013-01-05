// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/compil/project/file_path.h"

namespace lang
{

namespace compil
{

FilePath::FilePath()
{
}

FilePath::~FilePath()
{
}

FilePathSPtr FilePath::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<FilePath>(object);
}

const std::string& FilePath::path() const
{
    return mPath;
}

FilePath& FilePath::set_path(const std::string& path)
{
    mPath = path;
    return *this;
}

std::string& FilePath::mutable_path()
{
    return mPath;
}

FilePath& FilePath::operator<<(const std::string& path)
{
    return set_path(path);
}

const FilePathSPtr& operator<<(const FilePathSPtr& object, const std::string& path)
{
    BOOST_ASSERT(object);
    *object << path;
    return object;
}

FilePath& FilePath::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

FilePath& FilePath::operator<<(const SourceIdSPtr& sourceId)
{
    *(Object*)this << sourceId;
    return *this;
}

const FilePathSPtr& operator<<(const FilePathSPtr& object, const SourceIdSPtr& sourceId)
{
    BOOST_ASSERT(object);
    *object << sourceId;
    return object;
}

FilePath& FilePath::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

FilePath& FilePath::operator<<(const Line& line)
{
    *(Object*)this << line;
    return *this;
}

const FilePathSPtr& operator<<(const FilePathSPtr& object, const Line& line)
{
    BOOST_ASSERT(object);
    *object << line;
    return object;
}

FilePath& FilePath::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

FilePath& FilePath::operator<<(const Column& column)
{
    *(Object*)this << column;
    return *this;
}

const FilePathSPtr& operator<<(const FilePathSPtr& object, const Column& column)
{
    BOOST_ASSERT(object);
    *object << column;
    return object;
}

}

}

