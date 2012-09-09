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
        : mBits       (0)
        , mDeclaration(default_declaration())
        , mDecoration (default_decoration())
        , mAligned    (default_aligned())
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
    if (changed_declaration()) return false;
    if (exist_type()) return false;
    if (changed_decoration()) return false;
    if (changed_aligned()) return false;
    return true;
}

const ETypeDeclaration& DecoratedType::declaration() const
{
    return mDeclaration;
}

bool DecoratedType::changed_declaration() const
{
    return (mBits & bitmask_declaration()) != 0;
}

ETypeDeclaration DecoratedType::default_declaration()
{
    return ETypeDeclaration::invalid();
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

DecoratedType::Builder& DecoratedType::Builder::update_declaration(const ETypeDeclaration& declaration)
{
    if (mpObject->default_declaration() != declaration)
        return update_declaration(declaration);

    reset_declaration();
    return *this;
}

void DecoratedType::Builder::reset_declaration()
{
    mpObject->mDeclaration  =  mpObject->default_declaration();
    mpObject->mBits        &= ~bitmask_declaration          ();
}

const SimpleTypeSPtr& DecoratedType::type() const
{
    BOOST_ASSERT(exist_type());
    return mType;
}

bool DecoratedType::exist_type() const
{
    return (mBits & bitmask_type()) != 0;
}

DecoratedType::Builder& DecoratedType::Builder::set_type(const SimpleTypeSPtr& type)
{
    mpObject->mType  = type;
    mpObject->mBits |= bitmask_type();
    return *this;
}

void DecoratedType::Builder::clear_type()
{
    mpObject->mType.reset();
    mpObject->mBits &= ~bitmask_type();
}

const ETypeDecoration& DecoratedType::decoration() const
{
    return mDecoration;
}

bool DecoratedType::changed_decoration() const
{
    return (mBits & bitmask_decoration()) != 0;
}

ETypeDecoration DecoratedType::default_decoration()
{
    return ETypeDecoration::invalid();
}

DecoratedType::Builder& DecoratedType::Builder::set_decoration(const ETypeDecoration& decoration)
{
    mpObject->mDecoration  = decoration;
    mpObject->mBits       |= bitmask_decoration();
    return *this;
}

ETypeDecoration& DecoratedType::Builder::mutable_decoration()
{
    mpObject->mBits |= bitmask_decoration();
    return mpObject->mDecoration;
}

DecoratedType::Builder& DecoratedType::Builder::update_decoration(const ETypeDecoration& decoration)
{
    if (mpObject->default_decoration() != decoration)
        return update_decoration(decoration);

    reset_decoration();
    return *this;
}

void DecoratedType::Builder::reset_decoration()
{
    mpObject->mDecoration  =  mpObject->default_decoration();
    mpObject->mBits       &= ~bitmask_decoration          ();
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

DecoratedTypeSPtr CreateDecoratedType(const SimpleTypeSPtr& type)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const SimpleTypeSPtr& type)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_type(type);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDecoration& decoration)
{
    DecoratedType::Builder builder;
    builder.set_decoration(decoration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const ETypeDecoration& decoration)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_decoration(decoration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const SimpleTypeSPtr& type, const ETypeDecoration& decoration)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    builder.set_decoration(decoration);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                                              const SimpleTypeSPtr&  type,
                                                                                     const ETypeDecoration&  decoration)
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

DecoratedTypeSPtr CreateDecoratedType(const SimpleTypeSPtr& type, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const SimpleTypeSPtr& type, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_type(type);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDecoration& decoration, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                                              const ETypeDecoration&  decoration,
                                                                                      bool       aligned)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const SimpleTypeSPtr& type, const ETypeDecoration& decoration, bool aligned)
{
    DecoratedType::Builder builder;
    builder.set_type(type);
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                                              const SimpleTypeSPtr&  type,
                                                                                     const ETypeDecoration&  decoration,
                                                                                                             bool       aligned)
{
    DecoratedType::Builder builder;
    builder.set_declaration(declaration);
    builder.set_type(type);
    builder.set_decoration(decoration);
    builder.set_aligned(aligned);
    return builder.finalize();
}

