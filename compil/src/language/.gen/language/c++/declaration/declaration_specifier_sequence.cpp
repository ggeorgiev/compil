// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/declaration/declaration_specifier_sequence.h"

namespace lang
{

namespace cpp
{

DeclarationSpecifierSequence::DeclarationSpecifierSequence()
{
}

DeclarationSpecifierSequence::~DeclarationSpecifierSequence()
{
}

DeclarationSpecifierSequenceSPtr DeclarationSpecifierSequence::downcast(const DeclarationSPtr& object)
{
    return boost::static_pointer_cast<DeclarationSpecifierSequence>(object);
}

const std::vector<DeclarationSpecifierSPtr>& DeclarationSpecifierSequence::declarations() const
{
    return mDeclarations;
}

DeclarationSpecifierSequence& DeclarationSpecifierSequence::set_declarations(const std::vector<DeclarationSpecifierSPtr>& declarations)
{
    mDeclarations = declarations;
    return *this;
}

std::vector<DeclarationSpecifierSPtr>& DeclarationSpecifierSequence::mutable_declarations()
{
    return mDeclarations;
}

DeclarationSpecifierSequence& DeclarationSpecifierSequence::operator<<(const std::vector<DeclarationSpecifierSPtr>& declarations)
{
    return set_declarations(declarations);
}

const DeclarationSpecifierSequenceSPtr& operator<<(const DeclarationSpecifierSequenceSPtr& object,
                                                   const std::vector<DeclarationSpecifierSPtr>& declarations)
{
    BOOST_ASSERT(object);
    *object << declarations;
    return object;
}

DeclarationSpecifierSequence& DeclarationSpecifierSequence::operator<<(const DeclarationSpecifierSPtr& declarationsItem)
{
    mDeclarations.push_back(declarationsItem);
    return *this;
}

const DeclarationSpecifierSequenceSPtr& operator<<(const DeclarationSpecifierSequenceSPtr& object,
                                                   const DeclarationSpecifierSPtr& declarationsItem)
{
    BOOST_ASSERT(object);
    *object << declarationsItem;
    return object;
}

}

}

