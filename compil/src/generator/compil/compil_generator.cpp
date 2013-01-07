// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * The name of George Georgiev can not be used to endorse or 
// promote products derived from this software without specific prior 
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: george.georgiev@hotmail.com (George Georgiev)
//

#include "generator/compil/compil_generator.h"

#include "language/compil/all/object_factory.h"

namespace compil
{

const int CompilGenerator::declarationStream = 0;

CompilGenerator::CompilGenerator()
        : bAddNewLine(false)
{
    mStreams.push_back(boost::shared_ptr<std::stringstream>(new std::stringstream()));
    mIndent.push_back(0);
}

CompilGenerator::~CompilGenerator()
{
}

void CompilGenerator::generateFile(const FileSPtr&)
{
    line()  << "compil {}";
    eol(declarationStream);
}

void CompilGenerator::generateImport(const ImportSPtr& pImport)
{
    line()  << "import \"" << pImport->source() << "\";";
    eol(declarationStream);
}
    
void CompilGenerator::generateEnumerationPrefix(const EnumerationSPtr& pEnumeration)
{
    if (pEnumeration->structure().lock())
    {
        if (!table().isEmpty())
        {
            eot(declarationStream);
            eol(declarationStream);
        }
        bAddNewLine = true;
    }

    switch (pEnumeration->cast().value())
    {
        case CastableType::ECast::kWeak: 
            line() << "weak ";
            break;
        case CastableType::ECast::kStrong: 
            line() << "strong ";
            break;
        default:
            assert(false && "unknown cast type");
    }
   
    line()  << "enum";
    TypeSPtr pType = pEnumeration->parameterType().lock();
    if (pType)
    {
        line()  << "<" << pType->name()->value() << ">";
    }
    
    line()  << " " << pEnumeration->name()->value();
    openBlock(declarationStream);
}

void CompilGenerator::generateEnumerationSuffix(const EnumerationSPtr&)
{
    eot(declarationStream);
    closeBlock(declarationStream);
}

void CompilGenerator::generateEnumerationValuePrefix(const EnumerationValueSPtr& pEnumerationValue)
{
    table() << TableAligner::row()
            << pEnumerationValue->name()->value()
            << ";";
}
    
void CompilGenerator::generateEnumerationValueSuffix(const EnumerationValueSPtr&)
{
}

void CompilGenerator::generateSpecimenPrefix(const SpecimenSPtr& pSpecimen)
{
    line()  << "specimen";
    TypeSPtr pType = pSpecimen->parameterType().lock();
    if (pType)
    {
        line()  << "<" << pType->name()->value() << ">";
    }
    
    line()  << " " << pSpecimen->name()->value();
    openBlock(declarationStream);
}

void CompilGenerator::generateSpecimenSuffix(const SpecimenSPtr&)
{
    eot(declarationStream);
    closeBlock(declarationStream);
}

void CompilGenerator::generateFactoryPrefix(const FactorySPtr& pFactory)
{
    switch (pFactory->type().value())
    {
        case Factory::EType::kHierarchy: 
            line() << "hierarchy ";
            break;
        case Factory::EType::kObject: 
            line() << "object ";
            break;
        default:
            assert(false && "unknown cast type");
    }

    line()  << "factory";
    TypeSPtr pType = pFactory->parameterType().lock();
    if (pType)
    {
        line()  << "<" << pType->name()->value() << ">";
    }
    
    line()  << " " << pFactory->name()->value();
    openBlock(declarationStream);
}

void CompilGenerator::generateFactorySuffix(const FactorySPtr&)
{
    eot(declarationStream);
    closeBlock(declarationStream);
}

void CompilGenerator::generateStructurePrefix(const StructureSPtr& pStructure)
{
    if (pStructure->controlled())
        line() << "controlled ";
        
    if (pStructure->immutable())
        line() << "immutable ";
        
    if (pStructure->partial())
        line() << "partial ";

    line() << "structure " << pStructure->name()->value();
    
    int indexOffset = 0;
    StructureSPtr pBaseStructure = pStructure->baseStructure().lock();
    if (pBaseStructure)
    {
        eol(declarationStream);
        
        ++indexOffset;
        ++mIndent[declarationStream];
        line() << "inherit " << pBaseStructure->name()->value();
        
        const std::vector<ObjectSPtr>& objects = pStructure->objects();
        bool first_alter = true;
        std::vector<ObjectSPtr>::const_iterator it;
        for (it = objects.begin(); it != objects.end(); ++it)
        {
            AlterSPtr pAlter = ObjectFactory::downcastAlter(*it);
            if (!pAlter) continue;
            
            if (first_alter)
            {
                first_alter = false;
                eol(declarationStream);
                ++mIndent[declarationStream];
                ++indexOffset;
                table() << TableAligner::row()
                        << "alter ";
            }
            else
            {
                table() << ","
                        << TableAligner::row();
            }
            
            table() << TableAligner::col()
                    << pAlter->field()->name()->value() << " "
                    << TableAligner::col()
                    << "= "
                    << pAlter->defaultValue()->value();        
        }
    }
    mIndent[declarationStream] -= indexOffset;
    openBlock(declarationStream, indexOffset);
}

void CompilGenerator::generateStructureSuffix(const StructureSPtr&)
{
    eot(declarationStream);
    closeBlock(declarationStream);
    eol(declarationStream);
    bAddNewLine = false;
}

void CompilGenerator::generateFieldPrefix(const FieldSPtr& pField)
{
    table() << TableAligner::row();
        
    if (bAddNewLine)
    {
        table() << TableAligner::row();
        bAddNewLine = false;
    }
        
    // only 2 levels allowed - reference< containter<type> > or containter< reference<type> > 
    UnaryTemplateSPtr pTemplate = ObjectFactory::downcastUnaryTemplate(pField->type());
    if (pTemplate)
    {
        table() << pTemplate->name()->value() << "<";
        UnaryTemplateSPtr pTemplate2 = 
            ObjectFactory::downcastUnaryTemplate(pTemplate->parameterType().lock());
        if (pTemplate2)
        {
            table() << " " 
                << pTemplate2->name()->value() 
                << "<"   
                << pTemplate2->parameterType().lock()->name()->value()
                << "> ";
        }
        else
        {
            table() << pTemplate->parameterType().lock()->name()->value();
        }
        table() << ">";
    }
    else
    {
        table() << pField->type()->name()->value();
    }
    
    table() << ' ' 
            << TableAligner::col()
            << pField->name()->value();

    if (pField->defaultValue())
    {
        table() << ' ' 
                << TableAligner::col()
                << "= "
                << TableAligner::col();
        if (pField->defaultValue()->optional())
        {
            table() << "optional";
        }
        else
        {
            if (pField->type()->literal() == Type::ELiteral::string())
            {
                table() << "'" << pField->defaultValue()->value() << "'";
            }
            else
            {
                table() << pField->defaultValue()->value();
            }
        }
    }
    table() << ";";
}

void CompilGenerator::generateFieldSuffix(const FieldSPtr&)
{
}

void CompilGenerator::generateIdentificationPrefix(const IdentificationSPtr& pIdentification)
{
    switch (pIdentification->type().value())
    {
        case Identification::EType::kRuntime: 
            line() << "runtime";
            break;
        case Identification::EType::kInproc: 
            line() << "inproc";
            break;
        default:
            assert(false && "unknown identification type");
    }

    line()  << " identification;";
    eol(declarationStream);
}

void CompilGenerator::generateIdentificationSuffix(const IdentificationSPtr&)
{
}

void CompilGenerator::generateInterfacePrefix(const InterfaceSPtr& pInterface)
{
    line() << "interface " << pInterface->name()->value();
    openBlock(declarationStream);
}

void CompilGenerator::generateInterfaceSuffix(const InterfaceSPtr&)
{
    closeBlock(declarationStream);
}

void CompilGenerator::generateMethodPrefix(const MethodSPtr& pMethod)
{
    line() << "method " << pMethod->name()->value();
    openBlock(declarationStream);
}

void CompilGenerator::generateMethodSuffix(const MethodSPtr&)
{
    closeBlock(declarationStream);
}

void CompilGenerator::generateParameterPrefix(const ParameterSPtr& pParameter)
{
    switch (pParameter->direction().value())
    {
        case Parameter::EDirection::kIn:  line() << "-->"; break;
        case Parameter::EDirection::kOut: line() << "<--"; break;
        case Parameter::EDirection::kIo:  line() << "<->"; break;
        default: assert(false && "unknown parameter direction");
    }
    line()  << " " << pParameter->type()->name()->value()
            << " " << pParameter->name()->value() << ";";
    eol(declarationStream);
}

void CompilGenerator::generateParameterSuffix(const ParameterSPtr&)
{
}

void CompilGenerator::generateObject(const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kImport:
        {
            ImportSPtr pImport = boost::static_pointer_cast<Import>(pObject); 
            generateImport(pImport);
            break;
        }        
        case EObjectId::kEnumeration:
        {
            EnumerationSPtr pEnumeration = boost::static_pointer_cast<Enumeration>(pObject); 
            generateEnumerationPrefix(pEnumeration);
            
            const std::vector<EnumerationValueSPtr>& enumerationValues = pEnumeration->enumerationValues();
            std::vector<EnumerationValueSPtr>::const_iterator it;
            for (it = enumerationValues.begin(); it != enumerationValues.end(); ++it)
            {
                generateEnumerationValuePrefix(*it);
                generateEnumerationValueSuffix(*it);
            }
            generateEnumerationSuffix(pEnumeration);
            break;
        }
        case EObjectId::kSpecimen:
        {
            SpecimenSPtr pSpecimen = boost::static_pointer_cast<Specimen>(pObject);
            generateSpecimenPrefix(pSpecimen);
            generateSpecimenSuffix(pSpecimen);
            break;
        }
        case EObjectId::kFactory:
        {
            FactorySPtr pFactory = boost::static_pointer_cast<Factory>(pObject);
            generateFactoryPrefix(pFactory);
            generateFactorySuffix(pFactory);
            break;
        }
        case EObjectId::kFile:
        {
            FileSPtr file = boost::static_pointer_cast<File>(pObject);
            generateFile(file);
            break;
        }
        case EObjectId::kStructure:
        {
            StructureSPtr pStructure = boost::static_pointer_cast<Structure>(pObject); 
            generateStructurePrefix(pStructure);
            generateObjects(pStructure->objects());
            generateStructureSuffix(pStructure);
            break;
        }
        
        case EObjectId::kAlter:
            break;
        
        case EObjectId::kField:
        {
            FieldSPtr pField = boost::static_pointer_cast<Field>(pObject); 
            generateFieldPrefix(pField);
            generateFieldSuffix(pField);
            break;
        }
        case EObjectId::kIdentification:
        {
            IdentificationSPtr pIdentification = boost::static_pointer_cast<Identification>(pObject); 
            generateIdentificationPrefix(pIdentification);
            generateIdentificationSuffix(pIdentification);
            break;
        }        
            
        case EObjectId::kInterface:
        {
            InterfaceSPtr pInterface = boost::static_pointer_cast<Interface>(pObject); 
            generateInterfacePrefix(pInterface);
            generateObjects(pInterface->objects());
            generateInterfaceSuffix(pInterface);
            break;
        }
            
        case EObjectId::kMethod:
        {
            MethodSPtr pMethod = boost::static_pointer_cast<Method>(pObject); 
            generateMethodPrefix(pMethod);
            generateObjects(pMethod->objects());
            generateMethodSuffix(pMethod);
            break;
        }
            
        case EObjectId::kParameter:
        {
            ParameterSPtr pParameter = boost::static_pointer_cast<Parameter>(pObject); 
            generateParameterPrefix(pParameter);
            generateParameterSuffix(pParameter);
            break;
        }

        default:
            assert(false);
    }
}

void CompilGenerator::generateObjects(const std::vector<ObjectSPtr>& objects)
{
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if ((*it)->sourceId() != mDocument->mainFile()->sourceId())
			continue;

        generateObject(*it);
    }
}
    
bool CompilGenerator::generate()
{
    generateObject(mDocument->mainFile());
    generateObjects(mDocument->objects());
    return serializeStreams();
}

}

