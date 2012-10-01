#include "type_decoration.h"

namespace cpp
{

namespace frm
{

ETypeDecoration::ETypeDecoration()
        : mValue(kInvalid)
{
}

ETypeDecoration::ETypeDecoration(long value)
        : mValue(value)
{
}

const ETypeDecoration ETypeDecoration::invalid()
{
    return ETypeDecoration(kInvalid);
}

const ETypeDecoration ETypeDecoration::pointer()
{
    return ETypeDecoration(kPointer);
}

const ETypeDecoration ETypeDecoration::reference()
{
    return ETypeDecoration(kReference);
}

long ETypeDecoration::value() const
{
    return mValue;
}

const char* ETypeDecoration::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "pointer",
        "reference",
    };
    return names[(size_t)value];
}

const char* ETypeDecoration::shortName() const
{
    return shortName(value());
}

bool ETypeDecoration::operator==(const ETypeDecoration& rValue) const
{
    return mValue == rValue.mValue;
}

bool ETypeDecoration::operator!=(const ETypeDecoration& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

