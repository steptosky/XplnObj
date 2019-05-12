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
    ASSERT_TRUE(inM->mAttr.mManip);
    const auto manip = std::get_if<MANIP>(&inM->mAttr.mManip->mType);
    ASSERT_TRUE(manip);
    outAttr = manip;
}

template<typename MANIP>
void addManip(ObjMain & inOutMain, const MANIP & inManip) {
    ObjMesh * outM = TestUtilsObjMesh::createObjMesh("m1", 0.0);
    ObjLodGroup & outLGroup = inOutMain.addLod();
    outLGroup.transform().addObject(outM);
    outM->mAttr.mManip = AttrManip(inManip);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisKnob) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipAxisKnob.obj");
    //-----------------------------
    AttrManipAxisKnob outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mMin = 40.0f;
    outManip.mMax = 50.0f;
    outManip.mClickDelta = 20.0f;
    outManip.mHoldDelta = 30.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mMin, inManip->mMin);
    ASSERT_EQ(outManip.mMax, inManip->mMax);
    ASSERT_EQ(outManip.mClickDelta, inManip->mClickDelta);
    ASSERT_EQ(outManip.mHoldDelta, inManip->mHoldDelta);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisSwitchLeftRight) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipAxisSwitchLeftRight.obj");
    //-----------------------------
    AttrManipAxisSwitchLeftRight outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mMin = 40.0f;
    outManip.mMax = 50.0f;
    outManip.mClickDelta = 20.0f;
    outManip.mHoldDelta = 30.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mMin, inManip->mMin);
    ASSERT_EQ(outManip.mMax, inManip->mMax);
    ASSERT_EQ(outManip.mClickDelta, inManip->mClickDelta);
    ASSERT_EQ(outManip.mHoldDelta, inManip->mHoldDelta);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipAxisSwitchUpDown) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipAxisSwitchUpDown.obj");
    //-----------------------------
    AttrManipAxisSwitchUpDown outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mMin = 40.0f;
    outManip.mMax = 50.0f;
    outManip.mClickDelta = 20.0f;
    outManip.mHoldDelta = 30.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mMin, inManip->mMin);
    ASSERT_EQ(outManip.mMax, inManip->mMax);
    ASSERT_EQ(outManip.mClickDelta, inManip->mClickDelta);
    ASSERT_EQ(outManip.mHoldDelta, inManip->mHoldDelta);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmd) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmd.obj");
    //-----------------------------
    AttrManipCmd outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mCommand = "I'm/a/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mCommand.c_str(), inManip->mCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdAxis) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdAxis.obj");
    //-----------------------------
    AttrManipCmdAxis outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mDirX = 5.0f;
    outManip.mDirY = 10.0f;
    outManip.mDirZ = 20.0f;
    outManip.mPosCommand = "I'm/a/Negative/Command";
    outManip.mNegCommand = "I'm/a/Positive/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_EQ(outManip.mDirX, inManip->mDirX);
    ASSERT_EQ(outManip.mDirY, inManip->mDirY);
    ASSERT_EQ(outManip.mDirZ, inManip->mDirZ);
    ASSERT_STREQ(outManip.mPosCommand.c_str(), inManip->mPosCommand.c_str());
    ASSERT_STREQ(outManip.mNegCommand.c_str(), inManip->mNegCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdKnob) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdKnob.obj");
    //-----------------------------
    AttrManipCmdKnob outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mPosCommand = "I'm/a/Negative/Command";
    outManip.mNegCommand = "I'm/a/Positive/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mPosCommand.c_str(), inManip->mPosCommand.c_str());
    ASSERT_STREQ(outManip.mNegCommand.c_str(), inManip->mNegCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdKnob2) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdKnob2.obj");
    //-----------------------------
    AttrManipCmdKnob2 outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mCommand = "I'm/a/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mCommand.c_str(), inManip->mCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchLeftRight) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchLeftRight.obj");
    //-----------------------------
    AttrManipCmdSwitchLeftRight outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mPosCommand = "I'm/a/Negative/Command";
    outManip.mNegCommand = "I'm/a/Positive/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mPosCommand.c_str(), inManip->mPosCommand.c_str());
    ASSERT_STREQ(outManip.mNegCommand.c_str(), inManip->mNegCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchLeftRight2) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchLeftRight2.obj");
    //-----------------------------
    AttrManipCmdSwitchLeftRight2 outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mCommand = "I'm/a/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mCommand.c_str(), inManip->mCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchUpDown) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchUpDown.obj");
    //-----------------------------
    AttrManipCmdSwitchUpDown outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mNegCommand = "I'm/a/Negative/Command";
    outManip.mPosCommand = "I'm/a/Positive/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mPosCommand.c_str(), inManip->mPosCommand.c_str());
    ASSERT_STREQ(outManip.mNegCommand.c_str(), inManip->mNegCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipCmdSwitchUpDown2) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipCmdSwitchUpDown2.obj");
    //-----------------------------
    AttrManipCmdSwitchUpDown2 outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mCommand = "I'm/a/Command";

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mCommand.c_str(), inManip->mCommand.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDelta) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDelta.obj");
    //-----------------------------
    AttrManipDelta outManip;
    outManip.mCursor = ECursor(ECursor::left);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mDown = 5.0f;
    outManip.mHold = 10.0f;
    outManip.mMin = 20.0f;
    outManip.mMax = 30.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mDown, inManip->mDown);
    ASSERT_EQ(outManip.mHold, inManip->mHold);
    ASSERT_EQ(outManip.mMin, inManip->mMin);
    ASSERT_EQ(outManip.mMax, inManip->mMax);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragAxis) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragAxis.obj");
    //-----------------------------
    AttrManipDragAxis outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mDirX = 5.0f;
    outManip.mDirY = 10.0f;
    outManip.mDirZ = 20.0f;
    outManip.mVal1 = 50.0f;
    outManip.mVal2 = 51.0f;

    outManip.mWheel = AttrManipWheel(15.0f);

    outManip.mAxisDetented = AttrAxisDetented(60.0f, 61.0f, 62.0f, 70.0f, 71.0, "I'm/a/dataref-2");
    outManip.mAxisDetentRanges = {AttrAxisDetentRange(19.0f, 20.0f, 21.0f), AttrAxisDetentRange(22.0f, 23.0f, 24.0f)};

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mDirX, inManip->mDirX);
    ASSERT_EQ(outManip.mDirY, inManip->mDirY);
    ASSERT_EQ(outManip.mDirZ, inManip->mDirZ);
    ASSERT_EQ(outManip.mVal1, inManip->mVal1);
    ASSERT_EQ(outManip.mVal2, inManip->mVal2);

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);

    ASSERT_TRUE(inManip->mAxisDetented);
    ASSERT_EQ(outManip.mAxisDetented, inManip->mAxisDetented);

    ASSERT_EQ(2, inManip->mAxisDetentRanges.size());
    ASSERT_EQ(outManip.mAxisDetentRanges[0], inManip->mAxisDetentRanges[0]);
    ASSERT_EQ(outManip.mAxisDetentRanges[1], inManip->mAxisDetentRanges[1]);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragAxisPix) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragAxisPix.obj");
    //-----------------------------
    AttrManipDragAxisPix outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mDxPix = 1;
    outManip.mStep = 2;
    outManip.mExp = 20.0f;
    outManip.mVal1 = 30.0f;
    outManip.mVal2 = 40.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mDxPix, inManip->mDxPix);
    ASSERT_EQ(outManip.mStep, inManip->mStep);
    ASSERT_EQ(outManip.mExp, inManip->mExp);
    ASSERT_EQ(outManip.mVal1, inManip->mVal1);
    ASSERT_EQ(outManip.mVal2, inManip->mVal2);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragRotate) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragRotate.obj");
    //-----------------------------
    AttrManipDragRotate outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mOriginX = 1.0f;
    outManip.mOriginY = 2.0f;
    outManip.mOriginZ = 3.0f;
    outManip.mDirX = 4.0f;
    outManip.mDirY = 5.0f;
    outManip.mDirZ = 6.0f;
    outManip.mAngle1 = 7.0f;
    outManip.mAngle2 = 8.0f;
    outManip.mLift = 8.5f;
    outManip.mV1Min = 9.0f;
    outManip.mV1Max = 10.0f;
    outManip.mV2Min = 11.0f;
    outManip.mV2Max = 12.0f;
    outManip.mDataref1 = "I'm/a/dataref-1";
    outManip.mDataref2 = "I'm/a/dataref-2";

    outManip.mKeys = {AttrManipKeyFrame(15.0f, 16.0f), AttrManipKeyFrame(17.0f, 18.0f)};
    outManip.mAxisDetentRanges = {AttrAxisDetentRange(19.0f, 20.0f, 21.0f), AttrAxisDetentRange(22.0f, 23.0f, 24.0f)};

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

    EXPECT_EQ(outManip.mCursor, inManip->mCursor);
    EXPECT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    EXPECT_STREQ(outManip.mDataref1.c_str(), inManip->mDataref1.c_str());
    EXPECT_STREQ(outManip.mDataref2.c_str(), inManip->mDataref2.c_str());
    EXPECT_EQ(outManip.mOriginX, inManip->mOriginX);
    EXPECT_EQ(outManip.mOriginY, inManip->mOriginY);
    EXPECT_EQ(outManip.mOriginZ, inManip->mOriginZ);
    EXPECT_EQ(outManip.mDirX, inManip->mDirX);
    EXPECT_EQ(outManip.mDirY, inManip->mDirY);
    EXPECT_EQ(outManip.mDirZ, inManip->mDirZ);
    EXPECT_EQ(outManip.mAngle1, inManip->mAngle1);
    EXPECT_EQ(outManip.mAngle2, inManip->mAngle2);
    EXPECT_EQ(outManip.mLift, inManip->mLift);
    EXPECT_EQ(outManip.mV1Min, inManip->mV1Min);
    EXPECT_EQ(outManip.mV1Max, inManip->mV1Max);
    EXPECT_EQ(outManip.mV2Min, inManip->mV2Min);
    EXPECT_EQ(outManip.mV2Max, inManip->mV2Max);

    ASSERT_EQ(2, inManip->mKeys.size());
    ASSERT_EQ(outManip.mKeys[0], inManip->mKeys[0]);
    ASSERT_EQ(outManip.mKeys[1], inManip->mKeys[1]);

    ASSERT_EQ(2, inManip->mAxisDetentRanges.size());
    ASSERT_EQ(outManip.mAxisDetentRanges[0], inManip->mAxisDetentRanges[0]);
    ASSERT_EQ(outManip.mAxisDetentRanges[1], inManip->mAxisDetentRanges[1]);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipDragXy) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipDragXy.obj");
    //-----------------------------
    AttrManipDragXy outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mXDataref = "I'm/a/dataref/X";
    outManip.mYDataref = "I'm/a/dataref/Y";
    outManip.mX = 20.0f;
    outManip.mY = 30.0f;
    outManip.mXMin = 40.0f;
    outManip.mYMin = 50.0f;
    outManip.mXMax = 60.0f;
    outManip.mYMax = 70.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mXDataref.c_str(), inManip->mXDataref.c_str());
    ASSERT_STREQ(outManip.mYDataref.c_str(), inManip->mYDataref.c_str());
    ASSERT_EQ(outManip.mX, inManip->mX);
    ASSERT_EQ(outManip.mY, inManip->mY);
    ASSERT_EQ(outManip.mXMin, inManip->mXMin);
    ASSERT_EQ(outManip.mYMin, inManip->mYMin);
    ASSERT_EQ(outManip.mXMax, inManip->mXMax);
    ASSERT_EQ(outManip.mYMax, inManip->mYMax);
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
    AttrManipPush outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mDown = 20.0f;
    outManip.mUp = 30.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mDown, inManip->mDown);
    ASSERT_EQ(outManip.mUp, inManip->mUp);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipRadio) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipRadio.obj");
    //-----------------------------
    AttrManipRadio outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mDown = 20.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mDown, inManip->mDown);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipToggle) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipToggle.obj");
    //-----------------------------
    AttrManipToggle outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mOn = 20.0f;
    outManip.mOff = 30.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mOn, inManip->mOn);
    ASSERT_EQ(outManip.mOff, inManip->mOff);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(TestManipIO, AttrManipWrap) {
    const auto fileName = XOBJ_PATH("TestManipIO-AttrManipWrap.obj");
    //-----------------------------
    AttrManipWrap outManip;
    outManip.mCursor = ECursor(ECursor::right);
    outManip.mToolType = "ToolTip";
    outManip.mDataref = "I'm/a/dataref";
    outManip.mDown = 20.0f;
    outManip.mHold = 30.0f;
    outManip.mMin = 40.0f;
    outManip.mMax = 50.0f;

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

    ASSERT_EQ(outManip.mCursor, inManip->mCursor);
    ASSERT_STREQ(outManip.mToolType.c_str(), inManip->mToolType.c_str());
    ASSERT_STREQ(outManip.mDataref.c_str(), inManip->mDataref.c_str());
    ASSERT_EQ(outManip.mDown, inManip->mDown);
    ASSERT_EQ(outManip.mHold, inManip->mHold);
    ASSERT_EQ(outManip.mMin, inManip->mMin);
    ASSERT_EQ(outManip.mMax, inManip->mMax);

    /***************************************************************************************/

    outManip.mWheel = AttrManipWheel(15.0f);

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

    ASSERT_TRUE(outManip.mWheel);
    ASSERT_TRUE(inManip->mWheel);
    ASSERT_EQ(outManip.mWheel->mWheelDelta, inManip->mWheel->mWheelDelta);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
