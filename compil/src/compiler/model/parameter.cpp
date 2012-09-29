#include "parameter.h"

namespace compil
{

Parameter::Parameter()
{
}

Parameter::~Parameter()
{
}

ParameterSPtr Parameter::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Parameter>(object);
}

const MethodWPtr& Parameter::method() const
{
    return mMethod;
}

Parameter& Parameter::set_method(const MethodSPtr& method)
{
    mMethod = method;
    return *this;
}

const CommentSPtr& Parameter::comment() const
{
    return mComment;
}

Parameter& Parameter::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
    return *this;
}

const TypeSPtr& Parameter::type() const
{
    return mType;
}

Parameter& Parameter::set_type(const TypeSPtr& type)
{
    mType = type;
    return *this;
}

const NameSPtr& Parameter::name() const
{
    return mName;
}

Parameter& Parameter::set_name(const NameSPtr& name)
{
    mName = name;
    return *this;
}

Parameter::EDirection::EDirection()
        : mValue(kInvalid)
{
}

Parameter::EDirection::EDirection(long value)
        : mValue(value)
{
}

const Parameter::EDirection Parameter::EDirection::invalid()
{
    return EDirection(kInvalid);
}

const Parameter::EDirection Parameter::EDirection::in()
{
    return EDirection(kIn);
}

const Parameter::EDirection Parameter::EDirection::out()
{
    return EDirection(kOut);
}

const Parameter::EDirection Parameter::EDirection::io()
{
    return EDirection(kIo);
}

long Parameter::EDirection::value() const
{
    return mValue;
}

const char* Parameter::EDirection::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "in",
        "out",
        "io",
    };
    return names[(size_t)value];
}

const char* Parameter::EDirection::shortName() const
{
    return shortName(value());
}

bool Parameter::EDirection::operator==(const EDirection& rValue) const
{
    return mValue == rValue.mValue;
}

bool Parameter::EDirection::operator!=(const EDirection& rValue) const
{
    return mValue != rValue.mValue;
}

const Parameter::EDirection& Parameter::direction() const
{
    return mDirection;
}

Parameter& Parameter::set_direction(const EDirection& direction)
{
    mDirection = direction;
    return *this;
}

Parameter::EDirection& Parameter::mutable_direction()
{
    return mDirection;
}

}

