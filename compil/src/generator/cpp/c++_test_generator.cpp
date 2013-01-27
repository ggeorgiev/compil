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

#include "generator/cpp/c++_test_generator.h"

#include "generator/c++/implementer_stream.h"

#include "library/c++/boost/exception.h"
#include "library/c++/compil/builder.h"
#include "library/c++/compil/specimen.h"

#include "language/c++/logical/local_variable_name.h"

namespace compil
{

using namespace lib::cpp;
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

void CppTestGenerator::generateSpecimenDeclaration(const SpecimenSPtr& specimen)
{
    TestSuite suite;
    suite << TestSuiteName("Specimen" + specimen->name()->value() + "Test");
    
    ClassSPtr class_ = CppSpecimen::class_(specimen);
        
    VariableExpressionSPtr specimen1 = variableExpressionRef()
        << (localVariableNameRef() << "specimen1");
    VariableExpressionSPtr specimen2 = variableExpressionRef()
        << (localVariableNameRef() << "specimen2");
        
    if (specimen->hasOperator(EOperatorAction::equalTo(), EOperatorFlags::native()))
    {
        TestSPtr test = testRef();
        test << TestName("operatorEqualTo");

        test << (variableDeclarationStatementRef() << class_
                                                   << specimen1->variable());
        test << (variableDeclarationStatementRef() << class_
                                                   << specimen2->variable());
                                                   
        GenericEqualityExpressionSPtr genericEqualityExpression = boost::make_shared<GenericEqualityExpression>();
        genericEqualityExpression->set_type(EqualityExpression::EType::equalTo());
        genericEqualityExpression->set_first(specimen1);
        genericEqualityExpression->set_second(specimen2);
        
        test    << (unaryTestStatementRef() << UnaryTestStatement::EType::isTrue()
                                            << genericEqualityExpression);
                                                   
        suite << test;
    }
    
    if (specimen->hasOperator(EOperatorAction::equalTo(), EOperatorFlags::native()))
    {
        TestSPtr test = testRef();
        test << TestName("operatorNotEqualTo");

        test << (variableDeclarationStatementRef() << class_
                                                   << specimen1->variable());
        test << (variableDeclarationStatementRef() << class_
                                                   << specimen2->variable());
                                                   
        GenericEqualityExpressionSPtr genericEqualityExpression = boost::make_shared<GenericEqualityExpression>();
        genericEqualityExpression->set_type(EqualityExpression::EType::notEqualTo());
        genericEqualityExpression->set_first(specimen1);
        genericEqualityExpression->set_second(specimen2);
        
        test    << (unaryTestStatementRef() << UnaryTestStatement::EType::isFalse()
                                            << genericEqualityExpression);
                                                   
        suite << test;
    }
    
    NamerConfigurationSPtr nc = boost::make_shared<NamerConfiguration>();
    
    ImplementerStream stream(impl->mConfiguration, nc, frm->mpFormatterConfiguration, mpAlignerConfiguration);
    
    stream << suite;
    
    line() << stream.str();
    eol(mainStream);
}

void CppTestGenerator::generateStructureDeclaration(const StructureSPtr& structure)
{
    TestSuite suite;
    suite << TestSuiteName("Structure" + structure->name()->value() + "Test");
    
    ClassSPtr class_ = classRef()
        << (identifierClassNameRef() << (identifierRef() << structure->name()->value()));
        
    ClassSPtr builderClass = CppBuilder::class_(class_);
    
    VariableExpressionSPtr structure1 = variableExpressionRef()
        << (localVariableNameRef() << "structure1");
    
    if (structure->controlled())
    {
        TestSPtr test = testRef();
        test << TestName("available_DefaultValues");
        
        test << (variableDeclarationStatementRef() << class_
                                                   << structure1->variable());
                                                   
        std::vector<FieldSPtr> fields = structure->combinedFields();
        for (std::vector<FieldSPtr>::iterator it = fields.begin(); it != fields.end(); ++it)
        {
            const FieldSPtr& field = *it;
            StructureSPtr fieldStructure = field->structure().lock();
            if (!fieldStructure->controlled())
                continue;
                
            AlterSPtr alter = structure->findTopAlter(field);
            UnaryTestStatement::EType type = alter
                                           ? UnaryTestStatement::EType::isTrue()
                                           : UnaryTestStatement::EType::isFalse();
            
            MethodCallExpressionSPtr availableFieldCall = methodCallExpressionRef()
                << structure1
                << (identifierMethodNameRef() << (identifierRef() << frm->availableMethodName(field)->value()));
                
            test    << (unaryTestStatementRef() << type
                                                << availableFieldCall);
        }

        suite << test;
    } 
    
    if (structure->isInitializable() && !structure->immutable())
    {
        TestSPtr test = testRef();
        test << TestName("isInitialized");
        
        test << (variableDeclarationStatementRef() << class_
                                                   << structure1->variable());
        
        MethodCallExpressionSPtr isInitializedCall = methodCallExpressionRef()
            << structure1
            << (identifierMethodNameRef() << (identifierRef() << "isInitialized"));
            
        if (!structure->isOptional())
        {
            test    << (unaryTestStatementRef() << UnaryTestStatement::EType::isFalse()
                                                << isInitializedCall);
        }
            
        std::vector<FieldSPtr> fields = structure->combinedFields();
        for (std::vector<FieldSPtr>::iterator it = fields.begin(); it != fields.end(); ++it)
        {
            const FieldSPtr& field = *it;
            if (field->defaultValue())
                continue;
                
            ConstructorCallExpressionSPtr constructor = constructorCallExpressionRef()
                << (identifierClassNameRef() << (identifierRef() << impl->cppType(field->type())->name()->value()));
            
            MethodCallExpressionSPtr setFieldCall = methodCallExpressionRef()
                << structure1
                << (identifierMethodNameRef() << (identifierRef() << frm->setMethodName(field)->value()))
                << (expressionListRef() << constructor);
                
            test << (expressionStatementRef() << setFieldCall);
        }
        
        test    << (unaryTestStatementRef() << UnaryTestStatement::EType::isTrue()
                                            << isInitializedCall);
        
        suite << test;
    }
    
    if (structure->isInitializable() && structure->immutable() && !structure->isInitializeAlwaysTrue())
    {
        TestSPtr test = testRef();
        test << TestName("negativeBuild");
        
        VariableExpressionSPtr builder1 = variableExpressionRef()
            << (localVariableNameRef() << "builder");

        test << (variableDeclarationStatementRef() << builderClass
                                                   << builder1->variable());
                                                   
        MethodCallExpressionSPtr build = methodCallExpressionRef()
                << builder1
                << CppBuilder::methodNameBuild();
                
        test << (throwTestStatementRef() << build
                                         << BoostException::assertClass());
                                         
        MethodCallExpressionSPtr finalize = methodCallExpressionRef()
                << builder1
                << CppBuilder::methodNameFinalize();
                
        test << (throwTestStatementRef() << finalize
                                         << BoostException::assertClass());

        suite << test;
    }
    
    NamerConfigurationSPtr nc = boost::make_shared<NamerConfiguration>();
    
    ImplementerStream stream(impl->mConfiguration, nc, frm->mpFormatterConfiguration, mpAlignerConfiguration);
    
    stream << suite;
    
    line() << stream.str();
    eol(mainStream);
}

void CppTestGenerator::generateObjectDeclaration(const ObjectSPtr& object)
{
    switch (object->runtimeObjectId().value())
    {
        case EObjectId::kSpecimen:
        {
            SpecimenSPtr specimen = boost::static_pointer_cast<Specimen>(object);
            generateSpecimenDeclaration(specimen);
            break;
        }
        case EObjectId::kStructure:
        {
            StructureSPtr structure = boost::static_pointer_cast<Structure>(object);
            generateStructureDeclaration(structure);
            break;
        }
        default:
            break;
    }
}

bool CppTestGenerator::generate()
{
    addDependency(impl->cppHeaderFileDependency(mDocument->name()->value(),
                                                mDocument->package()));
                                                
    addDependency(Dependency("gtest",
                             "gtest.h",
                             Dependency::system_type,
                             Dependency::thirdparty_level,
                             Dependency::private_section,
                             "Google Test framework"));

    addDependency(Dependency("core/boost",
                             "boost_assert_handler.h",
                             Dependency::system_type,
                             Dependency::thirdparty_level,
                             Dependency::private_section,
                             "Boost C++ core"));
                             
    includeHeaders(mainStream, Dependency::private_section);
    
    openNamespace(mainStream);
    
    const std::vector<ObjectSPtr>& objects = mDocument->objects();
    std::vector<ObjectSPtr>::const_iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
		if ((*it)->sourceId() != mDocument->mainFile()->sourceId())
			continue;

        generateObjectDeclaration(*it);
    }

    closeNamespace(mainStream);

    return serializeStreams();
}

}

