// Boost C++ Utility
#include <boost/assert.hpp>

#include "simple_type.h"

namespace cpp
{

namespace frm
{

SimpleType::SimpleType()
{
}

SimpleType::~SimpleType()
{
}

const NamespaceSPtr& SimpleType::namespace_() const
{
    return mNamespace;
}

SimpleType& SimpleType::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

SimpleType& SimpleType::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const SimpleTypeSPtr& operator<<(const SimpleTypeSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

const std::string& SimpleType::value() const
{
    return mValue;
}

SimpleType& SimpleType::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& SimpleType::mutable_value()
{
    return mValue;
}

SimpleType& SimpleType::operator<<(const std::string& value)
{
    return set_value(value);
}

const SimpleTypeSPtr& operator<<(const SimpleTypeSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

