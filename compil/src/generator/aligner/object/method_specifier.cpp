#include "method_specifier.h"

EMethodSpecifier::EMethodSpecifier()
        : mValue(kInvalid)
{
}

EMethodSpecifier::EMethodSpecifier(long value)
        : mValue(value)
{
}

const EMethodSpecifier EMethodSpecifier::invalid()
{
    return EMethodSpecifier(kInvalid);
}

const EMethodSpecifier EMethodSpecifier::inline_()
{
    return EMethodSpecifier(kInline);
}

const EMethodSpecifier EMethodSpecifier::static_()
{
    return EMethodSpecifier(kStatic);
}

const EMethodSpecifier EMethodSpecifier::virtual_()
{
    return EMethodSpecifier(kVirtual);
}

long EMethodSpecifier::value() const
{
    return mValue;
}

const char* EMethodSpecifier::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "inline",
        "static",
        "virtual",
    };
    return names[(size_t)value];
}

const char* EMethodSpecifier::shortName() const
{
    return shortName(value());
}

bool EMethodSpecifier::operator==(const EMethodSpecifier& rValue) const
{
    return mValue == rValue.mValue;
}

bool EMethodSpecifier::operator!=(const EMethodSpecifier& rValue) const
{
    return mValue != rValue.mValue;
}

