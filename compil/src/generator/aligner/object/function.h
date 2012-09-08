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


#ifndef _ALIGNER_FUNCTION_H__
#define _ALIGNER_FUNCTION_H__

#include "argument.h"
#include "namespace.h"
#include "function_name.h"
#include "cast_operator.h"
#include "method_declaration.h"
#include "method_specifier.h"

#include <vector>

namespace compil
{

class Function 
{
public:
    Function();
    
    explicit Function(const FunctionNameSPtr& name);
    
    Function(const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name);
             
    Function(const FunctionNameSPtr& name, 
             const EMethodDeclaration& declaration);
             
    Function(const CastOperator& castOperator, 
             const EMethodDeclaration& declaration);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const EMethodDeclaration& declaration);
             
    Function(const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument1,
             const ArgumentSPtr& argument2);
             
    Function(const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument, 
             const EMethodDeclaration& declaration);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument, 
             const EMethodDeclaration& declaration);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument1,
             const ArgumentSPtr& argument2,
             const EMethodDeclaration& declaration);
             
    Function(const NamespaceSPtr& namesp,
             const FunctionNameSPtr& name);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const NamespaceSPtr& namesp,
             const FunctionNameSPtr& name);
             
    Function(const NamespaceSPtr& namesp, 
             const FunctionNameSPtr& name, 
             const EMethodDeclaration& declaration);
             
    Function(const NamespaceSPtr& namesp, 
             const CastOperator& castOperator, 
             const EMethodDeclaration& declaration);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const NamespaceSPtr& namesp, 
             const FunctionNameSPtr& name, 
             const EMethodDeclaration& declaration);
             
    Function(const NamespaceSPtr& namesp,
             const FunctionNameSPtr& name,
             const ArgumentSPtr& argument);
             
    Function(const DecoratedTypeSPtr& returnType,
             const NamespaceSPtr& namesp, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument);
             
    Function(const DecoratedTypeSPtr& returnType,
             const NamespaceSPtr& namesp,
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument1,
             const ArgumentSPtr& argument2);
             
    Function(const NamespaceSPtr& namesp, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument, 
             const EMethodDeclaration& declaration);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const NamespaceSPtr& namesp, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument, 
             const EMethodDeclaration& declaration);
             
    Function(const DecoratedTypeSPtr& returnType, 
             const NamespaceSPtr& namesp, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument1,
             const ArgumentSPtr& argument2, 
             const EMethodDeclaration& declaration);
             
    Function(const EMethodSpecifier& specifier,
             const FunctionNameSPtr& name, 
             const EMethodDeclaration& declaration);
             
    Function(const EMethodSpecifier& specifier,
             const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name);

    Function(const EMethodSpecifier& specifier,
             const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument);

    Function(const EMethodSpecifier& specifier,
             const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument,
             const EMethodDeclaration& declaration);
             
    Function(const EMethodSpecifier& specifier,
             const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument1,
             const ArgumentSPtr& argument2);
             
    Function(const EMethodSpecifier& specifier,
             const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument1,
             const ArgumentSPtr& argument2,
             const EMethodDeclaration& declaration);
             
    Function(const EMethodSpecifier& specifier,
             const DecoratedTypeSPtr& returnType,
             const NamespaceSPtr& namesp,
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument);

    Function(const EMethodSpecifier& specifier,
             const DecoratedTypeSPtr& returnType, 
             const FunctionNameSPtr& name, 
             const EMethodDeclaration& declaration);
             
    Function(const EMethodSpecifier& specifier,
             const FunctionNameSPtr& name, 
             const ArgumentSPtr& argument);
    
    Function& operator <<(const ArgumentSPtr& argument);

    EMethodSpecifier mSpecifier;
    DecoratedTypeSPtr mReturnType;
    NamespaceSPtr mNamespace;
    FunctionNameSPtr mName;
    CastOperator mCastOperator;
    std::vector<ArgumentSPtr> mvArgument;
    EMethodDeclaration mDeclaration;
};

}
#endif
