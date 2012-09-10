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

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_ARGUMENT_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_ARGUMENT_COMPIL_H_

#include "argument.h"
#include "decorated_type.h"
#include "variable_name.h"

// Argument is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class Argument
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void            operator= (const Builder&           );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                Builder   ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                Builder   (const Argument&          object);
        // Destructor of Builder
        /*lax*/                 ~Builder  ();

        // Instantiates Argument instance with the current initialization
        // of the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const Argument& build     ()                        const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                ArgumentSPtr    finalize  ();


        // Setter method for the data field type
                Builder&        set_type  (const DecoratedTypeSPtr& type);
        // Clears the optional data field type
                void            clear_type();

        // Setter method for the data field name
                Builder&        set_name  (const VariableNameSPtr&  name);
        // Clears the optional data field name
                void            clear_name();

    protected:
        // constructor needed from potential derived classes
                                Builder   (ArgumentRPtr             object);

        ArgumentRPtr mpObject;
    };

    // Default constructor
                                     Argument     ();
    // Destructor
    /*lax*/                          ~Argument    ();

    // Returns true if every required field is initialized.
    // Note: If the class is used properly it should always return true,
    // because the object could be instantiated only if it is already
    // initialized and can not be changed. Called by the Builder class.
            bool                     isInitialized() const;

            bool                     isVoid       () const;

    // Getter method for the data field type
            const DecoratedTypeSPtr& type         () const;
    // Checks if the optional field type exists
            bool                     exist_type   () const;

    // Getter method for the data field name
            const VariableNameSPtr&  name         () const;
    // Checks if the optional field name exists
            bool                     exist_name   () const;

private:
    // Returns unique bitmask value for the field type
    static int bitmask_type();
    // Returns unique bitmask value for the field name
    static int bitmask_name();

    // Stores availability information for the fields
    int               mBits;

    // variable for the data field type
    DecoratedTypeSPtr mType;
    // variable for the data field name
    VariableNameSPtr  mName;
};

ArgumentSPtr CreateArgument(const DecoratedTypeSPtr& type);
ArgumentSPtr CreateArgument(const VariableNameSPtr&  name);
ArgumentSPtr CreateArgument(const DecoratedTypeSPtr& type, const VariableNameSPtr& name);

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_ARGUMENT_COMPIL_H_

// Forward declarations
class Argument;
typedef Argument*                         ArgumentRPtr;
typedef boost::shared_ptr<Argument>       ArgumentSPtr;
typedef boost::shared_ptr<const Argument> ArgumentSCPtr;
typedef boost::weak_ptr<Argument>         ArgumentWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_ARGUMENT_COMPIL_H_

