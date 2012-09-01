// Boost C++ Utility
#include <boost/assert.hpp>

#include "namespace.h"

namespace lang
{

namespace cpp
{

int Namespace::bitmask_names()
{
    return 0x1;
}

Namespace::Namespace()
        : mBits(0)
{
}

Namespace::~Namespace()
{
}

bool Namespace::isInitialized() const
{
    return true;
}

bool Namespace::isVoid() const
{
    if (exist_names()) return false;
    return true;
}

const std::vector<NamespaceNameSPtr>& Namespace::names() const
{
    BOOST_ASSERT(exist_names());
    return mNames;
}

bool Namespace::exist_names() const
{
    return (mBits & bitmask_names()) != 0;
}

Namespace& Namespace::set_names(const std::vector<NamespaceNameSPtr>& names)
{
    mNames  = names;
    mBits  |= bitmask_names();
    return *this;
}

Namespace& Namespace::operator<<(const std::vector<NamespaceNameSPtr>& names)
{
    return set_names(names);
}

Namespace& Namespace::operator<<(const NamespaceNameSPtr& namesItem)
{
    mBits |= bitmask_names();
    mNames.push_back(namesItem);
    return *this;
}

std::vector<NamespaceNameSPtr>& Namespace::mutable_names()
{
    mBits |= bitmask_names();
    return mNames;
}

void Namespace::clear_names()
{
    mNames.clear();
    mBits &= ~bitmask_names();
}

}

}

