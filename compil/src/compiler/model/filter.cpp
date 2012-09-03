#include "filter.h"

namespace compil
{

Filter::Filter()
{
}

Filter::~Filter()
{
}

FilterSPtr Filter::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Filter>(pObject);
}

const CommentSPtr& Filter::comment() const
{
    return mComment;
}

Filter& Filter::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const FieldSPtr& Filter::field() const
{
    return mField;
}

Filter& Filter::set_field(const FieldSPtr& field)
{
    mField = field;
    return *this;
}

const std::string& Filter::method() const
{
    return mMethod;
}

Filter& Filter::set_method(const std::string& method)
{
    mMethod = method;
    return *this;
}

std::string& Filter::mutable_method()
{
    return mMethod;
}

}

