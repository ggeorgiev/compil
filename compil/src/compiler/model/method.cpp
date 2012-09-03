#include "method.h"

namespace compil
{

Method::Method()
{
}

Method::~Method()
{
}

MethodSPtr Method::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Method>(pObject);
}

const InterfaceWPtr& Method::interface_() const
{
    return mInterface;
}

Method& Method::set_interface(const InterfaceSPtr& interface_)
{
    mInterface = interface_;
    return *this;
}

const CommentSPtr& Method::comment() const
{
    return mComment;
}

Method& Method::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const NameSPtr& Method::name() const
{
    return mName;
}

Method& Method::set_name(const NameSPtr& name)
{
    mName = name;
    return *this;
}

const std::vector<ObjectSPtr>& Method::objects() const
{
    return mObjects;
}

Method& Method::set_objects(const std::vector<ObjectSPtr>& objects)
{
    mObjects = objects;
    return *this;
}

std::vector<ObjectSPtr>& Method::mutable_objects()
{
    return mObjects;
}

}

