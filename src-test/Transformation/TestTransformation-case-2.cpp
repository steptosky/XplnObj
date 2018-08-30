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

#include <xpln/obj/ObjMain.h>
#include <xpln/obj/ObjMesh.h>
#include "../TestUtilsObjMesh.h"
#include "../totext.h"
#include "../TestUtils.h"

using namespace xobj;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* SET 2 */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- (T)obj1 <- (T|R)obj2 <- obj3
 *
 *  +============================+
 *  | Original                   |
 *  +============================+
 *  | [TOP]                      |
 *  |                     +X     |
 *  |     +---------------->     |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   |  T  >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   |  TR >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +========================================+
 *  | Result of obj files                    |
 *  +========================================+
 *  | [TOP]                                  |
 *  |                                        |
 *  |       ^ -Z                             |
 *  |       |                                |
 *  |       |           ^           ^        |
 *  |      /|\         / \         / \       |
 *  |     / | \       /   \       /   \  +X  |
 *  |    /  +----------------------------->  |
 *  |   /   T   \   /   TR  \   /       \    |
 *  |  /---------\ /---------\ /---------\   |
 *  |                                        |
 *  +========================================+
 *
 */
TEST(TestTransform_case2, case1) {
    const std::string path(std::string(TOTEXT(TestTransform_case2)).append(".").append(TOTEXT(case1)).append(".obj"));
    //-------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.createChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.createChild(TOTEXT(transformOut2));
    Transform & transformOut3 = transformOut2.createChild(TOTEXT(transformOut3));

    transformOut1.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    mainOut.pMatrix.rotateDegreesY(90.0f);
    mainOut.pMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.pMatrix.rotateDegreesY(-90.0f);
    transformOut2.pMatrix.rotateDegreesY(-90.0f);
    transformOut3.pMatrix.rotateDegreesY(-90.0f);
    transformOut1.pMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.pMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));
    transformOut3.pMatrix.setPosition(Point3(0.0f, 0.0f, 150.0f));

    TestUtils::createTestAnimTranslate(transformOut1.pAnimTrans, Point3(0.0f, 0.0f, 50.0f), TMatrix(), "trans1");
    TestUtils::createTestAnimRotate(transformOut2.pAnimRotate, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    TestUtils::createTestAnimTranslate(transformOut2.pAnimTrans, Point3(50.0f, 0.0f, 0.0f), TMatrix(), "trans2");
    ASSERT_TRUE(mainOut.exportToFile(path));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ASSERT_TRUE(mainIn.importFromFile(path));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    Transform * transformIn1 = nullptr;
    Transform * transformIn2 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ObjMesh * meshIn3 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn1, 0, transformIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 0, meshIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 1, meshIn3));

    //-------------------
    // check results

    Transform animResult1;
    Transform animResult2;
    TestUtils::createTestAnimTranslate(animResult1.pAnimTrans,
                                       AnimTransKey(-50.0f, 0.0f, 0.0f, -10.0f), AnimTransKey(50.0f, 0.0f, -0.0f, 10.0f), "trans1");
    TestUtils::createTestAnimTranslate(animResult2.pAnimTrans,
                                       AnimTransKey(0.0f, 0.0f, -0.0f, -10.0f), AnimTransKey(100.0f, 0.0f, -0.0f, 10.0f), "trans2");
    TestUtils::createTestAnimRotate(animResult2.pAnimRotate, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh("mesh 3", Point3(50.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->pMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn2->pMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->pAnimTrans == animResult1.pAnimTrans);
    ASSERT_TRUE(transformIn2->pAnimTrans == animResult2.pAnimTrans);
    ASSERT_TRUE(transformIn2->pAnimRotate == animResult2.pAnimRotate);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- (R)obj1 <- (R)obj2 <- obj3
 *
 *  +============================+
 *  | Original                   |
 *  +============================+
 *  | [TOP]                      |
 *  |                     +X     |
 *  |     +---------------->     |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   |  R  >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   |  R  >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +========================================+
 *  | Result of obj files                    |
 *  +========================================+
 *  | [TOP]                                  |
 *  |                                        |
 *  |       ^ -Z                             |
 *  |       |                                |
 *  |       |           ^           ^        |
 *  |      /|\         / \         / \       |
 *  |     / | \       /   \       /   \  +X  |
 *  |    /  +----------------------------->  |
 *  |   /   R   \   /   R   \   /       \    |
 *  |  /---------\ /---------\ /---------\   |
 *  |                                        |
 *  +========================================+
 *
 */
TEST(TestTransform_case2, case2) {
    const std::string path(std::string(TOTEXT(TestTransform_case2)).append(".").append(TOTEXT(case2)).append(".obj"));
    //-------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.createChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.createChild(TOTEXT(transformOut2));
    Transform & transformOut3 = transformOut2.createChild(TOTEXT(transformOut3));

    transformOut1.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    mainOut.pMatrix.rotateDegreesY(90.0f);
    mainOut.pMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.pMatrix.rotateDegreesY(-90.0f);
    transformOut2.pMatrix.rotateDegreesY(-90.0f);
    transformOut3.pMatrix.rotateDegreesY(-90.0f);
    transformOut1.pMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.pMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));
    transformOut3.pMatrix.setPosition(Point3(0.0f, 0.0f, 150.0f));

    TestUtils::createTestAnimRotate(transformOut1.pAnimRotate, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    TestUtils::createTestAnimRotate(transformOut2.pAnimRotate, Point3(0.0f, 1.0f, 0.0f), "rotate2");
    ASSERT_TRUE(mainOut.exportToFile(path));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ASSERT_TRUE(mainIn.importFromFile(path));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    Transform * transformIn1 = nullptr;
    Transform * transformIn2 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ObjMesh * meshIn3 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn1, 0, transformIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 0, meshIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 1, meshIn3));

    //-------------------
    // check results

    Transform animResult1;
    Transform animResult2;
    TestUtils::createTestAnimRotate(animResult1.pAnimRotate, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    TestUtils::createTestAnimRotate(animResult2.pAnimRotate, Point3(0.0f, 1.0f, 0.0f), "rotate2");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh("mesh 3", Point3(50.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->pMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn2->pMatrix.position() == Point3(50.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->pAnimRotate == animResult1.pAnimRotate);
    ASSERT_TRUE(transformIn2->pAnimRotate == animResult2.pAnimRotate);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
