// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/declaration_factory.h"

namespace lang
{

namespace cpp
{

EDeclarationId::EDeclarationId()
        : mValue(kInvalid)
{
}

EDeclarationId::EDeclarationId(long value)
        : mValue(value)
{
}

const EDeclarationId EDeclarationId::invalid()
{
    return EDeclarationId(kInvalid);
}

const EDeclarationId EDeclarationId::blockDeclaration()
{
    return EDeclarationId(kBlockDeclaration);
}

const EDeclarationId EDeclarationId::classDeclaration()
{
    return EDeclarationId(kClassDeclaration);
}

const EDeclarationId EDeclarationId::classTypeName()
{
    return EDeclarationId(kClassTypeName);
}

const EDeclarationId EDeclarationId::declaration()
{
    return EDeclarationId(kDeclaration);
}

const EDeclarationId EDeclarationId::declarationSpecifier()
{
    return EDeclarationId(kDeclarationSpecifier);
}

const EDeclarationId EDeclarationId::declarationSpecifierSequence()
{
    return EDeclarationId(kDeclarationSpecifierSequence);
}

const EDeclarationId EDeclarationId::simpleBlockDeclaration()
{
    return EDeclarationId(kSimpleBlockDeclaration);
}

const EDeclarationId EDeclarationId::simpleDeclaration()
{
    return EDeclarationId(kSimpleDeclaration);
}

const EDeclarationId EDeclarationId::simpleTypeSpecifier()
{
    return EDeclarationId(kSimpleTypeSpecifier);
}

const EDeclarationId EDeclarationId::typeDeclarationSpecifier()
{
    return EDeclarationId(kTypeDeclarationSpecifier);
}

const EDeclarationId EDeclarationId::typeName()
{
    return EDeclarationId(kTypeName);
}

const EDeclarationId EDeclarationId::typeNameSimpleTypeSpecifier()
{
    return EDeclarationId(kTypeNameSimpleTypeSpecifier);
}

const EDeclarationId EDeclarationId::typeSpecifier()
{
    return EDeclarationId(kTypeSpecifier);
}

long EDeclarationId::value() const
{
    return mValue;
}

const char* EDeclarationId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "BlockDeclaration",
        "ClassDeclaration",
        "ClassTypeName",
        "Declaration",
        "DeclarationSpecifier",
        "DeclarationSpecifierSequence",
        "SimpleBlockDeclaration",
        "SimpleDeclaration",
        "SimpleTypeSpecifier",
        "TypeDeclarationSpecifier",
        "TypeName",
        "TypeNameSimpleTypeSpecifier",
        "TypeSpecifier",
    };
    return names[(size_t)value];
}

const char* EDeclarationId::shortName() const
{
    return shortName(value());
}

bool EDeclarationId::operator==(const EDeclarationId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EDeclarationId::operator!=(const EDeclarationId& rValue) const
{
    return mValue != rValue.mValue;
}

EDeclarationId BlockDeclaration::staticDeclarationId()
{
    return EDeclarationId::blockDeclaration();
}

EDeclarationId BlockDeclaration::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId ClassDeclaration::staticDeclarationId()
{
    return EDeclarationId::classDeclaration();
}

EDeclarationId ClassDeclaration::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId ClassTypeName::staticDeclarationId()
{
    return EDeclarationId::classTypeName();
}

EDeclarationId ClassTypeName::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId Declaration::staticDeclarationId()
{
    return EDeclarationId::declaration();
}

EDeclarationId Declaration::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId DeclarationSpecifier::staticDeclarationId()
{
    return EDeclarationId::declarationSpecifier();
}

EDeclarationId DeclarationSpecifier::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId DeclarationSpecifierSequence::staticDeclarationId()
{
    return EDeclarationId::declarationSpecifierSequence();
}

EDeclarationId DeclarationSpecifierSequence::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId SimpleBlockDeclaration::staticDeclarationId()
{
    return EDeclarationId::simpleBlockDeclaration();
}

EDeclarationId SimpleBlockDeclaration::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId SimpleDeclaration::staticDeclarationId()
{
    return EDeclarationId::simpleDeclaration();
}

EDeclarationId SimpleDeclaration::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId SimpleTypeSpecifier::staticDeclarationId()
{
    return EDeclarationId::simpleTypeSpecifier();
}

EDeclarationId SimpleTypeSpecifier::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId TypeDeclarationSpecifier::staticDeclarationId()
{
    return EDeclarationId::typeDeclarationSpecifier();
}

EDeclarationId TypeDeclarationSpecifier::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId TypeName::staticDeclarationId()
{
    return EDeclarationId::typeName();
}

EDeclarationId TypeName::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId TypeNameSimpleTypeSpecifier::staticDeclarationId()
{
    return EDeclarationId::typeNameSimpleTypeSpecifier();
}

EDeclarationId TypeNameSimpleTypeSpecifier::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

EDeclarationId TypeSpecifier::staticDeclarationId()
{
    return EDeclarationId::typeSpecifier();
}

EDeclarationId TypeSpecifier::runtimeDeclarationId() const
{
    return staticDeclarationId();
}

DeclarationSPtr DeclarationFactory::clone(const DeclarationSPtr& pObject)
{
    switch (pObject->runtimeDeclarationId().value())
    {
        case EDeclarationId::kBlockDeclaration:
        {
            BlockDeclarationSPtr pClone(new BlockDeclaration());
            *pClone = *downcastBlockDeclaration(pObject);
            return pClone;
        }
        case EDeclarationId::kClassDeclaration:
        {
            ClassDeclarationSPtr pClone(new ClassDeclaration());
            *pClone = *downcastClassDeclaration(pObject);
            return pClone;
        }
        case EDeclarationId::kClassTypeName:
        {
            ClassTypeNameSPtr pClone(new ClassTypeName());
            *pClone = *downcastClassTypeName(pObject);
            return pClone;
        }
        case EDeclarationId::kDeclaration:
        {
            DeclarationSPtr pClone(new Declaration());
            *pClone = *pObject;
            return pClone;
        }
        case EDeclarationId::kDeclarationSpecifier:
        {
            DeclarationSpecifierSPtr pClone(new DeclarationSpecifier());
            *pClone = *downcastDeclarationSpecifier(pObject);
            return pClone;
        }
        case EDeclarationId::kDeclarationSpecifierSequence:
        {
            DeclarationSpecifierSequenceSPtr pClone(new DeclarationSpecifierSequence());
            *pClone = *downcastDeclarationSpecifierSequence(pObject);
            return pClone;
        }
        case EDeclarationId::kSimpleBlockDeclaration:
        {
            SimpleBlockDeclarationSPtr pClone(new SimpleBlockDeclaration());
            *pClone = *downcastSimpleBlockDeclaration(pObject);
            return pClone;
        }
        case EDeclarationId::kSimpleDeclaration:
        {
            SimpleDeclarationSPtr pClone(new SimpleDeclaration());
            *pClone = *downcastSimpleDeclaration(pObject);
            return pClone;
        }
        case EDeclarationId::kSimpleTypeSpecifier:
        {
            SimpleTypeSpecifierSPtr pClone(new SimpleTypeSpecifier());
            *pClone = *downcastSimpleTypeSpecifier(pObject);
            return pClone;
        }
        case EDeclarationId::kTypeDeclarationSpecifier:
        {
            TypeDeclarationSpecifierSPtr pClone(new TypeDeclarationSpecifier());
            *pClone = *downcastTypeDeclarationSpecifier(pObject);
            return pClone;
        }
        case EDeclarationId::kTypeName:
        {
            TypeNameSPtr pClone(new TypeName());
            *pClone = *downcastTypeName(pObject);
            return pClone;
        }
        case EDeclarationId::kTypeNameSimpleTypeSpecifier:
        {
            TypeNameSimpleTypeSpecifierSPtr pClone(new TypeNameSimpleTypeSpecifier());
            *pClone = *downcastTypeNameSimpleTypeSpecifier(pObject);
            return pClone;
        }
        case EDeclarationId::kTypeSpecifier:
        {
            TypeSpecifierSPtr pClone(new TypeSpecifier());
            *pClone = *downcastTypeSpecifier(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return DeclarationSPtr();
}

BlockDeclarationSPtr DeclarationFactory::downcastBlockDeclaration(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == BlockDeclaration::staticDeclarationId())
          // or any of the derived classes
          || (pObject->runtimeDeclarationId() == SimpleBlockDeclaration::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<BlockDeclaration>(pObject);
    return BlockDeclarationSPtr();
}

ClassDeclarationSPtr DeclarationFactory::downcastClassDeclaration(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == ClassDeclaration::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<ClassDeclaration>(pObject);
    return ClassDeclarationSPtr();
}

ClassTypeNameSPtr DeclarationFactory::downcastClassTypeName(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == ClassTypeName::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<ClassTypeName>(pObject);
    return ClassTypeNameSPtr();
}

DeclarationSpecifierSPtr DeclarationFactory::downcastDeclarationSpecifier(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == DeclarationSpecifier::staticDeclarationId())
          // or any of the derived classes
          || (pObject->runtimeDeclarationId() == TypeDeclarationSpecifier::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<DeclarationSpecifier>(pObject);
    return DeclarationSpecifierSPtr();
}

DeclarationSpecifierSequenceSPtr DeclarationFactory::downcastDeclarationSpecifierSequence(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == DeclarationSpecifierSequence::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<DeclarationSpecifierSequence>(pObject);
    return DeclarationSpecifierSequenceSPtr();
}

SimpleBlockDeclarationSPtr DeclarationFactory::downcastSimpleBlockDeclaration(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == SimpleBlockDeclaration::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<SimpleBlockDeclaration>(pObject);
    return SimpleBlockDeclarationSPtr();
}

SimpleDeclarationSPtr DeclarationFactory::downcastSimpleDeclaration(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == SimpleDeclaration::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<SimpleDeclaration>(pObject);
    return SimpleDeclarationSPtr();
}

SimpleTypeSpecifierSPtr DeclarationFactory::downcastSimpleTypeSpecifier(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == SimpleTypeSpecifier::staticDeclarationId())
          // or any of the derived classes
          || (pObject->runtimeDeclarationId() == TypeNameSimpleTypeSpecifier::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<SimpleTypeSpecifier>(pObject);
    return SimpleTypeSpecifierSPtr();
}

TypeDeclarationSpecifierSPtr DeclarationFactory::downcastTypeDeclarationSpecifier(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == TypeDeclarationSpecifier::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<TypeDeclarationSpecifier>(pObject);
    return TypeDeclarationSpecifierSPtr();
}

TypeNameSPtr DeclarationFactory::downcastTypeName(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == TypeName::staticDeclarationId())
          // or any of the derived classes
          || (pObject->runtimeDeclarationId() == ClassTypeName::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<TypeName>(pObject);
    return TypeNameSPtr();
}

TypeNameSimpleTypeSpecifierSPtr DeclarationFactory::downcastTypeNameSimpleTypeSpecifier(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == TypeNameSimpleTypeSpecifier::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<TypeNameSimpleTypeSpecifier>(pObject);
    return TypeNameSimpleTypeSpecifierSPtr();
}

TypeSpecifierSPtr DeclarationFactory::downcastTypeSpecifier(const DeclarationSPtr& pObject)
{
    bool b = (pObject->runtimeDeclarationId() == TypeSpecifier::staticDeclarationId())
          // or any of the derived classes
          || (pObject->runtimeDeclarationId() == SimpleTypeSpecifier::staticDeclarationId())
          || (pObject->runtimeDeclarationId() == TypeNameSimpleTypeSpecifier::staticDeclarationId());

    if (b)
        return boost::static_pointer_cast<TypeSpecifier>(pObject);
    return TypeSpecifierSPtr();
}

}

}

