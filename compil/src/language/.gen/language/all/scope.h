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
#include <vector>

#ifndef __ALL_SCOPE_SCOMPIL_H_
#define __ALL_SCOPE_SCOMPIL_H_

#include "language/all/scope.h"

namespace lang
{

namespace all
{

class Scope
{
public:
    // Default constructor
            Scope ();
    // Destructor
    /*lax*/ ~Scope();

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class ESquiggles
    {
    public:
        // Default constructor - sets the value to invalid
                             ESquiggles();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             ESquiggles(long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                         const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                         const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const ESquiggles& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const ESquiggles& rValue) const;

        // static methods for enum class objects
        static const ESquiggles invalid ();
        static const ESquiggles none    ();
        static const ESquiggles brackets();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid  = 0,
            kNone     = 1,
            kBrackets = 2,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field squiggles
    const ESquiggles&               squiggles        ()                                      const;
    // Setter method for the data field squiggles
    Scope&                          set_squiggles    (const ESquiggles& squiggles);
    // Provides mutable access to field squiggles
    ESquiggles&                     mutable_squiggles();
    // Store operator for the data field squiggles
    Scope&                          operator<<       (const ESquiggles& squiggles);

    // Getter method for the data field lines
    const std::vector<std::string>& lines            ()                                      const;
    // Setter method for the data field lines
    Scope&                          set_lines        (const std::vector<std::string>& lines);
    // Provides mutable access to field lines
    std::vector<std::string>&       mutable_lines    ();
    // Store operator for the data field lines
    Scope&                          operator<<       (const std::vector<std::string>& lines);
    // Store operator for an item of data field lines
    Scope&                          operator<<       (const std::string& linesItem);

private:
    // variable for the data field squiggles
    ESquiggles               mSquiggles;
    // variable for the data field lines
    std::vector<std::string> mLines;
};

// Reference store operator for the data field squiggles
const ScopeSPtr& operator<<(const ScopeSPtr& , const Scope::ESquiggles& );
// Reference store operator for the data field lines
const ScopeSPtr& operator<<(const ScopeSPtr& , const std::vector<std::string>& );
// Reference store operator for an item of data field lines
const ScopeSPtr& operator<<(const ScopeSPtr& , const std::string& );

inline ScopeSPtr scopeRef()
{
    return boost::make_shared<Scope>();
}

}

}

#else // __ALL_SCOPE_SCOMPIL_H_

namespace lang
{

namespace all
{

// Forward declarations
class Scope;
typedef Scope*                         ScopeRPtr;
typedef boost::shared_ptr<Scope>       ScopeSPtr;
typedef boost::shared_ptr<const Scope> ScopeSCPtr;
typedef boost::weak_ptr<Scope>         ScopeWPtr;

}

}

#endif // __ALL_SCOPE_SCOMPIL_H_

