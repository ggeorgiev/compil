// Boost C++ Utility
#include <boost/assert.hpp>

#include "default_value.h"

namespace compil
{

int DefaultValue::bitmask_optional()
{
    return 0x1;
}

int DefaultValue::bitmask_value()
{
    return 0x2;
}

DefaultValue::DefaultValue()
        : mBits    (0)
        , mOptional(default_optional())
{
}

DefaultValue::~DefaultValue()
{
}

DefaultValueSPtr DefaultValue::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<DefaultValue>(pObject);
}

bool DefaultValue::isInitialized() const
{
    // structure Object is not controlled. This function assume it is initilized
    if (!valid_value()) return false;
    return true;
}

bool DefaultValue::optional() const
{
    return mOptional;
}

bool DefaultValue::changed_optional() const
{
    return (mBits & bitmask_optional()) != 0;
}

bool DefaultValue::default_optional()
{
    return false;
}

void DefaultValue::set_optional(bool optional)
{
    mOptional  = optional;
    mBits     |= bitmask_optional();
}

void DefaultValue::reset_optional()
{
    mOptional  =  default_optional();
    mBits     &= ~bitmask_optional();
}

const std::string& DefaultValue::value() const
{
    BOOST_ASSERT(valid_value());
    return mValue;
}

bool DefaultValue::valid_value() const
{
    return (mBits & bitmask_value()) != 0;
}

void DefaultValue::set_value(const std::string& value)
{
    mValue  = value;
    mBits  |= bitmask_value();
}

std::string& DefaultValue::mutable_value()
{
    mBits |= bitmask_value();
    return mValue;
}

void DefaultValue::erase_value()
{
    mValue.clear();
    mBits &= ~bitmask_value();
}

}

