// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/expression/equality_expression.h"

namespace lang
{

namespace cpp
{

EqualityExpression::EqualityExpression()
{
}

EqualityExpression::~EqualityExpression()
{
}

EqualityExpressionSPtr EqualityExpression::downcast(const ExpressionSPtr& object)
{
    return boost::static_pointer_cast<EqualityExpression>(object);
}

EqualityExpression::EType::EType()
        : mValue(kInvalid)
{
}

EqualityExpression::EType::EType(long value)
        : mValue(value)
{
}

const EqualityExpression::EType EqualityExpression::EType::invalid()
{
    return EType(kInvalid);
}

const EqualityExpression::EType EqualityExpression::EType::equalTo()
{
    return EType(kEqualTo);
}

const EqualityExpression::EType EqualityExpression::EType::notEqualTo()
{
    return EType(kNotEqualTo);
}

long EqualityExpression::EType::value() const
{
    return mValue;
}

const char* EqualityExpression::EType::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "equalTo",
        "notEqualTo",
    };
    return names[(size_t)value];
}

const char* EqualityExpression::EType::shortName() const
{
    return shortName(value());
}

bool EqualityExpression::EType::operator==(const EType& rValue) const
{
    return mValue == rValue.mValue;
}

bool EqualityExpression::EType::operator!=(const EType& rValue) const
{
    return mValue != rValue.mValue;
}

const EqualityExpression::EType& EqualityExpression::type() const
{
    return mType;
}

EqualityExpression& EqualityExpression::set_type(const EType& type)
{
    mType = type;
    return *this;
}

EqualityExpression::EType& EqualityExpression::mutable_type()
{
    return mType;
}

EqualityExpression& EqualityExpression::operator<<(const EType& type)
{
    return set_type(type);
}

const EqualityExpressionSPtr& operator<<(const EqualityExpressionSPtr& object, const EqualityExpression::EType& type)
{
    BOOST_ASSERT(object);
    *object << type;
    return object;
}

}

}

