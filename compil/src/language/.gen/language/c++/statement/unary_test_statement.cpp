// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/unary_test_statement.h"

namespace lang
{

namespace cpp
{

UnaryTestStatement::UnaryTestStatement()
{
}

UnaryTestStatement::~UnaryTestStatement()
{
}

UnaryTestStatementSPtr UnaryTestStatement::downcast(const StatementSPtr& object)
{
    return boost::static_pointer_cast<UnaryTestStatement>(object);
}

UnaryTestStatement::EType::EType()
        : mValue(kInvalid)
{
}

UnaryTestStatement::EType::EType(long value)
        : mValue(value)
{
}

const UnaryTestStatement::EType UnaryTestStatement::EType::invalid()
{
    return EType(kInvalid);
}

const UnaryTestStatement::EType UnaryTestStatement::EType::isTrue()
{
    return EType(kIsTrue);
}

const UnaryTestStatement::EType UnaryTestStatement::EType::isFalse()
{
    return EType(kIsFalse);
}

long UnaryTestStatement::EType::value() const
{
    return mValue;
}

const char* UnaryTestStatement::EType::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "isTrue",
        "isFalse",
    };
    return names[(size_t)value];
}

const char* UnaryTestStatement::EType::shortName() const
{
    return shortName(value());
}

bool UnaryTestStatement::EType::operator==(const EType& rValue) const
{
    return mValue == rValue.mValue;
}

bool UnaryTestStatement::EType::operator!=(const EType& rValue) const
{
    return mValue != rValue.mValue;
}

const UnaryTestStatement::EType& UnaryTestStatement::type() const
{
    return mType;
}

UnaryTestStatement& UnaryTestStatement::set_type(const EType& type)
{
    mType = type;
    return *this;
}

UnaryTestStatement::EType& UnaryTestStatement::mutable_type()
{
    return mType;
}

UnaryTestStatement& UnaryTestStatement::operator<<(const EType& type)
{
    return set_type(type);
}

const UnaryTestStatementSPtr& operator<<(const UnaryTestStatementSPtr& object, const UnaryTestStatement::EType& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

const ExpressionSPtr& UnaryTestStatement::expression() const
{
    return mExpression;
}

UnaryTestStatement& UnaryTestStatement::set_expression(const ExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

UnaryTestStatement& UnaryTestStatement::operator<<(const ExpressionSPtr& expression)
{
    return set_expression(expression);
}

const UnaryTestStatementSPtr& operator<<(const UnaryTestStatementSPtr& object, const ExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

UnaryTestStatement& UnaryTestStatement::set_close(const EClose& close)
{
    Statement::set_close(close);
    return *this;
}

UnaryTestStatement& UnaryTestStatement::operator<<(const EClose& close)
{
    *(Statement*)this << close;
    return *this;
}

const UnaryTestStatementSPtr& operator<<(const UnaryTestStatementSPtr& object, const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

