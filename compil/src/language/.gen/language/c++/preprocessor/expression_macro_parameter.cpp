// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/preprocessor/expression_macro_parameter.h"

namespace lang
{

namespace cpp
{

ExpressionMacroParameter::ExpressionMacroParameter()
{
}

ExpressionMacroParameter::~ExpressionMacroParameter()
{
}

ExpressionMacroParameterSPtr ExpressionMacroParameter::downcast(const MacroParameterSPtr& object)
{
    return boost::static_pointer_cast<ExpressionMacroParameter>(object);
}

const ExpressionSPtr& ExpressionMacroParameter::expression() const
{
    return mExpression;
}

ExpressionMacroParameter& ExpressionMacroParameter::set_expression(const ExpressionSPtr& expression)
{
    mExpression = expression;
    return *this;
}

ExpressionMacroParameter& ExpressionMacroParameter::operator<<(const ExpressionSPtr& expression)
{
    return set_expression(expression);
}

const ExpressionMacroParameterSPtr& operator<<(const ExpressionMacroParameterSPtr& object,
                                               const ExpressionSPtr& expression)
{
    BOOST_ASSERT(object);
    *object << expression;
    return object;
}

}

}

