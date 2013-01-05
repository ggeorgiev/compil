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

#ifndef __COMPIL_PROJECT_FILE_PATH_SCOMPIL_H_
#define __COMPIL_PROJECT_FILE_PATH_SCOMPIL_H_

#include "language/compil/all/object.h"
#include "language/compil/project/file_path.h"

namespace lang
{

namespace compil
{

class FilePath : public Object
{
public:
    // Default constructor
                               FilePath       ();
    // Destructor
    virtual                    ~FilePath      ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  FilePathSPtr       downcast       (const ObjectSPtr& object);

    // Identifier for the objects from FilePath class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId          staticObjectId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId          runtimeObjectId()                             const;

    // Getter method for the data field path
            const std::string& path           ()                             const;
    // Setter method for the data field path
            FilePath&          set_path       (const std::string& path);
    // Provides mutable access to field path
            std::string&       mutable_path   ();
    // Store operator for the data field path
            FilePath&          operator<<     (const std::string& path);

    // Setter method for the data field sourceId
            FilePath&          set_sourceId   (const SourceIdSPtr& sourceId);
    // Store operator for the data field sourceId
            FilePath&          operator<<     (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            FilePath&          set_line       (const Line& line);
    // Store operator for the data field line
            FilePath&          operator<<     (const Line& line);

    // Setter method for the data field column
            FilePath&          set_column     (const Column& column);
    // Store operator for the data field column
            FilePath&          operator<<     (const Column& column);

private:
    // variable for the data field path
    std::string mPath;
};

// Reference store operator for the data field sourceId
const FilePathSPtr& operator<<(const FilePathSPtr& , const SourceIdSPtr& );
// Reference store operator for the data field line
const FilePathSPtr& operator<<(const FilePathSPtr& , const Line& );
// Reference store operator for the data field column
const FilePathSPtr& operator<<(const FilePathSPtr& , const Column& );
// Reference store operator for the data field path
const FilePathSPtr& operator<<(const FilePathSPtr& , const std::string& );

inline FilePathSPtr filePathRef()
{
    return boost::make_shared<FilePath>();
}

}

}

#else // __COMPIL_PROJECT_FILE_PATH_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class FilePath;
typedef FilePath*                         FilePathRPtr;
typedef boost::shared_ptr<FilePath>       FilePathSPtr;
typedef boost::shared_ptr<const FilePath> FilePathSCPtr;
typedef boost::weak_ptr<FilePath>         FilePathWPtr;

class EObjectId;

}

}

#endif // __COMPIL_PROJECT_FILE_PATH_SCOMPIL_H_
