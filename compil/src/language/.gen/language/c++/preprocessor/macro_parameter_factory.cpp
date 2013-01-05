// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/preprocessor/macro_parameter_factory.h"

namespace lang
{

namespace cpp
{

EMacroParameterId::EMacroParameterId()
        : mValue(kInvalid)
{
}

EMacroParameterId::EMacroParameterId(long value)
        : mValue(value)
{
}

const EMacroParameterId EMacroParameterId::invalid()
{
    return EMacroParameterId(kInvalid);
}

const EMacroParameterId EMacroParameterId::declarationMacroParameter()
{
    return EMacroParameterId(kDeclarationMacroParameter);
}

const EMacroParameterId EMacroParameterId::expressionMacroParameter()
{
    return EMacroParameterId(kExpressionMacroParameter);
}

const EMacroParameterId EMacroParameterId::macroParameter()
{
    return EMacroParameterId(kMacroParameter);
}

long EMacroParameterId::value() const
{
    return mValue;
}

const char* EMacroParameterId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "DeclarationMacroParameter",
        "ExpressionMacroParameter",
        "MacroParameter",
    };
    return names[(size_t)value];
}

const char* EMacroParameterId::shortName() const
{
    return shortName(value());
}

bool EMacroParameterId::operator==(const EMacroParameterId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EMacroParameterId::operator!=(const EMacroParameterId& rValue) const
{
    return mValue != rValue.mValue;
}

EMacroParameterId DeclarationMacroParameter::staticMacroParameterId()
{
    return EMacroParameterId::declarationMacroParameter();
}

EMacroParameterId DeclarationMacroParameter::runtimeMacroParameterId() const
{
    return staticMacroParameterId();
}

EMacroParameterId ExpressionMacroParameter::staticMacroParameterId()
{
    return EMacroParameterId::expressionMacroParameter();
}

EMacroParameterId ExpressionMacroParameter::runtimeMacroParameterId() const
{
    return staticMacroParameterId();
}

EMacroParameterId MacroParameter::staticMacroParameterId()
{
    return EMacroParameterId::macroParameter();
}

EMacroParameterId MacroParameter::runtimeMacroParameterId() const
{
    return staticMacroParameterId();
}

MacroParameterSPtr MacroParameterFactory::clone(const MacroParameterSPtr& pObject)
{
    switch (pObject->runtimeMacroParameterId().value())
    {
        case EMacroParameterId::kDeclarationMacroParameter:
        {
            DeclarationMacroParameterSPtr pClone(new DeclarationMacroParameter());
            *pClone = *downcastDeclarationMacroParameter(pObject);
            return pClone;
        }
        case EMacroParameterId::kExpressionMacroParameter:
        {
            ExpressionMacroParameterSPtr pClone(new ExpressionMacroParameter());
            *pClone = *downcastExpressionMacroParameter(pObject);
            return pClone;
        }
        case EMacroParameterId::kMacroParameter:
        {
            MacroParameterSPtr pClone(new MacroParameter());
            *pClone = *pObject;
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return MacroParameterSPtr();
}

DeclarationMacroParameterSPtr MacroParameterFactory::downcastDeclarationMacroParameter(const MacroParameterSPtr& pObject)
{
    bool b = (pObject->runtimeMacroParameterId() == DeclarationMacroParameter::staticMacroParameterId());

    if (b)
        return boost::static_pointer_cast<DeclarationMacroParameter>(pObject);
    return DeclarationMacroParameterSPtr();
}

ExpressionMacroParameterSPtr MacroParameterFactory::downcastExpressionMacroParameter(const MacroParameterSPtr& pObject)
{
    bool b = (pObject->runtimeMacroParameterId() == ExpressionMacroParameter::staticMacroParameterId());

    if (b)
        return boost::static_pointer_cast<ExpressionMacroParameter>(pObject);
    return ExpressionMacroParameterSPtr();
}

}

}

