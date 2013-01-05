// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/class_declaration.h"

namespace lang
{

namespace cpp
{

ClassDeclaration::ClassDeclaration()
{
}

ClassDeclaration::~ClassDeclaration()
{
}

ClassDeclarationSPtr ClassDeclaration::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<ClassDeclaration>(object);
}

const ClassSPtr& ClassDeclaration::class_() const
{
    return mClass;
}

ClassDeclaration& ClassDeclaration::set_class(const ClassSPtr& class_)
{
    mClass = class_;
    return *this;
}

ClassDeclaration& ClassDeclaration::operator<<(const ClassSPtr& class_)
{
    return set_class(class_);
}

const ClassDeclarationSPtr& operator<<(const ClassDeclarationSPtr& object, const ClassSPtr& class_)
{
    BOOST_ASSERT(object);
    *object << class_;
    return object;
}

}

}

