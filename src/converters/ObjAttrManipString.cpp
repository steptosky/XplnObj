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

#include "ObjAttrManipString.h"
#include "common/AttributeNames.h"
#include "xpln/obj/manipulators/AttrManipDragXy.h"
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
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
#include "xpln/obj/manipulators/AttrManipCmdSwitchLeftRight.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h"
#include "StringStream.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const AttrManipBase * inVal) {
		switch (inVal->type().id()) {
			case EManipulator::axis_knob:
				return toObjString(*static_cast<const AttrManipAxisKnob*>(inVal));
			case EManipulator::axis_switch_lr:
				return toObjString(*static_cast<const AttrManipAxisSwitchLeftRight*>(inVal));
			case EManipulator::axis_switch_ud:
				return toObjString(*static_cast<const AttrManipAxisSwitchUpDown*>(inVal));
			case EManipulator::eId::command:
				return toObjString(*static_cast<const AttrManipCmd*>(inVal));
			case EManipulator::eId::command_axis:
				return toObjString(*static_cast<const AttrManipCmdAxis*>(inVal));
			case EManipulator::command_knob:
				return toObjString(*static_cast<const AttrManipCmdKnob*>(inVal));
			case EManipulator::command_switch_lr:
				return toObjString(*static_cast<const AttrManipCmdSwitchLeftRight*>(inVal));
			case EManipulator::command_switch_ud:
				return toObjString(*static_cast<const AttrManipCmdSwitchUpDown*>(inVal));
			case EManipulator::eId::delta:
				return toObjString(*static_cast<const AttrManipDelta*>(inVal));
			case EManipulator::eId::drag_axis:
				return toObjString(*static_cast<const AttrManipDragAxis*>(inVal));
			case EManipulator::eId::drag_axis_pix:
				return toObjString(*static_cast<const AttrManipDragAxisPix*>(inVal));
			case EManipulator::eId::drag_xy:
				return toObjString(*static_cast<const AttrManipDragXy*>(inVal));
			case EManipulator::eId::noop:
				return toObjString(*static_cast<const AttrManipNoop*>(inVal));
			case EManipulator::eId::push:
				return toObjString(*static_cast<const AttrManipPush*>(inVal));
			case EManipulator::eId::radio:
				return toObjString(*static_cast<const AttrManipRadio*>(inVal));
			case EManipulator::eId::toggle:
				return toObjString(*static_cast<const AttrManipToggle*>(inVal));
			case EManipulator::eId::wrap:
				return toObjString(*static_cast<const AttrManipWrap*>(inVal));
			case EManipulator::eId::none:
			default:
				return std::string();
		}
	}

	std::string toObjString(const AttrManipAxisKnob & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_AXIS_KNOB;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.minimum();
		outStr << " " << inVal.maximum();
		outStr << " " << inVal.clickDelta();
		outStr << " " << inVal.holdDelta();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipAxisSwitchLeftRight & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_AXIS_SWITCH_LEFT_RIGHT;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.minimum();
		outStr << " " << inVal.maximum();
		outStr << " " << inVal.clickDelta();
		outStr << " " << inVal.holdDelta();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipAxisSwitchUpDown & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_AXIS_SWITCH_UP_DOWN;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.minimum();
		outStr << " " << inVal.maximum();
		outStr << " " << inVal.clickDelta();
		outStr << " " << inVal.holdDelta();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipCmd & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_COMMAND;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.command();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipCmdAxis & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_COMMAND_AXIS;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.x();
		outStr << " " << inVal.y();
		outStr << " " << inVal.z();
		outStr << " " << inVal.cmdPositive();
		outStr << " " << inVal.cmdNegative();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipCmdKnob & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_COMMAND_KNOB;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.cmdPositive();
		outStr << " " << inVal.cmdNegative();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipCmdSwitchLeftRight & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_SWITCH_LEFT_RIGHT;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.cmdPositive();
		outStr << " " << inVal.cmdNegative();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipCmdSwitchUpDown & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_SWITCH_UP_DOWN;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.cmdPositive();
		outStr << " " << inVal.cmdNegative();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipDelta & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_DELTA;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.down();
		outStr << " " << inVal.hold();
		outStr << " " << inVal.minimum();
		outStr << " " << inVal.maximum();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipDragAxis & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_DRAG_AXIS;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.x();
		outStr << " " << inVal.y();
		outStr << " " << inVal.z();
		outStr << " " << inVal.val1();
		outStr << " " << inVal.val2();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipDragAxisPix & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_DRAG_AXIS_PIX;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.dxPix();
		outStr << " " << inVal.step();
		outStr << " " << inVal.exp();
		outStr << " " << inVal.val1();
		outStr << " " << inVal.val2();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipDragXy & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_DRAG_XY;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.x();
		outStr << " " << inVal.y();
		outStr << " " << inVal.xMin();
		outStr << " " << inVal.xMax();
		outStr << " " << inVal.yMin();
		outStr << " " << inVal.yMax();
		outStr << " " << inVal.xDataref();
		outStr << " " << inVal.yDataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipNoop & /* inVal */) {
		return std::string(ATTR_MANIP_NOOP);
	}

	std::string toObjString(const AttrManipPush & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_PUSH;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.down();
		outStr << " " << inVal.up();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipRadio & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_RADIO;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.down();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipToggle & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_TOGGLE;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.on();
		outStr << " " << inVal.off();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipWrap & inVal) {
		StringStream outStr;
		outStr << ATTR_MANIP_WRAP;
		outStr << " " << inVal.cursor().toString();
		outStr << " " << inVal.down();
		outStr << " " << inVal.hold();
		outStr << " " << inVal.minimum();
		outStr << " " << inVal.maximum();
		outStr << " " << inVal.dataref();
		outStr << " " << inVal.toolTip();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrManipWheel & inVal) {
		if (inVal.isWheelEnabled()) {
			StringStream outStr;
			outStr << ATTR_MANIP_WHEEL;
			outStr << " " << inVal.wheelDelta();
			outStr.flush();
			return outStr.str();
		}
		return "";
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
