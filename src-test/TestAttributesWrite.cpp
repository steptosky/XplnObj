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

#include "ph/stdafx.h"
#include <gtest/gtest.h>

#include "MockIWriter.h"
#include "xpln/obj/ObjMesh.h"
#include "common/AttributeNames.h"
#include "converters/ObjAttrString.h"
#include "io/writer/ObjWriteAttr.h"
#include "io/writer/ObjWriteManip.h"

using namespace xobj;
using ::testing::_;
using ::testing::StrEq;
using ::testing::InSequence;
ObjWriteManip gObjWriteManip;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
 * This tests are for checking attributes logic for writing only and they are low level.
 * There are also top level tests (TestAttributesIOLogic) like this.
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, default) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;

    EXPECT_CALL(writer, printLine(_)).Times(0);
    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, boolean_case1) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.setDraw(true); // default
    main1.pAttr.setDraped(true);
    main1.pAttr.setCastShadow(true); // default
    main1.pAttr.setSolidForCamera(true);

    // disable
    main2.pAttr.setDraw(false);
    main2.pAttr.setDraped(false);
    main2.pAttr.setCastShadow(false);
    main2.pAttr.setSolidForCamera(false);

    main3.pAttr.setDraw(false);
    main3.pAttr.setDraped(false);
    main3.pAttr.setCastShadow(false);
    main3.pAttr.setSolidForCamera(false);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(6, attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case2) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.setDraw(true); // default
    main1.pAttr.setDraped(true);
    main1.pAttr.setCastShadow(true); // default
    main1.pAttr.setSolidForCamera(true);

    main2.pAttr.setDraw(true); // default
    main2.pAttr.setDraped(true);
    main2.pAttr.setCastShadow(true); // default
    main2.pAttr.setSolidForCamera(true);

    // disable
    main3.pAttr.setDraw(false);
    main3.pAttr.setDraped(false);
    main3.pAttr.setCastShadow(false);
    main3.pAttr.setSolidForCamera(false);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(6, attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case3) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.setDraw(true); // default
    main1.pAttr.setDraped(true);
    main1.pAttr.setCastShadow(true); // default
    main1.pAttr.setSolidForCamera(true);

    main2.pAttr.setDraw(true); // default
    main2.pAttr.setDraped(true);
    main2.pAttr.setCastShadow(true); // default
    main2.pAttr.setSolidForCamera(true);

    main3.pAttr.setDraw(true); // default
    main3.pAttr.setDraped(true);
    main3.pAttr.setCastShadow(true); // default
    main3.pAttr.setSolidForCamera(true);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(2, attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case4) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.setDraw(false);
    main1.pAttr.setDraped(false);
    main1.pAttr.setCastShadow(false);
    main1.pAttr.setSolidForCamera(false);

    // enable
    main2.pAttr.setDraw(true); // default
    main2.pAttr.setDraped(true);
    main2.pAttr.setCastShadow(true); // default
    main2.pAttr.setSolidForCamera(true);

    main3.pAttr.setDraw(true); // default
    main3.pAttr.setDraped(true);
    main3.pAttr.setCastShadow(true); // default
    main3.pAttr.setSolidForCamera(true);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(6, attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case5) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.setDraw(false);
    main1.pAttr.setDraped(false);
    main1.pAttr.setCastShadow(false);
    main1.pAttr.setSolidForCamera(false);

    main2.pAttr.setDraw(false);
    main2.pAttr.setDraped(false);
    main2.pAttr.setCastShadow(false);
    main2.pAttr.setSolidForCamera(false);

    // enable
    main3.pAttr.setDraw(true); // default
    main3.pAttr.setDraped(true);
    main3.pAttr.setCastShadow(true); // default
    main3.pAttr.setSolidForCamera(true);

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(6, attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case6) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.pAttr.setDraw(true); // default
    main1.pAttr.setDraped(true);
    main1.pAttr.setCastShadow(true); // default
    main1.pAttr.setSolidForCamera(true);

    // disable
    main2.pAttr.setDraw(false);
    main2.pAttr.setDraped(false);
    main2.pAttr.setCastShadow(false);
    main2.pAttr.setSolidForCamera(false);

    // enable
    main3.pAttr.setDraw(true); // default
    main3.pAttr.setDraped(true);
    main3.pAttr.setCastShadow(true); // default
    main3.pAttr.setSolidForCamera(true);

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

    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(10, attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case7) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.setDraw(false);
    main1.pAttr.setDraped(false);
    main1.pAttr.setCastShadow(false);
    main1.pAttr.setSolidForCamera(false);

    // enable
    main2.pAttr.setDraw(true); // default
    main2.pAttr.setDraped(true);
    main2.pAttr.setCastShadow(true); // default
    main2.pAttr.setSolidForCamera(true);

    // disable
    main3.pAttr.setDraw(false);
    main3.pAttr.setDraped(false);
    main3.pAttr.setCastShadow(false);
    main3.pAttr.setSolidForCamera(false);

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

    attrWriter.write(&writer, &main1);
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(10, attrWriter.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, parameterized_case1) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.setHard(AttrHard(ESurface(ESurface::eId::dirt), false));
    main1.pAttr.setShiny(AttrShiny(0.1f));
    main1.pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.3f));
    main1.pAttr.setPolyOffset(AttrPolyOffset(5.0f));
    main1.pAttr.setLightLevel(AttrLightLevel(3.0f, 4.0f, "test"));
    main1.pAttr.setCockpit(AttrCockpit(AttrCockpit::region_3));

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny(0.1f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend(AttrBlend::no_blend,0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrLightLevel(3.0f, 4.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrCockpit(AttrCockpit::region_3))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_HARD))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(0.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_LIGHT_LEVEL_RESET))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);

    // enable
    attrWriter.write(&writer, &main1);
    // disable
    attrWriter.write(&writer, &main2);
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(12, attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case2) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.setHard(AttrHard(ESurface(ESurface::eId::dirt), false));
    main1.pAttr.setShiny(AttrShiny(0.8f));
    main1.pAttr.setBlend(AttrBlend(AttrBlend::shadow_blend, 0.7f));
    main1.pAttr.setPolyOffset(AttrPolyOffset(4.0f));
    main1.pAttr.setLightLevel(AttrLightLevel(2.0f, 6.0f, "test"));
    main1.pAttr.setCockpit(AttrCockpit(AttrCockpit::region_2));

    main3.pAttr.setHard(AttrHard(ESurface(ESurface::eId::concrete), true));
    main3.pAttr.setShiny(AttrShiny(10.0f));
    main3.pAttr.setBlend(AttrBlend(AttrBlend::shadow_blend, 0.3f));
    main3.pAttr.setPolyOffset(AttrPolyOffset(5.0f));
    main3.pAttr.setLightLevel(AttrLightLevel(3.0f, 4.0f, "test2"));
    main3.pAttr.setCockpit(AttrCockpit(AttrCockpit::region_3));

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny(0.8f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend(AttrBlend::shadow_blend,0.7f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(4.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrLightLevel(2.0f, 6.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrCockpit(AttrCockpit::region_2))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_HARD))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(0.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_LIGHT_LEVEL_RESET))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrHard(ESurface(ESurface::eId::concrete), true))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny(10.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend(AttrBlend::shadow_blend,0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrLightLevel(3.0f, 4.0f, "test2"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrCockpit(AttrCockpit::region_3))))).Times(1);

    // enable
    attrWriter.write(&writer, &main1);
    // disable
    attrWriter.write(&writer, &main2);
    // enable
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(18, attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case3) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.setHard(AttrHard(ESurface(ESurface::eId::dirt), false));
    main1.pAttr.setShiny(AttrShiny(0.8f));
    main1.pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.7f));
    main1.pAttr.setPolyOffset(AttrPolyOffset(4.0f));
    main1.pAttr.setLightLevel(AttrLightLevel(2.0f, 6.0f, "test"));
    main1.pAttr.setCockpit(AttrCockpit(AttrCockpit::region_1));

    main2.pAttr.setHard(AttrHard(ESurface(ESurface::eId::dirt), false));
    main2.pAttr.setShiny(AttrShiny(0.8f));
    main2.pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.7f));
    main2.pAttr.setPolyOffset(AttrPolyOffset(4.0f));
    main2.pAttr.setLightLevel(AttrLightLevel(2.0f, 6.0f, "test"));
    main2.pAttr.setCockpit(AttrCockpit(AttrCockpit::region_1));

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny(0.8f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend(AttrBlend::no_blend, 0.7f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(4.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrLightLevel(2.0f, 6.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrCockpit(AttrCockpit::region_1))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_HARD))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(0.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_LIGHT_LEVEL_RESET))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);

    // enable
    attrWriter.write(&writer, &main1);
    // equals
    attrWriter.write(&writer, &main2);
    // disable
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(12, attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case4) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.pAttr.setHard(AttrHard(ESurface(ESurface::eId::dirt), false));
    main1.pAttr.setShiny(AttrShiny(0.8f));
    main1.pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.7f));
    main1.pAttr.setPolyOffset(AttrPolyOffset(4.0f));
    main1.pAttr.setLightLevel(AttrLightLevel(2.0f, 6.0f, "test"));
    main1.pAttr.setCockpit(AttrCockpit(AttrCockpit::region_1));

    main2.pAttr.setHard(AttrHard(ESurface(ESurface::eId::concrete), true));
    main2.pAttr.setShiny(AttrShiny(10.0f));
    main2.pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.3f));
    main2.pAttr.setPolyOffset(AttrPolyOffset(5.0f));
    main2.pAttr.setLightLevel(AttrLightLevel(3.0f, 4.0f, "test2"));
    main2.pAttr.setCockpit(AttrCockpit(AttrCockpit::cockpit));

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny(0.8f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend(AttrBlend::no_blend, 0.7f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(4.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrLightLevel(2.0f, 6.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrCockpit(AttrCockpit::region_1))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrHard(ESurface(ESurface::eId::concrete), true))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny(10.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend(AttrBlend::no_blend, 0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrLightLevel(3.0f, 4.0f, "test2"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrCockpit(AttrCockpit::cockpit))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_HARD))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(0.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_LIGHT_LEVEL_RESET))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);

    // enable
    attrWriter.write(&writer, &main1);
    // NOT equals
    attrWriter.write(&writer, &main2);
    // disable
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(18, attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case5) {
    MockWriter writer;
    ObjWriteAttr attrWriter(&gObjWriteManip);
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main2.pAttr.setHard(AttrHard(ESurface(ESurface::eId::dirt), false));
    main2.pAttr.setShiny(AttrShiny(0.1f));
    main2.pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.3f));
    main2.pAttr.setPolyOffset(AttrPolyOffset(5.0f));
    main2.pAttr.setLightLevel(AttrLightLevel(3.0f, 4.0f, "test"));
    main2.pAttr.setCockpit(AttrCockpit(AttrCockpit::cockpit));

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrHard(ESurface(ESurface::eId::dirt), false))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny(0.1f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend(AttrBlend::no_blend, 0.3f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(5.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrLightLevel(3.0f, 4.0f, "test"))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrCockpit(AttrCockpit::cockpit))))).Times(1);

    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_HARD))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrShiny())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrBlend())))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(toObjString(AttrPolyOffset(0.0f))))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_LIGHT_LEVEL_RESET))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);

    attrWriter.write(&writer, &main1);
    // enable
    attrWriter.write(&writer, &main2);
    // disable
    attrWriter.write(&writer, &main3);
    ASSERT_EQ(12, attrWriter.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
