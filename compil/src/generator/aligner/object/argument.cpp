// Boost C++ Utility
#include <boost/assert.hpp>

#include "argument.h"
// Standard C Library
#include <stddef.h>

int Argument::bitmask_type()
{
    return 0x1;
}

int Argument::bitmask_name()
{
    return 0x2;
}

Argument::Builder::Builder()
        : mpObject(new Argument())
{
}

Argument::Builder::Builder(const Argument& object)
        : mpObject(new Argument())
{
    *(Argument*)mpObject = object;
}

Argument::Builder::Builder(ArgumentRPtr pObject)
        : mpObject(pObject)
{
}

Argument::Builder::~Builder()
{
    delete (ArgumentRPtr)mpObject;
    mpObject = NULL;
}

const Argument& Argument::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(ArgumentRPtr)mpObject;
}

ArgumentSPtr Argument::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    ArgumentRPtr objectRPtr = (ArgumentRPtr)mpObject;
    mpObject = NULL;
    return ArgumentSPtr(objectRPtr);
}

Argument::Argument()
        : mBits(0)
{
}

Argument::~Argument()
{
}

bool Argument::isInitialized() const
{
    return true;
}

bool Argument::isVoid() const
{
    if (exist_type()) return false;
    if (exist_name()) return false;
    return true;
}

const DecoratedTypeSPtr& Argument::type() const
{
    BOOST_ASSERT(exist_type());
    return mType;
}

bool Argument::exist_type() const
{
    return (mBits & bitmask_type()) != 0;
}

Argument::Builder& Argument::Builder::set_type(const DecoratedTypeSPtr& type)
{
    mpObject->mType  = type;
    mpObject->mBits |= bitmask_type();
    return *this;
}

void Argument::Builder::clear_type()
{
    mpObject->mType.reset();
    mpObject->mBits &= ~bitmask_type();
}

const VariableNameSPtr& Argument::name() const
{
    BOOST_ASSERT(exist_name());
    return mName;
}

bool Argument::exist_name() const
{
    return (mBits & bitmask_name()) != 0;
}

Argument::Builder& Argument::Builder::set_name(const VariableNameSPtr& name)
{
    mpObject->mName  = name;
    mpObject->mBits |= bitmask_name();
    return *this;
}

void Argument::Builder::clear_name()
{
    mpObject->mName.reset();
    mpObject->mBits &= ~bitmask_name();
}

ArgumentSPtr CreateArgument(const DecoratedTypeSPtr& type)
{
    Argument::Builder builder;
    builder.set_type(type);
    return builder.finalize();
}

ArgumentSPtr CreateArgument(const VariableNameSPtr& name)
{
    Argument::Builder builder;
    builder.set_name(name);
    return builder.finalize();
}

ArgumentSPtr CreateArgument(const DecoratedTypeSPtr& type, const VariableNameSPtr& name)
{
    Argument::Builder builder;
    builder.set_type(type);
    builder.set_name(name);
    return builder.finalize();
}

