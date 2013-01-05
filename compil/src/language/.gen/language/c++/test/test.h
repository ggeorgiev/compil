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

#ifndef __CPP_TEST_TEST_SCOMPIL_H_
#define __CPP_TEST_TEST_SCOMPIL_H_

#include "language/c++/statement/statement.h"
#include "language/c++/test/test.h"
#include "language/c++/test/test_name.h"

namespace lang
{

namespace cpp
{

class Test
{
public:
    // Default constructor
                                              Test              ();
    // Destructor
    /*lax*/                                   ~Test             ();

    // Getter method for the data field name
            const TestName&                   name              ()                                             const;
    // Setter method for the data field name
            Test&                             set_name          (const TestName& name);
    // Provides mutable access to field name
            TestName&                         mutable_name      ();
    // Store operator for the data field name
            Test&                             operator<<        (const TestName& name);

    // Getter method for the data field statements
            const std::vector<StatementSPtr>& statements        ()                                             const;
    // Setter method for the data field statements
            Test&                             set_statements    (const std::vector<StatementSPtr>& statements);
    // Provides mutable access to field statements
            std::vector<StatementSPtr>&       mutable_statements();
    // Store operator for the data field statements
            Test&                             operator<<        (const std::vector<StatementSPtr>& statements);
    // Store operator for an item of data field statements
            Test&                             operator<<        (const StatementSPtr& statementsItem);

private:
    // variable for the data field name
    TestName                   mName;
    // variable for the data field statements
    std::vector<StatementSPtr> mStatements;
};

// Reference store operator for the data field name
const TestSPtr& operator<<(const TestSPtr& , const TestName& );
// Reference store operator for the data field statements
const TestSPtr& operator<<(const TestSPtr& , const std::vector<StatementSPtr>& );
// Reference store operator for an item of data field statements
const TestSPtr& operator<<(const TestSPtr& , const StatementSPtr& );

inline TestSPtr testRef()
{
    return boost::make_shared<Test>();
}

}

}

#else // __CPP_TEST_TEST_SCOMPIL_H_

namespace lang
{

namespace cpp
{

// Forward declarations
class Test;
typedef Test*                         TestRPtr;
typedef boost::shared_ptr<Test>       TestSPtr;
typedef boost::shared_ptr<const Test> TestSCPtr;
typedef boost::weak_ptr<Test>         TestWPtr;

}

}

#endif // __CPP_TEST_TEST_SCOMPIL_H_

