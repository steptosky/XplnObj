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

TEST(TestGlobAttributesIO, defaults) {
    ObjMain mainOut;

    ASSERT_TRUE(mainOut.pAttr.texture().empty());
    ASSERT_TRUE(mainOut.pAttr.textureLit().empty());
    ASSERT_TRUE(mainOut.pAttr.textureNormal().empty());

    ASSERT_FALSE(mainOut.pAttr.isBlendGlass());
    ASSERT_FALSE(mainOut.pAttr.isNormalMetalness());
    ASSERT_FALSE(mainOut.pAttr.isTilted());
    ASSERT_FALSE(mainOut.pAttr.isNoShadow());
    ASSERT_FALSE(mainOut.pAttr.isCockpitLit());

    ASSERT_FALSE(mainOut.pAttr.wetDry());
    ASSERT_FALSE(mainOut.pAttr.blend());
    ASSERT_FALSE(mainOut.pAttr.layerGroup());
    ASSERT_FALSE(mainOut.pAttr.slungLoadWeight());
    ASSERT_FALSE(mainOut.pAttr.specular());
    ASSERT_FALSE(mainOut.pAttr.tint());
    ASSERT_FALSE(mainOut.pAttr.slopeLimit());
    ASSERT_FALSE(mainOut.pAttr.isDebug());
    ASSERT_FALSE(mainOut.pAttr.cockpitRegion(AttrCockpitRegion::r1));
    ASSERT_FALSE(mainOut.pAttr.cockpitRegion(AttrCockpitRegion::r2));
    ASSERT_FALSE(mainOut.pAttr.cockpitRegion(AttrCockpitRegion::r3));
    ASSERT_FALSE(mainOut.pAttr.cockpitRegion(AttrCockpitRegion::r4));

    ASSERT_FALSE(mainOut.pDrapedAttr.layerGroup());
    ASSERT_FALSE(mainOut.pDrapedAttr.lod());
}

TEST(TestGlobAttributesIO, textures) {
    ObjMain mainOut;
    mainOut.pAttr.setTexture("test");
    mainOut.pAttr.setTextureLit("test_lit");
    mainOut.pAttr.setTextureNormal("test_normal");

    //-------------------------------------------------------------------------

    IOStatistic stat;
    mainOut.exportToFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(3,stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    mainIn.importFromFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(3, stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_STREQ(mainOut.pAttr.texture().c_str(), "test");
    ASSERT_STREQ(mainOut.pAttr.textureLit().c_str(),"test_lit");
    ASSERT_STREQ(mainOut.pAttr.textureNormal().c_str(), "test_normal");
}

TEST(TestGlobAttributesIO, attributes) {
    ObjMain mainOut;
    mainOut.pAttr.setTint(AttrTint(0.3f, 0.7f));
    mainOut.pAttr.setBlendGlass(true);
    mainOut.pAttr.setNormalMetalness(true);
    mainOut.pAttr.setTilted(true);
    mainOut.pAttr.setSpecular(AttrSpecular(0.9f));
    mainOut.pAttr.setNoShadow(true);
    mainOut.pAttr.setCockpitLit(true);
    mainOut.pAttr.setDebug(true);
    mainOut.pAttr.setLayerGroup(AttrLayerGroup(ELayer(ELayer::taxiways), 5));
    mainOut.pAttr.setSlopeLimit(AttrSlopeLimit(0.3f, 0.5f, 0.7f, 0.9f));
    mainOut.pAttr.setSlungLoadWeight(AttrSlungLoadWeight(500));
    mainOut.pAttr.setCockpitRegion(AttrCockpitRegion(100, 200, 300, 400), AttrCockpitRegion::r1);
    mainOut.pAttr.setCockpitRegion(AttrCockpitRegion(500, 600, 700, 800), AttrCockpitRegion::r2);

    mainOut.pDrapedAttr.setLod(AttrLodDrap(1000));
    mainOut.pDrapedAttr.setLayerGroup(AttrDrapedLayerGroup(ELayer(ELayer::airports), -3));

    //-------------------------------------------------------------------------

    IOStatistic stat;
    mainOut.exportToFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(15, stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    mainIn.importFromFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(15, stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(mainIn.pAttr.tint(), AttrTint(0.3f, 0.7f));
    ASSERT_EQ(mainIn.pAttr.isBlendGlass(), true);
    ASSERT_EQ(mainIn.pAttr.isNormalMetalness(), true);
    ASSERT_EQ(mainIn.pAttr.isTilted(), true);
    ASSERT_EQ(mainIn.pAttr.specular(), AttrSpecular(0.9f));
    ASSERT_EQ(mainIn.pAttr.isNoShadow(), true);
    ASSERT_EQ(mainIn.pAttr.isCockpitLit(),true);
    ASSERT_EQ(mainIn.pAttr.isDebug(), true);
    ASSERT_EQ(mainIn.pAttr.layerGroup(), AttrLayerGroup(ELayer(ELayer::taxiways), 5));
    ASSERT_EQ(mainIn.pAttr.slopeLimit(), AttrSlopeLimit(0.3f, 0.5f, 0.7f, 0.9f));
    ASSERT_EQ(mainIn.pAttr.slungLoadWeight(), AttrSlungLoadWeight(500));
    ASSERT_EQ(mainIn.pAttr.cockpitRegion(AttrCockpitRegion::r1), AttrCockpitRegion(100, 200, 300, 400));
    ASSERT_EQ(mainIn.pAttr.cockpitRegion(AttrCockpitRegion::r2), AttrCockpitRegion(500, 600, 700, 800));
    ASSERT_EQ(mainIn.pAttr.cockpitRegion(AttrCockpitRegion::r3), AttrCockpitRegion());
    ASSERT_EQ(mainIn.pAttr.cockpitRegion(AttrCockpitRegion::r4), AttrCockpitRegion());

    ASSERT_EQ(mainIn.pDrapedAttr.lod(), AttrLodDrap(1000));
    ASSERT_EQ(mainIn.pDrapedAttr.layerGroup(), AttrDrapedLayerGroup(ELayer(ELayer::airports), -3));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestGlobAttributesIO, statable_state1) {
    ObjMain mainOut;
    mainOut.pAttr.setWetDry(AttrWetDry(AttrWetDry::wet));
    mainOut.pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.8f));

    //-------------------------------------------------------------------------

    IOStatistic stat;
    mainOut.exportToFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(2, stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    mainIn.importFromFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(2, stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(mainIn.pAttr.wetDry(), AttrWetDry(AttrWetDry::wet));
    ASSERT_EQ(mainIn.pAttr.blend(), AttrBlend(AttrBlend::no_blend, 0.8f));
}

TEST(TestGlobAttributesIO, statable_state2) {
    ObjMain mainOut;
    mainOut.pAttr.setWetDry(AttrWetDry(AttrWetDry::dry));
    mainOut.pAttr.setBlend(AttrBlend(AttrBlend::shadow_blend, 0.8f));

    //-------------------------------------------------------------------------

    IOStatistic stat;
    mainOut.exportToFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(2, stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ObjMain mainIn;
    mainIn.importFromFile(TOTEXT(TestGlobAttributesIO), stat);
    ASSERT_EQ(2, stat.pGlobAttrCount);

    //-------------------------------------------------------------------------

    ASSERT_EQ(mainIn.pAttr.wetDry(), AttrWetDry(AttrWetDry::dry));
    ASSERT_EQ(mainIn.pAttr.blend(), AttrBlend(AttrBlend::shadow_blend, 0.8f));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
