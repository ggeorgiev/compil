#include "structures.h"
// Google Test framework
#include <gtest/gtest.h>

TEST(StructureIsInitializeTest, isInitialized)
{
    StructureIsInitialize structure;
    EXPECT_FALSE(structure.isInitialized());
}


TEST(StructureIsInitialize2Test, isInitialized)
{
    StructureIsInitialize2 structure;
    EXPECT_FALSE(structure.isInitialized());
}


TEST(StructureIsInitialize3Test, isInitialized)
{
    StructureIsInitialize3 structure;
    EXPECT_FALSE(structure.isInitialized());
}


TEST(StructureIsInitialize4Test, isInitialized)
{
    StructureIsInitialize4 structure;
    EXPECT_FALSE(structure.isInitialized());
}

TEST(StructureIsInitializeVirtualTest, isInitialized)
{
    StructureIsInitializeVirtual structure;
    EXPECT_FALSE(structure.isInitialized());
}


TEST(StructureIsInitialize5Test, isInitialized)
{
    StructureIsInitialize5 structure;
    EXPECT_FALSE(structure.isInitialized());
}


TEST(StructureIsInitialize6Test, isInitialized)
{
    StructureIsInitialize6 structure;
    EXPECT_FALSE(structure.isInitialized());
}

TEST(StructureIsVoidTest, isInitialized)
{
    StructureIsVoid structure;
    EXPECT_TRUE(structure.isInitialized());
}

TEST(StructureIsVoid1Test, isInitialized)
{
    StructureIsVoid1 structure;
    EXPECT_TRUE(structure.isInitialized());
}




