#include "identifier.h"

namespace compil
{

Identifier::Identifier()
{
    set_kind(alter_kind());
}

Identifier::~Identifier()
{
}

IdentifierSPtr Identifier::downcast(const ObjectSPtr& object)
{
    return boost::static_pointer_cast<Identifier>(object);
}

Type::EKind Identifier::alter_kind()
{
    return Type::EKind::object();
}

}

