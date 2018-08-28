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

#include "ObjReaderInterpreter.h"
#include <cassert>
#include "xpln/obj/ObjMain.h"
#include <common/Logger.h>
#include <sts/string/StringUtils.h>
#include <exceptions/defines.h>
#include <algorithm>
#include "xpln/obj/manipulators/AttrManipWheel.h"
#include "common/AttributeNames.h"
#include "io/ObjTransformation.h"

namespace xobj {

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	std::string ObjReaderInterpreter::extractComment(const std::string & str, const char * dataref) {
		if (!str.empty()) {
			std::string name = str;
			sts::MbStrUtils::trimLeft(name, "#");
			sts::MbStrUtils::trim(name, " ");
			return name;
		}
		return dataref ? dataref : "";
	}

	/*************************************************************************************************/
	///////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/*************************************************************************************************/

	ObjReaderInterpreter::ObjReaderInterpreter(ObjMain * objMain, const TMatrix & rootMatrix, IOStatistic * ioStatistic)
		: mObjMain(objMain),
		mIOStatistic(ioStatistic),
		mCurrentLod(nullptr),
		mCurrentTransform(nullptr),
		mRootMtx(rootMatrix) {

		assert(objMain);
		assert(ioStatistic);
	}

	ObjReaderInterpreter::~ObjReaderInterpreter() {
		ObjReaderInterpreter::reset();
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotGlobAttrTexture(const std::string & val) {
		if (!val.empty()) {
			mObjMain->pAttr.setTexture(val);
			++mIOStatistic->pGlobAttrCount;
		}
		else {
			ULWarning << "Texture is not specified.";
		}
	}

	void ObjReaderInterpreter::gotGlobAttrTextureLit(const std::string & val) {
		mObjMain->pAttr.setTextureLit(val);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrTextureNormal(const std::string & val) {
		mObjMain->pAttr.setTextureNormal(val);
		++mIOStatistic->pGlobAttrCount;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotGlobAttrWetDry(const AttrWetDry & globAttr) {
		mObjMain->pAttr.setWetDry(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrTint(const AttrTint & globAttr) {
		mObjMain->pAttr.setTint(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrTilted() {
		mObjMain->pAttr.setTilted(true);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrBlend(const AttrBlend & globAttr) {
		mObjMain->pAttr.setBlend(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrSpecular(const AttrSpecular & globAttr) {
		mObjMain->pAttr.setSpecular(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrNoShadow() {
		mObjMain->pAttr.setNoShadow(true);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrLodDraped(const AttrLodDrap & globAttr) {
		mObjMain->pAttr.setLodDrap(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrCockpitLit() {
		mObjMain->pAttr.setCockpitLit(true);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrNormalMetalness() {
		mObjMain->pAttr.setNormalMetalness(true);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrBlendGlass() {
		mObjMain->pAttr.setBlendGlass(true);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrLayerGroup(const AttrLayerGroup & globAttr) {
		mObjMain->pAttr.setLayerGroup(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrSlopeLimit(const AttrSlopeLimit & globAttr) {
		mObjMain->pAttr.setSlopeLimit(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrCockpitRegion(const AttrCockpitRegion & globAttr) {
		if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r1)) {
			mObjMain->pAttr.setCockpitRegion(globAttr, AttrCockpitRegion::r1);
			++mIOStatistic->pGlobAttrCount;
		}
		else if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r2)) {
			mObjMain->pAttr.setCockpitRegion(globAttr, AttrCockpitRegion::r2);
			++mIOStatistic->pGlobAttrCount;
		}
		else if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r3)) {
			mObjMain->pAttr.setCockpitRegion(globAttr, AttrCockpitRegion::r3);
			++mIOStatistic->pGlobAttrCount;
		}
		else if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r4)) {
			mObjMain->pAttr.setCockpitRegion(globAttr, AttrCockpitRegion::r4);
			++mIOStatistic->pGlobAttrCount;
		}
		else {
			ULError << "Too many cockpit regions, must be 4 per file.";
		}
	}

	void ObjReaderInterpreter::gotGlobAttrSlungLoadWeight(const AttrSlungLoadWeight & globAttr) {
		mObjMain->pAttr.setSlungLoadWeight(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrLayerGroupDraped(const AttrDrapedLayerGroup & globAttr) {
		mObjMain->pAttr.setLayerGroupDraped(globAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrDebug() {
		mObjMain->pExportOptions.enable(XOBJ_EXP_DEBUG);
		mObjMain->pAttr.setDebug(true);
		++mIOStatistic->pGlobAttrCount;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotLod(float near, float far, const std::string & endLineComment) {
		ObjLodGroup & l = mObjMain->addLod();
		l.setNearVal(near);
		l.setFarVal(far);
		l.setObjectName(extractComment(endLineComment, l.objectName().c_str()));
		mCurrentLod = &l;
		mCurrentTransform = &l.transform();
		//mCurrentTransform->pMatrix *= mRootMtx;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotMeshVertices(const ObjMesh::VertexList & vertices) {
		mVertices = vertices;
	}

	void ObjReaderInterpreter::gotMeshFaces(const FaceIndexArray & indices) {
		mIndices = indices;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotTrisAttrHard(const AttrHard & attr) {
		mCurrentAttrSet.setHard(attr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrReset() {
		mCurrentAttrSet.setShiny(AttrShiny());
		// TODO Reset other light attributes like emission specular etc...
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrBlend(const AttrBlend & attr) {
		mCurrentAttrSet.setBlend(attr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrShadow(bool state) {
		mCurrentAttrSet.setCastShadow(state);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrDraped(bool state) {
		mCurrentAttrSet.setDraped(state);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrCockpit(const AttrCockpit & attr) {
		mCurrentAttrSet.setCockpit(attr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrPolyOffset(const AttrPolyOffset & attr) {
		mCurrentAttrSet.setPolyOffset(attr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrShiny(const AttrShiny & attr) {
		mCurrentAttrSet.setShiny(attr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrLightLevel(const AttrLightLevel & attr) {
		mCurrentAttrSet.setLightLevel(attr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrDrawEnable(bool state) {
		mCurrentAttrSet.setDraw(state);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrSolidCamera(bool state) {
		mCurrentAttrSet.setSolidForCamera(state);
		++mIOStatistic->pTrisAttrCount;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotTrisAttrManipNo() {
		mCurrentAttrSet.setManipulator(nullptr);
	}

	void ObjReaderInterpreter::gotTrisAttrManipWheel(const AttrManipWheel & manip) {
		if (mCurrentAttrSet.manipulator() != nullptr) {
			const AttrManipWheel * cm = dynamic_cast<const AttrManipWheel *>(mCurrentAttrSet.manipulator());
			if (!cm) {
				ULError << "Manipulator <" << mCurrentAttrSet.manipulator()->type().toString() << "> does not support mouse wheel";
				return;
			}
			AttrManipBase * mb = mCurrentAttrSet.manipulator()->clone();
			AttrManipWheel * mbcm = dynamic_cast<AttrManipWheel *>(mb);
			assert(mbcm);
			*mbcm = manip;
			mCurrentAttrSet.setManipulator(mb);
		}
		else {
			ULError << ATTR_MANIP_WHEEL << " is specified without main manipulator";
		}
	}

	void ObjReaderInterpreter::gotTrisAttrManip(const AttrManipBase & manip) {
		if (mCurrentAttrSet.manipulator() != nullptr) {
			if (manip.equals(mCurrentAttrSet.manipulator())) {
				return;
			}
		}
		// TODO Incorrect counting because AttrManipWheel is used as part of the manipulators.
		// So equals does not work as expected for this logic.
		// I don't have a good solution yet.
		++mIOStatistic->pTrisManipCount;
		mCurrentAttrSet.setManipulator(manip.clone());
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotTris(Index offset, Index count, const std::string & endLineComment) {
		checkForCreateLod();
		assert(mCurrentTransform);

		if (offset + count > mIndices.size()) {
			throw std::runtime_error(ExcTxt("Incorrect Tris's parameters."));
		}

		if (count == 0) {
			throw std::runtime_error(ExcTxt("The Tris's <count> parameter is 0."));
		}

		if (count % 3) {
			throw std::runtime_error(ExcTxt("The Tris's <count> parameter is not a multiple of 3."));
		}

		if (offset % 3) {
			throw std::runtime_error(ExcTxt("The Tris's <offset> parameter is not a multiple of 3."));
		}

		//--------------------------

		ObjMesh::FaceList flist(count / 3);
		size_t min = std::numeric_limits<size_t>::max();
		size_t max = std::numeric_limits<size_t>::min();

		// indices to faces and min/max vertex id
		for (FaceIndex i = 0, idx = 0; i < count; i += 3) {
			ObjMesh::Face & face = flist.at(idx++);

			face.pV0 = mIndices.at(offset + i);
			face.pV1 = mIndices.at(offset + i + 1);
			face.pV2 = mIndices.at(offset + i + 2);

			min = std::min(min, face.pV0);
			min = std::min(min, face.pV1);
			min = std::min(min, face.pV2);

			max = std::max(max, face.pV0);
			max = std::max(max, face.pV1);
			max = std::max(max, face.pV2);
		}

		if (max > mVertices.size() - 1) {
			throw std::runtime_error(ExcTxt("IDX value <").append(std::to_string(max))
														.append("> is out of range of the vertex array."));
		}

		//--------------------------

		ObjMesh::VertexList vlist((max - min) + 1);

		// make vertex array and fix vertex id of the faces
		for (auto & face : flist) {
			face.pV0 -= min;
			face.pV1 -= min;
			face.pV2 -= min;
			/* can be optimized, there are identical idx values, 
			 * so there are the situations when the same vertices are copied more than one time.
			 * example:
			 * IDX 2 1 0 2 3 1 2 0 3
			 */
			vlist.at(face.pV0) = mVertices.at(face.pV0 + min);
			vlist.at(face.pV1) = mVertices.at(face.pV1 + min);
			vlist.at(face.pV2) = mVertices.at(face.pV2 + min);
		}

		//--------------------------

		ObjMesh * mesh = new ObjMesh;
		mesh->pFaces.swap(flist);
		mesh->pVertices.swap(vlist);
		mesh->setObjectName(extractComment(endLineComment, mesh->objectName().c_str()));
		mesh->pAttr = mCurrentAttrSet;

		//--------------------------

		mCurrentTransform->addObject(mesh);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotAnimBegin() {
		checkForCreateLod();
		if (!mCurrentTransform) {
			LError << "Internal error, current transform is nullptr";
			return;
		}
		mCurrentTransform = &mCurrentTransform->createChild();
	}

	void ObjReaderInterpreter::gotAnimEnd() {
		checkForCreateLod();
		if (!mCurrentTransform) {
			LError << "Internal error, current transform is nullptr";
			return;
		}
		if (mCurrentTransform->isRoot()) {
			LError << "inconsistent anim begin/end count";
			return;
		}
		mCurrentTransform = static_cast<Transform *>(mCurrentTransform->parent());
	}

	void ObjReaderInterpreter::gotAnimHide(const AnimVisibility::Key & key) {
		checkForCreateLod();
		assert(key.pType == AnimVisibility::Key::HIDE);
		if (mCurrentTransform) {
			mCurrentTransform->pAnimVis.pKeys.emplace_back(key);
		}
	}

	void ObjReaderInterpreter::gotAnimShow(const AnimVisibility::Key & key) {
		checkForCreateLod();
		assert(key.pType == AnimVisibility::Key::SHOW);
		if (mCurrentTransform) {
			mCurrentTransform->pAnimVis.pKeys.emplace_back(key);
		}
	}

	void ObjReaderInterpreter::gotTranslateAnim(AnimTrans::KeyList & key, std::string & dataref,
												bool hasLoop, float loopVal) {
		checkForCreateLod();
		if (mCurrentTransform) {
			mCurrentTransform->pAnimTrans.emplace_back();
			AnimTrans & anim = mCurrentTransform->pAnimTrans.back();
			anim.pKeys.swap(key);
			anim.pDrf = dataref;
			anim.pHasLoop = hasLoop;
			anim.pLoopValue = loopVal;
		}
	}

	void ObjReaderInterpreter::gotRotateAnim(AnimRotate::KeyList & key, float ( & inVector)[3], std::string & dataref,
											bool hasLoop, float loopVal) {
		checkForCreateLod();
		if (mCurrentTransform) {
			mCurrentTransform->pAnimRotate.emplace_back();
			AnimRotate & anim = mCurrentTransform->pAnimRotate.back();
			anim.pKeys.swap(key);
			anim.pDrf = dataref;
			anim.pVector.set(inVector[0], inVector[1], inVector[2]);
			anim.pHasLoop = hasLoop;
			anim.pLoopValue = loopVal;
		}
	}

	/**************************************************************************************************/
	//////////////////////////////////////////* Functions */////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotFinished() {
		ObjTransformation::correctImportTransform(*mObjMain, mRootMtx);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::reset() {
		mVertices.clear();
		mIndices.clear();
		mCurrentLod = nullptr;
		mCurrentTransform = nullptr;
		mCurrentAttrSet.reset();
	}

	void ObjReaderInterpreter::checkForCreateLod() {
		if (!mCurrentLod) {
			mCurrentLod = &mObjMain->addLod();
			mCurrentTransform = &mCurrentLod->transform();
		}
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
