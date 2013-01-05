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

cpp::frm::ConstructorNameSPtr builderConstructorName = cpp::frm::constructorNameRef("Builder");

cpp::frm::TypeSPtr bl             = cpp::frm::typeRef() << cpp::frm::typeNameRef("bool");
cpp::frm::TypeSPtr vd             = cpp::frm::typeRef() << cpp::frm::typeNameRef("void");
cpp::frm::TypeSPtr st             = cpp::frm::typeRef() << cpp::frm::typeNameRef("size_t");
cpp::frm::TypeSPtr const_char_ptr = cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                                                        << cpp::frm::typeNameRef("char")
                                                        << cpp::frm::ETypeDecoration::pointer();
cpp::frm::TypeSPtr cloneFunction  = cpp::frm::typeRef() << cpp::frm::typeNameRef("fnClone");

cpp::frm::TypeSPtr T              = cpp::frm::typeRef() << cpp::frm::typeNameRef("T");
cpp::frm::TypeSPtr cstTRef        = cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                                                        << cpp::frm::typeNameRef("T")
                                                        << cpp::frm::ETypeDecoration::reference();
cpp::frm::TypeSPtr TPtr           = cpp::frm::typeRef() << cpp::frm::typeNameRef("T")
                                                        << cpp::frm::ETypeDecoration::pointer();

cpp::frm::TypeSPtr F              = cpp::frm::typeRef() << cpp::frm::typeNameRef("F");
cpp::frm::TypeSPtr cstFRef        = cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                                                        << cpp::frm::typeNameRef("F")
                                                        << cpp::frm::ETypeDecoration::reference();

cpp::frm::TypeSPtr builder        = cpp::frm::typeRef() << cpp::frm::typeNameRef("Builder");
cpp::frm::TypeSPtr cstBuilderRef  = cpp::frm::typeRef() << cpp::frm::ETypeDeclaration::const_()
                                                        << cpp::frm::typeNameRef("Builder")
                                                        << cpp::frm::ETypeDecoration::reference();

cpp::frm::TypeSPtr chr            = cpp::frm::typeRef() << cpp::frm::typeNameRef("char");
cpp::frm::TypeSPtr integer        = cpp::frm::typeRef() << cpp::frm::typeNameRef("int");

cpp::frm::MethodNameSPtr fnValue                  = cpp::frm::methodNameRef("value");
cpp::frm::MethodNameSPtr fnShortName              = cpp::frm::methodNameRef("shortName");
cpp::frm::MethodNameSPtr fnBuild                  = cpp::frm::methodNameRef("build");
cpp::frm::MethodNameSPtr fnClone                  = cpp::frm::methodNameRef("clone");
cpp::frm::MethodNameSPtr fnCreate                 = cpp::frm::methodNameRef("create");
cpp::frm::MethodNameSPtr fnFinalize               = cpp::frm::methodNameRef("finalize");

cpp::frm::MethodNameSPtr fnBuilder                = cpp::frm::methodNameRef("Builder");
cpp::frm::MethodNameSPtr fnDowncast               = cpp::frm::methodNameRef("downcast");
cpp::frm::MethodNameSPtr fnSharedFromThis         = cpp::frm::methodNameRef("shared_from_this");


cpp::frm::MethodNameSPtr fnIsInitialized          = cpp::frm::methodNameRef("isInitialized");
cpp::frm::MethodNameSPtr fnIsVoid                 = cpp::frm::methodNameRef("isVoid");

cpp::frm::MethodNameSPtr fnInprocId               = cpp::frm::methodNameRef("inprocId");
cpp::frm::MethodNameSPtr fnGet                    = cpp::frm::methodNameRef("get");
cpp::frm::MethodNameSPtr fnRegisterCloneFunction  = cpp::frm::methodNameRef("registerCloneFunction");
cpp::frm::MethodNameSPtr fnRegisterRelationship   = cpp::frm::methodNameRef("registerRelationship");
cpp::frm::MethodNameSPtr fnIsParent               = cpp::frm::methodNameRef("isParent");
cpp::frm::MethodNameSPtr fnIsDerivedFrom          = cpp::frm::methodNameRef("isDerivedFrom");

cpp::frm::MethodNameSPtr fnOperatorE              = cpp::frm::methodNameRef("operator=");
cpp::frm::MethodNameSPtr fnOperatorEq             = cpp::frm::methodNameRef("operator==");
cpp::frm::MethodNameSPtr fnOperatorNe             = cpp::frm::methodNameRef("operator!=");
cpp::frm::MethodNameSPtr fnOperatorLt             = cpp::frm::methodNameRef("operator<");
cpp::frm::MethodNameSPtr fnOperatorStore          = cpp::frm::methodNameRef("operator<<");
cpp::frm::MethodNameSPtr fnOperatorStoreEq        = cpp::frm::methodNameRef("operator<<=");
cpp::frm::MethodNameSPtr fnOperatorPlusEq         = cpp::frm::methodNameRef("operator+=");
cpp::frm::MethodNameSPtr fnOperatorFn             = cpp::frm::methodNameRef("operator()");
cpp::frm::MethodNameSPtr fnOperatorPlus           = cpp::frm::methodNameRef("operator+");
cpp::frm::MethodNameSPtr fnOperatorMinus          = cpp::frm::methodNameRef("operator-");

cpp::frm::MethodNameSPtr fnFunctionalOperatorEq   = cpp::frm::methodNameRef("isEqual");
cpp::frm::MethodNameSPtr fnFunctionalOperatorLt   = cpp::frm::methodNameRef("lessThan");

cpp::frm::MethodNameSPtr fnUpdate                 = cpp::frm::methodNameRef("update");
cpp::frm::MethodNameSPtr fnObtain                 = cpp::frm::methodNameRef("obtain");

cpp::frm::MethodNameSPtr fnReset                  = cpp::frm::methodNameRef("reset");
cpp::frm::MethodNameSPtr fnSet                    = cpp::frm::methodNameRef("set");
cpp::frm::MethodNameSPtr fnClear                  = cpp::frm::methodNameRef("clear");
cpp::frm::MethodNameSPtr fnTurn                   = cpp::frm::methodNameRef("turn");

cpp::frm::MethodNameSPtr fnAssemble               = cpp::frm::methodNameRef("assemble");
cpp::frm::MethodNameSPtr fnCombine                = cpp::frm::methodNameRef("combine");
cpp::frm::MethodNameSPtr fnIntersect              = cpp::frm::methodNameRef("intersect");
cpp::frm::MethodNameSPtr fnFlip                   = cpp::frm::methodNameRef("flip");

cpp::frm::MethodNameSPtr fnTest                   = cpp::frm::methodNameRef("test");
cpp::frm::MethodNameSPtr fnIsSet                  = cpp::frm::methodNameRef("isSet");
cpp::frm::MethodNameSPtr fnIsClear                = cpp::frm::methodNameRef("isClear");

cpp::frm::NamespaceNameSPtr nsBuilder = cpp::frm::namespaceNameRef("Builder");

cpp::frm::VariableNameSPtr bits     = cpp::frm::variableNameRef("bits");
cpp::frm::VariableNameSPtr child    = cpp::frm::variableNameRef("child");
cpp::frm::VariableNameSPtr function = cpp::frm::variableNameRef("function");
cpp::frm::VariableNameSPtr mask     = cpp::frm::variableNameRef("mask");
cpp::frm::VariableNameSPtr object   = cpp::frm::variableNameRef("object");
cpp::frm::VariableNameSPtr object1  = cpp::frm::variableNameRef("object1");
cpp::frm::VariableNameSPtr object2  = cpp::frm::variableNameRef("object2");
cpp::frm::VariableNameSPtr parent   = cpp::frm::variableNameRef("parent");
cpp::frm::VariableNameSPtr rValue   = cpp::frm::variableNameRef("rValue");
cpp::frm::VariableNameSPtr value    = cpp::frm::variableNameRef("value");


Aligner::Aligner(const AlignerConfigurationSPtr& pConfiguration)
        : mConfiguration(pConfiguration)
{
}

Aligner::~Aligner()
{
}

}
