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

EDestructorSpecifier& Destructor::mutable_specifier()
{
    return mSpecifier;
}

Destructor& Destructor::operator<<(const EDestructorSpecifier& specifier)
{
    return set_specifier(specifier);
}

DestructorSPtr& operator<<(DestructorSPtr& object, const EDestructorSpecifier& specifier)
{
    if (!object)
        object.reset(new Destructor());
    *object << specifier;
    return object;
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

DestructorSPtr& operator<<(DestructorSPtr& object, const DestructorNameSPtr& name)
{
    if (!object)
        object.reset(new Destructor());
    *object << name;
    return object;
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

DestructorSPtr& operator<<(DestructorSPtr& object, const NamespaceSPtr& namespace_)
{
    if (!object)
        object.reset(new Destructor());
    *object << namespace_;
    return object;
}

