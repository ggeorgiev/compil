// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/preprocessor/declaration_macro_parameter.h"

namespace lang
{

namespace cpp
{

DeclarationMacroParameter::DeclarationMacroParameter()
{
}

DeclarationMacroParameter::~DeclarationMacroParameter()
{
}

DeclarationMacroParameterSPtr DeclarationMacroParameter::downcast(const MacroParameterSPtr& object)
{
    return boost::static_pointer_cast<DeclarationMacroParameter>(object);
}

const DeclarationSPtr& DeclarationMacroParameter::declaration() const
{
    return mDeclaration;
}

DeclarationMacroParameter& DeclarationMacroParameter::set_declaration(const DeclarationSPtr& declaration)
{
    mDeclaration = declaration;
    return *this;
}

DeclarationMacroParameter& DeclarationMacroParameter::operator<<(const DeclarationSPtr& declaration)
{
    return set_declaration(declaration);
}

const DeclarationMacroParameterSPtr& operator<<(const DeclarationMacroParameterSPtr& object,
                                                const DeclarationSPtr& declaration)
{
    BOOST_ASSERT(object);
    *object << declaration;
    return object;
}

}

}

