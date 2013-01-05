#include "language/c++/declaration/type_specifier.h"

namespace lang
{

namespace cpp
{

TypeSpecifier::TypeSpecifier()
{
}

TypeSpecifier::~TypeSpecifier()
{
}

TypeSpecifierSPtr TypeSpecifier::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<TypeSpecifier>(object);
}

}

}

