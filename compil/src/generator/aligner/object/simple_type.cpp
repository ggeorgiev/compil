// Boost C++ Utility
#include <boost/assert.hpp>

#include "simple_type.h"
// Standard C Library
#include <stddef.h>

int SimpleType::bitmask_namespace()
{
    return 0x1;
}

int SimpleType::bitmask_value()
{
    return 0x2;
}

SimpleType::Builder::Builder()
        : mpObject(new SimpleType())
{
}

SimpleType::Builder::Builder(const SimpleType& object)
        : mpObject(new SimpleType())
{
    *(SimpleType*)mpObject = object;
}

SimpleType::Builder::Builder(SimpleTypeRPtr pObject)
        : mpObject(pObject)
{
}

SimpleType::Builder::~Builder()
{
    delete (SimpleTypeRPtr)mpObject;
    mpObject = NULL;
}

const SimpleType& SimpleType::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(SimpleTypeRPtr)mpObject;
}

SimpleTypeSPtr SimpleType::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    SimpleTypeRPtr objectRPtr = (SimpleTypeRPtr)mpObject;
    mpObject = NULL;
    return SimpleTypeSPtr(objectRPtr);
}

SimpleType::SimpleType()
        : mBits(0)
{
}

SimpleType::~SimpleType()
{
}

bool SimpleType::isInitialized() const
{
    if (!valid_value()) return false;
    return true;
}

const NamespaceSPtr& SimpleType::namespace_() const
{
    BOOST_ASSERT(exist_namespace());
    return mNamespace;
}

bool SimpleType::exist_namespace() const
{
    return (mBits & bitmask_namespace()) != 0;
}

SimpleType::Builder& SimpleType::Builder::set_namespace(const NamespaceSPtr& namespace_)
{
    mpObject->mNamespace  = namespace_;
    mpObject->mBits      |= bitmask_namespace();
    return *this;
}

void SimpleType::Builder::clear_namespace()
{
    mpObject->mNamespace.reset();
    mpObject->mBits &= ~bitmask_namespace();
}

const std::string& SimpleType::value() const
{
    BOOST_ASSERT(valid_value());
    return mValue;
}

bool SimpleType::valid_value() const
{
    return (mBits & bitmask_value()) != 0;
}

SimpleType::Builder& SimpleType::Builder::set_value(const std::string& value)
{
    mpObject->mValue  = value;
    mpObject->mBits  |= bitmask_value();
    return *this;
}

std::string& SimpleType::Builder::mutable_value()
{
    mpObject->mBits |= bitmask_value();
    return mpObject->mValue;
}

void SimpleType::Builder::erase_value()
{
    mpObject->mValue.clear();
    mpObject->mBits &= ~bitmask_value();
}

SimpleTypeSPtr CreateSimpleType(const std::string& value)
{
    SimpleType::Builder builder;
    builder.set_value(value);
    return builder.finalize();
}

SimpleTypeSPtr CreateSimpleType(const NamespaceSPtr& namespace_, const std::string& value)
{
    SimpleType::Builder builder;
    builder.set_namespace(namespace_);
    builder.set_value(value);
    return builder.finalize();
}

