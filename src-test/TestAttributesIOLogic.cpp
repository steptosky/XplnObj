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

#include "xpln/obj/ObjMesh.h"

#include "totext.h"
#include "xpln/obj/IOStatistic.h"
#include "xpln/obj/ObjMain.h"
#include "TestUtilsObjMesh.h"

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
 * This tests are for checking attributes logic of the chain 'mesh objects->file | file->mesh objects'.
 * So they test writer and reader for attribute of mesh objects.
 * The attributes have some logic for writing and reading you can see it in other tests like TestAttributesWrite.
 * Actually this tests are like as TestAttributesWrite except they test full chain (not only writing) for one attribute.
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class TestAttributesIOLogic : public ::testing::Test {
public:

    TestAttributesIOLogic(const TestAttributesIOLogic &) = delete;
    TestAttributesIOLogic & operator =(const TestAttributesIOLogic &) = delete;

    TestAttributesIOLogic() = default;
    virtual ~TestAttributesIOLogic() = default;

    static void extractMesh(const ObjMain & inMain, size_t inLodNumber, size_t inMeshNumber, ObjMesh *& outMesh) {
        ASSERT_TRUE(inLodNumber < inMain.lods().size());
        const ObjLodGroup & inLGroup = *inMain.lods().at(inLodNumber);
        ASSERT_TRUE(inMeshNumber < inLGroup.transform().objList().size());
        auto iterator = inLGroup.transform().objList().begin();
        for (size_t i = 0; i < inMeshNumber; ++i) {
            ++iterator;
        }
        ObjAbstract * obj = iterator->get();
        ASSERT_EQ(eObjectType::OBJ_MESH, obj->objType());
        outMesh = static_cast<ObjMesh *>(obj);
    }

    AttrPolyOffset mAttrPolyOffset;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST_F(TestAttributesIOLogic, case_1) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_1.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mAttrPolyOffset.setOffset(1.0f);
    // Attr
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    // No Attr
    // mObjMesh2
    // mObjMesh3
    // mObjMesh4

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(2, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(2, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);
}

TEST_F(TestAttributesIOLogic, case_2) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_2.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mAttrPolyOffset.setOffset(1.0f);
    // Attr
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    outM2->pAttr.mPolyOffset = mAttrPolyOffset;
    // No Attr
    // mObjMesh3
    // mObjMesh4

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(2, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(2, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);
}

TEST_F(TestAttributesIOLogic, case_3) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_3.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mAttrPolyOffset.setOffset(1.0f);
    // Attr
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    outM2->pAttr.mPolyOffset = mAttrPolyOffset;
    outM3->pAttr.mPolyOffset = mAttrPolyOffset;
    // No Attr
    // mObjMesh4

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(2, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(2, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);
}

TEST_F(TestAttributesIOLogic, case_4) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_4.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mAttrPolyOffset.setOffset(1.0f);
    // Attr
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    outM2->pAttr.mPolyOffset = mAttrPolyOffset;
    outM3->pAttr.mPolyOffset = mAttrPolyOffset;
    outM4->pAttr.mPolyOffset = mAttrPolyOffset;

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(mAttrPolyOffset, inM->pAttr.mPolyOffset);
}

TEST_F(TestAttributesIOLogic, case_5) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_5.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    // Attr
    mAttrPolyOffset.setOffset(1.0f);
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    // Attr
    mAttrPolyOffset.setOffset(2.0f);
    outM2->pAttr.mPolyOffset = mAttrPolyOffset;
    // Attr
    mAttrPolyOffset.setOffset(3.0f);
    outM3->pAttr.mPolyOffset = mAttrPolyOffset;
    // Attr
    mAttrPolyOffset.setOffset(4.0f);
    outM4->pAttr.mPolyOffset = mAttrPolyOffset;

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(4, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(4, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(AttrPolyOffset(1.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(AttrPolyOffset(2.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(AttrPolyOffset(3.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(AttrPolyOffset(4.0f), inM->pAttr.mPolyOffset);
}

TEST_F(TestAttributesIOLogic, case_6) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_6.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mAttrPolyOffset.setOffset(1.0f);
    // Attr
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    outM2->pAttr.mPolyOffset = mAttrPolyOffset;
    // Attr
    mAttrPolyOffset.setOffset(2.0f);
    outM3->pAttr.mPolyOffset = mAttrPolyOffset;
    // Attr
    mAttrPolyOffset.setOffset(3.0f);
    outM4->pAttr.mPolyOffset = mAttrPolyOffset;

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(3, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(3, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(AttrPolyOffset(1.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(AttrPolyOffset(1.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(AttrPolyOffset(2.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(AttrPolyOffset(3.0f), inM->pAttr.mPolyOffset);
}

TEST_F(TestAttributesIOLogic, case_7) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_7.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mAttrPolyOffset.setOffset(1.0f);
    // Attr
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    // No Attr
    // mObjMesh2
    // Attr
    mAttrPolyOffset.setOffset(2.0f);
    outM3->pAttr.mPolyOffset = mAttrPolyOffset;
    // Attr
    mAttrPolyOffset.setOffset(3.0f);
    outM4->pAttr.mPolyOffset = mAttrPolyOffset;

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(4, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(4, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(AttrPolyOffset(1.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(AttrPolyOffset(2.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(AttrPolyOffset(3.0f), inM->pAttr.mPolyOffset);
}

TEST_F(TestAttributesIOLogic, case_8) {
    const auto fileName = XOBJ_PATH("TestAttributesIOLogic-case_8.obj");
    //-----------------------------
    ObjMain outObj;
    ObjLodGroup & outLGroup = outObj.addLod();
    ObjMesh * outM1 = TestUtilsObjMesh::createObjMesh("m0", 0.0);
    ObjMesh * outM2 = TestUtilsObjMesh::createObjMesh("m1", 1.0);
    ObjMesh * outM3 = TestUtilsObjMesh::createObjMesh("m2", 2.0);
    ObjMesh * outM4 = TestUtilsObjMesh::createObjMesh("m3", 3.0);
    outLGroup.transform().addObject(outM1);
    outLGroup.transform().addObject(outM2);
    outLGroup.transform().addObject(outM3);
    outLGroup.transform().addObject(outM4);

    mAttrPolyOffset.setOffset(1.0f);
    // Attr
    outM1->pAttr.mPolyOffset = mAttrPolyOffset;
    // No Attr
    // mObjMesh2
    // Attr
    mAttrPolyOffset.setOffset(2.0f);
    outM3->pAttr.mPolyOffset = mAttrPolyOffset;
    // No Attr
    // mObjMesh4

    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(4, expContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(4, impContext.statistic().pTrisAttrCount);

    //-----------------------------

    ObjMesh * inM = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 0, inM));
    ASSERT_EQ(AttrPolyOffset(1.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 1, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 2, inM));
    ASSERT_EQ(AttrPolyOffset(2.0f), inM->pAttr.mPolyOffset);

    ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, 0, 3, inM));
    ASSERT_EQ(AttrPolyOffset(), inM->pAttr.mPolyOffset);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
