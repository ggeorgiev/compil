#include "structure.h"
#include "unary_container.h"
#include "name.h"

#include "gtest/gtest.h"

#include <iostream>


TEST(StructureTests, fieldIterateEmpty)
{
    compil::StructureSPtr pStructure(new compil::Structure());
    
    std::vector<compil::FieldSPtr> iteration;
    EXPECT_FALSE(pStructure->fieldIterate(iteration));
}

TEST(StructureTests, fieldIterateObligotary)
{
    compil::StructureSPtr pStructure(new compil::Structure());
    
    std::vector<compil::ObjectSPtr> objects;
    
    compil::FieldSPtr pField1(new compil::Field());
    objects.push_back(pField1);
    
    compil::FieldSPtr pField2(new compil::Field());
    objects.push_back(pField2);
    
    pStructure->set_objects(objects);
    
    std::vector<compil::FieldSPtr> iteration;
    EXPECT_TRUE(pStructure->fieldIterate(iteration));
    ASSERT_EQ(2U, iteration.size());
    EXPECT_EQ(pField1, iteration[0]);
    EXPECT_EQ(pField2, iteration[1]);

    EXPECT_FALSE(pStructure->fieldIterate(iteration));
}

TEST(StructureTests, fieldIterateOptional)
{
    compil::StructureSPtr pStructure(new compil::Structure());
    
    std::vector<compil::ObjectSPtr> objects;
    
    compil::FieldSPtr pField1(new compil::Field());
    pField1->set_defaultValue(compil::DefaultValueSPtr(new compil::DefaultValue()));
    objects.push_back(pField1);
    
    compil::FieldSPtr pField2(new compil::Field());
    pField2->set_defaultValue(compil::DefaultValueSPtr(new compil::DefaultValue()));
    objects.push_back(pField2);
    
    pStructure->set_objects(objects);
    
    std::vector<compil::FieldSPtr> iteration;
   
    EXPECT_TRUE(pStructure->fieldIterate(iteration));
    ASSERT_EQ(1U, iteration.size());
    EXPECT_EQ(pField1, iteration[0]);
    
    EXPECT_TRUE(pStructure->fieldIterate(iteration));
    ASSERT_EQ(1U, iteration.size());
    EXPECT_EQ(pField2, iteration[0]);
    
    EXPECT_TRUE(pStructure->fieldIterate(iteration));    
    ASSERT_EQ(2U, iteration.size());
    EXPECT_EQ(pField1, iteration[0]);
    EXPECT_EQ(pField2, iteration[1]);
    
    EXPECT_FALSE(pStructure->fieldIterate(iteration));
}

TEST(StructureTests, fieldIterateMixed)
{
    compil::StructureSPtr pStructure(new compil::Structure());
    
    std::vector<compil::ObjectSPtr> objects;
    
    compil::FieldSPtr pField1(new compil::Field());
    objects.push_back(pField1);
    
    compil::FieldSPtr pField2(new compil::Field());
    pField2->set_defaultValue(compil::DefaultValueSPtr(new compil::DefaultValue()));
    objects.push_back(pField2);

    compil::FieldSPtr pField3(new compil::Field());
    objects.push_back(pField3);
    
    compil::FieldSPtr pField4(new compil::Field());
    pField4->set_defaultValue(compil::DefaultValueSPtr(new compil::DefaultValue()));
    objects.push_back(pField4);
    
    pStructure->set_objects(objects);
    
    std::vector<compil::FieldSPtr> iteration;
   
    EXPECT_TRUE(pStructure->fieldIterate(iteration));
    ASSERT_EQ(2U, iteration.size());
    EXPECT_EQ(pField1, iteration[0]);
    EXPECT_EQ(pField3, iteration[1]);
    
    EXPECT_TRUE(pStructure->fieldIterate(iteration));
    ASSERT_EQ(3U, iteration.size());
    EXPECT_EQ(pField1, iteration[0]);
    EXPECT_EQ(pField2, iteration[1]);
    EXPECT_EQ(pField3, iteration[2]);
    
    EXPECT_TRUE(pStructure->fieldIterate(iteration));
    ASSERT_EQ(3U, iteration.size());
    EXPECT_EQ(pField1, iteration[0]);
    EXPECT_EQ(pField3, iteration[1]);
    EXPECT_EQ(pField4, iteration[2]);
    
    EXPECT_TRUE(pStructure->fieldIterate(iteration));    
    ASSERT_EQ(4U, iteration.size());
    EXPECT_EQ(pField1, iteration[0]);
    EXPECT_EQ(pField2, iteration[1]);
    EXPECT_EQ(pField3, iteration[2]);
    EXPECT_EQ(pField4, iteration[3]);
    
    EXPECT_FALSE(pStructure->fieldIterate(iteration));
}

TEST(StructureTests, DISABLED_fieldIterateVector)
{
    compil::StructureSPtr pStructure(new compil::Structure());
    
    std::vector<compil::ObjectSPtr> objects;
    
    compil::UnaryContainerSPtr pVector(new compil::UnaryContainer());
    compil::NameSPtr pName(new compil::Name());
    pName->set_value("vector");
    pVector->set_name(pName);
    pVector->set_literal(compil::Type::ELiteral::binary());
    pVector->set_kind(compil::Type::EKind::object());
    pVector->set_cast(compil::CastableType::ECast::weak());
    
    compil::FieldSPtr pField(new compil::Field());
    pField->set_type(pVector);
    objects.push_back(pField);
    pStructure->set_objects(objects);
    
    std::vector<compil::FieldSPtr> iteration;
    EXPECT_TRUE(pStructure->fieldIterate(iteration));
    
    
    EXPECT_FALSE(pStructure->fieldIterate(iteration));
}