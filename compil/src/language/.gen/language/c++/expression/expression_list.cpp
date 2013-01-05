// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/expression_list.h"

namespace lang
{

namespace cpp
{

ExpressionList::ExpressionList()
{
}

ExpressionList::~ExpressionList()
{
}

ExpressionListSPtr ExpressionList::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<ExpressionList>(object);
}

const std::vector<ExpressionSPtr>& ExpressionList::expressions() const
{
    return mExpressions;
}

ExpressionList& ExpressionList::set_expressions(const std::vector<ExpressionSPtr>& expressions)
{
    mExpressions = expressions;
    return *this;
}

std::vector<ExpressionSPtr>& ExpressionList::mutable_expressions()
{
    return mExpressions;
}

ExpressionList& ExpressionList::operator<<(const std::vector<ExpressionSPtr>& expressions)
{
    return set_expressions(expressions);
}

const ExpressionListSPtr& operator<<(const ExpressionListSPtr& object, const std::vector<ExpressionSPtr>& expressions)
{
    BOOST_ASSERT(object);
    *object << expressions;
    return object;
}

ExpressionList& ExpressionList::operator<<(const ExpressionSPtr& expressionsItem)
{
    mExpressions.push_back(expressionsItem);
    return *this;
}

const ExpressionListSPtr& operator<<(const ExpressionListSPtr& object, const ExpressionSPtr& expressionsItem)
{
    BOOST_ASSERT(object);
    *object << expressionsItem;
    return object;
}

}

}

