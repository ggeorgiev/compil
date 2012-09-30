#include "enumeration.h"

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

}

