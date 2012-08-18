#include "structure.h"

namespace compil
{

StructurePartial::StructurePartial()
{
    set_literal(alter_literal());
    set_kind(alter_kind());
}

StructurePartial::~StructurePartial()
{
}

StructureSPtr StructurePartial::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Structure>(pObject);
}

StructureSPtr StructurePartial::shared_from_this()
{
    return boost::static_pointer_cast<Structure>(
        boost::enable_shared_from_this<Object>::shared_from_this());
}

StructureSCPtr StructurePartial::shared_from_this() const
{
    return boost::static_pointer_cast<const Structure>(
        boost::enable_shared_from_this<Object>::shared_from_this());
}

Type::ELiteral StructurePartial::alter_literal()
{
    return Type::ELiteral::structure();
}

Type::EKind StructurePartial::alter_kind()
{
    return Type::EKind::object();
}

bool StructurePartial::abstract() const
{
    return mAbstract;
}

void StructurePartial::set_abstract(bool abstract)
{
    mAbstract = abstract;
}

bool StructurePartial::controlled() const
{
    return mControlled;
}

void StructurePartial::set_controlled(bool controlled)
{
    mControlled = controlled;
}

bool StructurePartial::immutable() const
{
    return mImmutable;
}

void StructurePartial::set_immutable(bool immutable)
{
    mImmutable = immutable;
}

bool StructurePartial::partial() const
{
    return mPartial;
}

void StructurePartial::set_partial(bool partial)
{
    mPartial = partial;
}

bool StructurePartial::sharable() const
{
    return mSharable;
}

void StructurePartial::set_sharable(bool sharable)
{
    mSharable = sharable;
}

bool StructurePartial::streamable() const
{
    return mStreamable;
}

void StructurePartial::set_streamable(bool streamable)
{
    mStreamable = streamable;
}

const std::vector<ObjectSPtr>& StructurePartial::objects() const
{
    return mObjects;
}

void StructurePartial::set_objects(const std::vector<ObjectSPtr>& objects)
{
    mObjects = objects;
}

const StructureWPtr& StructurePartial::baseStructure() const
{
    return mBaseStructure;
}

StructureWPtr StructurePartial::default_baseStructure()
{
    static StructureWPtr defaultObject;
    return defaultObject;
}

void StructurePartial::set_baseStructure(const StructureSPtr& baseStructure)
{
    mBaseStructure = baseStructure;
}

}

