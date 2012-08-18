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

#include "parameter_type_validator.h"
#include "identifier.h"
#include "enumeration.h"

#include "gtest/gtest.h"

class ParameterTypeValidatorTests : public ::testing::Test 
{
public:
    virtual void SetUp() 
    {
         mpMessageCollector.reset(new compil::MessageCollector());
    }
    
protected:
    compil::MessageCollectorPtr mpMessageCollector;
};

TEST_F(ParameterTypeValidatorTests, DISABLED_wrongTypeDeathTest)
{
    compil::ParameterTypeValidator validator(compil::EObjectId::identifier());
    compil::IdentifierSPtr pIdentifier(new compil::Identifier());
    ASSERT_DEATH(validator.validate(pIdentifier, mpMessageCollector), "Assertion.*failed");
}

TEST_F(ParameterTypeValidatorTests, validate)
{
    compil::ParameterTypeValidator validator(compil::EObjectId::identifier());

    compil::NameSPtr pName;
        
    compil::TypeSPtr pInt8Type(new compil::Integer());
    pInt8Type->set_sourceId(compil::SourceIdSPtr());
    pName.reset(new compil::Name());
    pName->set_value("int8");
    pInt8Type->set_name(pName);
    validator.addAcceptableType(pInt8Type);
    
    compil::TypeSPtr pBlahType(new compil::Integer());
    pName.reset(new compil::Name());
    pName->set_value("blah");
    pBlahType->set_name(pName);
    
    compil::IdentifierSPtr pIdentifier(new compil::Identifier());
    pIdentifier->set_sourceId(compil::SourceIdSPtr());
    pIdentifier->set_parameterType(pBlahType);
    EXPECT_FALSE(validator.validate(pIdentifier, mpMessageCollector));
    
    pIdentifier->set_parameterType(pInt8Type);
    EXPECT_TRUE(validator.validate(pIdentifier, mpMessageCollector));
    
    compil::EnumerationSPtr pEnumeration(new compil::Enumeration());
    EXPECT_TRUE(validator.validate(pEnumeration, mpMessageCollector));
}