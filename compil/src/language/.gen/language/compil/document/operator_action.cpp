#include "language/compil/document/operator_action.h"

namespace lang
{

namespace compil
{

EOperatorAction::EOperatorAction()
        : mValue(kInvalid)
{
}

EOperatorAction::EOperatorAction(long value)
        : mValue(value)
{
}

const EOperatorAction EOperatorAction::invalid()
{
    return EOperatorAction(kInvalid);
}

const EOperatorAction EOperatorAction::equalTo()
{
    return EOperatorAction(kEqualTo);
}

const EOperatorAction EOperatorAction::notEqualTo()
{
    return EOperatorAction(kNotEqualTo);
}

const EOperatorAction EOperatorAction::greaterThan()
{
    return EOperatorAction(kGreaterThan);
}

const EOperatorAction EOperatorAction::lessThan()
{
    return EOperatorAction(kLessThan);
}

const EOperatorAction EOperatorAction::addition()
{
    return EOperatorAction(kAddition);
}

const EOperatorAction EOperatorAction::subtraction()
{
    return EOperatorAction(kSubtraction);
}

const EOperatorAction EOperatorAction::prefixPP()
{
    return EOperatorAction(kPrefixPP);
}

const EOperatorAction EOperatorAction::postfixPP()
{
    return EOperatorAction(kPostfixPP);
}

const EOperatorAction EOperatorAction::prefixMM()
{
    return EOperatorAction(kPrefixMM);
}

const EOperatorAction EOperatorAction::postfixMM()
{
    return EOperatorAction(kPostfixMM);
}

long EOperatorAction::value() const
{
    return mValue;
}

const char* EOperatorAction::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "equalTo",
        "notEqualTo",
        "greaterThan",
        "lessThan",
        "addition",
        "subtraction",
        "prefixPP",
        "postfixPP",
        "prefixMM",
        "postfixMM",
    };
    return names[(size_t)value];
}

const char* EOperatorAction::shortName() const
{
    return shortName(value());
}

bool EOperatorAction::operator==(const EOperatorAction& rValue) const
{
    return mValue == rValue.mValue;
}

bool EOperatorAction::operator!=(const EOperatorAction& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

