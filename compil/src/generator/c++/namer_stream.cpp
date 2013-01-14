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

BodyFunctionDefinitionSPtr NamerStream::convertBodyFunctionDefinition(const BodyFunctionDefinitionSPtr& definition)
{
    BodyFunctionDefinitionSPtr newdefinition = bodyFunctionDefinitionRef()
        << definition->specifier()
        << convertDeclarator(definition->declarator());
    return newdefinition;
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

DeclarationSPtr NamerStream::convertDeclaration(const DeclarationSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == ClassDeclaration::staticDeclarationId())
    {
        ClassDeclarationSPtr cdeclaration = ClassDeclaration::downcast(declaration);
        return convertTypeNameSimpleTypeSpecifier(cdeclaration->class_());
    }
    
    BOOST_ASSERT(false);
    return DeclarationSPtr();
}

DeclaratorSPtr NamerStream::convertDeclarator(const DeclaratorSPtr& declarator)
{
    DirectDeclaratorSPtr directDeclarator = DeclaratorFactory::downcastDirectDeclarator(declarator);
    if (directDeclarator)
        return convertDirectDeclarator(directDeclarator);

    DeclaratorIdSPtr declaratorId = DeclaratorFactory::downcastDeclaratorId(declarator);
    if (declaratorId)
        return convertDeclaratorId(declaratorId);

    BOOST_ASSERT(false);
    return DeclaratorSPtr();
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
    
    if (expression->runtimeExpressionId() == GenericEqualityExpression::staticExpressionId())
    {
        GenericEqualityExpressionSPtr geexpression = GenericEqualityExpression::downcast(expression);
    
        GrammarEqualityExpressionSPtr grammarEqualityExpression = grammarEqualityExpressionRef()
            << geexpression->type()
            << convertEqualityExpression(geexpression->first())
            << convertRelationalExpression(geexpression->second());

        map[expression] = grammarEqualityExpression;
        return grammarEqualityExpression;
    }
    
    if (expression->runtimeExpressionId() == MethodCallExpression::staticExpressionId())
    {
        MethodCallExpressionSPtr mcexpression = MethodCallExpression::downcast(expression);

        IdentifierSPtr methodIdentifier = convertIdentifierMethodName(mcexpression->method())->identifier();
        IdentifierUnqualifiedIdSPtr methodUnqualifiedId = identifierUnqualifiedIdRef()
            << methodIdentifier;
        UnqualifiedIdExpressionSPtr methodExpression = unqualifiedIdExpressionRef()
            << methodUnqualifiedId;
        
        MemberAccessPostfixExpressionSPtr memberAccessExpression = memberAccessPostfixExpressionRef()
            << convertPostfixExpression(mcexpression->variable())
            << methodExpression;
            
        ParenthesesPostfixExpressionSPtr parenthesesExpression = parenthesesPostfixExpressionRef()
            << memberAccessExpression
            << convertExpressionList(mcexpression->list());
        
        map[expression] = parenthesesExpression;
        return parenthesesExpression;
    }
    
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
    if (expression->runtimeExpressionId() == VariableExpression::staticExpressionId())
    {
        RelationalEqualityExpressionSPtr relationalEqualityExpression = relationalEqualityExpressionRef()
            << convertRelationalExpression(expression);
        return relationalEqualityExpression;
    }

    BOOST_ASSERT(false);
    return EqualityExpressionSPtr();
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
    MethodNameSPtr methodName = DeclarationFactory::downcastMethodName(name);
    if (methodName)
        return convertIdentifierMethodName(methodName);
    
    BOOST_ASSERT(false);
    return FunctionNameSPtr();
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
        
    BOOST_ASSERT(false);
    return MemberDeclarationSPtr();
}

MemberDeclaratorSPtr NamerStream::convertMemberDeclarator(const MemberDeclaratorSPtr& declarator)
{
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
    if (name->runtimeDeclarationId() == IdentifierMethodName::staticDeclarationId())
        return IdentifierMethodName::downcast(name);
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

ParametersDirectDeclaratorSPtr NamerStream::convertParametersDirectDeclarator(const ParametersDirectDeclaratorSPtr& declarator)
{
    ParametersDirectDeclaratorSPtr newdeclarator = parametersDirectDeclaratorRef()
        << convertDirectDeclarator(declarator->declarator())
        << declarator->parameters();
        
    return newdeclarator;
}

PostfixExpressionSPtr NamerStream::convertPostfixExpression(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == VariableExpression::staticExpressionId())
    {
        VariableExpressionSPtr vexpression = VariableExpression::downcast(expression);

        IdentifierSPtr variableIdentifier = identifierRef()
            << vexpression->variable()->name()->value();

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

RelationalExpressionSPtr NamerStream::convertRelationalExpression(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == VariableExpression::staticExpressionId())
    {
        PostfixUnaryExpressionSPtr postfixUnaryExpression = postfixUnaryExpressionRef()
            << convertPostfixExpression(expression);
        UnaryCastExpressionSPtr unaryCastExpression = unaryCastExpressionRef()
            << postfixUnaryExpression;
        CastPmExpressionSPtr castPmExpression = castPmExpressionRef()
            << unaryCastExpression;
        PmMultiplicativeExpressionSPtr pmMultiplicativeExpression = pmMultiplicativeExpressionRef()
            << castPmExpression;
        MultiplicativeAdditiveExpressionSPtr multiplicativeAdditiveExpression = multiplicativeAdditiveExpressionRef()
            << pmMultiplicativeExpression;
        AdditiveShiftExpressionSPtr additiveShiftExpression = additiveShiftExpressionRef()
            << multiplicativeAdditiveExpression;
        ShiftRelationalExpressionSPtr shiftRelationalExpression = shiftRelationalExpressionRef()
            << additiveShiftExpression;
        
        return shiftRelationalExpression;
    }

    BOOST_ASSERT(false);
    return RelationalExpressionSPtr();
}

TypeNameSimpleTypeSpecifierSPtr NamerStream::convertTypeNameSimpleTypeSpecifier(const ClassSPtr& class_)
{
    ClassTypeNameSPtr classTypeName = classTypeNameRef()
        << convertIdentifierClassName(class_->name());
        
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
        
    TypeNameSimpleTypeSpecifierSPtr typeNameSimpleTypeSpecifier = typeNameSimpleTypeSpecifierRef()
        << nestedNameSpecifier
        << classTypeName;
        
    return typeNameSimpleTypeSpecifier;
}

StatementSPtr NamerStream::convertStatement(const StatementSPtr& statement)
{
    if (statement->runtimeStatementId() == CompoundStatement::staticStatementId())
    {
        CompoundStatementSPtr cstatment = CompoundStatement::downcast(statement);

        CompoundStatementSPtr newstatement = compoundStatementRef()
            << cstatment->close();
        const std::vector<StatementSPtr>& statements = cstatment->statements();
        for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
            newstatement << convertStatement(*it);
            
        return newstatement;
    }
    
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
    
    if (statement->runtimeStatementId() == VariableDeclarationStatement::staticStatementId())
    {
        VariableDeclarationStatementSPtr vdstatment = VariableDeclarationStatement::downcast(statement);
            
        TypeDeclarationSpecifierSPtr typeDeclarationSpecifier = typeDeclarationSpecifierRef()
            << convertTypeNameSimpleTypeSpecifier(vdstatment->type());
        DeclarationSpecifierSequenceSPtr declarationSpecifierSequence = declarationSpecifierSequenceRef()
            << typeDeclarationSpecifier;
            
        IdentifierClassNameSPtr identifierClassName = identifierClassNameRef()
            << (identifierRef() << vdstatment->variable()->name()->value());
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
    
    return statement;
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

NamerStream& NamerStream::operator<<(const lang::all::EndOfLineSPtr& endl)
{
    mFormatter << endl;
    return *this;
}

}
