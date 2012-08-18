// Boost C++ Utility
#include <boost/assert.hpp>

#include "object_factory.h"

namespace compil
{

EObjectId::EObjectId()
        : mValue(kInvalid)
{
}

EObjectId::EObjectId(long value)
        : mValue(value)
{
}

const EObjectId EObjectId::invalid()
{
    return EObjectId(kInvalid);
}

const EObjectId EObjectId::absoluteEnumerationValue()
{
    return EObjectId(kAbsoluteEnumerationValue);
}

const EObjectId EObjectId::alter()
{
    return EObjectId(kAlter);
}

const EObjectId EObjectId::comment()
{
    return EObjectId(kComment);
}

const EObjectId EObjectId::composedEnumerationValue()
{
    return EObjectId(kComposedEnumerationValue);
}

const EObjectId EObjectId::defaultValue()
{
    return EObjectId(kDefaultValue);
}

const EObjectId EObjectId::document()
{
    return EObjectId(kDocument);
}

const EObjectId EObjectId::enumeration()
{
    return EObjectId(kEnumeration);
}

const EObjectId EObjectId::enumerationValue()
{
    return EObjectId(kEnumerationValue);
}

const EObjectId EObjectId::factory()
{
    return EObjectId(kFactory);
}

const EObjectId EObjectId::field()
{
    return EObjectId(kField);
}

const EObjectId EObjectId::fieldOverride()
{
    return EObjectId(kFieldOverride);
}

const EObjectId EObjectId::filter()
{
    return EObjectId(kFilter);
}

const EObjectId EObjectId::identification()
{
    return EObjectId(kIdentification);
}

const EObjectId EObjectId::identifier()
{
    return EObjectId(kIdentifier);
}

const EObjectId EObjectId::import()
{
    return EObjectId(kImport);
}

const EObjectId EObjectId::integer()
{
    return EObjectId(kInteger);
}

const EObjectId EObjectId::interface_()
{
    return EObjectId(kInterface);
}

const EObjectId EObjectId::method()
{
    return EObjectId(kMethod);
}

const EObjectId EObjectId::name()
{
    return EObjectId(kName);
}

const EObjectId EObjectId::object()
{
    return EObjectId(kObject);
}

const EObjectId EObjectId::operator_()
{
    return EObjectId(kOperator);
}

const EObjectId EObjectId::package()
{
    return EObjectId(kPackage);
}

const EObjectId EObjectId::parameter()
{
    return EObjectId(kParameter);
}

const EObjectId EObjectId::reference()
{
    return EObjectId(kReference);
}

const EObjectId EObjectId::specimen()
{
    return EObjectId(kSpecimen);
}

const EObjectId EObjectId::structure()
{
    return EObjectId(kStructure);
}

const EObjectId EObjectId::type()
{
    return EObjectId(kType);
}

const EObjectId EObjectId::unaryContainer()
{
    return EObjectId(kUnaryContainer);
}

const EObjectId EObjectId::unaryTemplate()
{
    return EObjectId(kUnaryTemplate);
}

const EObjectId EObjectId::upcopy()
{
    return EObjectId(kUpcopy);
}

const EObjectId EObjectId::version()
{
    return EObjectId(kVersion);
}

long EObjectId::value() const
{
    return mValue;
}

const char* EObjectId::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "AbsoluteEnumerationValue",
        "Alter",
        "Comment",
        "ComposedEnumerationValue",
        "DefaultValue",
        "Document",
        "Enumeration",
        "EnumerationValue",
        "Factory",
        "Field",
        "FieldOverride",
        "Filter",
        "Identification",
        "Identifier",
        "Import",
        "Integer",
        "Interface",
        "Method",
        "Name",
        "Object",
        "Operator",
        "Package",
        "Parameter",
        "Reference",
        "Specimen",
        "Structure",
        "Type",
        "UnaryContainer",
        "UnaryTemplate",
        "Upcopy",
        "Version",
    };
    return names[(size_t)value];
}

const char* EObjectId::shortName() const
{
    return shortName(value());
}

bool EObjectId::operator==(const EObjectId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EObjectId::operator!=(const EObjectId& rValue) const
{
    return mValue != rValue.mValue;
}

EObjectId AbsoluteEnumerationValue::staticObjectId()
{
    return EObjectId::absoluteEnumerationValue();
}

EObjectId AbsoluteEnumerationValue::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Alter::staticObjectId()
{
    return EObjectId::alter();
}

EObjectId Alter::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Comment::staticObjectId()
{
    return EObjectId::comment();
}

EObjectId Comment::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId ComposedEnumerationValue::staticObjectId()
{
    return EObjectId::composedEnumerationValue();
}

EObjectId ComposedEnumerationValue::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId DefaultValue::staticObjectId()
{
    return EObjectId::defaultValue();
}

EObjectId DefaultValue::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Document::staticObjectId()
{
    return EObjectId::document();
}

EObjectId Document::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId EnumerationPartial::staticObjectId()
{
    return EObjectId::enumeration();
}

EObjectId EnumerationPartial::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId EnumerationValue::staticObjectId()
{
    return EObjectId::enumerationValue();
}

EObjectId EnumerationValue::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId FactoryPartial::staticObjectId()
{
    return EObjectId::factory();
}

EObjectId FactoryPartial::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Field::staticObjectId()
{
    return EObjectId::field();
}

EObjectId Field::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId FieldOverride::staticObjectId()
{
    return EObjectId::fieldOverride();
}

EObjectId FieldOverride::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Filter::staticObjectId()
{
    return EObjectId::filter();
}

EObjectId Filter::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Identification::staticObjectId()
{
    return EObjectId::identification();
}

EObjectId Identification::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Identifier::staticObjectId()
{
    return EObjectId::identifier();
}

EObjectId Identifier::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Import::staticObjectId()
{
    return EObjectId::import();
}

EObjectId Import::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Integer::staticObjectId()
{
    return EObjectId::integer();
}

EObjectId Integer::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Interface::staticObjectId()
{
    return EObjectId::interface_();
}

EObjectId Interface::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Method::staticObjectId()
{
    return EObjectId::method();
}

EObjectId Method::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Name::staticObjectId()
{
    return EObjectId::name();
}

EObjectId Name::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Object::staticObjectId()
{
    return EObjectId::object();
}

EObjectId Object::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Operator::staticObjectId()
{
    return EObjectId::operator_();
}

EObjectId Operator::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Package::staticObjectId()
{
    return EObjectId::package();
}

EObjectId Package::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Parameter::staticObjectId()
{
    return EObjectId::parameter();
}

EObjectId Parameter::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Reference::staticObjectId()
{
    return EObjectId::reference();
}

EObjectId Reference::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Specimen::staticObjectId()
{
    return EObjectId::specimen();
}

EObjectId Specimen::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId StructurePartial::staticObjectId()
{
    return EObjectId::structure();
}

EObjectId StructurePartial::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Type::staticObjectId()
{
    return EObjectId::type();
}

EObjectId Type::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId UnaryContainer::staticObjectId()
{
    return EObjectId::unaryContainer();
}

EObjectId UnaryContainer::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId UnaryTemplate::staticObjectId()
{
    return EObjectId::unaryTemplate();
}

EObjectId UnaryTemplate::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Upcopy::staticObjectId()
{
    return EObjectId::upcopy();
}

EObjectId Upcopy::runtimeObjectId() const
{
    return staticObjectId();
}

EObjectId Version::staticObjectId()
{
    return EObjectId::version();
}

EObjectId Version::runtimeObjectId() const
{
    return staticObjectId();
}

ObjectSPtr ObjectFactory::clone(const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kAbsoluteEnumerationValue:
        {
            AbsoluteEnumerationValueSPtr pClone(new AbsoluteEnumerationValue());
            *pClone = *downcastAbsoluteEnumerationValue(pObject);
            return pClone;
        }
        case EObjectId::kAlter:
        {
            AlterSPtr pClone(new Alter());
            *pClone = *downcastAlter(pObject);
            return pClone;
        }
        case EObjectId::kComment:
        {
            CommentSPtr pClone(new Comment());
            *pClone = *downcastComment(pObject);
            return pClone;
        }
        case EObjectId::kComposedEnumerationValue:
        {
            ComposedEnumerationValueSPtr pClone(new ComposedEnumerationValue());
            *pClone = *downcastComposedEnumerationValue(pObject);
            return pClone;
        }
        case EObjectId::kDefaultValue:
        {
            DefaultValueSPtr pClone(new DefaultValue());
            *pClone = *downcastDefaultValue(pObject);
            return pClone;
        }
        case EObjectId::kDocument:
        {
            DocumentSPtr pClone(new Document());
            *pClone = *downcastDocument(pObject);
            return pClone;
        }
        case EObjectId::kEnumeration:
        {
            EnumerationSPtr pClone(new Enumeration());
            *pClone = *downcastEnumeration(pObject);
            return pClone;
        }
        case EObjectId::kEnumerationValue:
        {
            EnumerationValueSPtr pClone(new EnumerationValue());
            *pClone = *downcastEnumerationValue(pObject);
            return pClone;
        }
        case EObjectId::kFactory:
        {
            FactorySPtr pClone(new Factory());
            *pClone = *downcastFactory(pObject);
            return pClone;
        }
        case EObjectId::kField:
        {
            FieldSPtr pClone(new Field());
            *pClone = *downcastField(pObject);
            return pClone;
        }
        case EObjectId::kFieldOverride:
        {
            FieldOverrideSPtr pClone(new FieldOverride());
            *pClone = *downcastFieldOverride(pObject);
            return pClone;
        }
        case EObjectId::kFilter:
        {
            FilterSPtr pClone(new Filter());
            *pClone = *downcastFilter(pObject);
            return pClone;
        }
        case EObjectId::kIdentification:
        {
            IdentificationSPtr pClone(new Identification());
            *pClone = *downcastIdentification(pObject);
            return pClone;
        }
        case EObjectId::kIdentifier:
        {
            IdentifierSPtr pClone(new Identifier());
            *pClone = *downcastIdentifier(pObject);
            return pClone;
        }
        case EObjectId::kImport:
        {
            ImportSPtr pClone(new Import());
            *pClone = *downcastImport(pObject);
            return pClone;
        }
        case EObjectId::kInteger:
        {
            IntegerSPtr pClone(new Integer());
            *pClone = *downcastInteger(pObject);
            return pClone;
        }
        case EObjectId::kInterface:
        {
            InterfaceSPtr pClone(new Interface());
            *pClone = *downcastInterface(pObject);
            return pClone;
        }
        case EObjectId::kMethod:
        {
            MethodSPtr pClone(new Method());
            *pClone = *downcastMethod(pObject);
            return pClone;
        }
        case EObjectId::kName:
        {
            NameSPtr pClone(new Name());
            *pClone = *downcastName(pObject);
            return pClone;
        }
        case EObjectId::kObject:
        {
            ObjectSPtr pClone(new Object());
            *pClone = *pObject;
            return pClone;
        }
        case EObjectId::kOperator:
        {
            OperatorSPtr pClone(new Operator());
            *pClone = *downcastOperator(pObject);
            return pClone;
        }
        case EObjectId::kPackage:
        {
            PackageSPtr pClone(new Package());
            *pClone = *downcastPackage(pObject);
            return pClone;
        }
        case EObjectId::kParameter:
        {
            ParameterSPtr pClone(new Parameter());
            *pClone = *downcastParameter(pObject);
            return pClone;
        }
        case EObjectId::kReference:
        {
            ReferenceSPtr pClone(new Reference());
            *pClone = *downcastReference(pObject);
            return pClone;
        }
        case EObjectId::kSpecimen:
        {
            SpecimenSPtr pClone(new Specimen());
            *pClone = *downcastSpecimen(pObject);
            return pClone;
        }
        case EObjectId::kStructure:
        {
            StructureSPtr pClone(new Structure());
            *pClone = *downcastStructure(pObject);
            return pClone;
        }
        case EObjectId::kType:
        {
            TypeSPtr pClone(new Type());
            *pClone = *downcastType(pObject);
            return pClone;
        }
        case EObjectId::kUnaryContainer:
        {
            UnaryContainerSPtr pClone(new UnaryContainer());
            *pClone = *downcastUnaryContainer(pObject);
            return pClone;
        }
        case EObjectId::kUnaryTemplate:
        {
            UnaryTemplateSPtr pClone(new UnaryTemplate());
            *pClone = *downcastUnaryTemplate(pObject);
            return pClone;
        }
        case EObjectId::kUpcopy:
        {
            UpcopySPtr pClone(new Upcopy());
            *pClone = *downcastUpcopy(pObject);
            return pClone;
        }
        case EObjectId::kVersion:
        {
            VersionSPtr pClone(new Version());
            *pClone = *downcastVersion(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return ObjectSPtr();
}

AbsoluteEnumerationValueSPtr ObjectFactory::downcastAbsoluteEnumerationValue(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == AbsoluteEnumerationValue::staticObjectId());

    if (b)
        return boost::static_pointer_cast<AbsoluteEnumerationValue>(pObject);
    return AbsoluteEnumerationValueSPtr();
}

AlterSPtr ObjectFactory::downcastAlter(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Alter::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Alter>(pObject);
    return AlterSPtr();
}

CommentSPtr ObjectFactory::downcastComment(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Comment::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Comment>(pObject);
    return CommentSPtr();
}

ComposedEnumerationValueSPtr ObjectFactory::downcastComposedEnumerationValue(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == ComposedEnumerationValue::staticObjectId());

    if (b)
        return boost::static_pointer_cast<ComposedEnumerationValue>(pObject);
    return ComposedEnumerationValueSPtr();
}

DefaultValueSPtr ObjectFactory::downcastDefaultValue(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == DefaultValue::staticObjectId());

    if (b)
        return boost::static_pointer_cast<DefaultValue>(pObject);
    return DefaultValueSPtr();
}

DocumentSPtr ObjectFactory::downcastDocument(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Document::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Document>(pObject);
    return DocumentSPtr();
}

EnumerationSPtr ObjectFactory::downcastEnumeration(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Enumeration::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Enumeration>(pObject);
    return EnumerationSPtr();
}

EnumerationValueSPtr ObjectFactory::downcastEnumerationValue(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == EnumerationValue::staticObjectId())
          // or any of the derived classes
          || (pObject->runtimeObjectId() == AbsoluteEnumerationValue::staticObjectId())
          || (pObject->runtimeObjectId() == ComposedEnumerationValue::staticObjectId());

    if (b)
        return boost::static_pointer_cast<EnumerationValue>(pObject);
    return EnumerationValueSPtr();
}

FactorySPtr ObjectFactory::downcastFactory(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Factory::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Factory>(pObject);
    return FactorySPtr();
}

FieldSPtr ObjectFactory::downcastField(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Field::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Field>(pObject);
    return FieldSPtr();
}

FieldOverrideSPtr ObjectFactory::downcastFieldOverride(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == FieldOverride::staticObjectId());

    if (b)
        return boost::static_pointer_cast<FieldOverride>(pObject);
    return FieldOverrideSPtr();
}

FilterSPtr ObjectFactory::downcastFilter(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Filter::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Filter>(pObject);
    return FilterSPtr();
}

IdentificationSPtr ObjectFactory::downcastIdentification(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Identification::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Identification>(pObject);
    return IdentificationSPtr();
}

IdentifierSPtr ObjectFactory::downcastIdentifier(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Identifier::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Identifier>(pObject);
    return IdentifierSPtr();
}

ImportSPtr ObjectFactory::downcastImport(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Import::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Import>(pObject);
    return ImportSPtr();
}

IntegerSPtr ObjectFactory::downcastInteger(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Integer::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Integer>(pObject);
    return IntegerSPtr();
}

InterfaceSPtr ObjectFactory::downcastInterface(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Interface::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Interface>(pObject);
    return InterfaceSPtr();
}

MethodSPtr ObjectFactory::downcastMethod(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Method::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Method>(pObject);
    return MethodSPtr();
}

NameSPtr ObjectFactory::downcastName(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Name::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Name>(pObject);
    return NameSPtr();
}

OperatorSPtr ObjectFactory::downcastOperator(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Operator::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Operator>(pObject);
    return OperatorSPtr();
}

PackageSPtr ObjectFactory::downcastPackage(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Package::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Package>(pObject);
    return PackageSPtr();
}

ParameterSPtr ObjectFactory::downcastParameter(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Parameter::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Parameter>(pObject);
    return ParameterSPtr();
}

ReferenceSPtr ObjectFactory::downcastReference(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Reference::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Reference>(pObject);
    return ReferenceSPtr();
}

SpecimenSPtr ObjectFactory::downcastSpecimen(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Specimen::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Specimen>(pObject);
    return SpecimenSPtr();
}

StructureSPtr ObjectFactory::downcastStructure(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Structure::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Structure>(pObject);
    return StructureSPtr();
}

TypeSPtr ObjectFactory::downcastType(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Type::staticObjectId())
          // or any of the derived classes
          || (pObject->runtimeObjectId() == Enumeration::staticObjectId())
          || (pObject->runtimeObjectId() == Factory::staticObjectId())
          || (pObject->runtimeObjectId() == Identifier::staticObjectId())
          || (pObject->runtimeObjectId() == Integer::staticObjectId())
          || (pObject->runtimeObjectId() == Reference::staticObjectId())
          || (pObject->runtimeObjectId() == Specimen::staticObjectId())
          || (pObject->runtimeObjectId() == Structure::staticObjectId())
          || (pObject->runtimeObjectId() == UnaryContainer::staticObjectId())
          || (pObject->runtimeObjectId() == UnaryTemplate::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Type>(pObject);
    return TypeSPtr();
}

UnaryContainerSPtr ObjectFactory::downcastUnaryContainer(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == UnaryContainer::staticObjectId());

    if (b)
        return boost::static_pointer_cast<UnaryContainer>(pObject);
    return UnaryContainerSPtr();
}

UnaryTemplateSPtr ObjectFactory::downcastUnaryTemplate(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == UnaryTemplate::staticObjectId())
          // or any of the derived classes
          || (pObject->runtimeObjectId() == Enumeration::staticObjectId())
          || (pObject->runtimeObjectId() == Factory::staticObjectId())
          || (pObject->runtimeObjectId() == Identifier::staticObjectId())
          || (pObject->runtimeObjectId() == Reference::staticObjectId())
          || (pObject->runtimeObjectId() == Specimen::staticObjectId())
          || (pObject->runtimeObjectId() == UnaryContainer::staticObjectId());

    if (b)
        return boost::static_pointer_cast<UnaryTemplate>(pObject);
    return UnaryTemplateSPtr();
}

UpcopySPtr ObjectFactory::downcastUpcopy(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Upcopy::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Upcopy>(pObject);
    return UpcopySPtr();
}

VersionSPtr ObjectFactory::downcastVersion(const ObjectSPtr& pObject)
{
    bool b = (pObject->runtimeObjectId() == Version::staticObjectId());

    if (b)
        return boost::static_pointer_cast<Version>(pObject);
    return VersionSPtr();
}

}

