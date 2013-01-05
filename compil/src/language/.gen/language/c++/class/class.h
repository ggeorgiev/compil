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

#ifndef __CPP_CLASS_CLASS_SCOMPIL_H_
#define __CPP_CLASS_CLASS_SCOMPIL_H_

#include "language/c++/class/class.h"
#include "language/c++/class/class_name.h"
#include "language/c++/namespace/namespace.h"

namespace lang
{

namespace cpp
{

class Class
{
public:
    // Default constructor
                                 Class             ();
    // Destructor
    /*lax*/                      ~Class            ();

    // Getter method for the data field namespace
            const NamespaceSPtr& namespace_        ()                                const;
    // Setter method for the data field namespace
            Class&               set_namespace     (const NamespaceSPtr& namespace_);
    // Store operator for the data field namespace
            Class&               operator<<        (const NamespaceSPtr& namespace_);

    // Getter method for the data field containerClass
            const ClassSPtr&     containerClass    ()                                const;
    // Setter method for the data field containerClass
            Class&               set_containerClass(const ClassSPtr& containerClass);
    // Store operator for the data field containerClass
            Class&               operator<<        (const ClassSPtr& containerClass);

    // Getter method for the data field name
            const ClassNameSPtr& name              ()                                const;
    // Setter method for the data field name
            Class&               set_name          (const ClassNameSPtr& name);
    // Store operator for the data field name
            Class&               operator<<        (const ClassNameSPtr& name);

private:
    // variable for the data field namespace
    NamespaceSPtr mNamespace;
    // variable for the data field containerClass
    ClassSPtr     mContainerClass;
    // variable for the data field name
    ClassNameSPtr mName;
};

// Reference store operator for the data field namespace
const ClassSPtr& operator<<(const ClassSPtr& , const NamespaceSPtr& );
// Reference store operator for the data field containerClass
const ClassSPtr& operator<<(const ClassSPtr& , const ClassSPtr& );
// Reference store operator for the data field name
const ClassSPtr& operator<<(const ClassSPtr& , const ClassNameSPtr& );

inline ClassSPtr classRef()
{
    return boost::make_shared<Class>();
}

}

}

#else // __CPP_CLASS_CLASS_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class Class;
typedef Class*                         ClassRPtr;
typedef boost::shared_ptr<Class>       ClassSPtr;
typedef boost::shared_ptr<const Class> ClassSCPtr;
typedef boost::weak_ptr<Class>         ClassWPtr;

}

}

#endif // __CPP_CLASS_CLASS_SCOMPIL_H_

