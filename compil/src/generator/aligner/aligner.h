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

#include "cpp/format/argument.h"
#include "cpp/format/cast_operator.h"
#include "cpp/format/constructor.h"
#include "cpp/format/function.h"
#include "cpp/format/method.h"
#include "cpp/format/initialization.h"

#include "decorated_type.h"
#include "destructor.h"
#include "function_call.h"
#include "method_declaration.h"
#include "method_name.h"
#include "simple_type.h"

#include <boost/shared_ptr.hpp>

#include <string>
#include <sstream>

namespace compil
{
extern cpp::frm::ConstructorNameSPtr builderConstructorName;

extern DecoratedTypeSPtr bl;
extern DecoratedTypeSPtr vd;
extern DecoratedTypeSPtr st;
extern DecoratedTypeSPtr const_char_ptr;
extern DecoratedTypeSPtr cloneFunction;

extern DecoratedTypeSPtr cstTRef;
extern DecoratedTypeSPtr TPtr;

extern MethodNameSPtr fnValue;
extern MethodNameSPtr fnShortName;
extern MethodNameSPtr fnBuild;
extern MethodNameSPtr fnClone;
extern MethodNameSPtr fnCreate;
extern MethodNameSPtr fnFinalize;

extern MethodNameSPtr fnBuilder;
extern MethodNameSPtr fnDowncast;
extern MethodNameSPtr fnSharedFromThis;

extern MethodNameSPtr fnIsInitialized;
extern MethodNameSPtr fnIsVoid;

extern MethodNameSPtr fnInprocId;
extern MethodNameSPtr fnGet;
extern MethodNameSPtr fnRegisterCloneFunction;
extern MethodNameSPtr fnRegisterRelationship;
extern MethodNameSPtr fnIsParent;
extern MethodNameSPtr fnIsDerivedFrom;

extern MethodNameSPtr fnOperatorE;
extern MethodNameSPtr fnOperatorEq;
extern MethodNameSPtr fnOperatorNe;
extern MethodNameSPtr fnOperatorLt;
extern MethodNameSPtr fnOperatorFn;
extern MethodNameSPtr fnOperatorStore;
extern MethodNameSPtr fnOperatorStoreEq;
extern MethodNameSPtr fnOperatorPlusEq;

extern MethodNameSPtr fnFunctionalOperatorEq;
extern MethodNameSPtr fnFunctionalOperatorLt;

extern MethodNameSPtr fnReset;
extern MethodNameSPtr fnSet;
extern MethodNameSPtr fnClear;
extern MethodNameSPtr fnTurn;

extern MethodNameSPtr fnAssemble;
extern MethodNameSPtr fnCombine;
extern MethodNameSPtr fnIntersect;
extern MethodNameSPtr fnFlip;

extern MethodNameSPtr fnTest;
extern MethodNameSPtr fnIsSet;
extern MethodNameSPtr fnIsClear;

extern NamespaceNameSPtr nsBuilder;

extern SimpleTypeSPtr builder;
extern SimpleTypeSPtr chr;
extern SimpleTypeSPtr integer;

extern VariableNameSPtr bits;
extern VariableNameSPtr child;
extern VariableNameSPtr function;
extern VariableNameSPtr mask;
extern VariableNameSPtr object;
extern VariableNameSPtr object1;
extern VariableNameSPtr object2;
extern VariableNameSPtr parent;
extern VariableNameSPtr rValue;
extern VariableNameSPtr value;


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
