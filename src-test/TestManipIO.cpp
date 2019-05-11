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

#include <gtest/gtest.h>

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
#include <xpln/obj/manipulators/AttrManipCmdKnob2.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchLeftRight.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchLeftRight2.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h>
#include <xpln/obj/manipulators/AttrManipCmdSwitchUpDown2.h>
#include <xpln/obj/manipulators/AttrManipDragRotate.h>

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/* 
 * This tests are for checking manipulators of the chain 'mesh object->file | file->mesh object'.
 * They test writer and reader for manipulators of one mesh object.
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<typename MANIP>
void extractManip(const ObjMain & inMain, const MANIP *& outAttr) {
    ASSERT_EQ(1, inMain.lods().size());
    const ObjLodGroup & inLGroup = *inMain.lods().at(0);
    ASSERT_EQ(1, inLGroup.transform().objList().size());
    ObjAbstract * obj = inLGroup.transform().objList().begin()->get();
    ASSERT_EQ(eObjectType::OBJ_MESH, obj->objType());
    auto * inM = static_cast<ObjMesh *>(obj);
    ASSERT_TRUE(inM->mAttr.mManipContainer);
    const auto manip = std::get_if<MANIP>(&inM->mAttr.mManipContainer->mType);
    ASSERT_TRUE(manip);
    outAttr = manip;
}

template<typename MANIP>
void addManip(ObjMain & inOutMain, const MANIP & inManip) {
    ObjMesh * outM = TestUtilsObjMesh::createObjMesh("m1", 0.0);
    ObjLodGroup & outLGroup = inOutMain.addLod();
    outLGroup.transform().addObject(outM);
    outM->mAttr.mManipContainer = AttrManip(inManip);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisKnob) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipAxisKnob.obj");
    //-----------------------------
    AttrManipAxisKnob outManip;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setClickDelta(20.0f);
    outManip.setHoldDelta(30.0f);
    outManip.setMinimum(40.0f);
    outManip.setMaximum(50.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipAxisKnob * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisKnob>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.clickDelta(), inManip->clickDelta());
    ASSERT_EQ(outManip.holdDelta(), inManip->holdDelta());
    ASSERT_EQ(outManip.minimum(), inManip->minimum());
    ASSERT_EQ(outManip.maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisKnob>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisSwitchLeftRight) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipAxisSwitchLeftRight.obj");
    //-----------------------------
	AttrManipAxisSwitchLeftRight outManip;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setClickDelta(20.0f);
    outManip.setHoldDelta(30.0f);
    outManip.setMinimum(40.0f);
    outManip.setMaximum(50.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipAxisSwitchLeftRight * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchLeftRight>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.clickDelta(), inManip->clickDelta());
    ASSERT_EQ(outManip.holdDelta(), inManip->holdDelta());
    ASSERT_EQ(outManip.minimum(), inManip->minimum());
    ASSERT_EQ(outManip.maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchLeftRight>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisSwitchUpDown) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipAxisSwitchUpDown.obj");
    //-----------------------------
	AttrManipAxisSwitchUpDown outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setClickDelta(20.0f);
    outManip.setHoldDelta(30.0f);
    outManip.setMinimum(40.0f);
    outManip.setMaximum(50.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipAxisSwitchUpDown * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchUpDown>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.clickDelta(), inManip->clickDelta());
    ASSERT_EQ(outManip.holdDelta(), inManip->holdDelta());
    ASSERT_EQ(outManip.minimum(), inManip->minimum());
    ASSERT_EQ(outManip.maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipAxisSwitchUpDown>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmd) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmd.obj");
    //-----------------------------
	AttrManipCmd outManip;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmd("I'm/a/Command");

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmd * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmd>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.cmd().c_str(), inManip->cmd().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdAxis) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdAxis.obj");
    //-----------------------------
	AttrManipCmdAxis outManip ;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmdNegative("I'm/a/Negative/Command");
    outManip.setCmdPositive("I'm/a/Positive/Command");
    outManip.setDirectionX(5.0f);
    outManip.setDirectionY(10.0f);
    outManip.setDirectionZ(20.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmdAxis * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdAxis>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_EQ(outManip.directionX(), inManip->directionX());
    ASSERT_EQ(outManip.directionY(), inManip->directionY());
    ASSERT_EQ(outManip.directionZ(), inManip->directionZ());
    ASSERT_STREQ(outManip.cmdNegative().c_str(), inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip.cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdKnob) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdKnob.obj");
    //-----------------------------
	AttrManipCmdKnob outManip;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmdNegative("I'm/a/Negative/Command");
    outManip.setCmdPositive("I'm/a/Positive/Command");

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmdKnob * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdKnob>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.cmdNegative().c_str(), inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip.cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdKnob2) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdKnob2.obj");
    //-----------------------------
	AttrManipCmdKnob2 outManip ;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmd("I'm/a/Command");

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmdKnob2 * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdKnob2>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.cmd().c_str(), inManip->cmd().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchLeftRight) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchLeftRight.obj");
    //-----------------------------
	AttrManipCmdSwitchLeftRight outManip ;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmdNegative("I'm/a/Negative/Command");
    outManip.setCmdPositive("I'm/a/Positive/Command");

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmdSwitchLeftRight * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdSwitchLeftRight>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.cmdNegative().c_str(), inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip.cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchLeftRight2) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchLeftRight2.obj");
    //-----------------------------
	AttrManipCmdSwitchLeftRight2 outManip ;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmd("I'm/a/Command");

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmdSwitchLeftRight2 * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdSwitchLeftRight2>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.cmd().c_str(), inManip->cmd().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchUpDown) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchUpDown.obj");
    //-----------------------------
	AttrManipCmdSwitchUpDown outManip ;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmdNegative("I'm/a/Negative/Command");
    outManip.setCmdPositive("I'm/a/Positive/Command");

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmdSwitchUpDown * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdSwitchUpDown>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.cmdNegative().c_str(), inManip->cmdNegative().c_str());
    ASSERT_STREQ(outManip.cmdPositive().c_str(), inManip->cmdPositive().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchUpDown2) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchUpDown2.obj");
    //-----------------------------
	AttrManipCmdSwitchUpDown2 outManip ;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setCmd("I'm/a/Command");

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipCmdSwitchUpDown2 * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipCmdSwitchUpDown2>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.cmd().c_str(), inManip->cmd().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDelta) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDelta.obj");
    //-----------------------------
	AttrManipDelta outManip ;
    outManip.setCursor(ECursor(ECursor::left));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setDown(5.0f);
    outManip.setHold(10.0f);
    outManip.setMinimum(20.0f);
    outManip.setMaximum(30.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipDelta * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDelta>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.down(), inManip->down());
    ASSERT_EQ(outManip.hold(), inManip->hold());
    ASSERT_EQ(outManip.minimum(), inManip->minimum());
    ASSERT_EQ(outManip.maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDelta>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragAxis) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragAxis.obj");
    //-----------------------------
	AttrManipDragAxis outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref-1");
    outManip.setDirection(5.0f, 10.0f, 20.0f);
    outManip.setValues(50.0f, 51.0f);

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    AttrAxisDetented detentedManip;
    detentedManip.setEnabled(true);
    detentedManip.setDirection(60.0f, 61.0f, 62.0f);
    detentedManip.setValue(70.0f, 71.0);
    detentedManip.setDataref("I'm/a/dataref-2");
    outManip.setAxisDetented(detentedManip);

    outManip.setDetentRanges({AttrAxisDetentRange(19.0f, 20.0f, 21.0f), AttrAxisDetentRange(22.0f, 23.0f, 24.0f)});

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(5, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipDragAxis * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragAxis>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.directionX(), inManip->directionX());
    ASSERT_EQ(outManip.directionY(), inManip->directionY());
    ASSERT_EQ(outManip.directionZ(), inManip->directionZ());
    ASSERT_EQ(outManip.val1(), inManip->val1());
    ASSERT_EQ(outManip.val2(), inManip->val2());

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());

    ASSERT_TRUE(inManip->axisDetented().isEnabled());
    ASSERT_EQ(outManip.axisDetented().directionX(), inManip->axisDetented().directionX());
    ASSERT_EQ(outManip.axisDetented().directionY(), inManip->axisDetented().directionY());
    ASSERT_EQ(outManip.axisDetented().directionZ(), inManip->axisDetented().directionZ());
    ASSERT_EQ(outManip.axisDetented().vMin(), inManip->axisDetented().vMin());
    ASSERT_EQ(outManip.axisDetented().vMax(), inManip->axisDetented().vMax());
    ASSERT_STREQ(outManip.axisDetented().dataref().c_str(), inManip->axisDetented().dataref().c_str());

    ASSERT_EQ(2, inManip->detentRanges().size());
    ASSERT_EQ(outManip.detentRanges()[0], inManip->detentRanges()[0]);
    ASSERT_EQ(outManip.detentRanges()[1], inManip->detentRanges()[1]);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragAxisPix) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragAxisPix.obj");
    //-----------------------------
	AttrManipDragAxisPix outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setDxPix(1);
    outManip.setStep(2);
    outManip.setExp(20.0f);
    outManip.setVal1(30.0f);
    outManip.setVal2(40.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipDragAxisPix * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragAxisPix>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.dxPix(), inManip->dxPix());
    ASSERT_EQ(outManip.step(), inManip->step());
    ASSERT_EQ(outManip.exp(), inManip->exp());
    ASSERT_EQ(outManip.val1(), inManip->val1());
    ASSERT_EQ(outManip.val2(), inManip->val2());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragAxisPix>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragRotate) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragRotate.obj");
    //-----------------------------
	AttrManipDragRotate outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setOrigin(1.0f, 2.0f, 3.0f);
    outManip.setDirection(4.0f, 5.0f, 6.0f);
    outManip.setAngles(7.0f, 8.0f);
    outManip.setLift(8.5f);
    outManip.setV1(9.0f, 10.0f);
    outManip.setV2(11.0f, 12.0f);
    outManip.setDatarefs("I'm/a/dataref-1", "I'm/a/dataref-2");

    outManip.setKeys({AttrManipKeyFrame(15.0f, 16.0f), AttrManipKeyFrame(17.0f, 18.0f)});
    outManip.setDetentRanges({AttrAxisDetentRange(19.0f, 20.0f, 21.0f), AttrAxisDetentRange(22.0f, 23.0f, 24.0f)});

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(5, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipDragRotate * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragRotate>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref1().c_str(), inManip->dataref1().c_str());
    ASSERT_STREQ(outManip.dataref2().c_str(), inManip->dataref2().c_str());
    ASSERT_EQ(outManip.originX(), inManip->originX());
    ASSERT_EQ(outManip.originY(), inManip->originY());
    ASSERT_EQ(outManip.originZ(), inManip->originZ());
    ASSERT_EQ(outManip.directionX(), inManip->directionX());
    ASSERT_EQ(outManip.directionY(), inManip->directionY());
    ASSERT_EQ(outManip.directionZ(), inManip->directionZ());
    ASSERT_EQ(outManip.angle1(), inManip->angle1());
    ASSERT_EQ(outManip.angle2(), inManip->angle2());
    ASSERT_EQ(outManip.lift(), inManip->lift());
    ASSERT_EQ(outManip.v1Min(), inManip->v1Min());
    ASSERT_EQ(outManip.v1Max(), inManip->v1Max());
    ASSERT_EQ(outManip.v2Min(), inManip->v2Min());
    ASSERT_EQ(outManip.v2Max(), inManip->v2Max());

    ASSERT_EQ(2, inManip->keys().size());
    ASSERT_EQ(outManip.keys()[0], inManip->keys()[0]);
    ASSERT_EQ(outManip.keys()[1], inManip->keys()[1]);

    ASSERT_EQ(2, inManip->detentRanges().size());
    ASSERT_EQ(outManip.detentRanges()[0], inManip->detentRanges()[0]);
    ASSERT_EQ(outManip.detentRanges()[1], inManip->detentRanges()[1]);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragXy) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragXy.obj");
    //-----------------------------
	AttrManipDragXy outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setXDataref("I'm/a/dataref/X");
    outManip.setYDataref("I'm/a/dataref/Y");
    outManip.setX(20.0f);
    outManip.setY(30.0f);
    outManip.setXMin(40.0f);
    outManip.setYMin(50.0f);
    outManip.setXMax(60.0f);
    outManip.setYMax(70.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipDragXy * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipDragXy>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.xDataref().c_str(), inManip->xDataref().c_str());
    ASSERT_STREQ(outManip.yDataref().c_str(), inManip->yDataref().c_str());
    ASSERT_EQ(outManip.x(), inManip->x());
    ASSERT_EQ(outManip.y(), inManip->y());
    ASSERT_EQ(outManip.xMin(), inManip->xMin());
    ASSERT_EQ(outManip.yMin(), inManip->yMin());
    ASSERT_EQ(outManip.xMax(), inManip->xMax());
    ASSERT_EQ(outManip.yMax(), inManip->yMax());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipNoop) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipNoop.obj");
    //-----------------------------
	AttrManipNoop outManip;

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipNoop * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipNoop>(inObj, inManip));

    //-----------------------------
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipPush) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipPush.obj");
    //-----------------------------
	AttrManipPush outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setDown(20.0f);
    outManip.setUp(30.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipPush * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipPush>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.down(), inManip->down());
    ASSERT_EQ(outManip.up(), inManip->up());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipPush>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipRadio) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipRadio.obj");
    //-----------------------------
	AttrManipRadio outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setDown(20.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipRadio * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipRadio>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.down(), inManip->down());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipRadio>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipToggle) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipToggle.obj");
    //-----------------------------
	AttrManipToggle outManip ;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setOn(20.0f);
    outManip.setOff(30.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipToggle * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipToggle>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.on(), inManip->on());
    ASSERT_EQ(outManip.off(), inManip->off());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipToggle>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipWrap) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipWrap.obj");
    //-----------------------------
	AttrManipWrap outManip;
    outManip.setCursor(ECursor(ECursor::right));
    outManip.setToolTip("ToolTip");
    outManip.setDataref("I'm/a/dataref");
    outManip.setDown(20.0f);
    outManip.setHold(30.0f);
    outManip.setMinimum(40.0f);
    outManip.setMaximum(50.0f);

    ObjMain outObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outObj, outManip));
    ExportContext expContext(fileName);
    ASSERT_TRUE(outObj.exportObj(expContext));
    ASSERT_EQ(1, expContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inObj;
    ImportContext impContext(fileName);
    ASSERT_TRUE(inObj.importObj(impContext));
    ASSERT_EQ(1, impContext.statistic().mTrisManipCount);
    const AttrManipWrap * inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipWrap>(inObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.cursor(), inManip->cursor());
    ASSERT_STREQ(outManip.toolTip().c_str(), inManip->toolTip().c_str());
    ASSERT_STREQ(outManip.dataref().c_str(), inManip->dataref().c_str());
    ASSERT_EQ(outManip.down(), inManip->down());
    ASSERT_EQ(outManip.hold(), inManip->hold());
    ASSERT_EQ(outManip.minimum(), inManip->minimum());
    ASSERT_EQ(outManip.maximum(), inManip->maximum());

    /***************************************************************************************/

    outManip.wheel().setEnabled(true);
    outManip.wheel().setDelta(15.0f);

    ObjMain outWheelObj;
    ASSERT_NO_FATAL_FAILURE(addManip(outWheelObj, outManip));
    ExportContext expWheelContext(fileName);
    ASSERT_TRUE(outWheelObj.exportObj(expWheelContext));
    ASSERT_EQ(2, expWheelContext.statistic().mTrisManipCount);

    //-----------------------------

    ObjMain inWheelObj;
    ImportContext impWheelContext(fileName);
    ASSERT_TRUE(inWheelObj.importObj(impWheelContext));
    ASSERT_EQ(1, impWheelContext.statistic().mTrisManipCount);
    inManip = nullptr;
    ASSERT_NO_FATAL_FAILURE(extractManip<AttrManipWrap>(inWheelObj, inManip));

    //-----------------------------

    ASSERT_EQ(outManip.wheel().isEnabled(), inManip->wheel().isEnabled());
    ASSERT_EQ(outManip.wheel().delta(), inManip->wheel().delta());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
