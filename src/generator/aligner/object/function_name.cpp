// Boost C++ Utility
#include <boost/assert.hpp>

#include "function_name.h"
// Standard C Library
#include <stddef.h>

int FunctionName::bitmask_value()
{
    return 0x1;
}

FunctionName::Builder::Builder()
        : mpObject(new FunctionName())
{
}

FunctionName::Builder::Builder(const FunctionName& object)
        : mpObject(new FunctionName())
{
    *(FunctionName*)mpObject = object;
}

FunctionName::Builder::Builder(FunctionNameRPtr pObject)
        : mpObject(pObject)
{
}

FunctionName::Builder::~Builder()
{
    delete (FunctionNameRPtr)mpObject;
    mpObject = NULL;
}

const FunctionName& FunctionName::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(FunctionNameRPtr)mpObject;
}

FunctionNameSPtr FunctionName::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    FunctionNameRPtr objectRPtr = (FunctionNameRPtr)mpObject;
    mpObject = NULL;
    return FunctionNameSPtr(objectRPtr);
}

FunctionName::FunctionName()
        : mBits(0)
{
}

FunctionName::~FunctionName()
{
}

bool FunctionName::isInitialized() const
{
    return true;
}

bool FunctionName::isVoid() const
{
    if (exist_value()) return false;
    return true;
}

const std::string& FunctionName::value() const
{
    BOOST_ASSERT(exist_value());
    return mValue;
}

bool FunctionName::exist_value() const
{
    return (mBits & bitmask_value()) != 0;
}

FunctionName::Builder& FunctionName::Builder::set_value(const std::string& value)
{
    mpObject->mValue  = value;
    mpObject->mBits  |= bitmask_value();
    return *this;
}

std::string& FunctionName::Builder::mutable_value()
{
    mpObject->mBits |= bitmask_value();
    return mpObject->mValue;
}

void FunctionName::Builder::clear_value()
{
    mpObject->mValue.clear();
    mpObject->mBits &= ~bitmask_value();
}

FunctionNameSPtr CreateFunctionName(const std::string& value)
{
    FunctionName::Builder builder;
    builder.set_value(value);
    return builder.finalize();
}

