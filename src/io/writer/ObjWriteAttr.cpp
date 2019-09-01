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
#include "xpln/obj/manipulators/AttrManipPanel.h"
#include "xpln/common/Logger.h"
#include "xpln/common/String.h"

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
            XULWarning << "The object <" << mMainObj->objectName()
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
            XULWarning << "The object <" << mMainObj->objectName() << "> has the attribute <"
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
            XULWarning << "The object <" << mMainObj->objectName() << "> has the attribute <"
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
            XULWarning << "The object <" << mMainObj->objectName() << "> has the attribute <"
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
            if (!String::hasIllegalSymbolsForPath(*string)) {
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
            XULWarning << "The object <" << mObj->objectName()
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
        mState->mObject.mManip = AttrManip(AttrManipPanel(attr));

        if (attr.mType == AttrCockpit::cockpit) {
            mWriter->writeLine(ATTR_COCKPIT);
        }
        else if (attr.mType == AttrCockpit::region_1) {
            if (!mState->mGlobal.mCockpitRegion1) {
                XULError << "The obj <" << mObj->objectName() << "> has the <" << ATTR_COCKPIT_REGION << " 0> attribute but <"
                        << ATTR_GLOBAL_COCKPIT_REGION << "> attribute isn't specified for the obj file.";
            }
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 0");
        }
        else if (attr.mType == AttrCockpit::region_2) {
            if (!mState->mGlobal.mCockpitRegion2) {
                XULError << "The obj <" << mObj->objectName() << "> has the <" << ATTR_COCKPIT_REGION << " 1> attribute but <"
                        << ATTR_GLOBAL_COCKPIT_REGION << "> attribute isn't specified for the obj file.";
            }
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 1");
        }
        else if (attr.mType == AttrCockpit::region_3) {
            if (!mState->mGlobal.mCockpitRegion3) {
                XULError << "The obj <" << mObj->objectName() << "> has the <" << ATTR_COCKPIT_REGION << " 2> attribute but <"
                        << ATTR_GLOBAL_COCKPIT_REGION << "> attribute isn't specified for the obj file.";
            }
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 2");
        }
        else if (attr.mType == AttrCockpit::region_4) {
            if (!mState->mGlobal.mCockpitRegion4) {
                XULError << "The obj <" << mObj->objectName() << "> has the <" << ATTR_COCKPIT_REGION << " 3> attribute but <"
                        << ATTR_GLOBAL_COCKPIT_REGION << "> attribute isn't specified for the obj file.";
            }
            mWriter->writeLine(ATTR_COCKPIT_REGION, " 3");
        }
        else if (attr.mType == AttrCockpit::cockpit_device) {
            if (attr.mDeviceName.empty()) {
                XULError << "The obj <" << mObj->objectName() << "> has the <" << ATTR_COCKPIT_DEVICE << "> attribute without a device name.";
            }
            mWriter->writeLine(ATTR_COCKPIT_DEVICE, " ", attr.mDeviceName, " ", attr.mDeviceBus, " ",
                               attr.mDeviceLightingChan, " ", attr.mDeviceAutoAdjust);
        }
        else {
            XULError << "unknown cockpit type: " << attr.mType;
        }
    }
    else {
        mIsPanelManip = false;
        mState->mObject.mManip = std::nullopt;

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
            XULWarning << "The object <" << mObj->objectName() << "> has the attribute <"
                    << ATTR_SHINY_RAT << "> with the out of range ration [0 > ration < 1].";
        }
        mWriter->writeLine(ATTR_SHINY_RAT, " ", std::clamp(attr.mRatio, 0.0f, 1.0f));
        mState->mObjHasAttrShinyRat = true;
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
            if (!manip.mAxisDetented && !manip.mAxisDetentRanges.empty()) {
                XULError << "The object <" << mAttrWriter->mObj->objectName() << "> uses <" << manip.mType.toString()
                        << "> manipulator with the " << ATTR_MANIP_AXIS_DETENT_RANGE << " but " << ATTR_MANIP_AXIS_DETENTED << " isn't enabled.";
            }
            // todo this is the code duplication
            if (!manip.mAxisDetentRanges.empty()) {
                std::size_t counter = 0;
                for (const auto & dr : manip.mAxisDetentRanges) {
                    if (dr.mStart > dr.mEnd) {
                        XULError << "The object <" << mAttrWriter->mObj->objectName() << "> has incorrect detent range values at <"
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
        else if constexpr (std::is_same_v<T, AttrManipDragAxisPix>) { }
        else if constexpr (std::is_same_v<T, AttrManipDragRotate>) {
            // todo this is the code duplication
            if (!manip.mAxisDetentRanges.empty()) {
                std::size_t counter = 0;
                for (const auto & dr : manip.mAxisDetentRanges) {
                    if (dr.mStart > dr.mEnd) {
                        XULError << "The object <" << mAttrWriter->mObj->objectName() << "> has incorrect detent range values at <"
                                << counter << "> position, start value must be smaller than end value.";
                    }
                    // todo implementation of checking
                    // You may use more than one ATTR_axis_detent_range to create complex detent patterns.
                    // You can include zero-length detents that are lower than their neighbors to create “stop pits’,
                    // but do not create zero length detents that are higher than their neighbors; they will not stop a drag.
                    ++counter;
                }
            }
            if (!manip.mKeys.empty()) {
                const auto & keyList = manip.mKeys;
                if (keyList.front() == AttrManipKeyFrame(manip.mV1Min, manip.mAngle1)) {
                    XULWarning << "The object <" << mAttrWriter->mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2min>/<angle1> at position 0.";
                }
                if (keyList.back() == AttrManipKeyFrame(manip.mV1Max, manip.mAngle2)) {
                    XULWarning << "The object <" << mAttrWriter->mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2max>/<angle2> at position " << keyList.size() - 1 << ".";
                }
            }
        }
        else if constexpr (std::is_same_v<T, AttrManipDragXy>) { }
        else if constexpr (std::is_same_v<T, AttrManipNone>) {
            if (!mAttrWriter->mIsPanelManip) {
                XULWarning << "The object <" << mAttrWriter->mObj->objectName() << "> uses <" << manip.mType.toString()
                        << "> manipulator, it does not make a sense because this manipulator is set automatically when it is needed.";
                mManipAllowed = false;
            }
        }
        else if constexpr (std::is_same_v<T, AttrManipNoop>) { }
        else if constexpr (std::is_same_v<T, AttrManipPanel>) {
            if (!mAttrWriter->mIsPanelManip) {
                XULError << "The object <" << mAttrWriter->mObj->objectName() << "> uses <" << manip.mType.toString()
                        << "> manipulator but the object doesn't have the attributes <" << ATTR_COCKPIT << " or " ATTR_COCKPIT_REGION
                        << "> the <" << manip.mType.toString() << "> can be used only for the geometry with one of those attributes.";
                mManipAllowed = false;
            }
            if (mAttrWriter->mObj->mAttr.mCockpit) {
                manip.mAttrCockpit = *mAttrWriter->mObj->mAttr.mCockpit;
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

    std::size_t printWheel(const std::optional<AttrManipWheel> & wheel) const {
        if (wheel) {
            w->writeLine(ATTR_MANIP_WHEEL, " ", wheel->mWheelDelta);
            return 1;
        }
        return 0;
    }

    std::size_t printDetent(const std::optional<AttrAxisDetented> & detent) const {
        if (detent) {
            w->writeLine(ATTR_MANIP_AXIS_DETENTED,
                         " ", detent->mDirX,
                         " ", detent->mDirY,
                         " ", detent->mDirZ,
                         " ", detent->mVMin,
                         " ", detent->mVMax,
                         " ", w->actualDataref(detent->mDataref));
            return 1;
        }
        return 0;
    }

    std::size_t printDetentRanges(const std::vector<AttrAxisDetentRange> & detentRange) const {
        for (const auto & dr : detentRange) {
            w->writeLine(ATTR_MANIP_AXIS_DETENT_RANGE, " ", dr.mStart, " ", dr.mEnd, " ", dr.mHeight);
        }
        return detentRange.size();
    }

    std::size_t printKeyFrame(const std::vector<AttrManipKeyFrame> & keys) const {
        for (const auto & key : keys) {
            w->writeLine(ATTR_MANIP_KEYFRAME, " ", key.mValue, " ", key.mAngle);
        }
        return keys.size();
    }

    template<typename MANIP>
    std::size_t operator()(MANIP && manip) {
        using T = std::decay_t<decltype(manip)>;
        if constexpr (std::is_same_v<T, AttrManipAxisKnob>) {
            w->writeLine(ATTR_MANIP_AXIS_KNOB,
                         " ", manip.mCursor.toString(),
                         " ", manip.mMin,
                         " ", manip.mMax,
                         " ", manip.mClickDelta,
                         " ", manip.mHoldDelta,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipAxisSwitchLeftRight>) {
            w->writeLine(ATTR_MANIP_AXIS_SWITCH_LEFT_RIGHT,
                         " ", manip.mCursor.toString(),
                         " ", manip.mMin,
                         " ", manip.mMax,
                         " ", manip.mClickDelta,
                         " ", manip.mHoldDelta,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipAxisSwitchUpDown>) {
            w->writeLine(ATTR_MANIP_AXIS_SWITCH_UP_DOWN,
                         " ", manip.mCursor.toString(),
                         " ", manip.mMin,
                         " ", manip.mMax,
                         " ", manip.mClickDelta,
                         " ", manip.mHoldDelta,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipCmd>) {
            w->writeLine(ATTR_MANIP_COMMAND,
                         " ", manip.mCursor.toString(),
                         " ", w->actualCommand(manip.mCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipCmdAxis>) {
            w->writeLine(ATTR_MANIP_COMMAND_AXIS,
                         " ", manip.mCursor.toString(),
                         " ", manip.mDirX,
                         " ", manip.mDirY,
                         " ", manip.mDirZ,
                         " ", w->actualCommand(manip.mPosCommand),
                         " ", w->actualCommand(manip.mNegCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipCmdKnob>) {
            w->writeLine(ATTR_MANIP_COMMAND_KNOB,
                         " ", manip.mCursor.toString(),
                         " ", w->actualCommand(manip.mPosCommand),
                         " ", w->actualCommand(manip.mNegCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipCmdKnob2>) {
            w->writeLine(ATTR_MANIP_COMMAND_KNOB2,
                         " ", manip.mCursor.toString(),
                         " ", w->actualCommand(manip.mCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchLeftRight>) {
            w->writeLine(ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT,
                         " ", manip.mCursor.toString(),
                         " ", w->actualCommand(manip.mPosCommand),
                         " ", w->actualCommand(manip.mNegCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchLeftRight2>) {
            w->writeLine(ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT2,
                         " ", manip.mCursor.toString(),
                         " ", w->actualCommand(manip.mCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchUpDown>) {
            w->writeLine(ATTR_MANIP_COMMAND_SWITCH_UP_DOWN,
                         " ", manip.mCursor.toString(),
                         " ", w->actualCommand(manip.mPosCommand),
                         " ", w->actualCommand(manip.mNegCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipCmdSwitchUpDown2>) {
            w->writeLine(ATTR_MANIP_COMMAND_SWITCH_UP_DOWN2,
                         " ", manip.mCursor.toString(),
                         " ", w->actualCommand(manip.mCommand),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipDelta>) {
            w->writeLine(ATTR_MANIP_DELTA,
                         " ", manip.mCursor.toString(),
                         " ", manip.mDown,
                         " ", manip.mHold,
                         " ", manip.mMin,
                         " ", manip.mMax,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipDragAxis>) {
            std::size_t outCounter = 1;
            w->writeLine(ATTR_MANIP_DRAG_AXIS,
                         " ", manip.mCursor.toString(),
                         " ", manip.mDirX,
                         " ", manip.mDirY,
                         " ", manip.mDirZ,
                         " ", manip.mVal1,
                         " ", manip.mVal2,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);

            outCounter += printWheel(manip.mWheel);
            if (manip.mAxisDetented) {
                outCounter += printDetent(manip.mAxisDetented);
                outCounter += printDetentRanges(manip.mAxisDetentRanges);
            }
            return outCounter;
        }
        else if constexpr (std::is_same_v<T, AttrManipDragAxisPix>) {
            w->writeLine(ATTR_MANIP_DRAG_AXIS_PIX,
                         " ", manip.mCursor.toString(),
                         " ", manip.mDxPix,
                         " ", manip.mStep,
                         " ", manip.mExp,
                         " ", manip.mVal1,
                         " ", manip.mVal2,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipDragRotate>) {
            std::size_t outCounter = 1;
            w->writeLine(ATTR_MANIP_DRAG_ROTATE,
                         " ", manip.mCursor.toString(),
                         " ", manip.mOriginX,
                         " ", manip.mOriginY,
                         " ", manip.mOriginZ,
                         " ", manip.mDirX,
                         " ", manip.mDirY,
                         " ", manip.mDirZ,
                         " ", manip.mAngle1,
                         " ", manip.mAngle2,
                         " ", manip.mLift,
                         " ", manip.mV1Min,
                         " ", manip.mV1Max,
                         " ", manip.mV2Min,
                         " ", manip.mV2Max,
                         " ", w->actualDataref(manip.mDataref1),
                         " ", w->actualDataref(manip.mDataref2),
                         " ", manip.mToolType);

            outCounter += printKeyFrame(manip.mKeys);
            outCounter += printDetentRanges(manip.mAxisDetentRanges);
            return outCounter;
        }
        else if constexpr (std::is_same_v<T, AttrManipDragXy>) {
            w->writeLine(ATTR_MANIP_DRAG_XY,
                         " ", manip.mCursor.toString(),
                         " ", manip.mX,
                         " ", manip.mY,
                         " ", manip.mXMin,
                         " ", manip.mXMax,
                         " ", manip.mYMin,
                         " ", manip.mYMax,
                         " ", w->actualDataref(manip.mXDataref),
                         " ", w->actualDataref(manip.mYDataref),
                         " ", manip.mToolType);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipNone>) {
            w->writeLine(ATTR_MANIP_NONE);
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipNoop>) {
            if (!manip.mToolType.empty()) {
                w->writeLine(ATTR_MANIP_NOOP, " ", manip.mToolType);
            }
            else {
                w->writeLine(ATTR_MANIP_NOOP);
            }
            return 1;
        }
        else if constexpr (std::is_same_v<T, AttrManipPanel>) {
#if 0
            w->printEol();
            w->writeLine("## panel manip");
#endif
            return 0;
        }
        else if constexpr (std::is_same_v<T, AttrManipPush>) {
            w->writeLine(ATTR_MANIP_PUSH,
                         " ", manip.mCursor.toString(),
                         " ", manip.mDown,
                         " ", manip.mUp,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipRadio>) {
            w->writeLine(ATTR_MANIP_RADIO,
                         " ", manip.mCursor.toString(),
                         " ", manip.mDown,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipToggle>) {
            w->writeLine(ATTR_MANIP_TOGGLE,
                         " ", manip.mCursor.toString(),
                         " ", manip.mOn,
                         " ", manip.mOff,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else if constexpr (std::is_same_v<T, AttrManipWrap>) {
            w->writeLine(ATTR_MANIP_WRAP,
                         " ", manip.mCursor.toString(),
                         " ", manip.mDown,
                         " ", manip.mHold,
                         " ", manip.mMin,
                         " ", manip.mMax,
                         " ", w->actualDataref(manip.mDataref),
                         " ", manip.mToolType);
            return 1 + printWheel(manip.mWheel);
        }
        else {
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
            return 0;
        }
    }

    AbstractWriter * w = nullptr;
};

void ObjWriteAttr::writeManip() {
    const auto & attrs = mObj->mAttr;
    auto manipCopy = attrs.mManip;
    //------------------------------
    // Checks the order of processing, the attributes must be processed before the manipulators.
    assert(mIsPanelManip == mObj->mAttr.mCockpit.has_value());
    //------------------------------
    if (manipCopy) {
        ManipChecker checker{this};
        std::visit(checker, *manipCopy);
        if (!checker.mManipAllowed) {
            manipCopy = std::nullopt;
        }
    }

    const auto switchFn = [&](const bool enable) {
        if (enable) {
            assert(manipCopy);
            if (const auto panelManip = std::get_if<AttrManipPanel>(&(*manipCopy))) {
                switchAttrState<AttrCockpit>(panelManip->mAttrCockpit.value_or(AttrCockpit()), true);
            }
            mManipNum += std::visit(ManipPrinter{mWriter}, *manipCopy);
        }
        else {
            mManipNum += std::visit(ManipPrinter{mWriter}, AttrManip(AttrManipNone()));
        }
    };

    ObjState::processAttr(manipCopy, mState->mObject.mManip, switchFn);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
