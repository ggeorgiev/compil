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

#include "compiler/parser/type_parser-mixin.h"

namespace compil
{

bool TypeParserMixin::parseType(const ParseContextSPtr& context,
                                std::vector<PackageElementSPtr>& packageElements,
                                TokenPtr& nameToken)
{
    TokenizerPtr& tokenizer = context->tokenizer;

    nameToken = tokenizer->current();

    tokenizer->shift();
    while (tokenizer->check(Token::TYPE_DOT))
    {
        tokenizer->shift();
        if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
            return false;

        PackageElementSPtr pe = boost::make_shared<PackageElement>();
        pe->set_value(nameToken->text());

        packageElements.push_back(pe);
        nameToken = tokenizer->current();
        tokenizer->shift();
    }

    return true;
}

// returns false if the format is broken
// if it returns true the type still could be unknown
bool TypeParserMixin::parseTypeParameter(const DocumentParseContextSPtr& context,
                                         const InitTypeMethod& initTypeMethod,
                                         const std::string& defaultTypeName,
                                         std::vector<LateTypeResolveInfo>& lateTypeResolve)
{
    TokenizerPtr& tokenizer = context->tokenizer;

    TypeSPtr type;

    std::vector<PackageElementSPtr> package_elements;
    if (!tokenizer->check(Token::TYPE_ANGLE_BRACKET, "<"))
    {
        if (defaultTypeName.empty())
        {
            *context <<= errorMessage(context, Message::p_expectType)
                         << Message::Classifier("class parameter");
            return false;
        }

        StructureSPtr structure;
        if (type)
            structure = ObjectFactory::downcastStructure(type);

        if (structure)
            type = context->mDocument->findType(context->mPackage, package_elements, structure->objects(), defaultTypeName);
        else
            type = context->mDocument->findType(context->mPackage, package_elements, defaultTypeName);

        if (!type)
        {
            *context <<= errorMessage(context, Message::p_unknownClassifierType)
                         << Message::Classifier("default class parameter")
                         << Message::Type(defaultTypeName);
        }
        else
        {
            initTypeMethod(type);
        }
        return true;
    }

    tokenizer->shift();
    skipComments(context);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *context <<= errorMessage(context, Message::p_expectType)
                     << Message::Classifier("class parameter");
        return false;
    }

    TokenPtr nameToken;
    if (!parseType(context, package_elements, nameToken))
        return FieldSPtr();

    skipComments(context);

    UnaryTemplateSPtr unaryTemplate = context->mDocument->findUnfinishedUnaryTemplate(nameToken->text());
    if (unaryTemplate)
    {
        UnaryTemplateSPtr unaryTemplateClone =
            ObjectFactory::downcastUnaryTemplate(ObjectFactory::clone(unaryTemplate));

        parseTypeParameter(context,
                           boost::bind(&UnaryTemplate::set_parameterType, unaryTemplateClone, _1),
                           "",
                           lateTypeResolve);

        context->mDocument->cache(unaryTemplateClone);
        type = unaryTemplateClone;

        ReferenceSPtr reference = ObjectFactory::downcastReference(type);
        if (reference)
            reference->set_weak(false);
    }
    else
    {
        type = context->mDocument->findType(context->mPackage, package_elements, nameToken->text());
    }

    if (!tokenizer->expect(Token::TYPE_ANGLE_BRACKET, ">"))
    {
        *context <<= errorMessage(context, Message::p_expectClosingAngleBracket);
        return false;
    }

    tokenizer->shift();
    skipComments(context);

    if (type)
    {
        initTypeMethod(type);
    }
    else
    {
        LateTypeResolveInfo info;
        info.token = nameToken;
        info.classifier = "class parameter";
        info.initTypeMethod = initTypeMethod;
        lateTypeResolve.push_back(info);
    }
    return true;
}

}