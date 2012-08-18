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

SpecimenSPtr Specimen::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Specimen>(pObject);
}

Type::EKind Specimen::alter_kind()
{
    return Type::EKind::object();
}

}

