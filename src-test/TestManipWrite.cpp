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
#include "converters/ObjAttrManipString.h"

#include "MockIWriter.h"
#include "io/writer/ObjWriteManip.h"
#include "xpln/obj/ObjMesh.h"

#include "xpln/obj/manipulators/AttrManipCmd.h"
#include "xpln/obj/manipulators/AttrManipCmdAxis.h"
#include "xpln/obj/manipulators/AttrManipNoop.h"
#include "xpln/obj/manipulators/AttrManipPush.h"

#include "common/AttributeNames.h"

using namespace xobj;
using ::testing::_;
using ::testing::StrEq;
using ::testing::InSequence;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
* This tests are for checking mnipulators logic for writing only and they are low level.
* There are also top level tests (TestManipIOLogic) like this.
*/

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class TestManipWriter : public ::testing::Test {

	TestManipWriter(const TestManipWriter &) = delete;
	TestManipWriter & operator =(const TestManipWriter &) = delete;

public:

	TestManipWriter() = default;
	virtual ~TestManipWriter() = default;

	void runWriter(AbstractWriter * inWriter) {
		mObjWriteManip.write(inWriter, &mObjMesh1);
		mObjWriteManip.write(inWriter, &mObjMesh2);
		mObjWriteManip.write(inWriter, &mObjMesh3);
		mObjWriteManip.write(inWriter, &mObjMesh4);
	}

	ObjWriteManip mObjWriteManip;

	ObjMesh mObjMesh1;
	ObjMesh mObjMesh2;
	ObjMesh mObjMesh3;
	ObjMesh mObjMesh4;

	AttrManipCmd mManipComd;
	AttrManipCmdAxis mManipComdAxis;
	AttrManipNoop mManipNoop;
	AttrManipPush mManipPush;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST_F(TestManipWriter, case_1) {
	MockWriter writer;
	EXPECT_CALL(writer, printLine(_)).Times(0);
	runWriter(&writer);
	ASSERT_EQ(0, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_2) {
	MockWriter writer;

	mManipComd.setCommand("test");
	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// No Manip
	// mObjMesh2
	// mObjMesh3
	// mObjMesh4

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
	runWriter(&writer);
	ASSERT_EQ(1, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_3) {
	MockWriter writer;

	mManipComd.setCommand("test");
	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// No Manip
	// mObjMesh3
	// mObjMesh4

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);

	runWriter(&writer);

	ASSERT_EQ(1, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_4) {
	MockWriter writer;

	mManipComd.setCommand("test");
	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// No Manip
	// mObjMesh4

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);

	runWriter(&writer);

	ASSERT_EQ(1, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_5) {
	MockWriter writer;

	mManipComd.setCommand("test");
	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	mObjMesh4.pAttr.setManipulator(new AttrManipCmd(mManipComd));

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);

	runWriter(&writer);

	ASSERT_EQ(1, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_6) {
	MockWriter writer;

	// Manip
	mManipComd.setCommand("test1");
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// Manip
	mManipComd.setCommand("test2");
	mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// Manip
	mManipComd.setCommand("test3");
	mObjMesh3.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// Manip
	mManipComd.setCommand("test4");
	mObjMesh4.pAttr.setManipulator(new AttrManipCmd(mManipComd));

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh2.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh3.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh4.pAttr.manipulator()).c_str()))).Times(1);

	runWriter(&writer);

	ASSERT_EQ(4, mObjWriteManip.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST_F(TestManipWriter, case_7) {
	MockWriter writer;

	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// Manip
	mObjMesh2.pAttr.setManipulator(new AttrManipCmdAxis(mManipComdAxis));
	// Manip
	mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
	// Manip
	mObjMesh4.pAttr.setManipulator(new AttrManipPush(mManipPush));

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh2.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh3.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh4.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(dynamic_cast<const AttrManipWheel&>(*mObjMesh4.pAttr.manipulator())).c_str()))).Times(0);

	runWriter(&writer);

	ASSERT_EQ(4, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_8) {
	MockWriter writer;

	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// Manip
	mObjMesh2.pAttr.setManipulator(new AttrManipCmdAxis(mManipComdAxis));
	// Manip
	mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
	// No Manip
	// mObjMesh4

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh2.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh3.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);

	runWriter(&writer);

	ASSERT_EQ(3, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_9) {
	MockWriter writer;

	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	mObjMesh2.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// Manip
	mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
	// Manip
	mObjMesh4.pAttr.setManipulator(new AttrManipPush(mManipPush));

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh3.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh4.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(dynamic_cast<const AttrManipWheel&>(*mObjMesh4.pAttr.manipulator())).c_str()))).Times(0);

	runWriter(&writer);

	ASSERT_EQ(3, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_10) {
	MockWriter writer;

	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// No Manip
	// mObjMesh2
	// Manip
	mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
	// Manip
	mObjMesh4.pAttr.setManipulator(new AttrManipPush(mManipPush));

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh3.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh4.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(dynamic_cast<const AttrManipWheel&>(*mObjMesh4.pAttr.manipulator())).c_str()))).Times(0);

	runWriter(&writer);

	ASSERT_EQ(3, mObjWriteManip.count());
}

TEST_F(TestManipWriter, case_11) {
	MockWriter writer;

	// Manip
	mObjMesh1.pAttr.setManipulator(new AttrManipCmd(mManipComd));
	// No Manip
	// mObjMesh2
	// Manip
	mObjMesh3.pAttr.setManipulator(new AttrManipNoop(mManipNoop));
	// No Manip
	// mObjMesh4

	InSequence dummy;

	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh1.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(toObjString(mObjMesh3.pAttr.manipulator()).c_str()))).Times(1);
	EXPECT_CALL(writer, printLine(StrEq(ATTR_MANIP_NONE))).Times(1);

	runWriter(&writer);

	ASSERT_EQ(2, mObjWriteManip.count());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
