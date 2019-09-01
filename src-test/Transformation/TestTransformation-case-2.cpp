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
    const auto fileName = XOBJ_PATH("TestTransform_case2-case1.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(String(TOTEXT(transformOut1)));
    Transform & transformOut2 = transformOut1.newChild(String(TOTEXT(transformOut2)));
    Transform & transformOut3 = transformOut2.newChild(String(TOTEXT(transformOut3)));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut3.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));
    transformOut3.mMatrix.setPosition(Point3(0.0f, 0.0f, 150.0f));

    TestUtils::createTestAnimTranslate(transformOut1.mPosition, Point3(0.0f, 0.0f, 50.0f), TMatrix(), "trans1");
    TestUtils::createTestAnimRotate(transformOut2.mRotation, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    TestUtils::createTestAnimTranslate(transformOut2.mPosition, Point3(50.0f, 0.0f, 0.0f), TMatrix(), "trans2");
    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));

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
    TestUtils::createTestAnimTranslate(animResult1.mPosition,
                                       Translate::Key{Point3(-50.0f, 0.0f, 0.0f), -10.0f},
                                       Translate::Key{Point3(50.0f, 0.0f, -0.0f), 10.0f},
                                       "trans1");
    TestUtils::createTestAnimTranslate(animResult2.mPosition,
                                       Translate::Key{Point3(0.0f, 0.0f, -0.0f), -10.0f},
                                       Translate::Key{Point3(100.0f, 0.0f, -0.0f), 10.0f},
                                       "trans2");
    TestUtils::createTestAnimRotate(animResult2.mRotation, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh("mesh 3", Point3(50.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn2->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mPosition == animResult1.mPosition);
    ASSERT_TRUE(transformIn2->mPosition == animResult2.mPosition);
    ASSERT_TRUE(transformIn2->mRotation == animResult2.mRotation);
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
    const auto fileName = XOBJ_PATH("TestTransform_case2-case2.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(String(TOTEXT(transformOut1)));
    Transform & transformOut2 = transformOut1.newChild(String(TOTEXT(transformOut2)));
    Transform & transformOut3 = transformOut2.newChild(String(TOTEXT(transformOut3)));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut3.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));
    transformOut3.mMatrix.setPosition(Point3(0.0f, 0.0f, 150.0f));

    TestUtils::createTestAnimRotate(transformOut1.mRotation, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    TestUtils::createTestAnimRotate(transformOut2.mRotation, Point3(0.0f, 1.0f, 0.0f), "rotate2");
    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));

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
    TestUtils::createTestAnimRotate(animResult1.mRotation, Point3(0.0f, 1.0f, 0.0f), "rotate1");
    TestUtils::createTestAnimRotate(animResult2.mRotation, Point3(0.0f, 1.0f, 0.0f), "rotate2");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh("mesh 3", Point3(50.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn2->mMatrix.position() == Point3(50.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mRotation == animResult1.mRotation);
    ASSERT_TRUE(transformIn2->mRotation == animResult2.mRotation);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
