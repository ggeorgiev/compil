// Boost C++ Utility
#include <boost/assert.hpp>

#include "comment.h"

namespace cpp
{

namespace frm
{

Comment::Comment()
{
}

Comment::~Comment()
{
}

const std::vector<std::string>& Comment::paragraphs() const
{
    return mParagraphs;
}

Comment& Comment::set_paragraphs(const std::vector<std::string>& paragraphs)
{
    mParagraphs = paragraphs;
    return *this;
}

std::vector<std::string>& Comment::mutable_paragraphs()
{
    return mParagraphs;
}

Comment& Comment::operator<<(const std::vector<std::string>& paragraphs)
{
    return set_paragraphs(paragraphs);
}

const CommentSPtr& operator<<(const CommentSPtr& object, const std::vector<std::string>& paragraphs)
{
    BOOST_ASSERT(object);
    *object << paragraphs;
    return object;
}

Comment& Comment::operator<<(const std::string& paragraphsItem)
{
    mParagraphs.push_back(paragraphsItem);
    return *this;
}

const CommentSPtr& operator<<(const CommentSPtr& object, const std::string& paragraphsItem)
{
    BOOST_ASSERT(object);
    *object << paragraphsItem;
    return object;
}

}

}

