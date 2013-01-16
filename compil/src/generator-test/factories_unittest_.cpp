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
// based on code from Adam Bowen posted on stackoverflow.com

#include "factories_another_factory_package.h"
#include "factories.h"

#include "gtest/gtest.h"

namespace factories
{

TEST(FactoriesTest, construct)
{
}

TEST(FactoriesTest, create_downcast)
{
    ObjSPtr pObj(new Obj());
    ObjSPtr pObjA(new ObjA());
    ObjSPtr pObjB1(new ObjB1());
    
    EXPECT_FALSE(HierarchyObjFactory::downcastObjA(pObj));
    EXPECT_TRUE(HierarchyObjFactory::downcastObjA(pObjA));
    EXPECT_FALSE(HierarchyObjFactory::downcastObjA(pObjB1));
    
    EXPECT_FALSE(HierarchyObjFactory::downcastObjB1(pObj));
    EXPECT_FALSE(HierarchyObjFactory::downcastObjB1(pObjA));
    EXPECT_TRUE(HierarchyObjFactory::downcastObjB1(pObjB1));
}

TEST(FactoriesTest, hierarchyClone)
{
    {
        ObjSPtr pObj(new ObjA());
        pObj->set_o(1);
        ObjSPtr pCloneObj = HierarchyObjFactory::clone(pObj);
        EXPECT_EQ(pObj->o(), pCloneObj->o());
        pObj->set_o(pObj->o() + 1);
        EXPECT_NE(pObj->o(), pCloneObj->o());
        
        ObjASPtr pObjA = HierarchyObjFactory::downcastObjA(pObj);
        pObjA->set_a(2);
        pCloneObj = HierarchyObjFactory::clone(pObj);
        ObjASPtr pCloneObjA = HierarchyObjFactory::downcastObjA(pCloneObj);
        EXPECT_EQ(pObjA->a(), pCloneObjA->a());
        pObjA->set_a(pObjA->a() + 1);
        EXPECT_NE(pObjA->a(), pCloneObjA->a());
    }
    
    {
        ObjSPtr pObj(new ObjB1());
        pObj->set_o(1);
        ObjSPtr pCloneObj = HierarchyObjFactory::clone(pObj);
        EXPECT_EQ(pObj->o(), pCloneObj->o());
        pObj->set_o(pObj->o() + 1);
        EXPECT_NE(pObj->o(), pCloneObj->o());
        
        ObjB1SPtr pObjB1 = HierarchyObjFactory::downcastObjB1(pObj);
        pObjB1->set_b1(3);
        pCloneObj = HierarchyObjFactory::clone(pObj);
        ObjB1SPtr pCloneObjB1 = HierarchyObjFactory::downcastObjB1(pCloneObj);
        EXPECT_EQ(pObjB1->b1(), pCloneObjB1->b1());
        pObjB1->set_b1(pObjB1->b1() + 1);
        EXPECT_NE(pObjB1->b1(), pCloneObjB1->b1());
    }
}

TEST(FactoriesTest, pluginDowncast)
{
    ObjSPtr pObj(new ObjA());
    ObjSPtr pObjNull;
    
    EXPECT_TRUE(ObjA::downcast(pObj));
    EXPECT_FALSE(ObjA::downcast(pObjNull));
}

TEST(FactoriesTest, pluginClone)
{
    {
        ObjASPtr pObjA(new ObjA());
        pObjA->set_o(1);
        pObjA->set_a(2);
       
        ObjASPtr pCloneObjA(PluginObjFactory::clone<ObjA>(*pObjA));
        EXPECT_EQ(pObjA->o(), pCloneObjA->o());
        pObjA->set_o(pObjA->o() + 1);
        EXPECT_NE(pObjA->o(), pCloneObjA->o());
        
        EXPECT_EQ(pObjA->a(), pCloneObjA->a());
        pObjA->set_a(pObjA->a() + 1);
        EXPECT_NE(pObjA->a(), pCloneObjA->a());
    }
    
    {
        IObjA1SPtr pIObjA1 = IObjA1::Builder().set_o(1).set_a(2).set_a1(3).finalize();
       
        IObjASPtr pCloneIObjA = IObjA::Builder(*pIObjA1).finalize();
        EXPECT_NE(pIObjA1, pCloneIObjA);
        EXPECT_EQ(pIObjA1->o(), pCloneIObjA->o());
        EXPECT_EQ(pIObjA1->a(), pCloneIObjA->a());
        
        IObjA1SPtr pCloneIObjA1 = IObjA1::downcast(pCloneIObjA);
        EXPECT_EQ(pIObjA1->a1(), pCloneIObjA1->a1());
    }
}

TEST(FactoriesTest, PluginObjFactory)
{
    EXPECT_TRUE(PluginObjFactory::isParent(Obj::staticInprocId(), ObjA::staticInprocId()));
    EXPECT_TRUE(PluginObjFactory::isParent(Obj::staticInprocId(), ObjA2::staticInprocId()));
    EXPECT_TRUE(PluginObjFactory::isParent(ObjA::staticInprocId(), ObjA2::staticInprocId()));
    
    EXPECT_FALSE(PluginObjFactory::isParent(ObjA2::staticInprocId(), ObjA::staticInprocId()));
    EXPECT_FALSE(PluginObjFactory::isParent(ObjA2::staticInprocId(), Obj::staticInprocId()));
    EXPECT_FALSE(PluginObjFactory::isParent(ObjA::staticInprocId(), Obj::staticInprocId()));
    
    Obj obj;
    EXPECT_TRUE(PluginObjFactory::isDerivedFrom<Obj>(obj));
    EXPECT_FALSE(PluginObjFactory::isDerivedFrom<ObjA>(obj));
    EXPECT_FALSE(PluginObjFactory::isDerivedFrom<ObjA2>(obj));
    
    ObjA2 objA2;
    EXPECT_TRUE(PluginObjFactory::isDerivedFrom<Obj>(objA2));
    EXPECT_TRUE(PluginObjFactory::isDerivedFrom<ObjA>(objA2));
    EXPECT_TRUE(PluginObjFactory::isDerivedFrom<ObjA2>(objA2));
}

TEST(FactoriesTest, MObjectFactory_create)
{
    IMObjectObjFactory::create(1, 2);

    IMObjectObj2Factory::create(1, 2, 3, 4);
}

}
