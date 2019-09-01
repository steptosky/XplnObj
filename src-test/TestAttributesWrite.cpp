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
#include <xpln/obj/manipulators/AttrManipNone.h>

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

// template<typename T>
// std::string strAttrResult(const T & attr) {
//     TestWriter w;
// 	attr.printObj(w);
//     if (!w.mResult.empty()) {
//         w.mResult.pop_back(); // remove '\n'
//     }
//     return w.mResult;
// }

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, default) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;

    EXPECT_CALL(writer, writeLine(_)).Times(0);
    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesWrite, boolean_case1) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.mAttr.mIsDraw = true; // default
    main1.mAttr.mIsDraped = true;
    main1.mAttr.mIsCastShadow = true; // default
    main1.mAttr.mIsSolidForCamera = true;

    // disable
    main2.mAttr.mIsDraw = false;
    main2.mAttr.mIsDraped = false;
    main2.mAttr.mIsCastShadow = false;
    main2.mAttr.mIsSolidForCamera = false;

    main3.mAttr.mIsDraw = false;
    main3.mAttr.mIsDraped = false;
    main3.mAttr.mIsCastShadow = false;
    main3.mAttr.mIsSolidForCamera = false;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case2) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.mAttr.mIsDraw = true; // default
    main1.mAttr.mIsDraped = true;
    main1.mAttr.mIsCastShadow = true; // default
    main1.mAttr.mIsSolidForCamera = true;

    main2.mAttr.mIsDraw = true; // default
    main2.mAttr.mIsDraped = true;
    main2.mAttr.mIsCastShadow = true; // default
    main2.mAttr.mIsSolidForCamera = true;

    // disable
    main3.mAttr.mIsDraw = false;
    main3.mAttr.mIsDraped = false;
    main3.mAttr.mIsCastShadow = false;
    main3.mAttr.mIsSolidForCamera = false;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case3) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.mAttr.mIsDraw = true; // default
    main1.mAttr.mIsDraped = true;
    main1.mAttr.mIsCastShadow = true; // default
    main1.mAttr.mIsSolidForCamera = true;

    main2.mAttr.mIsDraw = true; // default
    main2.mAttr.mIsDraped = true;
    main2.mAttr.mIsCastShadow = true; // default
    main2.mAttr.mIsSolidForCamera = true;

    main3.mAttr.mIsDraw = true; // default
    main3.mAttr.mIsDraped = true;
    main3.mAttr.mIsCastShadow = true; // default
    main3.mAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 2, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case4) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.mAttr.mIsDraw = false;
    main1.mAttr.mIsDraped = false;
    main1.mAttr.mIsCastShadow = false;
    main1.mAttr.mIsSolidForCamera = false;

    // enable
    main2.mAttr.mIsDraw = true; // default
    main2.mAttr.mIsDraped = true;
    main2.mAttr.mIsCastShadow = true; // default
    main2.mAttr.mIsSolidForCamera = true;

    main3.mAttr.mIsDraw = true; // default
    main3.mAttr.mIsDraped = true;
    main3.mAttr.mIsCastShadow = true; // default
    main3.mAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case5) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.mAttr.mIsDraw = false;
    main1.mAttr.mIsDraped = false;
    main1.mAttr.mIsCastShadow = false;
    main1.mAttr.mIsSolidForCamera = false;

    main2.mAttr.mIsDraw = false;
    main2.mAttr.mIsDraped = false;
    main2.mAttr.mIsCastShadow = false;
    main2.mAttr.mIsSolidForCamera = false;

    // enable
    main3.mAttr.mIsDraw = true; // default
    main3.mAttr.mIsDraped = true;
    main3.mAttr.mIsCastShadow = true; // default
    main3.mAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 6, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case6) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    // enable
    main1.mAttr.mIsDraw = true; // default
    main1.mAttr.mIsDraped = true;
    main1.mAttr.mIsCastShadow = true; // default
    main1.mAttr.mIsSolidForCamera = true;

    // disable
    main2.mAttr.mIsDraw = false;
    main2.mAttr.mIsDraped = false;
    main2.mAttr.mIsCastShadow = false;
    main2.mAttr.mIsSolidForCamera = false;

    // enable
    main3.mAttr.mIsDraw = true; // default
    main3.mAttr.mIsDraped = true;
    main3.mAttr.mIsCastShadow = true; // default
    main3.mAttr.mIsSolidForCamera = true;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SHADOW))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 10, 0), attrWriter.count());
}

TEST(TestAttributesWrite, boolean_case7) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.mAttr.mIsDraw = false;
    main1.mAttr.mIsDraped = false;
    main1.mAttr.mIsCastShadow = false;
    main1.mAttr.mIsSolidForCamera = false;

    // enable
    main2.mAttr.mIsDraw = true; // default
    main2.mAttr.mIsDraped = true;
    main2.mAttr.mIsCastShadow = true; // default
    main2.mAttr.mIsSolidForCamera = true;

    // disable
    main3.mAttr.mIsDraw = false;
    main3.mAttr.mIsDraped = false;
    main3.mAttr.mIsCastShadow = false;
    main3.mAttr.mIsSolidForCamera = false;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SHADOW))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_ENABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_SHADOW))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_DRAPED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SOLID_CAMERA))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_DRAW_DISABLE))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_NO_SHADOW))).Times(1);

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
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.mAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.mAttr.mShiny = AttrShiny(0.1f);
    main1.mAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.3f);
    main1.mAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main1.mAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, String("test"));
    main1.mAttr.mCockpit = AttrCockpit(AttrCockpit::region_3);

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_hard dirt"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.10000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_blend 0.30000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 5.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level 3.00000 4.00000 test"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_cockpit_region 2"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_manip_none"))).Times(1);

    // default
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_hard"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_blend 0.50000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level_reset"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_cockpit"))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // disable
    attrWriter.writeObjAttr(&writer, &main2);
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 12, 1), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case2) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.mAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.mAttr.mShiny = AttrShiny(0.8f);
    main1.mAttr.mBlend = AttrBlend(AttrBlend::shadow_blend, 0.7f);
    main1.mAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main1.mAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, String("test"));
    main1.mAttr.mCockpit = AttrCockpit(AttrCockpit::region_2);

    main3.mAttr.mHard = AttrHard(ESurface(ESurface::eId::concrete), true);
    main3.mAttr.mShiny = AttrShiny(10.0f);
    main3.mAttr.mBlend = AttrBlend(AttrBlend::shadow_blend, 0.3f);
    main3.mAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main3.mAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, String("test2"));
    main3.mAttr.mCockpit = AttrCockpit(AttrCockpit::region_3);

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_hard dirt"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.80000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shadow_blend 0.70000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 4.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level 2.00000 6.00000 test"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_cockpit_region 1"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_manip_none"))).Times(1);

    // default
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_hard"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_blend 0.50000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level_reset"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_cockpit"))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq("ATTR_hard_deck concrete"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 1.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shadow_blend 0.30000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 5.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level 3.00000 4.00000 test2"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_cockpit_region 2"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_manip_none"))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // disable
    attrWriter.writeObjAttr(&writer, &main2);
    // enable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 18, 2), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case3) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.mAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.mAttr.mShiny = AttrShiny(0.8f);
    main1.mAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.7f);
    main1.mAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main1.mAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, String("test"));
    main1.mAttr.mCockpit = AttrCockpit(AttrCockpit::region_1);

    main2.mAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main2.mAttr.mShiny = AttrShiny(0.8f);
    main2.mAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.7f);
    main2.mAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main2.mAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, String("test"));
    main2.mAttr.mCockpit = AttrCockpit(AttrCockpit::region_1);

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_hard dirt"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.80000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_blend 0.70000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 4.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level 2.00000 6.00000 test"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_cockpit_region 0"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_manip_none"))).Times(1);

    // default
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_hard"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_blend 0.50000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level_reset"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_cockpit"))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // equals
    attrWriter.writeObjAttr(&writer, &main2);
    // disable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 12, 1), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case4) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main1.mAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main1.mAttr.mShiny = AttrShiny(0.8f);
    main1.mAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.7f);
    main1.mAttr.mPolyOffset = AttrPolyOffset(4.0f);
    main1.mAttr.mLightLevel = AttrLightLevel(2.0f, 6.0f, String("test"));
    main1.mAttr.mCockpit = AttrCockpit(AttrCockpit::region_1);

    main2.mAttr.mHard = AttrHard(ESurface(ESurface::eId::concrete), true);
    main2.mAttr.mShiny = AttrShiny(10.0f);
    main2.mAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.3f);
    main2.mAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main2.mAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, String("test2"));
    main2.mAttr.mCockpit = AttrCockpit(AttrCockpit::cockpit);

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_hard dirt"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.80000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_blend 0.70000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 4.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level 2.00000 6.00000 test"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_cockpit_region 0"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_manip_none"))).Times(1);

    EXPECT_CALL(writer, writeLine(StrEq("ATTR_hard_deck concrete"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 1.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_blend 0.30000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 5.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level 3.00000 4.00000 test2"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_cockpit"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_manip_none"))).Times(1);

    // default
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_hard"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_blend 0.50000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level_reset"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_cockpit"))).Times(1);

    // enable
    attrWriter.writeObjAttr(&writer, &main1);
    // NOT equals
    attrWriter.writeObjAttr(&writer, &main2);
    // disable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 18, 2), attrWriter.count());
}

TEST(TestAttributesWrite, parameterized_case5) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMesh main1;
    ObjMesh main2;
    ObjMesh main3;

    main2.mAttr.mHard = AttrHard(ESurface(ESurface::eId::dirt), false);
    main2.mAttr.mShiny = AttrShiny(0.1f);
    main2.mAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.3f);
    main2.mAttr.mPolyOffset = AttrPolyOffset(5.0f);
    main2.mAttr.mLightLevel = AttrLightLevel(3.0f, 4.0f, String("test"));
    main2.mAttr.mCockpit = AttrCockpit(AttrCockpit::cockpit);

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_hard dirt"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.10000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_blend 0.30000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 5.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level 3.00000 4.00000 test"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_cockpit"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_manip_none"))).Times(1);

    // default
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_hard"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_shiny_rat 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_blend 0.50000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_poly_os 0.00000"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_light_level_reset"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("ATTR_no_cockpit"))).Times(1);

    attrWriter.writeObjAttr(&writer, &main1);
    // enable
    attrWriter.writeObjAttr(&writer, &main2);
    // disable
    attrWriter.writeObjAttr(&writer, &main3);
    ASSERT_EQ(std::make_tuple(0, 12, 1), attrWriter.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
