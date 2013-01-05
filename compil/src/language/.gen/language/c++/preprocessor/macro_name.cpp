// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/preprocessor/macro_name.h"

namespace lang
{

namespace cpp
{

MacroName::MacroName()
{
}

MacroName::~MacroName()
{
}

const std::string& MacroName::value() const
{
    return mValue;
}

MacroName& MacroName::set_value(const std::string& value)
{
    mValue = value;
    return *this;
}

std::string& MacroName::mutable_value()
{
    return mValue;
}

MacroName& MacroName::operator<<(const std::string& value)
{
    return set_value(value);
}

const MacroNameSPtr& operator<<(const MacroNameSPtr& object, const std::string& value)
{
    BOOST_ASSERT(object);
    *object << value;
    return object;
}

}

}

