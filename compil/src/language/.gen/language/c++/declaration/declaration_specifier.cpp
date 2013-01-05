#include "language/c++/declaration/declaration_specifier.h"

namespace lang
{

namespace cpp
{

DeclarationSpecifier::DeclarationSpecifier()
{
}

DeclarationSpecifier::~DeclarationSpecifier()
{
}

DeclarationSpecifierSPtr DeclarationSpecifier::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<DeclarationSpecifier>(object);
}

}

}

