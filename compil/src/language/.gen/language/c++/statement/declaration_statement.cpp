// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/declaration_statement.h"

namespace lang
{

namespace cpp
{

DeclarationStatement::DeclarationStatement()
{
}

DeclarationStatement::~DeclarationStatement()
{
}

DeclarationStatementSPtr DeclarationStatement::downcast(const StatementSPtr& object)
{
    return boost::static_pointer_cast<DeclarationStatement>(object);
}

DeclarationStatementSPtr DeclarationStatement::shared_from_this()
{
    return boost::static_pointer_cast<DeclarationStatement>(
        boost::enable_shared_from_this<Statement>::shared_from_this());
}

DeclarationStatementSCPtr DeclarationStatement::shared_from_this() const
{
    return boost::static_pointer_cast<const DeclarationStatement>(
        boost::enable_shared_from_this<Statement>::shared_from_this());
}

const BlockDeclarationSPtr& DeclarationStatement::declaration() const
{
    return mDeclaration;
}

DeclarationStatement& DeclarationStatement::set_declaration(const BlockDeclarationSPtr& declaration)
{
    mDeclaration = declaration;
    return *this;
}

DeclarationStatement& DeclarationStatement::operator<<(const BlockDeclarationSPtr& declaration)
{
    return set_declaration(declaration);
}

const DeclarationStatementSPtr& operator<<(const DeclarationStatementSPtr& object,
                                           const BlockDeclarationSPtr& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

DeclarationStatement& DeclarationStatement::set_close(const EClose& close)
{
    Statement::set_close(close);
    return *this;
}

DeclarationStatement& DeclarationStatement::operator<<(const EClose& close)
{
    *(Statement*)this << close;
    return *this;
}

const DeclarationStatementSPtr& operator<<(const DeclarationStatementSPtr& object, const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

