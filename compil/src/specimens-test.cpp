#include "specimens.h"
// Boost C++ Utility
#include <boost_assert_handler.h>
// Google Test framework
#include <gtest/gtest.h>

TEST(SpecimenIntegerSpecimenTest, operatorEqualTo)
{
    specimen::IntegerSpecimen speciment1;
    specimen::IntegerSpecimen speciment2;
    ASSERT_TRUE(speciment1 == speciment2);
}
TEST(SpecimenIntegerSpecimenTest, operatorNotEqualTo)
{
    specimen::IntegerSpecimen speciment1;
    specimen::IntegerSpecimen speciment2;
    ASSERT_FALSE(speciment1 != speciment2);
}




