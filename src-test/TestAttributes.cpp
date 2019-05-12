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
#include <sts/string/StringUtils.h>

#include "xpln/obj/attributes/AttrWetDry.h"
#include "xpln/obj/attributes/AttrTint.h"
#include "xpln/obj/attributes/AttrSpecular.h"
#include "xpln/obj/attributes/AttrSlungLoadWeight.h"
#include "xpln/obj/attributes/AttrShiny.h"
#include "xpln/obj/attributes/AttrPolyOffset.h"
#include "xpln/obj/attributes/AttrDrapedLod.h"
#include "xpln/obj/attributes/AttrLightLevel.h"
#include "xpln/obj/attributes/AttrDrapedLayerGroup.h"
#include "xpln/obj/attributes/AttrLayerGroup.h"
#include "xpln/obj/attributes/AttrHard.h"
#include "xpln/obj/attributes/AttrBlend.h"
#include "xpln/obj/attributes/AttrSlopeLimit.h"
#include "xpln/obj/attributes/AttrCockpitRegion.h"
#include "xpln/obj/attributes/AttrCockpit.h"

#include "converters/Defines.h"
#include "TestWriter.h"

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
 * This tests are for checking attributes' methods and states.
 */

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

// todo 
// template<typename T>
// std::string strAttrResult(const T & attr) {
//     TestWriter w;
//     attr.printObj(w);
//     if (!w.mResult.empty()) {
//         w.mResult.pop_back(); // remove '\n'
//     }
//     return w.mResult;
// }

// todo
// template<typename T>
// std::string strGlobAttrResult(const T & attr) {
//     TestWriter w;
//     printObjGlobAttr(attr, w);
//     if (!w.mResult.empty()) {
//         w.mResult.pop_back(); // remove '\n'
//     }
//     return w.mResult;
// }

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributes, AttrBlendShadow) {
    AttrBlend attr(AttrBlend::eType::shadow_blend, 0.5);
    // todo ASSERT_STREQ(std::string("ATTR_shadow_blend ").append(sts::toMbString(0.5f, PRECISION)).c_str(), strAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(0.5f, attr.mRatio);

    ASSERT_TRUE(AttrBlend() == AttrBlend());
    ASSERT_TRUE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) == AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_TRUE(AttrBlend() != AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_TRUE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) != AttrBlend(AttrBlend::eType::no_blend, 0.5f));
    ASSERT_TRUE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) != AttrBlend(AttrBlend::eType::shadow_blend, 0.6f));

    ASSERT_FALSE(AttrBlend() != AttrBlend());
    ASSERT_FALSE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) != AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_FALSE(AttrBlend() == AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_FALSE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) == AttrBlend(AttrBlend::eType::no_blend, 0.5f));
    ASSERT_FALSE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) == AttrBlend(AttrBlend::eType::shadow_blend, 0.6f));
}

TEST(TestAttributes, AttrBlend) {
    AttrBlend attr(AttrBlend::eType::no_blend, 0.5f);
    // todo  ASSERT_STREQ(std::string("ATTR_no_blend ").append(sts::toMbString(0.5f, PRECISION)).c_str(), strAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(0.5f, attr.mRatio);
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrGlobBlendShadow) {
    AttrBlend attr(AttrBlend::eType::shadow_blend, 0.5);
    // todo ASSERT_STREQ(std::string("GLOBAL_shadow_blend ").append(sts::toMbString(0.5f, PRECISION)).c_str(), strGlobAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(0.5f, attr.mRatio);

    ASSERT_TRUE(AttrBlend() == AttrBlend());
    ASSERT_TRUE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) == AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_TRUE(AttrBlend() != AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_TRUE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) != AttrBlend(AttrBlend::eType::no_blend, 0.5f));
    ASSERT_TRUE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) != AttrBlend(AttrBlend::eType::shadow_blend, 0.6f));

    ASSERT_FALSE(AttrBlend() != AttrBlend());
    ASSERT_FALSE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) != AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_FALSE(AttrBlend() == AttrBlend(AttrBlend::eType::shadow_blend, 0.5f));
    ASSERT_FALSE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) == AttrBlend(AttrBlend::eType::no_blend, 0.5f));
    ASSERT_FALSE(AttrBlend(AttrBlend::eType::shadow_blend, 0.5f) == AttrBlend(AttrBlend::eType::shadow_blend, 0.6f));
}

TEST(TestAttributes, AttrGlobBlend) {
    AttrBlend attr(AttrBlend::eType::no_blend, 0.5f);
    // todo ASSERT_STREQ(std::string("GLOBAL_no_blend ").append(sts::toMbString(0.5f, PRECISION)).c_str(), strGlobAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(0.5f, attr.mRatio);
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrHard) {
    AttrHard attr(ESurface(ESurface::eId::grass), false);
    // todo ASSERT_STREQ(std::string("ATTR_hard ").append(ESurface(ESurface::eId::grass).toString()).c_str(), strAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(ESurface::eId::grass, attr.mSurface.id());

    ASSERT_TRUE(AttrHard() == AttrHard());
    ASSERT_TRUE(AttrHard(ESurface(ESurface::eId::grass), false) == AttrHard(ESurface(ESurface::eId::grass), false));
    ASSERT_TRUE(AttrHard() != AttrHard(ESurface(ESurface::eId::grass), false));
    ASSERT_TRUE(AttrHard(ESurface(ESurface::eId::grass), false) != AttrHard(ESurface(ESurface::eId::asphalt), false));
    ASSERT_TRUE(AttrHard(ESurface(ESurface::eId::grass), false) != AttrHard(ESurface(ESurface::eId::grass), true));

    ASSERT_FALSE(AttrHard() != AttrHard());
    ASSERT_FALSE(AttrHard(ESurface(ESurface::eId::grass), false) != AttrHard(ESurface(ESurface::eId::grass), false));
    ASSERT_FALSE(AttrHard() == AttrHard(ESurface(ESurface::eId::grass), false));
    ASSERT_FALSE(AttrHard(ESurface(ESurface::eId::grass), false) == AttrHard(ESurface(ESurface::eId::asphalt), false));
    ASSERT_FALSE(AttrHard(ESurface(ESurface::eId::grass), false) == AttrHard(ESurface(ESurface::eId::grass), true));
}

TEST(TestAttributes, AttrHard_deck) {
    AttrHard attr(ESurface(ESurface::eId::blastpad), true);
    // todo  ASSERT_STREQ(std::string("ATTR_hard_deck ").append(ESurface(ESurface::eId::blastpad).toString()).c_str(), strAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(ESurface::eId::blastpad, attr.mSurface.id());
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrDrapedLayerGroup) {
    AttrDrapedLayerGroup attr;

    const ELayer layer(ELayer::eId::cars);
    attr.mOffset = 5;
    attr.mLayer = layer;

    // todo ASSERT_STREQ(std::string("ATTR_layer_group_draped ").append(layer.toString()).append(" 5").c_str(), strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(5, attr.mOffset);
    ASSERT_STREQ(layer.toString(), attr.mLayer.toString());

    ASSERT_TRUE(AttrDrapedLayerGroup() == AttrDrapedLayerGroup());
    ASSERT_TRUE(AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 5) == AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 5));
    ASSERT_TRUE(AttrDrapedLayerGroup() != AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), false));
    ASSERT_TRUE(AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 4) != AttrDrapedLayerGroup(ELayer(ELayer::eId::cars), 4));
    ASSERT_TRUE(AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 4) != AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 3));

    ASSERT_FALSE(AttrDrapedLayerGroup() != AttrDrapedLayerGroup());
    ASSERT_FALSE(AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 5) != AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 5));
    ASSERT_FALSE(AttrDrapedLayerGroup() == AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), false));
    ASSERT_FALSE(AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 4) == AttrDrapedLayerGroup(ELayer(ELayer::eId::cars), 4));
    ASSERT_FALSE(AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 4) == AttrDrapedLayerGroup(ELayer(ELayer::eId::markings), 3));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrLayerGroup) {
    AttrLayerGroup attr;

    ELayer layer(ELayer::eId::cars);
    attr.mOffset = 5;
    attr.mLayer = layer;

    // todo ASSERT_STREQ(std::string("ATTR_layer_group ").append(layer.toString()).append(" 5").c_str(), strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(5, attr.mOffset);
    ASSERT_STREQ(layer.toString(), attr.mLayer.toString());

    ASSERT_TRUE(AttrLayerGroup() == AttrLayerGroup());
    ASSERT_TRUE(AttrLayerGroup(ELayer(ELayer::eId::markings), 5) == AttrLayerGroup(ELayer(ELayer::eId::markings), 5));
    ASSERT_TRUE(AttrLayerGroup() != AttrLayerGroup(ELayer(ELayer::eId::markings), false));
    ASSERT_TRUE(AttrLayerGroup(ELayer(ELayer::eId::markings), 4) != AttrLayerGroup(ELayer(ELayer::eId::cars), 4));
    ASSERT_TRUE(AttrLayerGroup(ELayer(ELayer::eId::markings), 4) != AttrLayerGroup(ELayer(ELayer::eId::markings), 3));

    ASSERT_FALSE(AttrLayerGroup() != AttrLayerGroup());
    ASSERT_FALSE(AttrLayerGroup(ELayer(ELayer::eId::markings), 5) != AttrLayerGroup(ELayer(ELayer::eId::markings), 5));
    ASSERT_FALSE(AttrLayerGroup() == AttrLayerGroup(ELayer(ELayer::eId::markings), false));
    ASSERT_FALSE(AttrLayerGroup(ELayer(ELayer::eId::markings), 4) == AttrLayerGroup(ELayer(ELayer::eId::cars), 4));
    ASSERT_FALSE(AttrLayerGroup(ELayer(ELayer::eId::markings), 4) == AttrLayerGroup(ELayer(ELayer::eId::markings), 3));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrLightLevel) {
    AttrLightLevel attr;

    attr.mVal1 = 10.0f;
    attr.mVal2 = 20.0f;
    attr.mDataref = "dataref";

    // todo  ASSERT_STREQ(std::string("ATTR_light_level ")
    //             .append(sts::toMbString(10.0f, PRECISION)).append(" ")
    //             .append(sts::toMbString(20.0f, PRECISION)).append(" dataref")
    //             .c_str(),
    //             strAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(10.0f, attr.mVal1);
    ASSERT_EQ(20.0f, attr.mVal2);
    ASSERT_STREQ("dataref", attr.mDataref.c_str());

    ASSERT_TRUE(AttrLightLevel() == AttrLightLevel());
    ASSERT_TRUE(AttrLightLevel(10.0f, 20.0f, "dataref") == AttrLightLevel(10.0f, 20.0f, "dataref"));
    ASSERT_TRUE(AttrLightLevel() != AttrLightLevel(10.0f, 20.0f, "dataref"));
    ASSERT_TRUE(AttrLightLevel(10.0f, 20.0f, "dataref") != AttrLightLevel(20.0f, 20.0f, "dataref"));
    ASSERT_TRUE(AttrLightLevel(10.0f, 20.0f, "dataref") != AttrLightLevel(10.0f, 30.0f, "dataref"));
    ASSERT_TRUE(AttrLightLevel(10.0f, 20.0f, "dataref") != AttrLightLevel(10.0f, 20.0f, "dataref2"));

    ASSERT_FALSE(AttrLightLevel() != AttrLightLevel());
    ASSERT_FALSE(AttrLightLevel(10.0f, 20.0f, "dataref") != AttrLightLevel(10.0f, 20.0f, "dataref"));
    ASSERT_FALSE(AttrLightLevel() == AttrLightLevel(10.0f, 20.0f, "dataref"));
    ASSERT_FALSE(AttrLightLevel(10.0f, 20.0f, "dataref") == AttrLightLevel(20.0f, 20.0f, "dataref"));
    ASSERT_FALSE(AttrLightLevel(10.0f, 20.0f, "dataref") == AttrLightLevel(10.0f, 30.0f, "dataref"));
    ASSERT_FALSE(AttrLightLevel(10.0f, 20.0f, "dataref") == AttrLightLevel(10.0f, 20.0f, "dataref2"));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrLodDrap) {
    AttrDrapedLod attr;

    attr.mDistance = 10.0f;

    // todo ASSERT_STREQ(std::string("ATTR_LOD_draped ").append(sts::toMbString(10.0f, PRECISION)).c_str(), strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(10.0f, attr.mDistance);

    ASSERT_TRUE(AttrDrapedLod() == AttrDrapedLod());
    ASSERT_TRUE(AttrDrapedLod(0.3f) == AttrDrapedLod(0.3f));
    ASSERT_TRUE(AttrDrapedLod() != AttrDrapedLod(0.3f));
    ASSERT_TRUE(AttrDrapedLod(0.3f) != AttrDrapedLod(0.5f));

    ASSERT_FALSE(AttrDrapedLod() != AttrDrapedLod());
    ASSERT_FALSE(AttrDrapedLod(0.3f) != AttrDrapedLod(0.3f));
    ASSERT_FALSE(AttrDrapedLod() == AttrDrapedLod(0.3f));
    ASSERT_FALSE(AttrDrapedLod(0.3f) == AttrDrapedLod(0.5f));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrPolyOffset) {
    AttrPolyOffset attr;

    attr.mOffset = 10.0f;

    // todo ASSERT_STREQ(std::string("ATTR_poly_os ").append(sts::toMbString(10.0f, PRECISION)).c_str(), strAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(10.0f, attr.mOffset);

    ASSERT_TRUE(AttrPolyOffset() == AttrPolyOffset());
    ASSERT_TRUE(AttrPolyOffset(0.3f) == AttrPolyOffset(0.3f));
    ASSERT_TRUE(AttrPolyOffset() != AttrPolyOffset(0.3f));
    ASSERT_TRUE(AttrPolyOffset(0.3f) != AttrPolyOffset(0.5f));

    ASSERT_FALSE(AttrPolyOffset() != AttrPolyOffset());
    ASSERT_FALSE(AttrPolyOffset(0.3f) != AttrPolyOffset(0.3f));
    ASSERT_FALSE(AttrPolyOffset() == AttrPolyOffset(0.3f));
    ASSERT_FALSE(AttrPolyOffset(0.3f) == AttrPolyOffset(0.5f));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrShiny) {
    AttrShiny attr;

    attr.mRatio = 0.5f;

    // todo ASSERT_STREQ(std::string("ATTR_shiny_rat ").append(sts::toMbString(0.5f, PRECISION)).c_str(), strAttrResult(attr).c_str());
    // getters
    ASSERT_EQ(0.5f, attr.mRatio);

    ASSERT_TRUE(AttrShiny() == AttrShiny());
    ASSERT_TRUE(AttrShiny(0.3f) == AttrShiny(0.3f));
    ASSERT_TRUE(AttrShiny() != AttrShiny(0.3f));
    ASSERT_TRUE(AttrShiny(0.3f) != AttrShiny(0.5f));

    ASSERT_FALSE(AttrShiny() != AttrShiny());
    ASSERT_FALSE(AttrShiny(0.3f) != AttrShiny(0.3f));
    ASSERT_FALSE(AttrShiny() == AttrShiny(0.3f));
    ASSERT_FALSE(AttrShiny(0.3f) == AttrShiny(0.5f));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrSlungLoadWeight) {
    AttrSlungLoadWeight attr;

    attr.mWeight = 10.0f;

    // todo ASSERT_STREQ(std::string("slung_load_weight ").append(sts::toMbString(10.0f, PRECISION)).c_str(), strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(10.0f, attr.mWeight);

    ASSERT_TRUE(AttrSlungLoadWeight() == AttrSlungLoadWeight());
    ASSERT_TRUE(AttrSlungLoadWeight(0.3f) == AttrSlungLoadWeight(0.3f));
    ASSERT_TRUE(AttrSlungLoadWeight() != AttrSlungLoadWeight(0.3f));
    ASSERT_TRUE(AttrSlungLoadWeight(0.3f) != AttrSlungLoadWeight(0.5f));

    ASSERT_FALSE(AttrSlungLoadWeight() != AttrSlungLoadWeight());
    ASSERT_FALSE(AttrSlungLoadWeight(0.3f) != AttrSlungLoadWeight(0.3f));
    ASSERT_FALSE(AttrSlungLoadWeight() == AttrSlungLoadWeight(0.3f));
    ASSERT_FALSE(AttrSlungLoadWeight(0.3f) == AttrSlungLoadWeight(0.5f));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrSpecular) {
    AttrSpecular attr;

    attr.mRatio = 0.5f;

    // todo ASSERT_STREQ(std::string("GLOBAL_specular ").append(sts::toMbString(0.5f, PRECISION)).c_str(), strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(0.5f, attr.mRatio);

    ASSERT_TRUE(AttrSpecular() == AttrSpecular());
    ASSERT_TRUE(AttrSpecular(0.3f) == AttrSpecular(0.3f));
    ASSERT_TRUE(AttrSpecular() != AttrSpecular(0.3f));
    ASSERT_TRUE(AttrSpecular(0.3f) != AttrSpecular(0.5f));

    ASSERT_FALSE(AttrSpecular() != AttrSpecular());
    ASSERT_FALSE(AttrSpecular(0.3f) != AttrSpecular(0.3f));
    ASSERT_FALSE(AttrSpecular() == AttrSpecular(0.3f));
    ASSERT_FALSE(AttrSpecular(0.3f) == AttrSpecular(0.5f));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrTint) {
    AttrTint attr;

    attr.mAlbedo = 10.0f;
    attr.mEmissive = 20.0f;

    // todo ASSERT_STREQ(std::string("GLOBAL_tint ")
    //             .append(sts::toMbString(10.0f, PRECISION)).append(" ")
    //             .append(sts::toMbString(20.0f, PRECISION)).c_str(), strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(10.0f, attr.mAlbedo);
    ASSERT_EQ(20.0f, attr.mEmissive);

    ASSERT_TRUE(AttrTint() == AttrTint());
    ASSERT_TRUE(AttrTint(10.0f, 20.0f) == AttrTint(10.0f, 20.0f));
    ASSERT_TRUE(AttrTint() != AttrTint(10.0f, 20.0f));
    ASSERT_TRUE(AttrTint(10.0f, 20.0f) != AttrTint(20.0f, 20.0f));
    ASSERT_TRUE(AttrTint(10.0f, 20.0f) != AttrTint(10.0f, 30.0f));

    ASSERT_FALSE(AttrTint() != AttrTint());
    ASSERT_FALSE(AttrTint(10.0f, 20.0f) != AttrTint(10.0f, 20.0f));
    ASSERT_FALSE(AttrTint() == AttrTint(10.0f, 20.0f));
    ASSERT_FALSE(AttrTint(10.0f, 20.0f) == AttrTint(20.0f, 20.0f));
    ASSERT_FALSE(AttrTint(10.0f, 20.0f) == AttrTint(10.0f, 30.0f));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrWetDry) {
    AttrWetDry attr;

    attr.mState = AttrWetDry::eState::wet;
    // todo ASSERT_STREQ("REQUIRE_WET", strGlobAttrResult(attr).c_str());
    ASSERT_EQ(AttrWetDry::eState::wet, attr.mState);

    attr.mState = AttrWetDry::eState::dry;
    // todo ASSERT_STREQ("REQUIRE_DRY", strGlobAttrResult(attr).c_str());
    ASSERT_EQ(AttrWetDry::eState::dry, attr.mState);

    ASSERT_TRUE(AttrWetDry() == AttrWetDry());
    ASSERT_TRUE(AttrWetDry(AttrWetDry::eState::wet) == AttrWetDry(AttrWetDry::eState::wet));
    ASSERT_TRUE(AttrWetDry(AttrWetDry::eState::wet) != AttrWetDry(AttrWetDry::eState::dry));

    ASSERT_FALSE(AttrWetDry() != AttrWetDry());
    ASSERT_FALSE(AttrWetDry(AttrWetDry::eState::wet) != AttrWetDry(AttrWetDry::eState::wet));
    ASSERT_FALSE(AttrWetDry(AttrWetDry::eState::wet) == AttrWetDry(AttrWetDry::eState::dry));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrSlopeLimit) {
    AttrSlopeLimit attr;

    attr.mMinPitch = 10.0f;
    attr.mMaxPitch = 20.0f;
    attr.mMinRoll = 5.0f;
    attr.mMaxRoll = 15.0f;

    // todo  ASSERT_STREQ(std::string("SLOPE_LIMIT ")
    //             .append(sts::toMbString(10.0f, PRECISION)).append(" ")
    //             .append(sts::toMbString(20.0f, PRECISION)).append(" ")
    //             .append(sts::toMbString(5.0f, PRECISION)).append(" ")
    //             .append(sts::toMbString(15.0f, PRECISION)).c_str(), strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(10.0f, attr.mMinPitch);
    ASSERT_EQ(20.0f, attr.mMaxPitch);
    ASSERT_EQ(5.0f, attr.mMinRoll);
    ASSERT_EQ(15.0f, attr.mMaxRoll);

    ASSERT_TRUE(AttrSlopeLimit() == AttrSlopeLimit());
    ASSERT_TRUE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) == AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f));
    ASSERT_TRUE(AttrSlopeLimit() != AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f));
    ASSERT_TRUE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) != AttrSlopeLimit(3.0f, 20.0f, 5.0f, 15.0f));
    ASSERT_TRUE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) != AttrSlopeLimit(10.0f, 3.0f, 5.0f, 15.0f));
    ASSERT_TRUE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) != AttrSlopeLimit(10.0f, 20.0f, 3.0f, 15.0f));
    ASSERT_TRUE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) != AttrSlopeLimit(10.0f, 20.0f, 5.0f, 3.0f));

    ASSERT_FALSE(AttrSlopeLimit() != AttrSlopeLimit());
    ASSERT_FALSE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) != AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f));
    ASSERT_FALSE(AttrSlopeLimit() == AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f));
    ASSERT_FALSE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) == AttrSlopeLimit(3.0f, 20.0f, 5.0f, 15.0f));
    ASSERT_FALSE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) == AttrSlopeLimit(10.0f, 3.0f, 5.0f, 15.0f));
    ASSERT_FALSE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) == AttrSlopeLimit(10.0f, 20.0f, 3.0f, 15.0f));
    ASSERT_FALSE(AttrSlopeLimit(10.0f, 20.0f, 5.0f, 15.0f) == AttrSlopeLimit(10.0f, 20.0f, 5.0f, 3.0f));
}

//-------------------------------------------------------------------------

TEST(TestAttributes, AttrCockpitRegion) {
    AttrCockpitRegion attr;

    attr.mLeft = 10;
    attr.mBottom = 20;
    attr.mRight = 5;
    attr.mTop = 15;

    // todo  ASSERT_STREQ("COCKPIT_REGION 10 20 5 15", strGlobAttrResult(attr).c_str());

    // getters
    ASSERT_EQ(10, attr.mLeft);
    ASSERT_EQ(20, attr.mBottom);
    ASSERT_EQ(5, attr.mRight);
    ASSERT_EQ(15, attr.mTop);

    ASSERT_TRUE(AttrCockpitRegion() == AttrCockpitRegion());
    ASSERT_TRUE(AttrCockpitRegion(10, 20, 5, 15) == AttrCockpitRegion(10, 20, 5, 15));
    ASSERT_TRUE(AttrCockpitRegion() != AttrCockpitRegion(10, 20, 5, 15));
    ASSERT_TRUE(AttrCockpitRegion(10, 20, 5, 15) != AttrCockpitRegion(3, 20, 5, 15));
    ASSERT_TRUE(AttrCockpitRegion(10, 20, 5, 15) != AttrCockpitRegion(10, 3, 5, 15));
    ASSERT_TRUE(AttrCockpitRegion(10, 20, 5, 15) != AttrCockpitRegion(10, 20, 3, 15));
    ASSERT_TRUE(AttrCockpitRegion(10, 20, 5, 15) != AttrCockpitRegion(10, 20, 5, 3));

    ASSERT_FALSE(AttrCockpitRegion() != AttrCockpitRegion());
    ASSERT_FALSE(AttrCockpitRegion(10, 20, 5, 15) != AttrCockpitRegion(10, 20, 5, 15));
    ASSERT_FALSE(AttrCockpitRegion() == AttrCockpitRegion(10, 20, 5, 15));
    ASSERT_FALSE(AttrCockpitRegion(10, 20, 5, 15) == AttrCockpitRegion(3, 20, 5, 15));
    ASSERT_FALSE(AttrCockpitRegion(10, 20, 5, 15) == AttrCockpitRegion(10, 3, 5, 15));
    ASSERT_FALSE(AttrCockpitRegion(10, 20, 5, 15) == AttrCockpitRegion(10, 20, 3, 15));
    ASSERT_FALSE(AttrCockpitRegion(10, 20, 5, 15) == AttrCockpitRegion(10, 20, 5, 3));
}

TEST(TestAttributes, AttrCockpit) {
    AttrCockpit attr;

    ASSERT_EQ(AttrCockpit::cockpit, attr.mType);

    attr.mType = AttrCockpit::cockpit;
    // todo ASSERT_STREQ("ATTR_cockpit", strAttrResult(attr).c_str());
    ASSERT_EQ(AttrCockpit::cockpit, attr.mType);

    attr.mType = AttrCockpit::region_2;
    // todo ASSERT_STREQ("ATTR_cockpit_region 1", strAttrResult(attr).c_str());

    ASSERT_EQ(AttrCockpit::region_2, attr.mType);

    ASSERT_TRUE(AttrCockpit() == AttrCockpit());
    ASSERT_TRUE(AttrCockpit(AttrCockpit::cockpit) == AttrCockpit(AttrCockpit::cockpit));
    ASSERT_TRUE(AttrCockpit(AttrCockpit::cockpit) != AttrCockpit(AttrCockpit::region_2));

    ASSERT_FALSE(AttrCockpit() != AttrCockpit());
    ASSERT_FALSE(AttrCockpit(AttrCockpit::region_2) != AttrCockpit(AttrCockpit::region_2));
    ASSERT_FALSE(AttrCockpit() == AttrCockpit(AttrCockpit::region_2));
    ASSERT_FALSE(AttrCockpit(AttrCockpit::region_2) == AttrCockpit(AttrCockpit::cockpit));
}

TEST(TestAttributes, AttrCockpitDevice) {
    AttrCockpit attr;

    attr.mType = AttrCockpit::cockpit_device;
    attr.mDeviceName = "GNS430_1";
    attr.mDeviceBus = 3;
    attr.mDeviceLightingChan = 2;
    attr.mDeviceAutoAdjust = true;
    // todo ASSERT_STREQ("ATTR_cockpit_device GNS430_1 3 2 1", strAttrResult(attr).c_str());
    ASSERT_EQ(AttrCockpit::cockpit_device, attr.mType);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
