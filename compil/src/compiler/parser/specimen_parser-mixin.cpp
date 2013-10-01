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

#include "compiler/parser/specimen_parser-mixin.h"

namespace compil
{

ConstantSPtr SpecimenParserMixin::parseConstant(const DocumentParseContextSPtr& context,
                                                const CommentSPtr& comment,
                                                const Type::ELiteral& literal)
{
    TokenizerPtr& tokenizer = context->tokenizer;

    BOOST_ASSERT(tokenizer->check(Token::TYPE_IDENTIFIER, "constant"));

    ConstantSPtr constant = boost::make_shared<Constant>();
    initilizeObject(context, constant);

    tokenizer->shift();
    skipComments(context);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *context <<= errorMessage(context, Message::p_expectStatementName)
                     << Message::Statement("constant");
        return ConstantSPtr();
    }

    NameSPtr name = boost::make_shared<Name>();
    initilizeObject(context, name);
    name->set_value(tokenizer->current()->text());
    constant->set_name(name);

    tokenizer->shift();
    skipComments(context);

    if (!tokenizer->expect(Token::TYPE_OPERATOR, "="))
    {
        *context <<= errorMessage(context, Message::p_expectAssignmentOperator);
        return ConstantSPtr();
    }

    tokenizer->shift();
    skipComments(context);

    Token::Type type = getTokenType(literal);
    if (!tokenizer->expect(type))
    {
        *context <<= errorMessage(context, Message::p_expectValue)
                     << Message::Statement("constant");
        return ConstantSPtr();
    }

    constant->set_value(tokenizer->current()->text());

    tokenizer->shift();
    skipComments(context);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *context <<= errorMessage(context, Message::p_expectSemicolon);
        return ConstantSPtr();
    }

    tokenizer->shift();
    return constant;
}

SpecimenSPtr SpecimenParserMixin::parseSpecimen(const DocumentParseContextSPtr& context,
                                                const CommentSPtr& comment,
                                                std::vector<LateTypeResolveInfo>& lateTypeResolve)
{
    TokenizerPtr& tokenizer = context->tokenizer;

    SpecimenSPtr specimen = boost::make_shared<Specimen>();
    specimen->set_comment(comment);
    initilizeType(context, specimen);

    tokenizer->shift();
    skipComments(context);

    if (!TypeParserMixin::parseTypeParameter(context,
                                             boost::bind(&Specimen::set_parameterType, specimen, _1),
                                             "integer",
                                             lateTypeResolve))
        return SpecimenSPtr();

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *context <<= errorMessage(context, Message::p_expectStatementName)
                     << Message::Statement("specimen");
        return SpecimenSPtr();
    }

    NameSPtr name = boost::make_shared<Name>();
    initilizeObject(context, name);
    name->set_value(tokenizer->current()->text());
    specimen->set_name(name);

    tokenizer->shift();
    skipComments(context);
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "inherit"))
    {
        tokenizer->shift();
        skipComments(context);
        if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
        {
            *context <<= errorMessage(context, Message::p_expectClassifierStatementName)
                         << Message::Classifier("base")
                         << Message::Statement("specimen");
            return SpecimenSPtr();
        }

        std::vector<PackageElementSPtr> package_elements;
        TokenPtr typeNameToken;
        if (!TypeParserMixin::parseType(context, package_elements, typeNameToken))
            return SpecimenSPtr();

        skipComments(context);

        TypeSPtr type = context->mDocument->findType(context->mPackage,
                                                     package_elements,
                                                     typeNameToken->text());
        if (!type)
        {
            *context <<= errorMessage(context, Message::p_unknownClassifierType,
                                      typeNameToken->line(), typeNameToken->beginColumn())
                         << Message::Classifier("base")
                         << Message::Type(typeNameToken->text());
            return SpecimenSPtr();
        }

        if (type->runtimeObjectId() != EObjectId::specimen())
        {
            *context <<= errorMessage(context, Message::p_expectAppropriateType,
                                      typeNameToken->line(), typeNameToken->beginColumn())
                         << Message::Classifier("base")
                         << Message::Options("specimen");
            return SpecimenSPtr();
        }

        SpecimenSPtr baseSpecimen = boost::static_pointer_cast<Specimen>(type);
        specimen->set_baseSpecimen(baseSpecimen);
    }

    if (!tokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *context <<= errorMessage(context, Message::p_expectStatementBody)
                     << Message::Statement("specimen");
        return SpecimenSPtr();
    }

    std::vector<ConstantSPtr> constants;

    tokenizer->shift();
    for (;;)
    {
        CommentSPtr bodyComment = lastComment(context);

        if (tokenizer->eot())
        {
            *context <<= errorMessage(context, Message::p_unexpectEOFInStatementBody)
                         << Message::Statement("specimen");
            return SpecimenSPtr();
        }

        if (tokenizer->check(Token::TYPE_BRACKET, "}"))
        {
            skipComments(context, bodyComment);
            break;
        }

        if (!tokenizer->check(Token::TYPE_IDENTIFIER, "constant"))
        {
            *context <<= errorMessage(context, Message::p_unknownStatment)
                         << Message::Context("specimen item")
                         << Message::Options("constant");
            recoverAfterError(context);
            return SpecimenSPtr();
        }

        ConstantSPtr constant = parseConstant(context, bodyComment, specimen->literal());
        if (!constant)
        {
            recoverAfterError(context);
            break;
        }
        constants.push_back(constant);
    }

    specimen->set_constants(constants);

    skipComments(context);
    if (!tokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *context <<= errorMessage(context, Message::p_unexpectEOFInStatementBody)
                     << Message::Statement("specimen");
        return SpecimenSPtr();
    }

    return specimen;
}

}