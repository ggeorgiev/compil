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

#include <boost/shared_ptr.hpp>

#ifndef _ALIGNER_STREAM_H__
#define _ALIGNER_STREAM_H__

#include "aligner_configuration.h"

#include "language/all/element/element_factory.h"

#include <iostream>

class AlignerStream
{
public:
    AlignerStream(const AlignerConfigurationSPtr& configuration);
    virtual ~AlignerStream();
    
    std::string str();
    
    AlignerStream& operator<<(const lang::all::PassageSPtr& passage);

    AlignerConfigurationSPtr mConfiguration;
    
protected:
    AlignerStream& operator<<(const lang::all::LineSPtr& line);
    AlignerStream& operator<<(const lang::all::MoldSPtr& mold);
    AlignerStream& operator<<(const lang::all::ScopeSPtr& scope);

private:
    static std::vector<lang::all::ElementSPtr> flatten(const std::vector<lang::all::ElementSPtr>& elements);
    static std::vector<lang::all::MoldSPtr> mold(const std::vector<lang::all::ElementSPtr>& elements);
    
    static std::string evaluate(const lang::all::ElementSPtr& element);
    static std::string evaluate(const lang::all::ListSPtr& list);
    static std::string evaluate(const lang::all::PassageSPtr& passage);
    static std::string evaluate(const lang::all::StringSPtr& string);
    
    struct Endl {};
    static const Endl* endl;
    
    struct ResetEndl {};
    static const ResetEndl* resetEndl;

    AlignerStream& operator<<(const std::string& string);
    AlignerStream& operator<<(const Endl* endl);
    AlignerStream& operator<<(const ResetEndl* resetEndl);
        
    bool endlOn;
    
    std::string indent() const;

    std::ostringstream stream;
};

typedef boost::shared_ptr<AlignerStream> AlignerStreamSPtr;
typedef boost::weak_ptr<AlignerStream> AlignerStreamWPtr;



#endif

