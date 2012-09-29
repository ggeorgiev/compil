#include "unary_template.h"

namespace compil
{

UnaryTemplate::UnaryTemplate()
{
}

UnaryTemplate::~UnaryTemplate()
{
}

UnaryTemplateSPtr UnaryTemplate::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<UnaryTemplate>(object);
}

const TypeWPtr& UnaryTemplate::parameterType() const
{
    return mParameterType;
}

TypeWPtr UnaryTemplate::default_parameterType()
{
    static TypeWPtr defaultObject;
    return defaultObject;
}

UnaryTemplate& UnaryTemplate::set_parameterType(const TypeSPtr& parameterType)
{
    mParameterType = parameterType;
    return *this;
}

}

