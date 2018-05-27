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
#include "gmock/gmock.h"

#include "xpln/obj/ObjMesh.h"

#include "xpln/obj/manipulators/AttrManipCmd.h"
#include "xpln/obj/manipulators/AttrManipCmdAxis.h"
#include "xpln/obj/manipulators/AttrManipNoop.h"
#include "xpln/obj/manipulators/AttrManipPush.h"

#include "totext.h"
#include "xpln/obj/IOStatistic.h"
#include "xpln/obj/ObjMain.h"
#include "TestUtilsObjMesh.h"

using namespace xobj;
using ::testing::_;
using ::testing::StrEq;
using ::testing::InSequence;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/* 
 * This tests are for checking mnipulators logic of the chain 'mesh objects->file | file->mesh objects'.
 * So they test writter and reader for mnipulators of mesh objects.
 * The manipulators have some logic for writing and reading you can see it in other tests like TestManipWrite.
 * Acttualy this tests are like as TestManipWrite except they test full chain (not only writing).
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class TestManipIOLogic : public ::testing::Test {

    TestManipIOLogic(const TestManipIOLogic &) = delete;
    TestManipIOLogic & operator =(const TestManipIOLogic &) = delete;

public:

    TestManipIOLogic() = default;
    virtual ~TestManipIOLogic() = default;

public:

    static void extractMesh(const ObjMain & inMain, size_t inLodNumber, size_t inMeshNumber, ObjMesh *& outMesh) {
        ASSERT_TRUE(inLodNumber < inMain.lodCount());
        const ObjLodGroup & inLGroup = inMain.lod(inLodNumber);
        ASSERT_TRUE(inMeshNumber < inLGroup.transform().objList().size());
        auto iterator = inLGroup.transform().objList().begin();
        for (size_t i = 0; i < inMeshNumber; ++i) {
            ++iterator;
        }
        ObjAbstract * obj = *(iterator);
        ASSERT_EQ(eObjectType::OBJ_MESH, obj->objType());
        outMesh = static_cast<ObjMesh *>(obj);
    }

    template<typename MANIP>
    static void extractManip(const ObjMain & inMain, size_t inLodNumber, size_t inMeshNumber, const MANIP *& outAttr) {
        ObjMesh * inM = nullptr;
        extractMesh(inMain, inLodNumber, inMeshNumber, inM);
        outAttr = inM->pAttr.manipulator() == nullptr ? nullptr : static_cast<const MANIP *>(inM->pAttr.manipulator());
    }

    AttrManipCmd mManipComd;
    AttrManipCmdAxis mManipComdAxis;
    AttrManipNoop mManipNoop;
    AttrManipPush mManipPush;
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

// Manipulators are not set
TEST_F(TestManipIOLogic, case_1_no_manips) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    outLGroup.transform().addObject(TestUtilsObjMesh::createObjMesh("m0", 0.0));
    outLGroup.transform().addObject(TestUtilsObjMesh::createObjMesh("m1", 1.0));
    outLGroup.transform().addObject(TestUtilsObjMesh::createObjMesh("m2", 2.0));
    outLGroup.transform().addObject(TestUtilsObjMesh::createObjMesh("m3", 3.0));

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(0, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(0, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_EQ(nullptr, inManip);

    //-----------------------------
}

TEST_F(TestManipIOLogic, case_2) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mManipComd.setCommand("test");
    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    // No Manip
    // mObjMesh2
    // mObjMesh3
    // mObjMesh4

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_EQ(nullptr, inManip);
}

TEST_F(TestManipIOLogic, case_3) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mManipComd.setCommand("test");
    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    outM2->pAttr.setManipulator(mManipComd.clone());
    // No Manip
    // mObjMesh3
    // mObjMesh4

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_EQ(nullptr, inManip);
}

TEST_F(TestManipIOLogic, case_4) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mManipComd.setCommand("test");
    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    outM2->pAttr.setManipulator(mManipComd.clone());
    outM3->pAttr.setManipulator(mManipComd.clone());
    // No Manip
    // mObjMesh4

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_EQ(nullptr, inManip);
}

TEST_F(TestManipIOLogic, case_5) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mManipComd.setCommand("test");
    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    outM2->pAttr.setManipulator(mManipComd.clone());
    outM3->pAttr.setManipulator(mManipComd.clone());
    outM4->pAttr.setManipulator(mManipComd.clone());

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));
}

TEST_F(TestManipIOLogic, case_6) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    // Manip
    mManipComd.setCommand("test1");
    outM1->pAttr.setManipulator(mManipComd.clone());
    // Manip
    mManipComd.setCommand("test2");
    outM2->pAttr.setManipulator(mManipComd.clone());
    // Manip
    mManipComd.setCommand("test3");
    outM3->pAttr.setManipulator(mManipComd.clone());
    // Manip
    mManipComd.setCommand("test4");
    outM4->pAttr.setManipulator(mManipComd.clone());

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(4, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(4, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    mManipComd.setCommand("test1");
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_NE(nullptr, inManip);
    mManipComd.setCommand("test2");
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    mManipComd.setCommand("test3");
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_NE(nullptr, inManip);
    mManipComd.setCommand("test4");
    ASSERT_TRUE(inManip->equals(&mManipComd));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST_F(TestManipIOLogic, case_7) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    // Manip
    outM2->pAttr.setManipulator(mManipComdAxis.clone());
    // Manip
    outM3->pAttr.setManipulator(mManipNoop.clone());
    // Manip
    outM4->pAttr.setManipulator(mManipPush.clone());

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(4, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(4, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComdAxis));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipNoop));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipPush));
}

TEST_F(TestManipIOLogic, case_8) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    // Manip
    outM2->pAttr.setManipulator(mManipComdAxis.clone());
    // Manip
    outM3->pAttr.setManipulator(mManipNoop.clone());
    // No Manip
    // mObjMesh4

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(3, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(3, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComdAxis));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipNoop));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_EQ(nullptr, inManip);
}

TEST_F(TestManipIOLogic, case_9) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    outM2->pAttr.setManipulator(mManipComd.clone());
    // Manip
    outM3->pAttr.setManipulator(mManipNoop.clone());
    // Manip
    outM4->pAttr.setManipulator(mManipPush.clone());

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(3, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(3, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipNoop));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipPush));
}

TEST_F(TestManipIOLogic, case_10) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    // No Manip
    // mObjMesh2
    // Manip
    outM3->pAttr.setManipulator(mManipNoop.clone());
    // Manip
    outM4->pAttr.setManipulator(mManipPush.clone());

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(3, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(3, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipNoop));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipPush));
}

TEST_F(TestManipIOLogic, case_11) {
    ObjMain outObj;
    IOStatistic stat;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    // Manip
    outM1->pAttr.setManipulator(mManipComd.clone());
    // No Manip
    // mObjMesh2
    // Manip
    outM3->pAttr.setManipulator(mManipNoop.clone());
    // No Manip
    // mObjMesh4

    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(2, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIOLogic), stat));
    ASSERT_EQ(2, stat.pTrisManipCount);

    //-----------------------------

    const AttrManipBase * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 0, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipComd));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 1, inManip));
    ASSERT_EQ(nullptr, inManip);

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 2, inManip));
    ASSERT_NE(nullptr, inManip);
    ASSERT_TRUE(inManip->equals(&mManipNoop));

    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipBase>(inObj, 0, 3, inManip));
    ASSERT_EQ(nullptr, inManip);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
