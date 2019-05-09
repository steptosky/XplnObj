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
#include "io/writer/ObjWriteGlobAttr.h"
#include "common/AttributeNames.h"
#include "converters/ObjAttrString.h"
#include "TestWriter.h"

using namespace xobj;
using ::testing::StrEq;
using ::testing::InSequence;

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<typename T>
std::string strGlobAttrResult(const T & attr) {
    TestWriter w;
    printObjGlobAttr(attr, w);
    if (!w.mResult.empty()) {
        w.mResult.pop_back(); // remove '\n'
    }
    return w.mResult;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesWrite, textures) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;
    main.pAttr.mTexture = "test";
    main.pAttr.mTextureLit = "test_lit";
    main.pAttr.mTextureNormal = "test_normal";

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(std::string(ATTR_GLOBAL_TEXTURE).append(" ").append(*main.pAttr.mTexture)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(std::string(ATTR_GLOBAL_TEXTURE_LIT).append(" ").append(*main.pAttr.mTextureLit)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(std::string(ATTR_GLOBAL_TEXTURE_NORMAL).append(" ").append(*main.pAttr.mTextureNormal)))).Times(1);

    attrWriter.write(&writer, &main);
    ASSERT_EQ(3, attrWriter.count());
    ASSERT_STREQ("test", main.pAttr.mTexture->c_str());
    ASSERT_STREQ("test_lit", main.pAttr.mTextureLit->c_str());
    ASSERT_STREQ("test_normal", main.pAttr.mTextureNormal->c_str());
}

TEST(TestGlobAttributesWrite, boolean) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    ASSERT_FALSE(main.pAttr.mBlendClass);
    ASSERT_FALSE(main.pAttr.mNormalMetalness);
    ASSERT_FALSE(main.pAttr.mTilted);
    ASSERT_FALSE(main.pAttr.mDropShadow);
    ASSERT_FALSE(main.pAttr.mCockpitLit);
    ASSERT_FALSE(main.pAttr.mDebug);

    main.pAttr.mBlendClass = true;
    main.pAttr.mNormalMetalness = true;
    main.pAttr.mTilted = true;
    main.pAttr.mDropShadow = true;
    main.pAttr.mCockpitLit = true;
    main.pAttr.mDebug = true;

    InSequence dummy;
    EXPECT_CALL(writer, printLine(StrEq(ATTR_GLOBAL_BLEND_GLASS))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_GLOBAL_NORMAL_METALNESS))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_GLOBAL_TILTED))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_GLOBAL_NO_SHADOW))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_GLOBAL_COCKPIT_LIT))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_GLOBAL_DEBUG))).Times(0);

    attrWriter.write(&writer, &main);
    ASSERT_EQ(5, attrWriter.count());
    ASSERT_TRUE(main.pAttr.mBlendClass);
    ASSERT_TRUE(main.pAttr.mNormalMetalness);
    ASSERT_TRUE(main.pAttr.mTilted);
    ASSERT_TRUE(main.pAttr.mDropShadow);
    ASSERT_TRUE(main.pAttr.mCockpitLit);
    ASSERT_TRUE(main.pAttr.mDebug);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesWrite, AttrWetDry_wet) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrWetDry attr(AttrWetDry::eState::wet);
    main.pAttr.mWetDry = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
}

TEST(TestGlobAttributesWrite, AttrWetDry_Dry) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrWetDry attr(AttrWetDry::eState::dry);
    main.pAttr.mWetDry = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrGlobBlend_no_blend) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrBlend attr(AttrBlend::eType::no_blend, 0.5);
    main.pAttr.mBlend = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrGlobBlend_shadow_blend) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrBlend attr(AttrBlend::eType::shadow_blend, 0.5);
    main.pAttr.mBlend = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrLayerGroup) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrLayerGroup attr(ELayer(ELayer::eId::cars), 5);
    main.pAttr.mLayerGroup = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrDrapedLayerGroup) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrDrapedLayerGroup attr(ELayer(ELayer::eId::cars), 5);
    main.pDraped.pAttr.mLayerGroup = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrLodDrap) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrDrapedLod attr(10.0f);
    main.pDraped.pAttr.mLod = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrSlungLoadWeight) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrSlungLoadWeight attr(10.0f);
    main.pAttr.mSlungLoadWeight = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrSpecular) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrSpecular attr(0.5f);
    main.pAttr.mSpecular = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrTint) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrTint attr(0.5f, 0.8f);
    main.pAttr.mTint = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrSlopeLimit) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrSlopeLimit attr(0.5f, 0.8f, 5.0f, 10.0f);
    main.pAttr.mSlopeLimit = attr;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(1, attrWriter.count());
}

TEST(TestGlobAttributesWrite, AttrCockpitRegion) {
    MockWriter writer;
    ObjWriteGlobAttr attrWriter;
    ObjMain main;

    const AttrCockpitRegion attr0(1, 2, 3, 4);
    const AttrCockpitRegion attr1(5, 6, 7, 8);
    const AttrCockpitRegion attr2(9, 10, 11, 12);
    const AttrCockpitRegion attr3(13, 14, 15, 16);
    main.pAttr.mCockpitRegion1 = attr0;
    main.pAttr.mCockpitRegion2 = attr1;
    main.pAttr.mCockpitRegion3 = attr2;
    main.pAttr.mCockpitRegion4 = attr3;

    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr0)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr2)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(strGlobAttrResult(attr3)))).Times(1);
    attrWriter.write(&writer, &main);
    ASSERT_EQ(4, attrWriter.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
