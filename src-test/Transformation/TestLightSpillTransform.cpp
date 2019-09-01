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
#include <xpln/obj/ObjLightSpillCust.h>
#include <io/ObjTransformation.h>
#include "../TestUtils.h"

using namespace xobj;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

TEST(ObjLightSpillCust, transform_mirror_direction) {
    ObjLightSpillCust l;
    //-------------------------
    l.setPosition(Point3(10.0f, 10.0f, 10.0f));
    l.setDirection(Point3(2.0f, 2.0f, 2.0f));

    // mirror all axis
    TMatrix tm;
    tm.set(-1.0f, 0.0f, 0.0f,
           0.0f, -1.0f, 0.0f,
           0.0f, 0.0f, -1.0f,
           0.0f, 0.0f, 0.0f);
    l.applyTransform(tm);

    const auto dir = l.direction();
    EXPECT_FLOAT_EQ(-0.577350259f, dir.x);
    EXPECT_FLOAT_EQ(-0.577350259f, dir.y);
    EXPECT_FLOAT_EQ(-0.577350259f, dir.z);
    //-------------------------
}

TEST(ObjLightSpillCust, transform_rotate_direction) {
    ObjLightSpillCust l;
    //-------------------------
    l.setPosition(Point3(10.0f, 10.0f, 10.0f));
    l.setDirection(Point3(2.0f, 2.0f, 2.0f));

    TMatrix tm;
    tm.set(1.0f, 0.0f, 0.0f,
           0.0f, 1.0f, 0.0f,
           0.0f, 0.0f, 1.0f,
           0.0f, 0.0f, 0.0f);
    tm.rotateDegreesX(180.0f);
    l.applyTransform(tm);

    const auto dir = l.direction();
    EXPECT_FLOAT_EQ(0.577350259f, dir.x);
    EXPECT_FLOAT_EQ(-0.577350259f, dir.y);
    EXPECT_FLOAT_EQ(-0.577350259f, dir.z);
    //-------------------------
}

TEST(ObjLightSpillCust, transform_move_direction) {
    ObjLightSpillCust l;
    //-------------------------
    l.setPosition(Point3(10.0f, 10.0f, 10.0f));
    l.setDirection(Point3(2.0f, 2.0f, 2.0f));

    TMatrix tm;
    tm.set(1.0f, 0.0f, 0.0f,
           0.0f, 1.0f, 0.0f,
           0.0f, 0.0f, 1.0f,
           10.0f, 10.0f, 10.0f);
    l.applyTransform(tm);

    const auto dir = l.direction();
    EXPECT_FLOAT_EQ(0.577350259f, dir.x);
    EXPECT_FLOAT_EQ(0.577350259f, dir.y);
    EXPECT_FLOAT_EQ(0.577350259f, dir.z);
    //-------------------------
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// 3DsMax's system coordinates to OGL.
TEST(ObjLightSpillCust, real_usecase_case1) {
    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);

    // set OGL mtx
    mainOut.mMatrix.set(1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f);

    ObjLodGroup & lod = mainOut.addLod();
    Transform & lodTransform = lod.transform();
    Transform & lightTransform = lodTransform.newChild(String("light transform"));
    // scale
    lodTransform.mMatrix.set(0.1f, 0.0f, 0.0f,
                             0.0f, 0.1f, 0.0f,
                             0.0f, 0.0f, 0.1f,
                             0.0f, 0.0f, 0.0f);
    lightTransform.mMatrix.setPosition(Point3(0.0f, -10.0f, 0.0f));

    auto * light = new ObjLightSpillCust;
    light->setPosition(Point3(0.0f, -10.0f, 0.0f));
    light->setDirection(Point3(0.0f, -5.0f, 0.0f) - light->position());
    lightTransform.mObjects.emplace_back(light);

    ObjTransformation::correctExportTransform(mainOut, mainOut.mMatrix, true);

    const auto resultTrPos = lightTransform.mMatrix.position();
    EXPECT_FLOAT_EQ(0.0f, resultTrPos.x) << resultTrPos.toString();
    EXPECT_FLOAT_EQ(-10.0f, resultTrPos.y) << resultTrPos.toString();
    EXPECT_FLOAT_EQ(0.0f, resultTrPos.z) << resultTrPos.toString();

    const auto resultLightPos = light->position();
    EXPECT_FLOAT_EQ(0.0f, resultLightPos.x) << resultLightPos.toString();
    EXPECT_FLOAT_EQ(0.0f, resultLightPos.y) << resultLightPos.toString();
    EXPECT_FLOAT_EQ(2.0f, resultLightPos.z) << resultLightPos.toString();

    const auto resultDirection = light->direction();
    EXPECT_FLOAT_EQ(0.0f, resultDirection.x) << resultDirection.toString();
    EXPECT_FLOAT_EQ(0.0f, resultDirection.y) << resultDirection.toString();
    EXPECT_FLOAT_EQ(-1.0f, resultDirection.z) << resultDirection.toString();
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
