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
#include "xpln/obj/ObjMain.h"

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesIO, textures) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-textures.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.pAttr.mTexture = "test";
    mainOut.pAttr.mTextureLit = "test_lit";
    mainOut.pAttr.mTextureNormal = "test_normal";

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(3, expContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(3, impContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_TRUE(mainOut.pAttr.mTexture);
    ASSERT_TRUE(mainOut.pAttr.mTextureLit);
    ASSERT_TRUE(mainOut.pAttr.mTextureNormal);

    ASSERT_STREQ(mainOut.pAttr.mTexture->c_str(), "test");
    ASSERT_STREQ(mainOut.pAttr.mTextureLit->c_str(), "test_lit");
    ASSERT_STREQ(mainOut.pAttr.mTextureNormal->c_str(), "test_normal");
}

TEST(TestGlobAttributesIO, attributes) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-attributes.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.pAttr.mTint = AttrTint(0.3f, 0.7f);
    mainOut.pAttr.mBlendClass = true;
    mainOut.pAttr.mNormalMetalness = true;
    mainOut.pAttr.mTilted = true;
    mainOut.pAttr.mSpecular = AttrSpecular(0.9f);
    mainOut.pAttr.mDropShadow = true;
    mainOut.pAttr.mCockpitLit = true;
    mainOut.pAttr.mDebug = true;
    mainOut.pAttr.mLayerGroup = AttrLayerGroup(ELayer(ELayer::taxiways), 5);
    mainOut.pAttr.mAttrSlopeLimit = AttrSlopeLimit(0.3f, 0.5f, 0.7f, 0.9f);
    mainOut.pAttr.mSlungLoadWeight = AttrSlungLoadWeight(500);
    mainOut.pAttr.mAttrCockpitRegion1 = AttrCockpitRegion(100, 200, 300, 400);
    mainOut.pAttr.mAttrCockpitRegion2 = AttrCockpitRegion(500, 600, 700, 800);

    mainOut.pDraped.pAttr.setLod(AttrDrapedLod(1000));
    mainOut.pDraped.pAttr.setLayerGroup(AttrDrapedLayerGroup(ELayer(ELayer::airports), -3));

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(15, expContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(15, impContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(*mainIn.pAttr.mTint, AttrTint(0.3f, 0.7f));
    ASSERT_EQ(mainIn.pAttr.mBlendClass, true);
    ASSERT_EQ(mainIn.pAttr.mNormalMetalness, true);
    ASSERT_EQ(mainIn.pAttr.mTilted, true);
    ASSERT_EQ(*mainIn.pAttr.mSpecular, AttrSpecular(0.9f));
    ASSERT_EQ(mainIn.pAttr.mDropShadow, true);
    ASSERT_EQ(mainIn.pAttr.mCockpitLit, true);
    ASSERT_EQ(mainIn.pAttr.mDebug, true);
    ASSERT_EQ(*mainIn.pAttr.mLayerGroup, AttrLayerGroup(ELayer(ELayer::taxiways), 5));
    ASSERT_EQ(*mainIn.pAttr.mAttrSlopeLimit, AttrSlopeLimit(0.3f, 0.5f, 0.7f, 0.9f));
    ASSERT_EQ(*mainIn.pAttr.mSlungLoadWeight, AttrSlungLoadWeight(500));
    ASSERT_EQ(*mainIn.pAttr.mAttrCockpitRegion1, AttrCockpitRegion(100, 200, 300, 400));
    ASSERT_EQ(*mainIn.pAttr.mAttrCockpitRegion2, AttrCockpitRegion(500, 600, 700, 800));
    ASSERT_EQ(*mainIn.pAttr.mAttrCockpitRegion3, AttrCockpitRegion());
    ASSERT_EQ(*mainIn.pAttr.mAttrCockpitRegion4, AttrCockpitRegion());

    ASSERT_EQ(mainIn.pDraped.pAttr.lod(), AttrDrapedLod(1000));
    ASSERT_EQ(mainIn.pDraped.pAttr.layerGroup(), AttrDrapedLayerGroup(ELayer(ELayer::airports), -3));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesIO, statable_state1) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-statable_state1.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.pAttr.mAttrWetDry = AttrWetDry(AttrWetDry::wet);
    mainOut.pAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.8f);

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(2, expContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(2, impContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(*mainIn.pAttr.mAttrWetDry, AttrWetDry(AttrWetDry::wet));
    ASSERT_EQ(*mainIn.pAttr.mBlend, AttrBlend(AttrBlend::no_blend, 0.8f));
}

TEST(TestGlobAttributesIO, statable_state2) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-statable_state2.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.pAttr.mAttrWetDry = AttrWetDry(AttrWetDry::dry);
    mainOut.pAttr.mBlend = AttrBlend(AttrBlend::shadow_blend, 0.8f);

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(2, expContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(2, impContext.statistic().pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(*mainIn.pAttr.mAttrWetDry, AttrWetDry(AttrWetDry::dry));
    ASSERT_EQ(*mainIn.pAttr.mBlend, AttrBlend(AttrBlend::shadow_blend, 0.8f));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
