#include "language/c++/declaration/type_name.h"

namespace lang
{

namespace cpp
{

TypeName::TypeName()
{
}

TypeName::~TypeName()
{
}

TypeNameSPtr TypeName::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<TypeName>(object);
}

}

}

