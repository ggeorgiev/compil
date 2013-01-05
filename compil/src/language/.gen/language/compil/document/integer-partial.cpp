#include "language/compil/document/integer.h"

namespace lang
{

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

Integer& IntegerPartial::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_line(const Line& line)
{
    Object::set_line(line);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_column(const Column& column)
{
    Object::set_column(column);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *(Integer*)this;
}

Integer& IntegerPartial::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *(Integer*)this;
}

}

}

