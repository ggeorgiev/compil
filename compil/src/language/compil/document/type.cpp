#include "compil/document/type.h"
#include "compil/document/operator.h"

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