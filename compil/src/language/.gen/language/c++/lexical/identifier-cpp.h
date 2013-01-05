// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * The name of George Georgiev can not be used to endorse or
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

// Boost C++ Smart Pointers
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// Standard Template Library
#include <string>

#ifndef __CPP_LEXICAL_IDENTIFIER_CPP_SCOMPIL_H_
#define __CPP_LEXICAL_IDENTIFIER_CPP_SCOMPIL_H_

#include "language/c++/lexical/identifier-cpp.h"

namespace lang
{

namespace cpp
{

class Identifier
{
public:
    // Default constructor
                               Identifier   ();
    // Destructor
    /*lax*/                    ~Identifier  ();

    // Getter method for the data field value
            const std::string& value        ()                         const;
    // Setter method for the data field value
            Identifier&        set_value    (const std::string& value);
    // Provides mutable access to field value
            std::string&       mutable_value();
    // Store operator for the data field value
            Identifier&        operator<<   (const std::string& value);

private:
    // variable for the data field value
    std::string mValue;
};

// Reference store operator for the data field value
const IdentifierSPtr& operator<<(const IdentifierSPtr& , const std::string& );

inline IdentifierSPtr identifierRef()
{
    return boost::make_shared<Identifier>();
}

}

}

#else // __CPP_LEXICAL_IDENTIFIER_CPP_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class Identifier;
typedef Identifier*                         IdentifierRPtr;
typedef boost::shared_ptr<Identifier>       IdentifierSPtr;
typedef boost::shared_ptr<const Identifier> IdentifierSCPtr;
typedef boost::weak_ptr<Identifier>         IdentifierWPtr;

}

}

#endif // __CPP_LEXICAL_IDENTIFIER_CPP_SCOMPIL_H_

