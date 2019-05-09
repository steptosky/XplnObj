/*
**  Copyright(C) 2019, StepToSky
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
#include <io/writer/ObjWriteState.h>

using namespace std::string_literals;

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

TEST(ObjWriteState, processAttr_bool) {
    bool state = false;
    bool calledEnable = false;
    bool calledDisable = false;

    EXPECT_FALSE(ObjWriteState::processBool(false, state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_FALSE(state);
    EXPECT_FALSE(calledEnable);
    EXPECT_FALSE(calledDisable);

    calledEnable = false;
    calledDisable = false;
    EXPECT_TRUE(ObjWriteState::processBool(true, state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_TRUE(state);
    EXPECT_TRUE(calledEnable);
    EXPECT_FALSE(calledDisable);

    calledEnable = false;
    calledDisable = false;
    EXPECT_FALSE(ObjWriteState::processBool(true, state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_TRUE(state);
    EXPECT_FALSE(calledEnable);
    EXPECT_FALSE(calledDisable);

    calledEnable = false;
    calledDisable = false;
    EXPECT_TRUE(ObjWriteState::processBool(false, state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_FALSE(state);
    EXPECT_FALSE(calledEnable);
    EXPECT_TRUE(calledDisable);
}

TEST(ObjWriteState, processAttr) {
    typedef std::optional<AttrBlend> TestAttr;
    TestAttr state;
    bool calledEnable = false;
    bool calledDisable = false;
    // empty
    EXPECT_FALSE(ObjWriteState::processAttr(TestAttr(std::nullopt), state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_EQ(TestAttr(std::nullopt), state);
    EXPECT_FALSE(calledEnable);
    EXPECT_FALSE(calledDisable);
    // new
    calledEnable = false;
    calledDisable = false;
    EXPECT_TRUE(ObjWriteState::processAttr(TestAttr(AttrBlend(AttrBlend::blend, 0.5f)), state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_EQ(AttrBlend(AttrBlend::blend, 0.5f), state);
    EXPECT_TRUE(calledEnable);
    EXPECT_FALSE(calledDisable);
    // the same
    calledEnable = false;
    calledDisable = false;
    EXPECT_FALSE(ObjWriteState::processAttr(TestAttr(AttrBlend(AttrBlend::blend, 0.5f)), state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_EQ(AttrBlend (AttrBlend::blend, 0.5f), state);
    EXPECT_FALSE(calledEnable);
    EXPECT_FALSE(calledDisable);
    // value changed
    calledEnable = false;
    calledDisable = false;
    EXPECT_TRUE(ObjWriteState::processAttr(TestAttr(AttrBlend(AttrBlend::blend, 0.75f)), state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_EQ(AttrBlend(AttrBlend::blend, 0.75f), state);
    EXPECT_TRUE(calledEnable);
    EXPECT_FALSE(calledDisable);
    // disabling
    calledEnable = false;
    calledDisable = false;
    EXPECT_TRUE(ObjWriteState::processAttr(TestAttr(std::nullopt), state, [&]() {calledEnable = true; }, [&]() {calledDisable = true; }));
    EXPECT_EQ(TestAttr(std::nullopt), state);
    EXPECT_FALSE(calledEnable);
    EXPECT_TRUE(calledDisable);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
