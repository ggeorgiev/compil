#include "package.h"

namespace compil
{

Package::Package()
{
}

Package::~Package()
{
}

PackageSPtr Package::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Package>(pObject);
}

const std::vector<std::string>& Package::elements() const
{
    return mElements;
}

void Package::set_elements(const std::vector<std::string>& elements)
{
    mElements = elements;
}

}

