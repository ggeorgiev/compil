#include "language/compil/document/type.h"
#include "language/compil/document/operator.h"

namespace lang
{

namespace compil
{

size_t Type::hasher::operator()(const EOperatorAction& action) const
{
    return boost::hash_value(action.value());
}

Type::Type()
{
}

Type::~Type()
{
}

bool Type::hasOperator(const EOperatorAction& action,
                       const EOperatorFlags& flags) const
{
    boost::unordered_map<EOperatorAction, EOperatorFlags, hasher>::const_iterator it = mOperatorSupport.find(action);
    if (it == mOperatorSupport.end())
        return false;
    return it->second.isSet(flags);
}

const Type::ELiteral& Type::literal() const
{
    return TypePartial::literal();
}

}

}
