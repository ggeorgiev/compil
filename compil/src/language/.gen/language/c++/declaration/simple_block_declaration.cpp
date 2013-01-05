// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/simple_block_declaration.h"

namespace lang
{

namespace cpp
{

SimpleBlockDeclaration::SimpleBlockDeclaration()
{
}

SimpleBlockDeclaration::~SimpleBlockDeclaration()
{
}

SimpleBlockDeclarationSPtr SimpleBlockDeclaration::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<SimpleBlockDeclaration>(object);
}

const SimpleDeclarationSPtr& SimpleBlockDeclaration::declaration() const
{
    return mDeclaration;
}

SimpleBlockDeclaration& SimpleBlockDeclaration::set_declaration(const SimpleDeclarationSPtr& declaration)
{
    mDeclaration = declaration;
    return *this;
}

SimpleBlockDeclaration& SimpleBlockDeclaration::operator<<(const SimpleDeclarationSPtr& declaration)
{
    return set_declaration(declaration);
}

const SimpleBlockDeclarationSPtr& operator<<(const SimpleBlockDeclarationSPtr& object,
                                             const SimpleDeclarationSPtr& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

}

}

