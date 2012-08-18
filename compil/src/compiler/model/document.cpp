// Boost C++ Utility
#include <boost/assert.hpp>

#include "document.h"

namespace compil
{

int Document::bitmask_comments()
{
    return 0x1;
}

int Document::bitmask_version()
{
    return 0x2;
}

Document::Document()
        : mBits(0)
{
}

Document::~Document()
{
}

DocumentSPtr Document::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Document>(pObject);
}

bool Document::isInitialized() const
{
    // structure Object is not controlled. This function assume it is initilized
    if (!valid_version()) return false;
    return true;
}

const std::vector<CommentSPtr>& Document::comments() const
{
    BOOST_ASSERT(exist_comments());
    return mComments;
}

bool Document::exist_comments() const
{
    return (mBits & bitmask_comments()) != 0;
}

void Document::set_comments(const std::vector<CommentSPtr>& comments)
{
    mComments  = comments;
    mBits     |= bitmask_comments();
}

std::vector<CommentSPtr>& Document::mutable_comments()
{
    mBits |= bitmask_comments();
    return mComments;
}

void Document::clear_comments()
{
    mComments.clear();
    mBits &= ~bitmask_comments();
}

const Version& Document::version() const
{
    BOOST_ASSERT(valid_version());
    return mVersion;
}

bool Document::valid_version() const
{
    return (mBits & bitmask_version()) != 0;
}

void Document::set_version(const Version& version)
{
    mVersion  = version;
    mBits    |= bitmask_version();
}

Version& Document::mutable_version()
{
    mBits |= bitmask_version();
    return mVersion;
}

void Document::erase_version()
{
    mVersion  =  Version();
    mBits    &= ~bitmask_version();
}

}

