// Boost C++ Utility
#include <boost/assert.hpp>

#include "destructor.h"

namespace cpp
{

namespace frm
{

Destructor::Destructor()
{
}

Destructor::~Destructor()
{
}

const CommentSPtr& Destructor::comment() const
{
    return mComment;
}

Destructor& Destructor::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

Destructor& Destructor::operator<<(const CommentSPtr& comment)
{
    return set_comment(comment);
}

const DestructorSPtr& operator<<(const DestructorSPtr& object, const CommentSPtr& comment)
{
    BOOST_ASSERT(object);
    *object << comment;
    return object;
}

const EDestructorSpecifier& Destructor::specifier() const
{
    return mSpecifier;
}

Destructor& Destructor::set_specifier(const EDestructorSpecifier& specifier)
{
    mSpecifier = specifier;
    return *this;
}

EDestructorSpecifier& Destructor::mutable_specifier()
{
    return mSpecifier;
}

Destructor& Destructor::operator<<(const EDestructorSpecifier& specifier)
{
    return set_specifier(specifier);
}

const DestructorSPtr& operator<<(const DestructorSPtr& object, const EDestructorSpecifier& specifier)
{
    BOOST_ASSERT(object);
    *object << specifier;
    return object;
}

const DestructorNameSPtr& Destructor::name() const
{
    return mName;
}

Destructor& Destructor::set_name(const DestructorNameSPtr& name)
{
    mName = name;
    return *this;
}

Destructor& Destructor::operator<<(const DestructorNameSPtr& name)
{
    return set_name(name);
}

const DestructorSPtr& operator<<(const DestructorSPtr& object, const DestructorNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const NamespaceSPtr& Destructor::namespace_() const
{
    return mNamespace;
}

Destructor& Destructor::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

Destructor& Destructor::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const DestructorSPtr& operator<<(const DestructorSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

}

}

