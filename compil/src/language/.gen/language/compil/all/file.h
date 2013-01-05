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

#ifndef __COMPIL_ALL_FILE_SCOMPIL_H_
#define __COMPIL_ALL_FILE_SCOMPIL_H_

#include "language/compil/all/comment.h"
#include "language/compil/all/file.h"
#include "language/compil/all/object.h"
#include "language/compil/all/version.h"

namespace lang
{

namespace compil
{

class File : public Object
{
public:
    // Default constructor
                                            File            ();
    // Destructor
    virtual                                 ~File           ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  FileSPtr                        downcast        (const ObjectSPtr& object);

    // Identifier for the objects from File class.
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
    // Setter method for the data field comments
            File&                           set_comments    (const std::vector<CommentSPtr>& comments);
    // Provides mutable access to field comments
            std::vector<CommentSPtr>&       mutable_comments();
    // Store operator for the data field comments
            File&                           operator<<      (const std::vector<CommentSPtr>& comments);
    // Store operator for an item of data field comments
            File&                           operator<<      (const CommentSPtr& commentsItem);

    // Getter method for the data field version
            const Version&                  version         ()                                         const;
    // Setter method for the data field version
            File&                           set_version     (const Version& version);
    // Provides mutable access to field version
            Version&                        mutable_version ();
    // Store operator for the data field version
            File&                           operator<<      (const Version& version);

    // Setter method for the data field sourceId
            File&                           set_sourceId    (const SourceIdSPtr& sourceId);
    // Store operator for the data field sourceId
            File&                           operator<<      (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            File&                           set_line        (const Line& line);
    // Store operator for the data field line
            File&                           operator<<      (const Line& line);

    // Setter method for the data field column
            File&                           set_column      (const Column& column);
    // Store operator for the data field column
            File&                           operator<<      (const Column& column);

private:
    // variable for the data field comments
    std::vector<CommentSPtr> mComments;
    // variable for the data field version
    Version                  mVersion;
};

// Reference store operator for the data field sourceId
const FileSPtr& operator<<(const FileSPtr& , const SourceIdSPtr& );
// Reference store operator for the data field line
const FileSPtr& operator<<(const FileSPtr& , const Line& );
// Reference store operator for the data field column
const FileSPtr& operator<<(const FileSPtr& , const Column& );
// Reference store operator for the data field comments
const FileSPtr& operator<<(const FileSPtr& , const std::vector<CommentSPtr>& );
// Reference store operator for an item of data field comments
const FileSPtr& operator<<(const FileSPtr& , const CommentSPtr& );
// Reference store operator for the data field version
const FileSPtr& operator<<(const FileSPtr& , const Version& );

inline FileSPtr fileRef()
{
    return boost::make_shared<File>();
}

}

}

#else // __COMPIL_ALL_FILE_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class File;
typedef File*                         FileRPtr;
typedef boost::shared_ptr<File>       FileSPtr;
typedef boost::shared_ptr<const File> FileSCPtr;
typedef boost::weak_ptr<File>         FileWPtr;

class EObjectId;

}

}

#endif // __COMPIL_ALL_FILE_SCOMPIL_H_

