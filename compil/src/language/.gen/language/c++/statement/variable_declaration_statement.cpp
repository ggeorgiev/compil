// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/variable_declaration_statement.h"

namespace lang
{

namespace cpp
{

VariableDeclarationStatement::VariableDeclarationStatement()
{
}

VariableDeclarationStatement::~VariableDeclarationStatement()
{
}

VariableDeclarationStatementSPtr VariableDeclarationStatement::downcast(const StatementSPtr& object)
{
    return boost::static_pointer_cast<VariableDeclarationStatement>(object);
}

const ClassSPtr& VariableDeclarationStatement::type() const
{
    return mType;
}

VariableDeclarationStatement& VariableDeclarationStatement::set_type(const ClassSPtr& type)
{
    mType = type;
    return *this;
}

VariableDeclarationStatement& VariableDeclarationStatement::operator<<(const ClassSPtr& type)
{
    return set_type(type);
}

const VariableDeclarationStatementSPtr& operator<<(const VariableDeclarationStatementSPtr& object,
                                                   const ClassSPtr& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

const VariableSPtr& VariableDeclarationStatement::variable() const
{
    return mVariable;
}

VariableDeclarationStatement& VariableDeclarationStatement::set_variable(const VariableSPtr& variable)
{
    mVariable = variable;
    return *this;
}

VariableDeclarationStatement& VariableDeclarationStatement::operator<<(const VariableSPtr& variable)
{
    return set_variable(variable);
}

const VariableDeclarationStatementSPtr& operator<<(const VariableDeclarationStatementSPtr& object,
                                                   const VariableSPtr& variable)
{
    BOOST_ASSERT(object);
    *object << variable;
    return object;
}

VariableDeclarationStatement& VariableDeclarationStatement::set_close(const EClose& close)
{
    Statement::set_close(close);
    return *this;
}

VariableDeclarationStatement& VariableDeclarationStatement::operator<<(const EClose& close)
{
    *(Statement*)this << close;
    return *this;
}

const VariableDeclarationStatementSPtr& operator<<(const VariableDeclarationStatementSPtr& object,
                                                   const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

