#include "language/compil/document/specimen.h"

namespace lang
{

namespace compil
{

Specimen::Specimen()
{
}

Specimen::~Specimen()
{
}

bool Specimen::hasOperator(const EOperatorAction& action,
                           const EOperatorFlags& flags) const
{
    SpecimenSPtr base = baseSpecimen().lock();
    if (base)
        return base->hasOperator(action, flags);
        
    TypeSPtr type = parameterType().lock();
    if (type)
        return type->hasOperator(action, flags);
        
    return false;
}

const Type::ELiteral& Specimen::literal() const
{
    SpecimenSPtr base = baseSpecimen().lock();
    if (base)
        return base->literal();
        
    TypeSPtr type = parameterType().lock();
    if (type)
        return type->literal();
        
    return Type::literal();
}

}

}