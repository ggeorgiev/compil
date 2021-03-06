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

#ifndef _IMPLEMENTER_STREAM_H__
#define _IMPLEMENTER_STREAM_H__

#include "generator/c++/configuration/implementer_configuration.h"

#include "generator/c++/namer_stream.h"

#include "language/c++/test/test_suite.h"
#include "language/c++/declaration/declaration_factory.h"


#include <boost/shared_ptr.hpp>

class ImplementerStream
{
public:
    ImplementerStream(const ImplementerConfigurationSPtr& implementerConfiguration,
                      const NamerConfigurationSPtr& namerConfiguration,
                      const FormatterConfigurationSPtr& formatterConfiguration,
                      const AlignerConfigurationSPtr& alignerConfiguration);
    virtual ~ImplementerStream();
    
    std::string str();
    
    ImplementerStream& operator<<(const lang::cpp::TestSuite& suite);
    ImplementerStream& operator<<(const lang::cpp::ClassSPtr& class_);
    
private:
    lang::cpp::DeclarationSpecifierSequenceSPtr convert(const lang::cpp::DeclarationSpecifierSequenceSPtr& sequence);
    lang::cpp::DeclarationSpecifierSPtr convert(const lang::cpp::DeclarationSpecifierSPtr& specifier);
    void convert(const lang::cpp::MemberSpecificationSectionSPtr& section,
                 const std::vector<lang::cpp::ConstructorSPtr>& constructors);
    void convert(const lang::cpp::MemberSpecificationSectionSPtr& section,
                 const lang::cpp::DestructorSPtr& destructor);
    void convert(const lang::cpp::MemberSpecificationSectionSPtr& section,
                 const std::vector<lang::cpp::MethodSPtr>& methods);
    void convert(const lang::cpp::MemberSpecificationSectionSPtr& section,
                 const std::vector<lang::cpp::MemberVariableSPtr>& members);
                 
    lang::cpp::BodyFunctionDefinitionSPtr methodBodyDefinition(const lang::cpp::DeclarationSpecifierSequenceSPtr& specifier,
                                                               const lang::cpp::MethodNameSPtr& methodName,
                                                               const lang::cpp::ParameterDeclarationClauseSPtr& parameters,
                                                               const lang::cpp::CVQualifierSequenceSPtr& qualifier);

    lang::cpp::FunctionDefinitionMemberDeclarationSPtr methodDefinition(const lang::cpp::DeclarationSpecifierSequenceSPtr& specifier,
                                                                        const lang::cpp::MethodNameSPtr& methodName,
                                                                        const lang::cpp::ParameterDeclarationClauseSPtr& parameters,
                                                                        const lang::cpp::CVQualifierSequenceSPtr& qualifier);

    
    nmr::NamerStream mNamer;
    ImplementerConfigurationSPtr mConfiguration;
};

typedef boost::shared_ptr<ImplementerStream> ImplementerStreamSPtr;
typedef boost::weak_ptr<ImplementerStream> ImplementerStreamWPtr;

#endif

