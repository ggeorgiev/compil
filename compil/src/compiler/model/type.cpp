#include "type.h"

namespace compil
{

Type::Type()
{
}

Type::~Type()
{
}

TypeSPtr Type::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Type>(object);
}

TypeSPtr Type::shared_from_this()
{
    return boost::static_pointer_cast<Type>(
        boost::enable_shared_from_this<Object>::shared_from_this());
}

TypeSCPtr Type::shared_from_this() const
{
    return boost::static_pointer_cast<const Type>(
        boost::enable_shared_from_this<Object>::shared_from_this());
}

const PackageSPtr& Type::package() const
{
    return mPackage;
}

PackageSPtr Type::default_package()
{
    static PackageSPtr defaultObject;
    return defaultObject;
}

Type& Type::set_package(const PackageSPtr& package)
{
    mPackage = package;
    return *this;
}

const CommentSPtr& Type::comment() const
{
    return mComment;
}

Type& Type::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const NameSPtr& Type::name() const
{
    return mName;
}

Type& Type::set_name(const NameSPtr& name)
{
    mName = name;
    return *this;
}

Type::ELiteral::ELiteral()
        : mValue(kInvalid)
{
}

Type::ELiteral::ELiteral(long value)
        : mValue(value)
{
}

const Type::ELiteral Type::ELiteral::invalid()
{
    return ELiteral(kInvalid);
}

const Type::ELiteral Type::ELiteral::boolean()
{
    return ELiteral(kBoolean);
}

const Type::ELiteral Type::ELiteral::integer()
{
    return ELiteral(kInteger);
}

const Type::ELiteral Type::ELiteral::real()
{
    return ELiteral(kReal);
}

const Type::ELiteral Type::ELiteral::string()
{
    return ELiteral(kString);
}

const Type::ELiteral Type::ELiteral::binary()
{
    return ELiteral(kBinary);
}

const Type::ELiteral Type::ELiteral::reference()
{
    return ELiteral(kReference);
}

const Type::ELiteral Type::ELiteral::identifier()
{
    return ELiteral(kIdentifier);
}

const Type::ELiteral Type::ELiteral::structure()
{
    return ELiteral(kStructure);
}

long Type::ELiteral::value() const
{
    return mValue;
}

const char* Type::ELiteral::shortName(long value)
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

const char* Type::ELiteral::shortName() const
{
    return shortName(value());
}

bool Type::ELiteral::operator==(const ELiteral& rValue) const
{
    return mValue == rValue.mValue;
}

bool Type::ELiteral::operator!=(const ELiteral& rValue) const
{
    return mValue != rValue.mValue;
}

const Type::ELiteral& Type::literal() const
{
    return mLiteral;
}

Type& Type::set_literal(const ELiteral& literal)
{
    mLiteral = literal;
    return *this;
}

Type::ELiteral& Type::mutable_literal()
{
    return mLiteral;
}

Type::EKind::EKind()
        : mValue(kInvalid)
{
}

Type::EKind::EKind(long value)
        : mValue(value)
{
}

const Type::EKind Type::EKind::invalid()
{
    return EKind(kInvalid);
}

const Type::EKind Type::EKind::builtin()
{
    return EKind(kBuiltin);
}

const Type::EKind Type::EKind::object()
{
    return EKind(kObject);
}

const Type::EKind Type::EKind::string()
{
    return EKind(kString);
}

long Type::EKind::value() const
{
    return mValue;
}

const char* Type::EKind::shortName(long value)
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

const char* Type::EKind::shortName() const
{
    return shortName(value());
}

bool Type::EKind::operator==(const EKind& rValue) const
{
    return mValue == rValue.mValue;
}

bool Type::EKind::operator!=(const EKind& rValue) const
{
    return mValue != rValue.mValue;
}

const Type::EKind& Type::kind() const
{
    return mKind;
}

Type& Type::set_kind(const EKind& kind)
{
    mKind = kind;
    return *this;
}

Type::EKind& Type::mutable_kind()
{
    return mKind;
}

}

