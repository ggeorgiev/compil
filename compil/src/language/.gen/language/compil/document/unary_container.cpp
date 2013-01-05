#include "language/compil/document/unary_container.h"

namespace lang
{

namespace compil
{

UnaryContainer::UnaryContainer()
{
}

UnaryContainer::~UnaryContainer()
{
}

UnaryContainerSPtr UnaryContainer::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<UnaryContainer>(object);
}

UnaryContainer::ESize::ESize()
        : mValue(kInvalid)
{
}

UnaryContainer::ESize::ESize(long value)
        : mValue(value)
{
}

const UnaryContainer::ESize UnaryContainer::ESize::invalid()
{
    return ESize(kInvalid);
}

const UnaryContainer::ESize UnaryContainer::ESize::fixed()
{
    return ESize(kFixed);
}

const UnaryContainer::ESize UnaryContainer::ESize::dynamic()
{
    return ESize(kDynamic);
}

long UnaryContainer::ESize::value() const
{
    return mValue;
}

const char* UnaryContainer::ESize::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "fixed",
        "dynamic",
    };
    return names[(size_t)value];
}

const char* UnaryContainer::ESize::shortName() const
{
    return shortName(value());
}

bool UnaryContainer::ESize::operator==(const ESize& rValue) const
{
    return mValue == rValue.mValue;
}

bool UnaryContainer::ESize::operator!=(const ESize& rValue) const
{
    return mValue != rValue.mValue;
}

const UnaryContainer::ESize& UnaryContainer::size() const
{
    return mSize;
}

UnaryContainer& UnaryContainer::set_size(const ESize& size)
{
    mSize = size;
    return *this;
}

UnaryContainer::ESize& UnaryContainer::mutable_size()
{
    return mSize;
}

UnaryContainer& UnaryContainer::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

UnaryContainer& UnaryContainer::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

UnaryContainer& UnaryContainer::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

UnaryContainer& UnaryContainer::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *this;
}

UnaryContainer& UnaryContainer::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *this;
}

UnaryContainer& UnaryContainer::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *this;
}

UnaryContainer& UnaryContainer::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *this;
}

UnaryContainer& UnaryContainer::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *this;
}

UnaryContainer& UnaryContainer::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *this;
}

UnaryContainer& UnaryContainer::set_parameterType(const TypeSPtr& parameterType)
{
    UnaryTemplate::set_parameterType(parameterType);
    return *this;
}

}

}

