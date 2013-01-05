// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/nested_name_specifier.h"

namespace lang
{

namespace cpp
{

NestedNameSpecifier::NestedNameSpecifier()
{
}

NestedNameSpecifier::~NestedNameSpecifier()
{
}

NestedNameSpecifierSPtr NestedNameSpecifier::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<NestedNameSpecifier>(object);
}

const NestedNameSPtr& NestedNameSpecifier::name() const
{
    return mName;
}

NestedNameSpecifier& NestedNameSpecifier::set_name(const NestedNameSPtr& name)
{
    mName = name;
    return *this;
}

NestedNameSpecifier& NestedNameSpecifier::operator<<(const NestedNameSPtr& name)
{
    return set_name(name);
}

const NestedNameSpecifierSPtr& operator<<(const NestedNameSpecifierSPtr& object, const NestedNameSPtr& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const NestedNameSpecifierSPtr& NestedNameSpecifier::specifier() const
{
    return mSpecifier;
}

NestedNameSpecifier& NestedNameSpecifier::set_specifier(const NestedNameSpecifierSPtr& specifier)
{
    mSpecifier = specifier;
    return *this;
}

NestedNameSpecifier& NestedNameSpecifier::operator<<(const NestedNameSpecifierSPtr& specifier)
{
    return set_specifier(specifier);
}

const NestedNameSpecifierSPtr& operator<<(const NestedNameSpecifierSPtr& object,
                                          const NestedNameSpecifierSPtr& specifier)
{
    BOOST_ASSERT(object);
    *object << specifier;
    return object;
}

}

}

