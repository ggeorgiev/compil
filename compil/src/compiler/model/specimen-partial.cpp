#include "specimen.h"

namespace compil
{

SpecimenPartial::SpecimenPartial()
{
    set_kind(alter_kind());
}

SpecimenPartial::~SpecimenPartial()
{
}

SpecimenSPtr SpecimenPartial::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Specimen>(object);
}

TypePartial::EKind SpecimenPartial::alter_kind()
{
    return TypePartial::EKind::object();
}

const SpecimenWPtr& SpecimenPartial::baseSpecimen() const
{
    return mBaseSpecimen;
}

SpecimenWPtr SpecimenPartial::default_baseSpecimen()
{
    static SpecimenWPtr defaultObject;
    return defaultObject;
}

Specimen& SpecimenPartial::set_baseSpecimen(const SpecimenSPtr& baseSpecimen)
{
    mBaseSpecimen = baseSpecimen;
    return *(Specimen*)this;
}

}

