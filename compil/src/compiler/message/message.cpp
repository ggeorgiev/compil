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

#include "message.h"

namespace compil
{

const char* Message::t_unterminatedComment = 
    "Unterminated comment";

const char* Message::t_invalidIntegerLiteral =
    "Invalid integer constant";

const char* Message::t_missingTerminatingQuotationMark =
    "Missing terminating quotation mark";

const char* Message::t_newLineBeforeTerminatingQuotationMark =
    "String literals cannot cross line boundaries";

const char* Message::t_unknownEscapeSequence =
    "Unknown escape sequence";


const char* Message::p_expectImportSource =
    "expect import source";
    
const char* Message::p_importWithoutSourceProvider = 
    "import statment used in parser session without source provider specified";
    
const char* Message::p_sourceNotFound = 
    "source not found";   
  
const char* Message::p_openSourceFailed = 
    "open source failed"; 

// TODO: this message is unique for CompIL. It will cause a lot of confision
// it will need to provide a lot of details what it exactly means
const char* Message::p_misplacedComment = 
    "The comment will be not assigned to any descriptor statement";

const char* Message::p_unknownStatment = 
    "Unknown %context% statement. It should be one of:\n"
    "    %options%";
    
const char* Message::p_expectStatementName = 
    "Expected %statement% name";

const char* Message::p_expectClassifierStatementName = 
    "Expected %classifier% %statement% name";
    
const char* Message::p_expectStatementBody = 
    "Expected %statement% body";
    
const char* Message::p_expectKeyword = 
    "Expected %keyword% keyword";

const char* Message::p_unexpectEOFInStatementBody =
    "Unexpected eof before the %statement% body is closed";  
    
const char* Message::p_unknownClassifierType =
    "Unknown %classifier% type %type%";
    
const char* Message::p_expectBaseStructureFieldName =
    "Expected base struct field name";

const char* Message::p_expectFieldDefaultValue =
    "Expected default value";

const char* Message::p_expectType =
    "Expected %classifier% type";
 
const char* Message::p_expectAppropriateType =
    "Expected %classifier% type to be %options%";
    
const char* Message::p_expectSemicolon = 
    "Expected ';' semicolon";
    
const char* Message::p_expectAssignmentOperator = 
    "Expected '=' assignment operator";
    
const char* Message::p_expectSemicolonOrAssignmentOperator = 
    "Expected ';' semicolon or '=' assignment operator";
    
const char* Message::p_unexpectedStatmentModificator =
    "This statement can not be declared as %modificator%";

const char* Message::p_expectClosingAngleBracket =
    "Expect closing angle bracket";
    
const char* Message::p_nonByReferenceFieldDefaultWithNull =
    "Only field aggregated by reference could have null default value";
    
const char* Message::p_filterInNonObjectFactory =
    "Only object factory accepts filters";

const char* Message::p_filterInFactoryForNonStructure =
    "Only structure parameter type factory accepts filters";
    
const char* Message::p_asteriskPackageElement =
    "Asterisk package element can not be resolved";

const char* Message::v_unacceptableParameterType =
    "Unacceptable %statement% parameter type. It should be\n"
    "    %options%";

const char* Message::v_notUnique =
    "The %classifier% %statement% is not unique";

const char* Message::v_partualObjectInNonPartialGenerator =
    "An partial %statement% is not alowed in generation type %generator-type%";

const char* Message::v_baseStructureMustBeSharableForSharableStructure =
    "The base structure of a sharable structure must be shrable too";
    

Message::Message(Severity severity, const std::string& text,
                 const SourceIdSPtr& pSourceId, int line, int column)
        : mSeverity(severity)
        , mText(text)
        , mpSourceId(pSourceId)
        , mLine(line)
        , mColumn(column)
{
}

Message::~Message()
{
}

Message::Argument::Argument(const std::string& name, const std::string& value)
        : mName(name)
        , mValue(value)
{
}

Message::Severity Message::severity() const
{
    return mSeverity;
}

std::string Message::text() const
{
    return mText;
}

SourceIdSPtr Message::sourceId() const
{
    return mpSourceId;
}

int Message::line() const
{
    return mLine;
}

int Message::column() const
{
    return mColumn;
}

static bool replace(std::string &target, const std::string &that, const std::string &with)
{
    std::string::size_type where = target.find(that);
    if (where == std::string::npos)
        return false;
        
    target.replace(target.begin() + where, target.begin() + where + that.size(), with.begin(), with.end());
	return true;
}

Message& Message::operator<<(const Argument& argument)
{
    replace(mText, "%" + argument.mName + "%", argument.mValue);
    return *this;
}

bool Message::operator== (const Message& rValue) const
{
    if (severity() != rValue.severity()) return false;
    if (sourceId() != rValue.sourceId()) return false; 
    if (line() != rValue.line()) return false;
    if (column() != rValue.column()) return false;
    if (text() != rValue.text()) return false;
    return true;
}


}
