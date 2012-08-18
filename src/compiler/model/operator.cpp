#include "operator.h"

namespace compil
{

EOperatorAction::EOperatorAction()
        : mValue(kInvalid)
{
}

EOperatorAction::EOperatorAction(long value)
        : mValue(value)
{
}

const EOperatorAction EOperatorAction::invalid()
{
    return EOperatorAction(kInvalid);
}

const EOperatorAction EOperatorAction::equalTo()
{
    return EOperatorAction(kEqualTo);
}

const EOperatorAction EOperatorAction::notEqualTo()
{
    return EOperatorAction(kNotEqualTo);
}

const EOperatorAction EOperatorAction::greaterThan()
{
    return EOperatorAction(kGreaterThan);
}

const EOperatorAction EOperatorAction::lessThan()
{
    return EOperatorAction(kLessThan);
}

long EOperatorAction::value() const
{
    return mValue;
}

const char* EOperatorAction::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "equalTo",
        "notEqualTo",
        "greaterThan",
        "lessThan",
    };
    return names[(size_t)value];
}

const char* EOperatorAction::shortName() const
{
    return shortName(value());
}

bool EOperatorAction::operator==(const EOperatorAction& rValue) const
{
    return mValue == rValue.mValue;
}

bool EOperatorAction::operator!=(const EOperatorAction& rValue) const
{
    return mValue != rValue.mValue;
}

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

EOperatorParameter::EOperatorParameter()
        : flags_enumeration<long, EOperatorParameter>(0)
{
}

EOperatorParameter::EOperatorParameter(long value)
        : flags_enumeration<long, EOperatorParameter>(value)
{
}

const EOperatorParameter EOperatorParameter::nil()
{
    return EOperatorParameter(kNil);
}

const EOperatorParameter EOperatorParameter::object()
{
    return EOperatorParameter(kObject);
}

const EOperatorParameter EOperatorParameter::reference()
{
    return EOperatorParameter(kReference);
}

const EOperatorParameter EOperatorParameter::all()
{
    return EOperatorParameter(kAll);
}

long EOperatorParameter::value() const
{
    return mValue;
}

const char* EOperatorParameter::shortName(long value)
{
    switch (value)
    {
        case kObject   : return "object";
        case kReference: return "reference";
        default        : return "custom";
    }
}

const char* EOperatorParameter::shortName() const
{
    return shortName(value());
}

bool EOperatorParameter::operator==(const EOperatorParameter& rValue) const
{
    return mValue == rValue.mValue;
}

bool EOperatorParameter::operator!=(const EOperatorParameter& rValue) const
{
    return mValue != rValue.mValue;
}

Operator::Operator()
{
}

Operator::~Operator()
{
}

OperatorSPtr Operator::downcast(const ObjectSPtr& pObject)
{
    return boost::static_pointer_cast<Operator>(pObject);
}

const EOperatorAction& Operator::action() const
{
    return mAction;
}

void Operator::set_action(const EOperatorAction& action)
{
    mAction = action;
}

const EOperatorFlags& Operator::flags() const
{
    return mFlags;
}

void Operator::set_flags(const EOperatorFlags& flags)
{
    mFlags = flags;
}

const StructureWPtr& Operator::structure() const
{
    return mStructure;
}

StructureWPtr Operator::default_structure()
{
    static StructureWPtr defaultObject;
    return defaultObject;
}

void Operator::set_structure(const StructureSPtr& structure)
{
    mStructure = structure;
}

const CommentSPtr& Operator::comment() const
{
    return mComment;
}

void Operator::set_comment(const CommentSPtr& comment)
{
    mComment = comment;
}

}

