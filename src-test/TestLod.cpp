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

#include <gtest/gtest.h>

#include "totext.h"

#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/ObjMain.h"
#include "TestUtilsObjMesh.h"
#include <algorithms/LodsAlg.h>

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
 * Saving meshes in separated LODs to the file then read, parse and compare wrote data.
 */
TEST_F(TestLod, lods_grouping) {
    const auto fileName = XOBJ_PATH("TestLod-lods_grouping.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.mExportOptions.enable(eExportOptions::XOBJ_EXP_MARK_MESH);
    mainOut.mExportOptions.enable(eExportOptions::XOBJ_EXP_DEBUG);
    ObjLodGroup & lGroup1 = mainOut.addLod();
    ObjLodGroup & lGroup2 = mainOut.addLod();
    ObjLodGroup & lGroup3 = mainOut.addLod();

    lGroup1.setObjectName(TOTEXT(lGroup1));
    lGroup1.setNearVal(1000.0);
    lGroup1.setFarVal(1500.0);

    lGroup2.setObjectName(TOTEXT(lGroup2));
    lGroup2.setNearVal(500.0);
    lGroup2.setFarVal(1000.0);

    lGroup3.setObjectName(TOTEXT(lGroup3));
    lGroup3.setNearVal(0.0);
    lGroup3.setFarVal(500.0);

    lGroup1.transform().addObject(m1);
    lGroup2.transform().addObject(m2);
    lGroup3.transform().addObject(m3);
    lGroup3.transform().addObject(m4);

    //-------------------------------------------------------------------------
    // LODs are owners for its children, 
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

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));

    //-------------------------------------------------------------------------
    // WARNING: After export the LODs are sorted so they have reversed order!

    ASSERT_EQ(3, mainIn.lods().size());

    //-------------------------

    ObjLodGroup & lod1 = *mainIn.lods().at(2);
    ASSERT_STREQ(lGroup1.objectName().c_str(), lod1.objectName().c_str());
    ASSERT_EQ(1000.0, lod1.nearVal());
    ASSERT_EQ(1500.0, lod1.farVal());
    const Transform::ObjList & objList1 = lod1.transform().objList();
    ASSERT_EQ(1, objList1.size());
    const auto * obj1 = dynamic_cast<const ObjMesh*>(objList1.begin()->get());
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh1, obj1));

    //-------------------------

    ObjLodGroup & lod2 = *mainIn.lods().at(1);
    ASSERT_EQ(500.0, lod2.nearVal());
    ASSERT_EQ(1000.0, lod2.farVal());
    ASSERT_STREQ(lGroup2.objectName().c_str(), lod2.objectName().c_str());

    const Transform::ObjList & objList2 = lod2.transform().objList();
    ASSERT_EQ(1, objList2.size());
    const auto * obj2 = dynamic_cast<const ObjMesh*>(objList2.begin()->get());
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh2, obj2));

    //-------------------------

    ObjLodGroup & lod3 = *mainIn.lods().at(0);
    ASSERT_EQ(0.0, lod3.nearVal());
    ASSERT_EQ(500.0, lod3.farVal());
    ASSERT_STREQ(lGroup3.objectName().c_str(), lod3.objectName().c_str());

    const Transform::ObjList & objList3 = lod3.transform().objList();
    ASSERT_EQ(2, objList3.size());
    const auto * objMesh3 = dynamic_cast<const ObjMesh*>(objList3.begin()->get());
    const auto * objMesh4 = dynamic_cast<const ObjMesh*>((++objList3.begin())->get());
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh3, objMesh3));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMesh(mesh4, objMesh4));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
 * LODs shall have particular order from nearVal to farVal.
 */
TEST_F(TestLod, lods_sorting) {
    const auto fileName = XOBJ_PATH("TestLod-lods_sorting.obj");
    //-----------------------------
    ObjMain main;
    ObjLodGroup & lGroup1 = main.addLod();
    ObjLodGroup & lGroup2 = main.addLod();
    ObjLodGroup & lGroup3 = main.addLod();

    lGroup1.transform().addObject(new ObjMesh());
    lGroup2.transform().addObject(new ObjMesh());
    lGroup3.transform().addObject(new ObjMesh());

    lGroup1.setObjectName(TOTEXT(lGroup1));
    lGroup1.setNearVal(1000.0);
    lGroup1.setFarVal(1500.0);

    lGroup2.setObjectName(TOTEXT(lGroup2));
    lGroup2.setNearVal(500.0);
    lGroup2.setFarVal(1000.0);

    lGroup3.setObjectName(TOTEXT(lGroup3));
    lGroup3.setNearVal(0.0);
    lGroup3.setFarVal(500.0);

    ExportContext expContext(fileName);
    ASSERT_TRUE(main.exportObj(expContext));
    ASSERT_TRUE(&lGroup3 == &*main.lods().at(0));
    ASSERT_TRUE(&lGroup2 == &*main.lods().at(1));
    ASSERT_TRUE(&lGroup1 == &*main.lods().at(2));
}

/*
 * Setters and getters.
 */
TEST(TestLodAccess, property_access) {
    ObjMain main;
    ObjLodGroup & lGroup1 = main.addLod();

    lGroup1.setNearVal(10.0);
    lGroup1.setFarVal(20.0);
    lGroup1.setObjectName("Test");

    ASSERT_EQ(10.0, lGroup1.nearVal());
    ASSERT_EQ(20.0, lGroup1.farVal());
    ASSERT_STREQ("Test", lGroup1.objectName().c_str());
    ASSERT_STREQ("Test", lGroup1.transform().name().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST_F(TestLod, validator_near_far_values_case1) {
    ObjMain main;

    ObjLodGroup & lGroup1 = main.addLod();
    ObjLodGroup & lGroup2 = main.addLod();
    lGroup1.transform().addObject(m1);
    lGroup2.transform().addObject(m2);
    m1 = nullptr;
    m2 = nullptr;
    lGroup2.setNearVal(0.0f);
    lGroup2.setFarVal(100.0f);

    // far greater than near
    lGroup1.setNearVal(20.0f);
    lGroup1.setFarVal(10.0f);
    ASSERT_FALSE(LodsAlg::validate(main.lods(), main.objectName()));

    // far equals near
    lGroup1.setNearVal(20.0f);
    lGroup1.setFarVal(20.0f);
    ASSERT_FALSE(LodsAlg::validate(main.lods(), main.objectName()));

    // all okay
    lGroup1.setNearVal(0.0f);
    lGroup1.setFarVal(20.0f);
    ASSERT_TRUE(LodsAlg::validate(main.lods(), main.objectName()));
}

TEST_F(TestLod, validator_near_far_values_case2) {
    ObjMain main;

    ObjLodGroup & lGroup1 = main.addLod();
    lGroup1.transform().addObject(m1);
    m1 = nullptr;

    // one lod but starts not from 0.0 
    lGroup1.setNearVal(10.0);
    lGroup1.setFarVal(20.0);
    ASSERT_FALSE(LodsAlg::validate(main.lods(), main.objectName()));

    // all okay
    lGroup1.setNearVal(0.0);
    lGroup1.setFarVal(20.0);
    ASSERT_TRUE(LodsAlg::validate(main.lods(), main.objectName()));
}

TEST_F(TestLod, validator_no_objects) {
    ObjMain main;

    ObjLodGroup & lGroup1 = main.addLod();
    ASSERT_FALSE(LodsAlg::validate(main.lods(), main.objectName()));
    lGroup1.transform().addObject(m1);
    m1 = nullptr;
}

TEST_F(TestLod, validator_animation) {
    ObjMain main;

    ObjLodGroup & lGroup1 = main.addLod();
    lGroup1.transform().addObject(m1);
    lGroup1.transform().mAnimTrans.emplace_back(AnimTrans());
    lGroup1.transform().mAnimTrans.back().mKeys.emplace_back(AnimTransKey(1.0f, 1.0f, 1.0f, 1.0f));
    lGroup1.transform().mAnimTrans.back().mKeys.emplace_back(AnimTransKey(2.0f, 2.0f, 2.0f, 2.0f));
    m1 = nullptr;

    lGroup1.setNearVal(0.0);
    lGroup1.setFarVal(20.0);
    ASSERT_FALSE(LodsAlg::validate(main.lods(), main.objectName()));
}

TEST_F(TestLod, validator_identical_lods) {
    ObjMain main;

    ObjLodGroup & lGroup1 = main.addLod(new ObjLodGroup(TOTEXT(lGroup1), 0.0f, 100.0f));
    ObjLodGroup & lGroup2 = main.addLod(new ObjLodGroup(TOTEXT(lGroup1), 0.0f, 100.0f));
    lGroup1.transform().addObject(m1);
    lGroup2.transform().addObject(m2);
    ASSERT_FALSE(LodsAlg::validate(main.lods(), main.objectName()));
    m1 = nullptr;
    m2 = nullptr;
}

TEST_F(TestLod, validator_attr_hard) {
    ObjMain main;

    // no linked objects
    ObjLodGroup & lGroup1 = main.addLod(new ObjLodGroup(TOTEXT(lGroup1), 0.0f, 100.0f));
    ObjLodGroup & lGroup2 = main.addLod(new ObjLodGroup(TOTEXT(lGroup2), 100.0f, 200.0f));
    lGroup1.transform().addObject(m1);
    lGroup2.transform().addObject(m2);
    m2->mAttr.mHard = AttrHard(ESurface(ESurface::grass), false);
    ASSERT_FALSE(LodsAlg::validate(main.lods(), main.objectName()));
    m1 = nullptr;
    m2 = nullptr;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
