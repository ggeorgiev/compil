// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/compil/all/file.h"

namespace lang
{

namespace compil
{

File::File()
{
}

File::~File()
{
}

FileSPtr File::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<File>(object);
}

const std::vector<CommentSPtr>& File::comments() const
{
    return mComments;
}

File& File::set_comments(const std::vector<CommentSPtr>& comments)
{
    mComments = comments;
    return *this;
}

std::vector<CommentSPtr>& File::mutable_comments()
{
    return mComments;
}

File& File::operator<<(const std::vector<CommentSPtr>& comments)
{
    return set_comments(comments);
}

const FileSPtr& operator<<(const FileSPtr& object, const std::vector<CommentSPtr>& comments)
{
    BOOST_ASSERT(object);
    *object << comments;
    return object;
}

File& File::operator<<(const CommentSPtr& commentsItem)
{
    mComments.push_back(commentsItem);
    return *this;
}

const FileSPtr& operator<<(const FileSPtr& object, const CommentSPtr& commentsItem)
{
    BOOST_ASSERT(object);
    *object << commentsItem;
    return object;
}

const Version& File::version() const
{
    return mVersion;
}

File& File::set_version(const Version& version)
{
    mVersion = version;
    return *this;
}

Version& File::mutable_version()
{
    return mVersion;
}

File& File::operator<<(const Version& version)
{
    return set_version(version);
}

const FileSPtr& operator<<(const FileSPtr& object, const Version& version)
{
    BOOST_ASSERT(object);
    *object << version;
    return object;
}

File& File::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

File& File::operator<<(const SourceIdSPtr& sourceId)
{
    *(Object*)this << sourceId;
    return *this;
}

const FileSPtr& operator<<(const FileSPtr& object, const SourceIdSPtr& sourceId)
{
    BOOST_ASSERT(object);
    *object << sourceId;
    return object;
}

File& File::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

File& File::operator<<(const Line& line)
{
    *(Object*)this << line;
    return *this;
}

const FileSPtr& operator<<(const FileSPtr& object, const Line& line)
{
    BOOST_ASSERT(object);
    *object << line;
    return object;
}

File& File::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

File& File::operator<<(const Column& column)
{
    *(Object*)this << column;
    return *this;
}

const FileSPtr& operator<<(const FileSPtr& object, const Column& column)
{
    BOOST_ASSERT(object);
    *object << column;
    return object;
}

}

}

