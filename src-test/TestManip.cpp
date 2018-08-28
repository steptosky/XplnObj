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

#include "ph/stdafx.h"
#include <gtest/gtest.h>

#include <xpln/obj/manipulators/AttrManipDragXy.h>
#include <xpln/obj/manipulators/AttrManipDragAxis.h>
#include <xpln/obj/manipulators/AttrManipDragRotate.h>
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
#include <xpln/obj/manipulators/AttrManipCmdKnob2.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchLeftRight.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchLeftRight2.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchUpDown2.h>
#include <xpln/obj/manipulators/AttrManipNone.h>
#include <xpln/obj/manipulators/AttrAxisDetented.h>
#include <xpln/obj/manipulators/AttrAxisDetentRange.h>
#include <converters/Defines.h>
#include <sts/string/StringUtils.h>
#include "TestWriter.h"

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

TEST(TestManip, AttrAxisDetented) {
    TestWriter w;
    AttrAxisDetented manip;
    manip.setDirectionX(1.0f);
    manip.setDirectionY(2.0f);
    manip.setDirectionZ(3.0f);

    manip.setVMin(4.0f);
    manip.setVMax(5.0f);
    manip.setDataref("dataref");

    const auto result = std::string("ATTR_axis_detented ")
                        .append(sts::toMbString(1.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(2.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(3.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(4.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(5.0f, PRECISION))
                        .append(" dataref\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_EQ(1.0f, manip.directionX());
    ASSERT_EQ(2.0f, manip.directionY());
    ASSERT_EQ(3.0f, manip.directionZ());
    ASSERT_EQ(4.0f, manip.vMin());
    ASSERT_EQ(5.0f, manip.vMax());
    ASSERT_STREQ("dataref", manip.dataref().c_str());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrAxisDetentRange) {
    TestWriter w;
    AttrAxisDetentRange manip;
    manip.setStart(1.0f);
    manip.setEnd(2.0f);
    manip.setHeight(3.0f);

    const auto result = std::string("ATTR_axis_detent_range ")
                        .append(sts::toMbString(1.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(2.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(3.0f, PRECISION)).append("\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_EQ(1.0f, manip.start());
    ASSERT_EQ(2.0f, manip.end());
    ASSERT_EQ(3.0f, manip.height());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipAxisKnob) {
    TestWriter w;
    AttrManipAxisKnob manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setClickDelta(10.0f);
    manip.setHoldDelta(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    auto result = std::string("ATTR_manip_axis_knob ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.clickDelta());
    ASSERT_EQ(20.0f, manip.holdDelta());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::axis_knob), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipAxisSwitchLeftRight) {
    TestWriter w;
    AttrManipAxisSwitchLeftRight manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setClickDelta(10.0f);
    manip.setHoldDelta(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    auto result = std::string("ATTR_manip_axis_switch_left_right ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.clickDelta());
    ASSERT_EQ(20.0f, manip.holdDelta());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::axis_switch_lr), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipAxisSwitchUpDown) {
    TestWriter w;
    AttrManipAxisSwitchUpDown manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setClickDelta(10.0f);
    manip.setHoldDelta(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    auto result = std::string("ATTR_manip_axis_switch_up_down ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.clickDelta());
    ASSERT_EQ(20.0f, manip.holdDelta());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::axis_switch_ud), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmd) {
    TestWriter w;
    AttrManipCmd manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setCmd("command");

    const auto result = std::string("ATTR_manip_command ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_STREQ("command", manip.cmd().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdAxis) {
    TestWriter w;
    AttrManipCmdAxis manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setDirectionX(10.0f);
    manip.setDirectionY(20.0f);
    manip.setDirectionZ(30.0f);

    manip.setCmdPositive("p-command");
    manip.setCmdNegative("n-command");

    const auto result = std::string("ATTR_manip_command_axis ")
                        .append(cursor.toString())
                        .append(" ")
                        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                        .append("p-command n-command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.directionX());
    ASSERT_EQ(20.0f, manip.directionY());
    ASSERT_EQ(30.0f, manip.directionZ());
    ASSERT_STREQ("p-command", manip.cmdPositive().c_str());
    ASSERT_STREQ("n-command", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_axis), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdKnob) {
    TestWriter w;
    AttrManipCmdKnob manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmdPositive("p-command");
    manip.setCmdNegative("n-command");

    const auto result = std::string("ATTR_manip_command_knob ")
                        .append(cursor.toString())
                        .append(" p-command n-command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_STREQ("p-command", manip.cmdPositive().c_str());
    ASSERT_STREQ("n-command", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_knob), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdKnob2) {
    TestWriter w;
    AttrManipCmdKnob2 manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmd("command");

    const auto result = std::string("ATTR_manip_command_knob2 ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_STREQ("command", manip.cmd().c_str());
    ASSERT_EQ(EManipulator(EManipulator::command_knob2), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchLeftRight) {
    TestWriter w;
    AttrManipCmdSwitchLeftRight manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmdPositive("p-command");
    manip.setCmdNegative("n-command");

    const auto result = std::string("ATTR_manip_command_switch_left_right ")
                        .append(cursor.toString())
                        .append(" p-command n-command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_STREQ("p-command", manip.cmdPositive().c_str());
    ASSERT_STREQ("n-command", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_switch_lr), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchLeftRight2) {
    TestWriter w;
    AttrManipCmdSwitchLeftRight2 manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmd("command");

    const auto result = std::string("ATTR_manip_command_switch_left_right2 ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_STREQ("command", manip.cmd().c_str());
    ASSERT_EQ(EManipulator(EManipulator::command_switch_lr2), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchUpDown) {
    TestWriter w;
    AttrManipCmdSwitchUpDown manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmdPositive("p-command");
    manip.setCmdNegative("n-command");

    const auto result = std::string("ATTR_manip_command_switch_up_down ")
                        .append(cursor.toString())
                        .append(" p-command n-command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_STREQ("p-command", manip.cmdPositive().c_str());
    ASSERT_STREQ("n-command", manip.cmdNegative().c_str());

    ASSERT_EQ(EManipulator(EManipulator::command_switch_ud), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchUpDown2) {
    TestWriter w;
    AttrManipCmdSwitchUpDown2 manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setCmd("command");

    const auto result = std::string("ATTR_manip_command_switch_up_down2 ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_STREQ("command", manip.cmd().c_str());
    ASSERT_EQ(EManipulator(EManipulator::command_switch_ud2), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDelta) {
    TestWriter w;
    AttrManipDelta manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);
    manip.setHold(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    auto result = std::string("ATTR_manip_delta ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(20.0f, manip.hold());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::delta), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragAxis) {
    TestWriter w;
    AttrManipDragAxis manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setDirectionX(10.0f);
    manip.setDirectionY(20.0f);
    manip.setDirectionZ(30.0f);

    manip.setVal1(40.0f);
    manip.setVal2(50.0f);

    manip.setDataref("dataref");

    auto result = std::string("ATTR_manip_drag_axis ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(50.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    AttrAxisDetented detented;
    detented.setDirection(1.0f, 2.0f, 3.0f);
    detented.setValue(4.0, 5.0f);
    detented.setDataref("dataref-2");
    manip.setAxisDetented(detented);
    manip.setDetentRanges({AttrAxisDetentRange(1.0f, 2.0f, 3.0f), AttrAxisDetentRange(4.0f, 5.0f, 6.0f)});

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n")
          .append("ATTR_axis_detented ")
          .append(sts::toMbString(1.0f, PRECISION)).append(" ")
          .append(sts::toMbString(2.0f, PRECISION)).append(" ")
          .append(sts::toMbString(3.0f, PRECISION)).append(" ")
          .append(sts::toMbString(4.0f, PRECISION)).append(" ")
          .append(sts::toMbString(5.0f, PRECISION)).append(" ")
          .append("dataref-2")
          .append("\n")
          .append("ATTR_axis_detent_range ")
          .append(sts::toMbString(1.0f, PRECISION)).append(" ")
          .append(sts::toMbString(2.0f, PRECISION)).append(" ")
          .append(sts::toMbString(3.0f, PRECISION))
          .append("\n")
          .append("ATTR_axis_detent_range ")
          .append(sts::toMbString(4.0f, PRECISION)).append(" ")
          .append(sts::toMbString(5.0f, PRECISION)).append(" ")
          .append(sts::toMbString(6.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(5, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.directionX());
    ASSERT_EQ(20.0f, manip.directionY());
    ASSERT_EQ(30.0f, manip.directionZ());
    ASSERT_EQ(40.0f, manip.val1());
    ASSERT_EQ(50.0f, manip.val2());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::drag_axis), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragAxisPix) {
    TestWriter w;
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

    auto result = std::string("ATTR_manip_drag_axis_pix ")
                  .append(cursor.toString()).append(" 10 20 ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(50.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10, manip.dxPix());
    ASSERT_EQ(20, manip.step());
    ASSERT_EQ(30.0f, manip.exp());
    ASSERT_EQ(40.0f, manip.val1());
    ASSERT_EQ(50.0f, manip.val2());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::drag_axis_pix), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragRotate) {
    TestWriter w;
    AttrManipDragRotate manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setOrigin(10.0f, 20.0f, 30.0f);
    manip.setDirection(40.0f, 50.0f, 60.0f);
    manip.setAngles(70.0f, 80.0f);
    manip.setLift(90.0f);
    manip.setV1(91.0f, 92.0f);
    manip.setV2(93.0f, 94.0f);
    manip.setDatarefs("dataref-1", "dataref-2");

    auto result = std::string("ATTR_manip_drag_rotate ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(50.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(60.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(70.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(80.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(90.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(91.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(92.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(93.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(94.0f, PRECISION)).append(" ")
                  .append("dataref-1 dataref-2 ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.originX());
    ASSERT_EQ(20.0f, manip.originY());
    ASSERT_EQ(30.0f, manip.originZ());
    ASSERT_EQ(40.0f, manip.directionX());
    ASSERT_EQ(50.0f, manip.directionY());
    ASSERT_EQ(60.0f, manip.directionZ());
    ASSERT_EQ(70.0f, manip.angle1());
    ASSERT_EQ(80.0f, manip.angle2());
    ASSERT_EQ(90.0f, manip.lift());
    ASSERT_EQ(91.0f, manip.v1Min());
    ASSERT_EQ(92.0f, manip.v1Max());
    ASSERT_EQ(93.0f, manip.v2Min());
    ASSERT_EQ(94.0f, manip.v2Max());
    ASSERT_STREQ("dataref-1", manip.dataref1().c_str());
    ASSERT_STREQ("dataref-2", manip.dataref2().c_str());

    ASSERT_EQ(EManipulator(EManipulator::drag_rotate), manip.type());

    manip.setKeys({AttrManipKeyFrame(1.0f, 2.0f), AttrManipKeyFrame(3.0f, 4.0f)});
    manip.setDetentRanges({AttrAxisDetentRange(1.0f, 2.0f, 3.0f), AttrAxisDetentRange(4.0f, 5.0f, 6.0f)});

    result.append("ATTR_manip_keyframe ")
          .append(sts::toMbString(1.0f, PRECISION)).append(" ")
          .append(sts::toMbString(2.0f, PRECISION)).append("\n")
          .append("ATTR_manip_keyframe ")
          .append(sts::toMbString(3.0f, PRECISION)).append(" ")
          .append(sts::toMbString(4.0f, PRECISION)).append("\n")
          .append("ATTR_axis_detent_range ")
          .append(sts::toMbString(1.0f, PRECISION)).append(" ")
          .append(sts::toMbString(2.0f, PRECISION)).append(" ")
          .append(sts::toMbString(3.0f, PRECISION)).append("\n")
          .append("ATTR_axis_detent_range ")
          .append(sts::toMbString(4.0f, PRECISION)).append(" ")
          .append(sts::toMbString(5.0f, PRECISION)).append(" ")
          .append(sts::toMbString(6.0f, PRECISION)).append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(5, manipCount);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragXy) {
    TestWriter w;
    AttrManipDragXy manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    manip.setX(10.0f);
    manip.setXDataref("x-dataref");
    manip.setXMin(1.0f);
    manip.setXMax(2.0f);

    manip.setY(20.0);
    manip.setYDataref("y-dataref");
    manip.setYMin(3.0f);
    manip.setYMax(4.0f);

    const auto result = std::string("ATTR_manip_drag_xy ")
                        .append(cursor.toString())
                        .append(" ")
                        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(1.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(2.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(3.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(4.0f, PRECISION)).append(" ")
                        .append("x-dataref y-dataref ToolTip\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.x());
    ASSERT_EQ(1.0f, manip.xMin());
    ASSERT_EQ(2.0f, manip.xMax());
    ASSERT_STREQ("x-dataref", manip.xDataref().c_str());

    ASSERT_EQ(20.0f, manip.y());
    ASSERT_EQ(3.0f, manip.yMin());
    ASSERT_EQ(4.0f, manip.yMax());
    ASSERT_STREQ("y-dataref", manip.yDataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::drag_xy), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipKeyFrame) {
    TestWriter w;
    AttrManipKeyFrame manip(5.1f, 6.8f);
    manip.setValue(8.5f);
    manip.setAngle(10.6f);

    const auto result = std::string("ATTR_manip_keyframe ")
                        .append(sts::toMbString(8.5f, PRECISION)).append(" ")
                        .append(sts::toMbString(10.6f, PRECISION)).append("\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_EQ(8.5f, manip.value());
    ASSERT_EQ(10.6f, manip.angle());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipNone) {
    TestWriter w;
    AttrManipNone manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    const auto result = std::string("ATTR_manip_none\n");
    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    ASSERT_EQ(EManipulator(EManipulator::none), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipNoop) {
    TestWriter w;
    AttrManipNoop manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

    const auto result = std::string("ATTR_manip_noop\n");
    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    ASSERT_EQ(EManipulator(EManipulator::noop), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipPanel) {
    TestWriter w;
    AttrManipPanel manip;
    manip.setCockpit(AttrCockpit(AttrCockpit::cockpit));
    const ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");

#ifndef NDEBUG
    auto result = std::string("ATTR_cockpit ## panel manip\n");
#else
    auto result = std::string("ATTR_cockpit\n");
#endif

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    ASSERT_EQ(EManipulator(EManipulator::panel), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipPush) {
    TestWriter w;
    AttrManipPush manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);
    manip.setUp(20.0f);

    auto result = std::string("ATTR_manip_push ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(20.0f, manip.up());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::push), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipRadio) {
    TestWriter w;
    AttrManipRadio manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);

    auto result = std::string("ATTR_manip_radio ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION))
                  .append(" dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::radio), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipToggle) {
    TestWriter w;
    AttrManipToggle manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setOn(10.0f);
    manip.setOff(20.0f);

    auto result = std::string("ATTR_manip_toggle ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.on());
    ASSERT_EQ(20.0f, manip.off());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::toggle), manip.type());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipWheel) {
    TestWriter w;
    AttrManipWheel manip(5.1f);
    manip.setDelta(8.5f);

    const auto result = std::string("ATTR_manip_wheel ")
                        .append(sts::toMbString(8.5f, PRECISION))
                        .append("\n");

    const auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    // getters
    ASSERT_TRUE( manip.isEnabled());
    ASSERT_EQ(8.5f, manip.delta());
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipWrap) {
    TestWriter w;
    AttrManipWrap manip;
    ECursor cursor(ECursor::eId::hand);
    manip.setCursor(cursor);
    manip.setToolTip("ToolTip");
    manip.setDataref("dataref");

    manip.setDown(10.0f);
    manip.setHold(20.0f);
    manip.setMinimum(30.0f);
    manip.setMaximum(40.0f);

    auto result = std::string("ATTR_manip_wrap ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    auto manipCount = manip.printObj(w);
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(1, manipCount);

    manip.wheel().setEnabled(true);
    manip.wheel().setDelta(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    manipCount = manip.printObj(w.clear());
    ASSERT_STREQ(result.c_str(), w.mResult.c_str());
    ASSERT_EQ(2, manipCount);

    // getters
    ASSERT_EQ(10.0f, manip.down());
    ASSERT_EQ(20.0f, manip.hold());
    ASSERT_EQ(30.0f, manip.minimum());
    ASSERT_EQ(40.0f, manip.maximum());
    ASSERT_EQ(15.0f, manip.wheel().delta());
    ASSERT_TRUE(manip.wheel().isEnabled());
    ASSERT_STREQ("dataref", manip.dataref().c_str());

    ASSERT_EQ(EManipulator(EManipulator::wrap), manip.type());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
