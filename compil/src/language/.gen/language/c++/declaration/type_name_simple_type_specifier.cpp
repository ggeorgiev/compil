// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/type_name_simple_type_specifier.h"

namespace lang
{

namespace cpp
{

TypeNameSimpleTypeSpecifier::TypeNameSimpleTypeSpecifier()
{
}

TypeNameSimpleTypeSpecifier::~TypeNameSimpleTypeSpecifier()
{
}

TypeNameSimpleTypeSpecifierSPtr TypeNameSimpleTypeSpecifier::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<TypeNameSimpleTypeSpecifier>(object);
}

const NestedNameSpecifierSPtr& TypeNameSimpleTypeSpecifier::specifier() const
{
    return mSpecifier;
}

TypeNameSimpleTypeSpecifier& TypeNameSimpleTypeSpecifier::set_specifier(const NestedNameSpecifierSPtr& specifier)
{
    mSpecifier = specifier;
    return *this;
}

TypeNameSimpleTypeSpecifier& TypeNameSimpleTypeSpecifier::operator<<(const NestedNameSpecifierSPtr& specifier)
{
    return set_specifier(specifier);
}

const TypeNameSimpleTypeSpecifierSPtr& operator<<(const TypeNameSimpleTypeSpecifierSPtr& object,
                                                  const NestedNameSpecifierSPtr& specifier)
{
    BOOST_ASSERT(object);
    *object << specifier;
    return object;
}

const TypeNameSPtr& TypeNameSimpleTypeSpecifier::typeName() const
{
    return mTypeName;
}

TypeNameSimpleTypeSpecifier& TypeNameSimpleTypeSpecifier::set_typeName(const TypeNameSPtr& typeName)
{
    mTypeName = typeName;
    return *this;
}

TypeNameSimpleTypeSpecifier& TypeNameSimpleTypeSpecifier::operator<<(const TypeNameSPtr& typeName)
{
    return set_typeName(typeName);
}

const TypeNameSimpleTypeSpecifierSPtr& operator<<(const TypeNameSimpleTypeSpecifierSPtr& object,
                                                  const TypeNameSPtr& typeName)
{
    BOOST_ASSERT(object);
    *object << typeName;
    return object;
}

}

}

