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
#include <array>

#include <xpln/obj/ObjMain.h>
#include <xpln/obj/ObjMesh.h>
#include "../TestUtilsObjMesh.h"
#include "../totext.h"
#include "../TestUtils.h"

using namespace xobj;

// TODO fix the tests

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* SET 5 */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- [X] <- obj2 <- (T|R)obj3 [Y - rotate, Z - Translate]
 * [with root tm]
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
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | TR  >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +===============================+
 *  | Result of obj files           |
 *  +===============================+
 *  | [TOP]                         |
 *  |                               |
 *  |       ^ -Z                    |
 *  |       |                       |
 *  |       |           ^           |
 *  |      /|\         / \          |
 *  |     / | \       /   \     +X  |
 *  |    /  +-------------------->  |
 *  |   /       \   /   TR  \       |
 *  |  /---------\ /---------\      |
 *  |                               |
 *  +===============================+
 *
 */
TEST(DISABLED_TestTransform_case5, tr_case1) {
    const auto fileName = XOBJ_PATH("TestTransform_case5-tr_case1.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));

    TestUtils::createTestAnimRotate(transformOut2.mAnimRotate, Point3(0.0f, 1.0f, 0.0f), TMatrix(), "test1");
    TestUtils::createTestAnimTranslate(transformOut2.mAnimTrans, Point3(0.0f, 0.0f, 50.0f), TMatrix(), "test2");
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
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    TestUtils::createTestAnimRotate(animResult1.mAnimRotate, Point3(0.0f, 1.0f, 0.0f), TMatrix(), "test1");
    TestUtils::createTestAnimTranslate(animResult1.mAnimTrans,
                                       AnimTransKey(0.0f, 0.0f, 100.0f, -10.0f), AnimTransKey(-100.0f, 0.0f, 100.0f, 10.0f), "test2");

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mAnimRotate == animResult1.mAnimRotate);
    ASSERT_TRUE(transformIn1->mAnimTrans == animResult1.mAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- [X] <- obj2 <- (T|R)obj3 [Z - rotate, Z - Translate]
 * [with root tm]
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
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | TR  >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +===============================+
 *  | Result of obj files           |
 *  +===============================+
 *  | [TOP]                         |
 *  |                               |
 *  |       ^ -Z                    |
 *  |       |                       |
 *  |       |           ^           |
 *  |      /|\         / \          |
 *  |     / | \       /   \     +X  |
 *  |    /  +-------------------->  |
 *  |   /       \   /   TR  \       |
 *  |  /---------\ /---------\      |
 *  |                               |
 *  +===============================+
 *
 */
TEST(DISABLED_TestTransform_case5, tr_case2) {
    const auto fileName = XOBJ_PATH("TestTransform_case5-tr_case2.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));

    TestUtils::createTestAnimRotate(transformOut2.mAnimRotate, Point3(0.0f, 0.0f, 1.0f), TMatrix(), "test1");
    TestUtils::createTestAnimTranslate(transformOut2.mAnimTrans, Point3(0.0f, 0.0f, 50.0f), TMatrix(), "test2");
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
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    TestUtils::createTestAnimRotate(animResult1.mAnimRotate, Point3(0.0f, 0.0f, 1.0f), TMatrix(), "test1");
    std::array<AnimTrans::Key, 2> tKeys = {
        AnimTrans::Key(Point3(0.0f, 0.0f, 0.0f), -10.0f),
        AnimTrans::Key(Point3(100.0f, 0.0f, 0.0f), 10.0f)
    };
    TestUtils::createTestAnimTranslate(animResult1.mAnimTrans, tKeys.data(), tKeys.size(), TMatrix(), "test2");

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mAnimRotate == animResult1.mAnimRotate);
    ASSERT_TRUE(transformIn1->mAnimTrans == animResult1.mAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- [X] <- obj2 <- (R)obj3 [Y - rotate]
 * [with root tm]
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
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | R   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +===============================+
 *  | Result of obj files           |
 *  +===============================+
 *  | [TOP]                         |
 *  |                               |
 *  |       ^ -Z                    |
 *  |       |                       |
 *  |       |           ^           |
 *  |      /|\         / \          |
 *  |     / | \       /   \     +X  |
 *  |    /  +-------------------->  |
 *  |   /       \   /   R   \       |
 *  |  /---------\ /---------\      |
 *  |                               |
 *  +===============================+
 *
 */
TEST(TestTransform_case5, r_case1) {
    const auto fileName = XOBJ_PATH("TestTransform_case5-r_case1.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));

    TestUtils::createTestAnimRotate(transformOut2.mAnimRotate, Point3(0.0f, 1.0f, 0.0f), TMatrix(), "test1");
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
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    TestUtils::createTestAnimRotate(animResult1.mAnimRotate, Point3(0.0f, 1.0f, 0.0f), TMatrix(), "test1");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(50.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mAnimRotate == animResult1.mAnimRotate);
    ASSERT_TRUE(transformIn1->mAnimTrans == animResult1.mAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- [X] <- obj2 <- (R)obj3 [Z - rotate]
 * [with root tm]
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
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | R   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +===============================+
 *  | Result of obj files           |
 *  +===============================+
 *  | [TOP]                         |
 *  |                               |
 *  |       ^ -Z                    |
 *  |       |                       |
 *  |       |           ^           |
 *  |      /|\         / \          |
 *  |     / | \       /   \     +X  |
 *  |    /  +-------------------->  |
 *  |   /       \   /   R   \       |
 *  |  /---------\ /---------\      |
 *  |                               |
 *  +===============================+
 *
 */
TEST(TestTransform_case5, r_case2) {
    const auto fileName = XOBJ_PATH("TestTransform_case5-r_case2.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));

    TestUtils::createTestAnimRotate(transformOut2.mAnimRotate, Point3(0.0f, 0.0f, 1.0f), TMatrix(), "test1");
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
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    TestUtils::createTestAnimRotate(animResult1.mAnimRotate, Point3(0.0f, 0.0f, 1.0f), TMatrix(), "test1");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(50.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mAnimRotate == animResult1.mAnimRotate);
    ASSERT_TRUE(transformIn1->mAnimTrans == animResult1.mAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- [X] <- obj2 <- (T)obj3 [Z - Translate]
 * [with root tm]
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
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | TR  >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +===============================+
 *  | Result of obj files           |
 *  +===============================+
 *  | [TOP]                         |
 *  |                               |
 *  |       ^ -Z                    |
 *  |       |                       |
 *  |       |           ^           |
 *  |      /|\         / \          |
 *  |     / | \       /   \     +X  |
 *  |    /  +-------------------->  |
 *  |   /       \   /   TR  \       |
 *  |  /---------\ /---------\      |
 *  |                               |
 *  +===============================+
 *
 */
TEST(DISABLED_TestTransform_case5, t_case1) {
    const auto fileName = XOBJ_PATH("TestTransform_case5-t_case1.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));

    TestUtils::createTestAnimTranslate(transformOut2.mAnimTrans, Point3(0.0f, 0.0f, 50.0f), TMatrix(), "test2");
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
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    std::array<AnimTrans::Key, 2> tKeys = {
        AnimTrans::Key(Point3(0.0f, 0.0f, 0.0f), -10.0f),
        AnimTrans::Key(Point3(100.0f, 0.0f, 0.0f), 10.0f)
    };
    TestUtils::createTestAnimTranslate(animResult1.mAnimTrans, tKeys.data(), tKeys.size(), TMatrix(), "test2");

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mAnimRotate == animResult1.mAnimRotate);
    ASSERT_TRUE(transformIn1->mAnimTrans == animResult1.mAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- [X] <- obj2 <- (T)obj3 [X - Translate]
 * [with root tm]
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
 *  |   | |   >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |   + |                      |
 *  |   | +                      |
 *  |   | | +                    |
 *  |   | TR  >                  |
 *  |   | | +                    |
 *  |   | +                      |
 *  |   + |                      |
 *  |     |                      |
 *  |     V +Z                   |
 *  |                            |
 *  +============================+
 *                 |
 *                 V
 *  +===============================+
 *  | Result of obj files           |
 *  +===============================+
 *  | [TOP]                         |
 *  |                               |
 *  |       ^ -Z                    |
 *  |       |                       |
 *  |       |           ^           |
 *  |      /|\         / \          |
 *  |     / | \       /   \     +X  |
 *  |    /  +-------------------->  |
 *  |   /       \   /   TR  \       |
 *  |  /---------\ /---------\      |
 *  |                               |
 *  +===============================+
 *
 */
TEST(DISABLED_TestTransform_case5, t_case2) {
    const auto fileName = XOBJ_PATH("TestTransform_case5-t_case2.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));

    TestUtils::createTestAnimTranslate(transformOut2.mAnimTrans, Point3(50.0f, 0.0f, 0.0f), TMatrix(), "test2");
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
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    std::array<AnimTrans::Key, 2> tKeys = {
        AnimTrans::Key(Point3(50.0f, 0.0f, 50.0f), -10.0f),
        AnimTrans::Key(Point3(50.0f, 0.0f, -50.0f), 10.0f)
    };
    TestUtils::createTestAnimTranslate(animResult1.mAnimTrans, tKeys.data(), tKeys.size(), TMatrix(), "test2");

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mAnimRotate == animResult1.mAnimRotate);
    ASSERT_TRUE(transformIn1->mAnimTrans == animResult1.mAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
* Root <- [X] <- obj2 <- (T)obj3 [Y - Translate]
* [with root tm]
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
*  |   | |   >                  |
*  |   | | +                    |
*  |   | +                      |
*  |   + |                      |
*  |     |                      |
*  |   + |                      |
*  |   | +                      |
*  |   | | +                    |
*  |   | TR  >                  |
*  |   | | +                    |
*  |   | +                      |
*  |   + |                      |
*  |     |                      |
*  |     V +Z                   |
*  |                            |
*  +============================+
*                 |
*                 V
*  +===============================+
*  | Result of obj files           |
*  +===============================+
*  | [TOP]                         |
*  |                               |
*  |       ^ -Z                    |
*  |       |                       |
*  |       |           ^           |
*  |      /|\         / \          |
*  |     / | \       /   \     +X  |
*  |    /  +-------------------->  |
*  |   /       \   /   TR  \       |
*  |  /---------\ /---------\      |
*  |                               |
*  +===============================+
*
*/
TEST(TestTransform_case5, t_case3) {
    const auto fileName = XOBJ_PATH("TestTransform_case5-t_case3.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesY(90.0f);
    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));

    transformOut1.mMatrix.rotateDegreesY(-90.0f);
    transformOut2.mMatrix.rotateDegreesY(-90.0f);
    transformOut1.mMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, 100.0f));

    TestUtils::createTestAnimTranslate(transformOut2.mAnimTrans, Point3(0.0f, 50.0f, 0.0f), TMatrix(), "test2");
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
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    std::array<AnimTrans::Key, 2> tKeys = {
        AnimTrans::Key(Point3(50.0f, -50.0f, 0.0f), -10.0f),
        AnimTrans::Key(Point3(50.0f, 50.0f, 0.0f), 10.0f)
    };
    TestUtils::createTestAnimTranslate(animResult1.mAnimTrans, tKeys.data(), tKeys.size(), TMatrix(), "test2");

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mAnimRotate == animResult1.mAnimRotate);
    ASSERT_TRUE(transformIn1->mAnimTrans == animResult1.mAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
