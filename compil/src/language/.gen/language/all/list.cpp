// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/all/list.h"

namespace lang
{

namespace all
{

List::List()
{
}

List::~List()
{
}

List::ESquiggles::ESquiggles()
        : mValue(kInvalid)
{
}

List::ESquiggles::ESquiggles(long value)
        : mValue(value)
{
}

const List::ESquiggles List::ESquiggles::invalid()
{
    return ESquiggles(kInvalid);
}

const List::ESquiggles List::ESquiggles::none()
{
    return ESquiggles(kNone);
}

const List::ESquiggles List::ESquiggles::brackets()
{
    return ESquiggles(kBrackets);
}

const List::ESquiggles List::ESquiggles::parentheses()
{
    return ESquiggles(kParentheses);
}

long List::ESquiggles::value() const
{
    return mValue;
}

const char* List::ESquiggles::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "none",
        "brackets",
        "parentheses",
    };
    return names[(size_t)value];
}

const char* List::ESquiggles::shortName() const
{
    return shortName(value());
}

bool List::ESquiggles::operator==(const ESquiggles& rValue) const
{
    return mValue == rValue.mValue;
}

bool List::ESquiggles::operator!=(const ESquiggles& rValue) const
{
    return mValue != rValue.mValue;
}

const List::ESquiggles& List::squiggles() const
{
    return mSquiggles;
}

List& List::set_squiggles(const ESquiggles& squiggles)
{
    mSquiggles = squiggles;
    return *this;
}

List::ESquiggles& List::mutable_squiggles()
{
    return mSquiggles;
}

List& List::operator<<(const ESquiggles& squiggles)
{
    return set_squiggles(squiggles);
}

const ListSPtr& operator<<(const ListSPtr& object, const List::ESquiggles& squiggles)
{
    BOOST_ASSERT(object);
    *object << squiggles;
    return object;
}

List::EDelimiter::EDelimiter()
        : mValue(kInvalid)
{
}

List::EDelimiter::EDelimiter(long value)
        : mValue(value)
{
}

const List::EDelimiter List::EDelimiter::invalid()
{
    return EDelimiter(kInvalid);
}

const List::EDelimiter List::EDelimiter::comma()
{
    return EDelimiter(kComma);
}

long List::EDelimiter::value() const
{
    return mValue;
}

const char* List::EDelimiter::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "comma",
    };
    return names[(size_t)value];
}

const char* List::EDelimiter::shortName() const
{
    return shortName(value());
}

bool List::EDelimiter::operator==(const EDelimiter& rValue) const
{
    return mValue == rValue.mValue;
}

bool List::EDelimiter::operator!=(const EDelimiter& rValue) const
{
    return mValue != rValue.mValue;
}

const List::EDelimiter& List::delimiter() const
{
    return mDelimiter;
}

List& List::set_delimiter(const EDelimiter& delimiter)
{
    mDelimiter = delimiter;
    return *this;
}

List::EDelimiter& List::mutable_delimiter()
{
    return mDelimiter;
}

List& List::operator<<(const EDelimiter& delimiter)
{
    return set_delimiter(delimiter);
}

const ListSPtr& operator<<(const ListSPtr& object, const List::EDelimiter& delimiter)
{
    BOOST_ASSERT(object);
    *object << delimiter;
    return object;
}

const std::vector<std::string>& List::items() const
{
    return mItems;
}

List& List::set_items(const std::vector<std::string>& items)
{
    mItems = items;
    return *this;
}

std::vector<std::string>& List::mutable_items()
{
    return mItems;
}

List& List::operator<<(const std::vector<std::string>& items)
{
    return set_items(items);
}

const ListSPtr& operator<<(const ListSPtr& object, const std::vector<std::string>& items)
{
    BOOST_ASSERT(object);
    *object << items;
    return object;
}

List& List::operator<<(const std::string& itemsItem)
{
    mItems.push_back(itemsItem);
    return *this;
}

const ListSPtr& operator<<(const ListSPtr& object, const std::string& itemsItem)
{
    BOOST_ASSERT(object);
    *object << itemsItem;
    return object;
}

}

}

