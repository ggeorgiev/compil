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

#include "compiler/validator/structure_sharable_validator.h"

#include "language/compil/document/structure.h"

#include <set>

namespace compil
{

StructureSharableValidator::StructureSharableValidator()
{
}

StructureSharableValidator::~StructureSharableValidator()
{
}

bool StructureSharableValidator::validate(const ObjectSPtr& pObject,
                                          MessageCollectorPtr& pMessageCollector)
{
    const StructureSPtr pStructure = ObjectFactory::downcastStructure(pObject);
    if (!pStructure) return true;
    
    if (!pStructure->sharable()) return true;
    
    StructureSPtr pBaseStructure = pStructure->baseStructure().lock();
    if (!pBaseStructure) return true;
    if (pBaseStructure->sharable()) return true;
    
    Message error(Message::SEVERITY_ERROR, Message::v_baseStructureMustBeSharableForSharableStructure,
            pStructure->sourceId(), pStructure->line(), pStructure->column());
    pMessageCollector->addMessage(error);
    return false;
}

}
