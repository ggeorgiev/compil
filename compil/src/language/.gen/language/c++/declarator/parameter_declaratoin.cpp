#include "language/c++/declarator/parameter_declaratoin.h"

namespace lang
{

namespace cpp
{

ParameterDeclaration::ParameterDeclaration()
{
}

ParameterDeclaration::~ParameterDeclaration()
{
}

ParameterDeclarationSPtr ParameterDeclaration::downcast(const DeclaratorSPtr& object)
{
    return boost::static_pointer_cast<ParameterDeclaration>(object);
}

}

}

