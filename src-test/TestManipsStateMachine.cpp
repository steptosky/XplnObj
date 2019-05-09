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

#include "converters/ObjAttrString.h"

#include "MockIWriter.h"
#include "io/writer/ObjWriteManip.h"
#include "io/writer/ObjWriteAttr.h"
#include "common/AttributeNames.h"

#include "xpln/obj/ObjMesh.h"

#include "xpln/obj/manipulators/AttrManipCmd.h"
#include "xpln/obj/manipulators/AttrManipCmdAxis.h"
#include "xpln/obj/manipulators/AttrManipNoop.h"
#include "xpln/obj/manipulators/AttrManipPush.h"
#include "xpln/obj/manipulators/AttrManipPanel.h"
#include "xpln/obj/manipulators/AttrManipNone.h"
#include "totext.h"
#include "TestWriter.h"

using namespace xobj;
using ::testing::_;
using ::testing::StrEq;
using ::testing::HasSubstr;
using ::testing::InSequence;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * The tests for the manipulators' state machine.
 */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

template<typename T>
std::string strAttrResult(const T & attr) {
    TestWriter w;
    printObjAttr(attr, w);
    if (!w.mResult.empty()) {
        w.mResult.pop_back(); // remove '\n'
    }
    return w.mResult;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

class ManipsStates : public ::testing::Test {
public:

    ManipsStates(const ManipsStates &) = delete;
    ManipsStates & operator =(const ManipsStates &) = delete;

    ManipsStates()
        : mObjWriteAttr(&mObjWriteManip) {
        mObjMesh1.setObjectName(TOTEXT(mObjMesh1));
        mObjMesh2.setObjectName(TOTEXT(mObjMesh2));
        mObjMesh3.setObjectName(TOTEXT(mObjMesh3));
        mObjMesh4.setObjectName(TOTEXT(mObjMesh4));
    }

    virtual ~ManipsStates() = default;

    /*!
     * \details Processes all the meshes with the specified writer.
     * \param writer
     */
    void processMeshes(AbstractWriter * writer) {
        processMesh(writer, mObjMesh1);
        processMesh(writer, mObjMesh2);
        processMesh(writer, mObjMesh3);
        processMesh(writer, mObjMesh4);
    }

    /*!
     * \details Processes the specified mesh with the specified writer.
     * \param writer 
     * \param mesh 
     */
    void processMesh(AbstractWriter * writer, ObjMesh & mesh) {
        mObjWriteAttr.write(writer, &mesh);
        mObjWriteManip.write(writer, &mesh);
    }

    ObjWriteManip mObjWriteManip;
    ObjWriteAttr mObjWriteAttr;

    ObjMesh mObjMesh1;
    ObjMesh mObjMesh2;
    ObjMesh mObjMesh3;
    ObjMesh mObjMesh4;

    AttrManipCmd mManipCmd;
    AttrManipCmdAxis mManipComdAxis;
    AttrManipNoop mManipNoop;
    AttrManipPush mManipPush;

    AttrManipPanel mManipPanel;
    AttrManipNone mManipNone;

};

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// NO MANIPS ///////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// The objects do not have any manipulator.
TEST_F(ManipsStates, no_manips) {
    MockWriter writer;
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMeshes(&writer);
    ASSERT_EQ(0, mObjWriteManip.count());
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// SIMPLE TESTS FOR THE ONE MANIP TYPE /////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* ================================================ *\
 * result
 * =========================
 *    - manip
 *    -     [obj1]
 *    - manip_none
 *    -     [obj2]
 *    -     [obj3]
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, one_manip) {
    InSequence dummy;
    MockWriter writer;
    // 1 manipulator

    mManipCmd.setCmd("test");
    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // No Manip
    // mObjMesh2
    // mObjMesh3
    // mObjMesh4

    TestWriter w(false);
    const auto count = mObjMesh1.pAttr.manipulator()->printObj(w);

    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
}

/* ================================================ *\
 * result
 * =========================
 *    - manip
 *    -     [obj1]
 *    -     [obj2]
 *    - manip_none
 *    -     [obj3]
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, two_manips_with_the_same_vals) {
    InSequence dummy;
    MockWriter writer;
    // 2 the same manipulators

    mManipCmd.setCmd("test");
    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // No Manip
    // mObjMesh3
    // mObjMesh4

    TestWriter w(false);
    const auto count = mObjMesh1.pAttr.manipulator()->printObj(w);

    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
}

/* ================================================ *\
 * result
 * =========================
 *    - manip
 *    -     [obj1]
 *    -     [obj2]
 *    -     [obj3]
 *    - manip_none
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, three_manips_with_the_same_vals) {
    InSequence dummy;
    MockWriter writer;
    // 3 the same manipulators

    mManipCmd.setCmd("test");
    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // No Manip
    // mObjMesh4

    TestWriter w(false);
    const auto count = mObjMesh1.pAttr.manipulator()->printObj(w);

    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
}

/* ================================================ *\
 * result
 * =========================
 *    - manip
 *    -     [obj1]
 *    -     [obj2]
 *    -     [obj3]
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, four_manips_with_the_same_vals) {
    InSequence dummy;
    MockWriter writer;
    // 4 the same manipulators

    mManipCmd.setCmd("test");
    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    mObjMesh4.pAttr.setManipulator(new AttrManipCmd(mManipCmd));

    TestWriter w(false);
    const auto count = mObjMesh1.pAttr.manipulator()->printObj(w);

    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count, mObjWriteManip.count());
}

/* ================================================ *\
 * result
 * =========================
 *    - manip
 *    -     [obj1]
 *    - manip
 *    -     [obj2]
 *    - manip
 *    -     [obj3]
 *    - manip
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, four_manips_with_the_different_vals) {
    InSequence dummy;
    MockWriter writer;
    // 4 different manipulators

    // Manip
    mManipCmd.setCmd("test1");
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // Manip
    mManipCmd.setCmd("test2");
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // Manip
    mManipCmd.setCmd("test3");
    mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // Manip
    mManipCmd.setCmd("test4");
    mObjMesh4.pAttr.setManipulator(new AttrManipCmd(mManipCmd));

    TestWriter w1(false);
    TestWriter w2(false);
    TestWriter w3(false);
    TestWriter w4(false);
    const auto count1 = mObjMesh1.pAttr.manipulator()->printObj(w1);
    const auto count2 = mObjMesh2.pAttr.manipulator()->printObj(w2);
    const auto count3 = mObjMesh3.pAttr.manipulator()->printObj(w3);
    const auto count4 = mObjMesh4.pAttr.manipulator()->printObj(w4);

    EXPECT_CALL(writer, printLine(StrEq(w1.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w2.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w3.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w4.mResult))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count1 + count2 + count3 + count4, mObjWriteManip.count());
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// SIMPLE TESTS FOR THE DIFFERENT MANIP TYPES //////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* ================================================ *\
 * result
 * =========================
 *    - manip_1
 *    -     [obj1]
 *    - manip_2
 *    -     [obj2]
 *    - manip_3
 *    -     [obj3]
 *    - manip_4
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, four_different_manips) {
    InSequence dummy;
    MockWriter writer;

    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // Manip
    mObjMesh2.pAttr.setManipulator(new AttrManipCmdAxis(mManipComdAxis));
    // Manip
    mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
    // Manip
    mObjMesh4.pAttr.setManipulator(new AttrManipPush(mManipPush));

    TestWriter w1(false);
    TestWriter w2(false);
    TestWriter w3(false);
    TestWriter w4(false);
    const auto count1 = mObjMesh1.pAttr.manipulator()->printObj(w1);
    const auto count2 = mObjMesh2.pAttr.manipulator()->printObj(w2);
    const auto count3 = mObjMesh3.pAttr.manipulator()->printObj(w3);
    const auto count4 = mObjMesh4.pAttr.manipulator()->printObj(w4);

    EXPECT_CALL(writer, printLine(StrEq(w1.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w2.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w3.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w4.mResult))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count1 + count2 + count3 + count4, mObjWriteManip.count());
}

/* ================================================ *\
 * result
 * =========================
 *    - manip_1
 *    -     [obj1]
 *    - manip_2
 *    -     [obj2]
 *    - manip_3
 *    -     [obj3]
 *    - manip_none
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, three_different_manips) {
    InSequence dummy;
    MockWriter writer;

    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // Manip
    mObjMesh2.pAttr.setManipulator(new AttrManipCmdAxis(mManipComdAxis));
    // Manip
    mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
    // No Manip
    // mObjMesh4

    TestWriter w1(false);
    TestWriter w2(false);
    TestWriter w3(false);
    const auto count1 = mObjMesh1.pAttr.manipulator()->printObj(w1);
    const auto count2 = mObjMesh2.pAttr.manipulator()->printObj(w2);
    const auto count3 = mObjMesh3.pAttr.manipulator()->printObj(w3);

    EXPECT_CALL(writer, printLine(StrEq(w1.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w2.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w3.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count1 + count2 + count3 + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
}

/* ================================================ *\
 * result
 * =========================
 *    - manip_1
 *    -     [obj1]
 *    -     [obj2]
 *    - manip_2
 *    -     [obj3]
 *    - manip_3
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, two_the_same_and_two_different_manips) {
    InSequence dummy;
    MockWriter writer;

    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // Manip
    mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
    // Manip
    mObjMesh4.pAttr.setManipulator(new AttrManipPush(mManipPush));

    TestWriter w1(false);
    TestWriter w3(false);
    TestWriter w4(false);
    const auto count1 = mObjMesh1.pAttr.manipulator()->printObj(w1);
    const auto count3 = mObjMesh3.pAttr.manipulator()->printObj(w3);
    const auto count4 = mObjMesh4.pAttr.manipulator()->printObj(w4);

    EXPECT_CALL(writer, printLine(StrEq(w1.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w3.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w4.mResult))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count1 + count3 + count4, mObjWriteManip.count());
}

/* ================================================ *\
 * result
 * =========================
 *    - manip_1
 *    -     [obj1]
 *    - no_manip
 *    -     [obj2]
 *    - manip_2
 *    -     [obj3]
 *    - manip_3
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, one_manip_and_two_different_manips) {
    InSequence dummy;
    MockWriter writer;

    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // No Manip
    // mObjMesh2
    // Manip
    mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
    // Manip
    mObjMesh4.pAttr.setManipulator(new AttrManipPush(mManipPush));

    TestWriter w1(false);
    TestWriter w3(false);
    TestWriter w4(false);
    const auto count1 = mObjMesh1.pAttr.manipulator()->printObj(w1);
    const auto count3 = mObjMesh3.pAttr.manipulator()->printObj(w3);
    const auto count4 = mObjMesh4.pAttr.manipulator()->printObj(w4);

    EXPECT_CALL(writer, printLine(StrEq(w1.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w3.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w4.mResult))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count1 + count3 + count4 + 1, mObjWriteManip.count()); //  + ATTR_MANIP_NONE
}

/* ================================================ *\
 * result
 * =========================
 *    - manip_1
 *    -     [obj1]
 *    - manip_none
 *    -     [obj2]
 *    - manip_2
 *    -     [obj3]
 *    - manip_none
 *    -     [obj4]
\* ================================================ */
TEST_F(ManipsStates, two_different_manips) {
    InSequence dummy;
    MockWriter writer;

    // Manip
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    // No Manip
    // mObjMesh2
    // Manip
    mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
    // No Manip
    // mObjMesh4

    TestWriter w1(false);
    TestWriter w2(false);
    TestWriter w3(false);
    TestWriter w4(false);
    const auto count1 = mObjMesh1.pAttr.manipulator()->printObj(w1);
    const auto count3 = mObjMesh3.pAttr.manipulator()->printObj(w3);

    EXPECT_CALL(writer, printLine(StrEq(w1.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w3.mResult))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMeshes(&writer);
    ASSERT_EQ(count1 + count3 + 1 + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// MEANINGLESS SITUATIONS //////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* ================================================ *\
 * Manip panel on none panel textured objects.
 * This situation is not allowed, so the manipulator
 * should not be processed and error should be printed.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   manip_panel
 *       [obj1]        ==>       [obj1]
 *       [obj2]                  [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_panel_relation_simple_case2) {
    // make data
    MockWriter writer;
    InSequence dummy;
    //---------------------------
    // set data
    mObjMesh1.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(0, mObjWriteManip.count());
    //---------------------------
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// MANIP PANEL AND NONE MANIP AUUTO-DISABLING PANEL ////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
//                                                                                                //
//    Auto disable the panel manipulator.                                                         //
//    The cockpit geometry always has a manipulator if there is no manip_none set.                //
//    So if the user did not set the manip_none explicitly                                        //
//    then the panel manipulator will be auto-enabled after cockpit attribute.                    //
//                                                                                                //
//    THIS LIBRARY AUTO-DISABLES THE _PANEL_ MANIPULATOR IF IT IS NOT EXPLICITLY SET.             //
//                                                                                                //
//    The following set of the tests test the situations around auto-disabling mechanism.         //
//                                                                                                //
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* ================================================ *\
 * Enabling manipulator with the panel manip
 * for the second object
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit               cockpit
 *        [obj1]           manip_none // auto-disabling
 *   cockpit        ==>        [obj1] 
 *   manip_panel           cockpit(manip_panel)
 *        [obj2]               [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_panel_disabling_panel_case1) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::region_1);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh2.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    mManipPanel.setCockpit(cpAttr1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(HasSubstr(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipPanel.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter + ATTR_MANIP_NONE
    ASSERT_EQ(1 + 1, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Enabling manipulator with the manip attribute
 * for the second object
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit               cockpit
 *       [obj1]            manip_none // auto-disabling
 *   cockpit        ==>        [obj1]
 *   manip_1               manip_1
 *       [obj2]                [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_panel_disabling_panel_case2) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter + ATTR_MANIP_NONE
    ASSERT_EQ(1 + 1, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Check that there is not the manip_none 
 * on the first object if it has the panel manip.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit               cockpit
 *   manip_panel               [obj1]
 *       [obj1]     ==>        [obj2]
 *   cockpit     
 *   manip_panel 
 *       [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_panel_disabling_panel_case3) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh2.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(0, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Check that there is not the manip_none
 * on the first object if it has the manip attribute.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit               cockpit
 *   manip_1               manip_1
 *       [obj1]     ==>        [obj1]
 *   cockpit                   [obj2]
 *   manip_1
 *       [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_panel_disabling_panel_case4) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(1, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Check that there is the manip_none
 * after each cockpit type.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit_1             cockpit_1
         [obj1]            manip_none // auto-disabling
 *   cockpit_2      ==>        [obj1]
 *       [obj2]            cockpit_2
 *                         manip_none // auto-disabling
 *                             [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_panel_disabling_panel_case5) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    const AttrCockpit cpAttr2(AttrCockpit::region_1);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr2;
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr2)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter + ATTR_MANIP_NONE
    ASSERT_EQ(1 + 1, mObjWriteManip.count());
    //---------------------------
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// MANIPS AND COCKPIT SIMPLE ///////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* ================================================ *\
 * Checks the situation around the cockpit
 * when previous object has not the manipulator and cockpit.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *       [obj1]                [obj1]
 *   cockpit        ==>    cockpit
 *       [obj2]            manip_none // auto-disabling
 *                             [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_simple_case_1) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter + ATTR_MANIP_NONE
    ASSERT_EQ(1, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Checks the situation around the cockpit
 * when previous object has the manipulator and no cockpit.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   manip_1               manip_1
 *       [obj1]                [obj1]
 *   cockpit        ==>    cockpit
 *       [obj2]            manip_none // auto-disabling
 *                             [obj2]
 *
 \* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_simple_case_2) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    //------
    // mObjMesh3
    //------
    // mObjMesh4
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter + ATTR_MANIP_NONE
    ASSERT_EQ(1 + 1, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * After the no_cockpit the previous manip has been disabled,
 * so it must be enabled again.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit               cockpit
 *   manip                 manip
 *       [obj1]     ==>        [obj1]
 *   manip                 no_cockpit
 *       [obj2]            manip // no_cockpit disables the manips, so we have to enable it again.
 *                             [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_simple_case_4) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(2, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Switching cockpit type with panel manip.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit_1               cockpit_1
 *   manip_panel                 [obj1]
 *       [obj1]     ==>      cockpit_2
 *   cockpit_2                   [obj2]
 *   manip_panel
 *       [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_simple_case_5) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    const AttrCockpit cpAttr2(AttrCockpit::region_1);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr2;
    mObjMesh2.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr2)))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(0, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Switching cockpit type with non panel manip.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit_1               cockpit_1
 *   manip                   manip
 *       [obj1]     ==>          [obj1]
 *   cockpit_2               cockpit_2 // it enables panel manip, it is not what we need.
 *   manip                   manip     // se set the correct manip
 *       [obj2]                  [obj1]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_simple_case_6) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    const AttrCockpit cpAttr2(AttrCockpit::region_1);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr2;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr2)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(2, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * Switching cockpit type and manip type 
 * from panel to other.
 * ================================================
 *    origin                  result
 * ================================================
 *
 *   cockpit_1               cockpit_1
 *   manip_panel                 [obj1]
 *       [obj1]     ==>      cockpit_2
 *   cockpit_2               manip
 *   manip                       [obj2]
 *       [obj2]
 *
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_simple_case_7) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    const AttrCockpit cpAttr2(AttrCockpit::region_1);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr2;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr2)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(1, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
* Switching cockpit type and manip type
* from other to panel.
* ================================================
*    origin                  result
* ================================================
*
*   cockpit_1               cockpit_1
*   manip                   manip
*       [obj1]     ==>          [obj1]
*   cockpit_2               cockpit_2
*   manip_panel                 [obj2]
*       [obj2]
*
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_simple_case_8) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    const AttrCockpit cpAttr2(AttrCockpit::region_1);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr2;
    mObjMesh2.pAttr.setManipulator(new AttrManipPanel(mManipPanel));
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr2)))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check counter
    ASSERT_EQ(1, mObjWriteManip.count());
    //---------------------------
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// MANIPS AND COCKPIT COMPLEX //////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* ================================================ *\
 * An use case test for relation between manipulators and cockpit.
 * Switching cockpit type.
 * ================================================
 *    origin                  result
 * ================================================
 * 
 *   cockpit_1               cockpit_1
 *   manip                   manip
 *       [obj1]                  [obj1]
 *   cockpit_2               cockpit_2
 *   manip                       manip // change type from panel to what we need.
 *       [obj2]     ==>          [obj2]
 *   manip                   no_cockpit
 *       [obj3]              manip // no_cockpit disables the manips, so we have to enable it again.
 *   manip                       [obj4]
 *       [obj4]                  [obj4]
 * 
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_complex_case_1) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    const AttrCockpit cpAttr2(AttrCockpit::region_1);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr2;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh4.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr2)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh3);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh4);
    //---------------------------
    // check counter
    ASSERT_EQ(3, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * An use case test for relation between manipulators and cockpit.
 * This test may contain situations from the simple tests.
 * ================================================
 *    origin                  result
 * ================================================
 * 
 *   manip_1                 manip_1
 *       [obj1]                  [obj1]
 *   cockpit                 cockpit 
 *   manip_2                 manip_2
 *       [obj2]     ==>          [obj2]
 *   manip_3                 no_cockpit
 *       [obj3]              manip_3
 *   manip_3                     [obj3]
 *       [obj3]                  [obj4]
 * 
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_complex_case_2) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmdAxis(mManipComdAxis));
    //------
    mObjMesh3.pAttr.setManipulator(new AttrManipPush(mManipPush));
    //------
    mObjMesh4.pAttr.setManipulator(new AttrManipPush(mManipPush));
    //---------------------------
    // check printing
    TestWriter w1(false);
    const auto result1 = mManipCmd.printObj(w1);
    ASSERT_EQ(1, result1);
    EXPECT_CALL(writer, printLine(StrEq(w1.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    TestWriter w2(false);
    const auto result2 = mManipComdAxis.printObj(w2);
    ASSERT_EQ(1, result2);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w2.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check printing
    TestWriter w3(false);
    const auto result3 = mManipPush.printObj(w3);
    ASSERT_EQ(1, result3);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w3.mResult))).Times(1);
    processMesh(&writer, mObjMesh3);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh4);
    //---------------------------
    // check counter
    ASSERT_EQ(3, mObjWriteManip.count());
    //---------------------------
}

/* ================================================ *\
 * An use case test for relation between manipulators and cockpit.
 * This test may contain situations from the simple tests.
 * ================================================
 *    origin                  result
 * ================================================
 * 
 *   cockpit                 cockpit
 *   manip                   manip
 *       [obj1]                  [obj1]
 *   cockpit         ==>     manip_none
 *       [obj2]                  [obj2]
 *   cockpit                     [obj3]
 *       [obj3]                  [obj4]
 *   cockpit   
 *       [obj4]
 * 
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_complex_case_3) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    //------
    mObjMesh3.pAttr.mAttrCockpit = cpAttr1;
    //------
    mObjMesh4.pAttr.mAttrCockpit = cpAttr1;
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh3);
    processMesh(&writer, mObjMesh4);
    //---------------------------
    // check counter
    ASSERT_EQ(1 + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
    //---------------------------
}

/* ================================================ *\
 * An use case test for relation between manipulators and cockpit.
 * This test may contain situations from the simple tests.
 * ================================================
 *    origin                  result
 * ================================================
 * 
 *   cockpit                 cockpit
 *       [obj1]              manip_none // auto-disabling
 *   cockpit                     [obj1]
 *   manip                   manip  
 *       [obj2]      ==>         [obj2]
 *   cockpit                 manip_none
 *       [obj3]                  [obj3]
 *       [obj4]              no_cockpit
 *                               [obj4]
 * 
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_complex_case_4) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh3.pAttr.mAttrCockpit = cpAttr1;
    //------
    // mObjMesh4
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh3);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);
    processMesh(&writer, mObjMesh4);
    //---------------------------
    // check counter
    ASSERT_EQ(1 + 1 + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
    //---------------------------
}

/* ================================================ *\
 * An use case test for relation between manipulators and cockpit.
 * This test may contain situations from the simple tests.
 * ================================================
 *    origin                  result
 * ================================================
 * 
 *   cockpit                 cockpit
 *       [obj1]              manip_none // auto-disabling
 *   cockpit                     [obj1]
 *   manip                   manip
 *       [obj2]      ==>         [obj2]
 *   cockpit                     [obj3]
 *   manip                   no_cockpit
 *       [obj3]                  [obj4]
 *       [obj4]
 * 
\* ================================================ */
TEST_F(ManipsStates, manip_cockpit_relation_complex_case_5) {
    // make data
    MockWriter writer;
    InSequence dummy;
    const AttrCockpit cpAttr1(AttrCockpit::cockpit);
    //---------------------------
    // set data
    mObjMesh1.pAttr.mAttrCockpit = cpAttr1;
    //------
    mObjMesh2.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    mObjMesh3.pAttr.mAttrCockpit = cpAttr1;
    mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipCmd));
    //------
    // mObjMesh4
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(strAttrResult(cpAttr1)))).Times(1);
    EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
    processMesh(&writer, mObjMesh1);
    //---------------------------
    // check printing
    TestWriter w(false);
    const auto result = mManipCmd.printObj(w);
    ASSERT_EQ(1, result);
    EXPECT_CALL(writer, printLine(StrEq(w.mResult))).Times(1);
    processMesh(&writer, mObjMesh2);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(_)).Times(0);
    processMesh(&writer, mObjMesh3);
    //---------------------------
    // check printing
    EXPECT_CALL(writer, printLine(StrEq(ATTR_NO_COCKPIT))).Times(1);
    processMesh(&writer, mObjMesh4);
    //---------------------------
    // check counter
    ASSERT_EQ(1 + 1, mObjWriteManip.count()); // + ATTR_MANIP_NONE
    //---------------------------
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
