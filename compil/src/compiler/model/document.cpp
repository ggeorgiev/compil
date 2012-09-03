#include "document.h"

namespace compil
{

Document::Document()
{
}

Document::~Document()
{
}

DocumentSPtr Document::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Document>(pObject);
}

const std::vector<CommentSPtr>& Document::comments() const
{
    return mComments;
}

Document& Document::set_comments(const std::vector<CommentSPtr>& comments)
{
    mComments = comments;
    return *this;
}

std::vector<CommentSPtr>& Document::mutable_comments()
{
    return mComments;
}

const Version& Document::version() const
{
    return mVersion;
}

Document& Document::set_version(const Version& version)
{
    mVersion = version;
    return *this;
}

Version& Document::mutable_version()
{
    return mVersion;
}

}

