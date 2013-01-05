#include "language/c++/declaration/function_specifier.h"

namespace lang
{

namespace cpp
{

FunctionSpecifier::FunctionSpecifier()
{
}

FunctionSpecifier::~FunctionSpecifier()
{
}

FunctionSpecifierSPtr FunctionSpecifier::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<FunctionSpecifier>(object);
}

FunctionSpecifier::EType::EType()
        : mValue(kInvalid)
{
}

FunctionSpecifier::EType::EType(long value)
        : mValue(value)
{
}

const FunctionSpecifier::EType FunctionSpecifier::EType::invalid()
{
    return EType(kInvalid);
}

const FunctionSpecifier::EType FunctionSpecifier::EType::inline_()
{
    return EType(kInline);
}

const FunctionSpecifier::EType FunctionSpecifier::EType::virtual_()
{
    return EType(kVirtual);
}

const FunctionSpecifier::EType FunctionSpecifier::EType::explicit_()
{
    return EType(kExplicit);
}

long FunctionSpecifier::EType::value() const
{
    return mValue;
}

const char* FunctionSpecifier::EType::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "inline",
        "virtual",
        "explicit",
    };
    return names[(size_t)value];
}

const char* FunctionSpecifier::EType::shortName() const
{
    return shortName(value());
}

bool FunctionSpecifier::EType::operator==(const EType& rValue) const
{
    return mValue == rValue.mValue;
}

bool FunctionSpecifier::EType::operator!=(const EType& rValue) const
{
    return mValue != rValue.mValue;
}

}

}

