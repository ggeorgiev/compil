#include "language/compil/document/default_value.h"

namespace lang
{

namespace compil
{

DefaultValue::DefaultValue()
        : mOptional(default_optional())
{
}

DefaultValue::~DefaultValue()
{
}

DefaultValueSPtr DefaultValue::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<DefaultValue>(object);
}

bool DefaultValue::optional() const
{
    return mOptional;
}

bool DefaultValue::default_optional()
{
    return false;
}

DefaultValue& DefaultValue::set_optional(bool optional)
{
    mOptional = optional;
    return *this;
}

const std::string& DefaultValue::value() const
{
    return mValue;
}

DefaultValue& DefaultValue::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& DefaultValue::mutable_value()
{
    return mValue;
}

DefaultValue& DefaultValue::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

DefaultValue& DefaultValue::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

DefaultValue& DefaultValue::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

