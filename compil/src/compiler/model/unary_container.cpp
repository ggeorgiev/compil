#include "unary_container.h"

namespace compil
{

UnaryContainer::UnaryContainer()
{
}

UnaryContainer::~UnaryContainer()
{
}

UnaryContainerSPtr UnaryContainer::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<UnaryContainer>(object);
}

UnaryContainer::ESize::ESize()
        : mValue(kInvalid)
{
}

UnaryContainer::ESize::ESize(long value)
        : mValue(value)
{
}

const UnaryContainer::ESize UnaryContainer::ESize::invalid()
{
    return ESize(kInvalid);
}

const UnaryContainer::ESize UnaryContainer::ESize::fixed()
{
    return ESize(kFixed);
}

const UnaryContainer::ESize UnaryContainer::ESize::dynamic()
{
    return ESize(kDynamic);
}

long UnaryContainer::ESize::value() const
{
    return mValue;
}

const char* UnaryContainer::ESize::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "fixed",
        "dynamic",
    };
    return names[(size_t)value];
}

const char* UnaryContainer::ESize::shortName() const
{
    return shortName(value());
}

bool UnaryContainer::ESize::operator==(const ESize& rValue) const
{
    return mValue == rValue.mValue;
}

bool UnaryContainer::ESize::operator!=(const ESize& rValue) const
{
    return mValue != rValue.mValue;
}

const UnaryContainer::ESize& UnaryContainer::size() const
{
    return mSize;
}

UnaryContainer& UnaryContainer::set_size(const ESize& size)
{
    mSize = size;
    return *this;
}

UnaryContainer::ESize& UnaryContainer::mutable_size()
{
    return mSize;
}

}

