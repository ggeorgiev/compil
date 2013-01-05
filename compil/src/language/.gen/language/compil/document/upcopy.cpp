#include "language/compil/document/upcopy.h"

namespace lang
{

namespace compil
{

Upcopy::Upcopy()
{
}

Upcopy::~Upcopy()
{
}

UpcopySPtr Upcopy::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Upcopy>(object);
}

const CommentSPtr& Upcopy::comment() const
{
    return mComment;
}

Upcopy& Upcopy::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const StructureWPtr& Upcopy::structure() const
{
    return mStructure;
}

Upcopy& Upcopy::set_structure(const StructureSPtr& structure)
{
    mStructure = structure;
    return *this;
}

const StructureSPtr& Upcopy::baseStructure() const
{
    return mBaseStructure;
}

Upcopy& Upcopy::set_baseStructure(const StructureSPtr& baseStructure)
{
    mBaseStructure = baseStructure;
    return *this;
}

Upcopy& Upcopy::set_sourceId(const SourceIdSPtr& sourceId)
{
    Object::set_sourceId(sourceId);
    return *this;
}

Upcopy& Upcopy::set_line(const Line& line)
{
    Object::set_line(line);
    return *this;
}

Upcopy& Upcopy::set_column(const Column& column)
{
    Object::set_column(column);
    return *this;
}

}

}

