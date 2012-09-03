#include "field.h"

namespace compil
{

Field::Field()
{
}

Field::~Field()
{
}

FieldSPtr Field::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Field>(pObject);
}

const StructureWPtr& Field::structure() const
{
    return mStructure;
}

Field& Field::set_structure(const StructureSPtr& structure)
{
    mStructure = structure;
    return *this;
}

const CommentSPtr& Field::comment() const
{
    return mComment;
}

Field& Field::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const NameSPtr& Field::name() const
{
    return mName;
}

Field& Field::set_name(const NameSPtr& name)
{
    mName = name;
    return *this;
}

const TypeSPtr& Field::type() const
{
    return mType;
}

Field& Field::set_type(const TypeSPtr& type)
{
    mType = type;
    return *this;
}

const DefaultValueSPtr& Field::defaultValue() const
{
    return mDefaultValue;
}

DefaultValueSPtr Field::default_defaultValue()
{
    static DefaultValueSPtr defaultObject;
    return defaultObject;
}

Field& Field::set_defaultValue(const DefaultValueSPtr& defaultValue)
{
    mDefaultValue = defaultValue;
    return *this;
}

unsigned long Field::bitmask() const
{
    return mBitmask;
}

Field& Field::set_bitmask(unsigned long bitmask)
{
    mBitmask = bitmask;
    return *this;
}

}

