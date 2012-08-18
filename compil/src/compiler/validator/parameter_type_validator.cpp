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

#include "parameter_type_validator.h"

namespace compil
{

ParameterTypeValidator::ParameterTypeValidator(const EObjectId& objectId)
        : mObjectId(objectId)
{
}

ParameterTypeValidator::~ParameterTypeValidator()
{
}

void ParameterTypeValidator::addAcceptableType(const TypeSPtr& pType)
{
    mvAcceptableType.push_back(pType);
}

bool ParameterTypeValidator::validate(const ObjectSPtr& pObject, MessageCollectorPtr& pMessageCollector)
{
    BOOST_ASSERT(mvAcceptableType.size() >= 1);
    
    if (pObject->runtimeObjectId() != mObjectId)
        return true;
        
    UnaryTemplateSPtr pUnaryTemplate = boost::static_pointer_cast<UnaryTemplate>(pObject);

    TypeSPtr pParameterType = pUnaryTemplate->parameterType().lock();
    if (!pParameterType)
        return false;
    
    for (std::vector<TypeSPtr>::iterator it = mvAcceptableType.begin(); it != mvAcceptableType.end(); ++it)
    {
        if (pParameterType == *it)
        {
            return true;
        }
    }
    
    Message error(Message::SEVERITY_ERROR, Message::v_unacceptableParameterType,
           pUnaryTemplate->sourceId(), pUnaryTemplate->line(), pUnaryTemplate->column());
    error << Message::Statement(mObjectId);
    
    std::string options = mvAcceptableType[0]->name()->value();
    for (size_t i = 1; i < mvAcceptableType.size() - 1; ++i)
    {
        options += ", ";
        options += mvAcceptableType[i]->name()->value();
    }
    
    if (mvAcceptableType.size() >= 2)
    {
        options += " or ";
        options += mvAcceptableType[mvAcceptableType.size() - 1]->name()->value();
    }

    error << Message::Options(options);
    pMessageCollector->addMessage(error);
    return false;
}

}
