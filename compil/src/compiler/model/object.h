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

#ifndef __GENERATOR_SELF_COMPILER_MODEL_OBJECT_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_OBJECT_COMPIL_H_

#include "object.h"
#include "source_id.h"
// Boost C++ Smart Pointers
#include <boost/enable_shared_from_this.hpp>

namespace compil
{

class Object : public boost::enable_shared_from_this<Object>
{
public:
    // Default constructor
                                Object         ();
    // Destructor
    virtual                     ~Object        ();

    // Identifier for the objects from Object class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId           staticObjectId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId           runtimeObjectId()                             const;

    // Getter method for the data field sourceId
            const SourceIdSPtr& sourceId       ()                             const;
    // Setter method for the data field sourceId
            Object&             set_sourceId   (const SourceIdSPtr& sourceId);

    // Getter method for the data field line
            long                line           ()                             const;
    // Returns the default value -1 of the field line
    static  long                default_line   ();
    // Setter method for the data field line
            Object&             set_line       (long line);

    // Getter method for the data field column
            long                column         ()                             const;
    // Returns the default value -1 of the field column
    static  long                default_column ();
    // Setter method for the data field column
            Object&             set_column     (long column);

private:
    // variable for the data field sourceId
    SourceIdSPtr mSourceId;
    // variable for the data field line
    long         mLine;
    // variable for the data field column
    long         mColumn;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_OBJECT_COMPIL_H_

namespace compil
{

// Forward declarations
class Object;
typedef Object*                         ObjectRPtr;
typedef boost::shared_ptr<Object>       ObjectSPtr;
typedef boost::shared_ptr<const Object> ObjectSCPtr;
typedef boost::weak_ptr<Object>         ObjectWPtr;

class EObjectId;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_OBJECT_COMPIL_H_

