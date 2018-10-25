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
#include "xpln/obj/ObjMain.h"
#include "xpln/obj/ObjLodGroup.h"
#include <algorithms/LodsAlg.h>
#include "../TestUtilsObjMesh.h"

using namespace xobj;

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

inline void printLods(const ObjMain::Lods & lods) {
    std::stringstream out;
    for (const auto & lod : lods) {
        out << std::setw(5) << std::setprecision(1) << std::fixed
                << lod->nearVal()
                << " : "
                << lod->farVal()
                << std::endl;
    }
    std::cout << out.str();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(LodsAlg, sorting_normal_case1) {
    ObjMain::Lods lods;
    lods.emplace_back(std::make_unique<ObjLodGroup>("0", 0.0f, 50.f));     // additive 1
    lods.emplace_back(std::make_unique<ObjLodGroup>("1", 0.0f, 100.f));    // selective 1
    lods.emplace_back(std::make_unique<ObjLodGroup>("2", 0.0f, 25.f));     // additive 2
    lods.emplace_back(std::make_unique<ObjLodGroup>("3", 200.0f, 300.0f)); // selective 1:1:1
    lods.emplace_back(std::make_unique<ObjLodGroup>("4", 100.0f, 200.0f)); // selective 1:1
    lods.emplace_back(std::make_unique<ObjLodGroup>("5", 0.0f, 200.f));    // selective 2
    lods.emplace_back(std::make_unique<ObjLodGroup>("6", 300.0f, 400.0f)); // selective 2:2:2
    lods.emplace_back(std::make_unique<ObjLodGroup>("7", 200.0f, 300.0f)); // selective 2:2

    ASSERT_TRUE(LodsAlg::sort(lods, NoInterrupter()));
    printLods(lods);

    EXPECT_STREQ("0", lods.at(0)->objectName().c_str());
    EXPECT_STREQ("1", lods.at(1)->objectName().c_str());
    EXPECT_STREQ("4", lods.at(2)->objectName().c_str());
    EXPECT_STREQ("3", lods.at(3)->objectName().c_str());
    EXPECT_STREQ("6", lods.at(4)->objectName().c_str());
    EXPECT_STREQ("2", lods.at(5)->objectName().c_str());
    EXPECT_STREQ("5", lods.at(6)->objectName().c_str());
    EXPECT_STREQ("7", lods.at(7)->objectName().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(LodsAlg, sorting_incorrect_case1) {
    ObjMain::Lods lods;
    // 1 LOD starts with incorrect value
    lods.emplace_back(std::make_unique<ObjLodGroup>("0", 10.0f, 50.f)); // [incorrect]

    ASSERT_FALSE(LodsAlg::sort(lods, NoInterrupter()));
}

TEST(LodsAlg, sorting_incorrect_case2) {
    ObjMain::Lods lods;
    // near and far equal
    lods.emplace_back(std::make_unique<ObjLodGroup>("0", 0.0f, 25.f));
    lods.emplace_back(std::make_unique<ObjLodGroup>("1", 100.f, 100.f)); // [incorrect]

    ASSERT_FALSE(LodsAlg::sort(lods, NoInterrupter()));
}

TEST(LodsAlg, sorting_incorrect_case3) {
    ObjMain::Lods lods;
    // far less than near
    lods.emplace_back(std::make_unique<ObjLodGroup>("0", 0.0f, 25.f));
    lods.emplace_back(std::make_unique<ObjLodGroup>("1", 100.f, 50.f)); // [incorrect]

    ASSERT_FALSE(LodsAlg::sort(lods, NoInterrupter()));
}

TEST(LodsAlg, sorting_incorrect_case4) {
    ObjMain::Lods lods;
    // 1 LOD starts with incorrect value
    lods.emplace_back(std::make_unique<ObjLodGroup>("0", 0.0f, 50.f));     // additive 1
    lods.emplace_back(std::make_unique<ObjLodGroup>("1", 0.0f, 100.f));    // selective 1
    lods.emplace_back(std::make_unique<ObjLodGroup>("2", 200.0f, 300.0f)); // selective 1:1:1
    lods.emplace_back(std::make_unique<ObjLodGroup>("3", 150.0f, 200.0f)); // selective 1:1 [incorrect]

    ASSERT_FALSE(LodsAlg::sort(lods, NoInterrupter()));
}

TEST(LodsAlg, sorting_incorrect_case5) {
    ObjMain::Lods lods;
    // 2 LODs start with the same value 
    lods.emplace_back(std::make_unique<ObjLodGroup>("0", 0.0f, 50.f));    // additive 1
    lods.emplace_back(std::make_unique<ObjLodGroup>("1", 0.0f, 100.f));   // selective 1
    lods.emplace_back(std::make_unique<ObjLodGroup>("2", 100.f, 300.0f)); // selective 1:1:1
    lods.emplace_back(std::make_unique<ObjLodGroup>("3", 100.f, 200.0f)); // selective 1:1 [incorrect]

    ASSERT_FALSE(LodsAlg::sort(lods, NoInterrupter()));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(LodsAlg, removeWithoutObjects) {
    ObjMain::Lods lods;
    // 2 LODs start with the same value 
    lods.emplace_back(std::make_unique<ObjLodGroup>("0", 0.0f, 50.f));
    lods.emplace_back(std::make_unique<ObjLodGroup>("1", 0.0f, 100.f));
    lods.emplace_back(std::make_unique<ObjLodGroup>("2", 100.f, 300.0f));

    lods[0]->transform().addObject(TestUtilsObjMesh::createPyramidTestMesh("m1"));
    LodsAlg::removeWithoutObjects(lods, NoInterrupter());

    ASSERT_EQ(1, lods.size());
    ASSERT_STREQ("0", lods[0]->objectName().c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
