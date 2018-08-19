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

#include "stdafx.h"

#include "ObjAttrManipString.h"
#include "common/AttributeNames.h"
#include "xpln/obj/manipulators/AttrManipDragXy.h"
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/obj/manipulators/AttrManipDragRotate.h"
#include "xpln/obj/manipulators/AttrManipCmd.h"
#include "xpln/obj/manipulators/AttrManipCmdAxis.h"
#include "xpln/obj/manipulators/AttrManipNoop.h"
#include "xpln/obj/manipulators/AttrManipPush.h"
#include "xpln/obj/manipulators/AttrManipRadio.h"
#include "xpln/obj/manipulators/AttrManipToggle.h"
#include "xpln/obj/manipulators/AttrManipDelta.h"
#include "xpln/obj/manipulators/AttrManipWrap.h"
#include "xpln/obj/manipulators/AttrManipDragAxisPix.h"
#include "xpln/obj/manipulators/AttrManipAxisKnob.h"
#include "xpln/obj/manipulators/AttrManipAxisSwitchLeftRight.h"
#include "xpln/obj/manipulators/AttrManipAxisSwitchUpDown.h"
#include "xpln/obj/manipulators/AttrManipCmdKnob.h"
#include "xpln/obj/manipulators/AttrManipCmdKnob2.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchLeftRight.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchLeftRight2.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchUpDown2.h"
#include "xpln/obj/manipulators/AttrManipNone.h"
#include "xpln/obj/manipulators/AttrManipPanel.h"

#include "ObjAttrString.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

std::string toObjString(const AttrManipBase * manip) {
    switch (manip->type().id()) {
        case EManipulator::axis_knob:
            return toObjString(*static_cast<const AttrManipAxisKnob*>(manip));
        case EManipulator::axis_switch_lr:
            return toObjString(*static_cast<const AttrManipAxisSwitchLeftRight*>(manip));
        case EManipulator::axis_switch_ud:
            return toObjString(*static_cast<const AttrManipAxisSwitchUpDown*>(manip));
        case EManipulator::eId::command:
            return toObjString(*static_cast<const AttrManipCmd*>(manip));
        case EManipulator::eId::command_axis:
            return toObjString(*static_cast<const AttrManipCmdAxis*>(manip));
        case EManipulator::command_knob:
            return toObjString(*static_cast<const AttrManipCmdKnob*>(manip));
        case EManipulator::command_knob2:
            return toObjString(*static_cast<const AttrManipCmdKnob2*>(manip));
        case EManipulator::command_switch_lr:
            return toObjString(*static_cast<const AttrManipCmdSwitchLeftRight*>(manip));
        case EManipulator::command_switch_lr2:
            return toObjString(*static_cast<const AttrManipCmdSwitchLeftRight2*>(manip));
        case EManipulator::command_switch_ud:
            return toObjString(*static_cast<const AttrManipCmdSwitchUpDown*>(manip));
        case EManipulator::command_switch_ud2:
            return toObjString(*static_cast<const AttrManipCmdSwitchUpDown2*>(manip));
        case EManipulator::eId::delta:
            return toObjString(*static_cast<const AttrManipDelta*>(manip));
        case EManipulator::eId::drag_axis:
            return toObjString(*static_cast<const AttrManipDragAxis*>(manip));
        case EManipulator::eId::drag_rotate:
            return toObjString(*static_cast<const AttrManipDragRotate*>(manip));
        case EManipulator::eId::drag_axis_pix:
            return toObjString(*static_cast<const AttrManipDragAxisPix*>(manip));
        case EManipulator::eId::drag_xy:
            return toObjString(*static_cast<const AttrManipDragXy*>(manip));
        case EManipulator::eId::noop:
            return toObjString(*static_cast<const AttrManipNoop*>(manip));
        case EManipulator::eId::panel:
            return toObjString(*static_cast<const AttrManipPanel*>(manip));
        case EManipulator::eId::push:
            return toObjString(*static_cast<const AttrManipPush*>(manip));
        case EManipulator::eId::radio:
            return toObjString(*static_cast<const AttrManipRadio*>(manip));
        case EManipulator::eId::toggle:
            return toObjString(*static_cast<const AttrManipToggle*>(manip));
        case EManipulator::eId::wrap:
            return toObjString(*static_cast<const AttrManipWrap*>(manip));
        case EManipulator::eId::none:
            return toObjString(*static_cast<const AttrManipNone*>(manip));
        default:
            return std::string();
    }
}

std::string toObjString(const AttrManipNone &) {
    return std::string(ATTR_MANIP_NONE);
}

std::string toObjString(const AttrManipAxisKnob & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_AXIS_KNOB;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.minimum();
    outStr << " " << manip.maximum();
    outStr << " " << manip.clickDelta();
    outStr << " " << manip.holdDelta();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipAxisSwitchLeftRight & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_AXIS_SWITCH_LEFT_RIGHT;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.minimum();
    outStr << " " << manip.maximum();
    outStr << " " << manip.clickDelta();
    outStr << " " << manip.holdDelta();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipAxisSwitchUpDown & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_AXIS_SWITCH_UP_DOWN;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.minimum();
    outStr << " " << manip.maximum();
    outStr << " " << manip.clickDelta();
    outStr << " " << manip.holdDelta();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmd & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.command();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmdAxis & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_AXIS;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.x();
    outStr << " " << manip.y();
    outStr << " " << manip.z();
    outStr << " " << manip.cmdPositive();
    outStr << " " << manip.cmdNegative();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmdKnob & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_KNOB;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.cmdPositive();
    outStr << " " << manip.cmdNegative();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmdKnob2 & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_KNOB2;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.cmd();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmdSwitchLeftRight & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.cmdPositive();
    outStr << " " << manip.cmdNegative();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmdSwitchLeftRight2 & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT2;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.cmd();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmdSwitchUpDown & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_SWITCH_UP_DOWN;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.cmdPositive();
    outStr << " " << manip.cmdNegative();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipCmdSwitchUpDown2 & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_SWITCH_UP_DOWN2;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.cmd();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipDelta & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_DELTA;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.down();
    outStr << " " << manip.hold();
    outStr << " " << manip.minimum();
    outStr << " " << manip.maximum();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipDragAxis & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_DRAG_AXIS;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.x();
    outStr << " " << manip.y();
    outStr << " " << manip.z();
    outStr << " " << manip.val1();
    outStr << " " << manip.val2();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipDragRotate & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_DRAG_ROTATE;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.x();
    outStr << " " << manip.y();
    outStr << " " << manip.z();
    outStr << " " << manip.directionX();
    outStr << " " << manip.directionY();
    outStr << " " << manip.directionZ();
    outStr << " " << manip.angle1();
    outStr << " " << manip.angle2();
    outStr << " " << manip.lift();
    outStr << " " << manip.v1Min();
    outStr << " " << manip.v1Max();
    outStr << " " << manip.v2Min();
    outStr << " " << manip.v2Max();
    outStr << " " << manip.dataref1();
    outStr << " " << manip.dataref2();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipDragAxisPix & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_DRAG_AXIS_PIX;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.dxPix();
    outStr << " " << manip.step();
    outStr << " " << manip.exp();
    outStr << " " << manip.val1();
    outStr << " " << manip.val2();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipDragXy & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_DRAG_XY;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.x();
    outStr << " " << manip.y();
    outStr << " " << manip.xMin();
    outStr << " " << manip.xMax();
    outStr << " " << manip.yMin();
    outStr << " " << manip.yMax();
    outStr << " " << manip.xDataref();
    outStr << " " << manip.yDataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipNoop &) {
    return std::string(ATTR_MANIP_NOOP);
}

std::string toObjString(const AttrManipPanel & manip) {
    StringStream outStr;
    outStr << toObjString(manip.cockpit());
#ifndef NDEBUG
    outStr << " ## panel manip";
#endif
    return outStr.str();
}

std::string toObjString(const AttrManipPush & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_PUSH;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.down();
    outStr << " " << manip.up();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipRadio & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_RADIO;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.down();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipToggle & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_TOGGLE;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.on();
    outStr << " " << manip.off();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipWrap & manip) {
    StringStream outStr;
    outStr << ATTR_MANIP_WRAP;
    outStr << " " << manip.cursor().toString();
    outStr << " " << manip.down();
    outStr << " " << manip.hold();
    outStr << " " << manip.minimum();
    outStr << " " << manip.maximum();
    outStr << " " << manip.dataref();
    outStr << " " << manip.toolTip();
    return outStr.str();
}

std::string toObjString(const AttrManipWheel & manip) {
    if (manip.isWheelEnabled()) {
        StringStream outStr;
        outStr << ATTR_MANIP_WHEEL;
        outStr << " " << manip.wheelDelta();
        return outStr.str();
    }
    return "";
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
