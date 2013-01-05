#include "language/compil/document/operator_flags.h"

namespace lang
{

namespace compil
{

EOperatorFlags::EOperatorFlags()
        : flags_enumeration<long, EOperatorFlags>(0)
{
}

EOperatorFlags::EOperatorFlags(long value)
        : flags_enumeration<long, EOperatorFlags>(value)
{
}

const EOperatorFlags EOperatorFlags::nil()
{
    return EOperatorFlags(kNil);
}

const EOperatorFlags EOperatorFlags::native()
{
    return EOperatorFlags(kNative);
}

const EOperatorFlags EOperatorFlags::function()
{
    return EOperatorFlags(kFunction);
}

const EOperatorFlags EOperatorFlags::functor()
{
    return EOperatorFlags(kFunctor);
}

const EOperatorFlags EOperatorFlags::declaration()
{
    return EOperatorFlags(kDeclaration);
}

const EOperatorFlags EOperatorFlags::object()
{
    return EOperatorFlags(kObject);
}

const EOperatorFlags EOperatorFlags::reference()
{
    return EOperatorFlags(kReference);
}

const EOperatorFlags EOperatorFlags::parameter()
{
    return EOperatorFlags(kParameter);
}

const EOperatorFlags EOperatorFlags::member()
{
    return EOperatorFlags(kMember);
}

const EOperatorFlags EOperatorFlags::internal()
{
    return EOperatorFlags(kInternal);
}

const EOperatorFlags EOperatorFlags::external()
{
    return EOperatorFlags(kExternal);
}

const EOperatorFlags EOperatorFlags::location()
{
    return EOperatorFlags(kLocation);
}

const EOperatorFlags EOperatorFlags::all()
{
    return EOperatorFlags(kAll);
}

long EOperatorFlags::value() const
{
    return mValue;
}

const char* EOperatorFlags::shortName(long value)
{
    switch (value)
    {
        case kNative     : return "native";
        case kFunction   : return "function";
        case kFunctor    : return "functor";
        case kDeclaration: return "declaration";
        case kObject     : return "object";
        case kReference  : return "reference";
        case kParameter  : return "parameter";
        case kMember     : return "member";
        case kInternal   : return "internal";
        case kExternal   : return "external";
        case kLocation   : return "location";
        default          : return "custom";
    }
}

const char* EOperatorFlags::shortName() const
{
    return shortName(value());
}

bool EOperatorFlags::operator==(const EOperatorFlags& rValue) const
{
    return mValue == rValue.mValue;
}

bool EOperatorFlags::operator!=(const EOperatorFlags& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

