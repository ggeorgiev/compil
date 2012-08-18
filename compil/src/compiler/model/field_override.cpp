#include "field_override.h"

namespace compil
{

FieldOverride::FieldOverride()
{
}

FieldOverride::~FieldOverride()
{
}

FieldOverrideSPtr FieldOverride::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<FieldOverride>(pObject);
}

const FieldSPtr& FieldOverride::field() const
{
    return mField;
}

void FieldOverride::set_field(const FieldSPtr& field)
{
    mField = field;
}

const FieldSPtr& FieldOverride::overriddenField() const
{
    return mOverriddenField;
}

void FieldOverride::set_overriddenField(const FieldSPtr& overriddenField)
{
    mOverriddenField = overriddenField;
}

}

