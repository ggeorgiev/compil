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

#include "aligner.h"

namespace compil
{

ConstructorNameSPtr builderConstructorName = constructorNameRef("Builder");

DecoratedTypeSPtr bl             = decoratedTypeRef() << (simpleTypeRef() << "bool");
DecoratedTypeSPtr vd             = decoratedTypeRef() << (simpleTypeRef() << "void");
DecoratedTypeSPtr st             = decoratedTypeRef() << (simpleTypeRef() << "size_t");
DecoratedTypeSPtr const_char_ptr = decoratedTypeRef() << ETypeDeclaration::const_()
                                                      << (simpleTypeRef() << "char")
                                                      << ETypeDecoration::pointer();
DecoratedTypeSPtr cloneFunction  = decoratedTypeRef() << (simpleTypeRef() << "fnClone");

DecoratedTypeSPtr cstTRef        = decoratedTypeRef() << ETypeDeclaration::const_()
                                                      << (simpleTypeRef() << "T")
                                                      << ETypeDecoration::reference();
DecoratedTypeSPtr TPtr           = decoratedTypeRef() << (simpleTypeRef() << "T")
                                                      << ETypeDecoration::pointer();

MethodNameSPtr fnValue                  = methodNameRef("value");
MethodNameSPtr fnShortName              = methodNameRef("shortName");
MethodNameSPtr fnBuild                  = methodNameRef("build");
MethodNameSPtr fnClone                  = methodNameRef("clone");
MethodNameSPtr fnCreate                 = methodNameRef("create");
MethodNameSPtr fnFinalize               = methodNameRef("finalize");

MethodNameSPtr fnBuilder                = methodNameRef("Builder");
MethodNameSPtr fnDowncast               = methodNameRef("downcast");
MethodNameSPtr fnSharedFromThis         = methodNameRef("shared_from_this");


MethodNameSPtr fnIsInitialized          = methodNameRef("isInitialized");
MethodNameSPtr fnIsVoid                 = methodNameRef("isVoid");

MethodNameSPtr fnInprocId               = methodNameRef("inprocId");
MethodNameSPtr fnGet                    = methodNameRef("get");
MethodNameSPtr fnRegisterCloneFunction  = methodNameRef("registerCloneFunction");
MethodNameSPtr fnRegisterRelationship   = methodNameRef("registerRelationship");
MethodNameSPtr fnIsParent               = methodNameRef("isParent");
MethodNameSPtr fnIsDerivedFrom          = methodNameRef("isDerivedFrom");

MethodNameSPtr fnOperatorE              = methodNameRef("operator=");
MethodNameSPtr fnOperatorEq             = methodNameRef("operator==");
MethodNameSPtr fnOperatorNe             = methodNameRef("operator!=");
MethodNameSPtr fnOperatorLt             = methodNameRef("operator<");
MethodNameSPtr fnOperatorStore          = methodNameRef("operator<<");
MethodNameSPtr fnOperatorStoreEq        = methodNameRef("operator<<=");
MethodNameSPtr fnOperatorPlusEq         = methodNameRef("operator+=");
MethodNameSPtr fnOperatorFn             = methodNameRef("operator()");

MethodNameSPtr fnFunctionalOperatorEq   = methodNameRef("isEqual");
MethodNameSPtr fnFunctionalOperatorLt   = methodNameRef("lessThan");

MethodNameSPtr fnUpdate                 = methodNameRef("update");
MethodNameSPtr fnObtain                 = methodNameRef("obtain");

MethodNameSPtr fnReset                  = methodNameRef("reset");
MethodNameSPtr fnSet                    = methodNameRef("set");
MethodNameSPtr fnClear                  = methodNameRef("clear");
MethodNameSPtr fnTurn                   = methodNameRef("turn");

MethodNameSPtr fnAssemble               = methodNameRef("assemble");
MethodNameSPtr fnCombine                = methodNameRef("combine");
MethodNameSPtr fnIntersect              = methodNameRef("intersect");
MethodNameSPtr fnFlip                   = methodNameRef("flip");

MethodNameSPtr fnTest                   = methodNameRef("test");
MethodNameSPtr fnIsSet                  = methodNameRef("isSet");
MethodNameSPtr fnIsClear                = methodNameRef("isClear");

NamespaceNameSPtr nsBuilder = namespaceNameRef("Builder");

SimpleTypeSPtr builder = simpleTypeRef() << "Builder";
SimpleTypeSPtr chr     = simpleTypeRef() << "char";

VariableNameSPtr bits = variableNameRef("bits");
VariableNameSPtr child = variableNameRef("child");
VariableNameSPtr function = variableNameRef("function");
VariableNameSPtr mask = variableNameRef("mask");
VariableNameSPtr object = variableNameRef("object");
VariableNameSPtr object1 = variableNameRef("object1");
VariableNameSPtr object2 = variableNameRef("object2");
VariableNameSPtr parent = variableNameRef("parent");
VariableNameSPtr rValue = variableNameRef("rValue");
VariableNameSPtr value = variableNameRef("value");


Aligner::Aligner(const AlignerConfigurationPtr& pConfiguration)
        : mpConfiguration(pConfiguration)
{
}

Aligner::~Aligner()
{
}

}
