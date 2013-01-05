// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/overloading/operator_function_id.h"

namespace lang
{

namespace cpp
{

OperatorFunctionId::OperatorFunctionId()
{
}

OperatorFunctionId::~OperatorFunctionId()
{
}

const EOperator& OperatorFunctionId::operator_() const
{
    return mOperator;
}

OperatorFunctionId& OperatorFunctionId::set_operator(const EOperator& operator_)
{
    mOperator = operator_;
    return *this;
}

EOperator& OperatorFunctionId::mutable_operator()
{
    return mOperator;
}

OperatorFunctionId& OperatorFunctionId::operator<<(const EOperator& operator_)
{
    return set_operator(operator_);
}

const OperatorFunctionIdSPtr& operator<<(const OperatorFunctionIdSPtr& object, const EOperator& operator_)
{
    BOOST_ASSERT(object);
    *object << operator_;
    return object;
}

}

}

