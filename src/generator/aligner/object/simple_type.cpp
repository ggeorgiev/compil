// Boost C++ Utility
#include <boost/assert.hpp>

#include "simple_type.h"
// Standard C Library
#include <stddef.h>

int SimpleType::bitmask_namespace_()
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
    return true;
}

bool SimpleType::isVoid() const
{
    if (exist_namespace_()) return false;
    if (exist_value()) return false;
    return true;
}

const Namespace& SimpleType::namespace_() const
{
    BOOST_ASSERT(exist_namespace_());
    return mNamespace_;
}

bool SimpleType::exist_namespace_() const
{
    return (mBits & bitmask_namespace_()) != 0;
}

SimpleType::Builder& SimpleType::Builder::set_namespace_(const Namespace& namespace_)
{
    mpObject->mNamespace_  = namespace_;
    mpObject->mBits       |= bitmask_namespace_();
    return *this;
}

Namespace& SimpleType::Builder::mutable_namespace_()
{
    mpObject->mBits |= bitmask_namespace_();
    return mpObject->mNamespace_;
}

void SimpleType::Builder::clear_namespace_()
{
    mpObject->mNamespace_  =  Namespace();
    mpObject->mBits       &= ~bitmask_namespace_();
}

const std::string& SimpleType::value() const
{
    BOOST_ASSERT(exist_value());
    return mValue;
}

bool SimpleType::exist_value() const
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

void SimpleType::Builder::clear_value()
{
    mpObject->mValue.clear();
    mpObject->mBits &= ~bitmask_value();
}

SimpleTypeSPtr CreateSimpleType(const Namespace& namespace_)
{
    SimpleType::Builder builder;
    builder.set_namespace_(namespace_);
    return builder.finalize();
}

SimpleTypeSPtr CreateSimpleType(const std::string& value)
{
    SimpleType::Builder builder;
    builder.set_value(value);
    return builder.finalize();
}

SimpleTypeSPtr CreateSimpleType(const Namespace& namespace_, const std::string& value)
{
    SimpleType::Builder builder;
    builder.set_namespace_(namespace_);
    builder.set_value(value);
    return builder.finalize();
}

