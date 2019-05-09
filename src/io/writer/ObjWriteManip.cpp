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

#include "ObjWriteManip.h"
#include "xpln/obj/manipulators/AttrManipBase.h"
#include "AbstractWriter.h"

#include "common/AttributeNames.h"
#include "xpln/enums/eObjectType.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/manipulators/AttrManipPanel.h"
#include "xpln/obj/manipulators/AttrManipNone.h"
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/obj/manipulators/AttrManipDragRotate.h"
#include "common/Logger.h"

namespace xobj {

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

void ObjWriteManip::reset() {
    mActiveManip = nullptr;
    mManipCounter = 0;
    mIsPanelManip = false;
    mObj = nullptr;
}

size_t ObjWriteManip::count() const {
    return mManipCounter;
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

void ObjWriteManip::write(AbstractWriter * writer, const ObjAbstract * obj) {
    if (obj->objType() == eObjectType::OBJ_MESH) {
        mObj = static_cast<const ObjMesh *>(obj);
        write(writer, mObj->pAttr.manipulator());
    }
    else {
        mObj = nullptr;
    }
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

const AttrManipBase * ObjWriteManip::prepareManip(const AttrManipBase * manip) const {
    if (manip) {
        if (manip->type() == EManipulator::none) {
            if (!mIsPanelManip) {
                ULWarning << "The object <" << mObj->objectName() << "> uses <" << manip->type().toUiString()
                        << "> it does not make a sense because this manipulator is set automatically when it is needed.";
                return nullptr;
            }
        }
        else if (manip->type() == EManipulator::panel) {
            if (!mIsPanelManip) {
                ULError << "The object <" << mObj->objectName() << "> uses <" << manip->type().toUiString()
                        << "> manipulator but the object hasn't the attribute <" << ATTR_COCKPIT << " or " ATTR_COCKPIT_REGION
                        << "> the <" << manip->type().toUiString() << "> can be used only for the geometry with one of those attributes.";
                return nullptr;
            }

            // todo const cast isn't a good idea
            auto * panel = const_cast<AttrManipPanel*>(static_cast<const AttrManipPanel*>(manip));
            panel->setCockpit(*mObj->pAttr.mAttrCockpit);
        }
        else if (manip->type() == EManipulator::drag_axis) {
            // todo it seems this place isn't good for such a checking
            const auto * castedManip = static_cast<const AttrManipDragAxis*>(manip);
            if (!castedManip->axisDetented().isEnabled() && !castedManip->detentRanges().empty()) {
                ULError << "The object <" << mObj->objectName() << "> uses <" << manip->type().toUiString()
                        << "> manipulator with the " << ATTR_MANIP_AXIS_DETENT_RANGE << " but " << ATTR_MANIP_AXIS_DETENTED << " isn't enabled.";
            }
            // todo this is the code duplication
            if (!castedManip->detentRanges().empty()) {
                std::size_t counter = 0;
                for (const auto & dr : castedManip->detentRanges()) {
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
            const auto * castedManip = static_cast<const AttrManipDragRotate*>(manip);
            if (!castedManip->detentRanges().empty()) {
                std::size_t counter = 0;
                for (const auto & dr : castedManip->detentRanges()) {
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
            if (!castedManip->keys().empty()) {
                const auto & keyList = castedManip->keys();
                if (keyList.front() == AttrManipKeyFrame(castedManip->v1Min(), castedManip->angle1())) {
                    ULWarning << "The object <" << mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2min>/<angle1> at position 0.";
                }
                if (keyList.back() == AttrManipKeyFrame(castedManip->v1Max(), castedManip->angle2())) {
                    ULWarning << "The object <" << mObj->objectName() << "> has duplicate value " << ATTR_MANIP_KEYFRAME << " of "
                            << ATTR_MANIP_DRAG_ROTATE << ":<v2max>/<angle2> at position " << keyList.size() - 1 << ".";
                }
            }
        }
    }
    return manip;
}

void ObjWriteManip::write(AbstractWriter * writer, const AttrManipBase * manip) {
    assert(writer);
    //------------------------------
    /*! 
     * Checks the order of processing, the attributes must be processed before the manipulators.
     * The attributes' state machine calls this methods 
     * \link ObjWriteManip::setPanelEnabled \endlink and \link ObjWriteManip::setPanelDisabled \endlink
     * which set the \link ObjWriteManip::mIsPanelManip \endlink variable.
     */
    assert(mIsPanelManip == mObj->pAttr.mAttrCockpit.has_value());
    //------------------------------
    manip = prepareManip(manip);
    //------------------------------
    if (!manip) {
        if (mActiveManip) {
            AttrManipNone none;
            print(writer, &none);
            mActiveManip = nullptr;
        }
    }
    else {
        if (!mActiveManip) {
            print(writer, manip);
            mActiveManip = manip;
            return;
        }

        if (!manip->equals(mActiveManip)) {
            print(writer, manip);
            mActiveManip = manip;
            return;
        }

        mActiveManip = manip;
    }
    //------------------------------
}

//-------------------------------------------------------------------------

void ObjWriteManip::print(AbstractWriter * writer, const AttrManipBase * manip) {
    if (manip) {
        mManipCounter += manip->printObj(*writer);
    }
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

void ObjWriteManip::setPanelEnabled(const AttrCockpit & cockpit) {
    mIsPanelManip = true;
    mAttrManipPanel.setCockpit(cockpit);
    mActiveManip = &mAttrManipPanel;
}

void ObjWriteManip::setPanelDisabled() {
    mActiveManip = nullptr;
    mIsPanelManip = false;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
