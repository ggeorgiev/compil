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

#ifndef __COMPILER_PARSER_PROJECT_PARSER_MIXIN_H__
#define __COMPILER_PARSER_PROJECT_PARSER_MIXIN_H__
#pragma once

#include "compiler/parser/parser-mixin.h"

namespace compil
{

struct ProjectParseContext : public ParseContext
{
    ProjectSPtr mProject;
};

typedef boost::shared_ptr<ProjectParseContext> ProjectParseContextSPtr;

class ProjectParserMixin : public ParserMixin
{
public:
    static FilePathSPtr parseFilePath(const ProjectParseContextSPtr& context);
    static SectionSPtr parseSection(const ProjectParseContextSPtr& context, const CommentSPtr& comment);
    
    static bool parseProjectStatement(const ProjectParseContextSPtr& context, const CommentSPtr& comment);
    static ProjectSPtr parseProject(const ProjectParseContextSPtr& context);
};

}

#endif // __COMPILER_PARSER_PROJECT_PARSER_MIXIN_H__