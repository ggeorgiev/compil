#include "type_declaration.h"

namespace cpp
{

namespace frm
{

ETypeDeclaration::ETypeDeclaration()
        : mValue(kInvalid)
{
}

ETypeDeclaration::ETypeDeclaration(long value)
        : mValue(value)
{
}

const ETypeDeclaration ETypeDeclaration::invalid()
{
    return ETypeDeclaration(kInvalid);
}

const ETypeDeclaration ETypeDeclaration::const_()
{
    return ETypeDeclaration(kConst);
}

long ETypeDeclaration::value() const
{
    return mValue;
}

const char* ETypeDeclaration::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "const",
    };
    return names[(size_t)value];
}

const char* ETypeDeclaration::shortName() const
{
    return shortName(value());
}

bool ETypeDeclaration::operator==(const ETypeDeclaration& rValue) const
{
    return mValue == rValue.mValue;
}

bool ETypeDeclaration::operator!=(const ETypeDeclaration& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

