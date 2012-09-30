#include "integer.h"

namespace compil
{

IntegerPartial::IntegerPartial()
{
    set_literal(alter_literal());
    set_kind(alter_kind());
    set_cast(alter_cast());
}

IntegerPartial::~IntegerPartial()
{
}

IntegerSPtr IntegerPartial::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Integer>(object);
}

TypePartial::ELiteral IntegerPartial::alter_literal()
{
    return TypePartial::ELiteral::integer();
}

TypePartial::EKind IntegerPartial::alter_kind()
{
    return TypePartial::EKind::builtin();
}

CastableType::ECast IntegerPartial::alter_cast()
{
    return CastableType::ECast::weak();
}

const std::string& IntegerPartial::min() const
{
    return mMin;
}

Integer& IntegerPartial::set_min(const std::string& min)
{
    mMin = min;
    return *(Integer*)this;
}

std::string& IntegerPartial::mutable_min()
{
    return mMin;
}

const std::string& IntegerPartial::max() const
{
    return mMax;
}

Integer& IntegerPartial::set_max(const std::string& max)
{
    mMax = max;
    return *(Integer*)this;
}

std::string& IntegerPartial::mutable_max()
{
    return mMax;
}

}

