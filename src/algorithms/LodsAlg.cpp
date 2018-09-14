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

#include <algorithm>
#include "LodsAlg.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void LodsAlg::mergeIdenticalLods(ObjMain::Lods & /*inOutLods*/, const IInterrupt & /*interrupt*/) { }

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

Result LodsAlg::sort(ObjMain::Lods & inOutLods, const IInterrupt & interrupt) {
    using namespace std::string_literals;

    //-------------------------------------------
    // checking for incorrect LOD's "near" value
    if (inOutLods.size() == 1) {
        if (sts::isNotEqual(inOutLods[0]->nearVal(), 0.0f)) {
            return Result(false, "LOD <"s.append(inOutLods[0]->objectName())
                                         .append(R"(> contains incorrect "near" value)"));
        }
        inOutLods[0]->setNearVal(0.0f); // fix for float values like 0.0...01
        return Result(true);
    }
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, Result(false, "interrupted"));

    //-------------------------------------------
    // checking for incorrect LODs
    for (const auto & v : inOutLods) {
        if (sts::isEqual(v->nearVal(), v->farVal())) {
            return Result(false, "LOD <"s.append(v->objectName())
                                         .append(R"(> contains identical "near" and "far" values)"));
        }
        if (v->farVal() < v->nearVal()) {
            return Result(false, "LOD <"s.append(v->objectName())
                                         .append(R"(> contains "far" value that is less then "near")"));
        }
    }
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, Result(false, "interrupted"));

    //-------------------------------------------
    // separating LODs
    SeparatedLods separated = separateLods(inOutLods, interrupt);
    // all pointers should be nullptr after previous algorithm.
    inOutLods.clear();
    ObjMain::Lods & additiveLods = std::get<0>(separated);
    ObjMain::Lods & selectiveLods = std::get<1>(separated);
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, Result(false, "interrupted"));

    // From obj specification:
    // "LOD distances must all start from zero and be ordered from closest to farthest."
    std::sort(additiveLods.begin(), additiveLods.end(), [](const auto & i, const auto & j) {
        return i->farVal() < j->farVal();
    });

    // LODs with near value 0.0 will be before others.
    std::sort(selectiveLods.begin(), selectiveLods.end(), [](const auto & i, const auto & j) {
        return i->nearVal() < j->nearVal();
    });
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, Result(false, "interrupted"));

    //-------------------------------------------
    // orderings
    for (auto & lod : selectiveLods) {
        if (lod) {
            if (lod->nearVal() == 0.0f) {
                float nearVal = lod->farVal();
                inOutLods.emplace_back(std::move(lod));

                while (true) {
                    // search next distance
                    auto iter = std::find_if(selectiveLods.begin(), selectiveLods.end(), [&](const auto & val) {
                        return val && nearVal == val->nearVal();
                    });

                    if (iter == selectiveLods.end()) {
                        break;
                    }
                    nearVal = (*iter)->farVal();
                    inOutLods.emplace_back(std::move(*iter));
                }
            }
        }
    }
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, Result(false, "interrupted"));

    for (const auto & lod : selectiveLods) {
        if (lod) {
            return Result(false, "LOD <"s.append(lod->objectName())
                                         .append(R"(> "near" value can't be associated with "far" value of any other LOD.)")
                                         .append(R"( The necessary "far" valued don't exist or have already been associated with other LODs)"));
        }
    }

    //-------------------------------------------
    // adding additive LODs at the end.
    for (auto & v : additiveLods) {
        if (v) {
            inOutLods.emplace_back(std::move(v));
        }
    }

    //-------------------------------------------
    return Result(true);
}

LodsAlg::SeparatedLods LodsAlg::separateLods(ObjMain::Lods & inOutLods, const IInterrupt & interrupt) {
    auto out = std::make_tuple(ObjMain::Lods(), ObjMain::Lods());
    ObjMain::Lods & additiveLods = std::get<0>(out);
    ObjMain::Lods & selectiveLods = std::get<1>(out);

    for (auto & lod : inOutLods) {
        if (lod->nearVal() == 0.0f) {
            const auto found = std::any_of(inOutLods.begin(), inOutLods.end(), [&](const auto & val) {
                if (!val) {
                    return false;
                }
                return lod->farVal() == val->nearVal();
            });
            if (!found) {
                additiveLods.emplace_back(std::move(lod));
            }
        }
    }
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, out);

    for (auto & lod : inOutLods) {
        if (lod) {
            selectiveLods.emplace_back(std::move(lod));
        }
    }
    return out;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
