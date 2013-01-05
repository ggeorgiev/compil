#include "language/compil/document/type.h"

namespace lang
{

namespace compil
{

TypePartial::TypePartial()
{
}

TypePartial::~TypePartial()
{
}

TypeSPtr TypePartial::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Type>(object);
}

TypeSPtr TypePartial::shared_from_this()
{
    return boost::static_pointer_cast<Type>(
        boost::enable_shared_from_this<Object>::shared_from_this());
}

TypeSCPtr TypePartial::shared_from_this() const
{
    return boost::static_pointer_cast<const Type>(
        boost::enable_shared_from_this<Object>::shared_from_this());
}

const PackageSPtr& TypePartial::package() const
{
    return mPackage;
}

PackageSPtr TypePartial::default_package()
{
    static PackageSPtr defaultObject;
    return defaultObject;
}

Type& TypePartial::set_package(const PackageSPtr& package)
{
    mPackage = package;
    return *(Type*)this;
}

const CommentSPtr& TypePartial::comment() const
{
    return mComment;
}

Type& TypePartial::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *(Type*)this;
}

const NameSPtr& TypePartial::name() const
{
    return mName;
}

Type& TypePartial::set_name(const NameSPtr& name)
{
    mName = name;
    return *(Type*)this;
}

TypePartial::ELiteral::ELiteral()
        : mValue(kInvalid)
{
}

TypePartial::ELiteral::ELiteral(long value)
        : mValue(value)
{
}

const TypePartial::ELiteral TypePartial::ELiteral::invalid()
{
    return ELiteral(kInvalid);
}

const TypePartial::ELiteral TypePartial::ELiteral::boolean()
{
    return ELiteral(kBoolean);
}

const TypePartial::ELiteral TypePartial::ELiteral::integer()
{
    return ELiteral(kInteger);
}

const TypePartial::ELiteral TypePartial::ELiteral::real()
{
    return ELiteral(kReal);
}

const TypePartial::ELiteral TypePartial::ELiteral::string()
{
    return ELiteral(kString);
}

const TypePartial::ELiteral TypePartial::ELiteral::binary()
{
    return ELiteral(kBinary);
}

const TypePartial::ELiteral TypePartial::ELiteral::reference()
{
    return ELiteral(kReference);
}

const TypePartial::ELiteral TypePartial::ELiteral::identifier()
{
    return ELiteral(kIdentifier);
}

const TypePartial::ELiteral TypePartial::ELiteral::structure()
{
    return ELiteral(kStructure);
}

long TypePartial::ELiteral::value() const
{
    return mValue;
}

const char* TypePartial::ELiteral::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "boolean",
        "integer",
        "real",
        "string",
        "binary",
        "reference",
        "identifier",
        "structure",
    };
    return names[(size_t)value];
}

const char* TypePartial::ELiteral::shortName() const
{
    return shortName(value());
}

bool TypePartial::ELiteral::operator==(const ELiteral& rValue) const
{
    return mValue == rValue.mValue;
}

bool TypePartial::ELiteral::operator!=(const ELiteral& rValue) const
{
    return mValue != rValue.mValue;
}

const TypePartial::ELiteral& TypePartial::literal() const
{
    return mLiteral;
}

Type& TypePartial::set_literal(const ELiteral& literal)
{
    mLiteral = literal;
    return *(Type*)this;
}

TypePartial::ELiteral& TypePartial::mutable_literal()
{
    return mLiteral;
}

TypePartial::EKind::EKind()
        : mValue(kInvalid)
{
}

TypePartial::EKind::EKind(long value)
        : mValue(value)
{
}

const TypePartial::EKind TypePartial::EKind::invalid()
{
    return EKind(kInvalid);
}

const TypePartial::EKind TypePartial::EKind::builtin()
{
    return EKind(kBuiltin);
}

const TypePartial::EKind TypePartial::EKind::object()
{
    return EKind(kObject);
}

const TypePartial::EKind TypePartial::EKind::string()
{
    return EKind(kString);
}

long TypePartial::EKind::value() const
{
    return mValue;
}

const char* TypePartial::EKind::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "builtin",
        "object",
        "string",
    };
    return names[(size_t)value];
}

const char* TypePartial::EKind::shortName() const
{
    return shortName(value());
}

bool TypePartial::EKind::operator==(const EKind& rValue) const
{
    return mValue == rValue.mValue;
}

bool TypePartial::EKind::operator!=(const EKind& rValue) const
{
    return mValue != rValue.mValue;
}

const TypePartial::EKind& TypePartial::kind() const
{
    return mKind;
}

Type& TypePartial::set_kind(const EKind& kind)
{
    mKind = kind;
    return *(Type*)this;
}

TypePartial::EKind& TypePartial::mutable_kind()
{
    return mKind;
}

Type& TypePartial::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *(Type*)this;
}

Type& TypePartial::set_line(const Line& line)
{
    Object::set_line(line);
    return *(Type*)this;
}

Type& TypePartial::set_column(const Column& column)
{
    Object::set_column(column);
    return *(Type*)this;
}

}

}

