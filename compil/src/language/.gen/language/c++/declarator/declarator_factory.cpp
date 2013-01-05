// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declarator/declarator_factory.h"

namespace lang
{

namespace cpp
{

EDeclaratorId::EDeclaratorId()
        : mValue(kInvalid)
{
}

EDeclaratorId::EDeclaratorId(long value)
        : mValue(value)
{
}

const EDeclaratorId EDeclaratorId::invalid()
{
    return EDeclaratorId(kInvalid);
}

const EDeclaratorId EDeclaratorId::declarator()
{
    return EDeclaratorId(kDeclarator);
}

const EDeclaratorId EDeclaratorId::declaratorId()
{
    return EDeclaratorId(kDeclaratorId);
}

const EDeclaratorId EDeclaratorId::declaratorIdDirectDeclarator()
{
    return EDeclaratorId(kDeclaratorIdDirectDeclarator);
}

const EDeclaratorId EDeclaratorId::directDeclarator()
{
    return EDeclaratorId(kDirectDeclarator);
}

long EDeclaratorId::value() const
{
    return mValue;
}

const char* EDeclaratorId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "Declarator",
        "DeclaratorId",
        "DeclaratorIdDirectDeclarator",
        "DirectDeclarator",
    };
    return names[(size_t)value];
}

const char* EDeclaratorId::shortName() const
{
    return shortName(value());
}

bool EDeclaratorId::operator==(const EDeclaratorId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EDeclaratorId::operator!=(const EDeclaratorId& rValue) const
{
    return mValue != rValue.mValue;
}

EDeclaratorId Declarator::staticDeclaratorId()
{
    return EDeclaratorId::declarator();
}

EDeclaratorId Declarator::runtimeDeclaratorId() const
{
    return staticDeclaratorId();
}

EDeclaratorId DeclaratorId::staticDeclaratorId()
{
    return EDeclaratorId::declaratorId();
}

EDeclaratorId DeclaratorId::runtimeDeclaratorId() const
{
    return staticDeclaratorId();
}

EDeclaratorId DeclaratorIdDirectDeclarator::staticDeclaratorId()
{
    return EDeclaratorId::declaratorIdDirectDeclarator();
}

EDeclaratorId DeclaratorIdDirectDeclarator::runtimeDeclaratorId() const
{
    return staticDeclaratorId();
}

EDeclaratorId DirectDeclarator::staticDeclaratorId()
{
    return EDeclaratorId::directDeclarator();
}

EDeclaratorId DirectDeclarator::runtimeDeclaratorId() const
{
    return staticDeclaratorId();
}

DeclaratorSPtr DeclaratorFactory::clone(const DeclaratorSPtr& pObject)
{
    switch (pObject->runtimeDeclaratorId().value())
    {
        case EDeclaratorId::kDeclarator:
        {
            DeclaratorSPtr pClone(new Declarator());
            *pClone = *pObject;
            return pClone;
        }
        case EDeclaratorId::kDeclaratorId:
        {
            DeclaratorIdSPtr pClone(new DeclaratorId());
            *pClone = *downcastDeclaratorId(pObject);
            return pClone;
        }
        case EDeclaratorId::kDeclaratorIdDirectDeclarator:
        {
            DeclaratorIdDirectDeclaratorSPtr pClone(new DeclaratorIdDirectDeclarator());
            *pClone = *downcastDeclaratorIdDirectDeclarator(pObject);
            return pClone;
        }
        case EDeclaratorId::kDirectDeclarator:
        {
            DirectDeclaratorSPtr pClone(new DirectDeclarator());
            *pClone = *downcastDirectDeclarator(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return DeclaratorSPtr();
}

DeclaratorIdSPtr DeclaratorFactory::downcastDeclaratorId(const DeclaratorSPtr& pObject)
{
    bool b = (pObject->runtimeDeclaratorId() == DeclaratorId::staticDeclaratorId());

    if (b)
        return boost::static_pointer_cast<DeclaratorId>(pObject);
    return DeclaratorIdSPtr();
}

DeclaratorIdDirectDeclaratorSPtr DeclaratorFactory::downcastDeclaratorIdDirectDeclarator(const DeclaratorSPtr& pObject)
{
    bool b = (pObject->runtimeDeclaratorId() == DeclaratorIdDirectDeclarator::staticDeclaratorId());

    if (b)
        return boost::static_pointer_cast<DeclaratorIdDirectDeclarator>(pObject);
    return DeclaratorIdDirectDeclaratorSPtr();
}

DirectDeclaratorSPtr DeclaratorFactory::downcastDirectDeclarator(const DeclaratorSPtr& pObject)
{
    bool b = (pObject->runtimeDeclaratorId() == DirectDeclarator::staticDeclaratorId());

    if (b)
        return boost::static_pointer_cast<DirectDeclarator>(pObject);
    return DirectDeclaratorSPtr();
}

}

}

