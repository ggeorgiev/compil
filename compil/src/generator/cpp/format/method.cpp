// Boost C++ Utility
#include <boost/assert.hpp>

#include "method.h"

namespace cpp
{

namespace frm
{

Method::Method()
{
}

Method::~Method()
{
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

Method& Method::operator<<(const CommentSPtr& comment)
{
    return set_comment(comment);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const CommentSPtr& comment)
{
    BOOST_ASSERT(object);
    *object << comment;
    return object;
}

const EMethodSpecifier& Method::specifier() const
{
    return mSpecifier;
}

Method& Method::set_specifier(const EMethodSpecifier& specifier)
{
    mSpecifier = specifier;
    return *this;
}

EMethodSpecifier& Method::mutable_specifier()
{
    return mSpecifier;
}

Method& Method::operator<<(const EMethodSpecifier& specifier)
{
    return set_specifier(specifier);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const EMethodSpecifier& specifier)
{
    BOOST_ASSERT(object);
    *object << specifier;
    return object;
}

const DecoratedTypeSPtr& Method::return_() const
{
    return mReturn;
}

Method& Method::set_return(const DecoratedTypeSPtr& return_)
{
    mReturn = return_;
    return *this;
}

Method& Method::operator<<(const DecoratedTypeSPtr& return_)
{
    return set_return(return_);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const DecoratedTypeSPtr& return_)
{
    BOOST_ASSERT(object);
    *object << return_;
    return object;
}

const NamespaceSPtr& Method::namespace_() const
{
    return mNamespace;
}

Method& Method::set_namespace(const NamespaceSPtr& namespace_)
{
    mNamespace = namespace_;
    return *this;
}

Method& Method::operator<<(const NamespaceSPtr& namespace_)
{
    return set_namespace(namespace_);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const NamespaceSPtr& namespace_)
{
    BOOST_ASSERT(object);
    *object << namespace_;
    return object;
}

const MethodNameSPtr& Method::name() const
{
    return mName;
}

Method& Method::set_name(const MethodNameSPtr& name)
{
    mName = name;
    return *this;
}

Method& Method::operator<<(const MethodNameSPtr& name)
{
    return set_name(name);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const MethodNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<ArgumentSPtr>& Method::arguments() const
{
    return mArguments;
}

Method& Method::set_arguments(const std::vector<ArgumentSPtr>& arguments)
{
    mArguments = arguments;
    return *this;
}

std::vector<ArgumentSPtr>& Method::mutable_arguments()
{
    return mArguments;
}

Method& Method::operator<<(const std::vector<ArgumentSPtr>& arguments)
{
    return set_arguments(arguments);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const std::vector<ArgumentSPtr>& arguments)
{
    BOOST_ASSERT(object);
    *object << arguments;
    return object;
}

Method& Method::operator<<(const ArgumentSPtr& argumentsItem)
{
    mArguments.push_back(argumentsItem);
    return *this;
}

const MethodSPtr& operator<<(const MethodSPtr& object, const ArgumentSPtr& argumentsItem)
{
    BOOST_ASSERT(object);
    *object << argumentsItem;
    return object;
}

const EMethodDeclaration& Method::declaration() const
{
    return mDeclaration;
}

Method& Method::set_declaration(const EMethodDeclaration& declaration)
{
    mDeclaration = declaration;
    return *this;
}

EMethodDeclaration& Method::mutable_declaration()
{
    return mDeclaration;
}

Method& Method::operator<<(const EMethodDeclaration& declaration)
{
    return set_declaration(declaration);
}

const MethodSPtr& operator<<(const MethodSPtr& object, const EMethodDeclaration& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

}

}

