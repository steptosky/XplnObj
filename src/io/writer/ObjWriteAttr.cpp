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
#include <algorithm>

#include "ObjWriteAttr.h"

#include "AbstractWriter.h"
#include "common/AttributeNames.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/obj/manipulators/AttrManipDragRotate.h"
#include "xpln/obj/manipulators/AttrManipNone.h"
#include "io/StringValidator.h"
#include "xpln/obj/manipulators/AttrManipPanel.h"
#include "common/Logger.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAttr::reset(ObjState::Ptr state) {
    mState = std::move(state);
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

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrWetDry>>(const std::optional<AttrWetDry> & attr) {
    if (attr) {
        mWriter->writeLine(attr->mState == AttrWetDry::eState::wet ? ATTR_GLOBAL_WET : ATTR_GLOBAL_DRY);
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrBlend>>(const std::optional<AttrBlend> & attr) {
    if (attr) {
        if (attr->mRatio < 0.0f || attr->mRatio > 1.0f) {
            ULWarning << "The object <" << mMainObj->objectName()
                    << "> has the blending attribute with the out of range ration [0 > ration < 1].";
        }
        const auto ration = std::clamp(attr->mRatio, 0.0f, 1.0f);
        if (attr->mType == AttrBlend::no_blend) {
            mWriter->writeLine(ATTR_GLOBAL_NO_BLEND, " ", ration);
        }
        else if (attr->mType == AttrBlend::shadow_blend) {
            mWriter->writeLine(ATTR_GLOBAL_SHADOW_BLEND, " ", ration);
        }
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrLayerGroup>>(const std::optional<AttrLayerGroup> & attr) {
    if (attr) {
        if (attr->mOffset < -5 || attr->mOffset > 5) {
            ULWarning << "The object <" << mMainObj->objectName() << "> has the attribute <"
                    << ATTR_GLOBAL_LAYER_GROUP << "> with the out of range offset [-5 > ration < 5].";
        }
        mWriter->writeLine(ATTR_GLOBAL_LAYER_GROUP, " ", attr->mLayer.toString(), " ", std::clamp(attr->mOffset, -5, 5));
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrSlungLoadWeight>>(const std::optional<AttrSlungLoadWeight> & attr) {
    if (attr) {
        mWriter->writeLine(ATTR_GLOBAL_SLUNG_LOAD_WEIGHT, " ", attr->mWeight);
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrSpecular>>(const std::optional<AttrSpecular> & attr) {
    if (attr) {
        if (attr->mRatio < 0.0f || attr->mRatio > 1.0f) {
            ULWarning << "The object <" << mMainObj->objectName() << "> has the attribute <"
                    << ATTR_GLOBAL_SPECULAR << "> with the out of range ration [0 > ration < 1].";
        }
        mWriter->writeLine(ATTR_GLOBAL_SPECULAR, " ", std::clamp(attr->mRatio, 0.0f, 1.0f));
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrTint>>(const std::optional<AttrTint> & attr) {
    if (attr) {
        mWriter->writeLine(ATTR_GLOBAL_TINT, " ", attr->mAlbedo, " ", attr->mEmissive);
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrSlopeLimit>>(const std::optional<AttrSlopeLimit> & attr) {
    if (attr) {
        mWriter->writeLine(ATTR_GLOBAL_SLOPE_LIMIT,
                           " ", attr->mMinPitch,
                           " ", attr->mMaxPitch,
                           " ", attr->mMinRoll,
                           " ", attr->mMaxRoll);
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrCockpitRegion>>(const std::optional<AttrCockpitRegion> & attr) {
    if (attr) {
        mWriter->writeLine(ATTR_GLOBAL_COCKPIT_REGION,
                           " ", attr->mLeft,
                           " ", attr->mBottom,
                           " ", attr->mRight,
                           " ", attr->mTop);
        ++mGlobNum;
    }
}

//-------------------------------------------------------------------------

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrDrapedLayerGroup>>(const std::optional<AttrDrapedLayerGroup> & attr) {
    if (attr) {
        if (attr->mOffset < -5 || attr->mOffset > 5) {
            ULWarning << "The object <" << mMainObj->objectName() << "> has the attribute <"
                    << ATTR_GLOBAL_LAYER_GROUP_DRAPED << "> with the out of range offset [-5 > ration < 5].";
        }
        mWriter->writeLine(ATTR_GLOBAL_LAYER_GROUP_DRAPED,
                           " ", attr->mLayer.toString(),
                           " ", std::clamp(attr->mOffset, -5, 5));
        ++mGlobNum;
    }
}

template<>
void ObjWriteAttr::writeGlobAttrState<std::optional<AttrDrapedLod>>(const std::optional<AttrDrapedLod> & attr) {
    if (attr) {
        mWriter->writeLine(ATTR_GLOBAL_LOD_DRAPED, " ", attr->mDistance);
        ++mGlobNum;
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAttr::writeGlobAttr(AbstractWriter * writer, const ObjMain * obj) {
    assert(obj);
    assert(writer);
    mWriter = writer;
    mMainObj = obj;

    const auto writeBool = [&](const char * inAttr, const bool inState) {
        if (inState) {
            mWriter->writeLine(inAttr);
            ++mGlobNum;
        }
    };

    const auto writeString = [&](const char * inAttr, const std::optional<std::string> & string) {
        if (string && !string->empty()) {
            if (!StringValidator::hasIllegalSymbols(*string, "\t\n\r")) {
                mWriter->writeLine(std::string(inAttr).append(" ").append(*string));
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

    writeGlobAttrState(obj->mAttr.mWetDry);
    writeGlobAttrState(obj->mAttr.mBlend);
    writeGlobAttrState(obj->mAttr.mLayerGroup);
    writeGlobAttrState(obj->mAttr.mSlungLoadWeight);
    writeGlobAttrState(obj->mAttr.mSpecular);
    writeGlobAttrState(obj->mAttr.mTint);
    writeGlobAttrState(obj->mAttr.mSlopeLimit);
    writeGlobAttrState(obj->mAttr.mCockpitRegion1);
    writeGlobAttrState(obj->mAttr.mCockpitRegion2);
    writeGlobAttrState(obj->mAttr.mCockpitRegion3);
    writeGlobAttrState(obj->mAttr.mCockpitRegion4);

    writeGlobAttrState(obj->mDraped.mAttr.mLayerGroup);
    writeGlobAttrState(obj->mDraped.mAttr.mLod);
    mMainObj = nullptr;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<>
void ObjWriteAttr::switchAttrState<AttrBlend>(const AttrBlend & attr, const bool enable) {
    if (enable) {
        if (attr.mRatio < 0.0f || attr.mRatio > 1.0f) {
            ULWarning << "The object <" << mObj->objectName()
                    << "> has the blending attribute with the out of range ration [0 > ration < 1].";
        }
        const auto ratio = std::clamp(attr.mRatio, 0.0f, 1.0f);
        if (attr.mType == AttrBlend::no_blend) {
            mWriter->writeLine(ATTR_NO_BLEND, " ", ratio);
        }
        else if (attr.mType == AttrBlend::shadow_blend) {
            mWriter->writeLine(ATTR_SHADOW_BLEND, " ", ratio);
        }
        else {
            mWriter->writeLine(ATTR_BLEND, " ", ratio);
        }
    }
    else {
        mWriter->writeLine(ATTR_BLEND, " ", AttrBlend().mRatio);
    }
    ++mAttrNum;
}

template<>
void ObjWriteAttr::switchAttrState<AttrCockpit>(const AttrCockpit & attr, const bool enable) {
    if (enable) {
        mIsPanelManip = true;
        mState->mObject.mManipContainer = AttrManip(AttrManipPanel(attr));

        if (attr.mType == AttrCockpit::cockpit) {
            mWriter->writeLine(ATTR_COCKPIT);
        }
        else if (attr.mType == AttrCockpit::region_1) {
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 0");
        }
        else if (attr.mType == AttrCockpit::region_2) {
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 1");
        }
        else if (attr.mType == AttrCockpit::region_3) {
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 2");
        }
        else if (attr.mType == AttrCockpit::region_4) {
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 3");
        }
        else if (attr.mType == AttrCockpit::cockpit_device) {
            mWriter->writeLine(ATTR_COCKPIT_DEVICE, " ", attr.mDeviceName, " ", attr.mDeviceBus, " ",
                               attr.mDeviceLightingChan, " ", attr.mDeviceAutoAdjust);
        }
        else {
            ULError << "unknown cockpit type: " << attr.mType;
        }
    }
    else {
        mIsPanelManip = false;
        mState->mObject.mManipContainer = std::nullopt;

        mWriter->writeLine(ATTR_NO_COCKPIT);
    }
    ++mAttrNum;
}

template<>
void ObjWriteAttr::switchAttrState<AttrHard>(const AttrHard & attr, const bool enable) {
    if (enable) {
        mWriter->writeLine(attr.mIsDeck ? ATTR_HARD_DECK : ATTR_HARD, " ", attr.mSurface.toString());
    }
    else {
        mWriter->writeLine(ATTR_NO_HARD);
    }
    ++mAttrNum;
}

template<>
void ObjWriteAttr::switchAttrState<AttrLightLevel>(const AttrLightLevel & attr, const bool enable) {
    if (enable) {
        mWriter->writeLine(ATTR_LIGHT_LEVEL, " ", attr.mVal1, " ", attr.mVal2, " ", attr.mDataref);
    }
    else {
        mWriter->writeLine(ATTR_LIGHT_LEVEL_RESET);
    }
    ++mAttrNum;
}

template<>
void ObjWriteAttr::switchAttrState<AttrPolyOffset>(const AttrPolyOffset & attr, const bool enable) {
    if (enable) {
        mWriter->writeLine(ATTR_POLY_OS, " ", attr.mOffset);
    }
    else {
        mWriter->writeLine(ATTR_POLY_OS, " ", AttrPolyOffset().mOffset);
    }
    ++mAttrNum;
}

template<>
void ObjWriteAttr::switchAttrState<AttrShiny>(const AttrShiny & attr, const bool enable) {
    if (enable) {
        if (attr.mRatio < 0.0f || attr.mRatio > 1.0f) {
            ULWarning << "The object <" << mObj->objectName() << "> has the attribute <"
                    << ATTR_SHINY_RAT << "> with the out of range ration [0 > ration < 1].";
        }
        mWriter->writeLine(ATTR_SHINY_RAT, " ", std::clamp(attr.mRatio, 0.0f, 1.0f));
    }
    else {
        mWriter->writeLine(ATTR_SHINY_RAT, " ", 0.0f);
    }
    ++mAttrNum;
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
    mObj = nullptr;
}

void ObjWriteAttr::writeAttr() {
    const auto & attrs = mObj->mAttr;

    //-------------------------------------------------------------------------

    ObjState::processBool(attrs.mIsDraped, mState->mObject.mIsDraped, [&](const bool enable) {
        mWriter->writeLine(enable ? ATTR_DRAPED : ATTR_NO_DRAPED);
        ++mAttrNum;
    });

    ObjState::processBool(attrs.mIsSolidForCamera, mState->mObject.mIsSolidForCamera, [&](const bool enable) {
        mWriter->writeLine(enable ? ATTR_SOLID_CAMERA : ATTR_NO_SOLID_CAMERA);
        ++mAttrNum;
    });

    ObjState::processBool(attrs.mIsDraw, mState->mObject.mIsDraw, [&](const bool enable) {
        mWriter->writeLine(enable ? ATTR_DRAW_ENABLE : ATTR_DRAW_DISABLE);
        ++mAttrNum;
    });

    ObjState::processBool(attrs.mIsCastShadow, mState->mObject.mIsCastShadow, [&](const bool enable) {
        mWriter->writeLine(enable ? ATTR_SHADOW : ATTR_NO_SHADOW);
        ++mAttrNum;
    });

    //-------------------------------------------------------------------------

    ObjState::processAttr(attrs.mHard, mState->mObject.mHard, [&](const bool enable) {
        switchAttrState<AttrHard>(*attrs.mHard, enable);
    });

    ObjState::processAttr(attrs.mShiny, mState->mObject.mShiny, [&](const bool enable) {
        switchAttrState<AttrShiny>(*attrs.mShiny, enable);
    });

    ObjState::processAttr(attrs.mBlend, mState->mObject.mBlend, [&](const bool enable) {
        switchAttrState<AttrBlend>(*attrs.mBlend, enable);
    });

    ObjState::processAttr(attrs.mPolyOffset, mState->mObject.mPolyOffset, [&](const bool enable) {
        switchAttrState<AttrPolyOffset>(*attrs.mPolyOffset, enable);
    });

    ObjState::processAttr(attrs.mLightLevel, mState->mObject.mLightLevel, [&](const bool enable) {
        switchAttrState<AttrLightLevel>(*attrs.mLightLevel, enable);
    });

    ObjState::processAttr(attrs.mCockpit, mState->mObject.mCockpit, [&](const bool enable) {
        switchAttrState<AttrCockpit>(*attrs.mCockpit, enable);
    });

}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

class ObjWriteAttr::ManipChecker {
    template<class V>
    struct always_false : std::false_type {};

public:

    template<typename MANIP>
    void operator()(MANIP && manip) {
        using T = std::decay_t<decltype(manip)>;
        if constexpr (std::is_same_v<T, AttrManipAxisKnob>) { }
        else if constexpr (std::is_same_v<T, AttrManipAxisSwitchLeftRight>) { }
        else if constexpr (std::is_same_v<T, AttrManipAxisSwitchUpDown>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmd>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmdAxis>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmdKnob>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmdKnob2>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchLeftRight>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchLeftRight2>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchUpDown>) { }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchUpDown2>) { }
        else if constexpr (std::is_same_v<T, AttrManipDelta>) { }
        else if constexpr (std::is_same_v<T, AttrManipDragAxis>) {
            if (!manip.axisDetented().isEnabled() && !manip.detentRanges().empty()) {
                ULError << "The object <" << mAttrWriter->mObj->objectName() << "> uses <" << manip.type().toUiString()
                        << "> manipulator with the " << ATTR_MANIP_AXIS_DETENT_RANGE << " but " << ATTR_MANIP_AXIS_DETENTED << " isn't enabled.";
            }
            // todo this is the code duplication
            if (!manip.detentRanges().empty()) {
                std::size_t counter = 0;
                for (const auto & dr : manip.detentRanges()) {
                    if (dr.start() > dr.end()) {
                        ULError << "The object <" << mAttrWriter->mObj->objectName() << "> has incorrect detent range values at <"
                                << counter << "> position, start value must be smaller than end value.";
                    }
                    // todo implementation of checking
                    // You may use more than one ATTR_axis_detent_range to create complex detent patterns.
                    // You can include zero-length detents that are lower than their neighbors to create �stop pits�,
                    // but do not create zero length detents that are higher than their neighbors; they will not stop a drag.
                    ++counter;
                }
            }
        }
        else if constexpr (std::is_same_v<T, AttrManipDragAxisPix>) { }
        else if constexpr (std::is_same_v<T, AttrManipDragRotate>) {
            // todo this is the code duplication
            if (!manip.detentRanges().empty()) {
                std::size_t counter = 0;
                for (const auto & dr : manip.detentRanges()) {
                    if (dr.start() > dr.end()) {
                        ULError << "The object <" << mAttrWriter->mObj->objectName() << "> has incorrect detent range values at <"
                                << counter << "> position, start value must be smaller than end value.";
                    }
                    // todo implementation of checking
                    // You may use more than one ATTR_axis_detent_range to create complex detent patterns.
                    // You can include zero-length detents that are lower than their neighbors to create �stop pits�,
                    // but do not create zero length detents that are higher than their neighbors; they will not stop a drag.
                    ++counter;
                }
            }
            if (!manip.keys().empty()) {
                const auto & keyList = manip.keys();
                if (keyList.front() == AttrManipKeyFrame(manip.v1Min(), manip.angle1())) {
                    ULWarning << "The object <" << mAttrWriter->mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2min>/<angle1> at position 0.";
                }
                if (keyList.back() == AttrManipKeyFrame(manip.v1Max(), manip.angle2())) {
                    ULWarning << "The object <" << mAttrWriter->mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2max>/<angle2> at position " << keyList.size() - 1 << ".";
                }
            }
        }
        else if constexpr (std::is_same_v<T, AttrManipDragXy>) { }
        else if constexpr (std::is_same_v<T, AttrManipNone>) {
            if (!mAttrWriter->mIsPanelManip) {
                ULWarning << "The object <" << mAttrWriter->mObj->objectName() << "> uses <" << manip.type().toUiString()
                        << "> it does not make a sense because this manipulator is set automatically when it is needed.";
                mManipAllowed = false;
            }
        }
        else if constexpr (std::is_same_v<T, AttrManipNoop>) { }
        else if constexpr (std::is_same_v<T, AttrManipPanel>) {
            if (!mAttrWriter->mIsPanelManip) {
                ULError << "The object <" << mAttrWriter->mObj->objectName() << "> uses <" << manip.type().toUiString()
                        << "> manipulator but the object doesn't have the attributes <" << ATTR_COCKPIT << " or " ATTR_COCKPIT_REGION
                        << "> the <" << manip.type().toUiString() << "> can be used only for the geometry with one of those attributes.";
                mManipAllowed = false;
            }
            if (mAttrWriter->mObj->mAttr.mCockpit) {
                manip.setCockpit(*mAttrWriter->mObj->mAttr.mCockpit);
            }
        }
        else if constexpr (std::is_same_v<T, AttrManipPush>) { }
        else if constexpr (std::is_same_v<T, AttrManipRadio>) { }
        else if constexpr (std::is_same_v<T, AttrManipToggle>) { }
        else if constexpr (std::is_same_v<T, AttrManipWrap>) { }
        else {
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }
    }

    ObjWriteAttr * mAttrWriter = nullptr;
    bool mManipAllowed = true;
};

class ManipPrinter {
    template<class V>
    struct always_false : std::false_type {};

public:

    template<typename MANIP>
    std::size_t operator()(MANIP && manip) {
        return manip.printObj(*w);
        // todo remove printing method from manips and use this class
        // using T = std::decay_t<decltype(manip)>;
        // if constexpr (std::is_same_v<T, AttrManipAxisKnob>) { }
        // else if constexpr (std::is_same_v<T, AttrManipAxisSwitchLeftRight>) { }
        // else if constexpr (std::is_same_v<T, AttrManipAxisSwitchUpDown>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmd>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmdAxis>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmdKnob>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmdKnob2>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmdSwitchLeftRight>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmdSwitchLeftRight2>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmdSwitchUpDown>) { }
        // else if constexpr (std::is_same_v<T, AttrManipCmdSwitchUpDown2>) { }
        // else if constexpr (std::is_same_v<T, AttrManipDelta>) { }
        // else if constexpr (std::is_same_v<T, AttrManipDragAxis>) {}
        // else if constexpr (std::is_same_v<T, AttrManipDragAxisPix>) { }
        // else if constexpr (std::is_same_v<T, AttrManipDragRotate>) {}
        // else if constexpr (std::is_same_v<T, AttrManipDragXy>) { }
        // else if constexpr (std::is_same_v<T, AttrManipNone>) {}
        // else if constexpr (std::is_same_v<T, AttrManipNoop>) { }
        // else if constexpr (std::is_same_v<T, AttrManipPanel>) {}
        // else if constexpr (std::is_same_v<T, AttrManipPush>) { }
        // else if constexpr (std::is_same_v<T, AttrManipRadio>) { }
        // else if constexpr (std::is_same_v<T, AttrManipToggle>) { }
        // else if constexpr (std::is_same_v<T, AttrManipWrap>) { }
        // else {
        //     static_assert(always_false<T>::value, "non-exhaustive visitor!");
        // }
    }

    AbstractWriter * w = nullptr;
};

void ObjWriteAttr::writeManip() {
    const auto & attrs = mObj->mAttr;
    auto manipContainer = attrs.mManipContainer;
    //------------------------------
    // Checks the order of processing, the attributes must be processed before the manipulators.
    assert(mIsPanelManip == mObj->mAttr.mCockpit.has_value());
    //------------------------------
    if (manipContainer) {
        ManipChecker checker{this};
        std::visit(checker, manipContainer->mType);
        if (!checker.mManipAllowed) {
            manipContainer = std::nullopt;
        }
    }

    const auto switchFn = [&](const bool enable) {
        if (enable) {
            assert(manipContainer);
            if (const auto panelManip = std::get_if<AttrManipPanel>(&manipContainer->mType)) {
                switchAttrState<AttrCockpit>(panelManip->cockpit(), true);
            }
            mManipNum += std::visit(ManipPrinter{mWriter}, manipContainer->mType);
        }
        else {
            mManipNum += AttrManipNone().printObj(*mWriter);
        }
    };

    ObjState::processAttr(manipContainer, mState->mObject.mManipContainer, switchFn);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
