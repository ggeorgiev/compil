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

#include "formatter_stream.h"

#include "language/c++/expression/expression_factory.h"
#include "language/c++/statement/statement_factory.h"

using namespace lang::all;
using namespace lang::cpp;

FormatterStream::FormatterStream(const FormatterConfigurationSPtr& formatterConfiguration,
                                 const AlignerConfigurationSPtr& alignerConfiguration)
    : mAligner(alignerConfiguration)
    , mConfiguration(formatterConfiguration)
{
}

FormatterStream::~FormatterStream()
{
}

std::string FormatterStream::str()
{
    return mAligner.str();
}

ElementSPtr FormatterStream::convert(const AdditiveShiftExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const BodyFunctionDefinitionSPtr& definition)
{
    PassageSPtr passage = passageRef();
    if (definition->specifier())
    {
        passage << convert(definition->specifier())
                << (stringRef() << " ");
    }
        
    passage << convert(definition->declarator());
    return passage;
}

ElementSPtr FormatterStream::convert(const BuiltinSimpleTypeSpecifierSPtr& specifier)
{
    switch (specifier->type().value())
    {
        case BuiltinSimpleTypeSpecifier::EType::kBool_:
            return stringRef() << "bool";
        case BuiltinSimpleTypeSpecifier::EType::kSignedLong:
            return stringRef() << "long";
        default:
            BOOST_ASSERT(false);
    }
    
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const CastPmExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const CompoundStatementSPtr& compoundStatement)
{
    ScopeSPtr scope = scopeRef();
    scope << Scope::ESquiggles::brackets();
    
    const std::vector<StatementSPtr>& statements = compoundStatement->statements();
    for (std::vector<StatementSPtr>::const_iterator it = statements.begin(); it != statements.end(); ++it)
        scope << convert(*it);
        
    if (compoundStatement->close() == Statement::EClose::yes())
        scope << ";";

    return scope;
}

ElementSPtr FormatterStream::convert(const ClassTypeNameSPtr& declaration)
{
    return convert(IdentifierClassName::downcast(declaration->className()));
}

ElementSPtr FormatterStream::convert(const ClassHeadSPtr& head)
{
    PassageSPtr passage = passageRef();
    passage << convert(head->key())
            << (stringRef() << " ")
            << convert(IdentifierClassName::downcast(head->name()));
    return passage;
}

ElementSPtr FormatterStream::convert(const ClassNestedNameSPtr& expression)
{
    return convert(expression->name());
}

ElementSPtr FormatterStream::convert(const ClassSpecifierSPtr& specifier)
{
    PassageSPtr passage = passageRef();
    passage << convert(specifier->head())
            << endOfLineRef();

    ScopeSPtr scope = scopeRef();
    scope << Scope::ESquiggles::brackets();

    if (specifier->members())
        scope << convert(specifier->members());
        
    scope << ";"
          << endOfLineRef();
    passage << scope;
    return passage;
}

ElementSPtr FormatterStream::convert(const CVQualifierSequenceSPtr& qualifier)
{
    PassageSPtr passage = passageRef();
    const std::vector<ECVQualifier>& qualifiers = qualifier->qualifiers();
    for (std::vector<ECVQualifier>::const_iterator it = qualifiers.begin(); it != qualifiers.end(); ++it)
    {
        const ECVQualifier& qualifier = *it;
        passage << convert(qualifier);
    }
    return passage;
}


ElementSPtr FormatterStream::convert(const CVQualifierTypeSpecifierSPtr& specifier)
{
    return convert(specifier->qualifier());
}

ElementSPtr FormatterStream::convert(const CustomExpressionSPtr& expression)
{
    return stringRef() << expression->value();
}

ElementSPtr FormatterStream::convert(const CustomIdExpressionSPtr& expression)
{
    return stringRef() << expression->value();
}

ElementSPtr FormatterStream::convert(const DeclarationSPtr& declaration)
{
    if (declaration->runtimeDeclarationId() == BuiltinSimpleTypeSpecifier::staticDeclarationId())
        return convert(BuiltinSimpleTypeSpecifier::downcast(declaration));
    if (declaration->runtimeDeclarationId() == ClassTypeName::staticDeclarationId())
        return convert(ClassTypeName::downcast(declaration));
    if (declaration->runtimeDeclarationId() == CVQualifierTypeSpecifier::staticDeclarationId())
        return convert(CVQualifierTypeSpecifier::downcast(declaration));
    if (declaration->runtimeDeclarationId() == DeclarationSpecifierSequence::staticDeclarationId())
        return convert(DeclarationSpecifierSequence::downcast(declaration));
    if (declaration->runtimeDeclarationId() == FunctionDeclarationSpecifier::staticDeclarationId())
        return convert(FunctionDeclarationSpecifier::downcast(declaration));
    if (declaration->runtimeDeclarationId() == FunctionDefinitionMemberDeclaration::staticDeclarationId())
        return convert(FunctionDefinitionMemberDeclaration::downcast(declaration));
    if (declaration->runtimeDeclarationId() == IdentifierDestructorMethodName::staticDeclarationId())
        return convert(IdentifierDestructorMethodName::downcast(declaration));
    if (declaration->runtimeDeclarationId() == IdentifierMethodName::staticDeclarationId())
        return convert(IdentifierMethodName::downcast(declaration));
    if (declaration->runtimeDeclarationId() == OperatorMethodName::staticDeclarationId())
        return convert(OperatorMethodName::downcast(declaration));
    if (declaration->runtimeDeclarationId() == SimpleBlockDeclaration::staticDeclarationId())
        return convert(SimpleBlockDeclaration::downcast(declaration));
    if (declaration->runtimeDeclarationId() == SimpleDeclaration::staticDeclarationId())
        return convert(SimpleDeclaration::downcast(declaration));
    if (declaration->runtimeDeclarationId() == SpecifierMemberDeclaration::staticDeclarationId())
        return convert(SpecifierMemberDeclaration::downcast(declaration));
    if (declaration->runtimeDeclarationId() == TypeNameSimpleTypeSpecifier::staticDeclarationId())
        return convert(TypeNameSimpleTypeSpecifier::downcast(declaration));
    if (declaration->runtimeDeclarationId() == TypeDeclarationSpecifier::staticDeclarationId())
        return convert(TypeDeclarationSpecifier::downcast(declaration));

    BOOST_ASSERT(false);
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const DeclarationSpecifierSequenceSPtr& declaration)
{
    const std::vector<DeclarationSpecifierSPtr>& declarations = declaration->declarations();
    BOOST_ASSERT(declarations.size() >= 1);

    PassageSPtr passage = passageRef();
    for (std::vector<DeclarationSpecifierSPtr>::const_iterator it = declarations.begin(); it != declarations.end(); ++it)
    {
        if (it != declarations.begin())
            passage << (stringRef() << " ");
        passage << convert(*it);
    }
    return passage;
}

ElementSPtr FormatterStream::convert(const DeclaratorSPtr& declarator)
{
    if (declarator->runtimeDeclaratorId() == BodyFunctionDefinition::staticDeclaratorId())
        return convert(BodyFunctionDefinition::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == CVQualifierSequence::staticDeclaratorId())
        return convert(CVQualifierSequence::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == DeclaratorParameterDeclaration::staticDeclaratorId())
        return convert(DeclaratorParameterDeclaration::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == FunctionNameDeclaratorId::staticDeclaratorId())
        return convert(FunctionNameDeclaratorId::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == InitDeclarator::staticDeclaratorId())
        return convert(InitDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == DeclaratorIdDirectDeclarator::staticDeclaratorId())
        return convert(DeclaratorIdDirectDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == DeclaratorMemberDeclarator::staticDeclaratorId())
        return convert(DeclaratorMemberDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == NameDeclarator::staticDeclaratorId())
        return convert(NameDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == ParameterDeclarationClause::staticDeclaratorId())
        return convert(ParameterDeclarationList::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == ParameterDeclarationList::staticDeclaratorId())
        return convert(ParameterDeclarationClause::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == ParametersDirectDeclarator::staticDeclaratorId())
        return convert(ParametersDirectDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == PointerDeclarator::staticDeclaratorId())
        return convert(PointerDeclarator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == ReferencePointerOperator::staticDeclaratorId())
        return convert(ReferencePointerOperator::downcast(declarator));
    if (declarator->runtimeDeclaratorId() == TypeNameDeclaratorId::staticDeclaratorId())
        return convert(TypeNameDeclaratorId::downcast(declarator));

    BOOST_ASSERT(false);
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const DeclaratorMemberDeclaratorSPtr& declarator)
{
    return convert(declarator->declarator());
}

ElementSPtr FormatterStream::convert(const DeclarationMacroArgumentSPtr& parameter)
{
    return convert(parameter->declaration());
}

ElementSPtr FormatterStream::convert(const DeclaratorParameterDeclarationSPtr& declarator)
{
    PassageSPtr passage = passageRef();
    passage << convert(declarator->declaration());
    
    if (declarator->declarator()->runtimeDeclaratorId() != PointerDeclarator::staticDeclaratorId())
        passage << (stringRef() << " ");

    passage << convert(declarator->declarator());
    return passage;
}

ElementSPtr FormatterStream::convert(const DeclarationStatementSPtr& statement)
{
    PassageSPtr passage = passageRef();
    passage << convert(statement->declaration())
            << convert(statement->close())
            << endOfLineRef();
    return passage;
}

ElementSPtr FormatterStream::convert(const DeclaratorIdDirectDeclaratorSPtr& declarator)
{
    return convert(declarator->declarator());
}

ElementSPtr FormatterStream::convert(const EAccessSpecifier& specifier)
{
    return stringRef() << specifier.shortName();
}

ElementSPtr FormatterStream::convert(const EClassKey& key)
{
    return stringRef() << key.shortName();
}

ElementSPtr FormatterStream::convert(const ECVQualifier& qualifier)
{
    return stringRef() << qualifier.shortName();
}

ElementSPtr FormatterStream::convert(const EFunctionSpecifier& specifier)
{
    return stringRef() << specifier.shortName();
}

ElementSPtr FormatterStream::convert(const EOperator& operator_)
{
    switch (operator_.value())
    {
        case EOperator::kEqualTo:
            return stringRef() << "==";
        case EOperator::kNotEqualTo:
            return stringRef() << "!=";
        case EOperator::kLessThan:
            return stringRef() << "<";
    }
    
    BOOST_ASSERT(false);
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const ExpressionSPtr& expression)
{
    if (expression->runtimeExpressionId() == AdditiveShiftExpression::staticExpressionId())
        return convert(AdditiveShiftExpression::downcast(expression));
    if (expression->runtimeExpressionId() == CastPmExpression::staticExpressionId())
        return convert(CastPmExpression::downcast(expression));
    if (expression->runtimeExpressionId() == ClassNestedName::staticExpressionId())
        return convert(ClassNestedName::downcast(expression));
    if (expression->runtimeExpressionId() == CustomExpression::staticExpressionId())
        return convert(CustomExpression::downcast(expression));
    if (expression->runtimeExpressionId() == CustomIdExpression::staticExpressionId())
        return convert(CustomIdExpression::downcast(expression));
    if (expression->runtimeExpressionId() == ExpressionList::staticExpressionId())
        return convert(ExpressionList::downcast(expression));
    if (expression->runtimeExpressionId() == IdentifierUnqualifiedId::staticExpressionId())
        return convert(IdentifierUnqualifiedId::downcast(expression));
    if (expression->runtimeExpressionId() == IdExpressionPrimaryExpression::staticExpressionId())
        return convert(IdExpressionPrimaryExpression::downcast(expression));
    if (expression->runtimeExpressionId() == GrammarEqualityExpression::staticExpressionId())
        return convert(GrammarEqualityExpression::downcast(expression));
    if (expression->runtimeExpressionId() == MemberAccessPostfixExpression::staticExpressionId())
        return convert(MemberAccessPostfixExpression::downcast(expression));
    if (expression->runtimeExpressionId() == MultiplicativeAdditiveExpression::staticExpressionId())
        return convert(MultiplicativeAdditiveExpression::downcast(expression));
    if (expression->runtimeExpressionId() == NamespaceNestedName::staticExpressionId())
        return convert(NamespaceNestedName::downcast(expression));
    if (expression->runtimeExpressionId() == NestedNameSpecifier::staticExpressionId())
        return convert(NestedNameSpecifier::downcast(expression));
    if (expression->runtimeExpressionId() == ParenthesesPostfixExpression::staticExpressionId())
        return convert(ParenthesesPostfixExpression::downcast(expression));
    if (expression->runtimeExpressionId() == PmMultiplicativeExpression::staticExpressionId())
        return convert(PmMultiplicativeExpression::downcast(expression));
    if (expression->runtimeExpressionId() == PostfixUnaryExpression::staticExpressionId())
        return convert(PostfixUnaryExpression::downcast(expression));
    if (expression->runtimeExpressionId() == PrimaryExpressionPostfixExpression::staticExpressionId())
        return convert(PrimaryExpressionPostfixExpression::downcast(expression));
    if (expression->runtimeExpressionId() == RelationalEqualityExpression::staticExpressionId())
        return convert(RelationalEqualityExpression::downcast(expression));
    if (expression->runtimeExpressionId() == ShiftRelationalExpression::staticExpressionId())
        return convert(ShiftRelationalExpression::downcast(expression));
    if (expression->runtimeExpressionId() == UnaryCastExpression::staticExpressionId())
        return convert(UnaryCastExpression::downcast(expression));
    if (expression->runtimeExpressionId() == UnqualifiedIdExpression::staticExpressionId())
        return convert(UnqualifiedIdExpression::downcast(expression));
        
    BOOST_ASSERT(false);
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const ExpressionListSPtr& expressionList)
{
    ListSPtr list = listRef();
    list << List::ESquiggles::none();
    list << List::EDelimiter::comma();
    
    const std::vector<ExpressionSPtr>& expressions = expressionList->expressions();
    for (std::vector<ExpressionSPtr>::const_iterator it = expressions.begin(); it != expressions.end(); ++it)
        list << convert(*it);
    
    return list;
}

ElementSPtr FormatterStream::convert(const ExpressionMacroArgumentSPtr& parameter)
{
    return convert(parameter->expression());
}

ElementSPtr FormatterStream::convert(const ExpressionStatementSPtr& statement)
{
    PassageSPtr passage = passageRef();
    passage << convert(statement->expression())
            << (stringRef() << ";")
            << endOfLineRef();
    return passage;
}

ElementSPtr FormatterStream::convert(const FunctionDeclarationSpecifierSPtr& declaration)
{
    PassageSPtr passage = passageRef();
    passage << convert(declaration->specifier());
    return passage;
}

ElementSPtr FormatterStream::convert(const FunctionNameDeclaratorIdSPtr& declarator)
{
    return convert(declarator->functionName());
}

ElementSPtr FormatterStream::convert(const FunctionDefinitionMemberDeclarationSPtr& declaration)
{
    return convert(declaration->definition());
}

ElementSPtr FormatterStream::convert(const IdentifierUnqualifiedIdSPtr& expression)
{
    return convert(expression->identifier());
}

ElementSPtr FormatterStream::convert(const IdentifierSPtr& identifier)
{
     return stringRef() << identifier->value();
}

ElementSPtr FormatterStream::convert(const IdentifierClassNameSPtr& name)
{
    return convert(name->identifier());
}

ElementSPtr FormatterStream::convert(const IdentifierDestructorMethodNameSPtr& name)
{
    PassageSPtr passage = passageRef();
    passage << (stringRef() << "~")
            << convert(name->identifier());
    return passage;
}

ElementSPtr FormatterStream::convert(const IdentifierMethodNameSPtr& name)
{
    return convert(name->identifier());
}

ElementSPtr FormatterStream::convert(const IdentifierNamespaceNameSPtr& name)
{
    return convert(name->identifier());
}

ElementSPtr FormatterStream::convert(const IdExpressionPrimaryExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const InitDeclaratorSPtr& declarator)
{
    return convert(declarator->declarator());
}

ElementSPtr FormatterStream::convert(const OperatorFunctionIdSPtr& operator_)
{
    PassageSPtr passage = passageRef();
    passage << (stringRef() << "operator")
            << convert(operator_->operator_());
    return passage;
}

ElementSPtr FormatterStream::convert(const OperatorMethodNameSPtr& name)
{
    return convert(name->operator_());
}

ElementSPtr FormatterStream::convert(const GrammarEqualityExpressionSPtr& expression)
{
    PassageSPtr passage = passageRef();
    passage << convert(expression->first());
    switch (expression->type().value())
    {
        case EqualityExpression::EType::kEqualTo:
            passage << (stringRef() << " == ");
            break;
        case EqualityExpression::EType::kNotEqualTo:
            passage << (stringRef() << " != ");
            break;
        default:
            BOOST_ASSERT(false);
    }
    passage << convert(expression->second());
    return passage;
}

ElementSPtr FormatterStream::convert(const MacroNameSPtr& name)
{
    return stringRef() << name->value();
}

ElementSPtr FormatterStream::convert(const MacroArgumentSPtr& parameter)
{
    if (parameter->runtimeMacroArgumentId() == ExpressionMacroArgument::staticMacroArgumentId())
        return convert(ExpressionMacroArgument::downcast(parameter));
    if (parameter->runtimeMacroArgumentId() == DeclarationMacroArgument::staticMacroArgumentId())
        return convert(DeclarationMacroArgument::downcast(parameter));

    BOOST_ASSERT(false);
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const MacroStatementSPtr& macro)
{
    PassageSPtr passage = passageRef();
    passage << convert(macro->name());
    
    ListSPtr list = listRef();
    list << List::ESquiggles::parentheses();
    list << List::EDelimiter::comma();
    
    const std::vector<MacroArgumentSPtr>& parameters = macro->parameters();
    for (std::vector<MacroArgumentSPtr>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
        list << convert(*it);
        
    passage << list
            << convert(macro->close())
            << endOfLineRef();

    return passage;
}

ElementSPtr FormatterStream::convert(const MemberAccessPostfixExpressionSPtr& expression)
{
    PassageSPtr passage = passageRef();
    passage << convert(expression->first())
            << (stringRef() << ".")
            << convert(expression->second());
    return passage;
}

ElementSPtr FormatterStream::convert(const MemberSpecificationSPtr& specification)
{
    const std::vector<MemberSpecificationSectionSPtr>& sections = specification->sections();
    
    PassageSPtr passage = passageRef();
    for (std::vector<MemberSpecificationSectionSPtr>::const_iterator it = sections.begin(); it != sections.end(); ++it)
        passage << convert(*it);
    
    return passage;
}

ElementSPtr FormatterStream::convert(const MemberSpecificationSectionSPtr& section)
{
    PassageSPtr passage = passageRef();
    
    passage << (levelRef() << -1)
            << convert(section->accessSpecifier())
            << (stringRef() << ":")
            << endOfLineRef();
    
    const std::vector<MemberDeclarationSPtr>& declarations = section->declarations();
    for (std::vector<MemberDeclarationSPtr>::const_iterator it = declarations.begin(); it != declarations.end(); ++it)
    {
        passage << convert(*it)
                << (stringRef() << ";")
                << endOfLineRef();
    }
    
    return passage;
}

ElementSPtr FormatterStream::convert(const MultiplicativeAdditiveExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const NameDeclaratorSPtr& declarator)
{
    PassageSPtr passage = passageRef();
    passage << (stringRef() << declarator->name());
    return passage;
}

ElementSPtr FormatterStream::convert(const NamespaceNestedNameSPtr& expression)
{
    return convert(expression->name());
}

ElementSPtr FormatterStream::convert(const NestedNameSpecifierSPtr& expression)
{
    PassageSPtr passage = passageRef();
    passage << convert(expression->name())
            << (stringRef() << "::");
    return passage;
}

ElementSPtr FormatterStream::convert(const ParameterDeclarationListSPtr& declarator)
{
    ListSPtr list = listRef();
    list << List::ESquiggles::parentheses()
         << List::EDelimiter::comma();

    if (declarator)
    {
        const std::vector<ParameterDeclarationSPtr>& declarators = declarator->declarators();
        for (std::vector<ParameterDeclarationSPtr>::const_iterator it = declarators.begin(); it != declarators.end(); ++it)
            list << convert(*it);
    }
    
    return list;
}

ElementSPtr FormatterStream::convert(const ParameterDeclarationClauseSPtr& declarator)
{
    if (declarator)
        return convert(declarator->list());
    return convert(ParameterDeclarationListSPtr());
}

ElementSPtr FormatterStream::convert(const ParametersDirectDeclaratorSPtr& declarator)
{
    PassageSPtr passage = passageRef();
    passage << convert(declarator->declarator())
            << convert(declarator->parameters());
    if (declarator->qualifier())
    {
        passage << (stringRef() << " ")
                << convert(declarator->qualifier());
    }
    return passage;
}

ElementSPtr FormatterStream::convert(const ParenthesesPostfixExpressionSPtr& expression)
{
    PassageSPtr passage = passageRef();
    passage << convert(expression->expression())
            << (stringRef() << "(");
    if (expression->list())
        passage << convert(expression->list());
    passage << (stringRef() << ")");
    return passage;
}

ElementSPtr FormatterStream::convert(const PmMultiplicativeExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const PointerDeclaratorSPtr& declarator)
{
    PassageSPtr passage = passageRef();
    passage << convert(declarator->operator_())
            << convert(declarator->declarator());
    return passage;
}

ElementSPtr FormatterStream::convert(const PostfixUnaryExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const PrimaryExpressionPostfixExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const RelationalEqualityExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const ReferencePointerOperatorSPtr& expression)
{
    if (mConfiguration->mPointerPosition == config::cpp::EPointerPosition::withTheType())
        return stringRef() << "& ";
    if (mConfiguration->mPointerPosition == config::cpp::EPointerPosition::withTheName())
        return stringRef() << " &";
    BOOST_ASSERT(false);
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const ShiftRelationalExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const SimpleBlockDeclarationSPtr& declaration)
{
    return convert(declaration->declaration());
}

ElementSPtr FormatterStream::convert(const SimpleDeclarationSPtr& declaration)
{
    BOOST_ASSERT(declaration->declaration() || declaration->declarator());

    PassageSPtr passage = passageRef();
    if (declaration->declaration())
    {
        passage << convert(declaration->declaration())
                << (stringRef() << " ");
    }
    if (declaration->declarator())
        passage << convert(declaration->declarator());
    return passage;
}

ElementSPtr FormatterStream::convert(const SpecifierMemberDeclarationSPtr& declaration)
{
    PassageSPtr passage = passageRef();
    passage << convert(declaration->specifier())
            << (stringRef() << " ")
            << convert(declaration->declarator());
    return passage;
}

ElementSPtr FormatterStream::convert(const StatementSPtr& statement)
{
    if (statement->runtimeStatementId() == CompoundStatement::staticStatementId())
        return convert(CompoundStatement::downcast(statement));
    if (statement->runtimeStatementId() == ExpressionStatement::staticStatementId())
        return convert(ExpressionStatement::downcast(statement));
    if (statement->runtimeStatementId() == DeclarationStatement::staticStatementId())
        return convert(DeclarationStatement::downcast(statement));
    if (statement->runtimeStatementId() == MacroStatement::staticStatementId())
        return convert(MacroStatement::downcast(statement));
         
    BOOST_ASSERT(false);
    return ElementSPtr();
}

ElementSPtr FormatterStream::convert(const Statement::EClose& close)
{
    return stringRef() << ((close == Statement::EClose::yes()) ? ";" : "");
}

ElementSPtr FormatterStream::convert(const TypeDeclarationSpecifierSPtr& declaration)
{
    return convert(declaration->declaration());
}

ElementSPtr FormatterStream::convert(const TypeNameDeclaratorIdSPtr& declarator)
{
    PassageSPtr passage = passageRef();
    if (declarator->spacifier())
        passage << convert(declarator->spacifier());
    passage << convert(declarator->typeName());
    return passage;
}

ElementSPtr FormatterStream::convert(const TypeNameSimpleTypeSpecifierSPtr& declaration)
{
    PassageSPtr passage = passageRef();
    if (declaration->specifier())
        passage << convert(declaration->specifier());
    passage << convert(declaration->typeName());
    return passage;
}

ElementSPtr FormatterStream::convert(const UnaryCastExpressionSPtr& expression)
{
    return convert(expression->expression());
}

ElementSPtr FormatterStream::convert(const UnqualifiedIdExpressionSPtr& expression)
{
    return convert(expression->unqualifiedId());
}

FormatterStream& FormatterStream::operator<<(const StatementSPtr& statement)
{
    mAligner << (passageRef() << convert(statement));
    return *this;
}

FormatterStream& FormatterStream::operator<<(const ClassSpecifierSPtr& specifier)
{
    mAligner << (passageRef() << convert(specifier));
    return *this;
}

FormatterStream& FormatterStream::operator<<(const EndOfLineSPtr& endl)
{
    mAligner << (passageRef() << endl);
    return *this;
}
