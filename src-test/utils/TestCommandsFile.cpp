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
#include <xpln/utils/CommandsFile.h>
#include <sstream>

using namespace xobj;
using namespace std::string_literals;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline void equals(const Command & cmd1, const Command & cmd2) {
    ASSERT_TRUE(cmd1.mId == cmd2.mId);
    ASSERT_TRUE(cmd1.mKey == cmd2.mKey);
    ASSERT_TRUE(cmd1.mDescription == cmd2.mDescription);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(CommandsFile, read_normal_drf) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    std::stringstream stream;
    stream << R"(sim/operation/quit                                 Quit X-Plane.)" << std::endl;
    stream << R"(sim/operation/screenshot                           Take a screenshot.)" << std::endl;
    stream << R"(sim/operation/show_menu                            Show the in-sim menu.)" << std::endl;
    //-----------------------
    CommandsFile cmd;
    ASSERT_NO_THROW(cmd.loadStream(stream));
    ASSERT_EQ(3, cmd.mData.size());

    ASSERT_NO_FATAL_FAILURE(equals(Command{uint64Max, "sim/operation/quit", "Quit X-Plane."},
        cmd.mData[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{uint64Max, "sim/operation/screenshot", "Take a screenshot."},
        cmd.mData[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{uint64Max, "sim/operation/show_menu", "Show the in-sim menu."},
        cmd.mData[2]));
}

TEST(CommandsFile, read_normal_drf_custom) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    std::stringstream stream;
    stream << R"(000001 sim/operation/quit                                 Quit X-Plane.)" << std::endl;
    stream << R"(sim/operation/screenshot                                  Take a screenshot.)" << std::endl;
    stream << R"(000005 sim/operation/show_menu                            Show the in-sim menu.)" << std::endl;
    //-----------------------
    CommandsFile cmd;
    ASSERT_NO_THROW(cmd.loadStream(stream));
    ASSERT_EQ(3, cmd.mData.size());
    ASSERT_EQ(6, cmd.generateId());

    ASSERT_NO_FATAL_FAILURE(equals(Command{1, "sim/operation/quit", "Quit X-Plane." },
        cmd.mData[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{uint64Max, "sim/operation/screenshot", "Take a screenshot." },
        cmd.mData[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{5, "sim/operation/show_menu", "Show the in-sim menu." },
        cmd.mData[2]));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(CommandsFile, write_normal_drf_custom) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    //-----------------------
    CommandsFile cmd;
    cmd.mData = {
        Command{uint64Max, "sim/operation/quit", "Quit X-Plane."},
        Command{3, "sim/operation/screenshot", "Take a screenshot."},
        Command{4, "sim/operation/show_menu", "Show the in - sim menu."},
    };
    //-----------------------
    std::stringstream resultStream;
    resultStream << R"(sim/operation/quit    Quit X-Plane.)" << std::endl;
    resultStream << R"(000003    sim/operation/screenshot    Take a screenshot.)" << std::endl;
    resultStream << R"(000004    sim/operation/show_menu    Show the in - sim menu.)" << std::endl;
    //-----------------------
    std::stringstream stream;
    cmd.saveStream(stream);
    ASSERT_STREQ(resultStream.str().c_str(), stream.str().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(CommandsFile, searchIdDuplicate_case1) {
    CommandsFile cmd;
    cmd.mData = {
        Command{1, "sim/operation/quit", "Quit X-Plane."},
        Command{1, "sim/operation/screenshot", "Take a screenshot."},
        Command{2, "sim/operation/show_menu", "Show the in - sim menu."},
    };
    //-----------------------
    ASSERT_THROW(cmd.searchIdDuplicate(), std::domain_error);
}

TEST(CommandsFile, searchIdDuplicate_case2) {
    CommandsFile cmd;
    cmd.mData = {
        Command{1, "sim/operation/quit", "Quit X-Plane."},
        Command{2, "sim/operation/screenshot", "Take a screenshot."},
        Command{1, "sim/operation/show_menu", "Show the in - sim menu."},
    };
    //-----------------------
    ASSERT_THROW(cmd.searchIdDuplicate(), std::domain_error);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(CommandsFile, searchKeyDuplicate_case1) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    //-----------------------
    CommandsFile cmd;
    cmd.mData = {
        Command{uint64Max, "sim/operation/quit_1", ""},
        Command{uint64Max, "sim/operation/quit_1", ""},
        Command{uint64Max, "sim/operation/quit_3", ""},
    };
    //-----------------------
    ASSERT_THROW(cmd.searchKeyDuplicate(), std::domain_error);
}

TEST(CommandsFile, searchKeyDuplicate_case2) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    //-----------------------
    CommandsFile cmd;
    cmd.mData = {
        Command{uint64Max, "sim/operation/quit_1", ""},
        Command{uint64Max, "sim/operation/quit_2", ""},
        Command{uint64Max, "sim/operation/quit_1", ""},
    };
    //-----------------------
    ASSERT_THROW(cmd.searchKeyDuplicate(), std::domain_error);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
