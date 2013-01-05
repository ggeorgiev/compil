// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/test/test.h"

namespace lang
{

namespace cpp
{

Test::Test()
{
}

Test::~Test()
{
}

const TestName& Test::name() const
{
    return mName;
}

Test& Test::set_name(const TestName& name)
{
    mName = name;
    return *this;
}

TestName& Test::mutable_name()
{
    return mName;
}

Test& Test::operator<<(const TestName& name)
{
    return set_name(name);
}

const TestSPtr& operator<<(const TestSPtr& object, const TestName& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<StatementSPtr>& Test::statements() const
{
    return mStatements;
}

Test& Test::set_statements(const std::vector<StatementSPtr>& statements)
{
    mStatements = statements;
    return *this;
}

std::vector<StatementSPtr>& Test::mutable_statements()
{
    return mStatements;
}

Test& Test::operator<<(const std::vector<StatementSPtr>& statements)
{
    return set_statements(statements);
}

const TestSPtr& operator<<(const TestSPtr& object, const std::vector<StatementSPtr>& statements)
{
    BOOST_ASSERT(object);
    *object << statements;
    return object;
}

Test& Test::operator<<(const StatementSPtr& statementsItem)
{
    mStatements.push_back(statementsItem);
    return *this;
}

const TestSPtr& operator<<(const TestSPtr& object, const StatementSPtr& statementsItem)
{
    BOOST_ASSERT(object);
    *object << statementsItem;
    return object;
}

}

}

