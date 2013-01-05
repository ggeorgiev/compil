// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/class/class.h"

namespace lang
{

namespace cpp
{

Class::Class()
{
}

Class::~Class()
{
}

const NamespaceSPtr& Class::namespace_() const
{
    return mNamespace;
}

Class& Class::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

Class& Class::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const ClassSPtr& operator<<(const ClassSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

const ClassSPtr& Class::containerClass() const
{
    return mContainerClass;
}

Class& Class::set_containerClass(const ClassSPtr& containerClass)
{
    mContainerClass = containerClass;
    return *this;
}

Class& Class::operator<<(const ClassSPtr& containerClass)
{
    return set_containerClass(containerClass);
}

const ClassSPtr& operator<<(const ClassSPtr& object, const ClassSPtr& containerClass)
{
    BOOST_ASSERT(object);
    *object << containerClass;
    return object;
}

const ClassNameSPtr& Class::name() const
{
    return mName;
}

Class& Class::set_name(const ClassNameSPtr& name)
{
    mName = name;
    return *this;
}

Class& Class::operator<<(const ClassNameSPtr& name)
{
    return set_name(name);
}

const ClassSPtr& operator<<(const ClassSPtr& object, const ClassNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

}

}

