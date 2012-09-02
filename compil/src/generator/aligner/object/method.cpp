#include "method.h"

Method::Method()
{
}

Method::~Method()
{
}

const EMethodSpecifier& Method::specifier() const
{
    return mSpecifier;
}

Method& Method::set_specifier(const EMethodSpecifier& specifier)
{
    mSpecifier = specifier;
    return *this;
}

Method& Method::operator<<(const EMethodSpecifier& specifier)
{
    return set_specifier(specifier);
}

const MethodNameSPtr& Method::name() const
{
    return mName;
}

Method& Method::set_name(const MethodNameSPtr& name)
{
    mName = name;
    return *this;
}

Method& Method::operator<<(const MethodNameSPtr& name)
{
    return set_name(name);
}

const NamespaceSPtr& Method::namespace_() const
{
    return mNamespace;
}

Method& Method::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

Method& Method::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

