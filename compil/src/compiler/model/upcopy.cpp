// Boost C++ Utility
#include <boost/assert.hpp>

#include "upcopy.h"

namespace compil
{

int Upcopy::bitmask_comment()
{
    return 0x1;
}

int Upcopy::bitmask_structure()
{
    return 0x2;
}

int Upcopy::bitmask_baseStructure()
{
    return 0x4;
}

Upcopy::Upcopy()
        : mBits(0)
{
}

Upcopy::~Upcopy()
{
}

UpcopySPtr Upcopy::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Upcopy>(pObject);
}

bool Upcopy::isInitialized() const
{
    // structure Object is not controlled. This function assume it is initilized
    if (!valid_comment()) return false;
    if (!valid_structure()) return false;
    if (!valid_baseStructure()) return false;
    return true;
}

const CommentSPtr& Upcopy::comment() const
{
    BOOST_ASSERT(valid_comment());
    return mComment;
}

bool Upcopy::valid_comment() const
{
    return (mBits & bitmask_comment()) != 0;
}

void Upcopy::set_comment(const CommentSPtr& comment)
{
    mComment  = comment;
    mBits    |= bitmask_comment();
}

void Upcopy::erase_comment()
{
    mComment.reset();
    mBits &= ~bitmask_comment();
}

const StructureWPtr& Upcopy::structure() const
{
    BOOST_ASSERT(valid_structure());
    return mStructure;
}

bool Upcopy::valid_structure() const
{
    return (mBits & bitmask_structure()) != 0;
}

void Upcopy::set_structure(const StructureSPtr& structure)
{
    mStructure  = structure;
    mBits      |= bitmask_structure();
}

void Upcopy::erase_structure()
{
    mStructure.reset();
    mBits &= ~bitmask_structure();
}

const StructureSPtr& Upcopy::baseStructure() const
{
    BOOST_ASSERT(valid_baseStructure());
    return mBaseStructure;
}

bool Upcopy::valid_baseStructure() const
{
    return (mBits & bitmask_baseStructure()) != 0;
}

void Upcopy::set_baseStructure(const StructureSPtr& baseStructure)
{
    mBaseStructure  = baseStructure;
    mBits          |= bitmask_baseStructure();
}

void Upcopy::erase_baseStructure()
{
    mBaseStructure.reset();
    mBits &= ~bitmask_baseStructure();
}

}

