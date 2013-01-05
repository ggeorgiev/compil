// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declarator/init_declarator.h"

namespace lang
{

namespace cpp
{

InitDeclarator::InitDeclarator()
{
}

InitDeclarator::~InitDeclarator()
{
}

InitDeclaratorSPtr InitDeclarator::downcast(const DeclaratorSPtr& object)
{
    return boost::static_pointer_cast<InitDeclarator>(object);
}

const DeclaratorSPtr& InitDeclarator::declarator() const
{
    return mDeclarator;
}

InitDeclarator& InitDeclarator::set_declarator(const DeclaratorSPtr& declarator)
{
    mDeclarator = declarator;
    return *this;
}

InitDeclarator& InitDeclarator::operator<<(const DeclaratorSPtr& declarator)
{
    return set_declarator(declarator);
}

const InitDeclaratorSPtr& operator<<(const InitDeclaratorSPtr& object, const DeclaratorSPtr& declarator)
{
    BOOST_ASSERT(object);
    *object << declarator;
    return object;
}

}

}

