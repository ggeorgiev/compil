#include "language/compil/document/enumeration.h"

namespace lang
{

namespace compil
{

EnumerationPartial::EnumerationPartial()
{
    set_literal(alter_literal());
    set_kind(alter_kind());
}

EnumerationPartial::~EnumerationPartial()
{
}

EnumerationSPtr EnumerationPartial::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Enumeration>(object);
}

TypePartial::ELiteral EnumerationPartial::alter_literal()
{
    return TypePartial::ELiteral::identifier();
}

TypePartial::EKind EnumerationPartial::alter_kind()
{
    return TypePartial::EKind::object();
}

bool EnumerationPartial::flags() const
{
    return mFlags;
}

Enumeration& EnumerationPartial::set_flags(bool flags)
{
    mFlags = flags;
    return *(Enumeration*)this;
}

const std::vector<EnumerationValueSPtr>& EnumerationPartial::enumerationValues() const
{
    return mEnumerationValues;
}

Enumeration& EnumerationPartial::set_enumerationValues(const std::vector<EnumerationValueSPtr>& enumerationValues)
{
    mEnumerationValues = enumerationValues;
    return *(Enumeration*)this;
}

std::vector<EnumerationValueSPtr>& EnumerationPartial::mutable_enumerationValues()
{
    return mEnumerationValues;
}

const StructureWPtr& EnumerationPartial::structure() const
{
    return mStructure;
}

StructureWPtr EnumerationPartial::default_structure()
{
    static StructureWPtr defaultObject;
    return defaultObject;
}

Enumeration& EnumerationPartial::set_structure(const StructureSPtr& structure)
{
    mStructure = structure;
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_line(const Line& line)
{
    Object::set_line(line);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_column(const Column& column)
{
    Object::set_column(column);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *(Enumeration*)this;
}

Enumeration& EnumerationPartial::set_parameterType(const TypeSPtr& parameterType)
{
    UnaryTemplate::set_parameterType(parameterType);
    return *(Enumeration*)this;
}

}

}

