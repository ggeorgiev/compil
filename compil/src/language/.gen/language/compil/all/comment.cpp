#include "language/compil/all/comment.h"

namespace lang
{

namespace compil
{

Comment::Comment()
{
}

Comment::~Comment()
{
}

CommentSPtr Comment::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Comment>(object);
}

const std::vector<std::string>& Comment::lines() const
{
    return mLines;
}

Comment& Comment::set_lines(const std::vector<std::string>& lines)
{
    mLines = lines;
    return *this;
}

std::vector<std::string>& Comment::mutable_lines()
{
    return mLines;
}

Comment& Comment::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Comment& Comment::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Comment& Comment::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

