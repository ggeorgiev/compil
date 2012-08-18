#include "parameter.h"

namespace compil
{

Parameter::Parameter()
{
}

Parameter::~Parameter()
{
}

ParameterSPtr Parameter::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Parameter>(pObject);
}

const MethodWPtr& Parameter::method() const
{
    return mMethod;
}

void Parameter::set_method(const MethodSPtr& method)
{
    mMethod = method;
}

const CommentSPtr& Parameter::comment() const
{
    return mComment;
}

void Parameter::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
}

const TypeSPtr& Parameter::type() const
{
    return mType;
}

void Parameter::set_type(const TypeSPtr& type)
{
    mType = type;
}

const NameSPtr& Parameter::name() const
{
    return mName;
}

void Parameter::set_name(const NameSPtr& name)
{
    mName = name;
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

void Parameter::set_direction(const EDirection& direction)
{
    mDirection = direction;
}

}

