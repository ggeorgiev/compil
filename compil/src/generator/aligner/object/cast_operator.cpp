// Boost C++ Utility
#include <boost/assert.hpp>

#include "cast_operator.h"

CastOperator::CastOperator()
{
}

CastOperator::~CastOperator()
{
}

const DecoratedTypeSPtr& CastOperator::type() const
{
    return mType;
}

CastOperator& CastOperator::set_type(const DecoratedTypeSPtr& type)
{
    mType = type;
    return *this;
}

CastOperator& CastOperator::operator<<(const DecoratedTypeSPtr& type)
{
    return set_type(type);
}

const CastOperatorSPtr& operator<<(const CastOperatorSPtr& object, const DecoratedTypeSPtr& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

