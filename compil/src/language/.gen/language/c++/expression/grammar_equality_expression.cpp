// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/grammar_equality_expression.h"

namespace lang
{

namespace cpp
{

GrammarEqualityExpression::GrammarEqualityExpression()
{
}

GrammarEqualityExpression::~GrammarEqualityExpression()
{
}

GrammarEqualityExpressionSPtr GrammarEqualityExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<GrammarEqualityExpression>(object);
}

const EqualityExpressionSPtr& GrammarEqualityExpression::first() const
{
    return mFirst;
}

GrammarEqualityExpression& GrammarEqualityExpression::set_first(const EqualityExpressionSPtr& first)
{
    mFirst = first;
    return *this;
}

GrammarEqualityExpression& GrammarEqualityExpression::operator<<(const EqualityExpressionSPtr& first)
{
    return set_first(first);
}

const GrammarEqualityExpressionSPtr& operator<<(const GrammarEqualityExpressionSPtr& object,
                                                const EqualityExpressionSPtr& first)
{
    BOOST_ASSERT(object);
    *object << first;
    return object;
}

const RelationalExpressionSPtr& GrammarEqualityExpression::second() const
{
    return mSecond;
}

GrammarEqualityExpression& GrammarEqualityExpression::set_second(const RelationalExpressionSPtr& second)
{
    mSecond = second;
    return *this;
}

GrammarEqualityExpression& GrammarEqualityExpression::operator<<(const RelationalExpressionSPtr& second)
{
    return set_second(second);
}

const GrammarEqualityExpressionSPtr& operator<<(const GrammarEqualityExpressionSPtr& object,
                                                const RelationalExpressionSPtr& second)
{
    BOOST_ASSERT(object);
    *object << second;
    return object;
}

GrammarEqualityExpression& GrammarEqualityExpression::set_type(const EType& type)
{
    EqualityExpression::set_type(type);
    return *this;
}

GrammarEqualityExpression& GrammarEqualityExpression::operator<<(const EType& type)
{
    *(EqualityExpression*)this << type;
    return *this;
}

const GrammarEqualityExpressionSPtr& operator<<(const GrammarEqualityExpressionSPtr& object,
                                                const EqualityExpression::EType& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

}

}

