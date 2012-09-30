#include "method_group.h"

EMethodGroup::EMethodGroup()
        : flags_enumeration<long, EMethodGroup>(0)
{
}

EMethodGroup::EMethodGroup(long value)
        : flags_enumeration<long, EMethodGroup>(value)
{
}

const EMethodGroup EMethodGroup::nil()
{
    return EMethodGroup(kNil);
}

const EMethodGroup EMethodGroup::reading()
{
    return EMethodGroup(kReading);
}

const EMethodGroup EMethodGroup::writing()
{
    return EMethodGroup(kWriting);
}

const EMethodGroup EMethodGroup::builder()
{
    return EMethodGroup(kBuilder);
}

const EMethodGroup EMethodGroup::special()
{
    return EMethodGroup(kSpecial);
}

const EMethodGroup EMethodGroup::overridden()
{
    return EMethodGroup(kOverridden);
}

const EMethodGroup EMethodGroup::all()
{
    return EMethodGroup(kAll);
}

long EMethodGroup::value() const
{
    return mValue;
}

const char* EMethodGroup::shortName(long value)
{
    switch (value)
    {
        case kReading   : return "reading";
        case kWriting   : return "writing";
        case kBuilder   : return "builder";
        case kSpecial   : return "special";
        case kOverridden: return "overridden";
        default         : return "custom";
    }
}

const char* EMethodGroup::shortName() const
{
    return shortName(value());
}

bool EMethodGroup::operator==(const EMethodGroup& rValue) const
{
    return mValue == rValue.mValue;
}

bool EMethodGroup::operator!=(const EMethodGroup& rValue) const
{
    return mValue != rValue.mValue;
}

