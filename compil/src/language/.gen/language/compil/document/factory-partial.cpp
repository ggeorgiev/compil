#include "language/compil/document/factory.h"

namespace lang
{

namespace compil
{

FactoryPartial::FactoryPartial()
{
    set_kind(alter_kind());
}

FactoryPartial::~FactoryPartial()
{
}

FactorySPtr FactoryPartial::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Factory>(object);
}

TypePartial::EKind FactoryPartial::alter_kind()
{
    return TypePartial::EKind::object();
}

FactoryPartial::EType::EType()
        : mValue(kInvalid)
{
}

FactoryPartial::EType::EType(long value)
        : mValue(value)
{
}

const FactoryPartial::EType FactoryPartial::EType::invalid()
{
    return EType(kInvalid);
}

const FactoryPartial::EType FactoryPartial::EType::hierarchy()
{
    return EType(kHierarchy);
}

const FactoryPartial::EType FactoryPartial::EType::object()
{
    return EType(kObject);
}

const FactoryPartial::EType FactoryPartial::EType::plugin()
{
    return EType(kPlugin);
}

long FactoryPartial::EType::value() const
{
    return mValue;
}

const char* FactoryPartial::EType::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "hierarchy",
        "object",
        "plugin",
    };
    return names[(size_t)value];
}

const char* FactoryPartial::EType::shortName() const
{
    return shortName(value());
}

bool FactoryPartial::EType::operator==(const EType& rValue) const
{
    return mValue == rValue.mValue;
}

bool FactoryPartial::EType::operator!=(const EType& rValue) const
{
    return mValue != rValue.mValue;
}

const FactoryPartial::EType& FactoryPartial::type() const
{
    return mType;
}

Factory& FactoryPartial::set_type(const EType& type)
{
    mType = type;
    return *(Factory*)this;
}

FactoryPartial::EType& FactoryPartial::mutable_type()
{
    return mType;
}

bool FactoryPartial::function() const
{
    return mFunction;
}

Factory& FactoryPartial::set_function(bool function)
{
    mFunction = function;
    return *(Factory*)this;
}

const std::vector<FilterSPtr>& FactoryPartial::filters() const
{
    return mFilters;
}

Factory& FactoryPartial::set_filters(const std::vector<FilterSPtr>& filters)
{
    mFilters = filters;
    return *(Factory*)this;
}

std::vector<FilterSPtr>& FactoryPartial::mutable_filters()
{
    return mFilters;
}

Factory& FactoryPartial::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_line(const Line& line)
{
    Object::set_line(line);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_column(const Column& column)
{
    Object::set_column(column);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *(Factory*)this;
}

Factory& FactoryPartial::set_parameterType(const TypeSPtr& parameterType)
{
    UnaryTemplate::set_parameterType(parameterType);
    return *(Factory*)this;
}

}

}

