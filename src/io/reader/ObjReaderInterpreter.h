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

#pragma once

#include "ObjReaderListener.h"
#include "xpln/obj/IOStatistic.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/attributes/AttrSet.h"
#include "xpln/obj/attributes/AttrGlobSet.h"

namespace xobj {

	class ObjMain;

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	class ObjReaderInterpreter : public ObjReaderListener {
	public:

		ObjReaderInterpreter(ObjMain * inObjMain, const TMatrix & rootMatrix, IOStatistic * inIOStatistic);
		~ObjReaderInterpreter();

	protected:

		//-----------------------------------------------------

		void gotGlobAttrTexture(const std::string & inVal) override;
		void gotGlobAttrTextureLit(const std::string & inVal) override;
		void gotGlobAttrTextureNormal(const std::string & inVal) override;

		//-----------------------------------------------------

		void gotGlobAttrTint(const AttrTint & inAttr) override;
		void gotGlobAttrWetDry(const AttrWetDry & inAttr) override;
		void gotGlobAttrBlend(const AttrBlend & inAttr) override;
		void gotGlobAttrSpecular(const AttrSpecular & inAttr) override;
		void gotGlobAttrLodDraped(const AttrLodDrap & inAttr) override;
		void gotGlobAttrLayerGroup(const AttrLayerGroup & inAttr) override;
		void gotGlobAttrSlopeLimit(const AttrSlopeLimit & inAttr) override;
		void gotGlobAttrSlungLoadWeight(const AttrSlungLoadWeight & inAttr) override;
		void gotGlobAttrLayerGroupDraped(const AttrDrapedLayerGroup & inAttr) override;
		void gotGlobAttrCockpitRegion(const AttrCockpitRegion & inAttr) override;
		void gotGlobAttrDebug() override;
		void gotGlobAttrTilted() override;
		void gotGlobAttrNoShadow() override;
		void gotGlobAttrCockpitLit() override;
		void gotGlobAttrNormalMetalness() override;
		void gotGlobAttrBlendGlass() override;

		//-----------------------------------------------------

		void gotLod(float inNear, float inFar, const std::string & inEndLineComment) override;

		//-----------------------------------------------------

		void gotMeshVertices(const ObjMesh::VertexList & inVertices) override;
		void gotMeshFaces(const FaceIndexArray & inIndices) override;

		//-----------------------------------------------------

		void gotTrisAttrHard(const AttrHard & inAttr) override;
		void gotTrisAttrShiny(const AttrShiny & inAttr) override;
		void gotTrisAttrBlend(const AttrBlend & inAttr) override;
		void gotTrisAttrPolyOffset(const AttrPolyOffset & inAttr) override;
		void gotTrisAttrLightLevel(const AttrLightLevel & inAttr) override;
		void gotTrisAttrCockpit(const AttrCockpit & inAttr) override;
		void gotTrisAttrShadow(bool inState) override;
		void gotTrisAttrDraped(bool inState) override;
		void gotTrisAttrDrawEnable(bool inState) override;
		void gotTrisAttrSolidCamera(bool inState) override;
		void gotTrisAttrReset() override;

		//-----------------------------------------------------

		void gotTrisAttrManipNo() override;
		void gotTrisAttrManipWheel(const AttrManipWheel & inManip) override;
		void gotTrisAttrManip(const AttrManipBase & inManip) override;

		//-----------------------------------------------------

		void gotTris(Index inOffset, Index inCount, const std::string & inEndLineComment) override /* exception */;

		//-----------------------------------------------------

		void gotAnimBegin() override;
		void gotAnimEnd() override;
		void gotAnimHide(const AnimVisibility::Key & InKey) override;
		void gotAnimShow(const AnimVisibility::Key & InKey) override;
		void gotTranslateAnim(AnimTrans::KeyList & inKeys, std::string & inDataref,
							bool hasLoop, float loopVal) override;
		void gotRotateAnim(AnimRotate::KeyList & inKeys, float ( & inVector)[3], std::string & inDataref,
							bool hasLoop, float loopVal) override;

		//-----------------------------------------------------

		void gotFinished() override;

		//-----------------------------------------------------

		void reset() override;

	private:

		void checkForCreateLod();
		static std::string extractComment(const std::string & inStr, const char * inDefaultVal);

		ObjMain * mObjMain;
		IOStatistic * mIOStatistic;

		AttrSet mCurrentAttrSet;
		ObjLodGroup * mCurrentLod;
		Transform * mCurrentTransform;

		ObjMesh::VertexList mVertices;
		FaceIndexArray mIndices;

		TMatrix mRootMtx;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
