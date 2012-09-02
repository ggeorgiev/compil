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


#ifndef _ALIGNER_H__
#define _ALIGNER_H__

#include "aligner_configuration.h"

#include "argument.h"
#include "cast_operator.h"
#include "constructor.h"
#include "declaration.h"
#include "decorated_type.h"
#include "destructor.h"
#include "decoration.h"
#include "function_call.h"
#include "function.h"
#include "method_name.h"
#include "initialization.h"
#include "simple_type.h"

#include <boost/shared_ptr.hpp>

#include <string>
#include <sstream>

namespace compil
{


extern Declaration cst;

extern Decoration ref;
extern Decoration ptr;
extern Decoration tilde;

extern DecoratedType bl;
extern DecoratedType vd;
extern DecoratedType st;
extern DecoratedType const_char_ptr;
extern DecoratedType cloneFunction;

extern DecoratedType cstTRef;
extern DecoratedType TPtr;

extern MethodName fnValue;
extern MethodName fnShortName;
extern MethodName fnBuild;
extern MethodName fnClone;
extern MethodName fnCreate;
extern MethodName fnFinalize;

extern MethodName fnBuilder;
extern MethodName fnDowncast;
extern MethodName fnSharedFromThis;

extern MethodName fnIsInitialized;
extern MethodName fnIsVoid;

extern MethodName fnInprocId;
extern MethodName fnGet;
extern MethodName fnRegisterCloneFunction;
extern MethodName fnRegisterRelationship;
extern MethodName fnIsParent;
extern MethodName fnIsDerivedFrom;

extern MethodName fnOperatorE;
extern MethodName fnOperatorEq;
extern MethodName fnOperatorNe;
extern MethodName fnOperatorLt;
extern MethodName fnOperatorFn;
extern MethodName fnOperatorStore;
extern MethodName fnOperatorStoreEq;
extern MethodName fnOperatorPlusEq;

extern MethodName fnFunctionalOperatorEq;
extern MethodName fnFunctionalOperatorLt;

extern MethodName fnReset;
extern MethodName fnSet;
extern MethodName fnClear;
extern MethodName fnTurn;

extern MethodName fnAssemble;
extern MethodName fnCombine;
extern MethodName fnIntersect;
extern MethodName fnFlip;

extern MethodName fnTest;
extern MethodName fnIsSet;
extern MethodName fnIsClear;

extern Modifier sttc;
extern Modifier vrtl;
extern Modifier non_vrtl;
extern Modifier expl;

extern NamespaceNameSPtr nsBuilder;

extern SimpleType builder;
extern SimpleType chr;


class Aligner
{
public:
    // optional space between function/method name and the opening bracket
    class FunctionSpace
    {
    };
    
    // optional space or new line between function/method type and name 
    // when the function/method is declared
    class FunctionDefinitionTypeSpace
    {
    };

    typedef boost::shared_ptr<std::ostringstream> OSStreamPtr;

    Aligner(const AlignerConfigurationPtr& pConfig);
    virtual ~Aligner();

    virtual std::string str(int indent) const = 0;

    AlignerConfigurationPtr mpConfiguration;
};

}
#endif
