#include "specimen.h"

namespace compil
{

Specimen::Specimen()
{
    set_kind(alter_kind());
}

Specimen::~Specimen()
{
}

SpecimenSPtr Specimen::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Specimen>(object);
}

Type::EKind Specimen::alter_kind()
{
    return Type::EKind::object();
}

const SpecimenWPtr& Specimen::baseSpecimen() const
{
    return mBaseSpecimen;
}

SpecimenWPtr Specimen::default_baseSpecimen()
{
    static SpecimenWPtr defaultObject;
    return defaultObject;
}

Specimen& Specimen::set_baseSpecimen(const SpecimenSPtr& baseSpecimen)
{
    mBaseSpecimen = baseSpecimen;
    return *this;
}

}

