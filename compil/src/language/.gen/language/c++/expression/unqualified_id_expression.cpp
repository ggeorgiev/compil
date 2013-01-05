// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/unqualified_id_expression.h"

namespace lang
{

namespace cpp
{

UnqualifiedIdExpression::UnqualifiedIdExpression()
{
}

UnqualifiedIdExpression::~UnqualifiedIdExpression()
{
}

UnqualifiedIdExpressionSPtr UnqualifiedIdExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<UnqualifiedIdExpression>(object);
}

const UnqualifiedIdSPtr& UnqualifiedIdExpression::unqualifiedId() const
{
    return mUnqualifiedId;
}

UnqualifiedIdExpression& UnqualifiedIdExpression::set_unqualifiedId(const UnqualifiedIdSPtr& unqualifiedId)
{
    mUnqualifiedId = unqualifiedId;
    return *this;
}

UnqualifiedIdExpression& UnqualifiedIdExpression::operator<<(const UnqualifiedIdSPtr& unqualifiedId)
{
    return set_unqualifiedId(unqualifiedId);
}

const UnqualifiedIdExpressionSPtr& operator<<(const UnqualifiedIdExpressionSPtr& object,
                                              const UnqualifiedIdSPtr& unqualifiedId)
{
    BOOST_ASSERT(object);
    *object << unqualifiedId;
    return object;
}

}

}

