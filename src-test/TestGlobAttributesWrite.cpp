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
#include "xpln/obj/ObjMain.h"
#include "common/AttributeNames.h"
#include "TestWriter.h"
#include <io/writer/ObjWriteAttr.h>

using namespace xobj;
using ::testing::StrEq;
using ::testing::InSequence;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesWrite, strings) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;
    main.mAttr.mTexture = "test";
    main.mAttr.mTextureLit = "test_lit";
    main.mAttr.mTextureNormal = "test_normal";
    main.mAttr.mParticleSystemPath = "test_particle_system";

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(std::string(ATTR_GLOBAL_TEXTURE).append(" ").append(*main.mAttr.mTexture)))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(std::string(ATTR_GLOBAL_TEXTURE_LIT).append(" ").append(*main.mAttr.mTextureLit)))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(std::string(ATTR_GLOBAL_TEXTURE_NORMAL).append(" ").append(*main.mAttr.mTextureNormal)))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(std::string(ATTR_GLOBAL_PARTICLE_SYSTEM).append(" ").append(*main.mAttr.mParticleSystemPath)))).Times(1);

    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(4, 0, 0), attrWriter.count());
    ASSERT_STREQ("test", main.mAttr.mTexture->c_str());
    ASSERT_STREQ("test_lit", main.mAttr.mTextureLit->c_str());
    ASSERT_STREQ("test_normal", main.mAttr.mTextureNormal->c_str());
    ASSERT_STREQ("test_particle_system", main.mAttr.mParticleSystemPath->c_str());
}

TEST(TestGlobAttributesWrite, boolean) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    ASSERT_FALSE(main.mAttr.mBlendClass);
    ASSERT_FALSE(main.mAttr.mNormalMetalness);
    ASSERT_FALSE(main.mAttr.mTilted);
    ASSERT_FALSE(main.mAttr.mDropShadow);
    ASSERT_FALSE(main.mAttr.mCockpitLit);
    ASSERT_FALSE(main.mAttr.mDebug);

    main.mAttr.mBlendClass = true;
    main.mAttr.mNormalMetalness = true;
    main.mAttr.mTilted = true;
    main.mAttr.mDropShadow = true;
    main.mAttr.mCockpitLit = true;
    main.mAttr.mDebug = true;

    InSequence dummy;
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_GLOBAL_BLEND_GLASS))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_GLOBAL_NORMAL_METALNESS))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_GLOBAL_TILTED))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_GLOBAL_NO_SHADOW))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_GLOBAL_COCKPIT_LIT))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq(ATTR_GLOBAL_DEBUG))).Times(0);

    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(5, 0, 0), attrWriter.count());
    ASSERT_TRUE(main.mAttr.mBlendClass);
    ASSERT_TRUE(main.mAttr.mNormalMetalness);
    ASSERT_TRUE(main.mAttr.mTilted);
    ASSERT_TRUE(main.mAttr.mDropShadow);
    ASSERT_TRUE(main.mAttr.mCockpitLit);
    ASSERT_TRUE(main.mAttr.mDebug);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesWrite, AttrWetDry_wet) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrWetDry attr(AttrWetDry::eState::wet);
    main.mAttr.mWetDry = attr;

    EXPECT_CALL(writer, writeLine(StrEq("REQUIRE_WET"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
}

TEST(TestGlobAttributesWrite, AttrWetDry_Dry) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrWetDry attr(AttrWetDry::eState::dry);
    main.mAttr.mWetDry = attr;

    EXPECT_CALL(writer, writeLine(StrEq("REQUIRE_DRY"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrGlobBlend_no_blend) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrBlend attr(AttrBlend::eType::no_blend, 0.5);
    main.mAttr.mBlend = attr;

    EXPECT_CALL(writer, writeLine(StrEq("GLOBAL_no_blend 0.50000"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrGlobBlend_shadow_blend) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrBlend attr(AttrBlend::eType::shadow_blend, 0.5);
    main.mAttr.mBlend = attr;

    EXPECT_CALL(writer, writeLine(StrEq("GLOBAL_shadow_blend 0.50000"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrLayerGroup) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrLayerGroup attr(ELayer(ELayer::eId::cars), 5);
    main.mAttr.mLayerGroup = attr;

    EXPECT_CALL(writer, writeLine(StrEq("ATTR_layer_group cars 5"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrDrapedLayerGroup) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrDrapedLayerGroup attr(ELayer(ELayer::eId::cars), 5);
    main.mDraped.mAttr.mLayerGroup = attr;

    EXPECT_CALL(writer, writeLine(StrEq("ATTR_layer_group_draped cars 5"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrLodDrap) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrDrapedLod attr(10.0f);
    main.mDraped.mAttr.mLod = attr;

    EXPECT_CALL(writer, writeLine(StrEq("ATTR_LOD_draped 10.00000"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrSlungLoadWeight) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrSlungLoadWeight attr(10.0f);
    main.mAttr.mSlungLoadWeight = attr;

    EXPECT_CALL(writer, writeLine(StrEq("slung_load_weight 10.00000"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrSpecular) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrSpecular attr(0.5f);
    main.mAttr.mSpecular = attr;

    EXPECT_CALL(writer, writeLine(StrEq("GLOBAL_specular 0.50000"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrTint) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrTint attr(0.5f, 0.8f);
    main.mAttr.mTint = attr;

    EXPECT_CALL(writer, writeLine(StrEq("GLOBAL_tint 0.50000 0.80000"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrSlopeLimit) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrSlopeLimit attr(0.5f, 0.8f, 5.0f, 10.0f);
    main.mAttr.mSlopeLimit = attr;

    EXPECT_CALL(writer, writeLine(StrEq("SLOPE_LIMIT 0.50000 0.80000 5.00000 10.00000"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(1, 0, 0), attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrCockpitRegion) {
    MockWriter writer;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    ObjMain main;

    const AttrCockpitRegion attr0(1, 2, 3, 4);
    const AttrCockpitRegion attr1(5, 6, 7, 8);
    const AttrCockpitRegion attr2(9, 10, 11, 12);
    const AttrCockpitRegion attr3(13, 14, 15, 16);
    main.mAttr.mCockpitRegion1 = attr0;
    main.mAttr.mCockpitRegion2 = attr1;
    main.mAttr.mCockpitRegion3 = attr2;
    main.mAttr.mCockpitRegion4 = attr3;

    EXPECT_CALL(writer, writeLine(StrEq("COCKPIT_REGION 1 2 3 4"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("COCKPIT_REGION 5 6 7 8"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("COCKPIT_REGION 9 10 11 12"))).Times(1);
    EXPECT_CALL(writer, writeLine(StrEq("COCKPIT_REGION 13 14 15 16"))).Times(1);
    attrWriter.writeGlobAttr(&writer, &main);
    ASSERT_EQ(std::make_tuple(4, 0, 0), attrWriter.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
