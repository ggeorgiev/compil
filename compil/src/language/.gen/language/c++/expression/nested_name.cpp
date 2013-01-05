#include "language/c++/expression/nested_name.h"

namespace lang
{

namespace cpp
{

NestedName::NestedName()
{
}

NestedName::~NestedName()
{
}

NestedNameSPtr NestedName::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<NestedName>(object);
}

}

}

