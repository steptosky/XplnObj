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

#include "gtest/gtest.h"
#include <xpln/obj/ObjMain.h>
#include <xpln/obj/ObjMesh.h>
#include "../TestUtilsObjMesh.h"
#include "../totext.h"
#include <memory>
#include "../TestUtils.h"

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/* 
 * Tests animation availability 
 */
TEST(TestTransformCommon, anim_enabled) {
	ObjMain main;
	ObjLodGroup & lod = main.addLod();

	ASSERT_FALSE(lod.transform().hasAnimTrans());
	ASSERT_FALSE(lod.transform().hasAnim());
	ASSERT_FALSE(lod.transform().hasAnimRotate());
	ASSERT_FALSE(lod.transform().hasAnimVis());

	//--------------------
	// translate

	lod.transform().pAnimTrans.emplace_back();
	AnimTrans & animTrans = lod.transform().pAnimTrans.back();
	animTrans.pKeys.emplace_back(AnimTrans::Key(Point3(1.0f, 2.0f, 3.0f), 1.0f));
	animTrans.pKeys.emplace_back(AnimTrans::Key(Point3(10.0f, 20.0f, 30.0f), 5.0f));

	ASSERT_TRUE(lod.transform().hasAnimTrans());
	ASSERT_TRUE(lod.transform().hasAnim());
	ASSERT_FALSE(lod.transform().hasAnimRotate());
	ASSERT_FALSE(lod.transform().hasAnimVis());

	//--------------------
	// rotation

	lod.transform().pAnimRotate.emplace_back();
	AnimRotate & animRotate = lod.transform().pAnimRotate.back();
	animRotate.pKeys.emplace_back(AnimRotate::Key(20.0f, 1.0f));
	animRotate.pKeys.emplace_back(AnimRotate::Key(30.0f, 5.0f));

	ASSERT_TRUE(lod.transform().hasAnimTrans());
	ASSERT_TRUE(lod.transform().hasAnim());
	ASSERT_TRUE(lod.transform().hasAnimRotate());
	ASSERT_FALSE(lod.transform().hasAnimVis());

	//--------------------
	// visibility

	AnimVisibility & animVis = lod.transform().pAnimVis;
	animVis.pKeys.emplace_back(AnimVisibility::Key(AnimVisibility::Key::HIDE, 1.0f, 2.0f, "drf"));
	animVis.pKeys.emplace_back(AnimVisibility::Key(AnimVisibility::Key::HIDE, 3.0f, 4.0f, "drf"));

	ASSERT_TRUE(lod.transform().hasAnimTrans());
	ASSERT_TRUE(lod.transform().hasAnim());
	ASSERT_TRUE(lod.transform().hasAnimRotate());
	ASSERT_TRUE(lod.transform().hasAnimVis());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
 * Root <- obj1
 * Actually it tests applying root transform for static mesh object.
 */
TEST(TestTransformCommon, apliing_root_transformation) {
	//-------------------
	// make out data and save to file

	ObjMain mainOut;
	TestUtils::setTestExportOptions(mainOut);
	ObjLodGroup & lodOut = mainOut.addLod();
	ObjMesh * meshOut1 = TestUtilsObjMesh::createPyramidTestMesh("mesh");
	Transform & transformOut1 = lodOut.transform().createChild();
	transformOut1.addObject(meshOut1);
	transformOut1.pMatrix.setPosition(Point3(10.0f));
	transformOut1.pMatrix.setRotate(Quaternion(0.5f, 0.5f, 0.5f, 0.5f));

	ASSERT_TRUE(mainOut.exportToFile(std::string(TOTEXT(apliing_root_transformation)).append(".obj").c_str()));

	//-------------------
	// load data from file

	ObjMain mainIn;
	ASSERT_TRUE(mainIn.importFromFile(std::string(TOTEXT(apliing_root_transformation)).append(".obj").c_str()));

	ObjLodGroup * lodIn = nullptr;
	ObjMesh * meshIn1 = nullptr;
	// One transform was optimized during export, it became lod's transform
	ASSERT_NO_FATAL_FAILURE(TestUtils::extractLod(mainIn, 0, lodIn));
	ASSERT_NO_FATAL_FAILURE(TestUtils::extractMesh(lodIn->transform(), 0, meshIn1));

	//-------------------
	// check results

	std::unique_ptr<ObjMesh> meshTarget1(TestUtilsObjMesh::createPyramidTestMesh("mesh"));
	meshTarget1->applyTransform(transformOut1.pMatrix, false);
	ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshData(meshIn1, meshTarget1.get()));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
