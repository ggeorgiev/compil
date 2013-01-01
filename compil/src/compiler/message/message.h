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


#ifndef _COMPIL_MESSAGE_H__
#define _COMPIL_MESSAGE_H__

#include "namespace_alias.h"

#include "compil/document/document.h"
#include "compil/document/object_factory.h"

#include <string>

namespace compil
{

class Message
{
public:
    struct Argument
    {
    protected:
        Argument(const std::string& name, const std::string& value);
    public:
        std::string mName;
        std::string mValue;
    };
    
    
    struct Context : public Argument
    {
        Context(const std::string& value) : Argument("context", value) {}
    };
    
    struct Modificator : public Argument
    {
        Modificator(const std::string& value) : Argument("modificator", value) {}
    };
    
    struct Classifier : public Argument
    {
        Classifier(const std::string& value) : Argument("classifier", value) {}
    };
    
    struct Identifier : public Argument
    {
        Identifier(const std::string& value) : Argument("identifier", value) {}
    };
    
    struct Keyword : public Argument
    {
        Keyword(const std::string& value) : Argument("keyword", value) {}
    };
    
    struct Language : public Argument
    {
        Language(const std::string& value) : Argument("language", value) {}
    };
    
    struct Compiler : public Argument
    {
        Compiler(const std::string& value) : Argument("compiler", value) {}
    };
    
    struct Options : public Argument
    {
        Options(const std::string& value) : Argument("options", value) {}
    };
    
    struct Statement : public Argument
    {
        Statement(const std::string& value) : Argument("statement", value) {}
        Statement(const EObjectId& objectId) : Argument("statement", "") 
        {
            switch (objectId.value())
            {
                case EObjectId::kEnumeration:
                    mValue = "enumeration";
                    break;
                case EObjectId::kIdentifier:
                    mValue = "identifier";
                    break;
                default:
                    BOOST_ASSERT(false);
            }
        }
    };
    
    struct Type : public Argument
    {
        Type(const std::string& value) : Argument("type", value) {}
    };
    
    struct GeneratorType : public Argument
    {
        GeneratorType(const std::string& value) : Argument("generator-type", value) {}
    };
    
    enum Severity
    {
        SEVERITY_INVALID = 0,
        SEVERITY_INFO,
        SEVERITY_WARNING,
        SEVERITY_ERROR
    };

    static const char* t_unterminatedComment;
    static const char* t_invalidIntegerLiteral;
    static const char* t_missingTerminatingQuotationMark;
    static const char* t_newLineBeforeTerminatingQuotationMark;
    static const char* t_unknownEscapeSequence;

    static const char* p_expectImportSource;
    static const char* p_importWithoutSourceProvider;
    static const char* p_sourceNotFound;
    static const char* p_openSourceFailed;

    static const char* p_misplacedComment;
    static const char* p_unknownStatment;
    
    static const char* p_expectStatementName;
    static const char* p_expectClassifierStatementName;
    static const char* p_unexpectEOFInStatementBody;
    static const char* p_expectStatementBody;
    static const char* p_expectKeyword;
    
    static const char* p_unexpectedStatmentModificator;
    
    static const char* p_unknownClassifierType;
    
    static const char* p_expectBaseStructureFieldName;
    static const char* p_expectFieldDefaultValue;
    
    static const char* p_expectType;
    static const char* p_expectAppropriateType;
    
    static const char* p_expectSemicolon;
    static const char* p_expectAssignmentOperator;
    static const char* p_expectSemicolonOrAssignmentOperator;

    static const char* p_expectClosingAngleBracket;
    
    static const char* p_nonByReferenceFieldDefaultWithNull;
    
    static const char* p_filterInNonObjectFactory;
    static const char* p_filterInFactoryForNonStructure;
    
    static const char* p_asteriskPackageElement;

    static const char* v_unacceptableParameterType;
    static const char* v_notUnique;

    static const char* v_partualObjectInNonPartialGenerator;
    static const char* v_baseStructureMustBeSharableForSharableStructure;
    
    Message(Severity severity, const std::string& text,
            const SourceIdSPtr& pSourceId, int line, int column);
    ~Message();

    Severity severity() const;
    std::string text() const;
    
    SourceIdSPtr sourceId() const;
    int line() const;
    int column() const;
    
    Message& operator<<(const Argument& argument);

    bool operator == (const Message& rValue) const;

private:
    Severity mSeverity;
    std::string mText;

    SourceIdSPtr mpSourceId;
    int mLine;
    int mColumn;
};

}

#else

namespace compil
{

class Message;
class ErrorMessage;

}

#endif

