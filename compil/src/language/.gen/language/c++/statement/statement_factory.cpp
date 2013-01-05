// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/statement/statement_factory.h"

namespace lang
{

namespace cpp
{

EStatementId::EStatementId()
        : mValue(kInvalid)
{
}

EStatementId::EStatementId(long value)
        : mValue(value)
{
}

const EStatementId EStatementId::invalid()
{
    return EStatementId(kInvalid);
}

const EStatementId EStatementId::compoundStatement()
{
    return EStatementId(kCompoundStatement);
}

const EStatementId EStatementId::declarationStatement()
{
    return EStatementId(kDeclarationStatement);
}

const EStatementId EStatementId::expressionStatement()
{
    return EStatementId(kExpressionStatement);
}

const EStatementId EStatementId::macroStatement()
{
    return EStatementId(kMacroStatement);
}

const EStatementId EStatementId::statement()
{
    return EStatementId(kStatement);
}

const EStatementId EStatementId::throwTestStatement()
{
    return EStatementId(kThrowTestStatement);
}

const EStatementId EStatementId::unaryTestStatement()
{
    return EStatementId(kUnaryTestStatement);
}

const EStatementId EStatementId::variableDeclarationStatement()
{
    return EStatementId(kVariableDeclarationStatement);
}

long EStatementId::value() const
{
    return mValue;
}

const char* EStatementId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "CompoundStatement",
        "DeclarationStatement",
        "ExpressionStatement",
        "MacroStatement",
        "Statement",
        "ThrowTestStatement",
        "UnaryTestStatement",
        "VariableDeclarationStatement",
    };
    return names[(size_t)value];
}

const char* EStatementId::shortName() const
{
    return shortName(value());
}

bool EStatementId::operator==(const EStatementId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EStatementId::operator!=(const EStatementId& rValue) const
{
    return mValue != rValue.mValue;
}

EStatementId CompoundStatement::staticStatementId()
{
    return EStatementId::compoundStatement();
}

EStatementId CompoundStatement::runtimeStatementId() const
{
    return staticStatementId();
}

EStatementId DeclarationStatement::staticStatementId()
{
    return EStatementId::declarationStatement();
}

EStatementId DeclarationStatement::runtimeStatementId() const
{
    return staticStatementId();
}

EStatementId ExpressionStatement::staticStatementId()
{
    return EStatementId::expressionStatement();
}

EStatementId ExpressionStatement::runtimeStatementId() const
{
    return staticStatementId();
}

EStatementId MacroStatement::staticStatementId()
{
    return EStatementId::macroStatement();
}

EStatementId MacroStatement::runtimeStatementId() const
{
    return staticStatementId();
}

EStatementId Statement::staticStatementId()
{
    return EStatementId::statement();
}

EStatementId Statement::runtimeStatementId() const
{
    return staticStatementId();
}

EStatementId ThrowTestStatement::staticStatementId()
{
    return EStatementId::throwTestStatement();
}

EStatementId ThrowTestStatement::runtimeStatementId() const
{
    return staticStatementId();
}

EStatementId UnaryTestStatement::staticStatementId()
{
    return EStatementId::unaryTestStatement();
}

EStatementId UnaryTestStatement::runtimeStatementId() const
{
    return staticStatementId();
}

EStatementId VariableDeclarationStatement::staticStatementId()
{
    return EStatementId::variableDeclarationStatement();
}

EStatementId VariableDeclarationStatement::runtimeStatementId() const
{
    return staticStatementId();
}

StatementSPtr StatementFactory::clone(const StatementSPtr& pObject)
{
    switch (pObject->runtimeStatementId().value())
    {
        case EStatementId::kCompoundStatement:
        {
            CompoundStatementSPtr pClone(new CompoundStatement());
            *pClone = *downcastCompoundStatement(pObject);
            return pClone;
        }
        case EStatementId::kDeclarationStatement:
        {
            DeclarationStatementSPtr pClone(new DeclarationStatement());
            *pClone = *downcastDeclarationStatement(pObject);
            return pClone;
        }
        case EStatementId::kExpressionStatement:
        {
            ExpressionStatementSPtr pClone(new ExpressionStatement());
            *pClone = *downcastExpressionStatement(pObject);
            return pClone;
        }
        case EStatementId::kMacroStatement:
        {
            MacroStatementSPtr pClone(new MacroStatement());
            *pClone = *downcastMacroStatement(pObject);
            return pClone;
        }
        case EStatementId::kStatement:
        {
            StatementSPtr pClone(new Statement());
            *pClone = *pObject;
            return pClone;
        }
        case EStatementId::kThrowTestStatement:
        {
            ThrowTestStatementSPtr pClone(new ThrowTestStatement());
            *pClone = *downcastThrowTestStatement(pObject);
            return pClone;
        }
        case EStatementId::kUnaryTestStatement:
        {
            UnaryTestStatementSPtr pClone(new UnaryTestStatement());
            *pClone = *downcastUnaryTestStatement(pObject);
            return pClone;
        }
        case EStatementId::kVariableDeclarationStatement:
        {
            VariableDeclarationStatementSPtr pClone(new VariableDeclarationStatement());
            *pClone = *downcastVariableDeclarationStatement(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return StatementSPtr();
}

CompoundStatementSPtr StatementFactory::downcastCompoundStatement(const StatementSPtr& pObject)
{
    bool b = (pObject->runtimeStatementId() == CompoundStatement::staticStatementId());

    if (b)
        return boost::static_pointer_cast<CompoundStatement>(pObject);
    return CompoundStatementSPtr();
}

DeclarationStatementSPtr StatementFactory::downcastDeclarationStatement(const StatementSPtr& pObject)
{
    bool b = (pObject->runtimeStatementId() == DeclarationStatement::staticStatementId());

    if (b)
        return boost::static_pointer_cast<DeclarationStatement>(pObject);
    return DeclarationStatementSPtr();
}

ExpressionStatementSPtr StatementFactory::downcastExpressionStatement(const StatementSPtr& pObject)
{
    bool b = (pObject->runtimeStatementId() == ExpressionStatement::staticStatementId());

    if (b)
        return boost::static_pointer_cast<ExpressionStatement>(pObject);
    return ExpressionStatementSPtr();
}

MacroStatementSPtr StatementFactory::downcastMacroStatement(const StatementSPtr& pObject)
{
    bool b = (pObject->runtimeStatementId() == MacroStatement::staticStatementId());

    if (b)
        return boost::static_pointer_cast<MacroStatement>(pObject);
    return MacroStatementSPtr();
}

ThrowTestStatementSPtr StatementFactory::downcastThrowTestStatement(const StatementSPtr& pObject)
{
    bool b = (pObject->runtimeStatementId() == ThrowTestStatement::staticStatementId());

    if (b)
        return boost::static_pointer_cast<ThrowTestStatement>(pObject);
    return ThrowTestStatementSPtr();
}

UnaryTestStatementSPtr StatementFactory::downcastUnaryTestStatement(const StatementSPtr& pObject)
{
    bool b = (pObject->runtimeStatementId() == UnaryTestStatement::staticStatementId());

    if (b)
        return boost::static_pointer_cast<UnaryTestStatement>(pObject);
    return UnaryTestStatementSPtr();
}

VariableDeclarationStatementSPtr StatementFactory::downcastVariableDeclarationStatement(const StatementSPtr& pObject)
{
    bool b = (pObject->runtimeStatementId() == VariableDeclarationStatement::staticStatementId());

    if (b)
        return boost::static_pointer_cast<VariableDeclarationStatement>(pObject);
    return VariableDeclarationStatementSPtr();
}

}

}

