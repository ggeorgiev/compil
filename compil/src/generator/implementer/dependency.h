// CompIL - Component Interface Language
// Copyright 2011 George Georgiev.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * The name of George Georgiev can not be used to endorse or 
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


#ifndef __GENERATOR_IMPLEMENTER_DEPENDENCY_H__
#define __GENERATOR_IMPLEMENTER_DEPENDENCY_H__
#pragma once

#include <boost/shared_ptr.hpp>

#include <string>

namespace compil
{

class Dependency
{
public:
    enum DependencyType
    {
        invalid_type = 0,
        system_type,
        quote_type
    };
    
    enum DependencyLevel
    {
        invalid_level = 0,
        application_level,
        core_level,
        thirdparty_level,
        stl_level,
        system_level
    };
    
    enum DependencySection
    {
        invalid_section = 0,
        global_section,
        private_section,
    };

    
    Dependency(const std::string& headerPackage = "",
               const std::string& headerName = "",
               DependencyType type = invalid_type, 
               DependencyLevel level = application_level, 
               DependencySection section = private_section,
               const std::string& library = "");
               
    operator bool() const;
    bool operator <(const Dependency& dependency) const;
    
    // TODO: change this to package object
    std::string mHeaderPackage;
    std::string mHeaderName;
    DependencyType mType;
    DependencyLevel mLevel;
    DependencySection mSection;
    std::string mLibrary;
};

}

#else

namespace compil
{

class Dependency;
typedef boost::shared_ptr<Dependency> DependencyPtr;

}

#endif // __GENERATOR_IMPLEMENTER_DEPENDENCY_H__