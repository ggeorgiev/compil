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

Declaration cst = *CreateDeclaration("const");

Decoration ref   = *CreateDecoration("&");
Decoration ptr   = *CreateDecoration("*");
Decoration tilde = *CreateDecoration("~");

DecoratedType bl             = *CreateDecoratedType(*CreateSimpleType("bool"));
DecoratedType vd             = *CreateDecoratedType(*CreateSimpleType("void"));
DecoratedType st             = *CreateDecoratedType(*CreateSimpleType("size_t"));
DecoratedType const_char_ptr = *CreateDecoratedType(*CreateDeclaration("const"), 
                                                    *CreateSimpleType("char"),
                                                    *CreateDecoration("*"));
DecoratedType cloneFunction  = *CreateDecoratedType(*CreateSimpleType("fnClone"));

DecoratedType cstTRef        = *CreateDecoratedType(cst, *CreateSimpleType("T"), ref);
DecoratedType TPtr           = *CreateDecoratedType(*CreateSimpleType("T"), ptr);

MethodName fnValue                  = *methodNameRef("value");
MethodName fnShortName              = *methodNameRef("shortName");
MethodName fnBuild                  = *methodNameRef("build");
MethodName fnClone                  = *methodNameRef("clone");
MethodName fnCreate                 = *methodNameRef("create");
MethodName fnFinalize               = *methodNameRef("finalize");

MethodName fnBuilder                = *methodNameRef("Builder");
MethodName fnDowncast               = *methodNameRef("downcast");
MethodName fnSharedFromThis         = *methodNameRef("shared_from_this");


MethodName fnIsInitialized          = *methodNameRef("isInitialized");
MethodName fnIsVoid                 = *methodNameRef("isVoid");

MethodName fnInprocId               = *methodNameRef("inprocId");
MethodName fnGet                    = *methodNameRef("get");
MethodName fnRegisterCloneFunction  = *methodNameRef("registerCloneFunction");
MethodName fnRegisterRelationship   = *methodNameRef("registerRelationship");
MethodName fnIsParent               = *methodNameRef("isParent");
MethodName fnIsDerivedFrom          = *methodNameRef("isDerivedFrom");

MethodName fnOperatorE              = *methodNameRef("operator=");
MethodName fnOperatorEq             = *methodNameRef("operator==");
MethodName fnOperatorNe             = *methodNameRef("operator!=");
MethodName fnOperatorLt             = *methodNameRef("operator<");
MethodName fnOperatorStore          = *methodNameRef("operator<<");
MethodName fnOperatorStoreEq        = *methodNameRef("operator<<=");
MethodName fnOperatorPlusEq         = *methodNameRef("operator+=");
MethodName fnOperatorFn             = *methodNameRef("operator()");

MethodName fnFunctionalOperatorEq   = *methodNameRef("isEqual");
MethodName fnFunctionalOperatorLt   = *methodNameRef("lessThan");

MethodName fnUpdate                 = *methodNameRef("update");
MethodName fnObtain                 = *methodNameRef("obtain");

MethodName fnReset                  = *methodNameRef("reset");
MethodName fnSet                    = *methodNameRef("set");
MethodName fnClear                  = *methodNameRef("clear");
MethodName fnTurn                   = *methodNameRef("turn");

MethodName fnAssemble               = *methodNameRef("assemble");
MethodName fnCombine                = *methodNameRef("combine");
MethodName fnIntersect              = *methodNameRef("intersect");
MethodName fnFlip                   = *methodNameRef("flip");

MethodName fnTest                   = *methodNameRef("test");
MethodName fnIsSet                  = *methodNameRef("isSet");
MethodName fnIsClear                = *methodNameRef("isClear");

Modifier sttc     = *CreateModifier("static");
Modifier vrtl     = *CreateModifier("virtual");
Modifier non_vrtl = *CreateModifier("/*lax*/");
Modifier expl     = *CreateModifier("explicit");


NamespaceNameSPtr nsBuilder = namespaceNameRef("Builder");

SimpleType builder = *CreateSimpleType("Builder");
SimpleType chr     = *CreateSimpleType("char");


Aligner::Aligner(const AlignerConfigurationPtr& pConfiguration)
        : mpConfiguration(pConfiguration)
{
}

Aligner::~Aligner()
{
}

}
