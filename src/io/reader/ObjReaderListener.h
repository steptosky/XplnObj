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

#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/Transform.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ObjReader;

class AttrManipCommandAxis;
class AttrManipDelta;
class AttrManipDragAxis;
class AttrManipDragAxisPix;
class AttrManipDragXy;
class AttrManipNoop;
class AttrManipPush;
class AttrManipRadio;
class AttrManipToggle;
class AttrManipWrap;
class AttrManipCommand;
class AttrAxisDetented;
class AttrAxisDetentRange;
class AttrManipKeyFrame;
class AttrManipWheel;

class AttrWetDry;
class AttrTint;
class AttrSpecular;
class AttrLodDrap;
class AttrLayerGroup;
class AttrSlopeLimit;
class AttrBlend;
class AttrSlungLoadWeight;
class AttrDrapedLayerGroup;
class AttrCockpit;
class AttrCockpitRegion;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ObjReaderListener {
protected:

    ObjReaderListener() = default;

public:

    typedef size_t Index;
    typedef Index FaceIndex;
    typedef std::vector<FaceIndex> FaceIndexArray;

    virtual ~ObjReaderListener() = default;

    //-----------------------------------------------------
    // Global attributes

    virtual void gotGlobAttrTexture(const std::string & val) = 0;
    virtual void gotGlobAttrTextureLit(const std::string & val) = 0;
    virtual void gotGlobAttrTextureNormal(const std::string & val) = 0;

    //-----------------------------------------------------
    // Global attributes

    virtual void gotGlobAttrTint(const AttrTint & globAttr) = 0;
    virtual void gotGlobAttrWetDry(const AttrWetDry & globAttr) = 0;
    virtual void gotGlobAttrBlend(const AttrBlend & globAttr) = 0;
    virtual void gotGlobAttrSpecular(const AttrSpecular & globAttr) = 0;
    virtual void gotGlobAttrLodDraped(const AttrLodDrap & globAttr) = 0;
    virtual void gotGlobAttrLayerGroup(const AttrLayerGroup & globAttr) = 0;
    virtual void gotGlobAttrSlopeLimit(const AttrSlopeLimit & globAttr) = 0;
    virtual void gotGlobAttrSlungLoadWeight(const AttrSlungLoadWeight & globAttr) = 0;
    virtual void gotGlobAttrLayerGroupDraped(const AttrDrapedLayerGroup & globAttr) = 0;
    virtual void gotGlobAttrCockpitRegion(const AttrCockpitRegion & globAttr) = 0;
    virtual void gotGlobAttrDebug() = 0;
    virtual void gotGlobAttrTilted() = 0;
    virtual void gotGlobAttrNoShadow() = 0;
    virtual void gotGlobAttrCockpitLit() = 0;
    virtual void gotGlobAttrNormalMetalness() = 0;
    virtual void gotGlobAttrBlendGlass() = 0;

    //-----------------------------------------------------
    // Lods

    virtual void gotLod(float near, float far, const std::string & endLineComment) = 0;

    //-----------------------------------------------------
    // Global Objects' data

    virtual void gotMeshVertices(const ObjMesh::VertexList & vertices) = 0;
    virtual void gotMeshFaces(const FaceIndexArray & indices) = 0;

    //-----------------------------------------------------
    // Objects' data

    virtual void gotTrisAttrHard(const AttrHard & attr) = 0;
    virtual void gotTrisAttrShiny(const AttrShiny & attr) = 0;
    virtual void gotTrisAttrBlend(const AttrBlend & attr) = 0;
    virtual void gotTrisAttrPolyOffset(const AttrPolyOffset & attr) = 0;
    virtual void gotTrisAttrLightLevel(const AttrLightLevel & attr) = 0;
    virtual void gotTrisAttrCockpit(const AttrCockpit & attr) = 0;
    virtual void gotTrisAttrShadow(bool state) = 0;
    virtual void gotTrisAttrDraped(bool state) = 0;
    virtual void gotTrisAttrDrawEnable(bool state) = 0;
    virtual void gotTrisAttrSolidCamera(bool state) = 0;
    virtual void gotTrisAttrReset() = 0;

    //-----------------------------------------------------
    // Objects' manipulators

    virtual void gotTrisAttrManipNo() = 0;
    virtual void gotTrisAttrManipAxisDetented(const AttrAxisDetented & manip) = 0;
    virtual void gotTrisAttrManipAxisDetentRange(const AttrAxisDetentRange & manip) = 0;
    virtual void gotTrisAttrManipKeyFrame(const AttrManipKeyFrame & manip) = 0;
    virtual void gotTrisAttrManipWheel(const AttrManipWheel & manip) = 0;
    virtual void gotTrisAttrManip(const AttrManipBase & manip) = 0;

    //-----------------------------------------------------
    // Objects

    virtual void gotTris(Index offset, Index count, const std::string & endLineComment) = 0;

    //-----------------------------------------------------
    // Animation data

    virtual void gotAnimBegin() = 0;
    virtual void gotAnimEnd() = 0;

    virtual void gotAnimHide(const AnimVisibility::Key & key) = 0;
    virtual void gotAnimShow(const AnimVisibility::Key & key) = 0;
    virtual void gotTranslateAnim(AnimTrans::KeyList & key, std::string & dataref,
                                  bool hasLoop, float loopVal) = 0;
    virtual void gotRotateAnim(AnimRotate::KeyList & keys, float (&inVector)[3], std::string & dataref,
                               bool hasLoop, float loopVal) = 0;

    //-----------------------------------------------------

    virtual void gotFinished() = 0;

    //-----------------------------------------------------

    virtual void reset() = 0;

    //-----------------------------------------------------
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
