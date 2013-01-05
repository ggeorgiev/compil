// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/statement.h"

namespace lang
{

namespace cpp
{

Statement::Statement()
        : mClose(default_close())
{
}

Statement::~Statement()
{
}

Statement::EClose::EClose()
        : mValue(kInvalid)
{
}

Statement::EClose::EClose(long value)
        : mValue(value)
{
}

const Statement::EClose Statement::EClose::invalid()
{
    return EClose(kInvalid);
}

const Statement::EClose Statement::EClose::yes()
{
    return EClose(kYes);
}

const Statement::EClose Statement::EClose::no()
{
    return EClose(kNo);
}

long Statement::EClose::value() const
{
    return mValue;
}

const char* Statement::EClose::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "yes",
        "no",
    };
    return names[(size_t)value];
}

const char* Statement::EClose::shortName() const
{
    return shortName(value());
}

bool Statement::EClose::operator==(const EClose& rValue) const
{
    return mValue == rValue.mValue;
}

bool Statement::EClose::operator!=(const EClose& rValue) const
{
    return mValue != rValue.mValue;
}

const Statement::EClose& Statement::close() const
{
    return mClose;
}

Statement::EClose Statement::default_close()
{
    return Statement::EClose::yes();
}

Statement& Statement::set_close(const EClose& close)
{
    mClose = close;
    return *this;
}

Statement::EClose& Statement::mutable_close()
{
    return mClose;
}

Statement& Statement::operator<<(const EClose& close)
{
    return set_close(close);
}

const StatementSPtr& operator<<(const StatementSPtr& object, const Statement::EClose& close)
{
    BOOST_ASSERT(object);
    *object << close;
    return object;
}

}

}

