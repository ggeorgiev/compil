#include "field_override.h"

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

}

