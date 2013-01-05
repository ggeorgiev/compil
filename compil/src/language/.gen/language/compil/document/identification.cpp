#include "language/compil/document/identification.h"

namespace lang
{

namespace compil
{

Identification::Identification()
{
}

Identification::~Identification()
{
}

IdentificationSPtr Identification::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Identification>(object);
}

Identification::EType::EType()
        : mValue(kInvalid)
{
}

Identification::EType::EType(long value)
        : mValue(value)
{
}

const Identification::EType Identification::EType::invalid()
{
    return EType(kInvalid);
}

const Identification::EType Identification::EType::runtime()
{
    return EType(kRuntime);
}

const Identification::EType Identification::EType::inproc()
{
    return EType(kInproc);
}

long Identification::EType::value() const
{
    return mValue;
}

const char* Identification::EType::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "runtime",
        "inproc",
    };
    return names[(size_t)value];
}

const char* Identification::EType::shortName() const
{
    return shortName(value());
}

bool Identification::EType::operator==(const EType& rValue) const
{
    return mValue == rValue.mValue;
}

bool Identification::EType::operator!=(const EType& rValue) const
{
    return mValue != rValue.mValue;
}

const Identification::EType& Identification::type() const
{
    return mType;
}

Identification& Identification::set_type(const EType& type)
{
    mType = type;
    return *this;
}

Identification::EType& Identification::mutable_type()
{
    return mType;
}

const StructureWPtr& Identification::structure() const
{
    return mStructure;
}

Identification& Identification::set_structure(const StructureSPtr& structure)
{
    mStructure = structure;
    return *this;
}

const CommentSPtr& Identification::comment() const
{
    return mComment;
}

Identification& Identification::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

Identification& Identification::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Identification& Identification::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Identification& Identification::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

