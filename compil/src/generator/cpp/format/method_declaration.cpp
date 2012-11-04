#include "method_declaration.h"

namespace cpp
{

namespace frm
{

EMethodDeclaration::EMethodDeclaration()
        : mValue(kInvalid)
{
}

EMethodDeclaration::EMethodDeclaration(long value)
        : mValue(value)
{
}

const EMethodDeclaration EMethodDeclaration::invalid()
{
    return EMethodDeclaration(kInvalid);
}

const EMethodDeclaration EMethodDeclaration::const_()
{
    return EMethodDeclaration(kConst);
}

long EMethodDeclaration::value() const
{
    return mValue;
}

const char* EMethodDeclaration::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "const",
    };
    return names[(size_t)value];
}

const char* EMethodDeclaration::shortName() const
{
    return shortName(value());
}

bool EMethodDeclaration::operator==(const EMethodDeclaration& rValue) const
{
    return mValue == rValue.mValue;
}

bool EMethodDeclaration::operator!=(const EMethodDeclaration& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

