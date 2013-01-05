// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/all/scope.h"

namespace lang
{

namespace all
{

Scope::Scope()
{
}

Scope::~Scope()
{
}

Scope::ESquiggles::ESquiggles()
        : mValue(kInvalid)
{
}

Scope::ESquiggles::ESquiggles(long value)
        : mValue(value)
{
}

const Scope::ESquiggles Scope::ESquiggles::invalid()
{
    return ESquiggles(kInvalid);
}

const Scope::ESquiggles Scope::ESquiggles::none()
{
    return ESquiggles(kNone);
}

const Scope::ESquiggles Scope::ESquiggles::brackets()
{
    return ESquiggles(kBrackets);
}

long Scope::ESquiggles::value() const
{
    return mValue;
}

const char* Scope::ESquiggles::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "none",
        "brackets",
    };
    return names[(size_t)value];
}

const char* Scope::ESquiggles::shortName() const
{
    return shortName(value());
}

bool Scope::ESquiggles::operator==(const ESquiggles& rValue) const
{
    return mValue == rValue.mValue;
}

bool Scope::ESquiggles::operator!=(const ESquiggles& rValue) const
{
    return mValue != rValue.mValue;
}

const Scope::ESquiggles& Scope::squiggles() const
{
    return mSquiggles;
}

Scope& Scope::set_squiggles(const ESquiggles& squiggles)
{
    mSquiggles = squiggles;
    return *this;
}

Scope::ESquiggles& Scope::mutable_squiggles()
{
    return mSquiggles;
}

Scope& Scope::operator<<(const ESquiggles& squiggles)
{
    return set_squiggles(squiggles);
}

const ScopeSPtr& operator<<(const ScopeSPtr& object, const Scope::ESquiggles& squiggles)
{
    BOOST_ASSERT(object);
    *object << squiggles;
    return object;
}

const std::vector<std::string>& Scope::lines() const
{
    return mLines;
}

Scope& Scope::set_lines(const std::vector<std::string>& lines)
{
    mLines = lines;
    return *this;
}

std::vector<std::string>& Scope::mutable_lines()
{
    return mLines;
}

Scope& Scope::operator<<(const std::vector<std::string>& lines)
{
    return set_lines(lines);
}

const ScopeSPtr& operator<<(const ScopeSPtr& object, const std::vector<std::string>& lines)
{
    BOOST_ASSERT(object);
    *object << lines;
    return object;
}

Scope& Scope::operator<<(const std::string& linesItem)
{
    mLines.push_back(linesItem);
    return *this;
}

const ScopeSPtr& operator<<(const ScopeSPtr& object, const std::string& linesItem)
{
    BOOST_ASSERT(object);
    *object << linesItem;
    return object;
}

}

}

