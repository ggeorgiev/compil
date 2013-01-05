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

#ifndef __COMPIL_ALL_PACKAGE_ELEMENT_SCOMPIL_H_
#define __COMPIL_ALL_PACKAGE_ELEMENT_SCOMPIL_H_

#include "language/compil/all/package_element.h"

namespace lang
{

namespace compil
{

class PackageElement
{
public:
    // Default constructor
                               PackageElement ();
    // Destructor
    /*lax*/                    ~PackageElement();

            bool               operator==     (const PackageElement& object)     const;

            bool               operator==     (const PackageElementSPtr& object) const;

    // Getter method for the data field value
            const std::string& value          ()                                 const;
    // Setter method for the data field value
            PackageElement&    set_value      (const std::string& value);
    // Provides mutable access to field value
            std::string&       mutable_value  ();
    // Store operator for the data field value
            PackageElement&    operator<<     (const std::string& value);

private:
    // variable for the data field value
    std::string mValue;
};

// Reference store operator for the data field value
const PackageElementSPtr& operator<<(const PackageElementSPtr& , const std::string& );

inline PackageElementSPtr packageElementRef()
{
    return boost::make_shared<PackageElement>();
}

}

}

#else // __COMPIL_ALL_PACKAGE_ELEMENT_SCOMPIL_H_

namespace lang
{

namespace compil
{

// Forward declarations
class PackageElement;
typedef PackageElement*                         PackageElementRPtr;
typedef boost::shared_ptr<PackageElement>       PackageElementSPtr;
typedef boost::shared_ptr<const PackageElement> PackageElementSCPtr;
typedef boost::weak_ptr<PackageElement>         PackageElementWPtr;

}

}

#endif // __COMPIL_ALL_PACKAGE_ELEMENT_SCOMPIL_H_
