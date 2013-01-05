#include "language/compil/document/enumeration_value.h"

namespace lang
{

namespace compil
{

EnumerationValue::EnumerationValue()
{
}

EnumerationValue::~EnumerationValue()
{
}

EnumerationValueSPtr EnumerationValue::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<EnumerationValue>(object);
}

const EnumerationWPtr& EnumerationValue::enumeration() const
{
    return mEnumeration;
}

EnumerationValue& EnumerationValue::set_enumeration(const EnumerationSPtr& enumeration)
{
    mEnumeration = enumeration;
    return *this;
}

const CommentSPtr& EnumerationValue::comment() const
{
    return mComment;
}

EnumerationValue& EnumerationValue::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const NameSPtr& EnumerationValue::name() const
{
    return mName;
}

EnumerationValue& EnumerationValue::set_name(const NameSPtr& name)
{
    mName = name;
    return *this;
}

EnumerationValue& EnumerationValue::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

EnumerationValue& EnumerationValue::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

EnumerationValue& EnumerationValue::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

AbsoluteEnumerationValue::AbsoluteEnumerationValue()
{
}

AbsoluteEnumerationValue::~AbsoluteEnumerationValue()
{
}

AbsoluteEnumerationValueSPtr AbsoluteEnumerationValue::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<AbsoluteEnumerationValue>(object);
}

long AbsoluteEnumerationValue::value() const
{
    return mValue;
}

AbsoluteEnumerationValue& AbsoluteEnumerationValue::set_value(long value)
{
    mValue = value;
    return *this;
}

AbsoluteEnumerationValue& AbsoluteEnumerationValue::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

AbsoluteEnumerationValue& AbsoluteEnumerationValue::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

AbsoluteEnumerationValue& AbsoluteEnumerationValue::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

AbsoluteEnumerationValue& AbsoluteEnumerationValue::set_enumeration(const EnumerationSPtr& enumeration)
{
    EnumerationValue::set_enumeration(enumeration);
    return *this;
}

AbsoluteEnumerationValue& AbsoluteEnumerationValue::set_comment(const CommentSPtr& comment)
{
    EnumerationValue::set_comment(comment);
    return *this;
}

AbsoluteEnumerationValue& AbsoluteEnumerationValue::set_name(const NameSPtr& name)
{
    EnumerationValue::set_name(name);
    return *this;
}

ComposedEnumerationValue::ComposedEnumerationValue()
{
}

ComposedEnumerationValue::~ComposedEnumerationValue()
{
}

ComposedEnumerationValueSPtr ComposedEnumerationValue::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<ComposedEnumerationValue>(object);
}

const std::vector<EnumerationValueSPtr>& ComposedEnumerationValue::values() const
{
    return mValues;
}

ComposedEnumerationValue& ComposedEnumerationValue::set_values(const std::vector<EnumerationValueSPtr>& values)
{
    mValues = values;
    return *this;
}

std::vector<EnumerationValueSPtr>& ComposedEnumerationValue::mutable_values()
{
    return mValues;
}

ComposedEnumerationValue& ComposedEnumerationValue::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

ComposedEnumerationValue& ComposedEnumerationValue::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

ComposedEnumerationValue& ComposedEnumerationValue::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

ComposedEnumerationValue& ComposedEnumerationValue::set_enumeration(const EnumerationSPtr& enumeration)
{
    EnumerationValue::set_enumeration(enumeration);
    return *this;
}

ComposedEnumerationValue& ComposedEnumerationValue::set_comment(const CommentSPtr& comment)
{
    EnumerationValue::set_comment(comment);
    return *this;
}

ComposedEnumerationValue& ComposedEnumerationValue::set_name(const NameSPtr& name)
{
    EnumerationValue::set_name(name);
    return *this;
}

}

}

