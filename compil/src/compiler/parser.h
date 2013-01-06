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

#ifndef _COMPIL_PARSER_H__
#define _COMPIL_PARSER_H__

#include "compiler/namespace_alias.h"

#include "compiler/parser/document_parser-mixin.h"
#include "compiler/parser/project_parser-mixin.h"

#include "compiler/message/message_collector.h"

#include "compiler/tokenizer/tokenizer.h"
#include "compiler/validator/validator.h"

#include "language/compil/document/document.h"

#include "boost/function.hpp"
#include "boost/bind.hpp"

#include <map>

namespace compil
{

class Parser : public DocumentParserMixin
             , public ProjectParserMixin
{
public:
    Parser();
    
    Parser(const Parser& parentParser);
    ~Parser();
    
    typedef boost::function1<void, const TypeSPtr&> InitTypeMethod;

    bool parseType(std::vector<PackageElementSPtr>& package_elements, TokenPtr& pNameToken);
    bool parseParameterType(InitTypeMethod initTypeMethod,
                            const std::string& defaultTypeName = "");
                            
    EnumerationValueSPtr parseEnumerationValue(const CommentSPtr& pComment,
                                               const std::vector<EnumerationValueSPtr>& values);
    EnumerationSPtr parseEnumeration(const CommentSPtr& pComment,
                                     const TokenPtr& pCast,
                                     const TokenPtr& pFlags);
    SpecimenSPtr parseSpecimen(const CommentSPtr& pComment);
    IdentifierSPtr parseIdentifier(const CommentSPtr& pComment,
                                   const TokenPtr& pCast);
                                   
    FilterSPtr parseFilter(const CommentSPtr& pComment, 
                           const StructureSPtr& pStructure);
    FactorySPtr parseFactory(const CommentSPtr& pComment,
                             const TokenPtr& pFunctionType,
                             const TokenPtr& pFactoryType);

    FieldSPtr parseField(const CommentSPtr& pComment, 
                         const std::vector<ObjectSPtr>& structureObjects,
                         TokenPtr& pWeak);
    FieldOverrideSPtr parseFieldOverride(const FieldSPtr& pField, 
                                         const StructureSPtr& pStructure,
                                         const TokenPtr& pOverride);
                         
    IdentificationSPtr parseIdentification(const CommentSPtr& pComment,
                                           const TokenPtr& pType);
    UpcopySPtr parseUpcopy(const CommentSPtr& pComment,
                           const StructureSPtr& pStructure);
    OperatorSPtr parseOperator(const CommentSPtr& pComment,
                               const TokenPtr& pOperatorDeclaration);
    StructureSPtr parseStructure(const CommentSPtr& pComment,
                                 const TokenPtr& pAbstract,
                                 const TokenPtr& pContolled,
                                 const TokenPtr& pImmutable,
                                 const TokenPtr& pPartial,
                                 const TokenPtr& pSharable,
                                 const TokenPtr& pStreamable);
                          
    bool parseImport();

    ParameterSPtr parseParameter(const CommentSPtr pComment);
    MethodSPtr parseMethod(const CommentSPtr& pComment);
    InterfaceSPtr parseInterface(const CommentSPtr& pComment);
    
    void parseAnyStatement(const CommentSPtr& pComment);
    
    void addValidator(const ValidatorPtr& pValidator);
    
    void initDocumentContext();
    
    // Parse the input and construct a Descriptor from it.
    // Returns true if no errors occurred, false otherwise.
    bool parseDocument(const StreamPtr& pInput,
                       DocumentSPtr& document);
    bool parseDocument(const SourceIdSPtr& sourceId, 
                       const StreamPtr& pInput, 
                       DocumentSPtr& document);
    bool parseDocument(const ISourceProviderSPtr& pSourceProvider,
                       const SourceIdSPtr& pSourceId,
                       DocumentSPtr& document);
               
    void setDocumentInput(const StreamPtr& pInput);
    
    void initProjectContext();
    
    bool parseProject(const SourceIdSPtr& sourceId,
                      const StreamPtr& pInput,
                      ProjectSPtr& project);
               
   const std::vector<Message>& messages();

    ParseContextSPtr mContext;

private:

    struct LateTypeResolveInfo
    {
        TokenPtr pToken;
        std::string classifier;
        InitTypeMethod initTypeMethod;
    };
    
    std::vector<LateTypeResolveInfo> mLateTypeResolve;
    void lateTypeResolve(const TypeSPtr& pNewType);
    
    PackageSPtr mpPackage;

    FileSPtr mFile;
    DocumentSPtr mDocument;
    std::vector<ValidatorPtr> mvValidator;
    
    Parser& operator<<(const Message& message);

    bool unexpectedStatement(const TokenPtr& pToken);
    void recover();

    bool validate(const DocumentSPtr& document);
    bool validate(const ObjectSPtr& pObject);
    
    
    static Token::Type getTokenType(const Type::ELiteral& literal);
};

typedef boost::shared_ptr<Parser> ParserPtr;

}

#else

namespace compil
{

class Parser;
typedef boost::shared_ptr<Parser> ParserPtr;

}

#endif // _COMPIL_PARSER_H__
