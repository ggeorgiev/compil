// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/expression_statement.h"

namespace lang
{

namespace cpp
{

ExpressionStatement::ExpressionStatement()
{
}

ExpressionStatement::~ExpressionStatement()
{
}

ExpressionStatementSPtr ExpressionStatement::downcast(const StatementSPtr& object)
{
    return boost::static_pointer_cast<ExpressionStatement>(object);
}

const ExpressionSPtr& ExpressionStatement::expression() const
{
    return mExpression;
}

ExpressionStatement& ExpressionStatement::set_expression(const ExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

ExpressionStatement& ExpressionStatement::operator<<(const ExpressionSPtr& expression)
{
    return set_expression(expression);
}

const ExpressionStatementSPtr& operator<<(const ExpressionStatementSPtr& object, const ExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

ExpressionStatement& ExpressionStatement::set_close(const EClose& close)
{
    Statement::set_close(close);
    return *this;
}

ExpressionStatement& ExpressionStatement::operator<<(const EClose& close)
{
    *(Statement*)this << close;
    return *this;
}

const ExpressionStatementSPtr& operator<<(const ExpressionStatementSPtr& object, const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

