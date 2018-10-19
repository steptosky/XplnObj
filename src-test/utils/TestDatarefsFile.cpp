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
    ASSERT_TRUE(drf1.mId == drf2.mId);
    ASSERT_TRUE(drf1.mKey == drf2.mKey);
    ASSERT_TRUE(drf1.mWritable == drf2.mWritable);
    ASSERT_TRUE(drf1.mValueType == drf2.mValueType);
    ASSERT_TRUE(drf1.mValueUnits == drf2.mValueUnits);
    ASSERT_TRUE(drf1.mDescription == drf2.mDescription);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(DatarefsFile, read_normal_drf) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    std::stringstream stream;
    stream << " first line " << std::endl;
    stream << std::endl;
    stream << R"(sim/aircraft/autopilot/vvi_step_ft	float	y	Feet	Step increment for autopilot VVI)" << std::endl;
    stream << R"(sim/aircraft/engine/acf_max_OILP	float	y	???	Max Oil.)" << std::endl;
    stream << R"(sim/aircraft/view/acf_Vno	float	y)" << std::endl;
    stream << R"(only_key_test)" << std::endl;
    //-----------------------
    Datarefs datarefs;
    ASSERT_NO_THROW(DatarefsFile::loadStream(stream, [&](const Dataref &d) ->bool {
            datarefs.emplace_back(d);
            return true;
        }));
    ASSERT_EQ(4, datarefs.size());

    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, uint64Max, "sim/aircraft/autopilot/vvi_step_ft", "float", "Feet", "Step increment for autopilot VVI"},
        datarefs[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, uint64Max, "sim/aircraft/engine/acf_max_OILP", "float", "???", "Max Oil."},
        datarefs[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, uint64Max, "sim/aircraft/view/acf_Vno", "float", "", ""},
        datarefs[2]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{false, uint64Max, "only_key_test", "", "", "" },
        datarefs[3]));
}

TEST(DatarefsFile, read_normal_drf_custom) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    std::stringstream stream;
    stream << " first line " << std::endl;
    stream << std::endl;
    stream << R"(000001	sim/aircraft/autopilot/vvi_step_ft	float	y	Feet	Step increment for autopilot VVI)" << std::endl;
    stream << R"(000005	sim/aircraft/engine/acf_max_OILP	float	y	???	Max Oil.)" << std::endl;
    stream << R"(sim/aircraft/view/acf_Vno	float	y)" << std::endl;
    stream << R"(000002	only_key_test_1)" << std::endl;
    stream << R"(#000008	only_key_test_2)" << std::endl;
    //-----------------------
    Datarefs datarefs;
    ASSERT_NO_THROW(DatarefsFile::loadStream(stream, [&](const Dataref &d) ->bool {
            datarefs.emplace_back(d);
            return true;
        }));
    ASSERT_EQ(4,datarefs.size());

    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, 1, "sim/aircraft/autopilot/vvi_step_ft", "float", "Feet", "Step increment for autopilot VVI" },
        datarefs[0]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, 5, "sim/aircraft/engine/acf_max_OILP", "float", "???", "Max Oil." },
        datarefs[1]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{true, uint64Max, "sim/aircraft/view/acf_Vno", "float", "", "" },
        datarefs[2]));
    ASSERT_NO_FATAL_FAILURE(equals(Dataref{false, 2, "only_key_test_1", "", "", "" },
        datarefs[3]));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(DatarefsFile, write_normal_drf_custom) {
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    //-----------------------
    Datarefs datarefs = {
        Dataref{true, uint64Max, "sim/aircraft/autopilot/vvi_step_ft", "float", "Feet", "Step increment for autopilot VVI"},
        Dataref{false, 3, "sim/aircraft/engine/acf_max_OILP", "float", "???", "Max Oil."},
        Dataref{true, 4, "sim/aircraft/view/acf_Vno", "float", "", ""},
        Dataref{false, uint64Max, "only_key_test_1", "", "", ""},
    };
    //-----------------------
    std::stringstream resultStream;
    resultStream << std::endl;
    resultStream << R"(sim/aircraft/autopilot/vvi_step_ft	float	y	Feet	Step increment for autopilot VVI)" << std::endl;
    resultStream << R"(000003	sim/aircraft/engine/acf_max_OILP	float	n	???	Max Oil.)" << std::endl;
    resultStream << R"(000004	sim/aircraft/view/acf_Vno	float	y)" << std::endl;
    resultStream << R"(only_key_test_1)" << std::endl;
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
