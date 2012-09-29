#include "name.h"

namespace compil
{

Name::Name()
{
}

Name::~Name()
{
}

NameSPtr Name::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Name>(object);
}

const std::string& Name::value() const
{
    return mValue;
}

Name& Name::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& Name::mutable_value()
{
    return mValue;
}

}

