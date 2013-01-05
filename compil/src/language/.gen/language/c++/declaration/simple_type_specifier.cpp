#include "language/c++/declaration/simple_type_specifier.h"

namespace lang
{

namespace cpp
{

SimpleTypeSpecifier::SimpleTypeSpecifier()
{
}

SimpleTypeSpecifier::~SimpleTypeSpecifier()
{
}

SimpleTypeSpecifierSPtr SimpleTypeSpecifier::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<SimpleTypeSpecifier>(object);
}

}

}

