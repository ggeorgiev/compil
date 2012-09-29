#include "enumeration_value.h"

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

}

