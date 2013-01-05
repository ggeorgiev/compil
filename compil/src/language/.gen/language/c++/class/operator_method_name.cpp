// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/class/operator_method_name.h"

namespace lang
{

namespace cpp
{

OperatorMethodName::OperatorMethodName()
{
}

OperatorMethodName::~OperatorMethodName()
{
}

OperatorMethodNameSPtr OperatorMethodName::downcast(const MethodNameSPtr& object)
{
    return boost::static_pointer_cast<OperatorMethodName>(object);
}

const OperatorFunctionIdSPtr& OperatorMethodName::operator_() const
{
    return mOperator;
}

OperatorMethodName& OperatorMethodName::set_operator(const OperatorFunctionIdSPtr& operator_)
{
    mOperator = operator_;
    return *this;
}

OperatorMethodName& OperatorMethodName::operator<<(const OperatorFunctionIdSPtr& operator_)
{
    return set_operator(operator_);
}

const OperatorMethodNameSPtr& operator<<(const OperatorMethodNameSPtr& object, const OperatorFunctionIdSPtr& operator_)
{
    BOOST_ASSERT(object);
    *object << operator_;
    return object;
}

}

}

