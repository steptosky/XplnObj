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

/*
 * Root <- obj1 <- obj2(T)
 * Without root matrix
 * The parent is not animated and it is rotated 90 degrees relative to Z in world space.
 * Animation moving the child along parent's X, so as the result in the world space the moving will be along Y axis
 */
TEST(TestTransformationAlgorithm_case3, case1) {
    const auto fileName = XOBJ_PATH("TestTransformationAlgorithm_case3-case1.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & trOut0 = lodOut.transform();
    Transform & trOut1 = trOut0.newChild(String(TOTEXT(trOut1)));
    Transform & trOut2 = trOut1.newChild(String(TOTEXT(trOut2)));

    trOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    trOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    trOut1.mMatrix.rotateDegreesZ(90.0f);
    trOut2.mMatrix.setPosition(Point3(50.0f, 0.0f, 50.0f));

    TestUtils::createTestAnimTranslate(trOut2.mPosition,
                                       Translate::Key{Point3(-50.0f, 0.0f, 0.0f), -10.0f},
                                       Translate::Key{Point3(50.0f, 0.0f, 0.0f), 10.0f},
                                       "trans1");
    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    Transform * trIn1 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, trIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*trIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    TestUtils::createTestAnimTranslate(animResult1.mPosition,
                                       Translate::Key{Point3(50.0f, -50.0f, 50.0f), -10.0f},
                                       Translate::Key{Point3(50.0f, 50.0f, 50.0f), 10.0f},
                                       "trans1");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", trOut1.mMatrix));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    ASSERT_TRUE(trIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(trIn1->mRotation == animResult1.mRotation);
    ASSERT_TRUE(trIn1->mPosition == animResult1.mPosition);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*
 * Root <- obj1 <- obj2(T)
 * With root matrix
 * The parent is not animated and it is rotated 90 degrees relative to Z in world space.
 * Animation moving the child along parent's X and then rotate the whole scene back with global matrix,
 *     so as the result in the world space the moving will be along X axis
 */
TEST(TestTransformationAlgorithm_case3, case2) {
    const auto fileName = XOBJ_PATH("TestTransformationAlgorithm_case3-case2.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & trOut0 = lodOut.transform();
    Transform & trOut1 = trOut0.newChild(String(TOTEXT(trOut1)));
    Transform & trOut2 = trOut1.newChild(String(TOTEXT(trOut2)));

    trOut1.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    trOut2.mObjects.emplace_back(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.mMatrix.rotateDegreesZ(-90.0f);
    trOut1.mMatrix.rotateDegreesZ(90.0f);
    trOut2.mMatrix.setPosition(Point3(50.0f, 0.0f, 50.0f));

    TestUtils::createTestAnimTranslate(trOut2.mPosition,
                                       Translate::Key{Point3(-50.0f, 0.0f, 0.0f), -10.0f},
                                       Translate::Key{Point3(50.0f, 0.0f, 0.0f), 10.0f},
                                       "trans1");
    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    Transform * trIn1 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, trIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*trIn1, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    TestUtils::createTestAnimTranslate(animResult1.mPosition,
                                       Translate::Key{Point3(-50.0f, -50.0f, 50.0f), -10.0f},
                                       Translate::Key{Point3(50.0f, -50.0f, 50.0f), 10.0f},
                                       "trans1");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", mainOut.mMatrix));

    ASSERT_TRUE(trIn1->mMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(trIn1->mRotation == animResult1.mRotation);
    ASSERT_TRUE(trIn1->mPosition == animResult1.mPosition);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
