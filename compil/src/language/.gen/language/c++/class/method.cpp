// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/class/method.h"

namespace lang
{

namespace cpp
{

Method::Method()
{
}

Method::~Method()
{
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

const MethodSPtr& operator<<(const MethodSPtr& object, const MethodNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const ClassWPtr& Method::class_() const
{
    return mClass;
}

Method& Method::set_class(const ClassSPtr& class_)
{
    mClass = class_;
    return *this;
}

Method& Method::operator<<(const ClassSPtr& class_)
{
    return set_class(class_);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const ClassSPtr& class_)
{
    BOOST_ASSERT(object);
    *object << class_;
    return object;
}

}

}

