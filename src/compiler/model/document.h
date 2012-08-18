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

#ifndef __GENERATOR_SELF_COMPILER_MODEL_DOCUMENT_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_DOCUMENT_COMPIL_H_

#include "comment.h"
#include "document.h"
#include "object.h"
#include "version.h"

namespace compil
{

class Document : public Object
{
public:
    // Default constructor
                                            Document        ();
    // Destructor
    virtual                                 ~Document       ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  DocumentSPtr                    downcast        (const ObjectSPtr& pObject);

    // Returns true if every required field is initialized.
    virtual bool                            isInitialized   ()                                         const;

    // Identifier for the objects from Document class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId                       staticObjectId  ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId                       runtimeObjectId ()                                         const;

    // Getter method for the data field comments
            const std::vector<CommentSPtr>& comments        ()                                         const;
    // Checks if the optional field comments exists
            bool                            exist_comments  ()                                         const;
    // Setter method for the data field comments
            void                            set_comments    (const std::vector<CommentSPtr>& comments);
            std::vector<CommentSPtr>&       mutable_comments();
    // Clears the optional data field comments
            void                            clear_comments  ();

    // Getter method for the data field version
            const Version&                  version         ()                                         const;
    // Returns true if the data field version was set and could be
    // considered valid
            bool                            valid_version   ()                                         const;
    // Setter method for the data field version
            void                            set_version     (const Version& version);
            Version&                        mutable_version ();
    // Erases the required data field version. Object can not be
    // instantiated before the field data is set again
            void                            erase_version   ();

private:
    // Returns unique bitmask value for the field comments
    static int bitmask_comments();
    // Returns unique bitmask value for the field version
    static int bitmask_version ();

    // Stores availability information for the fields
    int                      mBits;

    // variable for the data field comments
    std::vector<CommentSPtr> mComments;
    // variable for the data field version
    Version                  mVersion;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_DOCUMENT_COMPIL_H_

namespace compil
{

// Forward declarations
class Document;
typedef Document*                         DocumentRPtr;
typedef boost::shared_ptr<Document>       DocumentSPtr;
typedef boost::shared_ptr<const Document> DocumentSCPtr;
typedef boost::weak_ptr<Document>         DocumentWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_DOCUMENT_COMPIL_H_

