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

FunctionName fnValue                  = *CreateFunctionName("value");
FunctionName fnShortName              = *CreateFunctionName("shortName");
FunctionName fnBuild                  = *CreateFunctionName("build");
FunctionName fnClone                  = *CreateFunctionName("clone");
FunctionName fnCreate                 = *CreateFunctionName("create");
FunctionName fnFinalize               = *CreateFunctionName("finalize");

FunctionName fnBuilder                = *CreateFunctionName("Builder");
FunctionName fnDowncast               = *CreateFunctionName("downcast");
FunctionName fnSharedFromThis         = *CreateFunctionName("shared_from_this");


FunctionName fnIsInitialized          = *CreateFunctionName("isInitialized");
FunctionName fnIsVoid                 = *CreateFunctionName("isVoid");

FunctionName fnInprocId               = *CreateFunctionName("inprocId");
FunctionName fnGet                    = *CreateFunctionName("get");
FunctionName fnRegisterCloneFunction  = *CreateFunctionName("registerCloneFunction");
FunctionName fnRegisterRelationship   = *CreateFunctionName("registerRelationship");
FunctionName fnIsParent               = *CreateFunctionName("isParent");
FunctionName fnIsDerivedFrom          = *CreateFunctionName("isDerivedFrom");

FunctionName fnOperatorE              = *CreateFunctionName("operator=");
FunctionName fnOperatorEq             = *CreateFunctionName("operator==");
FunctionName fnOperatorNe             = *CreateFunctionName("operator!=");
FunctionName fnOperatorLt             = *CreateFunctionName("operator<");
FunctionName fnOperatorStore          = *CreateFunctionName("operator<<");
FunctionName fnOperatorStoreEq        = *CreateFunctionName("operator<<=");
FunctionName fnOperatorPlusEq         = *CreateFunctionName("operator+=");
FunctionName fnOperatorFn             = *CreateFunctionName("operator()");

FunctionName fnFunctionalOperatorEq   = *CreateFunctionName("isEqual");
FunctionName fnFunctionalOperatorLt   = *CreateFunctionName("lessThan");

FunctionName fnUpdate                 = *CreateFunctionName("update");
FunctionName fnObtain                 = *CreateFunctionName("obtain");

FunctionName fnReset                  = *CreateFunctionName("reset");
FunctionName fnSet                    = *CreateFunctionName("set");
FunctionName fnClear                  = *CreateFunctionName("clear");
FunctionName fnTurn                   = *CreateFunctionName("turn");

FunctionName fnAssemble               = *CreateFunctionName("assemble");
FunctionName fnCombine                = *CreateFunctionName("combine");
FunctionName fnIntersect              = *CreateFunctionName("intersect");
FunctionName fnFlip                   = *CreateFunctionName("flip");

FunctionName fnTest                   = *CreateFunctionName("test");
FunctionName fnIsSet                  = *CreateFunctionName("isSet");
FunctionName fnIsClear                = *CreateFunctionName("isClear");

Modifier sttc     = *CreateModifier("static");
Modifier vrtl     = *CreateModifier("virtual");
Modifier non_vrtl = *CreateModifier("/*lax*/");
Modifier expl     = *CreateModifier("explicit");

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
