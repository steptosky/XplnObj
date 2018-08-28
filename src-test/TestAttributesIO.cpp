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
#include "gmock/gmock.h"

#include "common/Logger.h"
#include "xpln/obj/ObjMain.h"
#include "xpln/obj/ObjMesh.h"

#include "TestUtilsObjMesh.h"

using namespace xobj;
using ::testing::_;
using ::testing::StrEq;
using ::testing::InSequence;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/* 
 * This tests are for checking attributes of the chain 'mesh object->file | file->mesh object'.
 * So they test writter and reader for attributes of one mesh object.
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void extractMesh(ObjMain & inMain, ObjMesh *& outAttr) {
	ASSERT_EQ(1, inMain.lodCount());
	const ObjLodGroup & inLGroup = inMain.lod(0);
	ASSERT_EQ(1, inLGroup.transform().objList().size());
	ObjAbstract * obj = *(inLGroup.transform().objList().begin());
	ASSERT_EQ(eObjectType::OBJ_MESH, obj->objType());
	outAttr = static_cast<ObjMesh *>(obj);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestAttributesIO, default_vals) {
	ObjMain outObj;
	IOStatistic stat;

	ObjMesh * outM = TestUtilsObjMesh::createObjMesh("m1", 0.0);
	ObjLodGroup & outLGroup = outObj.addLod();
	outLGroup.transform().addObject(outM);
	ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestAttributesIO), stat));
	ASSERT_EQ(0, stat.pTrisAttrCount);

	//-----------------------------

	ObjMain inObj;
	stat.reset();
	ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestAttributesIO), stat));
	ASSERT_EQ(0, stat.pTrisAttrCount);
	ObjMesh * inM = nullptr;
	ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, inM));

	//-----------------------------

	ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshAttributes(outM, inM));
}

TEST(TestAttributesIO, not_default_vals_case_1) {
	ObjMain outObj;
	IOStatistic stat;

	ObjMesh * outM = TestUtilsObjMesh::createObjMeshNotDefaultAttributes1("m1", 0.0);
	ObjLodGroup & outLGroup = outObj.addLod();
	outLGroup.transform().addObject(outM);
	ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestAttributesIO), stat));
	ASSERT_EQ(10, stat.pTrisAttrCount);

	//-----------------------------

	ObjMain inObj;
	stat.reset();
	ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestAttributesIO), stat));
	ASSERT_EQ(10, stat.pTrisAttrCount);
	ObjMesh * inM = nullptr;
	ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, inM));

	//-----------------------------

	ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshAttributes(outM, inM));
}

TEST(TestAttributesIO, not_default_vals_case_2) {
	ObjMain outObj;
	IOStatistic stat;

	ObjMesh * outM = TestUtilsObjMesh::createObjMeshNotDefaultAttributes2("m1", 0.0);
	ObjLodGroup & outLGroup = outObj.addLod();
	outLGroup.transform().addObject(outM);
	ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestAttributesIO), stat));
	ASSERT_EQ(10, stat.pTrisAttrCount);

	//-----------------------------

	ObjMain inObj;
	stat.reset();
	ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestAttributesIO), stat));
	ASSERT_EQ(10, stat.pTrisAttrCount);
	ObjMesh * inM = nullptr;
	ASSERT_NO_FATAL_FAILURE(extractMesh(inObj, inM));

	//-----------------------------

	ASSERT_NO_FATAL_FAILURE(TestUtilsObjMesh::compareMeshAttributes(outM, inM));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
