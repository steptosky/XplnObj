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

#include "ph/stdafx.h"

#include "converters/ObjAttrManipString.h"

#include <xpln/obj/manipulators/AttrManipDragXy.h>
#include <xpln/obj/manipulators/AttrManipDragAxis.h>
#include <xpln/obj/manipulators/AttrManipCmd.h>
#include <xpln/obj/manipulators/AttrManipCmdAxis.h>
#include <xpln/obj/manipulators/AttrManipNoop.h>
#include <xpln/obj/manipulators/AttrManipPanel.h>
#include <xpln/obj/manipulators/AttrManipPush.h>
#include <xpln/obj/manipulators/AttrManipRadio.h>
#include <xpln/obj/manipulators/AttrManipToggle.h>
#include <xpln/obj/manipulators/AttrManipDelta.h>
#include <xpln/obj/manipulators/AttrManipWrap.h>
#include <xpln/obj/manipulators/AttrManipDragAxisPix.h>
#include <xpln/obj/manipulators/AttrManipAxisKnob.h>
#include <xpln/obj/manipulators/AttrManipAxisSwitchUpDown.h>
#include <xpln/obj/manipulators/AttrManipAxisSwitchLeftRight.h>
#include <xpln/obj/manipulators/AttrManipCmdKnob.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchLeftRight.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h>
#include <xpln/obj/manipulators/AttrManipNone.h>
#include <converters/Defines.h>
#include <sts/string/StringUtils.h>

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * This tests are for manipulators' setter/getter/states/strings conversion etc...
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManip, AttrManipBase) {
    AttrManipDragXy manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    // getters
    ASSERT_STREQ(cursor.toString(), manip.cursor().toString());
    ASSERT_STREQ("ToolTip", manip.toolTip().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManip, AttrManipAxisKnob) {
    AttrManipAxisKnob manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setClickDelta(10.0f);
    manip.setHoldDelta(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    ASSERT_STREQ(std::string("ATTR_manip_axis_knob ")
        .append(cursor.toString()).append(" ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append(sts::toMbString(40.0f, PRECISION)).append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.clickDelta());
    ASSERT_EQ(20.0f, manip.holdDelta());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::axis_knob), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipAxisSwitchLeftRight) {
    AttrManipAxisSwitchLeftRight manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setClickDelta(10.0f);
    manip.setHoldDelta(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    ASSERT_STREQ(std::string("ATTR_manip_axis_switch_left_right ")
        .append(cursor.toString()).append(" ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append(sts::toMbString(40.0f, PRECISION)).append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.clickDelta());
    ASSERT_EQ(20.0f, manip.holdDelta());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::axis_switch_lr), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipAxisSwitchUpDown) {
    AttrManipAxisSwitchUpDown manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setClickDelta(10.0f);
    manip.setHoldDelta(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    ASSERT_STREQ(std::string("ATTR_manip_axis_switch_up_down ")
        .append(cursor.toString()).append(" ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append(sts::toMbString(40.0f, PRECISION)).append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.clickDelta());
    ASSERT_EQ(20.0f, manip.holdDelta());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::axis_switch_ud), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmd) {
    AttrManipCmd manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setCommand("command");

    ASSERT_STREQ(std::string("ATTR_manip_command ").append(cursor.toString())
        .append(" command ToolTip").c_str(),
        toObjString(&manip).c_str());

    // getters
    ASSERT_STREQ("command", manip.command().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdAxis) {
    AttrManipCmdAxis manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setX(10.0f);
    manip.setY(20.0f);
    manip.setZ(30.0f);

    manip.setCmdPositive("pcommand");
    manip.setCmdNegative("ncommand");

    ASSERT_STREQ(std::string("ATTR_manip_command_axis ").append(cursor.toString())
        .append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append("pcommand ncommand ToolTip").c_str(),
        toObjString(&manip).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.x());
    ASSERT_EQ(20.0f, manip.y());
    ASSERT_EQ(30.0f, manip.z());
    ASSERT_STREQ("pcommand", manip.cmdPositive().c_str());
    ASSERT_STREQ("ncommand", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_axis), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdKnob) {
    AttrManipCmdKnob manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmdPositive("pcommand");
    manip.setCmdNegative("ncommand");

    ASSERT_STREQ(std::string("ATTR_manip_command_knob ").append(cursor.toString())
        .append(" pcommand ncommand ToolTip").c_str(),
        toObjString(&manip).c_str());

    // getters
    ASSERT_STREQ("pcommand", manip.cmdPositive().c_str());
    ASSERT_STREQ("ncommand", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_knob), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchLeftRight) {
    AttrManipCmdSwitchLeftRight manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmdPositive("pcommand");
    manip.setCmdNegative("ncommand");

    ASSERT_STREQ(std::string("ATTR_manip_switch_left_right ").append(cursor.toString())
        .append(" pcommand ncommand ToolTip").c_str(),
        toObjString(&manip).c_str());

    // getters
    ASSERT_STREQ("pcommand", manip.cmdPositive().c_str());
    ASSERT_STREQ("ncommand", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_switch_lr), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchUpDown) {
    AttrManipCmdSwitchUpDown manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmdPositive("pcommand");
    manip.setCmdNegative("ncommand");

    ASSERT_STREQ(std::string("ATTR_manip_switch_up_down ").append(cursor.toString())
        .append(" pcommand ncommand ToolTip").c_str(),
        toObjString(&manip).c_str());

    // getters
    ASSERT_STREQ("pcommand", manip.cmdPositive().c_str());
    ASSERT_STREQ("ncommand", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_switch_ud), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDelta) {
    AttrManipDelta manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);
    manip.setHold(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    ASSERT_STREQ(std::string("ATTR_manip_delta ")
        .append(cursor.toString())
        .append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append(sts::toMbString(40.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(20.0f, manip.hold());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::delta), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragAxis) {
    AttrManipDragAxis manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setX(10.0f);
    manip.setY(20.0f);
    manip.setZ(30.0f);

    manip.setVal1(40.0f);
    manip.setVal2(50.0f);

    manip.setDataref("dataref");

    ASSERT_STREQ(std::string("ATTR_manip_drag_axis ")
        .append(cursor.toString())
        .append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append(sts::toMbString(40.0f, PRECISION)).append(" ")
        .append(sts::toMbString(50.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.x());
    ASSERT_EQ(20.0f, manip.y());
    ASSERT_EQ(30.0f, manip.z());
    ASSERT_EQ(40.0f, manip.val1());
    ASSERT_EQ(50.0f, manip.val2());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::drag_axis), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragAxisPix) {
    AttrManipDragAxisPix manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDxPix(10);
    manip.setStep(20);
    manip.setExp(30.0f);
    manip.setVal1(40.0f);
    manip.setVal2(50.0f);

    ASSERT_STREQ(std::string("ATTR_manip_drag_axis_pix ")
        .append(cursor.toString()).append(" 10 20 ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append(sts::toMbString(40.0f, PRECISION)).append(" ")
        .append(sts::toMbString(50.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10, manip.dxPix());
    ASSERT_EQ(20, manip.step());
    ASSERT_EQ(30.0f, manip.exp());
    ASSERT_EQ(40.0f, manip.val1());
    ASSERT_EQ(50.0f, manip.val2());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::drag_axis_pix), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragXy) {
    AttrManipDragXy manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setX(10.0f);
    manip.setXDataref("xdataref");
    manip.setXMin(1.0f);
    manip.setXMax(2.0f);

    manip.setY(20.0);
    manip.setYDataref("ydataref");
    manip.setYMin(3.0f);
    manip.setYMax(4.0f);

    ASSERT_STREQ(std::string("ATTR_manip_drag_xy ").append(cursor.toString())
        .append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append(sts::toMbString(1.0f, PRECISION)).append(" ")
        .append(sts::toMbString(2.0f, PRECISION)).append(" ")
        .append(sts::toMbString(3.0f, PRECISION)).append(" ")
        .append(sts::toMbString(4.0f, PRECISION)).append(" ")
        .append("xdataref ydataref ToolTip").c_str(),
        toObjString(&manip).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.x());
    ASSERT_EQ(1.0f, manip.xMin());
    ASSERT_EQ(2.0f, manip.xMax());
    ASSERT_STREQ("xdataref", manip.xDataref().c_str());

    ASSERT_EQ(20.0f, manip.y());
    ASSERT_EQ(3.0f, manip.yMin());
    ASSERT_EQ(4.0f, manip.yMax());
    ASSERT_STREQ("ydataref", manip.yDataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::drag_xy), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipNoop) {
    AttrManipNoop manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    ASSERT_STREQ("ATTR_manip_noop", toObjString(&manip).c_str());

    ASSERT_EQ(EManipulator(EManipulator::noop), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipNone) {
    AttrManipNone manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    ASSERT_STREQ("ATTR_manip_none", toObjString(&manip).c_str());

    ASSERT_EQ(EManipulator(EManipulator::none), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipPanel) {
    AttrManipPanel manip;
    manip.setCockpit(AttrCockpit(AttrCockpit::cockpit));
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

#ifndef NDEBUG
    const char * res = "ATTR_cockpit ## panel manip";
#else
	const char * res = "ATTR_cockpit";
#endif

    ASSERT_STREQ(res, toObjString(&manip).c_str());

    ASSERT_EQ(EManipulator(EManipulator::panel), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipPush) {
    AttrManipPush manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);
    manip.setUp(20.0f);

    ASSERT_STREQ(std::string("ATTR_manip_push ")
        .append(cursor.toString())
        .append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(20.0f, manip.up());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::push), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipRadio) {
    AttrManipRadio manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);

    ASSERT_STREQ(std::string("ATTR_manip_radio ")
        .append(cursor.toString()).append(" ")
        .append(sts::toMbString(10.0f, PRECISION))
        .append(" dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::radio), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipToggle) {
    AttrManipToggle manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setOn(10.0f);
    manip.setOff(20.0f);

    ASSERT_STREQ(std::string("ATTR_manip_toggle ")
        .append(cursor.toString())
        .append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.on());
    ASSERT_EQ(20.0f, manip.off());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::toggle), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipWrap) {
    AttrManipWrap manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);
    manip.setHold(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    ASSERT_STREQ(std::string("ATTR_manip_wrap ")
        .append(cursor.toString())
        .append(" ")
        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
        .append(sts::toMbString(40.0f, PRECISION)).append(" ")
        .append("dataref ToolTip")
        .c_str(),
        toObjString(&manip).c_str());

    manip.setWheelEnabled(true);
    manip.setWheelDelta(15.0);

    ASSERT_STREQ(std::string("ATTR_manip_wheel ").append(sts::toMbString(15.0f, PRECISION)).c_str(), toObjString(static_cast<const AttrManipWheel &>(manip)).c_str());

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(20.0f, manip.hold());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheelDelta());
    ASSERT_TRUE(manip.isWheelEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::wrap), manip.type());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
