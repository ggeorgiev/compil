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
#include <string>

#ifndef __GENERATOR_SELF_COMPILER_MODEL_SOURCE_ID_COMPIL_H_
#define __GENERATOR_SELF_COMPILER_MODEL_SOURCE_ID_COMPIL_H_

#include "source_id.h"

namespace compil
{

// SourceId is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class SourceId
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void            operator=                 (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                Builder                   ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                Builder                   (const SourceId& object);
        // Destructor of Builder
        /*lax*/                 ~Builder                  ();

        // Instantiates SourceId instance with the current initialization
        // of the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const SourceId& build                     ()                                      const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                SourceIdSPtr    finalize                  ();


        // Setter method for the data field value
                Builder&        set_value                 (const std::string& value);
        // Provide mutable access to field value
                std::string&    mutable_value             ();

        // Setter method for the data field uniquePresentation
                Builder&        set_uniquePresentation    (const std::string& uniquePresentation);
        // Provide mutable access to field uniquePresentation
                std::string&    mutable_uniquePresentation();

        // Setter method for the data field parent
                Builder&        set_parent                (const SourceIdSPtr& parent);

        // Setter method for the data field original
                Builder&        set_original              (const std::string& original);
        // Provide mutable access to field original
                std::string&    mutable_original          ();

    protected:
        // constructor needed from potential derived classes
                                Builder                   (SourceIdRPtr pObject);

        SourceIdRPtr mpObject;
    };

    // Default constructor
                                SourceId          ();
    // Destructor
    /*lax*/                     ~SourceId         ();

    // Getter method for the data field value
            const std::string&  value             () const;

    // Getter method for the data field uniquePresentation
            const std::string&  uniquePresentation() const;

    // Getter method for the data field parent
            const SourceIdSPtr& parent            () const;
    // Returns the default value null of the field parent
    static  SourceIdSPtr        default_parent    ();

    // Getter method for the data field original
            const std::string&  original          () const;

private:
    // variable for the data field value
    std::string  mValue;
    // variable for the data field uniquePresentation
    std::string  mUniquePresentation;
    // variable for the data field parent
    SourceIdSPtr mParent;
    // variable for the data field original
    std::string  mOriginal;
};

}

#else // __GENERATOR_SELF_COMPILER_MODEL_SOURCE_ID_COMPIL_H_

namespace compil
{

// Forward declarations
class SourceId;
typedef SourceId*                         SourceIdRPtr;
typedef boost::shared_ptr<SourceId>       SourceIdSPtr;
typedef boost::shared_ptr<const SourceId> SourceIdSCPtr;
typedef boost::weak_ptr<SourceId>         SourceIdWPtr;

}

#endif // __GENERATOR_SELF_COMPILER_MODEL_SOURCE_ID_COMPIL_H_

