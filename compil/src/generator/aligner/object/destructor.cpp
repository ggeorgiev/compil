#include "destructor.h"

Destructor::Destructor()
{
}

Destructor::~Destructor()
{
}

const EDestructorSpecifier& Destructor::specifier() const
{
    return mSpecifier;
}

Destructor& Destructor::set_specifier(const EDestructorSpecifier& specifier)
{
    mSpecifier = specifier;
    return *this;
}

Destructor& Destructor::operator<<(const EDestructorSpecifier& specifier)
{
    return set_specifier(specifier);
}

const DestructorNameSPtr& Destructor::name() const
{
    return mName;
}

Destructor& Destructor::set_name(const DestructorNameSPtr& name)
{
    mName = name;
    return *this;
}

Destructor& Destructor::operator<<(const DestructorNameSPtr& name)
{
    return set_name(name);
}

const NamespaceSPtr& Destructor::namespace_() const
{
    return mNamespace;
}

Destructor& Destructor::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

Destructor& Destructor::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

