// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/compil/project/section.h"

namespace lang
{

namespace compil
{

Section::Section()
{
}

Section::~Section()
{
}

SectionSPtr Section::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Section>(object);
}

const NameSPtr& Section::name() const
{
    return mName;
}

Section& Section::set_name(const NameSPtr& name)
{
    mName = name;
    return *this;
}

Section& Section::operator<<(const NameSPtr& name)
{
    return set_name(name);
}

const SectionSPtr& operator<<(const SectionSPtr& object, const NameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<FilePathSPtr>& Section::paths() const
{
    return mPaths;
}

Section& Section::set_paths(const std::vector<FilePathSPtr>& paths)
{
    mPaths = paths;
    return *this;
}

std::vector<FilePathSPtr>& Section::mutable_paths()
{
    return mPaths;
}

Section& Section::operator<<(const std::vector<FilePathSPtr>& paths)
{
    return set_paths(paths);
}

const SectionSPtr& operator<<(const SectionSPtr& object, const std::vector<FilePathSPtr>& paths)
{
    BOOST_ASSERT(object);
    *object << paths;
    return object;
}

Section& Section::operator<<(const FilePathSPtr& pathsItem)
{
    mPaths.push_back(pathsItem);
    return *this;
}

const SectionSPtr& operator<<(const SectionSPtr& object, const FilePathSPtr& pathsItem)
{
    BOOST_ASSERT(object);
    *object << pathsItem;
    return object;
}

Section& Section::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Section& Section::operator<<(const SourceIdSPtr& sourceId)
{
    *(Object*)this << sourceId;
    return *this;
}

const SectionSPtr& operator<<(const SectionSPtr& object, const SourceIdSPtr& sourceId)
{
    BOOST_ASSERT(object);
    *object << sourceId;
    return object;
}

Section& Section::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Section& Section::operator<<(const Line& line)
{
    *(Object*)this << line;
    return *this;
}

const SectionSPtr& operator<<(const SectionSPtr& object, const Line& line)
{
    BOOST_ASSERT(object);
    *object << line;
    return object;
}

Section& Section::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

Section& Section::operator<<(const Column& column)
{
    *(Object*)this << column;
    return *this;
}

const SectionSPtr& operator<<(const SectionSPtr& object, const Column& column)
{
    BOOST_ASSERT(object);
    *object << column;
    return object;
}

}

}

