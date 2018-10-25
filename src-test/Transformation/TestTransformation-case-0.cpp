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

/* SET 0 */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- obj1 <- obj2 <- obj3
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
 *  |                 /  |  \                      |
 *  |                /   |   \                     |
 *  |               /----|----\                    |
 *  |                    |                         |
 *  |         +-         |         -+              |
 *  |       +  |         |         |  +            |
 *  |     +    |         |         |    +     +X   |
 *  |   <      |         +---------|------>---->   |
 *  |     +    |                   |    +          |
 *  |       +  |                   |  +            |
 *  |         +-                   -+              |
 *  |                                              |
 *  +==============================================+
 *
 */
TEST(TestTransform_case0, case1) {
    const auto fileName = XOBJ_PATH("TestTransform_case0-case1.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));
    Transform & transformOut3 = transformOut2.newChild(TOTEXT(transformOut3));

    transformOut1.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));
    transformOut3.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 3"));

    transformOut1.pMatrix.rotateDegreesY(+90.0f);
    transformOut2.pMatrix.rotateDegreesY(0.0f);
    transformOut3.pMatrix.rotateDegreesY(-90.0f);

    transformOut1.pMatrix.setPosition(Point3(-50.0f, 0.0f, 0.0f));
    transformOut2.pMatrix.setPosition(Point3(0.0f, 0.0f, -50.0f));
    transformOut3.pMatrix.setPosition(Point3(50.0f, 0.0f, 0.0f));

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ObjMesh * meshIn3 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 1, meshIn2));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 2, meshIn3));

    //-------------------
    // check results

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(-50.0f, 0.0f, 0.0f), +90.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(0.0f, 0.0f, -50.0f), 0.0f));
    std::unique_ptr<ObjMesh> meshTarget3(TestUtilsObjMesh::createPyramidTestMesh("mesh 3", Point3(50.0f, 0.0f, 0.0f), -90.0f));

    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn3, meshTarget3.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Root <- obj1 <- obj2 [apply root matrix with Y rotation and translate by X]
 *
 *  +==============================================+
 *  | Result of obj files                          |
 *  +==============================================+
 *  | [TOP]                                        |
 *  |                                              |
 *  |       ^ -Z                                   |
 *  |       |                                      |
 *  |       |                                      |
 *  |       |                                      |
 *  |       |                                      |
 *  |       |                                      |
 *  |       |                                      |
 *  |       |                                      |
 *  |       |                                      |
 *  |       | +-                   -+              |
 *  |       +  |                   |  +            |
 *  |     + |  |                   |    +     +X   |
 *  |   <   +----------------------|------>---->   |
 *  |     +    |                   |    +          |
 *  |       +  |                   |  +            |
 *  |         +-                   -+              |
 *  |                                              |
 *  +==============================================+
 *
 */
TEST(TestTransform_case0, case2) {
    const auto fileName = XOBJ_PATH("TestTransform_case0-case2.obj");
    //-----------------------------
    // make out data and save to file

    ObjMain mainOut;
    TestUtils::setTestExportOptions(mainOut);
    ObjLodGroup & lodOut = mainOut.addLod();

    Transform & transformOut0 = lodOut.transform();
    Transform & transformOut1 = transformOut0.newChild(TOTEXT(transformOut1));
    Transform & transformOut2 = transformOut1.newChild(TOTEXT(transformOut2));

    transformOut1.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 1"));
    transformOut2.addObject(TestUtilsObjMesh::createPyramidTestMesh("mesh 2"));

    mainOut.pMatrix.rotateDegreesY(-90.0f);
    transformOut1.pMatrix.rotateDegreesY(180.0f);
    transformOut2.pMatrix.rotateDegreesY(0.0f);

    mainOut.pMatrix.setPosition(Point3(50.0f, 0.0f, 0.0f));
    transformOut1.pMatrix.setPosition(Point3(0.0f, 0.0f, 50.0f));
    transformOut2.pMatrix.setPosition(Point3(0.0f, 0.0f, -50.0f));

    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));

    //-------------------
    // load data from file

    ObjMain mainIn;
    ImportContext impContext(fileName);
    ASSERT_TRUE(mainIn.importObj(impContext));

    // extract data
    ObjLodGroup * lodIn = nullptr;
    ObjMesh * meshIn1 = nullptr;
    ObjMesh * meshIn2 = nullptr;
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));
    ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 1, meshIn2));

    //-------------------
    // check results

    std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh 1", Point3(00.0f, 0.0f, 0.0f), 90.0f));
    std::unique_ptr<ObjMesh> meshTarget2(TestUtilsObjMesh::createPyramidTestMesh("mesh 2", Point3(100.0f, 0.0f, 0.0f), -90.0f));

    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
    ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn2, meshTarget2.get()));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
