#include "structure.h"
#include "object_factory.h"

namespace compil
{

Structure::Structure()
{
}

Structure::~Structure()
{
}

bool Structure::isBuildable() const
{
    return (immutable() &&
           (!abstract() || hasField() || hasAlter() || !baseStructure().lock()));
}

bool Structure::isInitializable() const
{
    return controlled() &&
           (hasField() || !baseStructure().lock());
}

bool Structure::isOptional() const
{
    if (!controlled())
        return false;
        
    StructureSPtr pBaseStructure = baseStructure().lock();
    if (pBaseStructure)
    if (!pBaseStructure->isOptional()) return false;
    
    bool bResult = false;
    const std::vector<ObjectSPtr>& objs = objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objs.begin(); it != objs.end(); ++it)
    {
        FieldSPtr pField = ObjectFactory::downcastField(*it);
        if (!pField)
            continue;
        
        if (!pField->defaultValue())
            return false;
        
        if (!pField->defaultValue()->optional())
            continue;
        
        bResult = true;
    }
    return bResult;
}

bool Structure::hasRuntimeIdentification() const
{
    const std::vector<ObjectSPtr>& objs = objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objs.begin(); it != objs.end(); ++it)
    {
        IdentificationSPtr pIdentification = ObjectFactory::downcastIdentification(*it);
        if (pIdentification) 
        if (pIdentification->type() == Identification::EType::runtime())
            return true;
    }
    return false;
}

bool Structure::hasRuntimeIdentification(const StructureSPtr& pStructure)
{
    return pStructure->hasRuntimeIdentification();
}

bool Structure::hasField() const
{
    const std::vector<ObjectSPtr>& objs = objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objs.begin(); it != objs.end(); ++it)
    {
        FieldSPtr pField = ObjectFactory::downcastField(*it);
        if (pField) 
            return true;
    }
    return false;
}

bool Structure::hasAlter() const
{
    const std::vector<ObjectSPtr>& objs = objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objs.begin(); it != objs.end(); ++it)
    {
        AlterSPtr pAlter = ObjectFactory::downcastAlter(*it);
        if (pAlter) 
            return true;
    }
    return false;
}

StructureSPtr Structure::recursivelyBaseStructure()
{
    StructureSPtr pCheck = shared_from_this();
    for (;;)
    {
        StructureSPtr pBase = pCheck->baseStructure().lock();
        if (!pBase) break;
        pCheck = pBase;
    }
    return pCheck; 
}

bool Structure::isRecursivelyInherit(const StructureSPtr& pStructure)
{
    StructureSPtr pCheck = baseStructure().lock();
    while (pCheck)
    {
        if (pCheck == pStructure)
            return true;
        pCheck = pCheck->baseStructure().lock();
    }
    return false;
}

bool Structure::isRecursivelyRelatedTo(const StructureSPtr& pStructure)
{
    return isRecursivelyInherit(pStructure) || 
           pStructure->isRecursivelyInherit(shared_from_this());
}


FieldSPtr Structure::findField(const std::string& name) const
{
    StructureSCPtr pStruct = shared_from_this();
    while (pStruct)
    {
        const std::vector<ObjectSPtr>& objects = pStruct->objects();
        std::vector<ObjectSPtr>::const_iterator it;
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            FieldSPtr pField = ObjectFactory::downcastField(*it);
            if (pField)
            {
                if (pField->name()->value() == name)
                    return pField;
            }
        }
        pStruct = pStruct->baseStructure().lock();
    }    
        
    return FieldSPtr();
}

std::vector<FieldSPtr> Structure::combinedFields()
{
    std::vector<FieldSPtr> result;
    StructureSPtr pBaseStructure = baseStructure().lock();
    if (pBaseStructure)
        result = pBaseStructure->combinedFields();

    const std::vector<ObjectSPtr>& objs = objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objs.begin(); it != objs.end(); ++it)
    {
        FieldSPtr pField = ObjectFactory::downcastField(*it);
        if (pField)
            result.push_back(pField);
    }
    
    return result;
}

bool Structure::fieldIterate(std::vector<FieldSPtr>& iteration)
{
    std::vector<FieldSPtr> fields = combinedFields();
    std::vector<FieldSPtr>::iterator it;
    
    // if the iteration is empty first add all obligatory fields 
    if (iteration.size() == 0)
    {
        for (it = fields.begin(); it != fields.end(); ++it)
        {
            const FieldSPtr& pField = *it;
            if (!pField->defaultValue())
                iteration.push_back(pField);
        }
        
        if (iteration.size() != 0)
            return true;
    }
    
    std::vector<FieldSPtr>::iterator place = iteration.begin();
    for (it = fields.begin(); it != fields.end(); ++it)
    {
        const FieldSPtr& pField = *it;
        
        if (place != iteration.end())
        if (*place == pField)
        {
            if (pField->defaultValue())
                place = iteration.erase(place);
            else
                ++place;
            continue;
        }
        
        if (pField->defaultValue())
        {
            place = iteration.insert(place, pField);
            ++place;
            break;
        }
    }
    
    if (it == fields.end())
        return false;
    
    return true;
}

bool Structure::hasOperator(const EOperatorAction& action,
                            const EOperatorFlags& flags) const
{
    const std::vector<ObjectSPtr>& objs = objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objs.begin(); it != objs.end(); ++it)
    {
        OperatorSPtr pOperator = ObjectFactory::downcastOperator(*it);
        if (pOperator) 
        if (pOperator->action() == action)
        if (pOperator->flags().isSet(flags))
            return true;
    }
    return false;
}

bool Structure::isOverriden(const FieldSPtr& pField) const
{
    const std::vector<ObjectSPtr>& objs = objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objs.begin(); it != objs.end(); ++it)
    {
        FieldOverrideSPtr pFieldOverride = ObjectFactory::downcastFieldOverride(*it);
        if (!pFieldOverride) continue;
        
        if (pFieldOverride->overriddenField() == pField)
            return true;
    }
    return false;
}

}

