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

#include "sts/string/StringUtils.h"
#include "ObjReaderInterpreter.h"
#include "xpln/obj/ObjMain.h"
#include "exceptions/defines.h"
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/obj/manipulators/embeddable/AttrManipWheel.h"
#include "common/AttributeNames.h"
#include "io/ObjTransformation.h"
#include "xpln/obj/manipulators/AttrManipDragRotate.h"
#include "xpln/obj/manipulators/AttrManipAxisKnob.h"
#include "xpln/obj/manipulators/AttrManipAxisSwitchLeftRight.h"
#include "xpln/obj/manipulators/AttrManipAxisSwitchUpDown.h"
#include "xpln/obj/manipulators/AttrManipDelta.h"
#include "xpln/obj/manipulators/AttrManipDragAxisPix.h"
#include "xpln/obj/manipulators/AttrManipPush.h"
#include "xpln/obj/manipulators/AttrManipRadio.h"
#include "xpln/obj/manipulators/AttrManipToggle.h"
#include "xpln/obj/manipulators/AttrManipWrap.h"

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
        mObjMain->pAttr.mTexture = val;
        ++mIOStatistic->pGlobAttrCount;
    }
    else {
        ULWarning << "Texture is not specified.";
    }
}

void ObjReaderInterpreter::gotGlobAttrTextureLit(const std::string & val) {
    mObjMain->pAttr.mTextureLit = val;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrTextureNormal(const std::string & val) {
    mObjMain->pAttr.mTextureNormal = val;
    ++mIOStatistic->pGlobAttrCount;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotGlobAttrWetDry(const AttrWetDry & globAttr) {
    mObjMain->pAttr.mAttrWetDry = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrTint(const AttrTint & globAttr) {
    mObjMain->pAttr.mTint = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrTilted() {
    mObjMain->pAttr.mTilted = true;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrBlend(const AttrBlend & globAttr) {
    mObjMain->pAttr.mBlend = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrSpecular(const AttrSpecular & globAttr) {
    mObjMain->pAttr.mSpecular = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrNoShadow() {
    mObjMain->pAttr.mDropShadow = true;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrDrapedLod(const AttrDrapedLod & globAttr) {
    mObjMain->pDraped.pAttr.mLod = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrCockpitLit() {
    mObjMain->pAttr.mCockpitLit = true;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrNormalMetalness() {
    mObjMain->pAttr.mNormalMetalness = true;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrBlendGlass() {
    mObjMain->pAttr.mBlendClass = true;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrLayerGroup(const AttrLayerGroup & globAttr) {
    mObjMain->pAttr.mLayerGroup = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrSlopeLimit(const AttrSlopeLimit & globAttr) {
    mObjMain->pAttr.mAttrSlopeLimit = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrCockpitRegion(const AttrCockpitRegion & globAttr) {
    if (!mObjMain->pAttr.mAttrCockpitRegion1) {
        mObjMain->pAttr.mAttrCockpitRegion1 = globAttr;
        ++mIOStatistic->pGlobAttrCount;
    }
    else if (!mObjMain->pAttr.mAttrCockpitRegion2) {
        mObjMain->pAttr.mAttrCockpitRegion2 = globAttr;
        ++mIOStatistic->pGlobAttrCount;
    }
    else if (!mObjMain->pAttr.mAttrCockpitRegion3) {
        mObjMain->pAttr.mAttrCockpitRegion3 = globAttr;
        ++mIOStatistic->pGlobAttrCount;
    }
    else if (!mObjMain->pAttr.mAttrCockpitRegion4) {
        mObjMain->pAttr.mAttrCockpitRegion4 = globAttr;
        ++mIOStatistic->pGlobAttrCount;
    }
    else {
        ULError << "Too many cockpit regions, must be 4 per file.";
    }
}

void ObjReaderInterpreter::gotGlobAttrSlungLoadWeight(const AttrSlungLoadWeight & globAttr) {
    mObjMain->pAttr.mSlungLoadWeight = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrLayerGroupDraped(const AttrDrapedLayerGroup & globAttr) {
    mObjMain->pDraped.pAttr.mLayerGroup = globAttr;
    ++mIOStatistic->pGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrDebug() {
    mObjMain->pExportOptions.enable(XOBJ_EXP_DEBUG);
    mObjMain->pAttr.mDebug = true;
    ++mIOStatistic->pGlobAttrCount;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotLod(const float near, const float far, const std::string & endLineComment) {
    ObjLodGroup & l = mObjMain->addLod(new ObjLodGroup(near, far));
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
    mCurrentAttrSet.mAttrHard = attr;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrReset() {
    mCurrentAttrSet.mAttrShiny = AttrShiny();
    // TODO Reset other light attributes like emission specular etc...
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrBlend(const AttrBlend & attr) {
    mCurrentAttrSet.mAttrBlend = attr;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrShadow(const bool state) {
    mCurrentAttrSet.mIsCastShadow = state;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrDraped(const bool state) {
    mCurrentAttrSet.mIsDraped = state;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrCockpit(const AttrCockpit & attr) {
    mCurrentAttrSet.mAttrCockpit = attr;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrPolyOffset(const AttrPolyOffset & attr) {
    mCurrentAttrSet.mAttrPolyOffset = attr;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrShiny(const AttrShiny & attr) {
    mCurrentAttrSet.mAttrShiny = attr;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrLightLevel(const AttrLightLevel & attr) {
    mCurrentAttrSet.mAttrLightLevel = attr;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrDrawEnable(const bool state) {
    mCurrentAttrSet.mIsDraw = state;
    ++mIOStatistic->pTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrSolidCamera(const bool state) {
    mCurrentAttrSet.mIsSolidForCamera = state;
    ++mIOStatistic->pTrisAttrCount;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotTrisAttrManipNo() {
    mCurrentAttrSet.mManipContainer = std::nullopt;
}

void ObjReaderInterpreter::gotTrisAttrManipAxisDetented(const AttrAxisDetented & manip) {
    const auto & currManip = mCurrentAttrSet.mManipContainer;
    if (!currManip || !currManip->hasManip()) {
        ULError << ATTR_MANIP_AXIS_DETENTED << " is specified without main manipulator";
    }
    //--------------------------
    if (currManip->mManip->type() != EManipulator::drag_axis) {
        ULError << "Manipulator <" << currManip->mManip->type().toString() << "> doesn't support axis detented";
        return;
    }

    auto * clonedManip = currManip->mManip->clone();
    auto * castedClonedManip = dynamic_cast<AttrManipDragAxis *>(clonedManip);
    assert(castedClonedManip);
    if (castedClonedManip->axisDetented().isEnabled()) {
        LWarning << "Rewriting existing and enabled sub-manipulator";
    }
    castedClonedManip->setAxisDetented(manip);
    mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
}

void ObjReaderInterpreter::gotTrisAttrManipAxisDetentRange(const AttrAxisDetentRange & manip) {
    const auto & currManip = mCurrentAttrSet.mManipContainer;
    if (!currManip || !currManip->hasManip()) {
        ULError << ATTR_MANIP_AXIS_DETENT_RANGE << " is specified without main manipulator";
    }
    //--------------------------
    if (currManip->mManip->type() == EManipulator::drag_axis) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipDragAxis *>(clonedManip);
        assert(castedClonedManip);
        if (!castedClonedManip->axisDetented().isEnabled()) {
            ULWarning << ATTR_MANIP_AXIS_DETENT_RANGE << " is used when " << ATTR_MANIP_AXIS_DETENTED << " isn't enabled";
        }
        castedClonedManip->detentRanges().emplace_back(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::drag_rotate) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipDragRotate *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->detentRanges().emplace_back(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else {
        ULError << "Manipulator <" << currManip->mManip->type().toString() << "> doesn't support axis detent range";
    }
}

void ObjReaderInterpreter::gotTrisAttrManipKeyFrame(const AttrManipKeyFrame & manip) {
    const auto & currManip = mCurrentAttrSet.mManipContainer;
    if (!currManip || !currManip->hasManip()) {
        ULError << ATTR_MANIP_AXIS_DETENT_RANGE << " is specified without main manipulator";
    }
    //--------------------------
    if (currManip->mManip->type() == EManipulator::drag_rotate) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipDragRotate *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->keys().emplace_back(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else {
        ULError << "Manipulator <" << currManip->mManip->type().toString() << "> doesn't support key frame";
    }
}

void ObjReaderInterpreter::gotTrisAttrManipWheel(const AttrManipWheel & manip) {
    const auto & currManip = mCurrentAttrSet.mManipContainer;
    if (!currManip || !currManip->hasManip()) {
        ULError << ATTR_MANIP_WHEEL << " is specified without main manipulator";
    }
    //--------------------------
    if (currManip->mManip->type() == EManipulator::axis_knob) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipAxisKnob *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::axis_switch_lr) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipAxisSwitchLeftRight *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::axis_switch_ud) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipAxisSwitchUpDown *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::delta) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipDelta *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::drag_axis) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipDragAxis *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::drag_axis_pix) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipDragAxisPix *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::push) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipPush *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::radio) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipRadio *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::toggle) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipToggle *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else if (currManip->mManip->type() == EManipulator::wrap) {
        auto * clonedManip = currManip->mManip->clone();
        auto * castedClonedManip = dynamic_cast<AttrManipWrap *>(clonedManip);
        assert(castedClonedManip);
        castedClonedManip->setWheel(manip);
        mCurrentAttrSet.mManipContainer->setManip(castedClonedManip);
    }
    else {
        ULError << "Manipulator <" << currManip->mManip->type().toString() << "> doesn't support mouse wheel";
    }
}

void ObjReaderInterpreter::gotTrisAttrManip(const AttrManipBase & manip) {
    if (mCurrentAttrSet.mManipContainer) {
        if (mCurrentAttrSet.mManipContainer->mManip && mCurrentAttrSet.mManipContainer->mManip->equals(&manip)) {
            return;
        }
    }
    // TODO Incorrect counting because AttrManipWheel is used as part of the manipulators.
    // So equals does not work as expected for this logic.
    // I don't have a good solution yet.
    ++mIOStatistic->pTrisManipCount;
    mCurrentAttrSet.mManipContainer = ManipContainer(manip.clone());
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotTris(const Index offset, const Index count, const std::string & endLineComment) {
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

    auto * mesh = new ObjMesh;
    mesh->pFaces.swap(flist);
    mesh->pVertices.swap(vlist);
    mesh->setObjectName(extractComment(endLineComment, mesh->objectName().c_str()));
    mesh->pAttr = mCurrentAttrSet;

    //--------------------------

    if (!mesh->pAttr.mIsDraped) {
        mCurrentTransform->addObject(mesh);
    }
    else {
        mesh->applyTransform(mCurrentTransform->pMatrix);
        mObjMain->pDraped.transform().addObject(mesh);
    }
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
    mCurrentTransform = &mCurrentTransform->newChild();
}

void ObjReaderInterpreter::gotAnimEnd() {
    checkForCreateLod();
    if (!mCurrentTransform) {
        LError << "Internal error, current transform is nullptr";
        return;
    }
    if (mCurrentTransform->isRoot()) {
        LError << "inconsistent animation begin/end count";
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
                                            const std::optional<float> loopVal) {
    checkForCreateLod();
    if (mCurrentTransform) {
        mCurrentTransform->pAnimTrans.emplace_back();
        AnimTrans & anim = mCurrentTransform->pAnimTrans.back();
        anim.pKeys.swap(key);
        anim.pDrf = dataref;
        anim.pLoopValue = loopVal;
    }
}

void ObjReaderInterpreter::gotRotateAnim(AnimRotate::KeyList & key, float ( & inVector)[3], std::string & dataref,
                                         const std::optional<float> loopVal) {
    checkForCreateLod();
    if (mCurrentTransform) {
        mCurrentTransform->pAnimRotate.emplace_back();
        AnimRotate & anim = mCurrentTransform->pAnimRotate.back();
        anim.pKeys.swap(key);
        anim.pDrf = dataref;
        anim.pVector.set(inVector[0], inVector[1], inVector[2]);
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
