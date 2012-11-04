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
#include "cpp/format/function_call.h"
#include "cpp/format/destructor.h"
#include "cpp/format/function.h"
#include "cpp/format/method.h"
#include "cpp/format/initialization.h"

#include <boost/shared_ptr.hpp>

#include <string>
#include <sstream>

namespace compil
{
extern cpp::frm::ConstructorNameSPtr builderConstructorName;

extern cpp::frm::TypeSPtr bl;
extern cpp::frm::TypeSPtr vd;
extern cpp::frm::TypeSPtr st;
extern cpp::frm::TypeSPtr const_char_ptr;
extern cpp::frm::TypeSPtr cloneFunction;

extern cpp::frm::TypeSPtr T;
extern cpp::frm::TypeSPtr cstTRef;
extern cpp::frm::TypeSPtr TPtr;

extern cpp::frm::TypeSPtr F;
extern cpp::frm::TypeSPtr cstFRef;

extern cpp::frm::TypeSPtr builder;
extern cpp::frm::TypeSPtr cstBuilderRef;
extern cpp::frm::TypeSPtr chr;
extern cpp::frm::TypeSPtr integer;

extern cpp::frm::MethodNameSPtr fnValue;
extern cpp::frm::MethodNameSPtr fnShortName;
extern cpp::frm::MethodNameSPtr fnBuild;
extern cpp::frm::MethodNameSPtr fnClone;
extern cpp::frm::MethodNameSPtr fnCreate;
extern cpp::frm::MethodNameSPtr fnFinalize;

extern cpp::frm::MethodNameSPtr fnBuilder;
extern cpp::frm::MethodNameSPtr fnDowncast;
extern cpp::frm::MethodNameSPtr fnSharedFromThis;

extern cpp::frm::MethodNameSPtr fnIsInitialized;
extern cpp::frm::MethodNameSPtr fnIsVoid;

extern cpp::frm::MethodNameSPtr fnInprocId;
extern cpp::frm::MethodNameSPtr fnGet;
extern cpp::frm::MethodNameSPtr fnRegisterCloneFunction;
extern cpp::frm::MethodNameSPtr fnRegisterRelationship;
extern cpp::frm::MethodNameSPtr fnIsParent;
extern cpp::frm::MethodNameSPtr fnIsDerivedFrom;

extern cpp::frm::MethodNameSPtr fnOperatorE;
extern cpp::frm::MethodNameSPtr fnOperatorEq;
extern cpp::frm::MethodNameSPtr fnOperatorNe;
extern cpp::frm::MethodNameSPtr fnOperatorLt;
extern cpp::frm::MethodNameSPtr fnOperatorFn;
extern cpp::frm::MethodNameSPtr fnOperatorStore;
extern cpp::frm::MethodNameSPtr fnOperatorStoreEq;
extern cpp::frm::MethodNameSPtr fnOperatorPlusEq;

extern cpp::frm::MethodNameSPtr fnFunctionalOperatorEq;
extern cpp::frm::MethodNameSPtr fnFunctionalOperatorLt;

extern cpp::frm::MethodNameSPtr fnReset;
extern cpp::frm::MethodNameSPtr fnSet;
extern cpp::frm::MethodNameSPtr fnClear;
extern cpp::frm::MethodNameSPtr fnTurn;

extern cpp::frm::MethodNameSPtr fnAssemble;
extern cpp::frm::MethodNameSPtr fnCombine;
extern cpp::frm::MethodNameSPtr fnIntersect;
extern cpp::frm::MethodNameSPtr fnFlip;

extern cpp::frm::MethodNameSPtr fnTest;
extern cpp::frm::MethodNameSPtr fnIsSet;
extern cpp::frm::MethodNameSPtr fnIsClear;

extern cpp::frm::NamespaceNameSPtr nsBuilder;

extern cpp::frm::VariableNameSPtr bits;
extern cpp::frm::VariableNameSPtr child;
extern cpp::frm::VariableNameSPtr function;
extern cpp::frm::VariableNameSPtr mask;
extern cpp::frm::VariableNameSPtr object;
extern cpp::frm::VariableNameSPtr object1;
extern cpp::frm::VariableNameSPtr object2;
extern cpp::frm::VariableNameSPtr parent;
extern cpp::frm::VariableNameSPtr rValue;
extern cpp::frm::VariableNameSPtr value;


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
