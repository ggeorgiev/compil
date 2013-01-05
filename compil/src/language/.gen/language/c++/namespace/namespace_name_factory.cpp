// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/namespace/namespace_name_factory.h"

namespace lang
{

namespace cpp
{

ENamespaceNameId::ENamespaceNameId()
        : mValue(kInvalid)
{
}

ENamespaceNameId::ENamespaceNameId(long value)
        : mValue(value)
{
}

const ENamespaceNameId ENamespaceNameId::invalid()
{
    return ENamespaceNameId(kInvalid);
}

const ENamespaceNameId ENamespaceNameId::identifierNamespaceName()
{
    return ENamespaceNameId(kIdentifierNamespaceName);
}

const ENamespaceNameId ENamespaceNameId::namespaceName()
{
    return ENamespaceNameId(kNamespaceName);
}

long ENamespaceNameId::value() const
{
    return mValue;
}

const char* ENamespaceNameId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "IdentifierNamespaceName",
        "NamespaceName",
    };
    return names[(size_t)value];
}

const char* ENamespaceNameId::shortName() const
{
    return shortName(value());
}

bool ENamespaceNameId::operator==(const ENamespaceNameId& rValue) const
{
    return mValue == rValue.mValue;
}

bool ENamespaceNameId::operator!=(const ENamespaceNameId& rValue) const
{
    return mValue != rValue.mValue;
}

ENamespaceNameId IdentifierNamespaceName::staticNamespaceNameId()
{
    return ENamespaceNameId::identifierNamespaceName();
}

ENamespaceNameId IdentifierNamespaceName::runtimeNamespaceNameId() const
{
    return staticNamespaceNameId();
}

ENamespaceNameId NamespaceName::staticNamespaceNameId()
{
    return ENamespaceNameId::namespaceName();
}

ENamespaceNameId NamespaceName::runtimeNamespaceNameId() const
{
    return staticNamespaceNameId();
}

NamespaceNameSPtr NamespaceNameFactory::clone(const NamespaceNameSPtr& pObject)
{
    switch (pObject->runtimeNamespaceNameId().value())
    {
        case ENamespaceNameId::kIdentifierNamespaceName:
        {
            IdentifierNamespaceNameSPtr pClone(new IdentifierNamespaceName());
            *pClone = *downcastIdentifierNamespaceName(pObject);
            return pClone;
        }
        case ENamespaceNameId::kNamespaceName:
        {
            NamespaceNameSPtr pClone(new NamespaceName());
            *pClone = *pObject;
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return NamespaceNameSPtr();
}

IdentifierNamespaceNameSPtr NamespaceNameFactory::downcastIdentifierNamespaceName(const NamespaceNameSPtr& pObject)
{
    bool b = (pObject->runtimeNamespaceNameId() == IdentifierNamespaceName::staticNamespaceNameId());

    if (b)
        return boost::static_pointer_cast<IdentifierNamespaceName>(pObject);
    return IdentifierNamespaceNameSPtr();
}

}

}

