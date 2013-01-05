// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/parentheses_postfix_expression.h"

namespace lang
{

namespace cpp
{

ParenthesesPostfixExpression::ParenthesesPostfixExpression()
{
}

ParenthesesPostfixExpression::~ParenthesesPostfixExpression()
{
}

ParenthesesPostfixExpressionSPtr ParenthesesPostfixExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<ParenthesesPostfixExpression>(object);
}

const PostfixExpressionSPtr& ParenthesesPostfixExpression::expression() const
{
    return mExpression;
}

ParenthesesPostfixExpression& ParenthesesPostfixExpression::set_expression(const PostfixExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

ParenthesesPostfixExpression& ParenthesesPostfixExpression::operator<<(const PostfixExpressionSPtr& expression)
{
    return set_expression(expression);
}

const ParenthesesPostfixExpressionSPtr& operator<<(const ParenthesesPostfixExpressionSPtr& object,
                                                   const PostfixExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

const ExpressionListSPtr& ParenthesesPostfixExpression::list() const
{
    return mList;
}

ParenthesesPostfixExpression& ParenthesesPostfixExpression::set_list(const ExpressionListSPtr& list)
{
    mList = list;
    return *this;
}

ParenthesesPostfixExpression& ParenthesesPostfixExpression::operator<<(const ExpressionListSPtr& list)
{
    return set_list(list);
}

const ParenthesesPostfixExpressionSPtr& operator<<(const ParenthesesPostfixExpressionSPtr& object,
                                                   const ExpressionListSPtr& list)
{
    BOOST_ASSERT(object);
    *object << list;
    return object;
}

}

}

