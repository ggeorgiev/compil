// Boost C++ Utility
#include <boost/assert.hpp>

#include "function.h"

namespace cpp
{

namespace frm
{

Function::Function()
{
}

Function::~Function()
{
}

const DecoratedTypeSPtr& Function::return_() const
{
    return mReturn;
}

Function& Function::set_return(const DecoratedTypeSPtr& return_)
{
    mReturn = return_;
    return *this;
}

Function& Function::operator<<(const DecoratedTypeSPtr& return_)
{
    return set_return(return_);
}

const FunctionSPtr& operator<<(const FunctionSPtr& object, const DecoratedTypeSPtr& return_)
{
    BOOST_ASSERT(object);
    *object << return_;
    return object;
}

const FunctionNameSPtr& Function::name() const
{
    return mName;
}

Function& Function::set_name(const FunctionNameSPtr& name)
{
    mName = name;
    return *this;
}

Function& Function::operator<<(const FunctionNameSPtr& name)
{
    return set_name(name);
}

const FunctionSPtr& operator<<(const FunctionSPtr& object, const FunctionNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<ArgumentSPtr>& Function::arguments() const
{
    return mArguments;
}

Function& Function::set_arguments(const std::vector<ArgumentSPtr>& arguments)
{
    mArguments = arguments;
    return *this;
}

std::vector<ArgumentSPtr>& Function::mutable_arguments()
{
    return mArguments;
}

Function& Function::operator<<(const std::vector<ArgumentSPtr>& arguments)
{
    return set_arguments(arguments);
}

const FunctionSPtr& operator<<(const FunctionSPtr& object, const std::vector<ArgumentSPtr>& arguments)
{
    BOOST_ASSERT(object);
    *object << arguments;
    return object;
}

Function& Function::operator<<(const ArgumentSPtr& argumentsItem)
{
    mArguments.push_back(argumentsItem);
    return *this;
}

const FunctionSPtr& operator<<(const FunctionSPtr& object, const ArgumentSPtr& argumentsItem)
{
    BOOST_ASSERT(object);
    *object << argumentsItem;
    return object;
}

}

}

