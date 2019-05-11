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
#include "xpln/obj/ObjMain.h"

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesIO, strings) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-textures.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.mAttr.mTexture = "test";
    mainOut.mAttr.mTextureLit = "test_lit";
    mainOut.mAttr.mTextureNormal = "test_normal";
    mainOut.mAttr.mParticleSystemPath = "test_particle_system";

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(4, expContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(4, impContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_TRUE(mainOut.mAttr.mTexture);
    ASSERT_TRUE(mainOut.mAttr.mTextureLit);
    ASSERT_TRUE(mainOut.mAttr.mTextureNormal);
    ASSERT_TRUE(mainOut.mAttr.mParticleSystemPath);

    ASSERT_STREQ(mainOut.mAttr.mTexture->c_str(), "test");
    ASSERT_STREQ(mainOut.mAttr.mTextureLit->c_str(), "test_lit");
    ASSERT_STREQ(mainOut.mAttr.mTextureNormal->c_str(), "test_normal");
    ASSERT_STREQ(mainOut.mAttr.mParticleSystemPath->c_str(), "test_particle_system");
}

TEST(TestGlobAttributesIO, attributes) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-attributes.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.mAttr.mTint = AttrTint(0.3f, 0.7f);
    mainOut.mAttr.mBlendClass = true;
    mainOut.mAttr.mNormalMetalness = true;
    mainOut.mAttr.mTilted = true;
    mainOut.mAttr.mSpecular = AttrSpecular(0.9f);
    mainOut.mAttr.mDropShadow = true;
    mainOut.mAttr.mCockpitLit = true;
    mainOut.mAttr.mDebug = true;
    mainOut.mAttr.mLayerGroup = AttrLayerGroup(ELayer(ELayer::taxiways), 5);
    mainOut.mAttr.mSlopeLimit = AttrSlopeLimit(0.3f, 0.5f, 0.7f, 0.9f);
    mainOut.mAttr.mSlungLoadWeight = AttrSlungLoadWeight(500);
    mainOut.mAttr.mCockpitRegion1 = AttrCockpitRegion(100, 200, 300, 400);
    mainOut.mAttr.mCockpitRegion2 = AttrCockpitRegion(500, 600, 700, 800);

    mainOut.mDraped.mAttr.mLod = AttrDrapedLod(1000);
    mainOut.mDraped.mAttr.mLayerGroup = AttrDrapedLayerGroup(ELayer(ELayer::airports), -3);

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(15, expContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(15, impContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(*mainIn.mAttr.mTint, AttrTint(0.3f, 0.7f));
    ASSERT_EQ(mainIn.mAttr.mBlendClass, true);
    ASSERT_EQ(mainIn.mAttr.mNormalMetalness, true);
    ASSERT_EQ(mainIn.mAttr.mTilted, true);
    ASSERT_EQ(*mainIn.mAttr.mSpecular, AttrSpecular(0.9f));
    ASSERT_EQ(mainIn.mAttr.mDropShadow, true);
    ASSERT_EQ(mainIn.mAttr.mCockpitLit, true);
    ASSERT_EQ(mainIn.mAttr.mDebug, true);
    ASSERT_EQ(*mainIn.mAttr.mLayerGroup, AttrLayerGroup(ELayer(ELayer::taxiways), 5));
    ASSERT_EQ(*mainIn.mAttr.mSlopeLimit, AttrSlopeLimit(0.3f, 0.5f, 0.7f, 0.9f));
    ASSERT_EQ(*mainIn.mAttr.mSlungLoadWeight, AttrSlungLoadWeight(500));
    ASSERT_EQ(*mainIn.mAttr.mCockpitRegion1, AttrCockpitRegion(100, 200, 300, 400));
    ASSERT_EQ(*mainIn.mAttr.mCockpitRegion2, AttrCockpitRegion(500, 600, 700, 800));
    ASSERT_FALSE(mainIn.mAttr.mCockpitRegion3);
    ASSERT_FALSE(mainIn.mAttr.mCockpitRegion4);

    ASSERT_EQ(*mainIn.mDraped.mAttr.mLod, AttrDrapedLod(1000));
    ASSERT_EQ(*mainIn.mDraped.mAttr.mLayerGroup, AttrDrapedLayerGroup(ELayer(ELayer::airports), -3));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesIO, statable_state1) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-statable_state1.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.mAttr.mWetDry = AttrWetDry(AttrWetDry::wet);
    mainOut.mAttr.mBlend = AttrBlend(AttrBlend::no_blend, 0.8f);

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(2, expContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(2, impContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(*mainIn.mAttr.mWetDry, AttrWetDry(AttrWetDry::wet));
    ASSERT_EQ(*mainIn.mAttr.mBlend, AttrBlend(AttrBlend::no_blend, 0.8f));
}

TEST(TestGlobAttributesIO, statable_state2) {
    const auto fileName = XOBJ_PATH("TestGlobAttributesIO-statable_state2.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.mAttr.mWetDry = AttrWetDry(AttrWetDry::dry);
    mainOut.mAttr.mBlend = AttrBlend(AttrBlend::shadow_blend, 0.8f);

    //-------------------------------------------------------------------------

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
    ASSERT_EQ(2, expContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));
    ASSERT_EQ(2, impContext.statistic().mGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(*mainIn.mAttr.mWetDry, AttrWetDry(AttrWetDry::dry));
    ASSERT_EQ(*mainIn.mAttr.mBlend, AttrBlend(AttrBlend::shadow_blend, 0.8f));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
