// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/throw_test_statement.h"

namespace lang
{

namespace cpp
{

ThrowTestStatement::ThrowTestStatement()
{
}

ThrowTestStatement::~ThrowTestStatement()
{
}

ThrowTestStatementSPtr ThrowTestStatement::downcast(const StatementSPtr& object)
{
    return boost::static_pointer_cast<ThrowTestStatement>(object);
}

const ExpressionSPtr& ThrowTestStatement::expression() const
{
    return mExpression;
}

ThrowTestStatement& ThrowTestStatement::set_expression(const ExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

ThrowTestStatement& ThrowTestStatement::operator<<(const ExpressionSPtr& expression)
{
    return set_expression(expression);
}

const ThrowTestStatementSPtr& operator<<(const ThrowTestStatementSPtr& object, const ExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

const ClassSPtr& ThrowTestStatement::class_() const
{
    return mClass;
}

ThrowTestStatement& ThrowTestStatement::set_class(const ClassSPtr& class_)
{
    mClass = class_;
    return *this;
}

ThrowTestStatement& ThrowTestStatement::operator<<(const ClassSPtr& class_)
{
    return set_class(class_);
}

const ThrowTestStatementSPtr& operator<<(const ThrowTestStatementSPtr& object, const ClassSPtr& class_)
{
    BOOST_ASSERT(object);
    *object << class_;
    return object;
}

ThrowTestStatement& ThrowTestStatement::set_close(const EClose& close)
{
    Statement::set_close(close);
    return *this;
}

ThrowTestStatement& ThrowTestStatement::operator<<(const EClose& close)
{
    *(Statement*)this << close;
    return *this;
}

const ThrowTestStatementSPtr& operator<<(const ThrowTestStatementSPtr& object, const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

