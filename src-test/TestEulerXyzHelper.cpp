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

#include "xpln/common/EulerXyzHelper.h"

using namespace xobj;

#define THRESHOLD 0.00001f

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

// The apper case letter means the appropriate animated axis

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(EulerXyzHelper, xyz_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(0.0f, 0.0f));
    y.pKeys.push_back(AnimRotate::Key(0.0f, 0.0f));
    z.pKeys.push_back(AnimRotate::Key(0.0f, 0.0f));
    ASSERT_TRUE(EulerXyzHelper(x, y, z).animation().empty());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(EulerXyzHelper, Xyz_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    x.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    y.pKeys.push_back(AnimRotate::Key(180.0f, 0.0f));

    z.pKeys.push_back(AnimRotate::Key(180.0f, 0.0f));

    AnimRotateList a = EulerXyzHelper(x, y, z).animation();
    ASSERT_EQ(1, a.size());
    ASSERT_NEAR(1.0f, a[0].pVector.x, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.y, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.z, THRESHOLD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(EulerXyzHelper, xYz_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(90.0f, 0.0f));

    y.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    y.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    z.pKeys.push_back(AnimRotate::Key(90.0f, 0.0f));

    AnimRotateList a = EulerXyzHelper(x, y, z).animation();
    ASSERT_EQ(1, a.size());
    ASSERT_NEAR(-1.0f, a[0].pVector.x, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.y, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.z, THRESHOLD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(EulerXyzHelper, xyZ_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(90.0f, 0.0f));

    y.pKeys.push_back(AnimRotate::Key(90.0f, 0.0f));

    z.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    z.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    AnimRotateList a = EulerXyzHelper(x, y, z).animation();
    ASSERT_EQ(1, a.size());
    ASSERT_NEAR(0.0f, a[0].pVector.x, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.y, THRESHOLD);
    ASSERT_NEAR(1.0f, a[0].pVector.z, THRESHOLD);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(EulerXyzHelper, XYz_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    x.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    y.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    y.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    z.pKeys.push_back(AnimRotate::Key(180.0f, 0.0f));

    AnimRotateList a = EulerXyzHelper(x, y, z).animation();
    ASSERT_EQ(2, a.size());

    ASSERT_NEAR( 0.0f, a[0].pVector.x, THRESHOLD);
    ASSERT_NEAR(-1.0f, a[0].pVector.y, THRESHOLD);
    ASSERT_NEAR( 0.0f, a[0].pVector.z, THRESHOLD);

    ASSERT_NEAR(-1.0f, a[1].pVector.x, THRESHOLD);
    ASSERT_NEAR( 0.0f, a[1].pVector.y, THRESHOLD);
    ASSERT_NEAR( 0.0f, a[1].pVector.z, THRESHOLD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(EulerXyzHelper, xYZ_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(90.0f, 0.0f));

    y.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    y.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    z.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    z.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    AnimRotateList a = EulerXyzHelper(x, y, z).animation();
    ASSERT_EQ(2, a.size());

    ASSERT_NEAR(0.0f, a[0].pVector.x, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.y, THRESHOLD);
    ASSERT_NEAR(1.0f, a[0].pVector.z, THRESHOLD);

    ASSERT_NEAR(0.0f, a[1].pVector.x, THRESHOLD);
    ASSERT_NEAR(1.0f, a[1].pVector.y, THRESHOLD);
    ASSERT_NEAR(0.0f, a[1].pVector.z, THRESHOLD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(EulerXyzHelper, XyZ_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    x.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    y.pKeys.push_back(AnimRotate::Key(180.0f, 0.0f));

    z.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    z.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    AnimRotateList a = EulerXyzHelper(x, y, z).animation();
    ASSERT_EQ(2, a.size());

    ASSERT_NEAR(0.0f, a[0].pVector.x, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.y, THRESHOLD);
    ASSERT_NEAR(1.0f, a[0].pVector.z, THRESHOLD);

    ASSERT_NEAR(-1.0f, a[1].pVector.x, THRESHOLD);
    ASSERT_NEAR( 0.0f, a[1].pVector.y, THRESHOLD);
    ASSERT_NEAR( 0.0f, a[1].pVector.z, THRESHOLD);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(EulerXyzHelper, XYZ_case1) {
    AnimRotate x, y, z;
    x.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    x.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    y.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    y.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    z.pKeys.push_back(AnimRotate::Key(-10.0f, 0.0f));
    z.pKeys.push_back(AnimRotate::Key(10.0f, 0.0f));

    AnimRotateList a = EulerXyzHelper(x, y, z).animation();
    ASSERT_EQ(3, a.size());

    ASSERT_NEAR(0.0f, a[0].pVector.x, THRESHOLD);
    ASSERT_NEAR(0.0f, a[0].pVector.y, THRESHOLD);
    ASSERT_NEAR(1.0f, a[0].pVector.z, THRESHOLD);

    ASSERT_NEAR(0.0f, a[1].pVector.x, THRESHOLD);
    ASSERT_NEAR(1.0f, a[1].pVector.y, THRESHOLD);
    ASSERT_NEAR(0.0f, a[1].pVector.z, THRESHOLD);

    ASSERT_NEAR(1.0f, a[2].pVector.x, THRESHOLD);
    ASSERT_NEAR(0.0f, a[2].pVector.y, THRESHOLD);
    ASSERT_NEAR(0.0f, a[2].pVector.z, THRESHOLD);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
