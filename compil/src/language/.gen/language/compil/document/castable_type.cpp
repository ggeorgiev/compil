#include "language/compil/document/castable_type.h"

namespace lang
{

namespace compil
{

CastableType::CastableType()
{
}

CastableType::~CastableType()
{
}

CastableTypeSPtr CastableType::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<CastableType>(object);
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

CastableType& CastableType::set_cast(const ECast& cast)
{
    mCast = cast;
    return *this;
}

CastableType::ECast& CastableType::mutable_cast()
{
    return mCast;
}

CastableType& CastableType::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

CastableType& CastableType::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

CastableType& CastableType::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

CastableType& CastableType::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *this;
}

CastableType& CastableType::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *this;
}

CastableType& CastableType::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *this;
}

CastableType& CastableType::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *this;
}

CastableType& CastableType::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *this;
}

}

}
