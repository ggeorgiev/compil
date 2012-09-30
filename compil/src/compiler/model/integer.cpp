#include "integer.h"
#include "operator.h"

namespace compil
{

Integer::Integer()
{
}

Integer::~Integer()
{
}

bool Integer::hasOperator(const EOperatorAction& action,
                       const EOperatorFlags& flags) const
{
    if (flags.isSet(EOperatorFlags::native()))
    {
        return true;
    }

    return false;
}

}

