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

#include <gtest/gtest.h>

#include <tuple>
#include <xpln/obj/manipulators/AttrManip.h>
#include <xpln/obj/ObjMesh.h>
#include <io/writer/ObjWriteAttr.h>
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

std::tuple<std::string, std::size_t> print(const AttrSet & attrSet) {
    TestWriter w;
    ObjMesh mesh;
    mesh.mAttr = attrSet;
    ObjWriteAttr attrWriter(std::make_shared<ObjState>());
    attrWriter.writeObjAttr(&w, &mesh);
    const auto [globNum, objNum, manipNum] = attrWriter.count();
    return std::make_tuple(w.mResult, manipNum);
}

template<typename T>
std::tuple<std::string, std::size_t> print(const T & manip) {
    AttrSet attrSet;
    attrSet.mManip = AttrManip(manip);
    return print(attrSet);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManip, AttrManipAxisKnob) {
    AttrManipAxisKnob manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mMin = 30.0f;
    manip.mMax = 40.0f;
    manip.mClickDelta = 10.0f;
    manip.mHoldDelta = 20.0f;

    auto result = std::string("ATTR_manip_axis_knob ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);
    ASSERT_EQ(EManipulator(EManipulator::axis_knob), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipAxisSwitchLeftRight) {
    AttrManipAxisSwitchLeftRight manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mMin = 30.0f;
    manip.mMax = 40.0f;
    manip.mClickDelta = 10.0f;
    manip.mHoldDelta = 20.0f;

    auto result = std::string("ATTR_manip_axis_switch_left_right ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);
    ASSERT_EQ(EManipulator(EManipulator::axis_switch_lr), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipAxisSwitchUpDown) {
    AttrManipAxisSwitchUpDown manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mMin = 30.0f;
    manip.mMax = 40.0f;
    manip.mClickDelta = 10.0f;
    manip.mHoldDelta = 20.0f;

    auto result = std::string("ATTR_manip_axis_switch_up_down ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);
    ASSERT_EQ(EManipulator(EManipulator::axis_switch_ud), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmd) {
    AttrManipCmd manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mCommand = "command";

    const auto result = std::string("ATTR_manip_command ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdAxis) {
    AttrManipCmdAxis manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mDirX = 10.0f;
    manip.mDirY = 20.0f;
    manip.mDirZ = 30.0f;

    manip.mPosCommand = "p-command";
    manip.mNegCommand = "n-command";

    const auto result = std::string("ATTR_manip_command_axis ")
                        .append(cursor.toString())
                        .append(" ")
                        .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                        .append("p-command n-command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command_axis), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdKnob) {
    AttrManipCmdKnob manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mPosCommand = "p-command";
    manip.mNegCommand = "n-command";

    const auto result = std::string("ATTR_manip_command_knob ")
                        .append(cursor.toString())
                        .append(" p-command n-command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command_knob), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdKnob2) {
    AttrManipCmdKnob2 manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mCommand = "command";

    const auto result = std::string("ATTR_manip_command_knob2 ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command_knob2), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchLeftRight) {
    AttrManipCmdSwitchLeftRight manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mPosCommand = "p-command";
    manip.mNegCommand = "n-command";

    const auto result = std::string("ATTR_manip_command_switch_left_right ")
                        .append(cursor.toString())
                        .append(" p-command n-command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command_switch_lr), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchLeftRight2) {
    AttrManipCmdSwitchLeftRight2 manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mCommand = "command";

    const auto result = std::string("ATTR_manip_command_switch_left_right2 ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command_switch_lr2), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchUpDown) {
    AttrManipCmdSwitchUpDown manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mPosCommand = "p-command";
    manip.mNegCommand = "n-command";

    const auto result = std::string("ATTR_manip_command_switch_up_down ")
                        .append(cursor.toString())
                        .append(" p-command n-command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command_switch_ud), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipCmdSwitchUpDown2) {
    AttrManipCmdSwitchUpDown2 manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mCommand = "command";

    const auto result = std::string("ATTR_manip_command_switch_up_down2 ")
                        .append(cursor.toString())
                        .append(" command ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::command_switch_ud2), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDelta) {
    AttrManipDelta manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mDown = 10.0f;
    manip.mHold = 20.0f;
    manip.mMin = 30.0f;
    manip.mMax = 40.0f;

    auto result = std::string("ATTR_manip_delta ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(2, number2);

    ASSERT_EQ(EManipulator(EManipulator::delta), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragAxis) {
    AttrManipDragAxis manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mDirX = 10.0f;
    manip.mDirY = 20.0f;
    manip.mDirZ = 30.0f;

    manip.mVal1 = 40.0f;
    manip.mVal2 = 50.0f;

    manip.mDataref = "dataref";

    auto result = std::string("ATTR_manip_drag_axis ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(50.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);
    manip.mAxisDetented = AttrAxisDetented(1.0f, 2.0f, 3.0f, 4.0, 5.0f, "dataref-2");;
    manip.mAxisDetentRanges = {AttrAxisDetentRange(1.0f, 2.0f, 3.0f), AttrAxisDetentRange(4.0f, 5.0f, 6.0f)};

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

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(5, number2);

    ASSERT_EQ(EManipulator(EManipulator::drag_axis), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragAxisPix) {
    AttrManipDragAxisPix manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mDxPix = 10;
    manip.mStep = 20;
    manip.mExp = 30.0f;
    manip.mVal1 = 40.0f;
    manip.mVal2 = 50.0f;

    auto result = std::string("ATTR_manip_drag_axis_pix ")
                  .append(cursor.toString()).append(" 10 20 ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(50.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(2, number2);

    ASSERT_EQ(EManipulator(EManipulator::drag_axis_pix), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragRotate) {
    AttrManipDragRotate manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mOriginX = 10.0f;
    manip.mOriginY = 20.0f;
    manip.mOriginZ = 30.0f;
    manip.mDirX = 40.0f;
    manip.mDirY = 50.0f;
    manip.mDirZ = 60.0f;
    manip.mAngle1 = 70.0f;
    manip.mAngle2 = 80.0f;
    manip.mLift = 90.0f;
    manip.mV1Min = 91.0f;
    manip.mV1Max = 92.0f;
    manip.mV2Min = 93.0f;
    manip.mV2Max = 94.0f;
    manip.mDataref1 = "dataref-1";
    manip.mDataref2 = "dataref-2";

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

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mKeys = {AttrManipKeyFrame(1.0f, 2.0f), AttrManipKeyFrame(3.0f, 4.0f)};
    manip.mAxisDetentRanges = {AttrAxisDetentRange(1.0f, 2.0f, 3.0f), AttrAxisDetentRange(4.0f, 5.0f, 6.0f)};

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

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(5, number2);

    ASSERT_EQ(EManipulator(EManipulator::drag_rotate), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipDragXy) {
    AttrManipDragXy manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";

    manip.mX = 10.0f;
    manip.mXDataref = "x-dataref";
    manip.mXMin = 1.0f;
    manip.mXMax = 2.0f;

    manip.mY = 20.0;
    manip.mYDataref = "y-dataref";
    manip.mYMin = 3.0f;
    manip.mYMax = 4.0f;

    auto result = std::string("ATTR_manip_drag_xy ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(1.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(2.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(3.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(4.0f, PRECISION)).append(" ")
                  .append("x-dataref y-dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(2, number2);

    ASSERT_EQ(EManipulator(EManipulator::drag_xy), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipNone) {
    // This test works only when cockpit attribute is enabled
    // because the algorithm blocks printing ATTR_manip_none
    // in incorrect cases.
    AttrSet set;
    set.mCockpit = AttrCockpit();
    set.mManip = AttrManip(AttrManipNone());

    const auto [printed, number] = print(set);
    EXPECT_EQ(1, number);
    EXPECT_STREQ("ATTR_cockpit\nATTR_manip_none\n", printed.c_str());

    ASSERT_EQ(EManipulator(EManipulator::none), AttrManipNone::mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipNoop) {
    AttrManipNoop manip;
    manip.mToolType = "ToolTip";

    const auto result = std::string("ATTR_manip_noop ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    ASSERT_EQ(EManipulator(EManipulator::noop), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipPanel) {
    // This test works only when cockpit attribute is enabled
    // because the algorithm blocks printing ATTR_manip_none
    // in incorrect cases.
    AttrSet set;
    set.mCockpit = AttrCockpit();
    set.mManip = AttrManip(AttrManipPanel(AttrCockpit(AttrCockpit::cockpit)));

    // the manipulator is printed as the cockpit attribute.
    const auto [printed, number] = print(set);
    ASSERT_STREQ("ATTR_cockpit\n", printed.c_str());
    ASSERT_EQ(0, number);
    ASSERT_EQ(EManipulator(EManipulator::panel), AttrManipPanel::mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipPush) {
    AttrManipPush manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mDown = 10.0f;
    manip.mUp = 20.0f;

    auto result = std::string("ATTR_manip_push ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(2, number2);

    ASSERT_EQ(EManipulator(EManipulator::push), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipRadio) {
    AttrManipRadio manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mDown = 10.0f;

    auto result = std::string("ATTR_manip_radio ")
                  .append(cursor.toString()).append(" ")
                  .append(sts::toMbString(10.0f, PRECISION))
                  .append(" dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(2, number2);

    ASSERT_EQ(EManipulator(EManipulator::radio), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipToggle) {
    AttrManipToggle manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mOn = 10.0f;
    manip.mOff = 20.0f;

    auto result = std::string("ATTR_manip_toggle ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(2, number2);

    ASSERT_EQ(EManipulator(EManipulator::toggle), manip.mType);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipWrap) {
    AttrManipWrap manip;
    const ECursor cursor(ECursor::eId::hand);
    manip.mCursor = cursor;
    manip.mToolType = "ToolTip";
    manip.mDataref = "dataref";

    manip.mDown = 10.0f;
    manip.mHold = 20.0f;
    manip.mMin = 30.0f;
    manip.mMax = 40.0f;

    auto result = std::string("ATTR_manip_wrap ")
                  .append(cursor.toString())
                  .append(" ")
                  .append(sts::toMbString(10.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(20.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(30.0f, PRECISION)).append(" ")
                  .append(sts::toMbString(40.0f, PRECISION)).append(" ")
                  .append("dataref ToolTip\n");

    const auto [printed, number] = print(manip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(1, number);

    manip.mWheel = AttrManipWheel(15.0f);

    result.append("ATTR_manip_wheel ")
          .append(sts::toMbString(15.0f, PRECISION))
          .append("\n");

    const auto [printed2, number2] = print(manip);
    ASSERT_STREQ(result.c_str(), printed2.c_str());
    ASSERT_EQ(2, number2);

    ASSERT_EQ(EManipulator(EManipulator::wrap), manip.mType);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManip, AttrAxisDetented) {
    AttrManipDragAxis rootManip;
    rootManip.mAxisDetented = AttrAxisDetented(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, "dataref");

    const auto result = std::string("ATTR_manip_drag_axis none 0.00000 0.00000 0.00000 0.00000 1.00000  \n")
                        .append("ATTR_axis_detented ")
                        .append(sts::toMbString(1.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(2.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(3.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(4.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(5.0f, PRECISION))
                        .append(" dataref\n");

    const auto [printed, number] = print(rootManip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(2, number);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrAxisDetentRange) {
    AttrManipDragRotate rootManip;
    rootManip.mAxisDetentRanges = {AttrAxisDetentRange(1.0f, 2.0f, 3.0f)};

    const auto result = std::string("ATTR_manip_drag_rotate none 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 1.00000 0.00000 1.00000   \n")
                        .append("ATTR_axis_detent_range ")
                        .append(sts::toMbString(1.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(2.0f, PRECISION)).append(" ")
                        .append(sts::toMbString(3.0f, PRECISION)).append("\n");

    const auto [printed, number] = print(rootManip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(2, number);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipWheel) {
    AttrManipToggle rootManip;
    rootManip.mWheel = AttrManipWheel(8.5f);

    const auto result = std::string("ATTR_manip_toggle none 0.00000 0.00000  \n")
                        .append("ATTR_manip_wheel ")
                        .append(sts::toMbString(8.5f, PRECISION))
                        .append("\n");

    const auto [printed, number] = print(rootManip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(2, number);
}

//-------------------------------------------------------------------------

TEST(TestManip, AttrManipKeyFrame) {
    AttrManipDragRotate rootManip;
    rootManip.mKeys = {AttrManipKeyFrame(8.5f, 10.6f)};

    const auto result = std::string("ATTR_manip_drag_rotate none 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 1.00000 0.00000 1.00000   \n")
                        .append("ATTR_manip_keyframe ")
                        .append(sts::toMbString(8.5f, PRECISION)).append(" ")
                        .append(sts::toMbString(10.6f, PRECISION)).append("\n");

    const auto [printed, number] = print(rootManip);
    ASSERT_STREQ(result.c_str(), printed.c_str());
    ASSERT_EQ(2, number);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
