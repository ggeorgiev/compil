#include "language/compil/document/filter.h"

namespace lang
{

namespace compil
{

Filter::Filter()
{
}

Filter::~Filter()
{
}

FilterSPtr Filter::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Filter>(object);
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

Filter& Filter::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Filter& Filter::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Filter& Filter::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

