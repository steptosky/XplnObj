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
#include <xpln/utils/DatarefsFile.h>
#include <sstream>
#include <vector>

using namespace xobj;
using namespace std::string_literals;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

typedef std::vector<Dataref> Datarefs;

inline void equals(const Dataref & drf1, const Dataref & drf2) {
    ASSERT_EQ(drf1.mId, drf2.mId);
    ASSERT_EQ(drf1.mWritable, drf2.mWritable);
    ASSERT_STREQ(drf1.mKey.c_str(), drf2.mKey.c_str());
    ASSERT_STREQ(drf1.mValueType.c_str(), drf2.mValueType.c_str());
    ASSERT_STREQ(drf1.mValueUnits.c_str(), drf2.mValueUnits.c_str());
    ASSERT_STREQ(drf1.mDescription.c_str(), drf2.mDescription.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(Dataref, isKeyId) {
    EXPECT_TRUE(Dataref::isKeyId("61256"));
    EXPECT_FALSE(Dataref::isKeyId("+01256"));
    EXPECT_FALSE(Dataref::isKeyId("v"));
    EXPECT_FALSE(Dataref::isKeyId("61A56"));
}

TEST(Dataref, keyToId) {
    EXPECT_EQ(61256, Dataref::keyToId("61256"));
    EXPECT_EQ(25, Dataref::keyToId("25test"));
    EXPECT_ANY_THROW(Dataref::keyToId("test"));
    EXPECT_ANY_THROW(Dataref::keyToId("31243656867453255687685634224580987856643535435"));
}

TEST(Dataref, invalidId) {
    ASSERT_EQ(std::numeric_limits<std::uint64_t>::max(), Dataref::invalidId());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(DatarefsFile, read_normal_drf) {
    std::stringstream stream;
    stream << " first line " << std::endl;
    stream << std::endl;
    stream << "   " << std::endl;
    stream << R"( x/y/z )" << std::endl;
    stream << R"(123456)" << std::endl;
    stream << R"( 1/a/b/1		float int		y t		Feet Meters		:d1.0 11: d1.1: d1.2:1.3)" << std::endl;
    stream << R"(1/a/b/2		float int		y t		Feet Meters		:d2.0 22: d2.1: d2.2:2.3)" << std::endl;
    stream << R"(  1/a/b/3		float int		y t		Feet Meters		:d3.0 33: d3.1: d3.2:3.3)" << std::endl;
    stream << R"(   1/a/b/4		float int		n t		Feet Meters		:d4.0 44: d4.1: d4.2:4.3)" << std::endl;

    stream << R"(1/a/b/5	float	y	Feet)" << std::endl;
    stream << R"(1/a/b/6	float	y)" << std::endl;
    stream << R"(1/a/b/7	float	)" << std::endl;
    stream << R"(1/a/b/8)";
    //-----------------------
    Datarefs datarefs;
    ASSERT_NO_THROW(DatarefsFile::loadStream(stream, [&](const Dataref &d) ->bool {
            datarefs.emplace_back(d);
            return true;
        }));
    ASSERT_EQ(10, datarefs.size());
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ false, Dataref::invalidId(), "x/y/z", "", "", ""}, datarefs[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ false, Dataref::invalidId(), "123456", "", "", ""}, datarefs[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ true, Dataref::invalidId(), "1/a/b/1", "float int", "Feet Meters", ":d1.0 11: d1.1: d1.2:1.3"}, datarefs[2]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ true, Dataref::invalidId(), "1/a/b/2", "float int", "Feet Meters", ":d2.0 22: d2.1: d2.2:2.3"}, datarefs[3]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ true, Dataref::invalidId(), "1/a/b/3", "float int", "Feet Meters", ":d3.0 33: d3.1: d3.2:3.3"}, datarefs[4]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ false, Dataref::invalidId(), "1/a/b/4", "float int", "Feet Meters", ":d4.0 44: d4.1: d4.2:4.3" }, datarefs[5]));

    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ true, Dataref::invalidId(), "1/a/b/5", "float", "Feet", "" }, datarefs[6]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ true, Dataref::invalidId(), "1/a/b/6", "float", "", "" }, datarefs[7]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ false, Dataref::invalidId(), "1/a/b/7", "float", "", "" }, datarefs[8]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ false, Dataref::invalidId(), "1/a/b/8", "", "", "" }, datarefs[9]));
}

// uses space as id and dataref delimiter
TEST(DatarefsFile, read_normal_drf_custom_case1) {
    std::stringstream stream;
    stream << " first line " << std::endl;
    stream << std::endl;
    stream << R"(  000001:1/a/b/1	float	y	Feet	:d1.0 11: d1.1: d1.2:1.3)" << std::endl;
    stream << R"(000003:   1/a/b/2	float	y	Feet	:d2.0 22: d2.1: d2.2:2.3)" << std::endl;
    stream << R"( 000005   :1/a/b/3	float	y	Feet	:d3.0 33: d3.1: d3.2:3.3)" << std::endl;
    stream << R"(1/a/b/4	float	n	Feet	:d4.0 44: d4.1: d4.2:4.3)";
    //-----------------------
    Datarefs datarefs;
    ASSERT_NO_THROW(DatarefsFile::loadStream(stream, [&](const Dataref &d) ->bool {
            datarefs.emplace_back(d);
            return true;
        }));
    ASSERT_EQ(4,datarefs.size());
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, 1, "1/a/b/1", "float", "Feet", ":d1.0 11: d1.1: d1.2:1.3" }, datarefs[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, 3, "1/a/b/2", "float", "Feet", ":d2.0 22: d2.1: d2.2:2.3" }, datarefs[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, Dataref::invalidId(), "000005", "float", "Feet", ":d3.0 33: d3.1: d3.2:3.3" }, datarefs[2]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{false, Dataref::invalidId(), "1/a/b/4", "float", "Feet", ":d4.0 44: d4.1: d4.2:4.3" }, datarefs[3]));
}

// copy of previous but uses tabs as id and dataref delimiter
TEST(DatarefsFile, read_normal_drf_custom_case2) {
    std::stringstream stream;
    stream << " first line " << std::endl;
    stream << std::endl;
    stream << R"(	000001:1/a/b/1	float	y	Feet	:d1.0 11: d1.1: d1.2:1.3)" << std::endl;
    stream << R"(000003:	1/a/b/2	float	y	Feet	:d2.0 22: d2.1: d2.2:2.3)" << std::endl;
    stream << R"( 000005	:1/a/b/3	float	y	Feet	:d3.0 33: d3.1: d3.2:3.3)" << std::endl;
    stream << R"(1/a/b/4	float	n	Feet	:d4.0 44: d4.1: d4.2:4.3)";
    //-----------------------
    Datarefs datarefs;
    ASSERT_NO_THROW(DatarefsFile::loadStream(stream, [&](const Dataref &d) ->bool {
        datarefs.emplace_back(d);
        return true;
    }));
    ASSERT_EQ(4, datarefs.size());
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ true, 1, "1/a/b/1", "float", "Feet", ":d1.0 11: d1.1: d1.2:1.3" }, datarefs[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ true, 3, "1/a/b/2", "float", "Feet", ":d2.0 22: d2.1: d2.2:2.3" }, datarefs[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ false, Dataref::invalidId(), "000005", ":1/a/b/3", "y", "Feet	:d3.0 33: d3.1: d3.2:3.3" }, datarefs[2]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{ false, Dataref::invalidId(), "1/a/b/4", "float", "Feet", ":d4.0 44: d4.1: d4.2:4.3" }, datarefs[3]));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(DatarefsFile, write_normal_drf_custom) {
    //-----------------------
    Datarefs datarefs = {
        Dataref{true, Dataref::invalidId(), "1/a/b/1", "float", "Feet", ":d1.0 11: d1.1: d1.2:1.3"},
        Dataref{false, 3, "1/a/b/2", "float", "Feet", ":d2.0 22: d2.1: d2.2:2.3"},
        Dataref{true, 4, "1/a/b/3", "float", "", ""},
        Dataref{false, Dataref::invalidId(), "1/a/b/4", "", "", ""},
    };
    //-----------------------
    std::stringstream resultStream;
    resultStream << std::endl;
    resultStream << R"(1/a/b/1	float	y	Feet	:d1.0 11: d1.1: d1.2:1.3)" << std::endl;
    resultStream << R"(000003:	1/a/b/2	float	n	Feet	:d2.0 22: d2.1: d2.2:2.3)" << std::endl;
    resultStream << R"(000004:	1/a/b/3	float	y)" << std::endl;
    resultStream << R"(1/a/b/4)" << std::endl;
    //-----------------------
    std::stringstream stream;
    std::size_t counter = 0;
    DatarefsFile::saveStream(stream, [&](Dataref & d) ->bool {
        if (counter >= datarefs.size()) {
            return false;
        }
        d = datarefs[counter++];
        return true;
    });
    ASSERT_STREQ(resultStream.str().c_str(), stream.str().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(DatarefsFile, duplicate) {
    const Datarefs datarefs = {
        Dataref{false, 1, "only_key_test_2", "", "", ""},
        Dataref{false, 1, "only_key_test_3", "", "", ""},
        Dataref{false, 2, "only_key_test_3", "", "", ""},
    };
    //-----------------------
    const auto iter = DatarefsFile::duplicate(datarefs, [&](const Dataref & d1, const Dataref & d2) ->bool {
        return d1.mId == d2.mId;
    });
    ASSERT_TRUE(iter != datarefs.end());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
