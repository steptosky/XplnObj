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
#include <vector>

using namespace xobj;
using namespace std::string_literals;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

typedef std::vector<Command> Commands;

inline void equals(const Command & cmd1, const Command & cmd2) {
    ASSERT_EQ(cmd1.mId, cmd2.mId);
    ASSERT_STREQ(cmd1.mKey.c_str() ,cmd2.mKey.c_str());
    ASSERT_STREQ(cmd1.mDescription.c_str(), cmd2.mDescription.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(Command, isKeyId) {
    EXPECT_TRUE(Command::isKeyId("61256"));
    EXPECT_FALSE(Command::isKeyId("+01256"));
    EXPECT_FALSE(Command::isKeyId("v"));
    EXPECT_FALSE(Command::isKeyId("61A56"));
}

TEST(Command, keyToId) {
    EXPECT_EQ(61256, Command::keyToId("61256"));
    EXPECT_EQ(25, Command::keyToId("25test"));
    EXPECT_ANY_THROW(Command::keyToId("test"));
    EXPECT_ANY_THROW(Command::keyToId("31243656867453255687685634224580987856643535435"));
}

TEST(Command, invalidId) {
    ASSERT_EQ(std::numeric_limits<std::uint64_t>::max(), Command::invalidId());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(CommandsFile, read_normal_cmd) {
    std::stringstream stream;
    // it also checks id delimiter in the description - it should be ignored.
    stream << std::endl;
    stream << "   " << std::endl;
    stream << R"( x/y/z )" << std::endl;
    stream << R"(123456)" << std::endl;
    stream << R"( 1/a/b/1       11: :d1.0 d1.1: d1.2:1.3)" << std::endl;
    stream << R"(1/a/b/2        22: :d2.0 d2.1: d2.2:2.3)" << std::endl;
    stream << R"(  1/a/b/3      33: :d3.0 d3.1: d3.2:3.3)" << std::endl;
    stream << R"(   1/a/b/4     44: :d4.0 d4.1: d4.2:4.3)";
    //-----------------------
    Commands commands;
    ASSERT_NO_THROW(CommandsFile::loadStream(stream, [&](const Command &c) ->bool {
            commands.emplace_back(c);
            return true;
        }));
    ASSERT_EQ(6, commands.size());
    EXPECT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "x/y/z", "" }, commands[0]));
    EXPECT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "123456", "" }, commands[1]));
    EXPECT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "1/a/b/1", "11: :d1.0 d1.1: d1.2:1.3" }, commands[2]));
    EXPECT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "1/a/b/2", "22: :d2.0 d2.1: d2.2:2.3" }, commands[3]));
    EXPECT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "1/a/b/3", "33: :d3.0 d3.1: d3.2:3.3" }, commands[4]));
    EXPECT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "1/a/b/4", "44: :d4.0 d4.1: d4.2:4.3"}, commands[5]));
}

TEST(CommandsFile, read_normal_cmd_custom) {
    std::stringstream stream;
    stream << R"(  000001: x/y/z       00: :d0.0 d0.1: d0.2:0.3)" << std::endl;
    stream << R"(  000006:1/a/b/1      11: :d1.0 d1.1: d1.2:1.3)" << std::endl;
    stream << R"(000003:   1/a/b/2     22: :d2.0 d2.1: d2.2:2.3)" << std::endl;
    stream << R"( 000005   :1/a/b/3    33: :d3.0 d3.1: d3.2:3.3)" << std::endl;
    stream << R"(1/a/b/4               44: :d4.0 d4.1: d4.2:4.3)";
    //-----------------------
    Commands commands;
    ASSERT_NO_THROW(CommandsFile::loadStream(stream, [&](const Command &c) ->bool {
            commands.emplace_back(c);
            return true;
        }));
    ASSERT_EQ(5, commands.size());
    ASSERT_NO_FATAL_FAILURE(equals(Command{ 1, "x/y/z", "00: :d0.0 d0.1: d0.2:0.3" }, commands[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{ 6, "1/a/b/1", "11: :d1.0 d1.1: d1.2:1.3" }, commands[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{ 3, "1/a/b/2", "22: :d2.0 d2.1: d2.2:2.3" }, commands[2]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "000005", ":1/a/b/3    33: :d3.0 d3.1: d3.2:3.3" }, commands[3]));
    ASSERT_NO_FATAL_FAILURE(equals(Command{ Command::invalidId(), "1/a/b/4", "44: :d4.0 d4.1: d4.2:4.3" }, commands[4]));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(CommandsFile, write_normal_cmd_custom) {
    Commands commands = {
        Command{Command::invalidId(), "1/a/b/1", ":d1.0  d1.1: d1.2:1.3"},
        Command{3, "1/a/b/2", ":d2.0  d2.1: d2.2:2.3"},
        Command{4, "1/a/b/3", ":d3.0  d3.1: d3.2:3.3"},
    };
    //-----------------------
    std::stringstream resultStream;
    resultStream << R"(1/a/b/1    :d1.0  d1.1: d1.2:1.3)" << std::endl;
    resultStream << R"(000003:    1/a/b/2    :d2.0  d2.1: d2.2:2.3)" << std::endl;
    resultStream << R"(000004:    1/a/b/3    :d3.0  d3.1: d3.2:3.3)" << std::endl;
    //-----------------------
    std::stringstream stream;
    std::size_t counter = 0;
    CommandsFile::saveStream(stream, [&](Command & d) ->bool {
        if (counter >= commands.size()) {
            return false;
        }
        d = commands[counter++];
        return true;
    });
    ASSERT_STREQ(resultStream.str().c_str(), stream.str().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(CommandsFile, duplicate) {
    Commands commands = {
        Command{1, "sim/operation/quit", "Quit X-Plane."},
        Command{1, "sim/operation/screenshot", "Take a screenshot."},
        Command{2, "sim/operation/show_menu", "Show the in - sim menu."},
    };
    //-----------------------
    const auto iter = CommandsFile::duplicate(commands, [&](const Command & d1, const Command & d2) ->bool {
        return d1.mId == d2.mId;
    });
    ASSERT_TRUE(iter != commands.end());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
