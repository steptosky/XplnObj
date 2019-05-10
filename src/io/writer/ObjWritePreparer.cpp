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

#include "ObjWritePreparer.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "ObjWriteAnim.h"
#include "io/ObjValidators.h"
#include "algorithms/LodsAlg.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ObjWritePreparer::prepare(ObjMain & mainObj) {
    const size_t lodCount = mainObj.lods().size();
    for (size_t i = 0; i < lodCount; ++i) {
        ObjLodGroup & lod = *mainObj.lods().at(i);
        Transform & rootTransform = lod.transform();
        if (!proccessTransform(rootTransform, i, lod)) {
            return false;
        }
    }
    return true;
}

void ObjWritePreparer::deleteEmptyTransformsRecursively(Transform & transform) {
    const auto childrenNum = transform.childrenNum();
    std::vector<Transform*> forDelete;
    for (Transform::TransformIndex i = 0; i < childrenNum; ++i) {
        const auto currChild = transform.childAt(i);
        deleteEmptyTransformsRecursively(*currChild);

        if (!currChild->hasObjects() && currChild->childrenNum() == 0) {
            forDelete.emplace_back(currChild);
        }
    }

    for (const auto child : forDelete) {
        transform.deleteChild(child);
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ObjWritePreparer::proccessTransform(Transform & transform, const size_t lodNumber, const ObjLodGroup & lod) {
    if (!checkParameters(transform, transform.name())) {
        return false;
    }

    if (!proccessObjects(transform, lodNumber, lod)) {
        return false;
    }
    //-------------------------------------------------------------------------
    // children

    const Transform::TransformIndex chCount = transform.childrenNum();
    for (Transform::TransformIndex i = 0; i < chCount; ++i) {
        if (!proccessTransform(*static_cast<Transform*>(transform.childAt(i)), lodNumber, lod)) {
            return false;
        }
    }
    //-------------------------------------------------------------------------

    return true;
}

bool ObjWritePreparer::proccessObjects(Transform & transform, const size_t /*lodNumber*/, const ObjLodGroup & /*lod*/) {
    std::vector<ObjAbstract*> objToDelete;
    for (const auto & curr : transform.objList()) {
        if (!checkParameters(*curr, curr->objectName())) {
            objToDelete.emplace_back(curr.get());
        }
        else {
            checkForTwoSided(*curr);
        }
    }
    for (auto & curr : objToDelete) {
        transform.removeObject(curr);
    }
    return true;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWritePreparer::checkForTwoSided(ObjAbstract & obj) {
    if (obj.objType() != OBJ_MESH) {
        return;
    }
    auto * mesh = static_cast<ObjMesh*>(&obj);
    if (mesh->mAttr.mIsTwoSided) {
        mesh->makeTwoSided();
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
