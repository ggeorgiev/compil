#include "namespace_name.h"

#include "boost/make_shared.hpp"

NamespaceName::NamespaceName()
{
}

NamespaceName::NamespaceName(const std::string& value)
        : mValue(value)
{
}

NamespaceNameSPtr NamespaceName::sptr(const std::string& value)
{
    return boost::make_shared<NamespaceName>(value);
}

