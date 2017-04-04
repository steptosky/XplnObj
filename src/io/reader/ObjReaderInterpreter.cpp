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

	std::string ObjReaderInterpreter::extractComment(const std::string & inStr, const char * inDefaultVal) {
		if (!inStr.empty()) {
			std::string name = inStr;
			sts::MbStrUtils::trimLeft(name, "#");
			sts::MbStrUtils::trim(name, " ");
			return name;
		}
		return inDefaultVal ? inDefaultVal : "";
	}

	/*************************************************************************************************/
	///////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/*************************************************************************************************/

	ObjReaderInterpreter::ObjReaderInterpreter(ObjMain * inObjMain, const TMatrix & rootMatrix, IOStatistic * inIOStatistic)
		: mObjMain(inObjMain),
		mIOStatistic(inIOStatistic),
		mCurrentLod(nullptr),
		mCurrentTransform(nullptr),
		mRootMtx(rootMatrix) {

		assert(inObjMain);
		assert(inIOStatistic);
	}

	ObjReaderInterpreter::~ObjReaderInterpreter() {
		ObjReaderInterpreter::reset();
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotGlobAttrTexture(const std::string & inVal) {
		if (!inVal.empty()) {
			mObjMain->pAttr.setTexture(inVal);
			++mIOStatistic->pGlobAttrCount;
		}
		else {
			ULWarning << "Texture is not specified.";
		}
	}

	void ObjReaderInterpreter::gotGlobAttrTextureLit(const std::string & inVal) {
		mObjMain->pAttr.setTextureLit(inVal);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrTextureNormal(const std::string & inVal) {
		mObjMain->pAttr.setTextureNormal(inVal);
		++mIOStatistic->pGlobAttrCount;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotGlobAttrWetDry(const AttrWetDry & inAttr) {
		mObjMain->pAttr.setWetDry(inAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrTint(const AttrTint & inAttr) {
		mObjMain->pAttr.setTint(inAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrTilted() {
		mObjMain->pAttr.setTilted(true);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrBlend(const AttrBlend & inAttr) {
		mObjMain->pAttr.setBlend(inAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrSpecular(const AttrSpecular & inAttr) {
		mObjMain->pAttr.setSpecular(inAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrNoShadow() {
		mObjMain->pAttr.setNoShadow(true);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrLodDraped(const AttrLodDrap & inAttr) {
		mObjMain->pAttr.setLodDrap(inAttr);
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

	void ObjReaderInterpreter::gotGlobAttrLayerGroup(const AttrLayerGroup & inAttr) {
		mObjMain->pAttr.setLayerGroup(inAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrSlopeLimit(const AttrSlopeLimit & inAttr) {
		mObjMain->pAttr.setSlopeLimit(inAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrCockpitRegion(const AttrCockpitRegion & inAttr) {
		if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r1)) {
			mObjMain->pAttr.setCockpitRegion(inAttr, AttrCockpitRegion::r1);
			++mIOStatistic->pGlobAttrCount;
		}
		else if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r2)) {
			mObjMain->pAttr.setCockpitRegion(inAttr, AttrCockpitRegion::r2);
			++mIOStatistic->pGlobAttrCount;
		}
		else if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r3)) {
			mObjMain->pAttr.setCockpitRegion(inAttr, AttrCockpitRegion::r3);
			++mIOStatistic->pGlobAttrCount;
		}
		else if (!mObjMain->pAttr.cockpitRegion(AttrCockpitRegion::r4)) {
			mObjMain->pAttr.setCockpitRegion(inAttr, AttrCockpitRegion::r4);
			++mIOStatistic->pGlobAttrCount;
		}
		else {
			ULError << "Too many cocpit regions, must be 4 per file.";
		}
	}

	void ObjReaderInterpreter::gotGlobAttrSlungLoadWeight(const AttrSlungLoadWeight & inAttr) {
		mObjMain->pAttr.setSlungLoadWeight(inAttr);
		++mIOStatistic->pGlobAttrCount;
	}

	void ObjReaderInterpreter::gotGlobAttrLayerGroupDraped(const AttrDrapedLayerGroup & inAttr) {
		mObjMain->pAttr.setLayerGroupDraped(inAttr);
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

	void ObjReaderInterpreter::gotLod(float inNear, float inFar, const std::string & inEndLineComment) {
		ObjLodGroup & l = mObjMain->addLod();
		l.setNearVal(inNear);
		l.setFarVal(inFar);
		l.setObjectName(extractComment(inEndLineComment, l.objectName().c_str()));
		mCurrentLod = &l;
		mCurrentTransform = &l.transform();
		//mCurrentTransform->pMatrix *= mRootMtx;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotMeshVertices(const ObjMesh::VertexList & inVertices) {
		mVertices = inVertices;
	}

	void ObjReaderInterpreter::gotMeshFaces(const FaceIndexArray & inIndices) {
		mIndices = inIndices;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotTrisAttrHard(const AttrHard & inAttr) {
		mCurrentAttrSet.setHard(inAttr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrReset() {
		mCurrentAttrSet.setShiny(AttrShiny());
		// TODO Reset other light attributes like emission specular etc
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrBlend(const AttrBlend & inAttr) {
		mCurrentAttrSet.setBlend(inAttr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrShadow(bool inState) {
		mCurrentAttrSet.setCastShadow(inState);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrDraped(bool inState) {
		mCurrentAttrSet.setDraped(inState);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrCockpit(const AttrCockpit & inAttr) {
		mCurrentAttrSet.setCockpit(inAttr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrPolyOffset(const AttrPolyOffset & inAttr) {
		mCurrentAttrSet.setPolyOffset(inAttr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrShiny(const AttrShiny & inAttr) {
		mCurrentAttrSet.setShiny(inAttr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrLightLevel(const AttrLightLevel & inAttr) {
		mCurrentAttrSet.setLightLevel(inAttr);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrDrawEnable(bool inState) {
		mCurrentAttrSet.setDraw(inState);
		++mIOStatistic->pTrisAttrCount;
	}

	void ObjReaderInterpreter::gotTrisAttrSolidCamera(bool inState) {
		mCurrentAttrSet.setSolidForCamera(inState);
		++mIOStatistic->pTrisAttrCount;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotTrisAttrManipNo() {
		mCurrentAttrSet.setManipulator(nullptr);
	}

	void ObjReaderInterpreter::gotTrisAttrManipWheel(const AttrManipWheel & inManip) {
		if (mCurrentAttrSet.manipulator() != nullptr) {
			const AttrManipWheel * cm = dynamic_cast<const AttrManipWheel *>(mCurrentAttrSet.manipulator());
			if (!cm) {
				ULError << "Manipulator <" << mCurrentAttrSet.manipulator()->type().toString() << "> does not support mouse wheel";
				return;
			}
			AttrManipBase * mb = mCurrentAttrSet.manipulator()->clone();
			AttrManipWheel * mbcm = dynamic_cast<AttrManipWheel *>(mb);
			assert(mbcm);
			*mbcm = inManip;
			mCurrentAttrSet.setManipulator(mb);
		}
		else {
			ULError << ATTR_MANIP_WHEEL << " is specified without main manipulator";
		}
	}

	void ObjReaderInterpreter::gotTrisAttrManip(const AttrManipBase & inManip) {
		if (mCurrentAttrSet.manipulator() != nullptr) {
			if (inManip.equals(mCurrentAttrSet.manipulator())) {
				return;
			}
		}
		// TODO Incorrect counting because AttrManipWheel is used as part of the manipulators.
		// So equals does not work as expected for this logic.
		// I don't have a good solution yet.
		++mIOStatistic->pTrisManipCount;
		mCurrentAttrSet.setManipulator(inManip.clone());
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjReaderInterpreter::gotTris(Index inOffset, Index inCount, const std::string & inEndLineComment) {
		checkForCreateLod();
		assert(mCurrentTransform);

		if (inOffset + inCount > mIndices.size()) {
			throw std::runtime_error(ExcTxt("Incorrect Tris's paramenetrs."));
		}

		if (inCount == 0) {
			throw std::runtime_error(ExcTxt("The Tris's <count> paramenter is 0."));
		}

		if (inCount % 3) {
			throw std::runtime_error(ExcTxt("The Tris's <count> paramenter is not a multiple of 3."));
		}

		if (inOffset % 3) {
			throw std::runtime_error(ExcTxt("The Tris's <offset> paramenter is not a multiple of 3."));
		}

		//--------------------------

		ObjMesh::FaceList flist(inCount / 3);
		size_t min = std::numeric_limits<size_t>::max();
		size_t max = std::numeric_limits<size_t>::min();

		// indices to faces and min/max vertex id
		for (FaceIndex i = 0, idx = 0; i < inCount; i += 3) {
			ObjMesh::Face & face = flist.at(idx++);

			face.pV0 = mIndices.at(inOffset + i);
			face.pV1 = mIndices.at(inOffset + i + 1);
			face.pV2 = mIndices.at(inOffset + i + 2);

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

		// make vertex arrray and fix vertex id of the faces
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
		mesh->setObjectName(extractComment(inEndLineComment, mesh->objectName().c_str()));
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

	void ObjReaderInterpreter::gotAnimHide(const AnimVisibility::Key & InKey) {
		checkForCreateLod();
		assert(InKey.pType == AnimVisibility::Key::HIDE);
		if (mCurrentTransform) {
			mCurrentTransform->pAnimVis.pKeys.emplace_back(InKey);
		}
	}

	void ObjReaderInterpreter::gotAnimShow(const AnimVisibility::Key & InKey) {
		checkForCreateLod();
		assert(InKey.pType == AnimVisibility::Key::SHOW);
		if (mCurrentTransform) {
			mCurrentTransform->pAnimVis.pKeys.emplace_back(InKey);
		}
	}

	void ObjReaderInterpreter::gotTranslateAnim(AnimTrans::KeyList & inKeys, std::string & inDataref,
												bool hasLoop, float loopVal) {
		checkForCreateLod();
		if (mCurrentTransform) {
			mCurrentTransform->pAnimTrans.emplace_back();
			AnimTrans & anim = mCurrentTransform->pAnimTrans.back();
			anim.pKeys.swap(inKeys);
			anim.pDrf = inDataref;
			anim.pHasLoop = hasLoop;
			anim.pLoopValue = loopVal;
		}
	}

	void ObjReaderInterpreter::gotRotateAnim(AnimRotate::KeyList & inKeys, float ( & inVector)[3], std::string & inDataref,
											bool hasLoop, float loopVal) {
		checkForCreateLod();
		if (mCurrentTransform) {
			mCurrentTransform->pAnimRotate.emplace_back();
			AnimRotate & anim = mCurrentTransform->pAnimRotate.back();
			anim.pKeys.swap(inKeys);
			anim.pDrf = inDataref;
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
