#include "language/compil/document/specimen.h"

namespace lang
{

namespace compil
{

SpecimenPartial::SpecimenPartial()
{
    set_kind(alter_kind());
}

SpecimenPartial::~SpecimenPartial()
{
}

SpecimenSPtr SpecimenPartial::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Specimen>(object);
}

TypePartial::EKind SpecimenPartial::alter_kind()
{
    return TypePartial::EKind::object();
}

const SpecimenWPtr& SpecimenPartial::baseSpecimen() const
{
    return mBaseSpecimen;
}

SpecimenWPtr SpecimenPartial::default_baseSpecimen()
{
    static SpecimenWPtr defaultObject;
    return defaultObject;
}

Specimen& SpecimenPartial::set_baseSpecimen(const SpecimenSPtr& baseSpecimen)
{
    mBaseSpecimen = baseSpecimen;
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_line(const Line& line)
{
    Object::set_line(line);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_column(const Column& column)
{
    Object::set_column(column);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *(Specimen*)this;
}

Specimen& SpecimenPartial::set_parameterType(const TypeSPtr& parameterType)
{
    UnaryTemplate::set_parameterType(parameterType);
    return *(Specimen*)this;
}

}

}

