// Boost C++ Utility
#include <boost/assert.hpp>

#include "language/c++/test/test_suite.h"

namespace lang
{

namespace cpp
{

TestSuite::TestSuite()
{
}

TestSuite::~TestSuite()
{
}

const TestSuiteName& TestSuite::name() const
{
    return mName;
}

TestSuite& TestSuite::set_name(const TestSuiteName& name)
{
    mName = name;
    return *this;
}

TestSuiteName& TestSuite::mutable_name()
{
    return mName;
}

TestSuite& TestSuite::operator<<(const TestSuiteName& name)
{
    return set_name(name);
}

const TestSuiteSPtr& operator<<(const TestSuiteSPtr& object, const TestSuiteName& name)
{
    BOOST_ASSERT(object);
    *object << name;
    return object;
}

const std::vector<TestSPtr>& TestSuite::tests() const
{
    return mTests;
}

TestSuite& TestSuite::set_tests(const std::vector<TestSPtr>& tests)
{
    mTests = tests;
    return *this;
}

std::vector<TestSPtr>& TestSuite::mutable_tests()
{
    return mTests;
}

TestSuite& TestSuite::operator<<(const std::vector<TestSPtr>& tests)
{
    return set_tests(tests);
}

const TestSuiteSPtr& operator<<(const TestSuiteSPtr& object, const std::vector<TestSPtr>& tests)
{
    BOOST_ASSERT(object);
    *object << tests;
    return object;
}

TestSuite& TestSuite::operator<<(const TestSPtr& testsItem)
{
    mTests.push_back(testsItem);
    return *this;
}

const TestSuiteSPtr& operator<<(const TestSuiteSPtr& object, const TestSPtr& testsItem)
{
    BOOST_ASSERT(object);
    *object << testsItem;
    return object;
}

}

}

