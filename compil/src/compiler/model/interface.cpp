#include "interface.h"

namespace compil
{

Interface::Interface()
{
}

Interface::~Interface()
{
}

InterfaceSPtr Interface::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Interface>(pObject);
}

const CommentSPtr& Interface::comment() const
{
    return mComment;
}

void Interface::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
}

const NameSPtr& Interface::name() const
{
    return mName;
}

void Interface::set_name(const NameSPtr& name)
{
    mName = name;
}

const std::vector<ObjectSPtr>& Interface::objects() const
{
    return mObjects;
}

void Interface::set_objects(const std::vector<ObjectSPtr>& objects)
{
    mObjects = objects;
}

}

