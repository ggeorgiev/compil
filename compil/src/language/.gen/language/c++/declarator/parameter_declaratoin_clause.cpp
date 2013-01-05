// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declarator/parameter_declaratoin_clause.h"

namespace lang
{

namespace cpp
{

ParameterDeclarationClause::ParameterDeclarationClause()
{
}

ParameterDeclarationClause::~ParameterDeclarationClause()
{
}

ParameterDeclarationClauseSPtr ParameterDeclarationClause::downcast(const DeclaratorSPtr& object)
{
    return boost::static_pointer_cast<ParameterDeclarationClause>(object);
}

const ParameterDeclarationListSPtr& ParameterDeclarationClause::declarator() const
{
    return mDeclarator;
}

ParameterDeclarationClause& ParameterDeclarationClause::set_declarator(const ParameterDeclarationListSPtr& declarator)
{
    mDeclarator = declarator;
    return *this;
}

ParameterDeclarationClause& ParameterDeclarationClause::operator<<(const ParameterDeclarationListSPtr& declarator)
{
    return set_declarator(declarator);
}

const ParameterDeclarationClauseSPtr& operator<<(const ParameterDeclarationClauseSPtr& object,
                                                 const ParameterDeclarationListSPtr& declarator)
{
    BOOST_ASSERT(object);
    *object << declarator;
    return object;
}

}

}

