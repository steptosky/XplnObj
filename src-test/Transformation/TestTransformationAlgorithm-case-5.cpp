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

#include "ph/stdafx.h"
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
 * Root <- obj1(TR) <- obj2(T)
 * Without root matrix
 * The parent is animated and it is rotated 90 degrees relative to Z in world space and it has offset.
 * Animation rotate the parent around parent's X, so as the result in the world space the rotation will be around X axis
 * Animation moving the parent along world's X, so as the result in the world space the moving will be along X axis.
 * Animation moving the child along parent's X, so as the result in the world space the moving will be along Y axis.
 */
TEST(TestTransformationAlgorithm_case5, case1) {
    const std::string path(std::string(TOTEXT(TestTransformationAlgorithm_case5)).append(".").append(TOTEXT(case1)).append(".obj"));
    //-------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & trOut0 = lodOut.transform();
    Transform & trOut1 = trOut0.createChild(TOTEXT(trOut1));
    Transform & trOut2 = trOut1.createChild(TOTEXT(trOut2));

    trOut1.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    trOut2.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    trOut1.pMatrix.rotateDegreesZ(90.0f);
    trOut1.pMatrix.setPosition(Point3(-50.0f, 0.0f, -50.0f));
    trOut2.pMatrix.setPosition(Point3(50.0f, 0.0f, 50.0f));

    TestUtils::createTestAnimRotate(trOut1.pAnimRotate, Point3(1.0f, 0.0f, 0.0f), "rot1");
    TestUtils::createTestAnimTranslate(trOut1.pAnimTrans,
                                       AnimTransKey(-50.0f, 0.0f, 0.0f, -10.0f), AnimTransKey(50.0f, 0.0f, 0.0f, 10.0f), "trans1");
    TestUtils::createTestAnimTranslate(trOut2.pAnimTrans,
                                       AnimTransKey(-50.0f, 0.0f, 0.0f, -10.0f), AnimTransKey(50.0f, 0.0f, 0.0f, 10.0f), "trans2");
    ASSERT_TRUE(mainOut.exportToFile(path));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ASSERT_TRUE(mainIn.importFromFile(path));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    Transform * trIn1 = nullptr;
    Transform * trIn2 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, trIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*trIn1, 0, trIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*trIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*trIn2, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    Transform animResult2;
    TestUtils::createTestAnimRotate(animResult1.pAnimRotate, Point3(1.0f, 0.0f, 0.0f), "rot1");
    TestUtils::createTestAnimTranslate(animResult1.pAnimTrans,
                                       AnimTransKey(-100.0f, 0.0f, -50.0f, -10.0f), AnimTransKey(0.0f, 0.0f, -50.0f, 10.0f), "trans1");
    TestUtils::createTestAnimTranslate(animResult2.pAnimTrans,
                                       AnimTransKey(100.0f, -50.0f, 100.0f, -10.0f), AnimTransKey(100.0f, 50.0f, 100.0f, 10.0f), "trans2");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", trOut1.pMatrix.toRotation()));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    ASSERT_TRUE(trIn1->pMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(trIn1->pAnimRotate == animResult1.pAnimRotate);
    ASSERT_TRUE(trIn1->pAnimTrans == animResult1.pAnimTrans);
    ASSERT_TRUE(trIn2->pMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(trIn2->pAnimRotate == animResult2.pAnimRotate);
    ASSERT_TRUE(trIn2->pAnimTrans == animResult2.pAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*
 * Root <- obj1(TR) <- obj2(T)
 * With root matrix
 * The parent is animated and it is rotated 90 degrees relative to Z in world space and it has offset.
 * Animation rotate the parent around parent's X, so as the result in the world space the rotation will be around Y axis
 * Animation moving the parent along world's X, so as the result in the world space the moving will be along Y axis.
 * Animation moving the child along parent's X, so as the result in the world space the moving will be along X axis.
 * Then rotate the whole scene back with global matrix.
 */
TEST(TestTransformationAlgorithm_case5, case2) {
    const std::string path(std::string(TOTEXT(TestTransformationAlgorithm_case5)).append(".").append(TOTEXT(case2)).append(".obj"));
    //-------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & trOut0 = lodOut.transform();
    Transform & trOut1 = trOut0.createChild(TOTEXT(trOut1));
    Transform & trOut2 = trOut1.createChild(TOTEXT(trOut2));

    trOut1.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    trOut2.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.pMatrix.rotateDegreesZ(-90.0f);
    trOut1.pMatrix.rotateDegreesZ(90.0f);
    trOut1.pMatrix.setPosition(Point3(-50.0f, 0.0f, -50.0f));
    trOut2.pMatrix.setPosition(Point3(50.0f, 0.0f, 50.0f));

    TestUtils::createTestAnimRotate(trOut1.pAnimRotate, Point3(1.0f, 0.0f, 0.0f), "rot1");
    TestUtils::createTestAnimTranslate(trOut1.pAnimTrans,
                                       AnimTransKey(-50.0f, 0.0f, 0.0f, -10.0f), AnimTransKey(50.0f, 0.0f, 0.0f, 10.0f), "trans1");
    TestUtils::createTestAnimTranslate(trOut2.pAnimTrans,
                                       AnimTransKey(-50.0f, 0.0f, 0.0f, -10.0f), AnimTransKey(50.0f, 0.0f, 0.0f, 10.0f), "trans2");
    ASSERT_TRUE(mainOut.exportToFile(path));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ASSERT_TRUE(mainIn.importFromFile(path));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    Transform * trIn1 = nullptr;
    Transform * trIn2 = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(lodIn->transform(), 0, trIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractTransform(*trIn1, 0, trIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*trIn1, 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(*trIn2, 0, meshIn2));

    //-------------------
    // check results

    Transform animResult1;
    Transform animResult2;
    TestUtils::createTestAnimRotate(animResult1.pAnimRotate, Point3(0.0f, -1.0f, 0.0f), "rot1");
    TestUtils::createTestAnimTranslate(animResult1.pAnimTrans,
                                       AnimTransKey(0.0f, 100.0f, -50.0f, -10.0f), AnimTransKey(0.0f, 0.0f, -50.0f, 10.0f), "trans1");
    TestUtils::createTestAnimTranslate(animResult2.pAnimTrans,
                                       AnimTransKey(-50.0f, -100.0f, 100.0f, -10.0f), AnimTransKey(50.0f, -100.0f, 100.0f, 10.0f), "trans2");
    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", mainOut.pMatrix.toRotation()));

    ASSERT_TRUE(trIn1->pMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(trIn1->pAnimRotate == animResult1.pAnimRotate);
    ASSERT_TRUE(trIn1->pAnimTrans == animResult1.pAnimTrans);
    ASSERT_TRUE(trIn2->pMatrix.position() == Point3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(trIn2->pAnimRotate == animResult2.pAnimRotate);
    ASSERT_TRUE(trIn2->pAnimTrans == animResult2.pAnimTrans);
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
