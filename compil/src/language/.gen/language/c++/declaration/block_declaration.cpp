#include "language/c++/declaration/block_declaration.h"

namespace lang
{

namespace cpp
{

BlockDeclaration::BlockDeclaration()
{
}

BlockDeclaration::~BlockDeclaration()
{
}

BlockDeclarationSPtr BlockDeclaration::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<BlockDeclaration>(object);
}

}

}

