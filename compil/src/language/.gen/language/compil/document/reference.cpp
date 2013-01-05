#include "language/compil/document/reference.h"

namespace lang
{

namespace compil
{

Reference::Reference()
{
}

Reference::~Reference()
{
}

ReferenceSPtr Reference::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Reference>(object);
}

bool Reference::weak() const
{
    return mWeak;
}

Reference& Reference::set_weak(bool weak)
{
    mWeak = weak;
    return *this;
}

Reference& Reference::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Reference& Reference::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Reference& Reference::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

Reference& Reference::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *this;
}

Reference& Reference::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *this;
}

Reference& Reference::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *this;
}

Reference& Reference::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *this;
}

Reference& Reference::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *this;
}

Reference& Reference::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *this;
}

Reference& Reference::set_parameterType(const TypeSPtr& parameterType)
{
    UnaryTemplate::set_parameterType(parameterType);
    return *this;
}

}

}

