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

#include "generator/cpp/c++_flags_enumeration_generator.h"

namespace cf = cpp::frm;

namespace compil
{

const int CppFlagsEnumerationGenerator::declarationStream = 1;

CppFlagsEnumerationGenerator::CppFlagsEnumerationGenerator()
{
    for (int i = 0; i <= 1; ++i)
    {
        mStreams.push_back(boost::shared_ptr<std::stringstream>(new std::stringstream()));
        mIndent.push_back(0);
    }
}

CppFlagsEnumerationGenerator::~CppFlagsEnumerationGenerator()
{
}

bool CppFlagsEnumerationGenerator::generate()
{
    includeHeaders(declarationStream, Dependency::global_section);

    std::string guard = frm->headerGuard("core/flags_enumeration.hpp");

    line()  << "#ifndef "
            << guard;
    eol(declarationStream);
    line()  << "#define "
            << guard;
    eol(declarationStream);
    eol(declarationStream);

    includeHeaders(declarationStream, Dependency::private_section);

    cf::TypeSPtr decoratedType = T;
    cf::TypeSPtr decoratedInherit = F;
    cf::TypeSPtr decoratedInheritRef = cstFRef;

    cf::ConstructorNameSPtr class_name = cf::constructorNameRef("flags_enumeration");
    cf::VariableNameSPtr memberValue = frm->memberVariableName(value);
    cf::ArgumentSPtr argMask = cf::argumentRef() << decoratedInheritRef
                                                 << cf::variableNameRef("mask");
    cf::ArgumentSPtr argValue = cf::argumentRef() << decoratedInheritRef
                                                  << value;

    line()  << "template<class "
            << T->name()->value()
            << ", class "
            << F->name()->value()
            << ">";
    eol(declarationStream);

    line()  << "class "
            << class_name;
    openBlock(declarationStream);

    line()  << "public:";
    eol(declarationStream, -1);

    line()  << "// Default constructor - sets the value to invalid";
    eol(declarationStream);
    fdef()  << (cf::constructorRef() << class_name);
    eofd(declarationStream);
    line()  << ": "
            << (cf::initializationRef() << memberValue
                                        << cf::parameterValueRef("0"));
    openBlock(declarationStream, 1);
    closeBlock(declarationStream);
    eol(declarationStream);

    fdef()  << (cf::constructorRef() << class_name
                                     << (cf::argumentRef() << decoratedType
                                                           << value));
    eofd(declarationStream);
    line()  << ": "
            << (cf::initializationRef() << memberValue
                                        << frm->parameterValue(value));
    openBlock(declarationStream, 1);
    closeBlock(declarationStream);
    eol(declarationStream);

    fdef()  << (cf::methodRef() << decoratedType
                                << fnValue
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return "
            << memberValue
            << ";";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Resets the flags included in the mask to the state in value");
    fdef()  << (cf::methodRef() << vd
                                << fnReset
                                << argMask
                                << argValue);
    openBlock(declarationStream);
    line()  << memberValue
            << " = value.value() | (this->value() & ~mask.value());";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Sets the flags included in the mask. Equivalent to reset(mask, all).");
    fdef()  << (cf::methodRef() << vd
                                << fnSet
                                << argMask);
    openBlock(declarationStream);
    line()  << memberValue
            << " |= mask.value();";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                   "Clears the flags included in the mask. Equivalent to reset(mask, nil).");
    fdef()  << (cf::methodRef() << vd
                                << fnClear
                                << argMask);
    openBlock(declarationStream);
    line()  << memberValue
            << " &= ~mask.value();";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                   "Turns the flags included in the mask.");
    fdef()  << (cf::methodRef() << vd
                                << fnTurn
                                << argMask);
    openBlock(declarationStream);
    line()  << memberValue
            << " ^= mask.value();";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Returns assemble of the current flags with the flags from the mask to "
                  "the state in value. This is immutable version of reset.");
    fdef()  << (cf::methodRef() << decoratedInherit
                                << fnAssemble
                                << argMask
                                << argValue
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return "
            << F->name()->value()
            << "(value.value() | (this->value() & ~mask.value()));";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Returns combination of the flags included in the mask. "
                  "This is immutable version of set.");
    fdef()  << (cf::methodRef() << decoratedInherit
                                << fnCombine
                                << argMask
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return "
            << F->name()->value()
            << "(value() | mask.value());";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Returns intersection of the flags included in the mask. "
                  "This is immutable version of clear.");
    fdef()  << (cf::methodRef() << decoratedInherit
                                << fnIntersect
                                << argMask
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return "
            << F->name()->value()
            << "(value() & ~mask.value());";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Returns flipped the flags included in the mask. "
                  "This is immutable version of turn.");
    fdef()  << (cf::methodRef() << decoratedInherit
                                << fnFlip
                                << argMask
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return "
            << F->name()->value()
            << "(value() ^ mask.value());";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Tests if the flags included in the mask are the same state as state in value");
    fdef()  << (cf::methodRef() << bl
                                << fnTest
                                << argMask
                                << argValue
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return (this->value() & mask.value()) == value.value();";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Tests if the flags included in the mask are set. Equivalent to test(mask, all).");
    fdef()  << (cf::methodRef() << bl
                                << fnIsSet
                                << argMask
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return (value() & mask.value()) == mask.value();";
    closeBlock(declarationStream);
    eol(declarationStream);

    commentInLine(declarationStream,
                  "Tests if the flags included in the mask are clear. Equivalent to test(mask, nil).");
    fdef()  << (cf::methodRef() << bl
                                << fnIsClear
                                << argMask
                                << cf::EMethodDeclaration::const_());
    openBlock(declarationStream);
    line()  << "return (value() & mask.value()) == 0;";
    closeBlock(declarationStream);
    eol(declarationStream);

    line()  << "protected:";
    eol(declarationStream, -1);

    line()  << T->name()->value()
            << " "
            << memberValue
            << ";";
    eol(declarationStream);

    closeBlock(declarationStream, "};");
    eol(declarationStream);

    line()  << "#endif // "
            << guard;
    eol(declarationStream);
    eol(declarationStream);

	return serializeStreams();
}

}