#include "destructor_specifier.h"

namespace cpp
{

namespace frm
{

EDestructorSpecifier::EDestructorSpecifier()
        : mValue(kInvalid)
{
}

EDestructorSpecifier::EDestructorSpecifier(long value)
        : mValue(value)
{
}

const EDestructorSpecifier EDestructorSpecifier::invalid()
{
    return EDestructorSpecifier(kInvalid);
}

const EDestructorSpecifier EDestructorSpecifier::lax()
{
    return EDestructorSpecifier(kLax);
}

const EDestructorSpecifier EDestructorSpecifier::virtual_()
{
    return EDestructorSpecifier(kVirtual);
}

long EDestructorSpecifier::value() const
{
    return mValue;
}

const char* EDestructorSpecifier::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "lax",
        "virtual",
    };
    return names[(size_t)value];
}

const char* EDestructorSpecifier::shortName() const
{
    return shortName(value());
}

bool EDestructorSpecifier::operator==(const EDestructorSpecifier& rValue) const
{
    return mValue == rValue.mValue;
}

bool EDestructorSpecifier::operator!=(const EDestructorSpecifier& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

