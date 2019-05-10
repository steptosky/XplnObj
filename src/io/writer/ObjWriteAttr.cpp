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

#include <cassert>

#include "ObjWriteAttr.h"

#include "AbstractWriter.h"
#include "common/AttributeNames.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/obj/manipulators/AttrManipDragRotate.h"
#include "xpln/obj/manipulators/AttrManipNone.h"
#include "io/StringValidator.h"
#include "xpln/obj/manipulators/AttrManipPanel.h"
#include "converters/ObjAttrString.h"
#include "common/Logger.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAttr::reset() {
    mState.reset();
    mGlobNum = 0;
    mAttrNum = 0;
    mManipNum = 0;
    mObj = nullptr;
    mWriter = nullptr;
    mIsPanelManip = false;
}

std::tuple<std::size_t, std::size_t, std::size_t> ObjWriteAttr::count() const {
    return std::make_tuple(mGlobNum, mAttrNum, mManipNum);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<typename T>
std::size_t writeGlobAttrT(AbstractWriter * writer, const T & attr) {
    if (attr) {
        printObjGlobAttr(*attr, *writer);
    }
    return attr ? 1 : 0;
}

void ObjWriteAttr::writeGlobAttr(AbstractWriter * writer, const ObjMain * obj) {
    assert(obj);
    assert(writer);
    mWriter = writer;

    const auto writeBool = [&](const char * inAttr, const bool inState) {
        if (inState) {
            mWriter->printLine(inAttr);
            ++mGlobNum;
        }
    };

    const auto writeString = [&](const char * inAttr, const std::optional<std::string> & string) {
        if (string && !string->empty()) {
            if (!StringValidator::hasIllegalSymbols(*string, "\t\n\r")) {
                mWriter->printLine(std::string(inAttr).append(" ").append(*string));
                ++mGlobNum;
            }
        }
    };

    //-------------------------------------------------------------------------

    writeString(ATTR_GLOBAL_TEXTURE, obj->mAttr.mTexture);
    writeString(ATTR_GLOBAL_TEXTURE_LIT, obj->mAttr.mTextureLit);
    writeString(ATTR_GLOBAL_TEXTURE_NORMAL, obj->mAttr.mTextureNormal);
    writeString(ATTR_GLOBAL_PARTICLE_SYSTEM, obj->mAttr.mParticleSystemPath);

    writeBool(ATTR_GLOBAL_BLEND_GLASS, obj->mAttr.mBlendClass);
    writeBool(ATTR_GLOBAL_NORMAL_METALNESS, obj->mAttr.mNormalMetalness);
    writeBool(ATTR_GLOBAL_TILTED, obj->mAttr.mTilted);
    writeBool(ATTR_GLOBAL_NO_SHADOW, obj->mAttr.mDropShadow);
    writeBool(ATTR_GLOBAL_COCKPIT_LIT, obj->mAttr.mCockpitLit);
    // It is printed in another place.
    //writeBool(inWriter, ATTR_GLOBAL_DEBUG, inObj->mAttr.isDebug());

    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mWetDry);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mBlend);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mLayerGroup);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mSlungLoadWeight);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mSpecular);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mTint);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mSlopeLimit);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mCockpitRegion1);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mCockpitRegion2);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mCockpitRegion3);
    mGlobNum += writeGlobAttrT(writer, obj->mAttr.mCockpitRegion4);

    mGlobNum += writeGlobAttrT(writer, obj->mDraped.mAttr.mLayerGroup);
    mGlobNum += writeGlobAttrT(writer, obj->mDraped.mAttr.mLod);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAttr::writeObjAttr(AbstractWriter * writer, const ObjAbstract * obj) {
    assert(writer);
    assert(obj);
    mWriter = writer;
    if (obj->objType() != OBJ_MESH) {
        return;
    }
    mObj = static_cast<const ObjMesh*>(obj);
    writeAttr();
    writeManip();
}

void ObjWriteAttr::writeAttr() {
    const auto writeBool = [&](const char * attr) {
        ++mAttrNum;
        mWriter->printLine(attr);
    };

    const auto & attrs = mObj->mAttr;

    //-------------------------------------------------------------------------

    ObjState::processBool(attrs.mIsDraped, mState.mObject.mIsDraped, [&](const bool enable) {
        writeBool(enable ? ATTR_DRAPED : ATTR_NO_DRAPED);
    });

    ObjState::processBool(attrs.mIsSolidForCamera, mState.mObject.mIsSolidForCamera, [&](const bool enable) {
        writeBool(enable ? ATTR_SOLID_CAMERA : ATTR_NO_SOLID_CAMERA);
    });

    ObjState::processBool(attrs.mIsDraw, mState.mObject.mIsDraw, [&](const bool enable) {
        writeBool(enable ? ATTR_DRAW_ENABLE : ATTR_DRAW_DISABLE);
    });

    ObjState::processBool(attrs.mIsCastShadow, mState.mObject.mIsCastShadow, [&](const bool enable) {
        writeBool(enable ? ATTR_SHADOW : ATTR_NO_SHADOW);
    });

    //-------------------------------------------------------------------------

    ObjState::processAttr(attrs.mHard, mState.mObject.mHard, [&](const bool enable) {
        if (enable) {
            mAttrNum += attrs.mHard->printObj(*mWriter);
        }
        else {
            mWriter->printLine(AttrHard::objDisableStr());
            ++mAttrNum;
        }
    });

    ObjState::processAttr(attrs.mShiny, mState.mObject.mShiny, [&](const bool enable) {
        if (enable) {
            mAttrNum += attrs.mShiny->printObj(*mWriter);
        }
        else {
            mWriter->printLine(AttrShiny::objDisableStr());
            ++mAttrNum;
        }
    });

    ObjState::processAttr(attrs.mBlend, mState.mObject.mBlend, [&](const bool enable) {
        if (enable) {
            mAttrNum += attrs.mBlend->printObj(*mWriter);
        }
        else {
            mWriter->printLine(AttrBlend::objDisableStr());
            ++mAttrNum;
        }
    });

    ObjState::processAttr(attrs.mPolyOffset, mState.mObject.mPolyOffset, [&](const bool enable) {
        if (enable) {
            mAttrNum += attrs.mPolyOffset->printObj(*mWriter);
        }
        else {
            mWriter->printLine(AttrPolyOffset::objDisableStr());
            ++mAttrNum;
        }
    });

    ObjState::processAttr(attrs.mLightLevel, mState.mObject.mLightLevel, [&](const bool enable) {
        if (enable) {
            mAttrNum += attrs.mLightLevel->printObj(*mWriter);
        }
        else {
            mWriter->printLine(AttrLightLevel::objDisableStr());
            ++mAttrNum;
        }
    });

    ObjState::processAttr(attrs.mCockpit, mState.mObject.mCockpit, [&](const bool enable) {
        if (enable) {
            mIsPanelManip = true;
            mState.mObject.mManipContainer = ManipContainer(new AttrManipPanel(*attrs.mCockpit));
            mAttrNum += attrs.mCockpit->printObj(*mWriter);
        }
        else {
            mIsPanelManip = false;
            mState.mObject.mManipContainer = std::nullopt;
            mWriter->printLine(AttrCockpit::objDisableStr());
            ++mAttrNum;
        }
    });

    //-------------------------------------------------------------------------
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool ObjWriteAttr::checkManip(AttrManipBase * manip) const {
    if (manip) {
        if (manip->type() == EManipulator::none) {
            if (!mIsPanelManip) {
                ULWarning << "The object <" << mObj->objectName() << "> uses <" << manip->type().toUiString()
                        << "> it does not make a sense because this manipulator is set automatically when it is needed.";
                return false;
            }
        }
        else if (manip->type() == EManipulator::panel) {
            if (!mIsPanelManip) {
                ULError << "The object <" << mObj->objectName() << "> uses <" << manip->type().toUiString()
                        << "> manipulator but the object doesn't have the attributes <" << ATTR_COCKPIT << " or " ATTR_COCKPIT_REGION
                        << "> the <" << manip->type().toUiString() << "> can be used only for the geometry with one of those attributes.";
                return false;
            }
            auto * panel = static_cast<AttrManipPanel*>(manip);
            panel->setCockpit(*mObj->mAttr.mCockpit);
        }
        else if (manip->type() == EManipulator::drag_axis) {
            // todo it seems this place isn't good for such a checking
            const auto * castManip = static_cast<const AttrManipDragAxis*>(manip);
            if (!castManip->axisDetented().isEnabled() && !castManip->detentRanges().empty()) {
                ULError << "The object <" << mObj->objectName() << "> uses <" << manip->type().toUiString()
                        << "> manipulator with the " << ATTR_MANIP_AXIS_DETENT_RANGE << " but " << ATTR_MANIP_AXIS_DETENTED << " isn't enabled.";
            }
            // todo this is the code duplication
            if (!castManip->detentRanges().empty()) {
                std::size_t counter = 0;
                for (const auto & dr : castManip->detentRanges()) {
                    if (dr.start() > dr.end()) {
                        ULError << "The object <" << mObj->objectName() << "> has incorrect detent range values at <"
                                << counter << "> position, start value must be smaller than end value.";
                    }
                    // todo implementation of checking
                    // You may use more than one ATTR_axis_detent_range to create complex detent patterns.
                    // You can include zero-length detents that are lower than their neighbors to create “stop pits’,
                    // but do not create zero length detents that are higher than their neighbors; they will not stop a drag.
                    ++counter;
                }
            }
        }
        else if (manip->type() == EManipulator::drag_rotate) {
            // todo it seems this place isn't good for such a checking
            const auto * castManip = static_cast<const AttrManipDragRotate*>(manip);
            if (!castManip->detentRanges().empty()) {
                std::size_t counter = 0;
                for (const auto & dr : castManip->detentRanges()) {
                    if (dr.start() > dr.end()) {
                        ULError << "The object <" << mObj->objectName() << "> has incorrect detent range values at <"
                                << counter << "> position, start value must be smaller than end value.";
                    }
                    // todo implementation of checking
                    // You may use more than one ATTR_axis_detent_range to create complex detent patterns.
                    // You can include zero-length detents that are lower than their neighbors to create “stop pits’,
                    // but do not create zero length detents that are higher than their neighbors; they will not stop a drag.
                    ++counter;
                }
            }
            if (!castManip->keys().empty()) {
                const auto & keyList = castManip->keys();
                if (keyList.front() == AttrManipKeyFrame(castManip->v1Min(), castManip->angle1())) {
                    ULWarning << "The object <" << mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2min>/<angle1> at position 0.";
                }
                if (keyList.back() == AttrManipKeyFrame(castManip->v1Max(), castManip->angle2())) {
                    ULWarning << "The object <" << mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2max>/<angle2> at position " << keyList.size() - 1 << ".";
                }
            }
        }
    }
    return true;
}

void ObjWriteAttr::writeManip() {
    const auto & attrs = mObj->mAttr;
    auto manipContainer = attrs.mManipContainer;
    //------------------------------
    // Checks the order of processing, the attributes must be processed before the manipulators.
    assert(mIsPanelManip == mObj->mAttr.mCockpit.has_value());
    //------------------------------
    if (manipContainer && manipContainer->hasManip()) {
        if (!checkManip(manipContainer->mManip.get())) {
            manipContainer = std::nullopt;
        }
    }

    const auto switchFn = [&](const bool enable) {
        if (enable) {
            assert(manipContainer);
            assert(manipContainer->hasManip());
            mManipNum += manipContainer->mManip->printObj(*mWriter);
        }
        else {
            mManipNum += AttrManipNone().printObj(*mWriter);
        }
    };

    ObjState::processAttr(manipContainer, mState.mObject.mManipContainer, switchFn);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
