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


#ifndef __GENERATOR_CPP_CPP_GENERATOR_H__
#define __GENERATOR_CPP_CPP_GENERATOR_H__
#pragma once

#include "generator/generator.h"

#include <boost/shared_ptr.hpp>

#include <memory>
#include <string>

namespace compil
{

class CppGenerator : public Generator
{
public:
    CppGenerator();
    virtual ~CppGenerator();
    
    virtual bool generate();
    
    virtual void generateEnumerationValueDefinition(const EnumerationValueSPtr& pEnumerationValue);
    virtual void generateEnumerationDefinition(const EnumerationSPtr& pEnumeration);
    
    virtual void generateSpecimenDefinition(const SpecimenSPtr& pSpecimen);
    
    virtual void generateFactoryDefinition(const FactorySPtr& pFactory);
    virtual void generateHierarchyFactoryDefinition(const FactorySPtr& pFactory);
    virtual void generateObjectFactoryDefinition(const FactorySPtr& pFactory);
    virtual void generatePluginFactoryDefinition(const FactorySPtr& pFactory);
    
    virtual void generateIdentifierDefinition(const IdentifierSPtr& pIdentifier);
    
    virtual void generateInitialization(const cpp::frm::InitializationSPtr& initialization);
    
    virtual void generateStructureFieldMemberInitialization(const FieldSPtr& pField);
    virtual void generateStructureObjectMemberInitialization(const ObjectSPtr& pObject);

    virtual void generateStructureFieldWritingDefinition(const StructureSPtr& pStructure, 
                                                         const FieldSPtr& pField);
    virtual void generateStructureFieldConstantDefinition(const StructureSPtr& pStructure,
                                                          const FieldSPtr& pField, 
                                                          const Type::ELiteral literal,
                                                          const DefaultValueSPtr& pDefaultValue);
    virtual void generateStructureFieldDefinition(const FieldSPtr& pField);
    virtual void generateStructureFieldOverrideDefinition(const FieldOverrideSPtr& pFieldOverride);
                                                          
    virtual void generateStructureIdentificationMethodsDefinition(
                    const IdentificationSPtr& pIdentification);
    virtual void generateStructureRuntimeIdentificationMethodsDefinition(
                    const IdentificationSPtr& pIdentification);
    virtual void generateStructureInprocIdentificationMethodsDefinition(
                    const IdentificationSPtr& pIdentification);

    virtual std::string computeStructureOperatorExpression(
                    const TypeSPtr& pType,
                    const EOperatorAction& action,
                    const EOperatorFlags& flags,
                    const EOperatorFlags& stopFlags,
                    const std::string& cast,
                    const std::string& method,
                    bool reverse = false);
    virtual bool generateStructureOperatorAction(
                    const TypeSPtr& pType,
                    const EOperatorAction& action,
                    const EOperatorFlags& flags,
                    const EOperatorFlags& stopFlags,
                    const std::string& cast,
                    const std::string& method,
                    bool silent);
    virtual void generateStructureOperatorObjects(
                    const StructureSPtr& pStructure,
                    const OperatorSPtr& pOperator,
                    const EOperatorFlags& flags);
    virtual void generateStructureOperatorBaseStructure(
                    const StructureSPtr& pStructure,
                    const OperatorSPtr& pOperator,
                    const EOperatorFlags& flags);
    virtual void generateStructureOperatorMethodsDefinition(
                    const OperatorSPtr& pOperator,
                    const EOperatorFlags& flags);
    virtual void generateStructureOperatorMethodsDefinition(
                    const OperatorSPtr& pOperator);
    
                    
    virtual void generateStructureObjectDefinition(const StructureSPtr& pStructure, const ObjectSPtr& pObject);
    
    virtual void generateBaseStructureDefinition(const StructureSPtr& pStructure,
                                                 const StructureSPtr& pBaseStructure);
    virtual void generateStructureDefinition(const StructureSPtr& pStructure);
    
    virtual void generateObjectDefinition(const ObjectSPtr& pObject);
    
protected:
    static const int copyrightStream;
    static const int includeStream;
    static const int definitionStream;
    static const int cache1Stream;
    static const int cache2Stream;
};

typedef boost::shared_ptr<CppGenerator> CppGeneratorPtr;

}

#else

namespace compil
{

class CppGenerator;
typedef boost::shared_ptr<CppGenerator> CppGeneratorPtr;

}

#endif // __GENERATOR_CPP_CPP_GENERATOR_H__