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

#ifndef _COMPIL_PARTIAL_VALIDATOR_H__
#define _COMPIL_PARTIAL_VALIDATOR_H__

#include "validator.h"

#include "language/compil/document/type.h"

namespace compil
{

class PartialValidator : public Validator
{
public:
    PartialValidator(const std::string& type);
    ~PartialValidator();

    virtual bool validate(const ObjectSPtr& pObject, MessageCollectorPtr& pMessageCollector);

protected:
    std::string mType;
};

typedef boost::shared_ptr<PartialValidator> PartialValidatorPtr;
typedef boost::weak_ptr<PartialValidator> PartialValidatorWPtr;

}

#else // _COMPIL_STRUCTURE_FIELDS_VALIDATOR_H__

namespace compil
{

class PartialValidator;
typedef boost::shared_ptr<PartialValidator> PartialValidatorPtr;
typedef boost::weak_ptr<PartialValidator> PartialValidatorWPtr;

}

#endif // _COMPIL_STRUCTURE_FIELDS_VALIDATOR_H__
