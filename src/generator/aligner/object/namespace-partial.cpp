// Boost C++ Utility
#include <boost/assert.hpp>

#include "namespace.h"
// Standard C Library
#include <stddef.h>

int NamespacePartial::bitmask_value()
{
    return 0x1;
}

NamespacePartial::Builder::Builder()
        : mpObject(new Namespace())
{
}

NamespacePartial::Builder::Builder(const Namespace& object)
        : mpObject(new Namespace())
{
    *(Namespace*)mpObject = object;
}

NamespacePartial::Builder::Builder(NamespaceRPtr pObject)
        : mpObject(pObject)
{
}

NamespacePartial::Builder::~Builder()
{
    delete (NamespaceRPtr)mpObject;
    mpObject = NULL;
}

const Namespace& NamespacePartial::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(NamespaceRPtr)mpObject;
}

NamespaceSPtr NamespacePartial::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    NamespaceRPtr objectRPtr = (NamespaceRPtr)mpObject;
    mpObject = NULL;
    return NamespaceSPtr(objectRPtr);
}

NamespacePartial::NamespacePartial()
        : mBits(0)
{
}

NamespacePartial::~NamespacePartial()
{
}

bool NamespacePartial::isInitialized() const
{
    return true;
}

bool NamespacePartial::isVoid() const
{
    if (exist_value()) return false;
    return true;
}

const std::string& NamespacePartial::value() const
{
    BOOST_ASSERT(exist_value());
    return mValue;
}

bool NamespacePartial::exist_value() const
{
    return (mBits & bitmask_value()) != 0;
}

NamespacePartial::Builder& NamespacePartial::Builder::set_value(const std::string& value)
{
    mpObject->mValue  = value;
    mpObject->mBits  |= bitmask_value();
    return *this;
}

std::string& NamespacePartial::Builder::mutable_value()
{
    mpObject->mBits |= bitmask_value();
    return mpObject->mValue;
}

void NamespacePartial::Builder::clear_value()
{
    mpObject->mValue.clear();
    mpObject->mBits &= ~bitmask_value();
}

NamespaceSPtr CreateNamespace(const std::string& value)
{
    Namespace::Builder builder;
    builder.set_value(value);
    return builder.finalize();
}

