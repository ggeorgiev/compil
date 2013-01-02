#include "structures.h"
// Boost C++ Utility
#include <boost_assert_handler.h>
// Google Test framework
#include <gtest/gtest.h>

TEST(StructureStructureIsInitializeTest, available_DefaultValues)
{
    StructureIsInitialize structure1;
    ASSERT_FALSE(structure1.valid_r());
    ASSERT_FALSE(structure1.exist_o());
    ASSERT_FALSE(structure1.changed_d());
}
TEST(StructureStructureIsInitializeTest, isInitialized)
{
    StructureIsInitialize structure1;
    ASSERT_FALSE(structure1.isInitialized());
    structure1.set_r(long());
    ASSERT_TRUE(structure1.isInitialized());
}

TEST(StructureStructureIsInitialize1Test, available_DefaultValues)
{
    StructureIsInitialize1 structure1;
    ASSERT_TRUE(structure1.valid_r());
    ASSERT_FALSE(structure1.exist_o());
    ASSERT_FALSE(structure1.changed_d());
}

TEST(StructureStructureIsInitialize2Test, available_DefaultValues)
{
    StructureIsInitialize2 structure1;
    ASSERT_FALSE(structure1.valid_r());
    ASSERT_FALSE(structure1.exist_o());
    ASSERT_FALSE(structure1.changed_d());
    ASSERT_FALSE(structure1.valid_r2());
}
TEST(StructureStructureIsInitialize2Test, isInitialized)
{
    StructureIsInitialize2 structure1;
    ASSERT_FALSE(structure1.isInitialized());
    structure1.set_r(long());
    structure1.set_r2(long());
    ASSERT_TRUE(structure1.isInitialized());
}


TEST(StructureStructureIsInitialize3Test, available_DefaultValues)
{
    StructureIsInitialize3 structure1;
    ASSERT_FALSE(structure1.valid_r());
    ASSERT_FALSE(structure1.exist_o());
    ASSERT_FALSE(structure1.changed_d());
    ASSERT_FALSE(structure1.valid_r3());
}
TEST(StructureStructureIsInitialize3Test, isInitialized)
{
    StructureIsInitialize3 structure1;
    ASSERT_FALSE(structure1.isInitialized());
    structure1.set_r(long());
    structure1.set_r3(long());
    ASSERT_TRUE(structure1.isInitialized());
}


TEST(StructureStructureIsInitialize4Test, available_DefaultValues)
{
    StructureIsInitialize4 structure1;
    ASSERT_FALSE(structure1.valid_r());
    ASSERT_FALSE(structure1.exist_o());
    ASSERT_FALSE(structure1.changed_d());
    ASSERT_FALSE(structure1.valid_r4());
}
TEST(StructureStructureIsInitialize4Test, isInitialized)
{
    StructureIsInitialize4 structure1;
    ASSERT_FALSE(structure1.isInitialized());
    structure1.set_r(long());
    structure1.set_r4(long());
    ASSERT_TRUE(structure1.isInitialized());
}

TEST(StructureStructureIsInitializeVirtualTest, available_DefaultValues)
{
    StructureIsInitializeVirtual structure1;
    ASSERT_FALSE(structure1.valid_r());
}
TEST(StructureStructureIsInitializeVirtualTest, isInitialized)
{
    StructureIsInitializeVirtual structure1;
    ASSERT_FALSE(structure1.isInitialized());
    structure1.set_r(long());
    ASSERT_TRUE(structure1.isInitialized());
}


TEST(StructureStructureIsInitialize5Test, available_DefaultValues)
{
    StructureIsInitialize5 structure1;
    ASSERT_FALSE(structure1.valid_r());
    ASSERT_FALSE(structure1.valid_r5());
}
TEST(StructureStructureIsInitialize5Test, isInitialized)
{
    StructureIsInitialize5 structure1;
    ASSERT_FALSE(structure1.isInitialized());
    structure1.set_r(long());
    structure1.set_r5(long());
    ASSERT_TRUE(structure1.isInitialized());
}


TEST(StructureStructureIsInitialize6Test, available_DefaultValues)
{
    StructureIsInitialize6 structure1;
    ASSERT_FALSE(structure1.valid_r6());
}
TEST(StructureStructureIsInitialize6Test, isInitialized)
{
    StructureIsInitialize6 structure1;
    ASSERT_FALSE(structure1.isInitialized());
    structure1.set_r(long());
    structure1.set_r6(long());
    ASSERT_TRUE(structure1.isInitialized());
}

TEST(StructureStructureIsVoidTest, available_DefaultValues)
{
    StructureIsVoid structure1;
    ASSERT_FALSE(structure1.exist_o());
}
TEST(StructureStructureIsVoidTest, isInitialized)
{
    StructureIsVoid structure1;
    ASSERT_TRUE(structure1.isInitialized());
}

TEST(StructureStructureIsVoid1Test, available_DefaultValues)
{
    StructureIsVoid1 structure1;
    ASSERT_FALSE(structure1.exist_o());
    ASSERT_FALSE(structure1.exist_o1());
}
TEST(StructureStructureIsVoid1Test, isInitialized)
{
    StructureIsVoid1 structure1;
    ASSERT_TRUE(structure1.isInitialized());
}




