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

void Filter::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
}

const FieldSPtr& Filter::field() const
{
    return mField;
}

void Filter::set_field(const FieldSPtr& field)
{
    mField = field;
}

const std::string& Filter::method() const
{
    return mMethod;
}

void Filter::set_method(const std::string& method)
{
    mMethod = method;
}

}

