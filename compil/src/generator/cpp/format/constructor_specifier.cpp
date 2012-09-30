#include "constructor_specifier.h"

namespace cpp
{

namespace frm
{

EConstructorSpecifier::EConstructorSpecifier()
        : mValue(kInvalid)
{
}

EConstructorSpecifier::EConstructorSpecifier(long value)
        : mValue(value)
{
}

const EConstructorSpecifier EConstructorSpecifier::invalid()
{
    return EConstructorSpecifier(kInvalid);
}

const EConstructorSpecifier EConstructorSpecifier::explicit_()
{
    return EConstructorSpecifier(kExplicit);
}

long EConstructorSpecifier::value() const
{
    return mValue;
}

const char* EConstructorSpecifier::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "explicit",
    };
    return names[(size_t)value];
}

const char* EConstructorSpecifier::shortName() const
{
    return shortName(value());
}

bool EConstructorSpecifier::operator==(const EConstructorSpecifier& rValue) const
{
    return mValue == rValue.mValue;
}

bool EConstructorSpecifier::operator!=(const EConstructorSpecifier& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

