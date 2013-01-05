#include "language/c++/overloading/operator.h"

namespace lang
{

namespace cpp
{

EOperator::EOperator()
        : mValue(kInvalid)
{
}

EOperator::EOperator(long value)
        : mValue(value)
{
}

const EOperator EOperator::invalid()
{
    return EOperator(kInvalid);
}

const EOperator EOperator::equalTo()
{
    return EOperator(kEqualTo);
}

const EOperator EOperator::notEqualTo()
{
    return EOperator(kNotEqualTo);
}

const EOperator EOperator::addition()
{
    return EOperator(kAddition);
}

const EOperator EOperator::subtraction()
{
    return EOperator(kSubtraction);
}

long EOperator::value() const
{
    return mValue;
}

const char* EOperator::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "equalTo",
        "notEqualTo",
        "addition",
        "subtraction",
    };
    return names[(size_t)value];
}

const char* EOperator::shortName() const
{
    return shortName(value());
}

bool EOperator::operator==(const EOperator& rValue) const
{
    return mValue == rValue.mValue;
}

bool EOperator::operator!=(const EOperator& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

