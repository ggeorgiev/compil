// Boost C++ Utility
#include <boost/assert.hpp>

#include "decoration.h"
// Standard C Library
#include <stddef.h>

int Decoration::bitmask_value()
{
    return 0x1;
}

Decoration::Builder::Builder()
        : mpObject(new Decoration())
{
}

Decoration::Builder::Builder(const Decoration& object)
        : mpObject(new Decoration())
{
    *(Decoration*)mpObject = object;
}

Decoration::Builder::Builder(DecorationRPtr pObject)
        : mpObject(pObject)
{
}

Decoration::Builder::~Builder()
{
    delete (DecorationRPtr)mpObject;
    mpObject = NULL;
}

const Decoration& Decoration::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(DecorationRPtr)mpObject;
}

DecorationSPtr Decoration::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    DecorationRPtr objectRPtr = (DecorationRPtr)mpObject;
    mpObject = NULL;
    return DecorationSPtr(objectRPtr);
}

Decoration::Decoration()
        : mBits(0)
{
}

Decoration::~Decoration()
{
}

bool Decoration::isInitialized() const
{
    return true;
}

bool Decoration::isVoid() const
{
    if (exist_value()) return false;
    return true;
}

const std::string& Decoration::value() const
{
    BOOST_ASSERT(exist_value());
    return mValue;
}

bool Decoration::exist_value() const
{
    return (mBits & bitmask_value()) != 0;
}

Decoration::Builder& Decoration::Builder::set_value(const std::string& value)
{
    mpObject->mValue  = value;
    mpObject->mBits  |= bitmask_value();
    return *this;
}

std::string& Decoration::Builder::mutable_value()
{
    mpObject->mBits |= bitmask_value();
    return mpObject->mValue;
}

void Decoration::Builder::clear_value()
{
    mpObject->mValue.clear();
    mpObject->mBits &= ~bitmask_value();
}

DecorationSPtr CreateDecoration(const std::string& value)
{
    Decoration::Builder builder;
    builder.set_value(value);
    return builder.finalize();
}

