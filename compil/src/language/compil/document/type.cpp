#include "language/compil/document/type.h"
#include "language/compil/document/operator.h"

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
    return false;
}

}

}
