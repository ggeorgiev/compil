// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/class/method_name_factory.h"

namespace lang
{

namespace cpp
{

EMethodNameId::EMethodNameId()
        : mValue(kInvalid)
{
}

EMethodNameId::EMethodNameId(long value)
        : mValue(value)
{
}

const EMethodNameId EMethodNameId::invalid()
{
    return EMethodNameId(kInvalid);
}

const EMethodNameId EMethodNameId::identifierMethodName()
{
    return EMethodNameId(kIdentifierMethodName);
}

const EMethodNameId EMethodNameId::methodName()
{
    return EMethodNameId(kMethodName);
}

const EMethodNameId EMethodNameId::operatorMethodName()
{
    return EMethodNameId(kOperatorMethodName);
}

long EMethodNameId::value() const
{
    return mValue;
}

const char* EMethodNameId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "IdentifierMethodName",
        "MethodName",
        "OperatorMethodName",
    };
    return names[(size_t)value];
}

const char* EMethodNameId::shortName() const
{
    return shortName(value());
}

bool EMethodNameId::operator==(const EMethodNameId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EMethodNameId::operator!=(const EMethodNameId& rValue) const
{
    return mValue != rValue.mValue;
}

EMethodNameId IdentifierMethodName::staticMethodNameId()
{
    return EMethodNameId::identifierMethodName();
}

EMethodNameId IdentifierMethodName::runtimeMethodNameId() const
{
    return staticMethodNameId();
}

EMethodNameId MethodName::staticMethodNameId()
{
    return EMethodNameId::methodName();
}

EMethodNameId MethodName::runtimeMethodNameId() const
{
    return staticMethodNameId();
}

EMethodNameId OperatorMethodName::staticMethodNameId()
{
    return EMethodNameId::operatorMethodName();
}

EMethodNameId OperatorMethodName::runtimeMethodNameId() const
{
    return staticMethodNameId();
}

MethodNameSPtr MethodNameFactory::clone(const MethodNameSPtr& pObject)
{
    switch (pObject->runtimeMethodNameId().value())
    {
        case EMethodNameId::kIdentifierMethodName:
        {
            IdentifierMethodNameSPtr pClone(new IdentifierMethodName());
            *pClone = *downcastIdentifierMethodName(pObject);
            return pClone;
        }
        case EMethodNameId::kMethodName:
        {
            MethodNameSPtr pClone(new MethodName());
            *pClone = *pObject;
            return pClone;
        }
        case EMethodNameId::kOperatorMethodName:
        {
            OperatorMethodNameSPtr pClone(new OperatorMethodName());
            *pClone = *downcastOperatorMethodName(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return MethodNameSPtr();
}

IdentifierMethodNameSPtr MethodNameFactory::downcastIdentifierMethodName(const MethodNameSPtr& pObject)
{
    bool b = (pObject->runtimeMethodNameId() == IdentifierMethodName::staticMethodNameId());

    if (b)
        return boost::static_pointer_cast<IdentifierMethodName>(pObject);
    return IdentifierMethodNameSPtr();
}

OperatorMethodNameSPtr MethodNameFactory::downcastOperatorMethodName(const MethodNameSPtr& pObject)
{
    bool b = (pObject->runtimeMethodNameId() == OperatorMethodName::staticMethodNameId());

    if (b)
        return boost::static_pointer_cast<OperatorMethodName>(pObject);
    return OperatorMethodNameSPtr();
}

}

}

