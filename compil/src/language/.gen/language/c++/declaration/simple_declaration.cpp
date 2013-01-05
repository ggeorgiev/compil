// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/simple_declaration.h"

namespace lang
{

namespace cpp
{

SimpleDeclaration::SimpleDeclaration()
{
}

SimpleDeclaration::~SimpleDeclaration()
{
}

SimpleDeclarationSPtr SimpleDeclaration::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<SimpleDeclaration>(object);
}

const DeclarationSpecifierSequenceSPtr& SimpleDeclaration::declaration() const
{
    return mDeclaration;
}

SimpleDeclaration& SimpleDeclaration::set_declaration(const DeclarationSpecifierSequenceSPtr& declaration)
{
    mDeclaration = declaration;
    return *this;
}

SimpleDeclaration& SimpleDeclaration::operator<<(const DeclarationSpecifierSequenceSPtr& declaration)
{
    return set_declaration(declaration);
}

const SimpleDeclarationSPtr& operator<<(const SimpleDeclarationSPtr& object,
                                        const DeclarationSpecifierSequenceSPtr& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

const InitDeclaratorSPtr& SimpleDeclaration::declarator() const
{
    return mDeclarator;
}

SimpleDeclaration& SimpleDeclaration::set_declarator(const InitDeclaratorSPtr& declarator)
{
    mDeclarator = declarator;
    return *this;
}

SimpleDeclaration& SimpleDeclaration::operator<<(const InitDeclaratorSPtr& declarator)
{
    return set_declarator(declarator);
}

const SimpleDeclarationSPtr& operator<<(const SimpleDeclarationSPtr& object, const InitDeclaratorSPtr& declarator)
{
    BOOST_ASSERT(object);
    *object << declarator;
    return object;
}

}

}

