#include "language/c++/expression/unqualified_id.h"

namespace lang
{

namespace cpp
{

UnqualifiedId::UnqualifiedId()
{
}

UnqualifiedId::~UnqualifiedId()
{
}

UnqualifiedIdSPtr UnqualifiedId::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<UnqualifiedId>(object);
}

}

}

