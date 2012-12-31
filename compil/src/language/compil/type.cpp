#include "compil/type.h"
#include "compil/operator.h"

namespace lang
{

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

}
