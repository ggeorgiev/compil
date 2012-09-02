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

#include "function.h"

namespace compil
{

Function::Function()
{
}

Function::Function(const FunctionNameSPtr& name)
    : mName(name)
{
}

Function::Function(const DecoratedType& returnType,
                   const FunctionNameSPtr& name)
    : mReturnType(returnType), mName(name)
{
}

Function::Function(const FunctionNameSPtr& name,
                   const Declaration& declaration)
    : mName(name), mDeclaration(declaration)
{
}

Function::Function(const CastOperator& castOperator, 
                   const Declaration& declaration)
    : mCastOperator(castOperator), mDeclaration(declaration)
{
}

Function::Function(const DecoratedType& returnType,
                   const FunctionNameSPtr& name, 
                   const Declaration& declaration)
    : mReturnType(returnType), mName(name), mDeclaration(declaration)
{
}

Function::Function(const FunctionNameSPtr& name,
                   const Argument& argument)
    : mName(name)
{
    mvArgument.push_back(argument);
}

Function::Function(const DecoratedType& returnType,
                   const FunctionNameSPtr& name,
                   const Argument& argument)
    : mReturnType(returnType), mName(name)
{
    mvArgument.push_back(argument);
}

Function::Function(const DecoratedType& returnType,
                   const FunctionNameSPtr& name,
                   const Argument& argument1,
                   const Argument& argument2)
    : mReturnType(returnType), mName(name)
{
    mvArgument.push_back(argument1);
    mvArgument.push_back(argument2);
}

Function::Function(const FunctionNameSPtr& name,
                   const Argument& argument,
                   const Declaration& declaration)
    : mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument);
}

Function::Function(const DecoratedType& returnType,
                   const FunctionNameSPtr& name,
                   const Argument& argument,
                   const Declaration& declaration)
    : mReturnType(returnType), mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument);
}

Function::Function(const DecoratedType& returnType,
                   const FunctionNameSPtr& name,
                   const Argument& argument1,
                   const Argument& argument2,
                   const Declaration& declaration)
    : mReturnType(returnType), mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument1);
    mvArgument.push_back(argument2);
}

Function::Function(const NamespaceSPtr& namesp,
                   const FunctionNameSPtr& name,
                   const Declaration& declaration)
    : mNamespace(namesp), mName(name), mDeclaration(declaration)
{
}

Function::Function(const NamespaceSPtr& namesp,
                   const CastOperator& castOperator,
                   const Declaration& declaration)
    : mNamespace(namesp), mCastOperator(castOperator), mDeclaration(declaration)
{
}

Function::Function(const DecoratedType& returnType,
                   const NamespaceSPtr& namesp,
                   const FunctionNameSPtr& name,
                   const Declaration& declaration)
    : mReturnType(returnType), mNamespace(namesp), mName(name), mDeclaration(declaration)
{
}

Function::Function(const NamespaceSPtr& namesp, 
                   const FunctionNameSPtr& name)
    : mNamespace(namesp), mName(name)
{
}

Function::Function(const DecoratedType& returnType,
                   const NamespaceSPtr& namesp, 
                   const FunctionNameSPtr& name)
    : mReturnType(returnType), mNamespace(namesp), mName(name)
{
}

Function::Function(const NamespaceSPtr& namesp,
                   const FunctionNameSPtr& name,
                   const Argument& argument)
    : mNamespace(namesp), mName(name)
{
    mvArgument.push_back(argument);
}

Function::Function(const DecoratedType& returnType,
                   const NamespaceSPtr& namesp, 
                   const FunctionNameSPtr& name,
                   const Argument& argument)
    : mReturnType(returnType), mNamespace(namesp), mName(name)
{
    mvArgument.push_back(argument);
}


Function::Function(const DecoratedType& returnType,
                   const NamespaceSPtr& namesp,
                   const FunctionNameSPtr& name, 
                   const Argument& argument1,
                   const Argument& argument2)
    : mReturnType(returnType), mNamespace(namesp), mName(name)
{
    mvArgument.push_back(argument1);
    mvArgument.push_back(argument2);
}

Function::Function(const NamespaceSPtr& namesp, 
                   const FunctionNameSPtr& name, 
                   const Argument& argument, 
                   const Declaration& declaration)
    : mNamespace(namesp), mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument);
}

Function::Function(const DecoratedType& returnType,
                   const NamespaceSPtr& namesp, 
                   const FunctionNameSPtr& name, 
                   const Argument& argument, 
                   const Declaration& declaration)
    : mReturnType(returnType), mNamespace(namesp), mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument);
}

Function::Function(const DecoratedType& returnType,
                   const NamespaceSPtr& namesp,
                   const FunctionNameSPtr& name, 
                   const Argument& argument1, 
                   const Argument& argument2, 
                   const Declaration& declaration)
    : mReturnType(returnType), mNamespace(namesp), mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument1);
    mvArgument.push_back(argument2);
}

Function::Function(const EMethodSpecifier& specifier,
                   const FunctionNameSPtr& name, 
                   const Declaration& declaration)
    : mSpecifier(specifier), mName(name), mDeclaration(declaration)
{
}

Function::Function(const EMethodSpecifier& specifier,
                   const DecoratedType& returnType, 
                   const FunctionNameSPtr& name, 
                   const Argument& argument)
    : mSpecifier(specifier), mReturnType(returnType), mName(name)
{
    mvArgument.push_back(argument);
}

Function::Function(const EMethodSpecifier& specifier,
                   const DecoratedType& returnType, 
                   const FunctionNameSPtr& name, 
                   const Argument& argument,
                   const Declaration& declaration)
    : mSpecifier(specifier), mReturnType(returnType), mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument);
}

Function::Function(const EMethodSpecifier& specifier,
                   const DecoratedType& returnType,
                   const FunctionNameSPtr& name, 
                   const Argument& argument1,
                   const Argument& argument2)
    : mSpecifier(specifier), mReturnType(returnType), mName(name)
{
    mvArgument.push_back(argument1);
    mvArgument.push_back(argument2);
}

Function::Function(const EMethodSpecifier& specifier,
                   const DecoratedType& returnType, 
                   const FunctionNameSPtr& name, 
                   const Argument& argument1,
                   const Argument& argument2,
                   const Declaration& declaration)
    : mSpecifier(specifier), mReturnType(returnType), mName(name), mDeclaration(declaration)
{
    mvArgument.push_back(argument1);
    mvArgument.push_back(argument2);
}

Function::Function(const EMethodSpecifier& specifier,
                   const DecoratedType& returnType,
                   const NamespaceSPtr& namesp,
                   const FunctionNameSPtr& name, 
                   const Argument& argument)
    : mSpecifier(specifier), mReturnType(returnType), mNamespace(namesp), mName(name)
{
    mvArgument.push_back(argument);
}

Function::Function(const EMethodSpecifier& specifier,
                   const DecoratedType& returnType, 
                   const FunctionNameSPtr& name)
    : mSpecifier(specifier), mReturnType(returnType), mName(name)
{
}

Function::Function(const EMethodSpecifier& specifier,
                   const DecoratedType& returnType, 
                   const FunctionNameSPtr& name, 
                   const Declaration& declaration)
    : mSpecifier(specifier), mReturnType(returnType), mName(name), mDeclaration(declaration)
{
}

Function::Function(const EMethodSpecifier& specifier,
                   const FunctionNameSPtr& name,
                   const Argument& argument)
    : mSpecifier(specifier), mName(name)
{
    mvArgument.push_back(argument);
}

Function& Function::operator <<(const Argument& argument)
{
    mvArgument.push_back(argument);
    return *this;
}

}
