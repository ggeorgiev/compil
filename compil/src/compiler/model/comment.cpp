#include "comment.h"

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

}

