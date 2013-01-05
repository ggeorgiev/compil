// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/compound_statement.h"

namespace lang
{

namespace cpp
{

CompoundStatement::CompoundStatement()
{
    set_close(alter_close());
}

CompoundStatement::~CompoundStatement()
{
}

CompoundStatementSPtr CompoundStatement::downcast(const StatementSPtr& object)
{
    return boost::static_pointer_cast<CompoundStatement>(object);
}

Statement::EClose CompoundStatement::alter_close()
{
    return Statement::EClose::no();
}

const std::vector<StatementSPtr>& CompoundStatement::statements() const
{
    return mStatements;
}

CompoundStatement& CompoundStatement::set_statements(const std::vector<StatementSPtr>& statements)
{
    mStatements = statements;
    return *this;
}

std::vector<StatementSPtr>& CompoundStatement::mutable_statements()
{
    return mStatements;
}

CompoundStatement& CompoundStatement::operator<<(const std::vector<StatementSPtr>& statements)
{
    return set_statements(statements);
}

const CompoundStatementSPtr& operator<<(const CompoundStatementSPtr& object,
                                        const std::vector<StatementSPtr>& statements)
{
    BOOST_ASSERT(object);
    *object << statements;
    return object;
}

CompoundStatement& CompoundStatement::operator<<(const StatementSPtr& statementsItem)
{
    mStatements.push_back(statementsItem);
    return *this;
}

const CompoundStatementSPtr& operator<<(const CompoundStatementSPtr& object, const StatementSPtr& statementsItem)
{
    BOOST_ASSERT(object);
    *object << statementsItem;
    return object;
}

CompoundStatement& CompoundStatement::set_close(const EClose& close)
{
    Statement::set_close(close);
    return *this;
}

CompoundStatement& CompoundStatement::operator<<(const EClose& close)
{
    *(Statement*)this << close;
    return *this;
}

const CompoundStatementSPtr& operator<<(const CompoundStatementSPtr& object, const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

