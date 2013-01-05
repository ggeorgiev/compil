// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/class_type_name.h"

namespace lang
{

namespace cpp
{

ClassTypeName::ClassTypeName()
{
}

ClassTypeName::~ClassTypeName()
{
}

ClassTypeNameSPtr ClassTypeName::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<ClassTypeName>(object);
}

const IdentifierClassNameSPtr& ClassTypeName::className() const
{
    return mClassName;
}

ClassTypeName& ClassTypeName::set_className(const IdentifierClassNameSPtr& className)
{
    mClassName = className;
    return *this;
}

ClassTypeName& ClassTypeName::operator<<(const IdentifierClassNameSPtr& className)
{
    return set_className(className);
}

const ClassTypeNameSPtr& operator<<(const ClassTypeNameSPtr& object, const IdentifierClassNameSPtr& className)
{
    BOOST_ASSERT(object);
    *object << className;
    return object;
}

}

}

