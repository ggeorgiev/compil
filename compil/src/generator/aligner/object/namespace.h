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
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// Standard Template Library
#include <vector>

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_COMPIL_H_

#include "namespace.h"
#include "namespace_name.h"

class Namespace
{
public:
    // Default constructor
                                                  Namespace    ();
    // Destructor
    /*lax*/                                       ~Namespace   ();

    // Returns true if every required field is initialized.
            bool                                  isInitialized()                                     const;

            bool                                  isVoid       ()                                     const;

    // Getter method for the data field names
            const std::vector<NamespaceNameSPtr>& names        ()                                     const;
    // Checks if the optional field names exists
            bool                                  exist_names  ()                                     const;
    // Setter method for the data field names
            Namespace&                            set_names    (const std::vector<NamespaceNameSPtr>& names);
    // Provides mutable access to field names
            std::vector<NamespaceNameSPtr>&       mutable_names();
    // Store operator for the data field names
            Namespace&                            operator<<   (const std::vector<NamespaceNameSPtr>& names);
    // Store operator for an item of data field names
            Namespace&                            operator<<   (const NamespaceNameSPtr&              namesItem);
    // Clears the optional data field names
            void                                  clear_names  ();

private:
    // Returns unique bitmask value for the field names
    static int bitmask_names();

    // Stores availability information for the fields
    int                            mBits;

    // variable for the data field names
    std::vector<NamespaceNameSPtr> mNames;
};

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_COMPIL_H_

// Forward declarations
class Namespace;
typedef Namespace*                         NamespaceRPtr;
typedef boost::shared_ptr<Namespace>       NamespaceSPtr;
typedef boost::shared_ptr<const Namespace> NamespaceSCPtr;
typedef boost::weak_ptr<Namespace>         NamespaceWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_NAMESPACE_COMPIL_H_

