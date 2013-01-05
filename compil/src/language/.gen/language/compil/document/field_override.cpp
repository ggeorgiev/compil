#include "language/compil/document/field_override.h"

namespace lang
{

namespace compil
{

FieldOverride::FieldOverride()
{
}

FieldOverride::~FieldOverride()
{
}

FieldOverrideSPtr FieldOverride::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<FieldOverride>(object);
}

const FieldSPtr& FieldOverride::field() const
{
    return mField;
}

FieldOverride& FieldOverride::set_field(const FieldSPtr& field)
{
    mField = field;
    return *this;
}

const FieldSPtr& FieldOverride::overriddenField() const
{
    return mOverriddenField;
}

FieldOverride& FieldOverride::set_overriddenField(const FieldSPtr& overriddenField)
{
    mOverriddenField = overriddenField;
    return *this;
}

FieldOverride& FieldOverride::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

FieldOverride& FieldOverride::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

FieldOverride& FieldOverride::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

