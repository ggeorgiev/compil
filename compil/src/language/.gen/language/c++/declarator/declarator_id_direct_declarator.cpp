// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declarator/declarator_id_direct_declarator.h"

namespace lang
{

namespace cpp
{

DeclaratorIdDirectDeclarator::DeclaratorIdDirectDeclarator()
{
}

DeclaratorIdDirectDeclarator::~DeclaratorIdDirectDeclarator()
{
}

DeclaratorIdDirectDeclaratorSPtr DeclaratorIdDirectDeclarator::downcast(const DeclaratorSPtr& object)
{
    return boost::static_pointer_cast<DeclaratorIdDirectDeclarator>(object);
}

const DeclaratorIdSPtr& DeclaratorIdDirectDeclarator::declarator() const
{
    return mDeclarator;
}

DeclaratorIdDirectDeclarator& DeclaratorIdDirectDeclarator::set_declarator(const DeclaratorIdSPtr& declarator)
{
    mDeclarator = declarator;
    return *this;
}

DeclaratorIdDirectDeclarator& DeclaratorIdDirectDeclarator::operator<<(const DeclaratorIdSPtr& declarator)
{
    return set_declarator(declarator);
}

const DeclaratorIdDirectDeclaratorSPtr& operator<<(const DeclaratorIdDirectDeclaratorSPtr& object,
                                                   const DeclaratorIdSPtr& declarator)
{
    BOOST_ASSERT(object);
    *object << declarator;
    return object;
}

}

}

