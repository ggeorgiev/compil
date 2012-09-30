#include "integer.h"

namespace compil
{

Integer::Integer()
{
    set_literal(alter_literal());
    set_kind(alter_kind());
    set_cast(alter_cast());
}

Integer::~Integer()
{
}

IntegerSPtr Integer::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Integer>(object);
}

TypePartial::ELiteral Integer::alter_literal()
{
    return TypePartial::ELiteral::integer();
}

TypePartial::EKind Integer::alter_kind()
{
    return TypePartial::EKind::builtin();
}

CastableType::ECast Integer::alter_cast()
{
    return CastableType::ECast::weak();
}

const std::string& Integer::min() const
{
    return mMin;
}

Integer& Integer::set_min(const std::string& min)
{
    mMin = min;
    return *this;
}

std::string& Integer::mutable_min()
{
    return mMin;
}

const std::string& Integer::max() const
{
    return mMax;
}

Integer& Integer::set_max(const std::string& max)
{
    mMax = max;
    return *this;
}

std::string& Integer::mutable_max()
{
    return mMax;
}

}

