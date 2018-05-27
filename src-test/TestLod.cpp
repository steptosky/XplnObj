/*
**  Copyright(C) 2017, StepToSky
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1.Redistributions of source code must retain the above copyright notice, this
**    list of conditions and the following disclaimer.
**  2.Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and / or other materials provided with the distribution.
**  3.Neither the name of StepToSky nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
**  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**  Contacts: www.steptosky.com
*/

#include "gtest/gtest.h"
#include "totext.h"

#include "io/ObjValidators.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/ObjMain.h"
#include "TestUtilsObjMesh.h"

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class TestLod : public ::testing::Test {
public:

    ObjMesh * m1 = nullptr;
    ObjMesh * m2 = nullptr;
    ObjMesh * m3 = nullptr;
    ObjMesh * m4 = nullptr;

    void SetUp() override {
        m1 = TestUtilsObjMesh::createObjMesh(TOTEXT(m1), 0.0);
        m2 = TestUtilsObjMesh::createObjMesh(TOTEXT(m2), 1.0);
        m3 = TestUtilsObjMesh::createObjMesh(TOTEXT(m3), 2.0);
        m4 = TestUtilsObjMesh::createObjMesh(TOTEXT(m4), 3.0);
    }

    void TearDown() override {
        delete m1;
        delete m2;
        delete m3;
        delete m4;
    }
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
* Saving meshes in separated lods to the file then read, parse and compare wrote data.
*/
TEST_F(TestLod, lods_grouping) {
    ObjMain mainOut;
    mainOut.pExportOptions.enable(eExportOptions::XOBJ_EXP_MARK_MESH);
    mainOut.pExportOptions.enable(eExportOptions::XOBJ_EXP_DEBUG);
    ObjLodGroup & lgroup1 = mainOut.addLod();
    ObjLodGroup & lgroup2 = mainOut.addLod();
    ObjLodGroup & lgroup3 = mainOut.addLod();

    lgroup1.setObjectName(TOTEXT(lgroup1));
    lgroup1.setNearVal(1000.0);
    lgroup1.setFarVal(1500.0);

    lgroup2.setObjectName(TOTEXT(lgroup2));
    lgroup2.setNearVal(500.0);
    lgroup2.setFarVal(1000.0);

    lgroup3.setObjectName(TOTEXT(lgroup3));
    lgroup3.setNearVal(0.0);
    lgroup3.setFarVal(500.0);

    lgroup1.transform().addObject(m1);
    lgroup2.transform().addObject(m2);
    lgroup3.transform().addObject(m3);
    lgroup3.transform().addObject(m4);

    //-------------------------------------------------------------------------
    // Lods are owners for its children, 
    // so we need to make mesh pointer as nullptr for turning off deleting it by the TestLod class.

    ObjMesh * mesh1 = m1;
    ObjMesh * mesh2 = m2;
    ObjMesh * mesh3 = m3;
    ObjMesh * mesh4 = m4;
    m1 = nullptr;
    m2 = nullptr;
    m3 = nullptr;
    m4 = nullptr;

    //-------------------------------------------------------------------------

    ASSERT_TRUE(mainOut.exportToFile(TOTEXT(TestLod)));

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    mainIn.importFromFile(TOTEXT(TestLod));

    //-------------------------------------------------------------------------
    // WARNING: After export the lods are sorted so they have reversed order!

    ASSERT_EQ(3, mainIn.lodCount());

    //-------------------------

    ObjLodGroup & lod1 = mainIn.lod(2);
    ASSERT_STREQ(lgroup1.objectName().c_str(), lod1.objectName().c_str());
    ASSERT_EQ(1000.0, lod1.nearVal());
    ASSERT_EQ(1500.0, lod1.farVal());
    const Transform::ObjList & objList1 = lod1.transform().objList();
    ASSERT_EQ(1, objList1.size());
    const ObjMesh * obj1 = dynamic_cast<const ObjMesh*>(*objList1.begin());
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh1, obj1));

    //-------------------------

    ObjLodGroup & lod2 = mainIn.lod(1);
    ASSERT_EQ(500.0, lod2.nearVal());
    ASSERT_EQ(1000.0, lod2.farVal());
    ASSERT_STREQ(lgroup2.objectName().c_str(), lod2.objectName().c_str());

    const Transform::ObjList & objList2 = lod2.transform().objList();
    ASSERT_EQ(1, objList2.size());
    const ObjMesh * obj2 = dynamic_cast<const ObjMesh*>(*objList2.begin());
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh2, obj2));

    //-------------------------

    ObjLodGroup & lod3 = mainIn.lod(0);
    ASSERT_EQ(0.0, lod3.nearVal());
    ASSERT_EQ(500.0, lod3.farVal());
    ASSERT_STREQ(lgroup3.objectName().c_str(), lod3.objectName().c_str());

    const Transform::ObjList & objList3 = lod3.transform().objList();
    ASSERT_EQ(2, objList3.size());
    const ObjMesh * objMesh3 = dynamic_cast<const ObjMesh*>(*objList3.begin());
    const ObjMesh * objMesh4 = dynamic_cast<const ObjMesh*>(*(++objList3.begin()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh3, objMesh3));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh4, objMesh4));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
* Lods shall have particular order from nearVal to farVal.
*/
TEST_F(TestLod, lods_sorting) {
    ObjMain main;
    ObjLodGroup & lgroup1 = main.addLod();
    ObjLodGroup & lgroup2 = main.addLod();
    ObjLodGroup & lgroup3 = main.addLod();

    lgroup1.transform().addObject(new ObjMesh());
    lgroup2.transform().addObject(new ObjMesh());
    lgroup3.transform().addObject(new ObjMesh());

    lgroup1.setObjectName(TOTEXT(lgroup1));
    lgroup1.setNearVal(1000.0);
    lgroup1.setFarVal(1500.0);

    lgroup2.setObjectName(TOTEXT(lgroup2));
    lgroup2.setNearVal(500.0);
    lgroup2.setFarVal(1000.0);

    lgroup3.setObjectName(TOTEXT(lgroup3));
    lgroup3.setNearVal(0.0);
    lgroup3.setFarVal(500.0);

    ASSERT_TRUE(main.exportToFile(std::string(TOTEXT(TestLod)).append("Sorting")));
    ASSERT_TRUE(&lgroup3 == &main.lod(0));
    ASSERT_TRUE(&lgroup2 == &main.lod(1));
    ASSERT_TRUE(&lgroup1 == &main.lod(2));
}

/*
* Setters and getters.
*/
TEST(TestLodAccess, property_access) {
    ObjMain main;
    ObjLodGroup & lgroup1 = main.addLod();

    lgroup1.setNearVal(10.0);
    lgroup1.setFarVal(20.0);
    lgroup1.setObjectName("Test");

    ASSERT_EQ(10.0, lgroup1.nearVal());
    ASSERT_EQ(20.0, lgroup1.farVal());
    ASSERT_STREQ("Test", lgroup1.objectName().c_str());
    ASSERT_STREQ("Test", lgroup1.transform().name().c_str());
}

/*
* Validator.
* The lods can be adjustment incorrect so the validator checks this situation.
*/
TEST_F(TestLod, validator) {
    ObjMain main;

    // no linked objects
    ObjLodGroup & lgroup1 = main.addLod();
    ASSERT_FALSE(checkParameters(lgroup1, lgroup1.objectName()));
    lgroup1.transform().addObject(m1);
    m1 = nullptr;

    // incorrect values
    lgroup1.setNearVal(20.0);
    lgroup1.setFarVal(10.0);
    ASSERT_FALSE(checkParameters(lgroup1, lgroup1.objectName()));

    // all ok
    lgroup1.setNearVal(10.0);
    lgroup1.setFarVal(20.0);
    ASSERT_TRUE(checkParameters(lgroup1, lgroup1.objectName()));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
