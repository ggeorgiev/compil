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

#include "compiler/parser.h"
#include "compiler/validator/parameter_type_validator.h"
#include "compiler/validator/structure_fields_validator.h"
#include "compiler/validator/structure_sharable_validator.h"

#include "library/compil/document.h"

#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <assert.h>

namespace compil
{

static bool bInit = false;
static ParameterTypeValidatorPtr pParameterTypeEnumerationValidator(
            new ParameterTypeValidator(EObjectId::enumeration()));
static ParameterTypeValidatorPtr pParameterTypeIdentifierValidator(
            new ParameterTypeValidator(EObjectId::identifier()));
static StructureFieldsValidatorPtr pStructureFieldsValidator(
            new StructureFieldsValidator());
static StructureSharableValidatorPtr pStructureSharableValidator(
            new StructureSharableValidator());

Parser::Parser()
{
    if (!bInit)
    {
        bInit = true;

        DocumentSPtr document = lib::compil::CompilDocument::create();
        std::vector<PackageElementSPtr> package_elements;
        pParameterTypeEnumerationValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "small"));
        pParameterTypeEnumerationValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "short"));
        pParameterTypeEnumerationValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "integer"));

        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "small"));
        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "short"));
        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "integer"));
        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "long"));
        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "byte"));
        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "word"));
        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "dword"));
        pParameterTypeIdentifierValidator->addAcceptableType(
            document->findType(PackageSPtr(), package_elements, "qword"));
    }

    addValidator(pParameterTypeEnumerationValidator);
    addValidator(pParameterTypeIdentifierValidator);
    addValidator(pStructureFieldsValidator);
    addValidator(pStructureSharableValidator);
}

Parser::Parser(const Parser& parentParser)
{
    DocumentParseContextSPtr context = boost::make_shared<DocumentParseContext>();
    *context = *boost::static_pointer_cast<DocumentParseContext>(parentParser.mContext);
    mContext = context;
}

Parser::~Parser()
{
    if (mContext && mContext->mMessageCollector)
    {
        std::vector<Message> messages = mContext->mMessageCollector->messages();
        std::vector<Message>::iterator it;
        for (it = messages.begin(); it != messages.end(); ++it)
        {
            std::string source = it->sourceId() ? it->sourceId()->value() : "compil";
            std::cout << source << ":"
                      << it->line().value() << ":"
                      << it->column().value() << " "
                      << it->text() << "\n";
        }
    }
}

EnumerationValueSPtr Parser::parseEnumerationValue(const CommentSPtr& pComment,
                                                   const std::vector<EnumerationValueSPtr>& values)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    assert(tokenizer->check(Token::TYPE_IDENTIFIER));

    TokenPtr pNameToken = tokenizer->current();

    EnumerationValueSPtr pEnumerationValue;
    tokenizer->shift();
    skipComments(mContext);

    if (tokenizer->check(Token::TYPE_OPERATOR, "="))
    {
        tokenizer->shift();
        skipComments(mContext);

        std::vector<EnumerationValueSPtr> composeValues;
        for (;;)
        {
            if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
            {
                *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                          << Message::Statement("enumeration"));
                return EnumerationValueSPtr();
            }

            EnumerationValueSPtr pFoundValue;
            BOOST_FOREACH(EnumerationValueSPtr pValue, values)
            {
                if (tokenizer->current()->text() == pValue->name()->value())
                {
                    pFoundValue = pValue;
                    break;
                }
            }

            if (!pFoundValue)
            {
                *this << (errorMessage(mContext, Message::p_expectStatementName)
                          << Message::Statement("enumeration value"));
                return EnumerationValueSPtr();
            }

            composeValues.push_back(pFoundValue);

            tokenizer->shift();
            skipComments(mContext);

            if (!tokenizer->check(Token::TYPE_BITWISE_OPERATOR, "|"))
                break;

            tokenizer->shift();
            skipComments(mContext);
        }

        ComposedEnumerationValue* pComposedEnumerationValue = new ComposedEnumerationValue();
        pEnumerationValue.reset(pComposedEnumerationValue);

        pComposedEnumerationValue->set_values(composeValues);
    }
    else
    {
        pEnumerationValue.reset(new AbsoluteEnumerationValue());
    }

    initilizeObject(mContext, pNameToken, pEnumerationValue);
    pEnumerationValue->set_comment(pComment);

    NameSPtr pName(new Name());
    initilizeObject(mContext, pNameToken, pName);
    pName->set_value(pNameToken->text());

    pEnumerationValue->set_name(pName);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return EnumerationValueSPtr();
    }

    return pEnumerationValue;
}

EnumerationSPtr Parser::parseEnumeration(const CommentSPtr& pComment,
                                         const TokenPtr& pCast,
                                         const TokenPtr& pFlags)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    EnumerationSPtr pEnumeration(new Enumeration());
    pEnumeration->set_comment(pComment);
    initilizeObject(mContext, pCast
                            ? pCast
                            : pFlags, pEnumeration);
    pEnumeration->set_package(mContext->mPackage);

    CastableType::ECast cast = CastableType::ECast::weak();
    if (pCast && pCast->text() == "strong")
        cast = CastableType::ECast::strong();
    pEnumeration->set_cast(cast);
    pEnumeration->set_flags(pFlags);

    tokenizer->shift();
    skipComments(mContext);

    if (!parseTypeParameter(boost::static_pointer_cast<DocumentParseContext>(mContext),
                            boost::bind(&Enumeration::set_parameterType, pEnumeration, _1),
                            "integer",
                            mLateTypeResolve))
        return EnumerationSPtr();

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("enumeration"));
        return EnumerationSPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(tokenizer->current()->text());

    pEnumeration->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementBody)
                    << Message::Statement("enumeration"));
        return EnumerationSPtr();
    }

    tokenizer->shift();

    std::vector<EnumerationValueSPtr> enumerationValues;

    for (;;)
    {
        if (tokenizer->eot())
        {
            *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                      << Message::Statement("enumeration"));
            return EnumerationSPtr();
        }

        CommentSPtr pEnumerationComment = lastComment(mContext);

        if (tokenizer->check(Token::TYPE_IDENTIFIER))
        {
            EnumerationValueSPtr pEnumerationValue =
                parseEnumerationValue(pEnumerationComment, enumerationValues);
            if (!pEnumerationValue)
            {
                recoverAfterError(mContext);
                break;
            }
            pEnumerationValue->set_enumeration(pEnumeration);

            enumerationValues.push_back(pEnumerationValue);
        }
        else
        {
            skipComments(mContext, pEnumerationComment);
            break;
        }

        tokenizer->shift();
    }

    if (!tokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                      << Message::Statement("enumeration"));
        return EnumerationSPtr();
    }

    int mEnumValue = pEnumeration->flags() ? 0 : 1; // 0 reserved for invalid
    BOOST_FOREACH(EnumerationValueSPtr pEnumerationValue, enumerationValues)
    {
        AbsoluteEnumerationValueSPtr pAbsoluteValue =
            ObjectFactory::downcastAbsoluteEnumerationValue(pEnumerationValue);
        if (!pAbsoluteValue) continue;
        pAbsoluteValue->set_value(mEnumValue++);
    }

    pEnumeration->set_enumerationValues(enumerationValues);

    if (!validate(pEnumeration))
        return EnumerationSPtr();

    return pEnumeration;
}

IdentifierSPtr Parser::parseIdentifier(const CommentSPtr& pComment,
                                      const TokenPtr& pCast)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    IdentifierSPtr pIdentifier(new Identifier());
    pIdentifier->set_comment(pComment);
    initilizeObject(mContext, pCast, pIdentifier);
    pIdentifier->set_package(mContext->mPackage);

    CastableType::ECast cast = CastableType::ECast::weak();
    if (pCast && pCast->text() == "strong")
        cast = CastableType::ECast::strong();
    pIdentifier->set_cast(cast);

    tokenizer->shift();
    skipComments(mContext);

    if (!parseTypeParameter(boost::static_pointer_cast<DocumentParseContext>(mContext),
                            boost::bind(&Identifier::set_parameterType, pIdentifier, _1),
                            "integer",
                            mLateTypeResolve))
        return IdentifierSPtr();

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("identifier"));
        return IdentifierSPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(tokenizer->current()->text());

    pIdentifier->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementBody)
                    << Message::Statement("identifier"));
        return IdentifierSPtr();
    }

    tokenizer->shift();
    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                    << Message::Statement("identifier"));
        return IdentifierSPtr();
    }

    if (!validate(pIdentifier))
        return IdentifierSPtr();

    return pIdentifier;
}

FilterSPtr Parser::parseFilter(const CommentSPtr& pComment,
                               const StructureSPtr& pStructure)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    FilterSPtr pFilter(new Filter());
    pFilter->set_comment(pComment);
    initilizeObject(mContext, pFilter);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("field"));
        return FilterSPtr();
    }

    FieldSPtr pField = pStructure->findField(tokenizer->current()->text());
    if (!pField)
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("field"));
        return FilterSPtr();
    }

    pFilter->set_field(pField);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER, "with"))
    {
        *this << (errorMessage(mContext, Message::p_expectKeyword)
                    << Message::Keyword("with"));
        return FilterSPtr();
    }

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("external method"));
        return FilterSPtr();
    }

    pFilter->set_method(tokenizer->current()->text());

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return FilterSPtr();
    }

    return pFilter;
}

FactorySPtr Parser::parseFactory(const CommentSPtr& pComment,
                                 const TokenPtr& pFunctionType,
                                 const TokenPtr& pFactoryType)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    FactorySPtr pFactory(new Factory());
    pFactory->set_comment(pComment);
    initilizeObject(mContext, pFunctionType
                            ? pFunctionType
                            : pFactoryType, pFactory);
    pFactory->set_package(mContext->mPackage);

    tokenizer->shift();
    skipComments(mContext);

    if (!pFactoryType)
    {
        *this << (errorMessage(mContext, Message::p_expectAppropriateType)
                      << Message::Classifier("factory")
                      << Message::Options("hierarchy, object or plugin"));
        return FactorySPtr();
    }

    pFactory->set_function(pFunctionType);

    Factory::EType type = Factory::EType::invalid();
    if (pFactoryType->text() == "hierarchy")
        type = Factory::EType::hierarchy();
    if (pFactoryType->text() == "object")
        type = Factory::EType::object();
    if (pFactoryType->text() == "plugin")
        type = Factory::EType::plugin();

    if (pFunctionType && type != Factory::EType::object())
    {
        *this << (errorMessage(mContext, Message::p_expectAppropriateType)
                      << Message::Classifier("factory")
                      << Message::Options("object"));
        return FactorySPtr();
    }

    pFactory->set_type(type);
    if (!parseTypeParameter(boost::static_pointer_cast<DocumentParseContext>(mContext),
                            boost::bind(&Factory::set_parameterType, pFactory, _1),
                            "",
                            mLateTypeResolve))
        return FactorySPtr();

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("factory"));
        return FactorySPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(tokenizer->current()->text());

    pFactory->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementBody)
                    << Message::Statement("factory"));
        return FactorySPtr();
    }

    tokenizer->shift();

    if (tokenizer->check(Token::TYPE_IDENTIFIER, "filter"))
    {
        if (pFactory->type() != Factory::EType::object())
        {
            *this << (errorMessage(mContext, Message::p_filterInNonObjectFactory));
            recoverAfterError(mContext);
            return FactorySPtr();
        }

        if    (!pFactory->parameterType().lock()
           || (!ObjectFactory::downcastStructure(pFactory->parameterType().lock())))
        {
            *this << (errorMessage(mContext, Message::p_filterInFactoryForNonStructure));
            recoverAfterError(mContext);
            return FactorySPtr();
        }
    }

    std::vector<FilterSPtr> filters;
    for (;;)
    {
        if (tokenizer->eot())
        {
            *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                        << Message::Statement("factory"));
            return FactorySPtr();
        }

        CommentSPtr pBodyComment = lastComment(mContext);

        if (!tokenizer->check(Token::TYPE_IDENTIFIER, "filter"))
        {
            skipComments(mContext, pBodyComment);
            break;
        }

        FilterSPtr pFilter = parseFilter(pBodyComment,
            ObjectFactory::downcastStructure(pFactory->parameterType().lock()));
        if (!pFilter)
        {
            recoverAfterError(mContext);
            break;
        }
        filters.push_back(pFilter);

        tokenizer->shift();
    }

    pFactory->set_filters(filters);

    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                    << Message::Statement("factory"));
        return FactorySPtr();
    }

    if (!validate(pFactory))
        return FactorySPtr();

    return pFactory;
}

// TODO: string default value multi line support
// TODO: binary default value - binaty bin[] = base64:YASfsdfj==,
//                              binaty bin[] = hex:AC2312DFF004234534
// TODO: limits - string s[10], binary bin[10]
// TODO: auto limits - string s[] = "blah", binaty bin[] = base64:YASfsdfj==

FieldSPtr Parser::parseField(const CommentSPtr& pComment,
                             const std::vector<ObjectSPtr>& structureObjects,
                             TokenPtr& pWeak)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    FieldSPtr pField(new Field());
    initilizeObject(mContext, pWeak, pField);
    pField->set_comment(pComment);

    assert(tokenizer->check(Token::TYPE_IDENTIFIER));

    std::vector<PackageElementSPtr> package_elements;
    TokenPtr pTypeNameToken;
    if (!parseType(mContext, package_elements, pTypeNameToken))
        return FieldSPtr();

    skipComments(mContext);

    TypeSPtr pType;
    UnaryTemplateSPtr pUnaryTemplate = document()->findUnfinishedUnaryTemplate(pTypeNameToken->text());
    if (pUnaryTemplate)
    {
        UnaryTemplateSPtr pUnaryTemplateClone =
            ObjectFactory::downcastUnaryTemplate(ObjectFactory::clone(pUnaryTemplate));

        if (!parseTypeParameter(boost::static_pointer_cast<DocumentParseContext>(mContext),
                                boost::bind(&UnaryTemplate::set_parameterType, pUnaryTemplateClone, _1),
                                "",
                                mLateTypeResolve))
            return FieldSPtr();

        pType = pUnaryTemplateClone;

        ReferenceSPtr pReference = ObjectFactory::downcastReference(pType);
        if (pReference)
        {
            pReference->set_weak(pWeak);
            pWeak.reset();
        }
    }
    else
    {
        pType = document()->findType(mContext->mPackage, package_elements, structureObjects, pTypeNameToken->text());
    }

    if (pType)
    {
        pField->set_type(pType);
    }
    else
    {
        LateTypeResolveInfo info;
        info.token = pTypeNameToken;
        info.classifier = "field";
        info.initTypeMethod = boost::bind(&Field::set_type, pField, _1);
        mLateTypeResolve.push_back(info);
    }

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("field"));
        return FieldSPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(tokenizer->current()->text());

    pField->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);

    if (tokenizer->check(Token::TYPE_DELIMITER, ";"))
        return pField;

    if (!tokenizer->expect(Token::TYPE_OPERATOR, "="))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolonOrAssignmentOperator);
        return FieldSPtr();
    }

    tokenizer->shift();
    skipComments(mContext);

    DefaultValueSPtr pDefaultValue(new DefaultValue());
    initilizeObject(mContext, pDefaultValue);

    if (tokenizer->check(Token::TYPE_IDENTIFIER, "optional"))
    {
        pDefaultValue->set_optional(true);
    }
    else
    {
        // TODO: LateTypeResolve need to have a late value evaluation

        Token::Type type = getTokenType(pType->literal());
        if (!tokenizer->expect(type))
        {
            *this << (errorMessage(mContext, Message::p_expectValue)
                     << Message::Statement("field"));
            return FieldSPtr();
        }

        pDefaultValue->set_value(tokenizer->current()->text());
    }
    pField->set_defaultValue(pDefaultValue);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return FieldSPtr();
    }

    return pField;
}

FieldOverrideSPtr Parser::parseFieldOverride(const FieldSPtr& pField,
                                             const StructureSPtr& pStructure,
                                             const TokenPtr& pOverride)
{
    FieldOverrideSPtr pFieldOverride(new FieldOverride());
    initilizeObject(mContext, pOverride, pFieldOverride);

    StructureSPtr pBaseStructure = pStructure->baseStructure().lock();
    if (!pBaseStructure)
    {
        // TODO:
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return FieldOverrideSPtr();
    }

    FieldSPtr pBaseField = pBaseStructure->findField(pField->name()->value());
    if (!pBaseField)
    {
        // TODO:
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return FieldOverrideSPtr();
    }

    pFieldOverride->set_overriddenField(pBaseField);
    pFieldOverride->set_field(pField);

    return pFieldOverride;
}

IdentificationSPtr Parser::parseIdentification(const CommentSPtr& pComment,
                                               const TokenPtr& pType)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    IdentificationSPtr pIdentification(new Identification());
    pIdentification->set_comment(pComment);
    initilizeObject(mContext, pType, pIdentification);

    if (!pType)
    {
        *this << (errorMessage(mContext, Message::p_expectAppropriateType)
                    << Message::Classifier("identification")
                    << Message::Options("runtime or inproc"));
        return IdentificationSPtr();
    }

    Identification::EType type = Identification::EType::invalid();
    if (pType->text() == "runtime")
        type = Identification::EType::runtime();
    if (pType->text() == "inproc")
        type = Identification::EType::inproc();

    pIdentification->set_type(type);

    assert(tokenizer->check(Token::TYPE_IDENTIFIER, "identification"));

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return IdentificationSPtr();
    }

    return pIdentification;
}

UpcopySPtr Parser::parseUpcopy(const CommentSPtr& pComment,
                               const StructureSPtr& pStructure)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    UpcopySPtr pUpcopy(new Upcopy());
    pUpcopy->set_comment(pComment);
    initilizeObject(mContext, pUpcopy);

    assert(tokenizer->check(Token::TYPE_IDENTIFIER, "upcopy"));

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER, "from"))
    {
        *this << (errorMessage(mContext, Message::p_expectKeyword)
                    << Message::Keyword("from"));
        return UpcopySPtr();
    }

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectClassifierStatementName)
                    << Message::Classifier("upcopy")
                    << Message::Statement("structure"));
        return UpcopySPtr();
    }

    std::vector<PackageElementSPtr> package_elements;
    TokenPtr pTypeNameToken;
    if (!parseType(mContext, package_elements, pTypeNameToken))
        return UpcopySPtr();

    TypeSPtr pType = document()->findType(mContext->mPackage, package_elements, pTypeNameToken->text());
    if (!pType)
    {
        *this << (errorMessage(mContext, Message::p_unknownClassifierType,
                               pTypeNameToken->line(), pTypeNameToken->beginColumn())
                    << Message::Classifier("upcopy")
                    << Message::Type(pTypeNameToken->text()));
        return UpcopySPtr();
    }

    StructureSPtr pBaseStructure = ObjectFactory::downcastStructure(pType);
    if (!pBaseStructure)
    {
        *this << (errorMessage(mContext, Message::p_expectAppropriateType,
                               pTypeNameToken->line(), pTypeNameToken->beginColumn())
                    << Message::Classifier("upcopy")
                    << Message::Options("structure"));
        return UpcopySPtr();
    }

    if (!pStructure->isRecursivelyInherit(pBaseStructure))
    {
        *this << (errorMessage(mContext, Message::p_expectAppropriateType,
                               pTypeNameToken->line(), pTypeNameToken->beginColumn())
                    << Message::Classifier("upcopy")
                    << Message::Options("base structure"));
        return UpcopySPtr();
    }

    pUpcopy->set_baseStructure(pBaseStructure);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return UpcopySPtr();
    }

    return pUpcopy;
}

OperatorSPtr Parser::parseOperator(const CommentSPtr& pComment,
                                   const TokenPtr& pOperatorDeclaration)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    OperatorSPtr pOperator(new Operator());
    pOperator->set_comment(pComment);
    initilizeObject(mContext, pOperatorDeclaration, pOperator);

    if (!pOperatorDeclaration)
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return OperatorSPtr();
    }

    EOperatorFlags flags;
    if (pOperatorDeclaration->text() == "native")
    {
        flags.set(EOperatorFlags::native());
        flags.set(EOperatorFlags::member());
    }
    else
    if (pOperatorDeclaration->text() == "function")
    {
        flags.set(EOperatorFlags::function());
        flags.set(EOperatorFlags::member());
    }
    else
    if (pOperatorDeclaration->text() == "functor")
    {
        flags.set(EOperatorFlags::functor());
        flags.set(EOperatorFlags::internal());
    }

    flags.set(EOperatorFlags::object());
    flags.set(EOperatorFlags::reference());

    pOperator->set_flags(flags);

    tokenizer->shift();
    skipComments(mContext);

    if (tokenizer->expect(Token::TYPE_RELATIONAL_OPERATOR1, "=="))
    {
        pOperator->set_action(EOperatorAction::equalTo());
    }
    else
    if (tokenizer->expect(Token::TYPE_RELATIONAL_OPERATOR2, "<"))
    {
        pOperator->set_action(EOperatorAction::lessThan());
    }
    else
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return OperatorSPtr();
    }

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return OperatorSPtr();
    }

    return pOperator;
}

StructureSPtr Parser::parseStructure(const CommentSPtr& pComment,
                                     const TokenPtr& pAbstract,
                                     const TokenPtr& pContolled,
                                     const TokenPtr& pImmutable,
                                     const TokenPtr& pPartial,
                                     const TokenPtr& pSharable,
                                     const TokenPtr& pStreamable)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    StructureSPtr pStructure(new Structure());
    pStructure->set_comment(pComment);
    initilizeObject(mContext, (pAbstract   ? pAbstract   :
                              (pContolled  ? pContolled  :
                              (pImmutable  ? pImmutable  :
                              (pPartial    ? pPartial    :
                              (pSharable   ? pSharable   :
                                             pStreamable))))), pStructure);
    pStructure->set_package(mContext->mPackage);

    pStructure->set_abstract(pAbstract);
    pStructure->set_controlled(pContolled);
    pStructure->set_immutable(pImmutable);
    pStructure->set_partial(pPartial);
    pStructure->set_sharable(pSharable);
    pStructure->set_streamable(pStreamable);

    tokenizer->shift();
    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("structure"));
        return StructureSPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(tokenizer->current()->text());

    pStructure->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);

    std::vector<ObjectSPtr> objects;

    if (tokenizer->check(Token::TYPE_IDENTIFIER, "inherit"))
    {
        tokenizer->shift();
        skipComments(mContext);
        if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
        {
            *this << (errorMessage(mContext, Message::p_expectClassifierStatementName)
                        << Message::Classifier("base")
                        << Message::Statement("structure"));
            return StructureSPtr();
        }

        std::vector<PackageElementSPtr> package_elements;
        TokenPtr pTypeNameToken;
        if (!parseType(mContext, package_elements, pTypeNameToken))
            return StructureSPtr();

        skipComments(mContext);

        TypeSPtr pType = document()->findType(mContext->mPackage, package_elements, pTypeNameToken->text());
        if (!pType)
        {
            *this << (errorMessage(mContext, Message::p_unknownClassifierType,
                                   pTypeNameToken->line(), pTypeNameToken->beginColumn())
                        << Message::Classifier("base")
                        << Message::Type(pTypeNameToken->text()));
            return StructureSPtr();
        }
        if (pType->runtimeObjectId() != EObjectId::structure())
        {
            *this << (errorMessage(mContext, Message::p_expectAppropriateType,
                                   pTypeNameToken->line(), pTypeNameToken->beginColumn())
                        << Message::Classifier("base")
                        << Message::Options("structure"));
            return StructureSPtr();
        }

        StructureSPtr pBaseStructure = boost::static_pointer_cast<Structure>(pType);
        pStructure->set_baseStructure(pBaseStructure);

        if (tokenizer->check(Token::TYPE_IDENTIFIER, "alter"))
        {
            tokenizer->shift();
            skipComments(mContext);

            for (;;)
            {
                if (tokenizer->eot())
                {
                    *this << (errorMessage(mContext, Message::p_expectStatementName)
                                << Message::Statement("field"));
                    return StructureSPtr();
                }

                if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
                {
                    *this << (errorMessage(mContext, Message::p_expectStatementName)
                                << Message::Statement("field"));
                    return StructureSPtr();
                }

                AlterSPtr pAlter(new Alter());
                initilizeObject(mContext, pAlter);

                FieldSPtr pField = pBaseStructure->findField(tokenizer->current()->text());
                if (!pField)
                {
                    *this << (errorMessage(mContext, Message::p_expectBaseStructureFieldName));
                    return StructureSPtr();
                }

                pAlter->set_field(pField);

                tokenizer->shift();
                skipComments(mContext);

                if (!tokenizer->expect(Token::TYPE_OPERATOR, "="))
                {
                    *this << errorMessage(mContext, Message::p_expectAssignmentOperator);
                    return StructureSPtr();
                }

                tokenizer->shift();
                skipComments(mContext);

                Token::Type type = getTokenType(pField->type()->literal());
                if (!tokenizer->expect(type))
                {
                    *this << (errorMessage(mContext, Message::p_expectValue)
                             << Message::Statement("field"));
                    return StructureSPtr();
                }

                DefaultValueSPtr pDefaultValue(new DefaultValue());
                initilizeObject(mContext, pDefaultValue);
                pDefaultValue->set_value(tokenizer->current()->text());

                pAlter->set_defaultValue(pDefaultValue);

                tokenizer->shift();
                skipComments(mContext);

                objects.push_back(pAlter);

                if (!tokenizer->check(Token::TYPE_DELIMITER, ","))
                    break;

                tokenizer->shift();
                skipComments(mContext);
            }
        }
    }

    if (!tokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementBody)
                    << Message::Statement("structure"));
        return StructureSPtr();
    }

    int bitmask = 0;
    tokenizer->shift();
    for (;;)
    {
        if (tokenizer->eot())
        {
            *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                        << Message::Statement("structure"));
            return StructureSPtr();
        }

        CommentSPtr pBodyComment = lastComment(mContext);

        TokenPtr pStrong;
        TokenPtr pWeak;
        TokenPtr pIdentificationType;
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "weak"))
        {
            pWeak = tokenizer->current();
            tokenizer->shift();
            skipComments(mContext);
        }
        else
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "strong"))
        {
            pStrong = tokenizer->current();
            tokenizer->shift();
            skipComments(mContext);
        }
        else
        if (   tokenizer->check(Token::TYPE_IDENTIFIER, "runtime")
            || tokenizer->check(Token::TYPE_IDENTIFIER, "inproc"))
        {
            pIdentificationType = tokenizer->current();
            tokenizer->shift();
            skipComments(mContext);
        }

        TokenPtr pFlags;
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "flags"))
        {
            pFlags = tokenizer->current();
            tokenizer->shift();
            skipComments(mContext);
        }

        TokenPtr pOverride;
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "override"))
        {
            pOverride = tokenizer->current();
            tokenizer->shift();
            skipComments(mContext);
        }

        TokenPtr pOperatorDeclaration;
        if (   tokenizer->check(Token::TYPE_IDENTIFIER, "native")
            || tokenizer->check(Token::TYPE_IDENTIFIER, "function")
            || tokenizer->check(Token::TYPE_IDENTIFIER, "functor"))
        {
            pOperatorDeclaration = tokenizer->current();
            tokenizer->shift();
            skipComments(mContext);
        }

        if (tokenizer->check(Token::TYPE_IDENTIFIER, "identification"))
        {
            IdentificationSPtr pIdentification =
                parseIdentification(pBodyComment, pIdentificationType);
            if (!pIdentification)
            {
                recoverAfterError(mContext);
                break;
            }
            pIdentificationType.reset();
            pIdentification->set_structure(pStructure);
            objects.push_back(pIdentification);
        }
        else
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "upcopy"))
        {
            UpcopySPtr pUpcopy =
                parseUpcopy(pBodyComment, pStructure);
            if (!pUpcopy)
            {
                recoverAfterError(mContext);
                break;
            }
            pUpcopy->set_structure(pStructure);
            objects.push_back(pUpcopy);
        }
        else
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "operator"))
        {
            OperatorSPtr pOperator = parseOperator(pBodyComment, pOperatorDeclaration);
            pOperatorDeclaration.reset();
            if (!pOperator)
            {
                recoverAfterError(mContext);
                break;
            }
            pOperator->set_structure(pStructure);
            objects.push_back(pOperator);
        }
        else
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "enum"))
        {
            EnumerationSPtr pEnumeration =
                parseEnumeration(pBodyComment, pStrong ? pStrong : pWeak, pFlags);
            if (!pEnumeration)
            {
                recoverAfterError(mContext);
                break;
            }
            pStrong.reset();
            pWeak.reset();
            pFlags.reset();
            pEnumeration->set_structure(pStructure);
            objects.push_back(pEnumeration);
        }
        else
        if (tokenizer->check(Token::TYPE_IDENTIFIER))
        {
            FieldSPtr pField = parseField(pBodyComment, objects, pWeak);
            if (!pField)
            {
                recoverAfterError(mContext);
                break;
            }

            pField->set_structure(pStructure);

            if (pOverride)
            {
                FieldOverrideSPtr pFieldOverride = parseFieldOverride(pField, pStructure, pOverride);
                pOverride.reset();
                if (!pFieldOverride)
                {
                    recoverAfterError(mContext);
                    break;
                }

                objects.push_back(pFieldOverride);
            }
            else
            {
                // TODO: address the limit
                pField->set_bitmask(bitmask++);
                objects.push_back(pField);
            }
        }
        else
        {
            skipComments(mContext, pBodyComment);
            break;
        }

        tokenizer->shift();

        unexpectedStatement(pStrong);
        unexpectedStatement(pWeak);
        unexpectedStatement(pFlags);
        unexpectedStatement(pOverride);
        unexpectedStatement(pOperatorDeclaration);
        unexpectedStatement(pIdentificationType);
    }

    if (!tokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                    << Message::Statement("structure"));
        return StructureSPtr();
    }

    pStructure->set_objects(objects);

    if (!validate(pStructure))
        return StructureSPtr();

    return pStructure;
}

ParameterSPtr Parser::parseParameter(const CommentSPtr& pComment)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    ParameterSPtr pParameter(new Parameter());
    initilizeObject(mContext, pParameter);
    pParameter->set_comment(pComment);

    if (!tokenizer->expect(Token::TYPE_OPERATOR_ARROW))
    {
        *this << (errorMessage(mContext, Message::p_unknownStatment)
                    << Message::Context("method")
                    << Message::Options("direction arrow (-->, <--, <->)"));
        return ParameterSPtr();
    }
    Parameter::EDirection direction = Parameter::EDirection::invalid();

    const TokenPtr& current = tokenizer->current();
    const std::string& text = current->text();
    if (text == "-->")
        direction = Parameter::EDirection::in();
    else if (text == "<--")
        direction = Parameter::EDirection::out();
    else if (text == "<->")
        direction = Parameter::EDirection::io();
    else
        assert(false && "unknown arrow");

    pParameter->set_direction(direction);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectType)
                    << Message::Classifier("parameter"));
        return ParameterSPtr();
    }

    std::vector<PackageElementSPtr> package_elements;
    TypeSPtr pType = document()->findType(mContext->mPackage,
                                          package_elements,
                                          current->text());
    if (!pType)
    {
        *this << (errorMessage(mContext, Message::p_unknownClassifierType)
                    << Message::Classifier("parameter")
                    << Message::Type(current->text()));
        return ParameterSPtr();
    }
    pParameter->set_type(pType);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("parameter"));
        return ParameterSPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(current->text());

    pParameter->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return ParameterSPtr();
    }

    return pParameter;
}

MethodSPtr Parser::parseMethod(const CommentSPtr& pComment)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    MethodSPtr pMethod(new Method());
    initilizeObject(mContext, pMethod);
    pMethod->set_comment(pComment);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("method"));
        return MethodSPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(tokenizer->current()->text());

    pMethod->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);

    if (!tokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementBody)
                    << Message::Statement("method"));
        return MethodSPtr();
    }
    tokenizer->shift();

    CommentSPtr pParameterComment = lastComment(mContext);

    std::vector<ObjectSPtr> parameters;
    while (!tokenizer->check(Token::TYPE_BRACKET, "}"))
    {
        if (tokenizer->eot())
        {
            *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                        << Message::Statement("method"));
            return MethodSPtr();
        }

        ParameterSPtr pParameter = parseParameter(pParameterComment);
        if (!pParameter)
        {
            recoverAfterError(mContext);
            break;
        }

        pParameter->set_method(pMethod);
        parameters.push_back(pParameter);

        tokenizer->shift();
    }

    pMethod->set_objects(parameters);

    if (!tokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                    << Message::Statement("method"));
        return MethodSPtr();
    }

    tokenizer->shift();

    return pMethod;
}

InterfaceSPtr Parser::parseInterface(const CommentSPtr& pComment)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    InterfaceSPtr pInterface(new Interface());
    initilizeObject(mContext, pInterface);
    pInterface->set_comment(pComment);

    tokenizer->shift();
    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_IDENTIFIER))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementName)
                    << Message::Statement("interface"));
        return InterfaceSPtr();
    }

    NameSPtr pName(new Name());
    initilizeObject(mContext, pName);
    pName->set_value(tokenizer->current()->text());

    pInterface->set_name(pName);

    tokenizer->shift();
    skipComments(mContext);
    if (!tokenizer->expect(Token::TYPE_BRACKET, "{"))
    {
        *this << (errorMessage(mContext, Message::p_expectStatementBody)
                    << Message::Statement("interface"));
        return InterfaceSPtr();
    }
    tokenizer->shift();

    std::vector<ObjectSPtr> methods;
    while (!tokenizer->check(Token::TYPE_BRACKET, "}"))
    {
        if (tokenizer->eot())
        {
            *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                    << Message::Statement("interface"));
            return InterfaceSPtr();
        }

        CommentSPtr pMethodComment = lastComment(mContext);
        if (tokenizer->check(Token::TYPE_IDENTIFIER, "method"))
        {
            MethodSPtr pMethod = parseMethod(pMethodComment);
            if (!pMethod)
            {
                recoverAfterError(mContext);
                break;
            }
            pMethod->set_interface(pInterface);
            methods.push_back(pMethod);
        }
    }

    pInterface->set_objects(methods);

    if (!tokenizer->expect(Token::TYPE_BRACKET, "}"))
    {
        *this << (errorMessage(mContext, Message::p_unexpectEOFInStatementBody)
                    << Message::Statement("interface"));
        return InterfaceSPtr();
    }

    tokenizer->shift();
    return pInterface;
}

bool Parser::unexpectedStatement(const TokenPtr& pToken)
{
    if (!pToken)
        return false;

    *this << (errorMessage(mContext, Message::p_unexpectedStatmentModificator, pToken->line(), pToken->beginColumn())
          << Message::Modificator(pToken->text()));

    recoverAfterError(mContext);

    return true;
}

void Parser::parseAnyStatement(const CommentSPtr& pComment)
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    TokenPtr pAbstract;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "abstract"))
    {
        pAbstract = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pControlled;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "controlled"))
    {
        pControlled = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pImmutable;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "immutable"))
    {
        pImmutable = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pPartial;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "partial"))
    {
        pPartial = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pSharable;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "sharable"))
    {
        pSharable = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pStreamable;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "streamable"))
    {
        pStreamable = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pCast;
    if (  tokenizer->check(Token::TYPE_IDENTIFIER, "strong")
       || tokenizer->check(Token::TYPE_IDENTIFIER, "weak"))
    {
        pCast = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pFlags;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "flags"))
    {
        pFlags = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pFunctionType;
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "function"))
    {
        pFunctionType = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    TokenPtr pFactoryType;
    if (  tokenizer->check(Token::TYPE_IDENTIFIER, "hierarchy")
       || tokenizer->check(Token::TYPE_IDENTIFIER, "object")
       || tokenizer->check(Token::TYPE_IDENTIFIER, "plugin"))
    {
        pFactoryType = tokenizer->current();
        tokenizer->shift();
        skipComments(mContext);
    }

    if (tokenizer->check(Token::TYPE_IDENTIFIER, "structure"))
    {
        StructureSPtr pStructure = parseStructure(pComment, pAbstract, pControlled, pImmutable,
                                                  pPartial, pSharable, pStreamable);
        pAbstract.reset();
        pControlled.reset();
        pImmutable.reset();
        pPartial.reset();
        pSharable.reset();
        pStreamable.reset();
        if (pStructure)
        {
            document()->addStructure(pStructure);
            lateTypeResolve(pStructure);
        }
    }
    else
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "interface"))
    {
        InterfaceSPtr pInterface = parseInterface(pComment);
        if (pInterface)
            document()->addInterface(pInterface);
    }
    else
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "enum"))
    {
        EnumerationSPtr pEnumeration = parseEnumeration(pComment, pCast, pFlags);
        pCast.reset();
        pFlags.reset();
        if (pEnumeration)
            document()->addEnumeration(pEnumeration);
    }
    else
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "specimen"))
    {
        SpecimenSPtr specimen = parseSpecimen(boost::static_pointer_cast<DocumentParseContext>(mContext),
                                              pComment,
                                              mLateTypeResolve);
        if (specimen && validate(specimen))
            document()->addSpecimen(specimen);
    }
    else
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "identifier"))
    {
        IdentifierSPtr pIdentifier = parseIdentifier(pComment, pCast);
        pCast.reset();
        if (pIdentifier)
            document()->addIdentifier(pIdentifier);
    }
    else
    if (tokenizer->check(Token::TYPE_IDENTIFIER, "factory"))
    {
        FactorySPtr pFactory = parseFactory(pComment, pFunctionType, pFactoryType);
        pFunctionType.reset();
        pFactoryType.reset();
        if (pFactory)
            document()->addFactory(pFactory);
    }
    else
    {
        *this << (errorMessage(mContext, Message::p_unknownStatment)
                << Message::Context("top")
                << Message::Options("structure, interface, enum, specimen, identifier or factory"));
        tokenizer->shift();
    }

    unexpectedStatement(pAbstract);
    unexpectedStatement(pControlled);
    unexpectedStatement(pImmutable);
    unexpectedStatement(pPartial);
    unexpectedStatement(pSharable);
    unexpectedStatement(pStreamable);
    unexpectedStatement(pCast);
    unexpectedStatement(pFlags);
    unexpectedStatement(pFunctionType);
    unexpectedStatement(pFactoryType);
}

bool Parser::parseImport()
{
    TokenizerPtr& tokenizer = mContext->tokenizer;

    ImportSPtr pImport(new Import());
    initilizeObject(mContext, pImport);

    assert(tokenizer->check(Token::TYPE_IDENTIFIER, "import"));

    TokenPtr pImportToken = tokenizer->current();

    tokenizer->shift();
    if (!tokenizer->expect(Token::TYPE_STRING_LITERAL))
    {
        *this << errorMessage(mContext, Message::p_expectImportSource);
        return false;
    }

    pImport->set_source(tokenizer->current()->text());

    tokenizer->shift();
    if (!tokenizer->expect(Token::TYPE_DELIMITER, ";"))
    {
        *this << errorMessage(mContext, Message::p_expectSemicolon);
        return false;
    }

    document()->addImport(pImport);

    if (!mContext->mSourceProvider)
    {
        *this << warningMessage(mContext, Message::p_importWithoutSourceProvider,
                                pImportToken->line(), pImportToken->beginColumn());
        return true;
    }

    SourceIdSPtr pSourceId = mContext->mSourceProvider->sourceId(mContext->mSourceId, pImport->source());
    if (!pSourceId)
    {
        *this << errorMessage(mContext, Message::p_sourceNotFound,
                              pImportToken->line(), pImportToken->beginColumn());
        return false;
    }

    ParseContext::SourceMap::iterator it = mContext->mSources->find(pSourceId->value());
    if (it != mContext->mSources->end())
    {
        SourceIdSPtr parent = mContext->mSourceId;
        while (parent)
        {
            if (parent->value() == pSourceId->value())
                return true;

            if (!parent->parent())
                break;
            parent = parent->parent();
        }
        return true;
    }

    StreamPtr pStream = mContext->mSourceProvider->openInputStream(pSourceId);
    if (!pStream)
    {
        *this << errorMessage(mContext, Message::p_openSourceFailed,
                              pImportToken->line(), pImportToken->beginColumn());
        return false;
    }

    Parser parser(*this);

    DocumentSPtr document;
    if (!parser.parseDocument(pSourceId, pStream, document))
        return false;

    mLateTypeResolve.insert(mLateTypeResolve.end(), parser.mLateTypeResolve.begin(), parser.mLateTypeResolve.end());

    return true;
}

void Parser::addValidator(const ValidatorPtr& pValidator)
{
    mvValidator.push_back(pValidator);
}

void Parser::initDocumentContext()
{
    if (!mContext)
    {
        DocumentParseContextSPtr context = boost::make_shared<DocumentParseContext>();
        context->mMessageCollector = boost::make_shared<MessageCollector>();
        context->mSources = boost::make_shared<ParseContext::SourceMap>();
        context->mDocument = lib::compil::CompilDocument::create();
        mContext = context;
    }
}

bool Parser::parseDocument(const StreamPtr& pInput,
                           DocumentSPtr& resultDocument)
{
    initDocumentContext();
    TokenizerPtr& tokenizer = mContext->tokenizer;

    tokenizer = boost::make_shared<Tokenizer>(mContext->mMessageCollector, mContext->mSourceId, pInput);

    FileSPtr file = parseFile(mContext);
    if (!file)
        return false;

    if (!document()->mainFile())
        document()->set_mainFile(file);

    CommentSPtr pStatementComment = lastComment(mContext);
    while (tokenizer->check(Token::TYPE_IDENTIFIER, "import"))
    {
        if (!parseImport())
            return false;
        tokenizer->shift();
        pStatementComment = lastComment(mContext);
    }

    if (tokenizer->check(Token::TYPE_IDENTIFIER, "package"))
    {
        mContext->mPackage = parsePackage(mContext);
        if (!mContext->mPackage)
            return false;
        if (document()->mainFile() == file)
            document()->set_package(mContext->mPackage);

        tokenizer->shift();
        pStatementComment = lastComment(mContext);
    }

    while (tokenizer->current())
    {
        if (tokenizer->check(Token::TYPE_IDENTIFIER))
        {
            parseAnyStatement(pStatementComment);
        }
        else
        {
            tokenizer->shift();
        }
        pStatementComment = lastComment(mContext);
    }

    if (document()->mainFile() == file)
    {
        std::vector<LateTypeResolveInfo>::iterator it;
        for (it = mLateTypeResolve.begin(); it != mLateTypeResolve.end() ; ++it)
        {
            const TokenPtr& token = it->token;
            *this << (errorMessage(mContext, Message::p_unknownClassifierType,
                                   token->line(), token->beginColumn())
                  << Message::Classifier(it->classifier)
                  << Message::Type(token->text()));
        }

        if (mContext->mMessageCollector->severity() > Message::SEVERITY_WARNING)
            return false;

        if (!validate(document()))
            return false;
    }

    resultDocument = document();
    return true;
}

bool Parser::parseDocument(const SourceIdSPtr& sourceId,
                           const StreamPtr& pInput,
                           DocumentSPtr& resultDocument)
{
    initDocumentContext();
    mContext->mSourceId = sourceId;

    if (!document()->sourceId())
        document()->set_sourceId(sourceId);

    if (!document()->name())
    {
        NameSPtr name = (nameRef() << sourceId);
        std::string file = sourceId->original();
        size_t slashIdx = file.find_last_of(".");
        if (slashIdx == std::string::npos)
            name << file;
        else
            name << file.substr(0, slashIdx);

        document()->set_name(name);
    }

    assert(sourceId);
    mContext->mSources->insert(ParseContext::SourceMap::value_type(sourceId->value(), sourceId));

    return parseDocument(pInput, resultDocument);
}

bool Parser::parseDocument(const ISourceProviderSPtr& sourceProvider,
                           const SourceIdSPtr& sourceId,
                           DocumentSPtr& document)
{
    initDocumentContext();
    mContext->mSourceProvider = sourceProvider;

    StreamPtr pStream = mContext->mSourceProvider->openInputStream(sourceId);
    if (!pStream)
    {
        *this << Message(Message::SEVERITY_ERROR, Message::p_openSourceFailed, mContext->mSourceId, Line(1), Column(0));
        return false;
    }
    return parseDocument(sourceId, pStream, document);
}

void Parser::setDocumentInput(const boost::shared_ptr<std::istream>& pInput)
{
    initDocumentContext();
    mContext->tokenizer = boost::make_shared<Tokenizer>(mContext->mMessageCollector, mContext->mSourceId, pInput);
}

void Parser::initProjectContext()
{
    if (!mContext)
    {
        mContext = boost::make_shared<ProjectParseContext>();
        mContext->mMessageCollector = boost::make_shared<MessageCollector>();
        mContext->mSources = boost::make_shared<ParseContext::SourceMap>();
    }
}

bool Parser::parseProject(const SourceIdSPtr& sourceId,
                          const StreamPtr& pInput,
                          ProjectSPtr& project)
{
    initProjectContext();
    mContext->tokenizer = boost::make_shared<Tokenizer>(mContext->mMessageCollector, sourceId, pInput);
    mContext->mSourceId = sourceId;

    ProjectParseContextSPtr context = boost::static_pointer_cast<ProjectParseContext>(mContext);
    project = ProjectParserMixin::parseProject(context);
    return project;
}

const std::vector<Message>& Parser::messages()
{
    return mContext->mMessageCollector->messages();
}

void Parser::lateTypeResolve(const TypeSPtr& pNewType)
{
    std::vector<LateTypeResolveInfo>::iterator it = mLateTypeResolve.begin();
    while (it != mLateTypeResolve.end())
    {
        if (it->token->text() == pNewType->name()->value())
        {
            it->initTypeMethod(pNewType);
            it = mLateTypeResolve.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

Parser& Parser::operator<<(const Message& message)
{
    assert(message.text().find("%") == std::string::npos);
    mContext->mMessageCollector->addMessage(message);
	return *this;
}

bool Parser::validate(const DocumentSPtr&)
{
    return true;
}

bool Parser::validate(const ObjectSPtr& pObject)
{
    bool bResult = true;

    for (std::vector<ValidatorPtr>::iterator it = mvValidator.begin(); it != mvValidator.end(); ++it)
    {
        ValidatorPtr& pValidator = *it;

        if (!pValidator->validate(pObject, mContext->mMessageCollector))
            bResult = false;
    }

    return bResult;
}

}