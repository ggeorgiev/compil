// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declarator/parameter_declaratoin_list.h"

namespace lang
{

namespace cpp
{

ParameterDeclarationList::ParameterDeclarationList()
{
}

ParameterDeclarationList::~ParameterDeclarationList()
{
}

ParameterDeclarationListSPtr ParameterDeclarationList::downcast(const DeclaratorSPtr& object)
{
    return boost::static_pointer_cast<ParameterDeclarationList>(object);
}

const std::vector<ParameterDeclarationSPtr>& ParameterDeclarationList::declarators() const
{
    return mDeclarators;
}

ParameterDeclarationList& ParameterDeclarationList::set_declarators(const std::vector<ParameterDeclarationSPtr>& declarators)
{
    mDeclarators = declarators;
    return *this;
}

std::vector<ParameterDeclarationSPtr>& ParameterDeclarationList::mutable_declarators()
{
    return mDeclarators;
}

ParameterDeclarationList& ParameterDeclarationList::operator<<(const std::vector<ParameterDeclarationSPtr>& declarators)
{
    return set_declarators(declarators);
}

const ParameterDeclarationListSPtr& operator<<(const ParameterDeclarationListSPtr& object,
                                               const std::vector<ParameterDeclarationSPtr>& declarators)
{
    BOOST_ASSERT(object);
    *object << declarators;
    return object;
}

ParameterDeclarationList& ParameterDeclarationList::operator<<(const ParameterDeclarationSPtr& declaratorsItem)
{
    mDeclarators.push_back(declaratorsItem);
    return *this;
}

const ParameterDeclarationListSPtr& operator<<(const ParameterDeclarationListSPtr& object,
                                               const ParameterDeclarationSPtr& declaratorsItem)
{
    BOOST_ASSERT(object);
    *object << declaratorsItem;
    return object;
}

}

}

