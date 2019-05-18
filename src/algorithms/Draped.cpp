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
    TransformAlg::visitObjects(inOutDraped.transform(), [&](Transform &, ObjAbstract & obj) {
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

void Draped::extract(ObjDrapedGroup & inOutDraped,
                     Transform & inOutTransform,
                     const IInterrupter & interrupt) {

    auto drapedObjects = processObjects(inOutTransform);
    if (!drapedObjects.empty()) {
        const Transform * animatedTransform = TransformAlg::animatedParent(inOutTransform);
        if (animatedTransform) {
            ULWarning << " Object <" << inOutDraped.objectName() << "> has animated transform <" << animatedTransform->mName
                    << "> containing draped geometry in transform <" << inOutTransform.mName << ">."
                    << " Draped geometry can't be animated.";
        }

        for (auto & obj : drapedObjects) {
            obj->applyTransform(inOutDraped.transform().mMatrix.inversed());
            inOutDraped.transform().addObject(obj.release());
        }
    }

    for (auto & child : inOutTransform) {
        INTERRUPT_CHECK_WITH_RETURN(interrupt);
        extract(inOutDraped, *child, interrupt);
    }
}

Transform::ObjList Draped::processObjects(Transform & transform) {
    Transform::ObjList out;
    for (auto & obj : transform.objects()) {
        if (obj->objType() != OBJ_MESH) {
            continue;
        }
        auto mesh = static_cast<ObjMesh*>(obj.get());
        if (mesh->mAttr.mIsDraped) {
            mesh->applyTransform(transform.mMatrix);
            out.emplace_back(mesh);
        }
    }
    for (auto & obj : out) {
        transform.takeObject(obj.get());
    }
    return out;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
