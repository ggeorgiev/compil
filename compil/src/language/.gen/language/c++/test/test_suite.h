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
#include <vector>

#ifndef __CPP_TEST_TEST_SUITE_SCOMPIL_H_
#define __CPP_TEST_TEST_SUITE_SCOMPIL_H_

#include "language/c++/test/test.h"
#include "language/c++/test/test_suite.h"
#include "language/c++/test/test_suite_name.h"

namespace lang
{

namespace cpp
{

class TestSuite
{
public:
    // Default constructor
                                         TestSuite    ();
    // Destructor
    /*lax*/                              ~TestSuite   ();

    // Getter method for the data field name
            const TestSuiteName&         name         ()                                   const;
    // Setter method for the data field name
            TestSuite&                   set_name     (const TestSuiteName& name);
    // Provides mutable access to field name
            TestSuiteName&               mutable_name ();
    // Store operator for the data field name
            TestSuite&                   operator<<   (const TestSuiteName& name);

    // Getter method for the data field tests
            const std::vector<TestSPtr>& tests        ()                                   const;
    // Setter method for the data field tests
            TestSuite&                   set_tests    (const std::vector<TestSPtr>& tests);
    // Provides mutable access to field tests
            std::vector<TestSPtr>&       mutable_tests();
    // Store operator for the data field tests
            TestSuite&                   operator<<   (const std::vector<TestSPtr>& tests);
    // Store operator for an item of data field tests
            TestSuite&                   operator<<   (const TestSPtr& testsItem);

private:
    // variable for the data field name
    TestSuiteName         mName;
    // variable for the data field tests
    std::vector<TestSPtr> mTests;
};

// Reference store operator for the data field name
const TestSuiteSPtr& operator<<(const TestSuiteSPtr& , const TestSuiteName& );
// Reference store operator for the data field tests
const TestSuiteSPtr& operator<<(const TestSuiteSPtr& , const std::vector<TestSPtr>& );
// Reference store operator for an item of data field tests
const TestSuiteSPtr& operator<<(const TestSuiteSPtr& , const TestSPtr& );

inline TestSuiteSPtr testSuiteRef()
{
    return boost::make_shared<TestSuite>();
}

}

}

#else // __CPP_TEST_TEST_SUITE_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class TestSuite;
typedef TestSuite*                         TestSuiteRPtr;
typedef boost::shared_ptr<TestSuite>       TestSuiteSPtr;
typedef boost::shared_ptr<const TestSuite> TestSuiteSCPtr;
typedef boost::weak_ptr<TestSuite>         TestSuiteWPtr;

}

}

#endif // __CPP_TEST_TEST_SUITE_SCOMPIL_H_

