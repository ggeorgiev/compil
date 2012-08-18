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

void Field::set_structure(const StructureSPtr& structure)
{
    mStructure = structure;
}

const CommentSPtr& Field::comment() const
{
    return mComment;
}

void Field::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
}

const NameSPtr& Field::name() const
{
    return mName;
}

void Field::set_name(const NameSPtr& name)
{
    mName = name;
}

const TypeSPtr& Field::type() const
{
    return mType;
}

void Field::set_type(const TypeSPtr& type)
{
    mType = type;
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

void Field::set_defaultValue(const DefaultValueSPtr& defaultValue)
{
    mDefaultValue = defaultValue;
}

unsigned long Field::bitmask() const
{
    return mBitmask;
}

void Field::set_bitmask(unsigned long bitmask)
{
    mBitmask = bitmask;
}

}

