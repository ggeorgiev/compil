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
#include "table_aligner.h"
#include "line_aligner.h"

#include <boost/algorithm/string.hpp>

#include <assert.h>

namespace compil
{

TableCeil::TableCeil()
{
}

TableCeil::~TableCeil()
{
}

TableAligner::TableAligner(const AlignerConfigurationSPtr& pConfig) 
	: Aligner(pConfig)
{
}

TableAligner::~TableAligner()
{
}

bool TableAligner::isEmpty() const
{
	if (mTable.size() == 0) return true;
	if (mTable[0].size() == 0) return true;
	return false;
}

struct dereferencable_bool
{
    dereferencable_bool()
    {
    }
    
    dereferencable_bool(bool b) : val(b)
    {
    }

    operator bool() 
    {
        return val;
    }
private:
    bool val;
};

std::string TableAligner::str(int indent) const
{
	std::vector<size_t> width;
    std::vector<dereferencable_bool> vSplit(mTable.size(), false);
	std::vector<Row>::const_iterator rit;
    size_t r = 0;
	for (rit = mTable.begin(); rit != mTable.end(); ++rit, ++r)
	{
		const Row& row = *rit;
        if (row.mType != Row::normal) continue;
        
        size_t row_length = 0;
        
		for (size_t i = 0; i < row.size(); ++i)
		{
			const TableCeilSPtr& pTableCeil = row[i];
			size_t len = pTableCeil->str().length();
            row_length += len;
			if (width.size() <= i)
				width.push_back(0);
        }
        
        bool too_long = row_length > (size_t)mConfiguration->mColumnWidthLimit;
        vSplit[r] = too_long;
                
		for (size_t i = 0; i < row.size(); ++i)
		{
			const TableCeilSPtr& pTableCeil = row[i];
            size_t len = pTableCeil->str().length();
            if (too_long && pTableCeil->mOptionalNewLineColumns.size() > 0)
            {
                size_t plen = pTableCeil->mOptionalNewLineColumns[0];
                for (size_t j = 1; j < pTableCeil->mOptionalNewLineColumns.size(); ++j)
                {
                    size_t clen = pTableCeil->mOptionalNewLineColumns[j] -
                                  pTableCeil->mOptionalNewLineColumns[j - 1];
                    if (plen < clen)
                        plen = clen;
                }
                size_t clen = len - *pTableCeil->mOptionalNewLineColumns.rbegin();
                if (plen < clen)
                    plen = clen;
                    
                len = plen;
            }
            if (width[i] < len)
                width[i] = len;
		}
	}

	std::ostringstream out;
    r = 0;
	for (rit = mTable.begin(); rit != mTable.end(); ++rit, ++r)
	{
		LineAlignerPtr aligner(new LineAligner(mConfiguration));
		const Row& row = *rit;
        if (row.mType == Row::comment)
        {
            const OSStreamPtr& pStream = *row.begin();
            out << aligner->comment(indent + row.mIndent, pStream->str());
        }
        else
        {
            size_t length = 0;
            size_t pos = 0;
            int i = 0;
            std::vector<TableCeilSPtr>::const_iterator sit;
            for (sit = row.begin(); sit != row.end(); ++sit, ++i)
            {
                *aligner << std::string(pos - length, ' ');
                const TableCeilSPtr& pTableCeil = *sit;
                std::string field = pTableCeil->str();
                
                if (vSplit[r] && (pTableCeil->mOptionalNewLineColumns.size() > 0))
                {
                    std::string pfield = field.substr(0, pTableCeil->mOptionalNewLineColumns[0]);
                    boost::trim(pfield);
                    *aligner << pfield;
                    out << aligner->str(indent);
                    aligner.reset(new LineAligner(mConfiguration));
                    *aligner << std::string(pos, ' ');
                    for (size_t j = 1; j < pTableCeil->mOptionalNewLineColumns.size(); ++j)
                    {
                        pfield = field.substr(pTableCeil->mOptionalNewLineColumns[j - 1], 
                                              pTableCeil->mOptionalNewLineColumns[j] - 
                                              pTableCeil->mOptionalNewLineColumns[j - 1]);
                        boost::trim(pfield);
                        *aligner << pfield;
                        out << aligner->str(indent + row.mIndent);
                        aligner.reset(new LineAligner(mConfiguration));
                        *aligner << std::string(pos, ' ');
                    }
                    pfield = field.substr(*pTableCeil->mOptionalNewLineColumns.rbegin());
                    boost::trim(pfield);
                    *aligner << pfield;
                    length = pos + pfield.length();
                }
                else
                {
                    boost::trim(field);
                    *aligner << field;
                    length = pos + field.length();
                }
                pos += width[i];
            }
            out << aligner->str(indent + row.mIndent);
        }
	}
	return out.str();
}

TableCeil& TableAligner::ceil() 
{
	assert(pCurrent);
	return *pCurrent;
}

void TableAligner::newColumn()
{
	pCurrent.reset(new TableCeil());
	mTable.rbegin()->push_back(pCurrent);
}

void TableAligner::newRow(Row::Type type, int indent)
{
	mTable.push_back(Row(type, indent));
	newColumn();
}

TableAligner& operator<<(TableAligner& aligner, const TableAligner::col&)
{
	aligner.newColumn();
	return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const TableAligner::row&)
{
	aligner.newRow();
	return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const TableAligner::row_line& row_line)
{
    aligner.newRow(TableAligner::Row::line, row_line.mIndent);
	return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const TableAligner::row_comment&)
{
    aligner.newRow(TableAligner::Row::comment);
	return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const TableAligner::optional_new_line&)
{
    aligner.ceil().mOptionalNewLineColumns.push_back(aligner.ceil().str().size());
	return aligner;
}

static TableAligner& serialize(TableAligner& aligner, const cpp::frm::TypeSPtr& type, bool align, bool space)
{
    if (!type)
        return aligner;

    if (type->declaration() != cpp::frm::ETypeDeclaration::invalid())
        aligner << type->declaration() << ' ';

    if (type->namespace_())
    if (!type->namespace_()->isVoid())
        aligner << type->namespace_() << "::";
    
    aligner << type->name();
        
	if (aligner.mConfiguration->mDecoration == AlignerConfiguration::part_of_the_type)
	{
        if (type->decoration() != cpp::frm::ETypeDecoration::invalid())
            aligner << type->decoration();
        if (space)
            aligner << ' ';
        if (align)
            aligner << TableAligner::col();
	}
	else if (aligner.mConfiguration->mDecoration == AlignerConfiguration::part_of_the_name)
	{
        if (space)
            aligner << ' ';
        if (align)
            aligner << TableAligner::col();
        if (type->decoration() != cpp::frm::ETypeDecoration::invalid())
            aligner << type->decoration();
	}
	else if (aligner.mConfiguration->mDecoration == AlignerConfiguration::next_to_the_name)
	{
        if (space)
            aligner << ' ';
        if (align)
            aligner << TableAligner::col();
        if (type->decoration() != cpp::frm::ETypeDecoration::invalid())
            aligner << type->decoration();
        if (align)
            aligner << TableAligner::col();
	}
    else
    {
        assert(false && "unknown decoration");
    }
	return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::ArgumentSPtr& argument)
{
    if (argument->type())
        serialize(aligner, argument->type(), false, true);
    aligner << argument->name();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::CommentSPtr& comment)
{
    if (!comment)
        return aligner;
        
    std::vector<std::string> paragraphs = comment->paragraphs();
    std::vector<std::string>::iterator it;
    for (it = paragraphs.begin(); it != paragraphs.end(); ++it)
    {
        aligner << TableAligner::row_comment()
                << *it;
    }
    
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::CastOperatorSPtr& castOperator)
{
    aligner << castOperator->comment();
    
    aligner << TableAligner::row();

    aligner << TableAligner::col();
    
    if (castOperator->namespace_())
    {
        aligner << castOperator->namespace_()
                << "::";
    }
    aligner << "operator ";
    serialize(aligner, castOperator->type(), false, true);
    
    aligner << Aligner::FunctionSpace()
            << "("
            << TableAligner::col()
            << ")";
    
    if (castOperator->declaration() != cpp::frm::EMethodDeclaration::invalid())
    {
        aligner << ' '
                << TableAligner::col()
                << castOperator->declaration();
    }
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::ConstructorNameSPtr& name)
{
    if (name)
        aligner << name->value();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::EConstructorSpecifier& constructorSpecifier)
{
    if (constructorSpecifier != cpp::frm::EConstructorSpecifier::invalid())
    {
        aligner << constructorSpecifier.shortName()
                << ' ';
    }
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::ConstructorSPtr& constructor)
{
    aligner << constructor->comment();
    
    aligner << TableAligner::row();

    aligner << constructor->specifier();
        
    aligner << TableAligner::col();
    aligner << TableAligner::col();
    if (aligner.mConfiguration->mDecoration == AlignerConfiguration::next_to_the_name)
        aligner << TableAligner::col();
        
    if (constructor->namespace_())
    {
        aligner << constructor->namespace_()
                << "::";
    }
    aligner << constructor->name();
    
    aligner << Aligner::FunctionSpace();
    aligner << "("
            << TableAligner::col();
    if (constructor->arguments().size() > 0)
        aligner << constructor->arguments()[0];
    for (size_t i = 1; i < constructor->arguments().size(); ++i)
        aligner << ", " << constructor->arguments()[i];
    aligner << ")";
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::EDestructorSpecifier& destructorSpecifier)
{
    if (destructorSpecifier != cpp::frm::EDestructorSpecifier::invalid())
    {
        if (destructorSpecifier == cpp::frm::EDestructorSpecifier::lax())
            aligner << "/*lax*/";
        else
            aligner << destructorSpecifier.shortName();
    
        aligner << ' ';
    }
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::DestructorSPtr& destructor)
{
    aligner << destructor->comment();
    
    aligner << TableAligner::row();
    
    aligner << destructor->specifier();
        
    aligner << TableAligner::col();
    aligner << TableAligner::col();
    
    if (destructor->namespace_())
    {
        aligner << destructor->namespace_()
                << "::";
    }
    aligner << '~';
    if (aligner.mConfiguration->mDecoration == AlignerConfiguration::next_to_the_name)
        aligner << TableAligner::col();
    aligner << destructor->name();
    aligner << Aligner::FunctionSpace();
    aligner << "("
            << TableAligner::col()
            << ")";
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::FunctionCallSPtr& function)
{
    if (function->namespace_())
        aligner << function->namespace_() << "::";
    aligner << function->name() << Aligner::FunctionSpace();
    aligner << "(";
    if (function->parameters().size() > 0)
        aligner << function->parameters()[0];
    for (size_t i = 1; i < function->parameters().size(); ++i)
        aligner << ", " << function->parameters()[i];
    aligner << ")";
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::FunctionNameSPtr& name)
{
    if (name)
        aligner << name->value();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::FunctionSPtr& function)
{
    aligner << TableAligner::col();

    serialize(aligner, function->return_(), true, true);
    
    aligner << function->name();
        
    aligner << Aligner::FunctionSpace();
    aligner << "("
            << TableAligner::col();

    if (function->arguments().size() > 0)
        aligner << function->arguments()[0];
    for (size_t i = 1; i < function->arguments().size(); ++i)
    {
        aligner << ","
                << TableAligner::optional_new_line()
                << " "
                << function->arguments()[i];
    }
    aligner << ")";

    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::InitializationSPtr& initialization)
{
    BOOST_ASSERT(!initialization->variableName() != !initialization->constructorName());

    if (initialization->variableName())
        aligner << initialization->variableName();
    else
        aligner << initialization->constructorName();

    aligner << Aligner::FunctionSpace()
            << "("
            << initialization->parameter()
            << ")";
            
    return aligner;
}


TableAligner& operator<<(TableAligner& aligner, const cpp::frm::EMethodDeclaration& declaration)
{
    if (declaration != cpp::frm::EMethodDeclaration::invalid())
        aligner << declaration.shortName();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::EMethodSpecifier& methodSpecifier)
{
    if (methodSpecifier != cpp::frm::EMethodSpecifier::invalid())
    {
        aligner << methodSpecifier.shortName()
                << ' ';
    }
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::MethodSPtr& method)
{
    aligner << method->comment();
    
    aligner << TableAligner::row();
    
    aligner << method->specifier();
    aligner << TableAligner::col();

    serialize(aligner, method->return_(), true, true);

    if (method->namespace_())
    {
        aligner << method->namespace_()
                << "::";
    }

    aligner << method->name();

    aligner << Aligner::FunctionSpace();
    aligner << "("
            << TableAligner::col();

    if (method->arguments().size() > 0)
        aligner << method->arguments()[0];
    for (size_t i = 1; i < method->arguments().size(); ++i)
    {
        aligner << ","
                << TableAligner::optional_new_line()
                << " "
                << method->arguments()[i];
    }
    aligner << ")";
    
    if (method->declaration() != cpp::frm::EMethodDeclaration::invalid())
    {
        aligner << ' '
                << TableAligner::col()
                << method->declaration();
    }

    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::NamespaceNameSPtr& name)
{
    if (name)
        aligner << name->value();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::NamespaceSPtr& namespace_)
{
    if (namespace_)
    {
        const std::vector<cpp::frm::NamespaceNameSPtr>& names = namespace_->names();
        if (names.size() > 0)
            aligner << names[0];
        for (size_t i = 1; i < names.size(); ++i)
        {
            aligner << "::"
                    << names[i];
        }
    }
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::ParameterValueSPtr& parameter)
{
    if (parameter)
        aligner << parameter->value();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::ETypeDeclaration& declaration)
{
    if (declaration != cpp::frm::ETypeDeclaration::invalid())
        aligner << declaration.shortName();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::ETypeDecoration& decoration)
{
    switch (decoration.value())
    {
        case cpp::frm::ETypeDecoration::kPointer:
            aligner << '*';
            break;
        case cpp::frm::ETypeDecoration::kReference:
            aligner << '&';
            break;
        default:
            BOOST_ASSERT(false && "unknown type decoration");
    }

    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::TypeNameSPtr& name)
{
    if (name)
        aligner << name->value();
    return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::TypeSPtr& type)
{
    return serialize(aligner, type, false, false);
}

TableAligner& operator<<(TableAligner& aligner, const cpp::frm::VariableNameSPtr& name)
{
    if (name)
        aligner << name->value();
    return aligner;
}


TableAligner& operator<<(TableAligner& aligner, const Aligner::FunctionSpace&)
{
    if (aligner.mConfiguration->mFunctionSpace)
        aligner << ' ';
    aligner << TableAligner::col();
	return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const Aligner::FunctionDefinitionTypeSpace&)
{
    if (aligner.mConfiguration->mFunctionTypeOnNewLine)
        aligner << TableAligner::row();
    else
        aligner << ' ';
	return aligner;
}


TableAligner& operator<<(TableAligner& aligner, char ch)
{
	aligner.ceil() << ch;
	return aligner;
}

TableAligner& operator<<(TableAligner& aligner, const std::string& str)
{
	aligner.ceil() << str;
	return aligner;
}

}
