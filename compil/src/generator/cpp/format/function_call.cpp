// Boost C++ Utility
#include <boost/assert.hpp>

#include "function_call.h"

namespace cpp
{

namespace frm
{

FunctionCall::FunctionCall()
{
}

FunctionCall::~FunctionCall()
{
}

const NamespaceSPtr& FunctionCall::namespace_() const
{
    return mNamespace;
}

FunctionCall& FunctionCall::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

FunctionCall& FunctionCall::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const FunctionCallSPtr& operator<<(const FunctionCallSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

const FunctionNameSPtr& FunctionCall::name() const
{
    return mName;
}

FunctionCall& FunctionCall::set_name(const FunctionNameSPtr& name)
{
    mName = name;
    return *this;
}

FunctionCall& FunctionCall::operator<<(const FunctionNameSPtr& name)
{
    return set_name(name);
}

const FunctionCallSPtr& operator<<(const FunctionCallSPtr& object, const FunctionNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<ParameterValueSPtr>& FunctionCall::parameters() const
{
    return mParameters;
}

FunctionCall& FunctionCall::set_parameters(const std::vector<ParameterValueSPtr>& parameters)
{
    mParameters = parameters;
    return *this;
}

std::vector<ParameterValueSPtr>& FunctionCall::mutable_parameters()
{
    return mParameters;
}

FunctionCall& FunctionCall::operator<<(const std::vector<ParameterValueSPtr>& parameters)
{
    return set_parameters(parameters);
}

const FunctionCallSPtr& operator<<(const FunctionCallSPtr& object, const std::vector<ParameterValueSPtr>& parameters)
{
    BOOST_ASSERT(object);
    *object << parameters;
    return object;
}

FunctionCall& FunctionCall::operator<<(const ParameterValueSPtr& parametersItem)
{
    mParameters.push_back(parametersItem);
    return *this;
}

const FunctionCallSPtr& operator<<(const FunctionCallSPtr& object, const ParameterValueSPtr& parametersItem)
{
    BOOST_ASSERT(object);
    *object << parametersItem;
    return object;
}

}

}

