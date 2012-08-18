#include "alter.h"

namespace compil
{

Alter::Alter()
{
}

Alter::~Alter()
{
}

AlterSPtr Alter::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Alter>(pObject);
}

const FieldSPtr& Alter::field() const
{
    return mField;
}

void Alter::set_field(const FieldSPtr& field)
{
    mField = field;
}

const DefaultValueSPtr& Alter::defaultValue() const
{
    return mDefaultValue;
}

void Alter::set_defaultValue(const DefaultValueSPtr& defaultValue)
{
    mDefaultValue = defaultValue;
}

}

