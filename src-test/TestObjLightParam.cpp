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
#include <xpln/obj/ObjLightParam.h>
#include <xpln/common/TMatrix.h>
#include <sts/string/StringUtils.h>
#include <converters/Defines.h>

using namespace xobj;
using namespace std::string_literals;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(ObjLightParam, setParams_no_direction) {
    ObjLightParam l;
    l.setParams(String("0 $size"), {{"size", []() { return "3.0"; }}});
    ASSERT_STREQ("0 3.0", l.params().str().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(ObjLightParam, setParams_billboards_normal) {
    ObjLightParam l;
    const auto scale = LightUtils::billboardDirectionScaleFromAngle(1.5708f); // 90 deg
    l.setParams(String("$direction 0 $size"), {
                    {"direction", [&]() { return "0 -1 0 "s.append(sts::toString(scale, PRECISION)); }},
                    {"size", []() { return "3.0"; }},
                });
    ASSERT_STREQ("0.00000 -3.41420 0.00000 0 3.0", l.params().str().c_str());
}

TEST(ObjLightParam, setParams_billboards_expander_not_presented_case1) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"direction", [&]() { return "0 -1 0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction 0 $size"), expander), std::runtime_error);
}

TEST(ObjLightParam, setParams_billboards_expander_not_presented_case2) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"size", []() { return "3.0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction 0 $size"), expander), std::runtime_error);
}

TEST(ObjLightParam, setParams_billboards_not_enough_value) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"direction", [&]() { return "0 -1 0"; }},
                {"size", []() { return "3.0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction 0 $size"), expander), std::runtime_error);
}

TEST(ObjLightParam, setParams_billboards_incorrect_val) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"direction", [&]() { return "0 -1 0 test"; }},
                {"size", []() { return "3.0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction 0 $size"), expander), std::invalid_argument);
}

TEST(ObjLightParam, setParams_billboards_transform) {
    ObjLightParam l;
    l.setParams(String("$direction 0 $size"), {
                    {"direction", [&]() { return "0 -1 0 0.5"; }},
                    {"size", []() { return "3.0"; }},
                });
    TMatrix tm;
    tm.setPosition(Point3(1.0f, 1.0f, 1.0f)); // actually shouldn't be applied
    tm.rotateDegreesX(90.0f);
    l.applyTransform(tm);
    ASSERT_STREQ("0.00000 0.00000 -0.50000 0 3.0", l.params().str().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(ObjLightParam, setParams_spill_normal) {
    ObjLightParam l;
    l.setParams(String("$direction_sp 0 $size"), {
                    {"direction_sp", [&]() { return "0 -1 0 "; }},
                    {"size", []() { return "3.0"; }},
                });
    ASSERT_STREQ("0.00000 -1.00000 0.00000 0 3.0", l.params().str().c_str());
}

TEST(ObjLightParam, setParams_spill_expander_not_presented_case1) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"direction_sp", [&]() { return "0 -1 0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction_sp 0 $size"), expander), std::runtime_error);
}

TEST(ObjLightParam, setParams_spill_expander_not_presented_case2) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"size", []() { return "3.0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction_sp 0 $size"), expander), std::runtime_error);
}

TEST(ObjLightParam, setParams_spill_not_enough_value) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"direction_sp", [&]() { return "0 -1 "; }},
                {"size", []() { return "3.0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction_sp 0 $size"), expander), std::runtime_error);
}

TEST(ObjLightParam, setParams_spill_incorrect_val) {
    ObjLightParam l;
    const LightUtils::ParamExpanderMap expander{
                {"direction_sp", [&]() { return "0 -1 test"; }},
                {"size", []() { return "3.0"; }},
            };
    ASSERT_THROW(l.setParams(String("$direction_sp 0 $size"), expander), std::invalid_argument);
}

TEST(ObjLightParam, setParams_spill_transform) {
    ObjLightParam l;
    l.setParams(String("$direction_sp 0 $size"), {
                    {"direction_sp", [&]() { return "0 -1 0"; }},
                    {"size", []() { return "3.0"; }},
                });
    TMatrix tm;
    tm.setPosition(Point3(1.0f, 1.0f, 1.0f)); // actually shouldn't be applied
    tm.rotateDegreesX(90.0f);
    l.applyTransform(tm);
    ASSERT_STREQ("0.00000 0.00000 -1.00000 0 3.0", l.params().str().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
