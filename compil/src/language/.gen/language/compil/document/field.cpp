#include "language/compil/document/field.h"

namespace lang
{

namespace compil
{

Field::Field()
{
}

Field::~Field()
{
}

FieldSPtr Field::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Field>(object);
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

Field& Field::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Field& Field::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Field& Field::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

