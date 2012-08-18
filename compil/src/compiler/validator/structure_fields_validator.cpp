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

#include "structure_fields_validator.h"
#include "structure.h"
#include <set>

namespace compil
{

StructureFieldsValidator::StructureFieldsValidator()
{
}

StructureFieldsValidator::~StructureFieldsValidator()
{
}

bool StructureFieldsValidator::keywordCollision(const NameSPtr& pName, MessageCollectorPtr& pMessageCollector)
{
    return true;
}

bool StructureFieldsValidator::validate(const ObjectSPtr& pObject, MessageCollectorPtr& pMessageCollector)
{
    const StructureSPtr pStructure = ObjectFactory::downcastStructure(pObject);
    if (!pStructure) return true;
    
    std::set<std::string> names;
    
    bool bError = false;
    std::vector<ObjectSPtr> objects = pStructure->objects();
    for (std::vector<ObjectSPtr>::iterator it = objects.begin(); it != objects.end(); ++it)
    {
        FieldSPtr pField = ObjectFactory::downcastField(*it);
        if (!pField) continue;
        
        NameSPtr pName = pField->name();
        
        if (!keywordCollision(pName, pMessageCollector))
            bError = true;
        
        if (names.find(pName->value()) != names.end())
        {
            Message error(Message::SEVERITY_ERROR, Message::v_notUnique,
                    pName->sourceId(), pName->line(), pName->column());
            error << Message::Statement(pName->value())
                  << Message::Classifier("field name");
            pMessageCollector->addMessage(error);
            bError = true;
        }
        else
        {
            names.insert(pName->value());
        }
    }

    return !bError;
}

}
