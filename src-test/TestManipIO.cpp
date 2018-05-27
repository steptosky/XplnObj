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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "common/Logger.h"
#include "xpln/obj/ObjMain.h"
#include "xpln/obj/ObjMesh.h"

#include "TestUtilsObjMesh.h"
#include <xpln/obj/manipulators/AttrManipDelta.h>
#include <xpln/obj/manipulators/AttrManipDragAxis.h>
#include <xpln/obj/manipulators/AttrManipDragAxisPix.h>
#include <xpln/obj/manipulators/AttrManipDragXy.h>
#include <xpln/obj/manipulators/AttrManipNoop.h>
#include <xpln/obj/manipulators/AttrManipPush.h>
#include <xpln/obj/manipulators/AttrManipRadio.h>
#include <xpln/obj/manipulators/AttrManipToggle.h>
#include <xpln/obj/manipulators/AttrManipWrap.h>
#include <xpln/obj/manipulators/AttrManipCmd.h>
#include <xpln/obj/manipulators/AttrManipCmdAxis.h>
#include <xpln/obj/manipulators/AttrManipAxisKnob.h>
#include <xpln/obj/manipulators/AttrManipAxisSwitchLeftRight.h>
#include <xpln/obj/manipulators/AttrManipAxisSwitchUpDown.h>
#include <xpln/obj/manipulators/AttrManipCmdKnob.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchLeftRight.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h>

using namespace xobj;
using ::testing::_;
using ::testing::StrEq;
using ::testing::InSequence;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/* 
 * This tests are for checking mnipulators of the chain 'mesh object->file | file->mesh object'.
 * So they test the writter and reader for mnipulators of one mesh object.
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<typename MANIP>
void extractManip(const ObjMain & inMain, EManipulator::eId inManipType, const MANIP *& outAttr) {
    ASSERT_EQ(1, inMain.lodCount());
    const ObjLodGroup & inLGroup = inMain.lod(0);
    ASSERT_EQ(1, inLGroup.transform().objList().size());
    ObjAbstract * obj = *(inLGroup.transform().objList().begin());
    ASSERT_EQ(eObjectType::OBJ_MESH, obj->objType());
    ObjMesh * inM = static_cast<ObjMesh *>(obj);
    ASSERT_TRUE(inM->pAttr.manipulator() != nullptr);
    ASSERT_EQ(EManipulator(inManipType), inM->pAttr.manipulator()->type());
    outAttr = static_cast<const MANIP *>(inM->pAttr.manipulator());
}

void addManip(ObjMain & inOutMain, AttrManipBase * inManip) {
    ObjMesh * outM = TestUtilsObjMesh::createObjMesh("m1", 0.0);
    ObjLodGroup & outLGroup = inOutMain.addLod();
    outLGroup.transform().addObject(outM);
    outM->pAttr.setManipulator(inManip);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisKnob) {
    AttrManipAxisKnob * outManip = new AttrManipAxisKnob;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setClickDelta(20.0f);
    outManip->setHoldDelta(30.0f);
    outManip->setMinimum(40.0f);
    outManip->setMaximum(50.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipAxisKnob * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisKnob>(inObj, EManipulator::axis_knob, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->clickDelta(), inManip->clickDelta());
    ASSERT_EQ(outManip->holdDelta(), inManip->holdDelta());
    ASSERT_EQ(outManip->minimum(), inManip->minimum());
    ASSERT_EQ(outManip->maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisKnob>(inWheelObj, EManipulator::axis_knob, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisSwitchLeftRight) {
    AttrManipAxisSwitchLeftRight * outManip = new AttrManipAxisSwitchLeftRight;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setClickDelta(20.0f);
    outManip->setHoldDelta(30.0f);
    outManip->setMinimum(40.0f);
    outManip->setMaximum(50.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipAxisSwitchLeftRight * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchLeftRight>(inObj, EManipulator::axis_switch_lr, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->clickDelta(), inManip->clickDelta());
    ASSERT_EQ(outManip->holdDelta(), inManip->holdDelta());
    ASSERT_EQ(outManip->minimum(), inManip->minimum());
    ASSERT_EQ(outManip->maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchLeftRight>(inWheelObj, EManipulator::axis_switch_lr, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisSwitchUpDown) {
    AttrManipAxisSwitchUpDown * outManip = new AttrManipAxisSwitchUpDown;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setClickDelta(20.0f);
    outManip->setHoldDelta(30.0f);
    outManip->setMinimum(40.0f);
    outManip->setMaximum(50.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipAxisSwitchUpDown * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchUpDown>(inObj, EManipulator::axis_switch_ud, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->clickDelta(), inManip->clickDelta());
    ASSERT_EQ(outManip->holdDelta(), inManip->holdDelta());
    ASSERT_EQ(outManip->minimum(), inManip->minimum());
    ASSERT_EQ(outManip->maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchUpDown>(inWheelObj, EManipulator::axis_switch_ud, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmd) {
    AttrManipCmd * outManip = new AttrManipCmd;
    outManip->setCursor(ECursor(ECursor::left));
    outManip->setToolTip("ToolTip");
    outManip->setCommand("Im/a/Command");

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipCmd * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmd>(inObj, EManipulator::command, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->command().c_str(), inManip->command().c_str());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdAxis) {
    AttrManipCmdAxis * outManip = new AttrManipCmdAxis;
    outManip->setCursor(ECursor(ECursor::left));
    outManip->setToolTip("ToolTip");
    outManip->setCmdNegative("Im/a/Negative/Command");
    outManip->setCmdPositive("Im/a/Positive/Command");
    outManip->setX(5.0f);
    outManip->setY(10.0f);
    outManip->setZ(20.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipCmdAxis * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdAxis>(inObj, EManipulator::command_axis, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_EQ(outManip->x(), inManip->x());
    ASSERT_EQ(outManip->y(), inManip->y());
    ASSERT_EQ(outManip->z(), inManip->z());
    ASSERT_STREQ(outManip->cmdNegative().c_str() ,inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip->cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdKnob) {
    AttrManipCmdKnob * outManip = new AttrManipCmdKnob;
    outManip->setCursor(ECursor(ECursor::left));
    outManip->setToolTip("ToolTip");
    outManip->setCmdNegative("Im/a/Negative/Command");
    outManip->setCmdPositive("Im/a/Positive/Command");

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipCmdKnob * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdKnob>(inObj, EManipulator::command_knob, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->cmdNegative().c_str(), inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip->cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchLeftRight) {
    AttrManipCmdSwitchLeftRight * outManip = new AttrManipCmdSwitchLeftRight;
    outManip->setCursor(ECursor(ECursor::left));
    outManip->setToolTip("ToolTip");
    outManip->setCmdNegative("Im/a/Negative/Command");
    outManip->setCmdPositive("Im/a/Positive/Command");

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipCmdSwitchLeftRight * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdSwitchLeftRight>(inObj, EManipulator::command_switch_lr, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->cmdNegative().c_str(), inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip->cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchUpDown) {
    AttrManipCmdSwitchUpDown * outManip = new AttrManipCmdSwitchUpDown;
    outManip->setCursor(ECursor(ECursor::left));
    outManip->setToolTip("ToolTip");
    outManip->setCmdNegative("Im/a/Negative/Command");
    outManip->setCmdPositive("Im/a/Positive/Command");

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipCmdSwitchUpDown * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdSwitchUpDown>(inObj, EManipulator::command_switch_ud, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->cmdNegative().c_str(), inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip->cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipDelta) {
    AttrManipDelta * outManip = new AttrManipDelta;
    outManip->setCursor(ECursor(ECursor::left));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setDown(5.0f);
    outManip->setHold(10.0f);
    outManip->setMinimum(20.0f);
    outManip->setMaximum(30.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipDelta * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDelta>(inObj, EManipulator::delta, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->down(), inManip->down());
    ASSERT_EQ(outManip->hold(), inManip->hold());
    ASSERT_EQ(outManip->minimum(), inManip->minimum());
    ASSERT_EQ(outManip->maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDelta>(inWheelObj, EManipulator::delta, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragAxis) {
    AttrManipDragAxis * outManip = new AttrManipDragAxis;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setX(5.0f);
    outManip->setY(10.0f);
    outManip->setZ(20.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipDragAxis * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragAxis>(inObj, EManipulator::drag_axis, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->x(), inManip->x());
    ASSERT_EQ(outManip->y(), inManip->y());
    ASSERT_EQ(outManip->z(), inManip->z());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragAxis>(inWheelObj, EManipulator::drag_axis, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragAxisPix) {
    AttrManipDragAxisPix * outManip = new AttrManipDragAxisPix;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setDxPix(1);
    outManip->setStep(2);
    outManip->setExp(20.0f);
    outManip->setVal1(30.0f);
    outManip->setVal2(40.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipDragAxisPix * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragAxisPix>(inObj, EManipulator::drag_axis_pix, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->dxPix(), inManip->dxPix());
    ASSERT_EQ(outManip->step(), inManip->step());
    ASSERT_EQ(outManip->exp(), inManip->exp());
    ASSERT_EQ(outManip->val1(), inManip->val1());
    ASSERT_EQ(outManip->val2(), inManip->val2());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragAxisPix>(inWheelObj, EManipulator::drag_axis_pix, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragXy) {
    AttrManipDragXy * outManip = new AttrManipDragXy;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setXDataref("Im/a/dataref/X");
    outManip->setYDataref("Im/a/dataref/Y");
    outManip->setX(20.0f);
    outManip->setY(30.0f);
    outManip->setXMin(40.0f);
    outManip->setYMin(50.0f);
    outManip->setXMax(60.0f);
    outManip->setYMax(70.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipDragXy * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragXy>(inObj, EManipulator::drag_xy, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->xDataref().c_str(), inManip->xDataref().c_str());
    ASSERT_STREQ(outManip->yDataref().c_str(), inManip->yDataref().c_str());
    ASSERT_EQ(outManip->x(), inManip->x());
    ASSERT_EQ(outManip->y(), inManip->y());
    ASSERT_EQ(outManip->xMin(), inManip->xMin());
    ASSERT_EQ(outManip->yMin(), inManip->yMin());
    ASSERT_EQ(outManip->xMax(), inManip->xMax());
    ASSERT_EQ(outManip->yMax(), inManip->yMax());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipNoop) {
    AttrManipNoop * outManip = new AttrManipNoop;

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipNoop * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipNoop>(inObj, EManipulator::noop, inManip));

    //-----------------------------
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipPush) {
    AttrManipPush * outManip = new AttrManipPush;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setDown(20.0f);
    outManip->setUp(30.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipPush * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipPush>(inObj, EManipulator::push, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->down(), inManip->down());
    ASSERT_EQ(outManip->up(), inManip->up());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipPush>(inWheelObj, EManipulator::push, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipRadio) {
    AttrManipRadio * outManip = new AttrManipRadio;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setDown(20.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipRadio * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipRadio>(inObj, EManipulator::radio, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->down(), inManip->down());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipRadio>(inWheelObj, EManipulator::radio, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipToggle) {
    AttrManipToggle * outManip = new AttrManipToggle;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setOn(20.0f);
    outManip->setOff(30.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipToggle * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipToggle>(inObj, EManipulator::toggle, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->on(), inManip->on());
    ASSERT_EQ(outManip->off(), inManip->off());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipToggle>(inWheelObj, EManipulator::toggle, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/

TEST(TestManipIO, AttrManipWrap) {
    AttrManipWrap * outManip = new AttrManipWrap;
    outManip->setCursor(ECursor(ECursor::right));
    outManip->setToolTip("ToolTip");
    outManip->setDataref("Im/a/dataref");
    outManip->setDown(20.0f);
    outManip->setHold(30.0f);
    outManip->setMinimum(40.0f);
    outManip->setMaximum(50.0f);

    ObjMain outObj;
    IOStatistic stat;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ASSERT_TRUE(outObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    stat.reset();
    ASSERT_TRUE(inObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    const AttrManipWrap * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipWrap>(inObj, EManipulator::wrap, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->cursor(), inManip->cursor());
    ASSERT_STREQ(outManip->toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip->dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip->down(), inManip->down());
    ASSERT_EQ(outManip->hold(), inManip->hold());
    ASSERT_EQ(outManip->minimum(), inManip->minimum());
    ASSERT_EQ(outManip->maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip->setWheelEnabled(true);
    outManip->setWheelDelta(15.0f);

    ObjMain outWheelObj;
    stat.reset();
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip->clone()));
    ASSERT_TRUE(outWheelObj.exportToFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    stat.reset();
    ASSERT_TRUE(inWheelObj.importFromFile(TOTEXT(TestManipIO), stat));
    ASSERT_EQ(1, stat.pTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipWrap>(inWheelObj, EManipulator::wrap, inManip));

    //-----------------------------

    ASSERT_EQ(outManip->isWheelEnabled(), inManip->isWheelEnabled());
    ASSERT_EQ(outManip->wheelDelta(), inManip->wheelDelta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
