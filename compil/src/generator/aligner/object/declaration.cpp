// Boost C++ Utility
#include <boost/assert.hpp>

#include "declaration.h"
// Standard C Library
#include <stddef.h>

int Declaration::bitmask_value()
{
    return 0x1;
}

Declaration::Builder::Builder()
        : mpObject(new Declaration())
{
}

Declaration::Builder::Builder(const Declaration& object)
        : mpObject(new Declaration())
{
    *(Declaration*)mpObject = object;
}

Declaration::Builder::Builder(DeclarationRPtr pObject)
        : mpObject(pObject)
{
}

Declaration::Builder::~Builder()
{
    delete (DeclarationRPtr)mpObject;
    mpObject = NULL;
}

const Declaration& Declaration::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(DeclarationRPtr)mpObject;
}

DeclarationSPtr Declaration::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    DeclarationRPtr objectRPtr = (DeclarationRPtr)mpObject;
    mpObject = NULL;
    return DeclarationSPtr(objectRPtr);
}

Declaration::Declaration()
        : mBits(0)
{
}

Declaration::~Declaration()
{
}

bool Declaration::isInitialized() const
{
    return true;
}

bool Declaration::isVoid() const
{
    if (exist_value()) return false;
    return true;
}

const std::string& Declaration::value() const
{
    BOOST_ASSERT(exist_value());
    return mValue;
}

bool Declaration::exist_value() const
{
    return (mBits & bitmask_value()) != 0;
}

Declaration::Builder& Declaration::Builder::set_value(const std::string& value)
{
    mpObject->mValue  = value;
    mpObject->mBits  |= bitmask_value();
    return *this;
}

std::string& Declaration::Builder::mutable_value()
{
    mpObject->mBits |= bitmask_value();
    return mpObject->mValue;
}

void Declaration::Builder::clear_value()
{
    mpObject->mValue.clear();
    mpObject->mBits &= ~bitmask_value();
}

DeclarationSPtr CreateDeclaration(const std::string& value)
{
    Declaration::Builder builder;
    builder.set_value(value);
    return builder.finalize();
}

