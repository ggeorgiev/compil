#include "language/c++/declarator/direct_declarator.h"

namespace lang
{

namespace cpp
{

DirectDeclarator::DirectDeclarator()
{
}

DirectDeclarator::~DirectDeclarator()
{
}

DirectDeclaratorSPtr DirectDeclarator::downcast(const DeclaratorSPtr& object)
{
    return boost::static_pointer_cast<DirectDeclarator>(object);
}

}

}

