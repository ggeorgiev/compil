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
#include <vector>

#ifndef __CPP_DECLARATOR_PARAMETER_DECLARATOIN_LIST_SCOMPIL_H_
#define __CPP_DECLARATOR_PARAMETER_DECLARATOIN_LIST_SCOMPIL_H_

#include "language/c++/declarator/declarator.h"
#include "language/c++/declarator/parameter_declaratoin.h"
#include "language/c++/declarator/parameter_declaratoin_list.h"

namespace lang
{

namespace cpp
{

class ParameterDeclarationList : public Declarator
{
public:
    // Default constructor
                                                         ParameterDeclarationList ();
    // Destructor
    virtual                                              ~ParameterDeclarationList();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ParameterDeclarationListSPtr                 downcast                 (const DeclaratorSPtr& object);

    // Getter method for the data field declarators
            const std::vector<ParameterDeclarationSPtr>& declarators              ()                                                         const;
    // Setter method for the data field declarators
            ParameterDeclarationList&                    set_declarators          (const std::vector<ParameterDeclarationSPtr>& declarators);
    // Provides mutable access to field declarators
            std::vector<ParameterDeclarationSPtr>&       mutable_declarators      ();
    // Store operator for the data field declarators
            ParameterDeclarationList&                    operator<<               (const std::vector<ParameterDeclarationSPtr>& declarators);
    // Store operator for an item of data field declarators
            ParameterDeclarationList&                    operator<<               (const ParameterDeclarationSPtr& declaratorsItem);

private:
    // variable for the data field declarators
    std::vector<ParameterDeclarationSPtr> mDeclarators;
};

// Reference store operator for the data field declarators
const ParameterDeclarationListSPtr& operator<<(const ParameterDeclarationListSPtr& ,
                                               const std::vector<ParameterDeclarationSPtr>& );
// Reference store operator for an item of data field declarators
const ParameterDeclarationListSPtr& operator<<(const ParameterDeclarationListSPtr& , const ParameterDeclarationSPtr& );

inline ParameterDeclarationListSPtr parameterDeclarationListRef()
{
    return boost::make_shared<ParameterDeclarationList>();
}

}

}

#else // __CPP_DECLARATOR_PARAMETER_DECLARATOIN_LIST_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class ParameterDeclarationList;
typedef ParameterDeclarationList*                         ParameterDeclarationListRPtr;
typedef boost::shared_ptr<ParameterDeclarationList>       ParameterDeclarationListSPtr;
typedef boost::shared_ptr<const ParameterDeclarationList> ParameterDeclarationListSCPtr;
typedef boost::weak_ptr<ParameterDeclarationList>         ParameterDeclarationListWPtr;

}

}

#endif // __CPP_DECLARATOR_PARAMETER_DECLARATOIN_LIST_SCOMPIL_H_

