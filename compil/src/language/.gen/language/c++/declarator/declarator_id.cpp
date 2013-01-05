// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declarator/declarator_id.h"

namespace lang
{

namespace cpp
{

DeclaratorId::DeclaratorId()
{
}

DeclaratorId::~DeclaratorId()
{
}

DeclaratorIdSPtr DeclaratorId::downcast(const DeclaratorSPtr& object)
{
    return boost::static_pointer_cast<DeclaratorId>(object);
}

const TypeNameSPtr& DeclaratorId::typeName() const
{
    return mTypeName;
}

DeclaratorId& DeclaratorId::set_typeName(const TypeNameSPtr& typeName)
{
    mTypeName = typeName;
    return *this;
}

DeclaratorId& DeclaratorId::operator<<(const TypeNameSPtr& typeName)
{
    return set_typeName(typeName);
}

const DeclaratorIdSPtr& operator<<(const DeclaratorIdSPtr& object, const TypeNameSPtr& typeName)
{
    BOOST_ASSERT(object);
    *object << typeName;
    return object;
}

}

}

