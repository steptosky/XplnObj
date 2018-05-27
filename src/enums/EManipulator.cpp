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

#include "xpln/enums/EManipulator.h"
#include "common/Logger.h"
#include "common/ArrayLength.h"
#include "common/AttributeNames.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

EManipulator::List EManipulator::mList;

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

namespace EManipulatorData {

    struct Data {
        const char * mUi;
        const char * mAttr;
        EManipulator::eId mId;

        Data(const char * attr, const char * ui, EManipulator::eId id)
            : mUi(ui),
              mAttr(attr),
              mId(id) {}
    };

    typedef std::pair<std::string, EManipulator::eId> Association;

    const Data gList[] = {
        /* 00 */ Data(ATTR_MANIP_NONE, "None", EManipulator::none),
        /* 01 */ Data(ATTR_MANIP_AXIS_KNOB, "Axis knob", EManipulator::axis_knob),
        /* 02 */ Data(ATTR_MANIP_AXIS_SWITCH_LEFT_RIGHT, "Axis switch left-right", EManipulator::axis_switch_lr),
        /* 03 */ Data(ATTR_MANIP_AXIS_SWITCH_UP_DOWN, "Axis switch up-down", EManipulator::axis_switch_ud),
        /* 04 */ Data(ATTR_MANIP_COMMAND, "Command", EManipulator::command),
        /* 02 */ Data(ATTR_MANIP_COMMAND_AXIS, "Command axis", EManipulator::command_axis),
        /* 06 */ Data(ATTR_MANIP_COMMAND_KNOB, "Command knob", EManipulator::command_knob),
        /* 07 */ Data(ATTR_MANIP_SWITCH_LEFT_RIGHT, "Command switch left-right", EManipulator::command_switch_lr),
        /* 08 */ Data(ATTR_MANIP_SWITCH_UP_DOWN, "Command switch up-down", EManipulator::command_switch_ud),
        /* 09 */ Data(ATTR_MANIP_DELTA, "Delta", EManipulator::delta),
        /* 10 */ Data(ATTR_MANIP_DRAG_AXIS, "Drag axis", EManipulator::drag_axis),
        /* 11 */ Data(ATTR_MANIP_DRAG_AXIS_PIX, "Drag axis pix", EManipulator::drag_axis_pix),
        /* 12 */ Data(ATTR_MANIP_DRAG_XY, "Drag xy", EManipulator::drag_xy),
        /* 13 */ Data(ATTR_MANIP_NOOP, "Noop", EManipulator::noop),
        /* 14 */ Data("manip_panel_click", "Panel-Click", EManipulator::panel),
        /* 15 */ Data(ATTR_MANIP_PUSH, "Push", EManipulator::push),
        /* 16 */ Data(ATTR_MANIP_RADIO, "Radio", EManipulator::radio),
        /* 17 */ Data(ATTR_MANIP_TOGGLE, "Toggle", EManipulator::toggle),
        /* 18 */ Data(ATTR_MANIP_WRAP, "Wrap", EManipulator::wrap),
    };
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

EManipulator::EManipulator()
    : EManipulator(none) { }

EManipulator::EManipulator(eId id)
    : mId(id) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool EManipulator::operator==(const EManipulator & other) const {
    return mId == other.mId;
}

bool EManipulator::operator==(eId id) const {
    return mId == id;
}

bool EManipulator::operator!=(const EManipulator & other) const {
    return mId != other.mId;
}

bool EManipulator::operator!=(eId id) const {
    return mId != id;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

EManipulator EManipulator::fromUiString(const char * name) {
    if (name) {
        for (size_t i = 0; i < ARRAY_LENGTH(EManipulatorData::gList); ++i) {
            if (strcmp(name, EManipulatorData::gList[i].mUi) == 0) {
                return EManipulator(EManipulatorData::gList[i].mId);
            }
        }
        LError << TOTEXT(EManipulator) << " Does not contain ui name: \"" << name << "\"";
    }
    return EManipulator();
}

EManipulator EManipulator::fromString(const char * attrName) {
    if (attrName) {
        for (size_t i = 0; i < ARRAY_LENGTH(EManipulatorData::gList); ++i) {
            if (strcmp(attrName, EManipulatorData::gList[i].mAttr) == 0) {
                return EManipulator(EManipulatorData::gList[i].mId);
            }
        }
        LError << TOTEXT(EManipulator) << " Does not contain attribute name: \"" << attrName << "\"";
    }
    return EManipulator();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void EManipulator::makeList(List & outList) {
    if (outList.empty()) {
        for (size_t i = 0; i < ARRAY_LENGTH(EManipulatorData::gList); ++i) {
            outList.emplace_back(EManipulator(EManipulatorData::gList[i].mId));
        }
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool EManipulator::isValid() const {
    return mId != none;
}

EManipulator::eId EManipulator::id() const {
    return mId;
}

const char * EManipulator::toString() const {
    return EManipulatorData::gList[static_cast<size_t>(mId)].mAttr;
}

const char * EManipulator::toUiString() const {
    return EManipulatorData::gList[static_cast<size_t>(mId)].mUi;
}

const EManipulator::List & EManipulator::list() {
    makeList(mList);
    return mList;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
