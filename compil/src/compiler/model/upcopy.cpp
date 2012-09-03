#include "upcopy.h"

namespace compil
{

Upcopy::Upcopy()
{
}

Upcopy::~Upcopy()
{
}

UpcopySPtr Upcopy::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Upcopy>(pObject);
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

}

