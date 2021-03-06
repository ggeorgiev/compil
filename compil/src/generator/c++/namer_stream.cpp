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

#include "namer_stream.h"

#include "library/c++/compil/declarator.h"
#include "library/c++/stl/string.h"

#include "boost/unordered_map.hpp"

namespace nmr
{

NamerStream::NamerStream(const NamerConfigurationSPtr& namerConfiguration,
                const FormatterConfigurationSPtr& formatterConfiguration,
                const AlignerConfigurationSPtr& alignerConfiguration)
    : mFormatter(formatterConfiguration, alignerConfiguration)
    , mConfiguration(namerConfiguration)
{
}

NamerStream::~NamerStream()
{
}

std::string NamerStream::str()
{
    return mFormatter.str();
}

AdditiveExpressionSPtr NamerStream::convertAdditiveExpression(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == GenericAdditiveExpression::staticExpressionId())
    {
        GenericAdditiveExpressionSPtr adexpression = GenericAdditiveExpression::downcast(expression);
    
        GrammarAdditiveExpressionSPtr grammarAdditiveExpression = grammarAdditiveExpressionRef()
            << adexpression->type()
            << convertAdditiveExpression(adexpression->first())
            << convertMultiplicativeExpression(adexpression->second());

        return grammarAdditiveExpression;
    }
    
    MultiplicativeAdditiveExpressionSPtr multiplicativeAdditiveExpression = multiplicativeAdditiveExpressionRef()
        << convertMultiplicativeExpression(expression);
    
    return multiplicativeAdditiveExpression;
}

BodyFunctionDefinitionSPtr NamerStream::convertBodyFunctionDefinition(const BodyFunctionDefinitionSPtr& definition)
{
    BodyFunctionDefinitionSPtr newdefinition = bodyFunctionDefinitionRef();
    if (definition->specifier())
        newdefinition << convertDeclarationSpecifierSequence(definition->specifier());
    if (definition->declarator())
        newdefinition << convertDeclarator(definition->declarator());

    if (definition->body())
        newdefinition << convertFunctionBody(definition->body());
        
    return newdefinition;
}

CompoundStatementSPtr NamerStream::convertCompoundStatement(const CompoundStatementSPtr& statement)
{
    CompoundStatementSPtr newstatement = compoundStatementRef()
        << statement->close();
    const std::vector<StatementSPtr>& statements = statement->statements();
    for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
        newstatement << convertStatement(*it);
        
    return newstatement;
}

ClassHeadSPtr NamerStream::convertClassHead(const ClassHeadSPtr& head)
{
    ClassHeadSPtr newhead = classHeadRef()
        << head->key()
        << convertIdentifierClassName(head->name());
        
    return newhead;
}

ClassSpecifierSPtr NamerStream::convertClassSpecifier(const ClassSpecifierSPtr& specifier)
{
    ClassSpecifierSPtr newspecifier = classSpecifierRef()
        << convertClassHead(specifier->head())
        << convertMemberSpecification(specifier->members());
        
    return newspecifier;
}

CVQualifierSequenceSPtr NamerStream::convertCVQualifierSequence(const CVQualifierSequenceSPtr& qualifier)
{
    return qualifier;
}

CVQualifierTypeSpecifierSPtr NamerStream::convertCVQualifierTypeSpecifier(const CVQualifierTypeSpecifierSPtr& specifier)
{
    return specifier;
}

DeclarationSPtr NamerStream::convertDeclaration(const DeclarationSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == ClassDeclarationSpecifier::staticDeclarationId())
    {
        ClassDeclarationSpecifierSPtr cdeclaration = ClassDeclarationSpecifier::downcast(declaration);
        return convertTypeNameSimpleTypeSpecifier(cdeclaration->class_());
    }
    
    BOOST_ASSERT(false);
    return DeclarationSPtr();
}

DeclarationSpecifierSPtr NamerStream::convertDeclarationSpecifier(const ClassDeclarationSpecifierSPtr& specifier)
{
    return typeDeclarationSpecifierRef() << convertTypeNameSimpleTypeSpecifier(specifier->class_());
}

DeclarationSpecifierSPtr NamerStream::convertDeclarationSpecifier(const DeclarationSpecifierSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == ClassDeclarationSpecifier::staticDeclarationId())
        return convertDeclarationSpecifier(ClassDeclarationSpecifier::downcast(declaration));
    if (declaration->runtimeDeclarationId() == FunctionDeclarationSpecifier::staticDeclarationId())
        return convertFunctionDeclarationSpecifier(FunctionDeclarationSpecifier::downcast(declaration));
    if (declaration->runtimeDeclarationId() == TypeDeclarationSpecifier::staticDeclarationId())
        return convertTypeDeclarationSpecifier(TypeDeclarationSpecifier::downcast(declaration));

    BOOST_ASSERT(false);
    return DeclarationSpecifierSPtr();
}

DeclaratorSPtr NamerStream::convertDeclarator(const DeclaratorSPtr& declarator)
{
    DirectDeclaratorSPtr directDeclarator = DeclaratorFactory::downcastDirectDeclarator(declarator);
    if (directDeclarator)
        return convertDirectDeclarator(directDeclarator);

    DeclaratorIdSPtr declaratorId = DeclaratorFactory::downcastDeclaratorId(declarator);
    if (declaratorId)
        return convertDeclaratorId(declaratorId);
        
    if (declarator->runtimeDeclaratorId() == ParameterDeclarationClause::staticDeclaratorId())
        return convertParameterDeclarationClause(ParameterDeclarationClause::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == PointerDeclarator::staticDeclaratorId())
        return convertPointerDeclarator(PointerDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == VariableNameDeclarator::staticDeclaratorId())
        return convertVariableNameDeclarator(VariableNameDeclarator::downcast(declarator));

    BOOST_ASSERT(false);
    return DeclaratorSPtr();
}

DeclarationSpecifierSequenceSPtr NamerStream::convertDeclarationSpecifierSequence(const DeclarationSpecifierSequenceSPtr& declaration)
{
    DeclarationSpecifierSequenceSPtr newdeclaration = declarationSpecifierSequenceRef();
    
    const std::vector<DeclarationSpecifierSPtr>& declarations = declaration->declarations();
    for (std::vector<DeclarationSpecifierSPtr>::const_iterator it = declarations.begin(); it != declarations.end(); ++it)
        newdeclaration << convertDeclarationSpecifier(*it);

    return newdeclaration;
}

DeclaratorIdSPtr NamerStream::convertDeclaratorId(const DeclaratorIdSPtr& declarator)
{
    if (declarator->runtimeDeclaratorId() == FunctionNameDeclaratorId::staticDeclaratorId())
        return convertFunctionNameDeclaratorId(FunctionNameDeclaratorId::downcast(declarator));

    BOOST_ASSERT(false);
    return DeclaratorIdSPtr();
}

DeclaratorIdDirectDeclaratorSPtr NamerStream::convertDeclaratorIdDirectDeclarator(const DeclaratorIdDirectDeclaratorSPtr& declarator)
{
    DeclaratorIdDirectDeclaratorSPtr newdeclarator = declaratorIdDirectDeclaratorRef()
        << convertDeclaratorId(declarator->declarator());
    
    return newdeclarator;
}

DeclaratorMemberDeclaratorSPtr NamerStream::convertDeclaratorMemberDeclarator(const DeclaratorMemberDeclaratorSPtr& declarator)
{
    DeclaratorMemberDeclaratorSPtr newdeclarator = declaratorMemberDeclaratorRef()
        << convertDeclarator(declarator->declarator());
    return newdeclarator;
}

DeclaratorParameterDeclarationSPtr NamerStream::convertDeclaratorParameterDeclaration(const DeclaratorParameterDeclarationSPtr& declarator)
{
    DeclaratorParameterDeclarationSPtr newdeclarator = declaratorParameterDeclarationRef()
        << convertDeclarationSpecifierSequence(declarator->declaration())
        << convertDeclarator(declarator->declarator());
        
    return newdeclarator;
}

DirectDeclaratorSPtr NamerStream::convertDirectDeclarator(const DirectDeclaratorSPtr& declarator)
{
    if (declarator->runtimeDeclaratorId() == DeclaratorIdDirectDeclarator::staticDeclaratorId())
        return convertDeclaratorIdDirectDeclarator(DeclaratorIdDirectDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == ParametersDirectDeclarator::staticDeclaratorId())
        return convertParametersDirectDeclarator(ParametersDirectDeclarator::downcast(declarator));
        
    BOOST_ASSERT(false);
    return DirectDeclaratorSPtr();
}

ExpressionSPtr NamerStream::convertExpression(const ExpressionSPtr& expression)
{
    static boost::unordered_map<ExpressionSPtr, ExpressionSPtr> map;
    boost::unordered_map<ExpressionSPtr, ExpressionSPtr>::iterator it = map.find(expression);
    if (it != map.end())
        return it->second;

    if (expression->runtimeExpressionId() == ConstructorCallExpression::staticExpressionId())
    {
        ConstructorCallExpressionSPtr ccexpression = ConstructorCallExpression::downcast(expression);
        
        IdentifierSPtr constructorIdentifier = convertIdentifier(ccexpression->type());
        IdentifierUnqualifiedIdSPtr constructorUnqualifiedId = identifierUnqualifiedIdRef()
            << constructorIdentifier;
        UnqualifiedIdExpressionSPtr constructorUnqualifiedIdExpression = unqualifiedIdExpressionRef()
            << constructorUnqualifiedId;
        IdExpressionPrimaryExpressionSPtr constructorPrimaryExpression = idExpressionPrimaryExpressionRef()
            << constructorUnqualifiedIdExpression;
        PrimaryExpressionPostfixExpressionSPtr constructorPostfixExpression = primaryExpressionPostfixExpressionRef()
            << constructorPrimaryExpression;
            
        ParenthesesPostfixExpressionSPtr parenthesesExpression = parenthesesPostfixExpressionRef()
            << constructorPostfixExpression;
            
        map[expression] = parenthesesExpression;
        return parenthesesExpression;
    }
    
    if (expression->runtimeExpressionId() == CustomExpression::staticExpressionId())
    {
        map[expression] = expression;
        return expression;
    }

    if (expression->runtimeExpressionId() == GenericAdditiveExpression::staticExpressionId())
        return convertAdditiveExpression(expression);
    
    if (expression->runtimeExpressionId() == GenericEqualityExpression::staticExpressionId())
        return convertEqualityExpression(expression);

    if (expression->runtimeExpressionId() == GenericRelationalExpression::staticExpressionId())
        return convertRelationalExpression(expression);
    
    if (expression->runtimeExpressionId() == MethodCallExpression::staticExpressionId())
        return convertPostfixExpression(expression);
    
    if (expression->runtimeExpressionId() == VariableExpression::staticExpressionId())
    {
        PostfixExpressionSPtr variablePostfixExpression = convertPostfixExpression(expression);
        map[expression] = variablePostfixExpression;
        return variablePostfixExpression;
    }
    
    BOOST_ASSERT(false);
    return ExpressionSPtr();
}

EqualityExpressionSPtr NamerStream::convertEqualityExpression(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == GenericEqualityExpression::staticExpressionId())
    {
        GenericEqualityExpressionSPtr geexpression = GenericEqualityExpression::downcast(expression);
    
        GrammarEqualityExpressionSPtr grammarEqualityExpression = grammarEqualityExpressionRef()
            << geexpression->type()
            << convertEqualityExpression(geexpression->first())
            << convertRelationalExpression(geexpression->second());

        return grammarEqualityExpression;
    }

    RelationalEqualityExpressionSPtr relationalEqualityExpression = relationalEqualityExpressionRef()
        << convertRelationalExpression(expression);
    return relationalEqualityExpression;
}

ExpressionListSPtr NamerStream::convertExpressionList(const ExpressionListSPtr& list)
{
    if (!list)
        return list;
        
    ExpressionListSPtr newlist = expressionListRef();
    const std::vector<ExpressionSPtr>& expressions = list->expressions();
    for (std::vector<ExpressionSPtr>::const_iterator it = expressions.begin(); it != expressions.end(); ++it)
        newlist << convertExpression(*it);
        
    return newlist;
}

FunctionBodySPtr NamerStream::convertFunctionBody(const FunctionBodySPtr& body)
{
    FunctionBodySPtr newbody = functionBodyRef()
        << convertCompoundStatement(body->statement());
        
    return newbody;
}

FunctionDeclarationSpecifierSPtr NamerStream::convertFunctionDeclarationSpecifier(const FunctionDeclarationSpecifierSPtr& specifier)
{
    return specifier;
}

FunctionNameDeclaratorIdSPtr NamerStream::convertFunctionNameDeclaratorId(const FunctionNameDeclaratorIdSPtr& declarator)
{
    FunctionNameDeclaratorIdSPtr newdeclarator = functionNameDeclaratorIdRef()
        << convertFunctionName(declarator->functionName());
    
    return newdeclarator;
}

FunctionDefinitionSPtr NamerStream::convertFunctionDefinition(const FunctionDefinitionSPtr& definition)
{
    if (definition->runtimeDeclaratorId() == BodyFunctionDefinition::staticDeclaratorId())
        return convertBodyFunctionDefinition(BodyFunctionDefinition::downcast(definition));

    BOOST_ASSERT(false);
    return FunctionDefinitionSPtr();
}

FunctionDefinitionMemberDeclarationSPtr NamerStream::convertFunctionDefinitionMemberDeclaration(const FunctionDefinitionMemberDeclarationSPtr& declaration)
{
    FunctionDefinitionMemberDeclarationSPtr newdeclaration = functionDefinitionMemberDeclarationRef()
        << convertFunctionDefinition(declaration->definition());
        
    return newdeclaration;
}

FunctionNameSPtr NamerStream::convertFunctionName(const FunctionNameSPtr& name)
{
    if (name->runtimeDeclarationId() == OperatorMethodName::staticDeclarationId())
        return OperatorMethodName::downcast(name);
    
    MethodNameSPtr methodName = DeclarationFactory::downcastMethodName(name);
    if (methodName)
        return convertIdentifierMethodName(methodName);
    
    BOOST_ASSERT(false);
    return FunctionNameSPtr();
}

IdentifierSPtr NamerStream::convertIdentifier(const ClassNameSPtr& name)
{
    if (name->runtimeClassNameId() == IdentifierClassName::staticClassNameId())
        return IdentifierClassName::downcast(name)->identifier();
        
    BOOST_ASSERT(false);
    return IdentifierSPtr();
}

IdentifierClassNameSPtr NamerStream::convertIdentifierClassName(const ClassNameSPtr& name)
{
    if (name->runtimeClassNameId() == IdentifierClassName::staticClassNameId())
        return IdentifierClassName::downcast(name);
        
    BOOST_ASSERT(false);
    return IdentifierClassNameSPtr();
}

IdentifierMethodNameSPtr NamerStream::convertIdentifierMethodName(const MethodNameSPtr& name)
{
    if (name->runtimeDeclarationId() == ConstructorMethodName::staticDeclarationId())
    {
        ClassNameSPtr className = ConstructorMethodName::downcast(name)->className();
        return identifierMethodNameRef() << convertIdentifierClassName(className)->identifier();
    }
    if (name->runtimeDeclarationId() == DestructorMethodName::staticDeclarationId())
    {
        ClassNameSPtr className = DestructorMethodName::downcast(name)->className();
        return identifierDestructorMethodNameRef() << convertIdentifierClassName(className)->identifier();
    }
    if (name->runtimeDeclarationId() == IdentifierMethodName::staticDeclarationId())
        return IdentifierMethodName::downcast(name);
        
    BOOST_ASSERT(false);
    return IdentifierMethodNameSPtr();
}

IdentifierNamespaceNameSPtr NamerStream::convertIdentifierNamespaceName(const NamespaceNameSPtr& name)
{
    if (name->runtimeNamespaceNameId() == IdentifierNamespaceName::staticNamespaceNameId())
        return IdentifierNamespaceName::downcast(name);
        
    BOOST_ASSERT(false);
    return IdentifierNamespaceNameSPtr();
}

MacroArgumentSPtr NamerStream::convertMacroArgument(const MacroArgumentSPtr& parameter)
{
    if (parameter->runtimeMacroArgumentId() == ExpressionMacroArgument::staticMacroArgumentId())
        return expressionMacroArgumentRef() << convertExpression(ExpressionMacroArgument::downcast(parameter)->expression());
    if (parameter->runtimeMacroArgumentId() == DeclarationMacroArgument::staticMacroArgumentId())
        return declarationMacroArgumentRef() << convertDeclaration(DeclarationMacroArgument::downcast(parameter)->declaration());

    BOOST_ASSERT(false);
    return MacroArgumentSPtr();
}

MemberDeclarationSPtr NamerStream::convertMemberDeclaration(const MemberDeclarationSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == FunctionDefinitionMemberDeclaration::staticDeclarationId())
        return convertFunctionDefinitionMemberDeclaration(FunctionDefinitionMemberDeclaration::downcast(declaration));
    if (declaration->runtimeDeclarationId() == SpecifierMemberDeclaration::staticDeclarationId())
        return convertSpecifierMemberDeclaration(SpecifierMemberDeclaration::downcast(declaration));
        
    BOOST_ASSERT(false);
    return MemberDeclarationSPtr();
}

MemberDeclaratorSPtr NamerStream::convertMemberDeclarator(const MemberDeclaratorSPtr& declarator)
{
    if (declarator->runtimeDeclaratorId() == DeclaratorMemberDeclarator::staticDeclaratorId())
        return convertDeclaratorMemberDeclarator(DeclaratorMemberDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == PureMemberDeclarator::staticDeclaratorId())
        return convertPureMemberDeclarator(PureMemberDeclarator::downcast(declarator));
        
    BOOST_ASSERT(false);
    return MemberDeclaratorSPtr();
}

MemberSpecificationSPtr NamerStream::convertMemberSpecification(const MemberSpecificationSPtr& specification)
{
    MemberSpecificationSPtr newspecification = memberSpecificationRef();
    
    const std::vector<MemberSpecificationSectionSPtr>& sections = specification->sections();
    for (std::vector<MemberSpecificationSectionSPtr>::const_iterator it = sections.begin(); it != sections.end(); ++it)
        newspecification << convertMemberSpecificationSection(*it);
    return newspecification;
}

MemberSpecificationSectionSPtr NamerStream::convertMemberSpecificationSection(const MemberSpecificationSectionSPtr& section)
{
    MemberSpecificationSectionSPtr newsection = memberSpecificationSectionRef()
        << section->accessSpecifier();

    const std::vector<MemberDeclarationSPtr>& declarations = section->declarations();
    for (std::vector<MemberDeclarationSPtr>::const_iterator it = declarations.begin(); it != declarations.end(); ++it)
        newsection << convertMemberDeclaration(*it);
    
    return newsection;
}

MultiplicativeExpressionSPtr NamerStream::convertMultiplicativeExpression(const ExpressionSPtr& expression)
{
    PostfixUnaryExpressionSPtr postfixUnaryExpression = postfixUnaryExpressionRef()
        << convertPostfixExpression(expression);
    UnaryCastExpressionSPtr unaryCastExpression = unaryCastExpressionRef()
        << postfixUnaryExpression;
    CastPmExpressionSPtr castPmExpression = castPmExpressionRef()
        << unaryCastExpression;
    PmMultiplicativeExpressionSPtr pmMultiplicativeExpression = pmMultiplicativeExpressionRef()
        << castPmExpression;
    return pmMultiplicativeExpression;
}

NestedNameSpecifierSPtr NamerStream::convertNestedNameSpecifier(const ClassSPtr& class_)
{
    NestedNameSpecifierSPtr nestedNameSpecifier;
    
    for (ClassSPtr nested = class_; nested->containerClass(); nested = nested->containerClass())
    {
        ClassNestedNameSPtr classNestedName = classNestedNameRef()
            << convertIdentifierClassName(nested->containerClass()->name());
        
        NestedNameSpecifierSPtr thisNestedNameSpecifier = nestedNameSpecifierRef()
            << classNestedName;
            
        if (nestedNameSpecifier)
            thisNestedNameSpecifier << nestedNameSpecifier;
            
        nestedNameSpecifier = thisNestedNameSpecifier;
    }
    
    if (class_->namespace_())
    {
        const std::vector<NamespaceNameSPtr>& names = class_->namespace_()->names();
        for (std::vector<NamespaceNameSPtr>::const_reverse_iterator it = names.rbegin(); it != names.rend(); ++it)
        {
            NamespaceNestedNameSPtr namespaceNestedName = namespaceNestedNameRef()
                << convertIdentifierNamespaceName(*it);
        
            NestedNameSpecifierSPtr thisNestedNameSpecifier = nestedNameSpecifierRef()
                << namespaceNestedName;

            if (nestedNameSpecifier)
                thisNestedNameSpecifier << nestedNameSpecifier;

            nestedNameSpecifier = thisNestedNameSpecifier;
        }
    }
    return nestedNameSpecifier;
}

ParameterDeclarationSPtr NamerStream::convertParameterDeclaration(const ParameterDeclarationSPtr& declarator)
{
    if (declarator->runtimeDeclaratorId() == DeclaratorParameterDeclaration::staticDeclaratorId())
        return convertDeclaratorParameterDeclaration(DeclaratorParameterDeclaration::downcast(declarator));
        
    BOOST_ASSERT(false);
    return ParameterDeclarationSPtr();
}

ParameterDeclarationClauseSPtr NamerStream::convertParameterDeclarationClause(const ParameterDeclarationClauseSPtr& declarator)
{
    ParameterDeclarationClauseSPtr newdeclarator = parameterDeclarationClauseRef()
        << convertParameterDeclarationList(declarator->list());

    return newdeclarator;
}

ParameterDeclarationListSPtr NamerStream::convertParameterDeclarationList(const ParameterDeclarationListSPtr& declarator)
{
    ParameterDeclarationListSPtr newdeclarator = parameterDeclarationListRef();
    
    const std::vector<ParameterDeclarationSPtr>& declarators = declarator->declarators();
    for (std::vector<ParameterDeclarationSPtr>::const_iterator it = declarators.begin(); it != declarators.end(); ++it)
        newdeclarator << convertParameterDeclaration(*it);
    return newdeclarator;
}

ParametersDirectDeclaratorSPtr NamerStream::convertParametersDirectDeclarator(const ParametersDirectDeclaratorSPtr& declarator)
{
    ParametersDirectDeclaratorSPtr newdeclarator = parametersDirectDeclaratorRef()
        << convertDirectDeclarator(declarator->declarator());
    if (declarator->parameters())
        newdeclarator << convertParameterDeclarationClause(declarator->parameters());
    if (declarator->qualifier())
        newdeclarator << convertCVQualifierSequence(declarator->qualifier());
        
    return newdeclarator;
}

PointerDeclaratorSPtr NamerStream::convertPointerDeclarator(const PointerDeclaratorSPtr declarator)
{
    PointerDeclaratorSPtr newdeclarator = pointerDeclaratorRef()
        << convertDeclarator(declarator->declarator())
        << declarator->operator_();
    return newdeclarator;
}

PostfixExpressionSPtr NamerStream::convertPostfixExpression(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == VariableExpression::staticExpressionId())
    {
        VariableExpressionSPtr vexpression = VariableExpression::downcast(expression);

        IdentifierSPtr variableIdentifier = identifierRef()
            << vexpression->variable()->value();

        IdentifierUnqualifiedIdSPtr variableUnqualifiedId = identifierUnqualifiedIdRef()
            << variableIdentifier;
        UnqualifiedIdExpressionSPtr variableUnqualifiedIdExpression = unqualifiedIdExpressionRef()
            << variableUnqualifiedId;
        IdExpressionPrimaryExpressionSPtr variablePrimaryExpression = idExpressionPrimaryExpressionRef()
            << variableUnqualifiedIdExpression;
        PrimaryExpressionPostfixExpressionSPtr variablePostfixExpression = primaryExpressionPostfixExpressionRef()
            << variablePrimaryExpression;

        return variablePostfixExpression;
    }
    
    if (expression->runtimeExpressionId() == MethodCallExpression::staticExpressionId())
    {
        MethodCallExpressionSPtr mcexpression = MethodCallExpression::downcast(expression);

        IdentifierSPtr methodIdentifier = convertIdentifierMethodName(mcexpression->method())->identifier();
        IdentifierUnqualifiedIdSPtr methodUnqualifiedId = identifierUnqualifiedIdRef()
            << methodIdentifier;
        UnqualifiedIdExpressionSPtr methodExpression = unqualifiedIdExpressionRef()
            << methodUnqualifiedId;
        
        MemberAccessPostfixExpressionSPtr memberAccessExpression = memberAccessPostfixExpressionRef();
        if (mcexpression->variable())
            memberAccessExpression << convertPostfixExpression(mcexpression->variable());
        memberAccessExpression << methodExpression;
            
        ParenthesesPostfixExpressionSPtr parenthesesExpression = parenthesesPostfixExpressionRef()
            << memberAccessExpression
            << convertExpressionList(mcexpression->list());

        return parenthesesExpression;
    }

    BOOST_ASSERT(false);
    return PostfixExpressionSPtr();
}

PureMemberDeclaratorSPtr NamerStream::convertPureMemberDeclarator(const PureMemberDeclaratorSPtr& declarator)
{
    PureMemberDeclaratorSPtr newdeclarator = pureMemberDeclaratorRef()
        << convertDeclarator(declarator->declarator())
        << declarator->pure();
        
    return newdeclarator;
}

ReturnJumpStatementSPtr NamerStream::convertReturnJumpStatement(const ReturnJumpStatementSPtr& statement)
{
    ReturnJumpStatementSPtr newstatement = returnJumpStatementRef()
        << convertExpression(statement->expression());
    return newstatement;
}

RelationalExpressionSPtr NamerStream::convertRelationalExpression(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == GenericRelationalExpression::staticExpressionId())
    {
        GenericRelationalExpressionSPtr reexpression = GenericRelationalExpression::downcast(expression);
    
        GrammarRelationalExpressionSPtr grammarRelationalExpression = grammarRelationalExpressionRef()
            << reexpression->type()
            << convertRelationalExpression(reexpression->first())
            << convertShiftExpression(reexpression->second());

        return grammarRelationalExpression;
    }

    ShiftRelationalExpressionSPtr shiftRelationalExpression = shiftRelationalExpressionRef()
        << convertShiftExpression(expression);
    
    return shiftRelationalExpression;
}

ShiftExpressionSPtr NamerStream::convertShiftExpression(const ExpressionSPtr& expression)
{
    AdditiveShiftExpressionSPtr additiveShiftExpression = additiveShiftExpressionRef()
        << convertAdditiveExpression(expression);
    return additiveShiftExpression;
}

SpecifierMemberDeclarationSPtr NamerStream::convertSpecifierMemberDeclaration(const SpecifierMemberDeclarationSPtr& declaration)
{
    SpecifierMemberDeclarationSPtr newdeclaration = specifierMemberDeclarationRef()
        << convertDeclarationSpecifierSequence(declaration->specifier())
        << convertMemberDeclarator(declaration->declarator());
        
    return newdeclaration;
}

StatementSPtr NamerStream::convertStatement(const StatementSPtr& statement)
{
    if (statement->runtimeStatementId() == CompoundStatement::staticStatementId())
        return convertCompoundStatement(CompoundStatement::downcast(statement));
    
    if (statement->runtimeStatementId() == ExpressionStatement::staticStatementId())
    {
        ExpressionStatementSPtr estatement = ExpressionStatement::downcast(statement);
        ExpressionStatementSPtr newstatement = expressionStatementRef()
            << convertExpression(estatement->expression());
        return newstatement;
    }
    
    if (statement->runtimeStatementId() == MacroStatement::staticStatementId())
    {
        MacroStatementSPtr mstatement = MacroStatement::downcast(statement);
        MacroStatementSPtr newstatement = macroStatementRef()
            << mstatement->name()
            << mstatement->close();
            
        const std::vector<MacroArgumentSPtr>& parameters = mstatement->parameters();
        for (std::vector<MacroArgumentSPtr>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
            newstatement << convertMacroArgument(*it);
        
        return newstatement;
    }
    
    if (statement->runtimeStatementId() == ReturnJumpStatement::staticStatementId())
        return convertReturnJumpStatement(ReturnJumpStatement::downcast(statement));

    
    if (statement->runtimeStatementId() == VariableDeclarationStatement::staticStatementId())
    {
        VariableDeclarationStatementSPtr vdstatment = VariableDeclarationStatement::downcast(statement);
            
        TypeDeclarationSpecifierSPtr typeDeclarationSpecifier = typeDeclarationSpecifierRef()
            << convertTypeNameSimpleTypeSpecifier(vdstatment->type());
        DeclarationSpecifierSequenceSPtr declarationSpecifierSequence = declarationSpecifierSequenceRef()
            << typeDeclarationSpecifier;
            
        IdentifierClassNameSPtr identifierClassName = identifierClassNameRef()
            << (identifierRef() << vdstatment->variable()->value());
        ClassTypeNameSPtr classTypeName = classTypeNameRef()
            << identifierClassName;
        TypeNameDeclaratorIdSPtr typeNameDeclaratorId = typeNameDeclaratorIdRef()
            << classTypeName;
        DeclaratorIdDirectDeclaratorSPtr directDeclarator = declaratorIdDirectDeclaratorRef()
            << typeNameDeclaratorId;
        InitDeclaratorSPtr initDeclarator = initDeclaratorRef()
            << directDeclarator;
            
        SimpleDeclarationSPtr simpleDeclaration = simpleDeclarationRef()
            << initDeclarator
            << declarationSpecifierSequence;
        SimpleBlockDeclarationSPtr blockDeclaration = simpleBlockDeclarationRef()
            << simpleDeclaration;
            
        return declarationStatementRef() << blockDeclaration;
    }
    
    BOOST_ASSERT(false);
    return statement;
}

TypeSpecifierSPtr NamerStream::convertTypeSpecifier(const TypeSpecifierSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == BuiltinSimpleTypeSpecifier::staticDeclarationId())
        return BuiltinSimpleTypeSpecifier::downcast(declaration);
    if (declaration->runtimeDeclarationId() == TypeNameSimpleTypeSpecifier::staticDeclarationId())
        return TypeNameSimpleTypeSpecifier::downcast(declaration);
    if (declaration->runtimeDeclarationId() == CVQualifierTypeSpecifier::staticDeclarationId())
        return CVQualifierTypeSpecifier::downcast(declaration);

    BOOST_ASSERT(false);
    return TypeSpecifierSPtr();
}

TypeDeclarationSpecifierSPtr NamerStream::convertTypeDeclarationSpecifier(const TypeDeclarationSpecifierSPtr& declaration)
{
    TypeDeclarationSpecifierSPtr newdeclaration = typeDeclarationSpecifierRef()
        << convertTypeSpecifier(declaration->declaration());
        
    return newdeclaration;
}

TypeNameSimpleTypeSpecifierSPtr NamerStream::convertTypeNameSimpleTypeSpecifier(const ClassSPtr& class_)
{
    ClassTypeNameSPtr classTypeName = classTypeNameRef()
        << convertIdentifierClassName(class_->name());
        
    NestedNameSpecifierSPtr nestedNameSpecifier = convertNestedNameSpecifier(class_);
        
    TypeNameSimpleTypeSpecifierSPtr typeNameSimpleTypeSpecifier = typeNameSimpleTypeSpecifierRef()
        << nestedNameSpecifier
        << classTypeName;
        
    return typeNameSimpleTypeSpecifier;
}

VariableNameSPtr NamerStream::convertVariableName(const VariableNameSPtr& variable)
{
    return variable;
}

VariableNameDeclaratorSPtr NamerStream::convertVariableNameDeclarator(const VariableNameDeclaratorSPtr& declarator)
{
    VariableNameDeclaratorSPtr newdeclarator = variableNameDeclaratorRef()
        << convertVariableName(declarator->variable());
    return newdeclarator;
}

NamerStream& NamerStream::operator<<(const StatementSPtr& statement)
{
    mFormatter << convertStatement(statement);
    return *this;
}

NamerStream& NamerStream::operator<<(const ClassSpecifierSPtr& specifier)
{
    mFormatter << convertClassSpecifier(specifier);
    return *this;
}

NamerStream& NamerStream::operator<<(const BodyFunctionDefinitionSPtr& definition)
{
    mFormatter << convertBodyFunctionDefinition(definition);
    return *this;
}

NamerStream& NamerStream::operator<<(const lang::all::LineDelimiterSPtr& endl)
{
    mFormatter << lang::all::endOfLineRef();
    return *this;
}

}
