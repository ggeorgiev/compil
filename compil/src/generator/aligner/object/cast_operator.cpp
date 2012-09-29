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

const NamespaceSPtr& CastOperator::namespace_() const
{
    return mNamespace;
}

CastOperator& CastOperator::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

CastOperator& CastOperator::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const CastOperatorSPtr& operator<<(const CastOperatorSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

const EMethodDeclaration& CastOperator::declaration() const
{
    return mDeclaration;
}

CastOperator& CastOperator::set_declaration(const EMethodDeclaration& declaration)
{
    mDeclaration = declaration;
    return *this;
}

EMethodDeclaration& CastOperator::mutable_declaration()
{
    return mDeclaration;
}

CastOperator& CastOperator::operator<<(const EMethodDeclaration& declaration)
{
    return set_declaration(declaration);
}

const CastOperatorSPtr& operator<<(const CastOperatorSPtr& object, const EMethodDeclaration& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

