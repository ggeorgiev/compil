#include "enumeration_value.h"

namespace compil
{

EnumerationValue::EnumerationValue()
{
}

EnumerationValue::~EnumerationValue()
{
}

EnumerationValueSPtr EnumerationValue::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<EnumerationValue>(pObject);
}

const EnumerationWPtr& EnumerationValue::enumeration() const
{
    return mEnumeration;
}

void EnumerationValue::set_enumeration(const EnumerationSPtr& enumeration)
{
    mEnumeration = enumeration;
}

const CommentSPtr& EnumerationValue::comment() const
{
    return mComment;
}

void EnumerationValue::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
}

const NameSPtr& EnumerationValue::name() const
{
    return mName;
}

void EnumerationValue::set_name(const NameSPtr& name)
{
    mName = name;
}

AbsoluteEnumerationValue::AbsoluteEnumerationValue()
{
}

AbsoluteEnumerationValue::~AbsoluteEnumerationValue()
{
}

AbsoluteEnumerationValueSPtr AbsoluteEnumerationValue::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<AbsoluteEnumerationValue>(pObject);
}

long AbsoluteEnumerationValue::value() const
{
    return mValue;
}

void AbsoluteEnumerationValue::set_value(long value)
{
    mValue = value;
}

ComposedEnumerationValue::ComposedEnumerationValue()
{
}

ComposedEnumerationValue::~ComposedEnumerationValue()
{
}

ComposedEnumerationValueSPtr ComposedEnumerationValue::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<ComposedEnumerationValue>(pObject);
}

const std::vector<EnumerationValueSPtr>& ComposedEnumerationValue::values() const
{
    return mValues;
}

void ComposedEnumerationValue::set_values(const std::vector<EnumerationValueSPtr>& values)
{
    mValues = values;
}

}

