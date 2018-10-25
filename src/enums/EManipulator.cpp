/*
**  Copyright(C) 2018, StepToSky
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

#include <cstring>

#include "xpln/enums/EManipulator.h"
#include "common/ArrayLength.h"
#include "common/AttributeNames.h"
#include "common/Logger.h"

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

        Data(const char * attr, const char * ui, const EManipulator::eId id)
            : mUi(ui),
              mAttr(attr),
              mId(id) {}
    };

    typedef std::pair<std::string, EManipulator::eId> Association;

    // WARNING !!! Indexes are coordinated with the enum values !!!
    const Data gList[] = {
        /* 00 */ Data(ATTR_MANIP_NONE, "None", EManipulator::none),
        /* 01 */ Data(ATTR_MANIP_AXIS_KNOB, "Axis knob", EManipulator::axis_knob),
        /* 02 */ Data(ATTR_MANIP_AXIS_SWITCH_LEFT_RIGHT, "Axis switch left-right", EManipulator::axis_switch_lr),
        /* 03 */ Data(ATTR_MANIP_AXIS_SWITCH_UP_DOWN, "Axis switch up-down", EManipulator::axis_switch_ud),
        /* 04 */ Data(ATTR_MANIP_COMMAND, "Cmd", EManipulator::command),
        /* 05 */ Data(ATTR_MANIP_COMMAND_AXIS, "Cmd axis", EManipulator::command_axis),
        /* 06 */ Data(ATTR_MANIP_COMMAND_KNOB, "Cmd knob", EManipulator::command_knob),
        /* 07 */ Data(ATTR_MANIP_COMMAND_KNOB2, "Cmd knob2", EManipulator::command_knob2),
        /* 08 */ Data(ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT, "Cmd switch left-right", EManipulator::command_switch_lr),
        /* 09 */ Data(ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT2, "Cmd switch left-right2", EManipulator::command_switch_lr2),
        /* 10 */ Data(ATTR_MANIP_COMMAND_SWITCH_UP_DOWN, "Cmd switch up-down", EManipulator::command_switch_ud),
        /* 11 */ Data(ATTR_MANIP_COMMAND_SWITCH_UP_DOWN2, "Cmd switch up-down2", EManipulator::command_switch_ud2),
        /* 12 */ Data(ATTR_MANIP_DELTA, "Delta", EManipulator::delta),
        /* 13 */ Data(ATTR_MANIP_DRAG_AXIS, "Drag axis", EManipulator::drag_axis),
        /* 14 */ Data(ATTR_MANIP_DRAG_ROTATE, "Drag rotate", EManipulator::drag_rotate),
        /* 15 */ Data(ATTR_MANIP_DRAG_AXIS_PIX, "Drag axis pix", EManipulator::drag_axis_pix),
        /* 16 */ Data(ATTR_MANIP_DRAG_XY, "Drag xy", EManipulator::drag_xy),
        /* 17 */ Data(ATTR_MANIP_NOOP, "Noop", EManipulator::noop),
        /* 18 */ Data("manip_panel_click", "Panel-Click", EManipulator::panel),
        /* 19 */ Data(ATTR_MANIP_PUSH, "Push", EManipulator::push),
        /* 20 */ Data(ATTR_MANIP_RADIO, "Radio", EManipulator::radio),
        /* 21 */ Data(ATTR_MANIP_TOGGLE, "Toggle", EManipulator::toggle),
        /* 22 */ Data(ATTR_MANIP_WRAP, "Wrap", EManipulator::wrap),
    };
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

EManipulator::EManipulator()
    : EManipulator(none) { }

EManipulator::EManipulator(const eId id)
    : mId(id) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool EManipulator::operator==(const EManipulator & other) const {
    return mId == other.mId;
}

bool EManipulator::operator==(const eId id) const {
    return mId == id;
}

bool EManipulator::operator!=(const EManipulator & other) const {
    return mId != other.mId;
}

bool EManipulator::operator!=(const eId id) const {
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
        //-----------------------------------------------------
        // backward compatibility fixes for attribute name fix.
        // Read the tests for more information.
        if (strcmp(attrName, "ATTR_manip_switch_up_down") == 0) {
            attrName = ATTR_MANIP_COMMAND_SWITCH_UP_DOWN;
        }
        else if (strcmp(attrName, "ATTR_manip_switch_left_right") == 0) {
            attrName = ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT;
        }
        //-----------------------------------------------------
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
