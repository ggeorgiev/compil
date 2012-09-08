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

#ifndef __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECORATED_TYPE_COMPIL_H_
#define __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECORATED_TYPE_COMPIL_H_

#include "decorated_type.h"
#include "simple_type.h"
#include "type_declaration.h"
#include "type_decoration.h"

// DecoratedType is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class DecoratedType
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void                 operator=          (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                     Builder            ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                     Builder            (const DecoratedType& object);
        // Destructor of Builder
        /*lax*/                      ~Builder           ();

        // Instantiates DecoratedType instance with the current
        // initialization of the fields. After the instance is ready the
        // builder could be reused to instantiate more objects. The data is
        // not reset. Second call of build() will instantiate object with
        // the same data.
                const DecoratedType& build              ()                                    const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                DecoratedTypeSPtr    finalize           ();


        // Setter method for the data field declaration
                Builder&             set_declaration    (const ETypeDeclaration& declaration);
        // Provides mutable access to field declaration
                ETypeDeclaration&    mutable_declaration();
        // Updates the data field declaration. If the new value is equal to
        // the default it clears the field else it sets it to the new value
                Builder&             update_declaration (const ETypeDeclaration& declaration);
        // Resets the data field declaration to its default value invalid
                void                 reset_declaration  ();

        // Setter method for the data field type
                Builder&             set_type           (const SimpleType& type);
        // Provides mutable access to field type
                SimpleType&          mutable_type       ();
        // Clears the optional data field type
                void                 clear_type         ();

        // Setter method for the data field decoration
                Builder&             set_decoration     (const ETypeDecoration& decoration);
        // Provides mutable access to field decoration
                ETypeDecoration&     mutable_decoration ();
        // Updates the data field decoration. If the new value is equal to
        // the default it clears the field else it sets it to the new value
                Builder&             update_decoration  (const ETypeDecoration& decoration);
        // Resets the data field decoration to its default value invalid
                void                 reset_decoration   ();

        // Setter method for the data field aligned
                Builder&             set_aligned        (bool aligned);
        // Updates the data field aligned. If the new value is equal to the
        // default it clears the field else it sets it to the new value
                Builder&             update_aligned     (bool aligned);
        // Resets the data field aligned to its default value true
                void                 reset_aligned      ();

    protected:
        // constructor needed from potential derived classes
                                     Builder            (DecoratedTypeRPtr pObject);

        DecoratedTypeRPtr mpObject;
    };

    // Default constructor
                                    DecoratedType      ();
    // Destructor
    /*lax*/                         ~DecoratedType     ();

    // Returns true if every required field is initialized.
    // Note: If the class is used properly it should always return true,
    // because the object could be instantiated only if it is already
    // initialized and can not be changed. Called by the Builder class.
            bool                    isInitialized      () const;

            bool                    isVoid             () const;

    // Getter method for the data field declaration
            const ETypeDeclaration& declaration        () const;
    // Returns true if the data field value declaration was changed from
    // its default value invalid
            bool                    changed_declaration() const;
    // Returns the default value invalid of the field declaration
    static  ETypeDeclaration        default_declaration();

    // Getter method for the data field type
            const SimpleType&       type               () const;
    // Checks if the optional field type exists
            bool                    exist_type         () const;

    // Getter method for the data field decoration
            const ETypeDecoration&  decoration         () const;
    // Returns true if the data field value decoration was changed from its
    // default value invalid
            bool                    changed_decoration () const;
    // Returns the default value invalid of the field decoration
    static  ETypeDecoration         default_decoration ();

    // Getter method for the data field aligned
            bool                    aligned            () const;
    // Returns true if the data field value aligned was changed from its
    // default value true
            bool                    changed_aligned    () const;
    // Returns the default value true of the field aligned
    static  bool                    default_aligned    ();

private:
    // Returns unique bitmask value for the field declaration
    static int bitmask_declaration();
    // Returns unique bitmask value for the field type
    static int bitmask_type       ();
    // Returns unique bitmask value for the field decoration
    static int bitmask_decoration ();
    // Returns unique bitmask value for the field aligned
    static int bitmask_aligned    ();

    // Stores availability information for the fields
    int              mBits;

    // variable for the data field declaration
    ETypeDeclaration mDeclaration;
    // variable for the data field type
    SimpleType       mType;
    // variable for the data field decoration
    ETypeDecoration  mDecoration;
    // variable for the data field aligned
    bool             mAligned;
};

DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration);
DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const SimpleType& type);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDecoration& decoration);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const ETypeDecoration& decoration);
DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type, const ETypeDecoration& decoration);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                      const SimpleType& type,
                                      const ETypeDecoration& decoration);
DecoratedTypeSPtr CreateDecoratedType(bool aligned);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, bool aligned);
DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type, bool aligned);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration, const SimpleType& type, bool aligned);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDecoration& decoration, bool aligned);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                      const ETypeDecoration& decoration,
                                      bool aligned);
DecoratedTypeSPtr CreateDecoratedType(const SimpleType& type, const ETypeDecoration& decoration, bool aligned);
DecoratedTypeSPtr CreateDecoratedType(const ETypeDeclaration& declaration,
                                      const SimpleType& type,
                                      const ETypeDecoration& decoration,
                                      bool aligned);

#else // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECORATED_TYPE_COMPIL_H_

// Forward declarations
class DecoratedType;
typedef DecoratedType*                         DecoratedTypeRPtr;
typedef boost::shared_ptr<DecoratedType>       DecoratedTypeSPtr;
typedef boost::shared_ptr<const DecoratedType> DecoratedTypeSCPtr;
typedef boost::weak_ptr<DecoratedType>         DecoratedTypeWPtr;

#endif // __GENERATOR_SELF_GENERATOR_ALIGNER_OBJECT_DECORATED_TYPE_COMPIL_H_

