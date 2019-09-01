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
        mObjMain->mAttr.mTexture = val;
        ++mIOStatistic->mGlobAttrCount;
    }
    else {
        XULWarning << "Texture is not specified.";
    }
}

void ObjReaderInterpreter::gotGlobAttrTextureLit(const std::string & val) {
    mObjMain->mAttr.mTextureLit = val;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrTextureNormal(const std::string & val) {
    mObjMain->mAttr.mTextureNormal = val;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrParticleSystemPath(const std::string & val) {
    mObjMain->mAttr.mParticleSystemPath = val;
    ++mIOStatistic->mGlobAttrCount;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotGlobAttrWetDry(const AttrWetDry & globAttr) {
    mObjMain->mAttr.mWetDry = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrTint(const AttrTint & globAttr) {
    mObjMain->mAttr.mTint = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrTilted() {
    mObjMain->mAttr.mTilted = true;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrBlend(const AttrBlend & globAttr) {
    mObjMain->mAttr.mBlend = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrSpecular(const AttrSpecular & globAttr) {
    mObjMain->mAttr.mSpecular = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrNoShadow() {
    mObjMain->mAttr.mDropShadow = true;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrDrapedLod(const AttrDrapedLod & globAttr) {
    mObjMain->mDraped.mAttr.mLod = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrCockpitLit() {
    mObjMain->mAttr.mCockpitLit = true;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrNormalMetalness() {
    mObjMain->mAttr.mNormalMetalness = true;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrBlendGlass() {
    mObjMain->mAttr.mBlendClass = true;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrLayerGroup(const AttrLayerGroup & globAttr) {
    mObjMain->mAttr.mLayerGroup = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrSlopeLimit(const AttrSlopeLimit & globAttr) {
    mObjMain->mAttr.mSlopeLimit = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrCockpitRegion(const AttrCockpitRegion & globAttr) {
    if (!mObjMain->mAttr.mCockpitRegion1) {
        mObjMain->mAttr.mCockpitRegion1 = globAttr;
        ++mIOStatistic->mGlobAttrCount;
    }
    else if (!mObjMain->mAttr.mCockpitRegion2) {
        mObjMain->mAttr.mCockpitRegion2 = globAttr;
        ++mIOStatistic->mGlobAttrCount;
    }
    else if (!mObjMain->mAttr.mCockpitRegion3) {
        mObjMain->mAttr.mCockpitRegion3 = globAttr;
        ++mIOStatistic->mGlobAttrCount;
    }
    else if (!mObjMain->mAttr.mCockpitRegion4) {
        mObjMain->mAttr.mCockpitRegion4 = globAttr;
        ++mIOStatistic->mGlobAttrCount;
    }
    else {
        XULError << "Too many cockpit regions, must be 4 per file.";
    }
}

void ObjReaderInterpreter::gotGlobAttrSlungLoadWeight(const AttrSlungLoadWeight & globAttr) {
    mObjMain->mAttr.mSlungLoadWeight = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrLayerGroupDraped(const AttrDrapedLayerGroup & globAttr) {
    mObjMain->mDraped.mAttr.mLayerGroup = globAttr;
    ++mIOStatistic->mGlobAttrCount;
}

void ObjReaderInterpreter::gotGlobAttrDebug() {
    mObjMain->mExportOptions.enable(XOBJ_EXP_DEBUG);
    mObjMain->mAttr.mDebug = true;
    ++mIOStatistic->mGlobAttrCount;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotLod(const float near, const float far, const std::string & endLineComment) {
    ObjLodGroup & l = mObjMain->addLod(new ObjLodGroup(near, far));
    l.setObjectName(String(extractComment(endLineComment, l.objectName().str().c_str())));
    mCurrentLod = &l;
    mCurrentTransform = &l.transform();
    //mCurrentTransform->mMatrix *= mRootMtx;
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
    mCurrentAttrSet.mHard = attr;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrReset() {
    mCurrentAttrSet.mShiny = AttrShiny();
    // TODO Reset other light attributes like emission specular etc...
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrBlend(const AttrBlend & attr) {
    mCurrentAttrSet.mBlend = attr;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrShadow(const bool state) {
    mCurrentAttrSet.mIsCastShadow = state;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrDraped(const bool state) {
    mCurrentAttrSet.mIsDraped = state;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrCockpit(const AttrCockpit & attr) {
    mCurrentAttrSet.mCockpit = attr;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrPolyOffset(const AttrPolyOffset & attr) {
    mCurrentAttrSet.mPolyOffset = attr;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrShiny(const AttrShiny & attr) {
    mCurrentAttrSet.mShiny = attr;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrLightLevel(const AttrLightLevel & attr) {
    mCurrentAttrSet.mLightLevel = attr;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrDrawEnable(const bool state) {
    mCurrentAttrSet.mIsDraw = state;
    ++mIOStatistic->mTrisAttrCount;
}

void ObjReaderInterpreter::gotTrisAttrSolidCamera(const bool state) {
    mCurrentAttrSet.mIsSolidForCamera = state;
    ++mIOStatistic->mTrisAttrCount;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotTrisAttrManipNo() {
    mCurrentAttrSet.mManip = std::nullopt;
}

void ObjReaderInterpreter::gotTrisAttrManipAxisDetented(const AttrAxisDetented & manip) {
    if (!mCurrentAttrSet.mManip) {
        XULError << ATTR_MANIP_AXIS_DETENTED << " is specified without main manipulator";
    }
    //--------------------------
    const auto visitor = [&](auto && currManip) {
        using T = std::decay_t<decltype(currManip)>;
        if constexpr (std::is_same_v<T, AttrManipDragAxis>) {
            if (currManip.mAxisDetented) {
                XLWarning << "Rewriting existing and enabled sub-manipulator";
            }
            currManip.mAxisDetented = manip;
        }
        else {
            XULError << "Manipulator <" << currManip.mType.toString() << "> doesn't support axis detented";
        }
    };
    //--------------------------
    std::visit(visitor, *mCurrentAttrSet.mManip);
}

void ObjReaderInterpreter::gotTrisAttrManipAxisDetentRange(const AttrAxisDetentRange & manip) {
    if (!mCurrentAttrSet.mManip) {
        XULError << ATTR_MANIP_AXIS_DETENT_RANGE << " is specified without main manipulator";
    }
    //--------------------------
    const auto visitor = [&](auto && currManip) {
        using T = std::decay_t<decltype(currManip)>;
        if constexpr (std::is_same_v<T, AttrManipDragAxis>) {
            if (!currManip.mAxisDetented) {
                XULWarning << ATTR_MANIP_AXIS_DETENT_RANGE << " is used when " << ATTR_MANIP_AXIS_DETENTED << " isn't enabled";
            }
            currManip.mAxisDetentRanges.emplace_back(manip);
        }
        else if constexpr (std::is_same_v<T, AttrManipDragRotate>) {
            currManip.mAxisDetentRanges.emplace_back(manip);
        }
        else {
            XULError << "Manipulator <" << currManip.mType.toString() << "> doesn't support axis detent range";
        }
    };
    //--------------------------
    std::visit(visitor, *mCurrentAttrSet.mManip);
}

void ObjReaderInterpreter::gotTrisAttrManipKeyFrame(const AttrManipKeyFrame & manip) {
    if (!mCurrentAttrSet.mManip) {
        XULError << ATTR_MANIP_AXIS_DETENT_RANGE << " is specified without main manipulator";
    }
    //--------------------------
    const auto visitor = [&](auto && currManip) {
        using T = std::decay_t<decltype(currManip)>;
        if constexpr (std::is_same_v<T, AttrManipDragRotate>) {
            currManip.mKeys.emplace_back(manip);
        }
        else {
            XULError << "Manipulator <" << currManip.mType.toString() << "> doesn't support key frame";
        }
    };
    //--------------------------
    std::visit(visitor, *mCurrentAttrSet.mManip);
}

void ObjReaderInterpreter::gotTrisAttrManipWheel(const AttrManipWheel & manip) {
    if (!mCurrentAttrSet.mManip) {
        XULError << ATTR_MANIP_WHEEL << " is specified without main manipulator";
    }
    //--------------------------
    const auto visitor = [&](auto && currManip) {
        using T = std::decay_t<decltype(currManip)>;
        if constexpr (std::is_same_v<T, AttrManipAxisKnob>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipAxisSwitchLeftRight>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipAxisSwitchUpDown>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipDelta>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipDragAxis>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipDragAxisPix>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipPush>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipRadio>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipToggle>) { currManip.mWheel = manip; }
        else if constexpr (std::is_same_v<T, AttrManipWrap>) { currManip.mWheel = manip; }
        else { XULError << "Manipulator <" << currManip.mType.toString() << "> doesn't support mouse wheel"; }
    };
    //--------------------------
    std::visit(visitor, *mCurrentAttrSet.mManip);
}

void ObjReaderInterpreter::gotTrisAttrManip(const AttrManip & manip) {
    // TODO Incorrect counting because AttrManipWheel is used as part of the manipulators.
    ++mIOStatistic->mTrisManipCount;
    mCurrentAttrSet.mManip = manip;
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

        face.mV0 = mIndices.at(offset + i);
        face.mV1 = mIndices.at(offset + i + 1);
        face.mV2 = mIndices.at(offset + i + 2);

        min = std::min(min, face.mV0);
        min = std::min(min, face.mV1);
        min = std::min(min, face.mV2);

        max = std::max(max, face.mV0);
        max = std::max(max, face.mV1);
        max = std::max(max, face.mV2);
    }

    if (max > mVertices.size() - 1) {
        throw std::runtime_error(ExcTxt("IDX value <").append(std::to_string(max))
                                 .append("> is out of range of the vertex array."));
    }

    //--------------------------

    ObjMesh::VertexList vlist((max - min) + 1);

    // make vertex array and fix vertex id of the faces
    for (auto & face : flist) {
        face.mV0 -= min;
        face.mV1 -= min;
        face.mV2 -= min;
        /* can be optimized, there are identical idx values,
         * so there are the situations when the same vertices are copied more than one time.
         * example:
         * IDX 2 1 0 2 3 1 2 0 3
         */
        vlist.at(face.mV0) = mVertices.at(face.mV0 + min);
        vlist.at(face.mV1) = mVertices.at(face.mV1 + min);
        vlist.at(face.mV2) = mVertices.at(face.mV2 + min);
    }

    //--------------------------

    auto * mesh = new ObjMesh;
    mesh->mFaces.swap(flist);
    mesh->mVertices.swap(vlist);
    mesh->setObjectName(String(extractComment(endLineComment, mesh->objectName().str().c_str())));
    mesh->mAttr = mCurrentAttrSet;

    //--------------------------

    if (!mesh->mAttr.mIsDraped) {
        mCurrentTransform->mObjects.emplace_back(mesh);
    }
    else {
        mesh->applyTransform(mCurrentTransform->mMatrix);
        mObjMain->mDraped.transform().mObjects.emplace_back(mesh);
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjReaderInterpreter::gotAnimBegin() {
    checkForCreateLod();
    if (!mCurrentTransform) {
        XLError << "Internal error, current transform is nullptr";
        return;
    }
    mCurrentTransform = &mCurrentTransform->newChild();
}

void ObjReaderInterpreter::gotAnimEnd() {
    checkForCreateLod();
    if (!mCurrentTransform) {
        XLError << "Internal error, current transform is nullptr";
        return;
    }
    if (mCurrentTransform->isRoot()) {
        XLError << "inconsistent animation begin/end count";
        return;
    }
    mCurrentTransform = static_cast<Transform *>(mCurrentTransform->parent());
}

void ObjReaderInterpreter::gotAnimHide(VisibilityKey && key) {
    checkForCreateLod();
    assert(key.mType == VisibilityKey::HIDE);
    if (mCurrentTransform) {
        mCurrentTransform->mVisibility.mKeys.emplace_back(key);
    }
}

void ObjReaderInterpreter::gotAnimShow(VisibilityKey && key) {
    checkForCreateLod();
    assert(key.mType == VisibilityKey::SHOW);
    if (mCurrentTransform) {
        mCurrentTransform->mVisibility.mKeys.emplace_back(key);
    }
}

void ObjReaderInterpreter::gotTranslateAnim(Translate::KeyList & key, String && dataref,
                                            const std::optional<float> loopVal) {
    checkForCreateLod();
    if (mCurrentTransform) {
        auto & tr = mCurrentTransform->mPosition.mAnimation.emplace_back();
        tr.mKeys.swap(key);
        tr.mDataRef = dataref;
        tr.mLoop = loopVal;
    }
}

void ObjReaderInterpreter::gotRotateAnim(RotationAxis::KeyList & key, float ( & inVector)[3], String && dataref,
                                         const std::optional<float> loopVal) {
    checkForCreateLod();
    if (mCurrentTransform) {
        auto & anim = mCurrentTransform->mRotation.mAnimation;
        auto & axis = anim.mAxes.emplace_back();
        axis.mKeys.swap(key);
        axis.mDataRef = dataref;
        axis.mVector.set(inVector[0], inVector[1], inVector[2]);
        axis.mLoop = loopVal;
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
