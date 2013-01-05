#include "language/compil/document/interface.h"

namespace lang
{

namespace compil
{

Interface::Interface()
{
}

Interface::~Interface()
{
}

InterfaceSPtr Interface::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Interface>(object);
}

const CommentSPtr& Interface::comment() const
{
    return mComment;
}

Interface& Interface::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const NameSPtr& Interface::name() const
{
    return mName;
}

Interface& Interface::set_name(const NameSPtr& name)
{
    mName = name;
    return *this;
}

const std::vector<ObjectSPtr>& Interface::objects() const
{
    return mObjects;
}

Interface& Interface::set_objects(const std::vector<ObjectSPtr>& objects)
{
    mObjects = objects;
    return *this;
}

std::vector<ObjectSPtr>& Interface::mutable_objects()
{
    return mObjects;
}

Interface& Interface::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Interface& Interface::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Interface& Interface::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

