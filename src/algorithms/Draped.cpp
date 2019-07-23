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

#include "Draped.h"
#include "xpln/obj/ObjDrapedGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "common/IInterrupterInternal.h"
#include "TransformAlg.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void Draped::ensureDrapedAttrIsSet(ObjDrapedGroup & inOutDraped, const IInterrupter & interrupt) {
    TransformAlg::visitObjects(inOutDraped.transform(), [&](const Transform &, ObjAbstract & obj) {
        if (obj.objType() == OBJ_MESH) {
            static_cast<ObjMesh*>(&obj)->mAttr.mIsDraped = true;
        }
        INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);
        return true;
    });
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void Draped::extractDrapedObjects(ObjDrapedGroup & inOutDraped, Transform & inOutTransform, const IInterrupter & interrupt) {
    Transform::ObjList drapedObjects;
    extractDrapedObjects(inOutTransform, drapedObjects, interrupt);

    for (auto & obj : drapedObjects) {
        obj->applyTransform(inOutDraped.transform().mMatrix.inverse());
        inOutDraped.transform().mObjects.emplace_back(std::move(obj));
    }
}

void Draped::extractDrapedObjects(Transform & transform, Transform::ObjList & outObjects, const IInterrupter & interrupt) {
    const auto size = outObjects.size();
    extractDrapedObjects(transform.mObjects, outObjects, interrupt);

    if (size != outObjects.size()) {
        const auto animatedParent = TransformAlg::animatedParent(transform);
        for (auto it = outObjects.begin() + size; it != outObjects.end(); ++it) {
            (*it)->applyTransform(transform.mMatrix);
            if (animatedParent) {
                XULWarning << " Animated transform < " << animatedParent->mName
                        << "> contains draped object <" << (*it)->objectName() << "> in transform <" << transform.mName << ">."
                        << " Draped geometry must not be animated.";
            }
        }
    }

    for (auto & ch : transform) {
        INTERRUPT_CHECK_WITH_RETURN(interrupt);
        extractDrapedObjects(*ch, outObjects, interrupt);
    }
}

void Draped::extractDrapedObjects(Transform::ObjList & objects, Transform::ObjList & outObjects, const IInterrupter & interrupt) {
    for (auto objIt = objects.begin(); objIt != objects.end();) {
        INTERRUPT_CHECK_WITH_RETURN(interrupt);

        if ((*objIt)->objType() != OBJ_MESH) {
            ++objIt;
            continue;
        }
        if (!static_cast<ObjMesh*>((*objIt).get())->mAttr.mIsDraped) {
            ++objIt;
            continue;
        }
        outObjects.emplace_back(std::move(*objIt));
        objIt = objects.erase(objIt);
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
