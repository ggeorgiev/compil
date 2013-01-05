#include "language/compil/document/alter.h"

namespace lang
{

namespace compil
{

Alter::Alter()
{
}

Alter::~Alter()
{
}

AlterSPtr Alter::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Alter>(object);
}

const FieldSPtr& Alter::field() const
{
    return mField;
}

Alter& Alter::set_field(const FieldSPtr& field)
{
    mField = field;
    return *this;
}

const DefaultValueSPtr& Alter::defaultValue() const
{
    return mDefaultValue;
}

Alter& Alter::set_defaultValue(const DefaultValueSPtr& defaultValue)
{
    mDefaultValue = defaultValue;
    return *this;
}

Alter& Alter::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Alter& Alter::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Alter& Alter::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

