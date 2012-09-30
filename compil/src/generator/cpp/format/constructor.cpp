// Boost C++ Utility
#include <boost/assert.hpp>

#include "constructor.h"

namespace cpp
{

namespace frm
{

Constructor::Constructor()
{
}

Constructor::~Constructor()
{
}

const EConstructorSpecifier& Constructor::specifier() const
{
    return mSpecifier;
}

Constructor& Constructor::set_specifier(const EConstructorSpecifier& specifier)
{
    mSpecifier = specifier;
    return *this;
}

EConstructorSpecifier& Constructor::mutable_specifier()
{
    return mSpecifier;
}

Constructor& Constructor::operator<<(const EConstructorSpecifier& specifier)
{
    return set_specifier(specifier);
}

const ConstructorSPtr& operator<<(const ConstructorSPtr& object, const EConstructorSpecifier& specifier)
{
    BOOST_ASSERT(object);
    *object << specifier;
    return object;
}

const NamespaceSPtr& Constructor::namespace_() const
{
    return mNamespace;
}

Constructor& Constructor::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

Constructor& Constructor::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const ConstructorSPtr& operator<<(const ConstructorSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

const ConstructorNameSPtr& Constructor::name() const
{
    return mName;
}

Constructor& Constructor::set_name(const ConstructorNameSPtr& name)
{
    mName = name;
    return *this;
}

Constructor& Constructor::operator<<(const ConstructorNameSPtr& name)
{
    return set_name(name);
}

const ConstructorSPtr& operator<<(const ConstructorSPtr& object, const ConstructorNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<ArgumentSPtr>& Constructor::arguments() const
{
    return mArguments;
}

Constructor& Constructor::set_arguments(const std::vector<ArgumentSPtr>& arguments)
{
    mArguments = arguments;
    return *this;
}

std::vector<ArgumentSPtr>& Constructor::mutable_arguments()
{
    return mArguments;
}

Constructor& Constructor::operator<<(const std::vector<ArgumentSPtr>& arguments)
{
    return set_arguments(arguments);
}

const ConstructorSPtr& operator<<(const ConstructorSPtr& object, const std::vector<ArgumentSPtr>& arguments)
{
    BOOST_ASSERT(object);
    *object << arguments;
    return object;
}

Constructor& Constructor::operator<<(const ArgumentSPtr& argumentsItem)
{
    mArguments.push_back(argumentsItem);
    return *this;
}

const ConstructorSPtr& operator<<(const ConstructorSPtr& object, const ArgumentSPtr& argumentsItem)
{
    BOOST_ASSERT(object);
    *object << argumentsItem;
    return object;
}

}

}

