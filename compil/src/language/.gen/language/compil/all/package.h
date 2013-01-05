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

#ifndef __COMPIL_ALL_PACKAGE_SCOMPIL_H_
#define __COMPIL_ALL_PACKAGE_SCOMPIL_H_

#include "language/compil/all/object.h"
#include "language/compil/all/package.h"
#include "language/compil/all/package_element.h"

namespace lang
{

namespace compil
{

class Package : public Object
{
public:
    // Default constructor
                                                   Package        ();
    // Destructor
    virtual                                        ~Package       ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  PackageSPtr                            downcast       (const ObjectSPtr& object);

    // Identifier for the objects from Package class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjectId                              staticObjectId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjectId                              runtimeObjectId()                                              const;

    // Getter method for the data field short
            const std::vector<PackageElementSPtr>& short_         ()                                              const;
    // Setter method for the data field short
            Package&                               set_short      (const std::vector<PackageElementSPtr>& short_);
    // Provides mutable access to field short
            std::vector<PackageElementSPtr>&       mutable_short  ();

    // Getter method for the data field levels
            const std::vector<PackageElementSPtr>& levels         ()                                              const;
    // Setter method for the data field levels
            Package&                               set_levels     (const std::vector<PackageElementSPtr>& levels);
    // Provides mutable access to field levels
            std::vector<PackageElementSPtr>&       mutable_levels ();

    // Setter method for the data field sourceId
            Package&                               set_sourceId   (const SourceIdSPtr& sourceId);

    // Setter method for the data field line
            Package&                               set_line       (const Line& line);

    // Setter method for the data field column
            Package&                               set_column     (const Column& column);

private:
    // variable for the data field short
    std::vector<PackageElementSPtr> mShort;
    // variable for the data field levels
    std::vector<PackageElementSPtr> mLevels;
};

}

}

#else // __COMPIL_ALL_PACKAGE_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class Package;
typedef Package*                         PackageRPtr;
typedef boost::shared_ptr<Package>       PackageSPtr;
typedef boost::shared_ptr<const Package> PackageSCPtr;
typedef boost::weak_ptr<Package>         PackageWPtr;

class EObjectId;

}

}

#endif // __COMPIL_ALL_PACKAGE_SCOMPIL_H_

