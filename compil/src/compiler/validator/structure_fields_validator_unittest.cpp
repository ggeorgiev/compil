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

#include "structure_fields_validator.h"

#include "compil/document/structure.h"

#include "gtest/gtest.h"

class StructureFieldsValidatorTests : public ::testing::Test 
{
public:
    virtual void SetUp() 
    {
         mpMessageCollector.reset(new compil::MessageCollector());
    }
    
protected:
    compil::MessageCollectorPtr mpMessageCollector;
};



TEST_F(StructureFieldsValidatorTests, construct)
{
    compil::StructureFieldsValidator validator;
}

TEST_F(StructureFieldsValidatorTests, validate)
{
    compil::StructureSPtr pStructure(new compil::Structure());
    
    compil::NameSPtr pName(new compil::Name());
    pName->set_value("name");
    pName->set_sourceId(compil::SourceIdSPtr());
    
    compil::FieldSPtr pField(new compil::Field());
    pField->set_name(pName);
    
    std::vector<compil::ObjectSPtr> objects;
    
    objects.push_back(pField);
    pStructure->set_objects(objects);
    
    compil::StructureFieldsValidator validator;
    EXPECT_TRUE(validator.validate(pStructure, mpMessageCollector));
    
    objects.push_back(pField);
    pStructure->set_objects(objects);
    EXPECT_FALSE(validator.validate(pStructure, mpMessageCollector));
}