/*
**  Copyright(C) 2019, StepToSky
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
#include "xpln/obj/animation/LinearRotation.h"

using namespace xobj;

const float gEpsilon = 0.0002f;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

// double rotation around one axis [Z] [0/45/90] degrees
TEST(LinearRotation, makeAnimations_double_rotate_z) {
    LinearRotation input;

    input.mKeys.emplace_back(LinearRotation::Key{Quat(1.000000f, 0.0f, 0.0f, +0.000000f), 00.0f}); //  0
    input.mKeys.emplace_back(LinearRotation::Key{Quat(0.923880f, 0.0f, 0.0f, -0.382683f), 10.0f}); // 45
    input.mKeys.emplace_back(LinearRotation::Key{Quat(0.707107f, 0.0f, 0.0f, -0.707107f), 20.0f}); // 90

    const auto result = input.retrieveAxes();

    //-----------------------------------------------

    ASSERT_EQ(1, result.mAxes.size());
    const auto & anim1 = result.mAxes.at(0);

    EXPECT_NEAR(0.0f, anim1.mVector.x, gEpsilon);
    EXPECT_NEAR(0.0f, anim1.mVector.y, gEpsilon);
    EXPECT_NEAR(1.0f, anim1.mVector.z, gEpsilon);

    ASSERT_EQ(3, anim1.mKeys.size());
    EXPECT_NEAR(00.0f, anim1.mKeys.at(0).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(45.0f, anim1.mKeys.at(1).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(90.0f, anim1.mKeys.at(2).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(00.0f, anim1.mKeys.at(0).value, gEpsilon);
    EXPECT_NEAR(10.0f, anim1.mKeys.at(1).value, gEpsilon);
    EXPECT_NEAR(20.0f, anim1.mKeys.at(2).value, gEpsilon);
}

// it more complex and was taken from 3Ds Max, so this is not human readable.
// there is a scene where data for this test was created.
TEST(LinearRotation, makeAnimations_comples_3_axis) {
    LinearRotation input;

    // [WORLD] [0]
    input.mKeys.emplace_back(LinearRotation::Key{Quat(+1.000000f, +0.000000f, +0.000000f, +0.000000f), 00.0f});
    // [WORLD] [Z] [90]                             
    input.mKeys.emplace_back(LinearRotation::Key{Quat(+0.707107f, +0.000000f, +0.000000f, -0.707107f), 10.0f});
    // [WORLD] [Y] [90]                             
    input.mKeys.emplace_back(LinearRotation::Key{Quat(+0.500000f, -0.500000f, -0.500000f, -0.500000f), 20.0f});
    // [WORLD] [Y] [180]                            
    input.mKeys.emplace_back(LinearRotation::Key{Quat(+0.000000f, -0.707107f, -0.707107f, +0.000000f), 30.0f});
    // [WORLD] [X] [90]
    input.mKeys.emplace_back(LinearRotation::Key{Quat(-0.500000f, -0.500000f, -0.500000f, -0.500000f), 40.0f});

    const auto result = input.retrieveAxes();

    //-----------------------------------------------

    ASSERT_EQ(3, result.mAxes.size());

    const auto & anim1 = result.mAxes.at(0);
    const auto & anim2 = result.mAxes.at(1);
    const auto & anim3 = result.mAxes.at(2);

    ASSERT_EQ(3, anim1.mKeys.size());
    ASSERT_EQ(5, anim2.mKeys.size());
    ASSERT_EQ(3, anim3.mKeys.size());

    /*
        ANIM_begin
            ANIM_trans 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 none
            ANIM_rotate_begin 0.00000 1.00000 0.00000 dataref
                ANIM_rotate_key 0.00000  0.00000
                ANIM_rotate_key 0.25000 90.00000
                ANIM_rotate_key 1.00000 90.00000
            ANIM_rotate_end
            ANIM_rotate_begin 1.00000 0.00000 0.00000 dataref
                ANIM_rotate_key 0.00000   0.00000
                ANIM_rotate_key 0.25000   0.00000
                ANIM_rotate_key 0.50000  90.00000
                ANIM_rotate_key 0.75000 180.00000
                ANIM_rotate_key 1.00000 180.00000
            ANIM_rotate_end
            ANIM_rotate_begin 0.00000 0.00000 -1.00000 dataref
                ANIM_rotate_key 0.00000  0.00000
                ANIM_rotate_key 0.75000  0.00000
                ANIM_rotate_key 1.00000 90.00000
            ANIM_rotate_end
            TRIS 0 18 ## TestObject
        ANIM_end
     */

    EXPECT_NEAR(00.0f, anim1.mKeys.at(0).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(90.0f, anim1.mKeys.at(1).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(90.0f, anim1.mKeys.at(2).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(00.0f, anim1.mKeys.at(0).value, gEpsilon);
    EXPECT_NEAR(10.0f, anim1.mKeys.at(1).value, gEpsilon);
    EXPECT_NEAR(40.0f, anim1.mKeys.at(2).value, gEpsilon);

    EXPECT_NEAR(000.0f, anim2.mKeys.at(0).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(000.0f, anim2.mKeys.at(1).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(090.0f, anim2.mKeys.at(2).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(180.0f, anim2.mKeys.at(3).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(180.0f, anim2.mKeys.at(4).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(00.0f, anim2.mKeys.at(0).value, gEpsilon);
    EXPECT_NEAR(10.0f, anim2.mKeys.at(1).value, gEpsilon);
    EXPECT_NEAR(20.0f, anim2.mKeys.at(2).value, gEpsilon);
    EXPECT_NEAR(30.0f, anim2.mKeys.at(3).value, gEpsilon);
    EXPECT_NEAR(40.0f, anim2.mKeys.at(4).value, gEpsilon);

    EXPECT_NEAR(00.0f, anim3.mKeys.at(0).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(00.0f, anim3.mKeys.at(1).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(90.0f, anim3.mKeys.at(2).angleDeg.value(), gEpsilon);
    EXPECT_NEAR(00.0f, anim3.mKeys.at(0).value, gEpsilon);
    EXPECT_NEAR(30.0f, anim3.mKeys.at(1).value, gEpsilon);
    EXPECT_NEAR(40.0f, anim3.mKeys.at(2).value, gEpsilon);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(LinearRotation, checkDatarefValuesOrder_valid_cases) {
    LinearRotation input;

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), 1.0f}},
    };
    EXPECT_FALSE(input.checkDatarefValuesOrder().has_value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), 2.0f}},
    };
    EXPECT_FALSE(input.checkDatarefValuesOrder().has_value());;

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), 2.0f}},
            {LinearRotation::Key{Quat(), 3.0f}},
    };
    EXPECT_FALSE(input.checkDatarefValuesOrder().has_value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), -1.0f}},
    };
    EXPECT_FALSE(input.checkDatarefValuesOrder().has_value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), -1.0f}},
            {LinearRotation::Key{Quat(), -3.0f}},
    };
    EXPECT_FALSE(input.checkDatarefValuesOrder().has_value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), -1.0f}},
            {LinearRotation::Key{Quat(), 2.0f}},
            {LinearRotation::Key{Quat(), 3.0f}},
    };
    EXPECT_FALSE(input.checkDatarefValuesOrder().has_value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), -1.0f}},
            {LinearRotation::Key{Quat(), -2.0f}},
            {LinearRotation::Key{Quat(), -3.0f}},
    };
    EXPECT_FALSE(input.checkDatarefValuesOrder().has_value());
}

TEST(LinearRotation, checkDatarefValuesOrder_invalid_cases) {
    LinearRotation input;

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), -2.0f}},
            {LinearRotation::Key{Quat(), 3.0f}},
    };
    auto result = input.checkDatarefValuesOrder();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(2, result.value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), 2.0f}},
            {LinearRotation::Key{Quat(), -1.0f}},
    };
    result = input.checkDatarefValuesOrder();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(2, result.value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), 1.0f}},
            {LinearRotation::Key{Quat(), 3.0f}},
            {LinearRotation::Key{Quat(), 2.0f}},
    };
    result = input.checkDatarefValuesOrder();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(2, result.value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), -1.0f}},
            {LinearRotation::Key{Quat(), -2.0f}},
            {LinearRotation::Key{Quat(), 3.0f}},
    };
    result = input.checkDatarefValuesOrder();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(2, result.value());

    input.mKeys = {
            {LinearRotation::Key{Quat(), -1.0f}},
            {LinearRotation::Key{Quat(), 2.0f}},
            {LinearRotation::Key{Quat(), -1.0f}},
    };
    result = input.checkDatarefValuesOrder();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(2, result.value());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
