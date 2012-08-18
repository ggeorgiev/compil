// Boost C++ Utility
#include <boost/assert.hpp>

#include "modifier.h"
// Standard C Library
#include <stddef.h>

int Modifier::bitmask_value()
{
    return 0x1;
}

Modifier::Builder::Builder()
        : mpObject(new Modifier())
{
}

Modifier::Builder::Builder(const Modifier& object)
        : mpObject(new Modifier())
{
    *(Modifier*)mpObject = object;
}

Modifier::Builder::Builder(ModifierRPtr pObject)
        : mpObject(pObject)
{
}

Modifier::Builder::~Builder()
{
    delete (ModifierRPtr)mpObject;
    mpObject = NULL;
}

const Modifier& Modifier::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(ModifierRPtr)mpObject;
}

ModifierSPtr Modifier::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    ModifierRPtr objectRPtr = (ModifierRPtr)mpObject;
    mpObject = NULL;
    return ModifierSPtr(objectRPtr);
}

Modifier::Modifier()
        : mBits(0)
{
}

Modifier::~Modifier()
{
}

bool Modifier::isInitialized() const
{
    return true;
}

bool Modifier::isVoid() const
{
    if (exist_value()) return false;
    return true;
}

const std::string& Modifier::value() const
{
    BOOST_ASSERT(exist_value());
    return mValue;
}

bool Modifier::exist_value() const
{
    return (mBits & bitmask_value()) != 0;
}

Modifier::Builder& Modifier::Builder::set_value(const std::string& value)
{
    mpObject->mValue  = value;
    mpObject->mBits  |= bitmask_value();
    return *this;
}

std::string& Modifier::Builder::mutable_value()
{
    mpObject->mBits |= bitmask_value();
    return mpObject->mValue;
}

void Modifier::Builder::clear_value()
{
    mpObject->mValue.clear();
    mpObject->mBits &= ~bitmask_value();
}

ModifierSPtr CreateModifier(const std::string& value)
{
    Modifier::Builder builder;
    builder.set_value(value);
    return builder.finalize();
}

