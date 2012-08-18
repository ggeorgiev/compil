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

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECLARATION_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECLARATION_COMPIL_H_

#include "declaration.h"

// Declaration is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class Declaration
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void               operator=    (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                   Builder      ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                   Builder      (const Declaration& object);
        // Destructor of Builder
        /*lax*/                    ~Builder     ();

        // Instantiates Declaration instance with the current
        // initialization of the fields. After the instance is ready the
        // builder could be reused to instantiate more objects. The data is
        // not reset. Second call of build() will instantiate object with
        // the same data.
                const Declaration& build        ()                          const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                DeclarationSPtr    finalize     ();


        // Setter method for the data field value
                Builder&           set_value    (const std::string& value);
                std::string&       mutable_value();
        // Clears the optional data field value
                void               clear_value  ();

    protected:
        // constructor needed from potential derived classes
                                   Builder      (DeclarationRPtr pObject);

        DeclarationRPtr mpObject;
    };

    // Default constructor
                               Declaration  ();
    // Destructor
    /*lax*/                    ~Declaration ();

    // Returns true if every required field is initialized.
    // Note: If the class is used properly it should always return true,
    // because the object could be instantiated only if it is already
    // initialized and can not be changed. Called by the Builder class.
            bool               isInitialized() const;

            bool               isVoid       () const;

    // Getter method for the data field value
            const std::string& value        () const;
    // Checks if the optional field value exists
            bool               exist_value  () const;

private:
    // Returns unique bitmask value for the field value
    static int bitmask_value();

    // Stores availability information for the fields
    int         mBits;

    // variable for the data field value
    std::string mValue;
};

DeclarationSPtr CreateDeclaration(const std::string& value);

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECLARATION_COMPIL_H_

// Forward declarations
class Declaration;
typedef Declaration*                         DeclarationRPtr;
typedef boost::shared_ptr<Declaration>       DeclarationSPtr;
typedef boost::shared_ptr<const Declaration> DeclarationSCPtr;
typedef boost::weak_ptr<Declaration>         DeclarationWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECLARATION_COMPIL_H_

