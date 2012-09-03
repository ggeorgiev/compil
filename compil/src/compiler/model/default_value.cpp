#include "default_value.h"

namespace compil
{

DefaultValue::DefaultValue()
        : mOptional(default_optional())
{
}

DefaultValue::~DefaultValue()
{
}

DefaultValueSPtr DefaultValue::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<DefaultValue>(pObject);
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

}

