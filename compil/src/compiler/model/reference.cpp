#include "reference.h"

namespace compil
{

Reference::Reference()
{
}

Reference::~Reference()
{
}

ReferenceSPtr Reference::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Reference>(object);
}

bool Reference::weak() const
{
    return mWeak;
}

Reference& Reference::set_weak(bool weak)
{
    mWeak = weak;
    return *this;
}

}

