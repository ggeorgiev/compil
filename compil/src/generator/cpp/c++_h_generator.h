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


#ifndef _CPP_HEADER_GENERATOR_H__
#define _CPP_HEADER_GENERATOR_H__

#include "generator/generator.h"
#include "generator/method_group.h"

#include <boost/shared_ptr.hpp>

#include <string>

namespace compil
{

class CppHeaderGenerator : public Generator
{
public:
    CppHeaderGenerator();
    virtual ~CppHeaderGenerator();
    
    virtual bool generate();
    
    virtual void generateImport(const ImportSPtr& pImport);
    virtual void generateForwardClassDeclarations(const TypeSPtr& pType);
    
    virtual void generateEnumerationValueConstDeclaration(const EnumerationValueSPtr& pEnumerationValue);
    virtual void generateEnumerationValueDeclaration(const EnumerationValueSPtr& pEnumerationValue);
    virtual void generateEnumerationDeclaration(const EnumerationSPtr& pEnumeration);
    
    virtual void generateSpecimenDeclaration(const SpecimenSPtr& pSpecimen);
    
    virtual void generateFactoryDeclaration(const FactorySPtr& pFactory);
    virtual void generateHierarchyFactoryDeclaration(const FactorySPtr& pFactory);
    virtual void generateObjectFactoryDeclaration(const FactorySPtr& pFactory);
    virtual void generatePluginFactoryDeclaration(const FactorySPtr& pFactory);

    virtual void generateIdentifierDeclaration(const IdentifierSPtr& pIdentifier);
    
    virtual void generateStructureFieldMemberDeclaration(const FieldSPtr& pField);
    
    virtual void generateStructureIdentificationMethodsDeclaration(
                    const IdentificationSPtr& pIdentification);
    virtual void generateStructureRuntimeIdentificationMethodsDeclaration(
                    const IdentificationSPtr& pIdentification);
    virtual void generateStructureInprocIdentificationMethodsDeclaration(
                    const IdentificationSPtr& pIdentification);
           
    virtual void generateStructureOperatorMethodsDeclaration(
                    const OperatorSPtr& pOperator,
                    const EOperatorFlags& flags,
                    bool& declaredFunctor);
    virtual void generateStructureOperatorMethodsDeclaration(
                    const OperatorSPtr& pOperator);

    virtual void generateStructureObjectMemberDeclaration(const ObjectSPtr& pObject);

    virtual void generateStructureFieldMethodsDeclaration(const StructureSPtr& pCurrStructure,
                                                          const FieldSPtr& pField,
                                                          const EMethodGroup& mg);
    virtual void generateStructureFieldOverrideMethodsDeclaration(const FieldOverrideSPtr& pFieldOverride,
                                                                  const EMethodGroup& mg);
    virtual void generateStructureObjectMethodsDeclaration(const ObjectSPtr& pObject,
                                                           const EMethodGroup& mg);
    
    virtual void generateImmutableBaseStructureBuilderDeclaration(const StructureSPtr& pCurrStructure,
                                                                  const StructureSPtr& pStructure,
                                                                  const EMethodGroup& overridden);
                                                                  
    virtual void generateBaseStructureDeclaration(const StructureSPtr& pCurrStructure,
                                                  const StructureSPtr& pStructure,
                                                  const EMethodGroup& overridden);
                                                                  
    virtual void generateStructureDeclaration(const StructureSPtr& pStructure);
    
    virtual void generateObjectDeclaration(const ObjectSPtr& pObject);

protected:
    void encapsulateInLine(int streamIndex, const std::string& encapsulation);
    void encapsulateInTable(const std::string& encapsulation);

    std::string mEncapsulation;

    static const int copyrightStream;
    static const int includeStream;
    static const int declarationStream;
    static const int inlineDefinitionStream;
    static const int forwardDeclarationStream;
};

typedef boost::shared_ptr<CppHeaderGenerator> CppHeaderGeneratorPtr;

}

#else

namespace compil
{

class CppHeaderGenerator;
typedef boost::shared_ptr<CppHeaderGenerator> CppHeaderGeneratorPtr;

}

#endif

