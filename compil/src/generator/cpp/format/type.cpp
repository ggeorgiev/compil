// Boost C++ Utility
#include <boost/assert.hpp>

#include "type.h"

namespace cpp
{

namespace frm
{

Type::Type()
        : mDeclaration(default_declaration())
        , mDecoration (default_decoration())
{
}

Type::~Type()
{
}

const ETypeDeclaration& Type::declaration() const
{
    return mDeclaration;
}

ETypeDeclaration Type::default_declaration()
{
    return ETypeDeclaration::invalid();
}

Type& Type::set_declaration(const ETypeDeclaration& declaration)
{
    mDeclaration = declaration;
    return *this;
}

ETypeDeclaration& Type::mutable_declaration()
{
    return mDeclaration;
}

Type& Type::operator<<(const ETypeDeclaration& declaration)
{
    return set_declaration(declaration);
}

const TypeSPtr& operator<<(const TypeSPtr& object, const ETypeDeclaration& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

const NamespaceSPtr& Type::namespace_() const
{
    return mNamespace;
}

Type& Type::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

Type& Type::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const TypeSPtr& operator<<(const TypeSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

const TypeNameSPtr& Type::name() const
{
    return mName;
}

Type& Type::set_name(const TypeNameSPtr& name)
{
    mName = name;
    return *this;
}

Type& Type::operator<<(const TypeNameSPtr& name)
{
    return set_name(name);
}

const TypeSPtr& operator<<(const TypeSPtr& object, const TypeNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const ETypeDecoration& Type::decoration() const
{
    return mDecoration;
}

ETypeDecoration Type::default_decoration()
{
    return ETypeDecoration::invalid();
}

Type& Type::set_decoration(const ETypeDecoration& decoration)
{
    mDecoration = decoration;
    return *this;
}

ETypeDecoration& Type::mutable_decoration()
{
    return mDecoration;
}

Type& Type::operator<<(const ETypeDecoration& decoration)
{
    return set_decoration(decoration);
}

const TypeSPtr& operator<<(const TypeSPtr& object, const ETypeDecoration& decoration)
{
    BOOST_ASSERT(object);
    *object << decoration;
    return object;
}

}

}

