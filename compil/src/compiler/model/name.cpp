#include "name.h"

namespace compil
{

Name::Name()
{
}

Name::~Name()
{
}

NameSPtr Name::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Name>(pObject);
}

const std::string& Name::value() const
{
    return mValue;
}

void Name::set_value(const std::string& value)
{
    mValue = value;
}

}

