/*
**  Copyright(C) 2018, StepToSky
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
#include <xpln/utils/LightUtils.h>

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(LightUtils, spill_cone) {
    EXPECT_FLOAT_EQ(0.17364657f, LightUtils::spillConeWidthFromAngle(2.79253f));  // 160 deg
    EXPECT_FLOAT_EQ(0.70710552f, LightUtils::spillConeWidthFromAngle(1.5708f));   // 90 deg
    EXPECT_FLOAT_EQ(0.96592581f, LightUtils::spillConeWidthFromAngle(0.523599f)); // 30 deg

    EXPECT_FLOAT_EQ(2.79253f, LightUtils::spillConeWidthToAngle(0.17364657f));  // 160 deg
    EXPECT_FLOAT_EQ(1.5708f, LightUtils::spillConeWidthToAngle(0.70710552f));   // 90 deg
    EXPECT_FLOAT_EQ(0.523599f, LightUtils::spillConeWidthToAngle(0.96592581f)); // 30 deg
}

TEST(LightUtils, billboard_cone) {
    EXPECT_FLOAT_EQ(0.46410179f, LightUtils::billboardConeWidthFromAngle(5.23599f));  // 300 deg
    EXPECT_FLOAT_EQ(-0.21013595f, LightUtils::billboardConeWidthFromAngle(2.79253f)); // 160 deg
    EXPECT_FLOAT_EQ(-28.347729f, LightUtils::billboardConeWidthFromAngle(0.523599f)); // 30 deg

    EXPECT_FLOAT_EQ(0.53589821f, LightUtils::billboardDirectionScaleFromAngle(5.23599f)); // 300 deg
    EXPECT_FLOAT_EQ(1.2101359f, LightUtils::billboardDirectionScaleFromAngle(2.79253f));  // 160 deg
    EXPECT_FLOAT_EQ(29.347729f, LightUtils::billboardDirectionScaleFromAngle(0.523599f)); // 30 deg

    EXPECT_FLOAT_EQ(5.23599f, LightUtils::billboardConeWidthToAngle(0.46410179f));  // 300 deg
    EXPECT_FLOAT_EQ(2.79253f, LightUtils::billboardConeWidthToAngle(-0.21013595f)); // 160 deg
    EXPECT_FLOAT_EQ(0.523599f, LightUtils::billboardConeWidthToAngle(-28.347729f)); // 30 deg
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(LightUtils, replaceVariables_normal) {
    ASSERT_STRCASEEQ("word 1 2 word", LightUtils::replaceVariables("word $test1 $test2 word", LightUtils::ParamExpanderMap{
            LightUtils::ParamExpanderMap::value_type{ "test1", []()->std::string {return "1"; }},
        LightUtils::ParamExpanderMap::value_type{ "test2", []()->std::string {return "2"; }},
        }).c_str());
}

TEST(LightUtils, replaceVariables_incorrect_var) {
    ASSERT_ANY_THROW(LightUtils::replaceVariables("word $test1 $ word", LightUtils::ParamExpanderMap{
            LightUtils::ParamExpanderMap::value_type{ "test1", []()->std::string {return "1"; }},
        LightUtils::ParamExpanderMap::value_type{ "test2", []()->std::string {return "2"; }},
        }));
}

TEST(LightUtils, replaceVariables_no_getter) {
    ASSERT_ANY_THROW(LightUtils::replaceVariables("word $test1 $test2 word", LightUtils::ParamExpanderMap{
            LightUtils::ParamExpanderMap::value_type{ "test1", []()->std::string {return "1"; }},
        }));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(LightUtils, billboardCorrectConeAngle_normal) {
    //------------------------------
    auto result = LightUtils::billboardCorrectConeAngle("$direction", 10.0f);
    EXPECT_STREQ("$direction", std::get<0>(result).c_str());
    EXPECT_FLOAT_EQ(10.0f, std::get<1>(result));
    //------------------------------
    result = LightUtils::billboardCorrectConeAngle("$direction:a5.5", 10.0f);
    EXPECT_STREQ("$direction", std::get<0>(result).c_str());
    EXPECT_FLOAT_EQ(5.5f, std::get<1>(result));
    //------------------------------
    result = LightUtils::billboardCorrectConeAngle("$direction:a+5.5", 10.0f);
    EXPECT_STREQ("$direction", std::get<0>(result).c_str());
    EXPECT_FLOAT_EQ(15.5f, std::get<1>(result));
    //------------------------------
    result = LightUtils::billboardCorrectConeAngle("$direction:a-5.5", 10.0f);
    EXPECT_STREQ("$direction", std::get<0>(result).c_str());
    EXPECT_FLOAT_EQ(4.5f, std::get<1>(result));
    //------------------------------
}

TEST(LightUtils, billboardCorrectConeAngle_not_normal) {
    EXPECT_THROW(LightUtils::billboardCorrectConeAngle("$direction:b", 10.0f), std::runtime_error);
    EXPECT_THROW(LightUtils::billboardCorrectConeAngle("$direction:ab", 10.0f), std::invalid_argument);
    EXPECT_THROW(LightUtils::billboardCorrectConeAngle("$direction:a5c", 10.0f), std::invalid_argument);

    EXPECT_THROW(LightUtils::billboardCorrectConeAngle("$direction:a+b", 10.0f), std::invalid_argument);
    EXPECT_THROW(LightUtils::billboardCorrectConeAngle("$direction:a-1.c", 10.0f), std::invalid_argument);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
