#include "castable_type.h"

namespace compil
{

CastableType::CastableType()
{
}

CastableType::~CastableType()
{
}

CastableTypeSPtr CastableType::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<CastableType>(pObject);
}

CastableType::ECast::ECast()
        : mValue(kInvalid)
{
}

CastableType::ECast::ECast(long value)
        : mValue(value)
{
}

const CastableType::ECast CastableType::ECast::invalid()
{
    return ECast(kInvalid);
}

const CastableType::ECast CastableType::ECast::weak()
{
    return ECast(kWeak);
}

const CastableType::ECast CastableType::ECast::strong()
{
    return ECast(kStrong);
}

long CastableType::ECast::value() const
{
    return mValue;
}

const char* CastableType::ECast::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "weak",
        "strong",
    };
    return names[(size_t)value];
}

const char* CastableType::ECast::shortName() const
{
    return shortName(value());
}

bool CastableType::ECast::operator==(const ECast& rValue) const
{
    return mValue == rValue.mValue;
}

bool CastableType::ECast::operator!=(const ECast& rValue) const
{
    return mValue != rValue.mValue;
}

const CastableType::ECast& CastableType::cast() const
{
    return mCast;
}

void CastableType::set_cast(const ECast& cast)
{
    mCast = cast;
}

}

