#include "constructor.h"

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

ConstructorSPtr& operator<<(ConstructorSPtr& object, const EConstructorSpecifier& specifier)
{
    if (!object)
        object.reset(new Constructor());
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

ConstructorSPtr& operator<<(ConstructorSPtr& object, const NamespaceSPtr& namespace_)
{
    if (!object)
        object.reset(new Constructor());
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

ConstructorSPtr& operator<<(ConstructorSPtr& object, const ConstructorNameSPtr& name)
{
    if (!object)
        object.reset(new Constructor());
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

ConstructorSPtr& operator<<(ConstructorSPtr& object, const std::vector<ArgumentSPtr>& arguments)
{
    if (!object)
        object.reset(new Constructor());
    *object << arguments;
    return object;
}

Constructor& Constructor::operator<<(const ArgumentSPtr& argumentsItem)
{
    mArguments.push_back(argumentsItem);
    return *this;
}

ConstructorSPtr& operator<<(ConstructorSPtr& object, const ArgumentSPtr& argumentsItem)
{
    if (!object)
        object.reset(new Constructor());
    *object << argumentsItem;
    return object;
}

