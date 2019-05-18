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
#include "common/Logger.h"
#include "sts/utilities/Compare.h"
#include "xpln/obj/ObjMesh.h"
#include "common/IInterrupterInternal.h"
#include "TransformAlg.h"

using namespace std::string_literals;

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool LodsAlg::validate(ObjMain::Lods & inOutLods,
                       const std::string & objectName,
                       const IInterrupter & interrupt) {

    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);

    if (inOutLods.size() == 1 && inOutLods[0]) {
        //---------------------------
        // Checking if the LOD has incorrect "near" value.
        if (inOutLods[0]->nearVal() != 0.0f) {
            ULError << objectName << " - LOD <" << inOutLods[0]->objectName()
                    << R"(> expected "near" value equals 0.0 but it equals: )" << inOutLods[0]->nearVal();
            return false;
        }
    }

    for (const auto & lod : inOutLods) {
        if (!lod) {
            continue;
        }
        //---------------------------
        // Checking if the LOD has animation.
        if (lod->transform().hasAnim()) {
            ULError << objectName << " - LOD <" << lod->objectName() << "> isn't allowed to have animation.";
            return false;
        }
        //---------------------------
        // Checking if the LOD doesn't have objects.
        INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);
        const auto hasObjects = !TransformAlg::visitObjectsConst(lod->transform(), [](const auto &, const auto &) { return false; });
        if (!hasObjects) {
            ULError << objectName << " - LOD <" << lod->objectName() << "> doesn't contain any objects.";
            return false;
        }
        //---------------------------
        // Checking "near" and "far" values.
        if (inOutLods.size() != 1 && sts::isEqual(lod->nearVal(), lod->farVal())) {
            ULError << objectName << " - LOD <" << lod->objectName()
                    << R"(> contains identical "near:)" << lod->nearVal() << R"(" and "far:)" << lod->farVal() << R"(" values.)";
            return false;
        }
        if (lod->farVal() < lod->nearVal()) {
            ULError << objectName << " - LOD <" << lod->objectName()
                    << R"(> contains "far:)" << lod->farVal() << R"(" value that is less then "near:)" << lod->nearVal() << R"(".)";
            return false;
        }
        //---------------------------
        // Checking for identical LODs.
        INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);
        auto iter = std::find_if(inOutLods.begin(), inOutLods.end(), [&](const auto & val) {
            return val && lod != val &&
                   lod->nearVal() == val->nearVal() &&
                   lod->farVal() == val->farVal();
        });

        if (iter != inOutLods.end()) {
            ULError << objectName << " - LOD <" << lod->objectName() << "> and LOD <" << (*iter)->objectName()
                    << "> have identical distance values. Merge them into one LOD.";
            return false;
        }
        //---------------------------
        // Checking hard polygons.
        INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);
        const auto hasHardPoly = !TransformAlg::visitObjectsConst(lod->transform(), [&](const Transform &, const ObjAbstract & obj) {
            if (obj.objType() != OBJ_MESH) {
                return true;
            }
            return !bool(static_cast<const ObjMesh*>(&obj)->mAttr.mHard);
        });
        if (hasHardPoly && lod->nearVal() != 0.0f) {
            ULError << objectName << " - LOD <" << lod->objectName() << "> contains hard polygons on some objects, "
                    << R"(but only the LOD whose "near" value equals "0.0" allowed to contain hard polygons)";
            return false;
        }
        //---------------------------
    }
    //-----------------------------------------------
    return true;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void LodsAlg::removeWithoutObjects(ObjMain::Lods & inOutLods, const IInterrupter & interrupt) {
    for (auto iter = inOutLods.begin(); iter != inOutLods.end();) {
        INTERRUPT_CHECK_WITH_RETURN(interrupt);
        const auto hasObjects = !TransformAlg::visitObjectsConst((*iter)->transform(), [](const auto &, const auto &) {
            return false;
        });

        if (!hasObjects) {
#ifndef NDEBUG
            LInfo << "LOD <" << (*iter)->objectName() << "> will be removed because it doesn't have any objects.";
#endif
            iter = inOutLods.erase(iter);
        }
        else {
            ++iter;
        }
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void LodsAlg::mergeIdenticalLods(ObjMain::Lods & /*inOutLods*/, const IInterrupter & interrupt) {
    INTERRUPT_CHECK_WITH_RETURN(interrupt);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool LodsAlg::sort(ObjMain::Lods & inOutLods, const IInterrupter & interrupt) {
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);
    //-------------------------------------------
    // orderings
    ObjMain::Lods orderedList;
    orderedList.reserve(inOutLods.size());
    for (auto & lod : inOutLods) {
        if (!lod) {
            continue;
        }
        if (lod->nearVal() == 0.0f) {
            float nearVal = lod->farVal();
            orderedList.emplace_back(std::move(lod));

            while (true) {
                // search next distance part
                auto iter = std::find_if(inOutLods.begin(), inOutLods.end(), [&](const auto & val) {
                    return val && nearVal == val->nearVal();
                });

                if (iter == inOutLods.end()) {
                    break;
                }
                nearVal = (*iter)->farVal();
                orderedList.emplace_back(std::move(*iter));
            }
        }
    }
    INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);

    //-------------------------------------------
    // checking remaining
    for (const auto & lod : inOutLods) {
        if (lod) {
            LError << "LOD <" << lod->objectName()
                    << R"(> "near" value can't be associated with "far" value of any other LOD.)"
                    << R"( The necessary "far" values don't exist or have already been associated with other LODs)";;
            return false;
        }
    }

    //-------------------------------------------
    inOutLods = std::move(orderedList);
    //-------------------------------------------
    return true;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
