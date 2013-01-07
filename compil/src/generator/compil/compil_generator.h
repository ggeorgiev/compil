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


#ifndef _COMPIL_GENERATOR_H__
#define _COMPIL_GENERATOR_H__

#include "generator/generator.h"

#include <boost/shared_ptr.hpp>

#include <memory>
#include <string>

namespace compil
{

class CompilGenerator : public Generator
{
public:
    CompilGenerator();
    virtual ~CompilGenerator();
    
    virtual bool generate();
    
    virtual void generateFile(const FileSPtr& file);
    
    virtual void generateImport(const ImportSPtr& pImport);
    
    virtual void generateEnumerationPrefix(const EnumerationSPtr& pEnumeration);
    virtual void generateEnumerationSuffix(const EnumerationSPtr& pEnumeration);
    
    virtual void generateSpecimenPrefix(const SpecimenSPtr& pSpecimen);
    virtual void generateSpecimenSuffix(const SpecimenSPtr& pSpecimen);
    
    virtual void generateFactoryPrefix(const FactorySPtr& pFactory);
    virtual void generateFactorySuffix(const FactorySPtr& pFactory);
    
    virtual void generateEnumerationValuePrefix(const EnumerationValueSPtr& pEnumerationValue);
    virtual void generateEnumerationValueSuffix(const EnumerationValueSPtr& pEnumerationValue); 
    
    virtual void generateStructurePrefix(const StructureSPtr& pStructure);
    virtual void generateStructureSuffix(const StructureSPtr& pStructure);

    virtual void generateFieldPrefix(const FieldSPtr& pField);
    virtual void generateFieldSuffix(const FieldSPtr& pField);
    
    virtual void generateIdentificationPrefix(const IdentificationSPtr& pIdentification);
    virtual void generateIdentificationSuffix(const IdentificationSPtr& pIdentification);

    virtual void generateInterfacePrefix(const InterfaceSPtr& pInterface);
    virtual void generateInterfaceSuffix(const InterfaceSPtr& pInterface);

    virtual void generateMethodPrefix(const MethodSPtr& pMethod);
    virtual void generateMethodSuffix(const MethodSPtr& pMethod);

    virtual void generateParameterPrefix(const ParameterSPtr& pParameter);
    virtual void generateParameterSuffix(const ParameterSPtr& pParameter);
    
    void generateObject(const ObjectSPtr& object);
    void generateObjects(const std::vector<ObjectSPtr>& objects);
    
protected:
    static const int declarationStream;
    
private:
    bool bAddNewLine;
};

typedef boost::shared_ptr<CompilGenerator> CompilGeneratorPtr;

}

#else

namespace compil
{

class CompilGenerator;
typedef boost::shared_ptr<CompilGenerator> CompilGeneratorPtr;

}

#endif

