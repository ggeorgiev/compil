#include "language/compil/document/unary_template.h"

namespace lang
{

namespace compil
{

UnaryTemplate::UnaryTemplate()
{
}

UnaryTemplate::~UnaryTemplate()
{
}

UnaryTemplateSPtr UnaryTemplate::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<UnaryTemplate>(object);
}

const TypeWPtr& UnaryTemplate::parameterType() const
{
    return mParameterType;
}

TypeWPtr UnaryTemplate::default_parameterType()
{
    static TypeWPtr defaultObject;
    return defaultObject;
}

UnaryTemplate& UnaryTemplate::set_parameterType(const TypeSPtr& parameterType)
{
    mParameterType = parameterType;
    return *this;
}

UnaryTemplate& UnaryTemplate::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_package(const PackageSPtr& package)
{
    TypePartial::set_package(package);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_comment(const CommentSPtr& comment)
{
    TypePartial::set_comment(comment);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_name(const NameSPtr& name)
{
    TypePartial::set_name(name);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_literal(const ELiteral& literal)
{
    TypePartial::set_literal(literal);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_kind(const EKind& kind)
{
    TypePartial::set_kind(kind);
    return *this;
}

UnaryTemplate& UnaryTemplate::set_cast(const ECast& cast)
{
    CastableType::set_cast(cast);
    return *this;
}

}

}

