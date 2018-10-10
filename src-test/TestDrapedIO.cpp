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
#include "xpln/obj/ObjDrapedGroup.h"
#include "TestUtils.h"
#include "TestUtilsObjMesh.h"

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(Draped, DISABLED_io) {
    const auto fileName = "Draped-io.obj";
    //-------------------
    // make out data and save to file
    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lod1 = mainOut.addLod(new ObjLodGroup("l1", 0.0f, 100.0f));
    ObjLodGroup & lod2 = mainOut.addLod(new ObjLodGroup("l2", 100.0f, 200.0f));

    lod1.transform().addObject(TestUtilsObjMesh::createPyramidTestMesh("l1-m1"));
    lod1.transform().addObject(TestUtilsObjMesh::createPyramidTestMesh("l1-m2"));

    lod2.transform().addObject(TestUtilsObjMesh::createPyramidTestMesh("l2-m1"));
    lod2.transform().addObject(TestUtilsObjMesh::createPyramidTestMesh("l2-m2"));

    mainOut.pDraped.transform().addObject(TestUtilsObjMesh::createPyramidTestMesh("d1"));
    mainOut.pDraped.transform().addObject(TestUtilsObjMesh::createPyramidTestMesh("d2"));

    ASSERT_TRUE(mainOut.exportToFile(fileName));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ASSERT_TRUE(mainIn.importFromFile(fileName));

    ObjLodGroup * lodIn1 = nullptr;
    ObjLodGroup * lodIn2 = nullptr;
    // One transform was optimized during export, it became LOD's transform
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 1, lodIn2));

    //-------------------
    // check results

    EXPECT_EQ(2, lodIn1->transform().objList().size());
    EXPECT_EQ(2, lodIn2->transform().objList().size());
    EXPECT_EQ(2, mainIn.pDraped.transform().objList().size());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
