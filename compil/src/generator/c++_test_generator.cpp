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

#include "c++_test_generator.h"
#include "implementer_stream.h"

#include "c++/expression/custom_expression.h"
#include "c++/test/test_suite.h"
#include "c++/statement/test_statement.h"
#include "c++/statement/declaration_statement.h"

namespace compil
{

using namespace lang::cpp;

const int CppTestGenerator::mainStream = 0;

CppTestGenerator::CppTestGenerator()
{
    for (int i = 0; i <= 0; ++i)
    {
        mStreams.push_back(boost::shared_ptr<std::stringstream>(new std::stringstream()));
        mIndent.push_back(0);
    }
}

CppTestGenerator::~CppTestGenerator()
{
}

const TestSPtr& operator<<(const TestSPtr& test, const DeclarationStatementSPtr& statement)
{
    return test << boost::shared_polymorphic_cast<Statement>(statement);
}

void CppTestGenerator::generateStructureDeclaration(const StructureSPtr& pStructure)
{
    TestSuite suite;
    suite << TestSuiteName(pStructure->name()->value() + "Test");
    
    if (pStructure->isInitializable())
    {
        TestSPtr test = testRef();
        test << TestName("isInitialized");
        
        test << (declarationStatementRef() << ClassName(pStructure->name()->value())
                                           << std::string("structure"));
                                           
        UnaryTestStatement::EType type = pStructure->isOptional()
                                         ? UnaryTestStatement::EType::isTrue()
                                         : UnaryTestStatement::EType::isFalse();
        test << (unaryTestStatementRef() << type
                                         << (customExpressionRef() << std::string("structure.isInitialized()")));
        
        suite << test;
    }
    
    ImplementerStream stream(impl->mpConfiguration, frm->mpFormatterConfiguration, mpAlignerConfiguration);
    
    stream << suite;
    
    line() << stream.str();
    eol(mainStream);
}

void CppTestGenerator::generateObjectDeclaration(const ObjectSPtr& pObject)
{
    switch (pObject->runtimeObjectId().value())
    {
        case EObjectId::kStructure:
        {
            StructureSPtr pStructure = boost::static_pointer_cast<Structure>(pObject);
            generateStructureDeclaration(pStructure);
            break;
        }
        default:
            break;
    }
}

bool CppTestGenerator::generate()
{
    addDependency(impl->cppHeaderFileDependency(mpModel->name()->value(),
                                                mpModel->package()));
                                                
    addDependency(Dependency("gtest/gtest.h",
                             Dependency::system_type,
                             Dependency::thirdparty_level,
                             Dependency::private_section,
                             "Google Test framework"));
                             
    includeHeaders(mainStream, Dependency::private_section);
    
    const std::vector<ObjectSPtr>& objects = mpModel->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
		if ((*it)->sourceId() != mpModel->mainDocument()->sourceId())
			continue;

        generateObjectDeclaration(*it);
    }

    return serializeStreams();
}

}

