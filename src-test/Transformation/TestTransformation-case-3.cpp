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

/* SET 3 */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- (R)obj1 <- (R)obj2 <- (R)obj3
 *
 *  +==============================================+
 *  | Result of obj files                          |
 *  +==============================================+
 *  | [TOP]                                        |
 *  |                                              |
 *  |                    ^ -Z                      |
 *  |                    |                         |
 *  |                    |                         |
 *  |                   /|\                        |
 *  |                  / | \                       |
 *  |                 /  R  \                      |
 *  |                /   |   \                     |
 *  |               /----|----\                    |
 *  |                    |                         |
 *  |         +-         |         -+              |
 *  |       +  |         |         |  +            |
 *  |     +    |         |         |    +     +X   |
 *  |   <   R  |         +---------|--R--->---->   |
 *  |     +    |                   |    +          |
 *  |       +  |                   |  +            |
 *  |         +-                   -+              |
 *  |                                              |
 *  +==============================================+
 *
 */
TEST(TestTransform_case3, case1) {
    const auto fileName = XOBJ_PATH("TestTransform_case3-case1.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));
    Transform & transformOut3 = transformOut2.newChild(TOTEXT(transformOut3));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    transformOut1.mMatrix.rotateDegreesY(+90.0f);
    transformOut2.mMatrix.rotateDegreesY(0.0f);
    transformOut3.mMatrix.rotateDegreesY(-90.0f);

    transformOut1.mMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));
    transformOut2.mMatrix.setPosition(Point3(0.0f, 0.0f, -50.0f));
    transformOut3.mMatrix.setPosition(Point3(50.0f, 0.0f, 0.0f));

    TestUtils::createTestAnimRotate(transformOut1.mRotation, Point3(0.0f, 1.0f, 0.0f), "test1");
    TestUtils::createTestAnimRotate(transformOut2.mRotation, Point3(0.0f, 1.0f, 0.0f), "test2");
    TestUtils::createTestAnimRotate(transformOut3.mRotation, Point3(0.0f, 1.0f, 0.0f), "test3");
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
    Transform * transformIn3 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ObjMesh * meshIn3 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn1, 0, transformIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn2, 0, transformIn3));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 0, meshIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn3, 0, meshIn3));

    //-------------------
    // check results

    Transform animResult1;
    Transform animResult2;
    Transform animResult3;
    TestUtils::createTestAnimRotate(animResult1.mRotation, Point3(0.0f, 1.0f, 0.0f), "test1");
    TestUtils::createTestAnimRotate(animResult2.mRotation, Point3(0.0f, 1.0f, 0.0f), "test2");
    TestUtils::createTestAnimRotate(animResult3.mRotation, Point3(0.0f, 1.0f, 0.0f), "test3");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", +90.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", 0.0f));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh("mesh 3", -90.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(-50.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn2->mMatrix.position() == Point3(50.0f, 0.0f, -50.0f));
    ASSERT_TRUE(transformIn3->mMatrix.position() == Point3(50.0f, 0.0f, 50.0f));
    ASSERT_TRUE(transformIn1->mRotation == animResult1.mRotation);
    ASSERT_TRUE(transformIn2->mRotation == animResult2.mRotation);
    ASSERT_TRUE(transformIn3->mRotation == animResult3.mRotation);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- (R)obj1 <- (R)obj2 <- (R)obj3
 *
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
 *  |   /   R   \   /   R   \   /   R   \    |
 *  |  /---------\ /---------\ /---------\   |
 *  |                                        |
 *  +========================================+
 *
 */
TEST(TestTransform_case3, case2) {
    const auto fileName = XOBJ_PATH("TestTransform_case3-case2.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));
    Transform & transformOut3 = transformOut2.newChild(TOTEXT(transformOut3));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    mainOut.mMatrix.setPosition(Point3(-50.0f, 0.0f, -50.0f));
    mainOut.mMatrix.rotateDegreesY(45.0f);

    transformOut1.mMatrix.rotateDegreesY(-45.0f);
    transformOut2.mMatrix.rotateDegreesY(-45.0f);
    transformOut3.mMatrix.rotateDegreesY(-45.0f);
    transformOut1.mMatrix.setPosition(Point3(50.0f, 0.0f, 50.0f));
    transformOut2.mMatrix.setPosition(Point3(100.0f, 0.0f, 100.0f));
    transformOut3.mMatrix.setPosition(Point3(150.0f, 0.0f, 150.0f));

    TestUtils::createTestAnimRotate(transformOut1.mRotation, Point3(0.0f, 1.0f, 0.0f), "test1");
    TestUtils::createTestAnimRotate(transformOut2.mRotation, Point3(0.0f, 1.0f, 0.0f), "test2");
    TestUtils::createTestAnimRotate(transformOut3.mRotation, Point3(0.0f, 1.0f, 0.0f), "test3");
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
    Transform * transformIn3 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ObjMesh * meshIn3 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn1, 0, transformIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn2, 0, transformIn3));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 0, meshIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 0, meshIn3));

    //-------------------
    // check results

    Transform animResult1;
    Transform animResult2;
    Transform animResult3;
    TestUtils::createTestAnimRotate(animResult1.mRotation, Point3(0.0f, 1.0f, 0.0f), "test1");
    TestUtils::createTestAnimRotate(animResult2.mRotation, Point3(0.0f, 1.0f, 0.0f), "test2");
    TestUtils::createTestAnimRotate(animResult3.mRotation, Point3(0.0f, 1.0f, 0.0f), "test3");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, 0.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh("mesh 3", Point3(0.0f, 0.0f, 0.0f), 0.0f));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn2->mMatrix.position() == Point3(70.71068f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn3->mMatrix.position() == Point3(70.71068f, 0.0f, 0.0f));
    ASSERT_TRUE(transformIn1->mRotation == animResult1.mRotation);
    ASSERT_TRUE(transformIn2->mRotation == animResult2.mRotation);
    ASSERT_TRUE(transformIn3->mRotation == animResult3.mRotation);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * This test reproduces the case when animation translate is the position of animation rotation axis.
 * Root <- (T)obj1 <- (T)obj2 <- (T)obj3
 */
TEST(TestTransform_case3, case3) {
    const auto fileName = XOBJ_PATH("TestTransform_case3-case3.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));
    Transform & transformOut3 = transformOut2.newChild(TOTEXT(transformOut3));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    transformOut1.mMatrix.setPosition(Point3(50.0f));
    transformOut2.mMatrix.setPosition(Point3(100.0f));
    transformOut3.mMatrix.setPosition(Point3(150.0f));

    auto & animTr1 = transformOut1.mPosition.mAnimation.emplace_back();
    animTr1.mDataRef.str() = "test";
    animTr1.mKeys.emplace_back();
    animTr1.mKeys.emplace_back();

    auto & animTr2 = transformOut2.mPosition.mAnimation.emplace_back();
    animTr2.mDataRef.str() = "test";
    animTr2.mKeys.emplace_back();
    animTr2.mKeys.emplace_back();

    auto & animTr3 = transformOut3.mPosition.mAnimation.emplace_back();
    animTr3.mDataRef.str() = "test";
    animTr3.mKeys.emplace_back();
    animTr3.mKeys.emplace_back();

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
    Transform * transformIn3 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ObjMesh * meshIn3 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn1, 0, transformIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn2, 0, transformIn3));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 0, meshIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn3, 0, meshIn3));

    //-------------------
    // check results

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh(nullptr, Point3(0.0f)));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh(nullptr, Point3(0.0f)));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh(nullptr, Point3(0.0f)));

    ASSERT_TRUE(transformIn1->mMatrix.position() == Point3(50.0f));
    ASSERT_TRUE(transformIn2->mMatrix.position() == Point3(50.0f));
    ASSERT_TRUE(transformIn3->mMatrix.position() == Point3(50.0f));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- (T)obj1 <- (T)obj2 <- (T)obj3
 *
 *  +===================================================================================================================================+
 *  | Result of obj files                                                                                                               |
 *  +===========================================+===========================================+===========================================+
 *  | [FRONT]                                   | [LEFT]                                    | [TOP]                                     |
 *  |                                           |                                           |                                           |
 *  |                                  ^        |                                  ^        |        ^ -Z                               |
 *  |                                 / \       |                                 / \       |        |                                  |
 *  |                                /   \      |                                /   \      |        |                                  |
 *  |                               /  T  \     |                               /  T  \     |       /|\                                 |
 *  |                     ^        /       \    |                     ^        /       \    |      / | \        +X                      |
 *  |                    / \      /---------\   |                    / \      /---------\   |     /  +----------->                      |
 *  |        ^ +Y       /   \                   |        ^ +Y       /   \                   |    /   T   \        ^                     |
 *  |        |         /  T  \                  |        |         /  T  \                  |   /---------\      / \                    |
 *  |        |        /       \                 |        |        /       \                 |                   /   \                   |
 *  |       /|\      /---------\                |       /|\      /---------\                |                  /  T  \                  |
 *  |      / | \        +X                      |      / | \        +Z                      |                 /       \        ^        |
 *  |     /  +----------->                      |     /  +----------->                      |                /---------\      / \       |
 *  |    /   T   \                              |    /   T   \                              |                                /   \      |
 *  |   /---------\                             |   /---------\                             |                               /  T  \     |
 *  |                                           |                                           |                              /       \    |
 *  |                                           |                                           |                             /---------\   |
 *  |                                           |                                           |                                           |
 *  +===========================================+============================================+==========================================+
 *
 */
TEST(TestTransform_case3, case4) {
    const auto fileName = XOBJ_PATH("TestTransform_case3-case4.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));
    Transform & transformOut3 = transformOut2.newChild(TOTEXT(transformOut3));

    transformOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    mainOut.mMatrix.setPosition(Point3(-50.0f));
    transformOut1.mMatrix.setPosition(Point3(50.0f));
    transformOut2.mMatrix.setPosition(Point3(100.0f));
    transformOut3.mMatrix.setPosition(Point3(150.0f));

    TestUtils::createTestAnimTranslate(transformOut1.mPosition, TMatrix(), "test1");
    TestUtils::createTestAnimTranslate(transformOut2.mPosition, TMatrix(), "test2");
    TestUtils::createTestAnimTranslate(transformOut3.mPosition, TMatrix(), "test3");
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
    Transform * transformIn3 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ObjMesh * meshIn3 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, transformIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn1, 0, transformIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*transformIn2, 0, transformIn3));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn2, 0, meshIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*transformIn3, 0, meshIn3));

    //-------------------
    // check results

    Transform animResult1;
    Transform animResult2;
    Transform animResult3;
    TestUtils::createTestAnimTranslate(animResult1.mPosition, Point3(0.0f), "test1");
    TestUtils::createTestAnimTranslate(animResult2.mPosition, Point3(50.0f), "test2");
    TestUtils::createTestAnimTranslate(animResult3.mPosition, Point3(50.0f), "test3");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh(nullptr, Point3(00.0f)));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh(nullptr, Point3(00.0f)));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh(nullptr, Point3(00.0f)));

    ASSERT_TRUE(transformIn1->mPosition == animResult1.mPosition);
    ASSERT_TRUE(transformIn2->mPosition == animResult2.mPosition);
    ASSERT_TRUE(transformIn3->mPosition == animResult3.mPosition);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
