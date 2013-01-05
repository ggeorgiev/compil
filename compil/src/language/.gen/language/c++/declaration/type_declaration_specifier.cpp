// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/type_declaration_specifier.h"

namespace lang
{

namespace cpp
{

TypeDeclarationSpecifier::TypeDeclarationSpecifier()
{
}

TypeDeclarationSpecifier::~TypeDeclarationSpecifier()
{
}

TypeDeclarationSpecifierSPtr TypeDeclarationSpecifier::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<TypeDeclarationSpecifier>(object);
}

const TypeSpecifierSPtr& TypeDeclarationSpecifier::declaration() const
{
    return mDeclaration;
}

TypeDeclarationSpecifier& TypeDeclarationSpecifier::set_declaration(const TypeSpecifierSPtr& declaration)
{
    mDeclaration = declaration;
    return *this;
}

TypeDeclarationSpecifier& TypeDeclarationSpecifier::operator<<(const TypeSpecifierSPtr& declaration)
{
    return set_declaration(declaration);
}

const TypeDeclarationSpecifierSPtr& operator<<(const TypeDeclarationSpecifierSPtr& object,
                                               const TypeSpecifierSPtr& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

}

}

