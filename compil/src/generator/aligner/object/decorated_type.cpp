// Boost C++ Utility
#include <boost/assert.hpp>

#include "decorated_type.h"
// Standard C Library
#include <stddef.h>

int DecoratedType::bitmask_declaration()
{
    return 0x1;
}

int DecoratedType::bitmask_type()
{
    return 0x2;
}

int DecoratedType::bitmask_decoration()
{
    return 0x4;
}

int DecoratedType::bitmask_aligned()
{
    return 0x8;
}

DecoratedType::Builder::Builder()
        : mpObject(new DecoratedType())
{
}

DecoratedType::Builder::Builder(const DecoratedType& object)
        : mpObject(new DecoratedType())
{
    *(DecoratedType*)mpObject = object;
}

DecoratedType::Builder::Builder(DecoratedTypeRPtr pObject)
        : mpObject(pObject)
{
}

DecoratedType::Builder::~Builder()
{
    delete (DecoratedTypeRPtr)mpObject;
    mpObject = NULL;
}

const DecoratedType& DecoratedType::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(DecoratedTypeRPtr)mpObject;
}

DecoratedTypeSPtr DecoratedType::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    DecoratedTypeRPtr objectRPtr = (DecoratedTypeRPtr)mpObject;
    mpObject = NULL;
    return DecoratedTypeSPtr(objectRPtr);
}

DecoratedType::DecoratedType()
        : mBits   (0)
        , mAligned(default_aligned())
{
}

DecoratedType::~DecoratedType()
{
}

bool DecoratedType::isInitialized() const
{
    return true;
}

bool DecoratedType::isVoid() const
{
    if (exist_declaration()) return false;
    if (exist_type()) return false;
    if (exist_decoration()) return false;
    return true;
}

const ETypeDeclaration& DecoratedType::declaration() const
{
    BOOST_ASSERT(exist_declaration());
    return mDeclaration;
}

bool DecoratedType::exist_declaration() const
{
    return (mBits & bitmask_declaration()) != 0;
}

DecoratedType::Builder& DecoratedType::Builder::set_declaration(const ETypeDeclaration& declaration)
{
    mpObject->mDeclaration  = declaration;
    mpObject->mBits        |= bitmask_declaration();
    return *this;
}

ETypeDeclaration& DecoratedType::Builder::mutable_declaration()
{
    mpObject->mBits |= bitmask_declaration();
    return mpObject->mDeclaration;
}

void DecoratedType::Builder::clear_declaration()
{
    mpObject->mDeclaration  =  ETypeDeclaration::invalid();
    mpObject->mBits        &= ~bitmask_declaration         ();
}

const SimpleType& DecoratedType::type() const
{
    BOOST_ASSERT(exist_type());
    return mType;
}

bool DecoratedType::exist_type() const
{
    return (mBits & bitmask_type()) != 0;
}

DecoratedType::Builder& DecoratedType::Builder::set_type(const SimpleType& type)
{
    mpObject->mType  = type;
    mpObject->mBits |= bitmask_type();
    return *this;
}

SimpleType& DecoratedType::Builder::mutable_type()
{
    mpObject->mBits |= bitmask_type();
    return mpObject->mType;
}

void DecoratedType::Builder::clear_type()
{
    mpObject->mType  =  SimpleType();
    mpObject->mBits &= ~bitmask_type ();
}

const Decoration& DecoratedType::decoration() const
{
    BOOST_ASSERT(exist_decoration());
    return mDecoration;
}

bool DecoratedType::exist_decoration() const
{
    return (mBits & bitmask_decoration()) != 0;
}

DecoratedType::Builder& DecoratedType::Builder::set_decoration(const Decoration& decoration)
{
    mpObject->mDecoration  = decoration;
    mpObject->mBits       |= bitmask_decoration();
    return *this;
}

Decoration& DecoratedType::Builder::mutable_decoration()
{
    mpObject->mBits |= bitmask_decoration();
    return mpObject->mDecoration;
}

void DecoratedType::Builder::clear_decoration()
{
    mpObject->mDecoration  =  Decoration();
    mpObject->mBits       &= ~bitmask_decoration();
}

bool DecoratedType::aligned() const
{
    return mAligned;
}

bool DecoratedType::changed_aligned() const
{
    return (mBits & bitmask_aligned()) != 0;
}

bool DecoratedType::default_aligned()
{
    return true;
}

DecoratedType::Builder& DecoratedType::Builder::set_aligned(bool aligned)
{
    mpObject->mAligned  = aligned;
    mpObject->mBits    |= bitmask_aligned();
    return *this;
}

DecoratedType::Builder& DecoratedType::Builder::update_aligned(bool aligned)
{
    if (mpObject->default_aligned() != aligned)
        return update_aligned(aligned);

    reset_aligned();
    return *this;
}

void DecoratedType::Builder::reset_aligned()
{
    mpObject->mAligned  =  mpObject->default_aligned();
    mpObject->mBits    &= ~bitmask_aligned          ();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const SimpleType& type)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_type(type);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const Decoration& decoration)
{
    DecoratedType::Builder builder;
    builder.set_decoration(decoration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const Decoration& decoration)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_decoration(decoration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type, const Decoration& decoration)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    builder.set_decoration(decoration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                      const SimpleType& type,
                                      const Decoration& decoration)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_type(type);
    builder.set_decoration(decoration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const SimpleType& type, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_type(type);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const Decoration& decoration, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const Decoration& decoration, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type, const Decoration& decoration, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                      const SimpleType& type,
                                      const Decoration& decoration,
                                      bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_type(type);
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

