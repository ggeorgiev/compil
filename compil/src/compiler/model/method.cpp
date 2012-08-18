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

void Method::set_interface(const InterfaceSPtr& interface_)
{
    mInterface = interface_;
}

const CommentSPtr& Method::comment() const
{
    return mComment;
}

void Method::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
}

const NameSPtr& Method::name() const
{
    return mName;
}

void Method::set_name(const NameSPtr& name)
{
    mName = name;
}

const std::vector<ObjectSPtr>& Method::objects() const
{
    return mObjects;
}

void Method::set_objects(const std::vector<ObjectSPtr>& objects)
{
    mObjects = objects;
}

}

