#pragma once

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

    ObjReaderInterpreter(ObjMain * objMain, const TMatrix & rootMatrix, IOStatistic * ioStatistic);
    ~ObjReaderInterpreter();

protected:

    //-----------------------------------------------------

    void gotGlobAttrTexture(const std::string & val) override;
    void gotGlobAttrTextureLit(const std::string & val) override;
    void gotGlobAttrTextureNormal(const std::string & val) override;

    //-----------------------------------------------------

    void gotGlobAttrTint(const AttrTint & globAttr) override;
    void gotGlobAttrWetDry(const AttrWetDry & globAttr) override;
    void gotGlobAttrBlend(const AttrBlend & globAttr) override;
    void gotGlobAttrSpecular(const AttrSpecular & globAttr) override;
    void gotGlobAttrDrapedLod(const AttrDrapedLod & globAttr) override;
    void gotGlobAttrLayerGroup(const AttrLayerGroup & globAttr) override;
    void gotGlobAttrSlopeLimit(const AttrSlopeLimit & globAttr) override;
    void gotGlobAttrSlungLoadWeight(const AttrSlungLoadWeight & globAttr) override;
    void gotGlobAttrLayerGroupDraped(const AttrDrapedLayerGroup & globAttr) override;
    void gotGlobAttrCockpitRegion(const AttrCockpitRegion & globAttr) override;
    void gotGlobAttrDebug() override;
    void gotGlobAttrTilted() override;
    void gotGlobAttrNoShadow() override;
    void gotGlobAttrCockpitLit() override;
    void gotGlobAttrNormalMetalness() override;
    void gotGlobAttrBlendGlass() override;

    //-----------------------------------------------------

    void gotLod(float near, float far, const std::string & endLineComment) override;

    //-----------------------------------------------------

    void gotMeshVertices(const ObjMesh::VertexList & vertices) override;
    void gotMeshFaces(const FaceIndexArray & indices) override;

    //-----------------------------------------------------

    void gotTrisAttrHard(const AttrHard & attr) override;
    void gotTrisAttrShiny(const AttrShiny & attr) override;
    void gotTrisAttrBlend(const AttrBlend & attr) override;
    void gotTrisAttrPolyOffset(const AttrPolyOffset & attr) override;
    void gotTrisAttrLightLevel(const AttrLightLevel & attr) override;
    void gotTrisAttrCockpit(const AttrCockpit & attr) override;
    void gotTrisAttrShadow(bool state) override;
    void gotTrisAttrDraped(bool state) override;
    void gotTrisAttrDrawEnable(bool state) override;
    void gotTrisAttrSolidCamera(bool state) override;
    void gotTrisAttrReset() override;

    //-----------------------------------------------------

    void gotTrisAttrManipNo() override;
    void gotTrisAttrManipAxisDetented(const AttrAxisDetented & manip) override;
    void gotTrisAttrManipAxisDetentRange(const AttrAxisDetentRange & manip) override;
    void gotTrisAttrManipKeyFrame(const AttrManipKeyFrame & manip) override;
    void gotTrisAttrManipWheel(const AttrManipWheel & manip) override;
    void gotTrisAttrManip(const AttrManipBase & manip) override;

    //-----------------------------------------------------

    void gotTris(Index offset, Index count, const std::string & endLineComment) override /* exception */;

    //-----------------------------------------------------

    void gotAnimBegin() override;
    void gotAnimEnd() override;
    void gotAnimHide(const AnimVisibility::Key & key) override;
    void gotAnimShow(const AnimVisibility::Key & key) override;
    void gotTranslateAnim(AnimTrans::KeyList & key, std::string & dataref,
                          bool hasLoop, float loopVal) override;
    void gotRotateAnim(AnimRotate::KeyList & key, float ( & inVector)[3], std::string & dataref,
                       bool hasLoop, float loopVal) override;

    //-----------------------------------------------------

    void gotFinished() override;

    //-----------------------------------------------------

    void reset() override;

private:

    void checkForCreateLod();
    static std::string extractComment(const std::string & str, const char * dataref);

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
