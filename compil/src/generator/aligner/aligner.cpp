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

FunctionName fnValue                  = *functionNameRef("value");
FunctionName fnShortName              = *functionNameRef("shortName");
FunctionName fnBuild                  = *functionNameRef("build");
FunctionName fnClone                  = *functionNameRef("clone");
FunctionName fnCreate                 = *functionNameRef("create");
FunctionName fnFinalize               = *functionNameRef("finalize");

FunctionName fnBuilder                = *functionNameRef("Builder");
FunctionName fnDowncast               = *functionNameRef("downcast");
FunctionName fnSharedFromThis         = *functionNameRef("shared_from_this");


FunctionName fnIsInitialized          = *functionNameRef("isInitialized");
FunctionName fnIsVoid                 = *functionNameRef("isVoid");

FunctionName fnInprocId               = *functionNameRef("inprocId");
FunctionName fnGet                    = *functionNameRef("get");
FunctionName fnRegisterCloneFunction  = *functionNameRef("registerCloneFunction");
FunctionName fnRegisterRelationship   = *functionNameRef("registerRelationship");
FunctionName fnIsParent               = *functionNameRef("isParent");
FunctionName fnIsDerivedFrom          = *functionNameRef("isDerivedFrom");

FunctionName fnOperatorE              = *functionNameRef("operator=");
FunctionName fnOperatorEq             = *functionNameRef("operator==");
FunctionName fnOperatorNe             = *functionNameRef("operator!=");
FunctionName fnOperatorLt             = *functionNameRef("operator<");
FunctionName fnOperatorStore          = *functionNameRef("operator<<");
FunctionName fnOperatorStoreEq        = *functionNameRef("operator<<=");
FunctionName fnOperatorPlusEq         = *functionNameRef("operator+=");
FunctionName fnOperatorFn             = *functionNameRef("operator()");

FunctionName fnFunctionalOperatorEq   = *functionNameRef("isEqual");
FunctionName fnFunctionalOperatorLt   = *functionNameRef("lessThan");

FunctionName fnUpdate                 = *functionNameRef("update");
FunctionName fnObtain                 = *functionNameRef("obtain");

FunctionName fnReset                  = *functionNameRef("reset");
FunctionName fnSet                    = *functionNameRef("set");
FunctionName fnClear                  = *functionNameRef("clear");
FunctionName fnTurn                   = *functionNameRef("turn");

FunctionName fnAssemble               = *functionNameRef("assemble");
FunctionName fnCombine                = *functionNameRef("combine");
FunctionName fnIntersect              = *functionNameRef("intersect");
FunctionName fnFlip                   = *functionNameRef("flip");

FunctionName fnTest                   = *functionNameRef("test");
FunctionName fnIsSet                  = *functionNameRef("isSet");
FunctionName fnIsClear                = *functionNameRef("isClear");

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
