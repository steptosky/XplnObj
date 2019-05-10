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
#include "algorithms/Draped.h"
#include "xpln/obj/ObjDrapedGroup.h"
#include "TestUtils.h"
#include "TestUtilsObjMesh.h"

using namespace xobj;

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

TEST(DrapedAlg, extract) {
    Transform transformRoot;
    auto & transform = transformRoot.newChild("l1");
    ObjDrapedGroup draped;

    const auto l1M1 = TestUtilsObjMesh::createPyramidTestMesh("l1-m1");
    const auto l2M1 = TestUtilsObjMesh::createPyramidTestMesh("l2-m2");
    auto l1M2 = TestUtilsObjMesh::createPyramidTestMesh("l1-m1");
    auto l2M2 = TestUtilsObjMesh::createPyramidTestMesh("l2-m2");

    l1M2->mAttr.mIsDraped = true;
    l2M2->mAttr.mIsDraped = true;

    transformRoot.addObject(l1M1);
    transformRoot.addObject(l1M2);

    transform.addObject(l2M1);
    transform.addObject(l2M2);

    Draped::extract(draped, transformRoot, NoInterrupter());

    EXPECT_EQ(1, transformRoot.objList().size());
    EXPECT_EQ(1, transformRoot.childAt(0)->objList().size());

    ASSERT_EQ(2, draped.transform().objList().size());
    EXPECT_STREQ("l1-m1", draped.transform().objList()[0]->objectName().c_str());
    EXPECT_STREQ("l2-m2", draped.transform().objList()[1]->objectName().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
