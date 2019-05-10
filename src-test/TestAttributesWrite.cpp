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

#include "MockIWriter.h"
#include "xpln/obj/ObjMesh.h"
#include "common/AttributeNames.h"
#include "io/writer/ObjWriteAttr.h"
#include "TestWriter.h"

using namespace xobj;
using ::testing::_;
using ::testing::StrEq;
using ::testing::InSequence;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
 * This tests are for checking attributes logic for writing only and they are low level.
 * There are also top level tests (TestAttributesIOLogic) like this.
 */

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<typename T>
std::string strAttrResult(const T & attr) {
    TestWriter w;
	attr.printObj(w);
    if (!w.mResult.empty()) {
        w.mResult.pop_back(); // remove '\n'
    }
    return w.mResult;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, default) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;

    EXPECT_CALL(writer, printLine(_)).Times(0);
    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, boolean_case1) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.mIsDraw = true; // default
    main1.pAttr.mIsDraped = true;
    main1.pAttr.mIsCastShadow = true; // default
    main1.pAttr.mIsSolidForCamera = true;

    // disable
    main2.pAttr.mIsDraw = false;
    main2.pAttr.mIsDraped = false;
    main2.pAttr.mIsCastShadow = false;
    main2.pAttr.mIsSolidForCamera = false;

    main3.pAttr.mIsDraw = false;
    main3.pAttr.mIsDraped = false;
    main3.pAttr.mIsCastShadow = false;
    main3.pAttr.mIsSolidForCamera = false;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case2) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.mIsDraw = true; // default
    main1.pAttr.mIsDraped = true;
    main1.pAttr.mIsCastShadow = true; // default
    main1.pAttr.mIsSolidForCamera = true;

    main2.pAttr.mIsDraw = true; // default
    main2.pAttr.mIsDraped = true;
    main2.pAttr.mIsCastShadow = true; // default
    main2.pAttr.mIsSolidForCamera = true;

    // disable
    main3.pAttr.mIsDraw = false;
    main3.pAttr.mIsDraped = false;
    main3.pAttr.mIsCastShadow = false;
    main3.pAttr.mIsSolidForCamera = false;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case3) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.mIsDraw = true; // default
    main1.pAttr.mIsDraped = true;
    main1.pAttr.mIsCastShadow = true; // default
    main1.pAttr.mIsSolidForCamera = true;

    main2.pAttr.mIsDraw = true; // default
    main2.pAttr.mIsDraped = true;
    main2.pAttr.mIsCastShadow = true; // default
    main2.pAttr.mIsSolidForCamera = true;

    main3.pAttr.mIsDraw = true; // default
    main3.pAttr.mIsDraped = true;
    main3.pAttr.mIsCastShadow = true; // default
    main3.pAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 2, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case4) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.mIsDraw = false;
    main1.pAttr.mIsDraped = false;
    main1.pAttr.mIsCastShadow = false;
    main1.pAttr.mIsSolidForCamera = false;

    // enable
    main2.pAttr.mIsDraw = true; // default
    main2.pAttr.mIsDraped = true;
    main2.pAttr.mIsCastShadow = true; // default
    main2.pAttr.mIsSolidForCamera = true;

    main3.pAttr.mIsDraw = true; // default
    main3.pAttr.mIsDraped = true;
    main3.pAttr.mIsCastShadow = true; // default
    main3.pAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case5) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.mIsDraw = false;
    main1.pAttr.mIsDraped = false;
    main1.pAttr.mIsCastShadow = false;
    main1.pAttr.mIsSolidForCamera = false;

    main2.pAttr.mIsDraw = false;
    main2.pAttr.mIsDraped = false;
    main2.pAttr.mIsCastShadow = false;
    main2.pAttr.mIsSolidForCamera = false;

    // enable
    main3.pAttr.mIsDraw = true; // default
    main3.pAttr.mIsDraped = true;
    main3.pAttr.mIsCastShadow = true; // default
    main3.pAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case6) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.mIsDraw = true; // default
    main1.pAttr.mIsDraped = true;
    main1.pAttr.mIsCastShadow = true; // default
    main1.pAttr.mIsSolidForCamera = true;

    // disable
    main2.pAttr.mIsDraw = false;
    main2.pAttr.mIsDraped = false;
    main2.pAttr.mIsCastShadow = false;
    main2.pAttr.mIsSolidForCamera = false;

    // enable
    main3.pAttr.mIsDraw = true; // default
    main3.pAttr.mIsDraped = true;
    main3.pAttr.mIsCastShadow = true; // default
    main3.pAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 10, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case7) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.mIsDraw = false;
    main1.pAttr.mIsDraped = false;
    main1.pAttr.mIsCastShadow = false;
    main1.pAttr.mIsSolidForCamera = false;

    // enable
    main2.pAttr.mIsDraw = true; // default
    main2.pAttr.mIsDraped = true;
    main2.pAttr.mIsCastShadow = true; // default
    main2.pAttr.mIsSolidForCamera = true;

    // disable
    main3.pAttr.mIsDraw = false;
    main3.pAttr.mIsDraped = false;
    main3.pAttr.mIsCastShadow = false;
    main3.pAttr.mIsSolidForCamera = false;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SHADOW))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 10, 0), attrWriter.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, parameterized_case1) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.pAttr.mShiny = AttrShiny(0.1f);
    main1.pAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.3f);
    main1.pAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main1.pAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, "test");
    main1.pAttr.mCockpit = AttrCockpit(AttrCockpit::region_3);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrShiny(0.1f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrBlend(AttrBlend::no_blend,0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrLightLevel(3.0f, 4.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrCockpit(AttrCockpit::region_3))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(AttrHard::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrShiny::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrBlend::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrPolyOffset::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrLightLevel::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrCockpit::objDisableStr()))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // disable
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 12, 0), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case2) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.pAttr.mShiny = AttrShiny(0.8f);
    main1.pAttr.mBlend = AttrBlend(AttrBlend::shadow_blend, 0.7f);
    main1.pAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main1.pAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, "test");
    main1.pAttr.mCockpit = AttrCockpit(AttrCockpit::region_2);

    main3.pAttr.mHard = AttrHard(ESurface(ESurface::eId::concrete), true);
    main3.pAttr.mShiny = AttrShiny(10.0f);
    main3.pAttr.mBlend = AttrBlend(AttrBlend::shadow_blend, 0.3f);
    main3.pAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main3.pAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, "test2");
    main3.pAttr.mCockpit = AttrCockpit(AttrCockpit::region_3);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrShiny(0.8f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrBlend(AttrBlend::shadow_blend,0.7f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrPolyOffset(4.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrLightLevel(2.0f, 6.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrCockpit(AttrCockpit::region_2))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(AttrHard::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrShiny::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrBlend::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrPolyOffset::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrLightLevel::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrCockpit::objDisableStr()))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrHard(ESurface(ESurface::eId::concrete), true))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrShiny(10.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrBlend(AttrBlend::shadow_blend,0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrLightLevel(3.0f, 4.0f, "test2"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrCockpit(AttrCockpit::region_3))))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // disable
    attrWriter.writeObjAttr(&writer, &main2);
    // enable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 18, 0), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case3) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.pAttr.mShiny = AttrShiny(0.8f);
    main1.pAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.7f);
    main1.pAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main1.pAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, "test");
    main1.pAttr.mCockpit = AttrCockpit(AttrCockpit::region_1);

    main2.pAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main2.pAttr.mShiny = AttrShiny(0.8f);
    main2.pAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.7f);
    main2.pAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main2.pAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, "test");
    main2.pAttr.mCockpit = AttrCockpit(AttrCockpit::region_1);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrShiny(0.8f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrBlend(AttrBlend::no_blend, 0.7f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrPolyOffset(4.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrLightLevel(2.0f, 6.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrCockpit(AttrCockpit::region_1))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(AttrHard::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrShiny::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrBlend::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrPolyOffset::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrLightLevel::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrCockpit::objDisableStr()))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // equals
    attrWriter.writeObjAttr(&writer, &main2);
    // disable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 12, 0), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case4) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.pAttr.mShiny = AttrShiny(0.8f);
    main1.pAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.7f);
    main1.pAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main1.pAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, "test");
    main1.pAttr.mCockpit = AttrCockpit(AttrCockpit::region_1);

    main2.pAttr.mHard = AttrHard(ESurface(ESurface::eId::concrete), true);
    main2.pAttr.mShiny = AttrShiny(10.0f);
    main2.pAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.3f);
    main2.pAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main2.pAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, "test2");
    main2.pAttr.mCockpit = AttrCockpit(AttrCockpit::cockpit);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrShiny(0.8f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrBlend(AttrBlend::no_blend, 0.7f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrPolyOffset(4.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrLightLevel(2.0f, 6.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrCockpit(AttrCockpit::region_1))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrHard(ESurface(ESurface::eId::concrete), true))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrShiny(10.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrBlend(AttrBlend::no_blend, 0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrLightLevel(3.0f, 4.0f, "test2"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrCockpit(AttrCockpit::cockpit))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(AttrHard::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrShiny::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrBlend::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrPolyOffset::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrLightLevel::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrCockpit::objDisableStr()))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // NOT equals
    attrWriter.writeObjAttr(&writer, &main2);
    // disable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 18, 0), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case5) {
    MockWriter writer;
    ObjWriteAttr attrWriter;
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main2.pAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main2.pAttr.mShiny = AttrShiny(0.1f);
    main2.pAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.3f);
    main2.pAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main2.pAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, "test");
    main2.pAttr.mCockpit = AttrCockpit(AttrCockpit::cockpit);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrShiny(0.1f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrBlend(AttrBlend::no_blend, 0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrLightLevel(3.0f, 4.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(AttrCockpit(AttrCockpit::cockpit))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(AttrHard::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrShiny::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrBlend::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrPolyOffset::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrLightLevel::objDisableStr()))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(AttrCockpit::objDisableStr()))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    // enable
    attrWriter.writeObjAttr(&writer, &main2);
    // disable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 12, 0), attrWriter.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
