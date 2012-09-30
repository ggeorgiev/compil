#include "type.h"
#include "operator.h"

namespace compil
{

Type::Type()
{
}

Type::~Type()
{
}

bool Type::hasOperator(const EOperatorAction& action,
                       const EOperatorFlags& flags) const
{
    return true;
}

}

