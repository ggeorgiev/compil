// Boost C++ Utility
#include <boost/assert.hpp>

#include "comment.h"

namespace compil
{

int Comment::bitmask_lines()
{
    return 0x1;
}

Comment::Comment()
        : mBits(0)
{
}

Comment::~Comment()
{
}

CommentSPtr Comment::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Comment>(pObject);
}

bool Comment::isInitialized() const
{
    // structure Object is not controlled. This function assume it is initilized
    if (!valid_lines()) return false;
    return true;
}

const std::vector<std::string>& Comment::lines() const
{
    BOOST_ASSERT(valid_lines());
    return mLines;
}

bool Comment::valid_lines() const
{
    return (mBits & bitmask_lines()) != 0;
}

void Comment::set_lines(const std::vector<std::string>& lines)
{
    mLines  = lines;
    mBits  |= bitmask_lines();
}

std::vector<std::string>& Comment::mutable_lines()
{
    mBits |= bitmask_lines();
    return mLines;
}

void Comment::erase_lines()
{
    mLines.clear();
    mBits &= ~bitmask_lines();
}

}

