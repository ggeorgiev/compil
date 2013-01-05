#include "language/compil/document/identifier.h"

namespace lang
{

namespace compil
{

Identifier::Identifier()
{
    set_kind(alter_kind());
}

Identifier::~Identifier()
{
}

IdentifierSPtr Identifier::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Identifier>(object);
}

TypePartial::EKind Identifier::alter_kind()
{
    return TypePartial::EKind::object();
}

Identifier& Identifier::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Identifier& Identifier::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Identifier& Identifier::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

Identifier& Identifier::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *this;
}

Identifier& Identifier::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *this;
}

Identifier& Identifier::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *this;
}

Identifier& Identifier::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *this;
}

Identifier& Identifier::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *this;
}

Identifier& Identifier::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *this;
}

Identifier& Identifier::set_parameterType(const TypeSPtr& parameterType)
{
    UnaryTemplate::set_parameterType(parameterType);
    return *this;
}

}

}

