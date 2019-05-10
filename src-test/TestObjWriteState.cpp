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
#include <io/ObjWriteState.h>

using namespace std::string_literals;

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

TEST(ObjWriteState, processAttr_bool) {
    bool state = false;
    bool switchEnable = false;
    bool called = false;

    ObjWriteState::processBool(false, state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_FALSE(state);
    EXPECT_FALSE(switchEnable);
    EXPECT_FALSE(called);

    switchEnable = false;
    called = false;
    ObjWriteState::processBool(true, state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_TRUE(state);
    EXPECT_TRUE(switchEnable);
    EXPECT_TRUE(called);

    switchEnable = false;
    called = false;
    ObjWriteState::processBool(true, state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_TRUE(state);
    EXPECT_FALSE(switchEnable);
    EXPECT_FALSE(called);

    switchEnable = false;
    called = false;
    ObjWriteState::processBool(false, state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_FALSE(state);
    EXPECT_FALSE(switchEnable);
    EXPECT_TRUE(called);
}

TEST(ObjWriteState, processAttr) {
    typedef std::optional<AttrBlend> TestAttr;
    TestAttr state;
    bool switchEnable = false;
    bool called = false;
    // empty
    ObjWriteState::processAttr(TestAttr(std::nullopt), state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_EQ(TestAttr(std::nullopt), state);
    EXPECT_FALSE(switchEnable);
    EXPECT_FALSE(called);
    // new
    switchEnable = false;
    called = false;
    ObjWriteState::processAttr(TestAttr(AttrBlend(AttrBlend::blend, 0.5f)), state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_EQ(AttrBlend(AttrBlend::blend, 0.5f), state);
    EXPECT_TRUE(switchEnable);
    EXPECT_TRUE(called);
    // the same
    switchEnable = false;
    called = false;
    ObjWriteState::processAttr(TestAttr(AttrBlend(AttrBlend::blend, 0.5f)), state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_EQ(AttrBlend (AttrBlend::blend, 0.5f), state);
    EXPECT_FALSE(switchEnable);
    EXPECT_FALSE(called);
    // value changed
    switchEnable = false;
    called = false;
    ObjWriteState::processAttr(TestAttr(AttrBlend(AttrBlend::blend, 0.75f)), state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_EQ(AttrBlend(AttrBlend::blend, 0.75f), state);
    EXPECT_TRUE(switchEnable);
    EXPECT_TRUE(called);
    // disabling
    switchEnable = false;
    called = false;
    ObjWriteState::processAttr(TestAttr(std::nullopt), state, [&](const bool enable) {
        switchEnable = enable;
        called = true;
    });
    EXPECT_EQ(TestAttr(std::nullopt), state);
    EXPECT_FALSE(switchEnable);
    EXPECT_TRUE(called);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
