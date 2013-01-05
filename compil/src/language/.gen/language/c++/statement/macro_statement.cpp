// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/macro_statement.h"

namespace lang
{

namespace cpp
{

MacroStatement::MacroStatement()
{
}

MacroStatement::~MacroStatement()
{
}

MacroStatementSPtr MacroStatement::downcast(const StatementSPtr& object)
{
    return boost::static_pointer_cast<MacroStatement>(object);
}

const MacroNameSPtr& MacroStatement::name() const
{
    return mName;
}

MacroStatement& MacroStatement::set_name(const MacroNameSPtr& name)
{
    mName = name;
    return *this;
}

MacroStatement& MacroStatement::operator<<(const MacroNameSPtr& name)
{
    return set_name(name);
}

const MacroStatementSPtr& operator<<(const MacroStatementSPtr& object, const MacroNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<MacroParameterSPtr>& MacroStatement::parameters() const
{
    return mParameters;
}

MacroStatement& MacroStatement::set_parameters(const std::vector<MacroParameterSPtr>& parameters)
{
    mParameters = parameters;
    return *this;
}

std::vector<MacroParameterSPtr>& MacroStatement::mutable_parameters()
{
    return mParameters;
}

MacroStatement& MacroStatement::operator<<(const std::vector<MacroParameterSPtr>& parameters)
{
    return set_parameters(parameters);
}

const MacroStatementSPtr& operator<<(const MacroStatementSPtr& object,
                                     const std::vector<MacroParameterSPtr>& parameters)
{
    BOOST_ASSERT(object);
    *object << parameters;
    return object;
}

MacroStatement& MacroStatement::operator<<(const MacroParameterSPtr& parametersItem)
{
    mParameters.push_back(parametersItem);
    return *this;
}

const MacroStatementSPtr& operator<<(const MacroStatementSPtr& object, const MacroParameterSPtr& parametersItem)
{
    BOOST_ASSERT(object);
    *object << parametersItem;
    return object;
}

MacroStatement& MacroStatement::set_close(const EClose& close)
{
    Statement::set_close(close);
    return *this;
}

MacroStatement& MacroStatement::operator<<(const EClose& close)
{
    *(Statement*)this << close;
    return *this;
}

const MacroStatementSPtr& operator<<(const MacroStatementSPtr& object, const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

