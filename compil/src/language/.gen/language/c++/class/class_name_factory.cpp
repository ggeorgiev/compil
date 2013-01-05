// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/class/class_name_factory.h"

namespace lang
{

namespace cpp
{

EClassNameId::EClassNameId()
        : mValue(kInvalid)
{
}

EClassNameId::EClassNameId(long value)
        : mValue(value)
{
}

const EClassNameId EClassNameId::invalid()
{
    return EClassNameId(kInvalid);
}

const EClassNameId EClassNameId::className()
{
    return EClassNameId(kClassName);
}

const EClassNameId EClassNameId::identifierClassName()
{
    return EClassNameId(kIdentifierClassName);
}

long EClassNameId::value() const
{
    return mValue;
}

const char* EClassNameId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "ClassName",
        "IdentifierClassName",
    };
    return names[(size_t)value];
}

const char* EClassNameId::shortName() const
{
    return shortName(value());
}

bool EClassNameId::operator==(const EClassNameId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EClassNameId::operator!=(const EClassNameId& rValue) const
{
    return mValue != rValue.mValue;
}

EClassNameId ClassName::staticClassNameId()
{
    return EClassNameId::className();
}

EClassNameId ClassName::runtimeClassNameId() const
{
    return staticClassNameId();
}

EClassNameId IdentifierClassName::staticClassNameId()
{
    return EClassNameId::identifierClassName();
}

EClassNameId IdentifierClassName::runtimeClassNameId() const
{
    return staticClassNameId();
}

ClassNameSPtr ClassNameFactory::clone(const ClassNameSPtr& pObject)
{
    switch (pObject->runtimeClassNameId().value())
    {
        case EClassNameId::kClassName:
        {
            ClassNameSPtr pClone(new ClassName());
            *pClone = *pObject;
            return pClone;
        }
        case EClassNameId::kIdentifierClassName:
        {
            IdentifierClassNameSPtr pClone(new IdentifierClassName());
            *pClone = *downcastIdentifierClassName(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return ClassNameSPtr();
}

IdentifierClassNameSPtr ClassNameFactory::downcastIdentifierClassName(const ClassNameSPtr& pObject)
{
    bool b = (pObject->runtimeClassNameId() == IdentifierClassName::staticClassNameId());

    if (b)
        return boost::static_pointer_cast<IdentifierClassName>(pObject);
    return IdentifierClassNameSPtr();
}

}

}

