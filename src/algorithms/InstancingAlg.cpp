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

#include <cassert>

#include "InstancingAlg.h"
#include "xpln/obj/ObjMain.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "common/AttributeNames.h"
#include "common/Logger.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool InstancingAlg::validateAndPrepare(ObjMain & inObjMain, const IInterrupter & /*interrupt*/) {
    ULWarning << "The instance checking is in the test mode, so it may work incorrectly.";
    ULInfo << " To check whether your object is instanced, put the word DEBUG in the end of the OBJ file and run X-Plane."
            << " The log file will contain a printout about your object."
            << R"( If the word "complex" is not present and the word "additive" is (or your object does not contain multiple LODs) then your object can be instanced.)";
    // TODO checking: LOD must be additive, not selective, or only one LOD 
    bool outResult = true;
    for (const auto & lod : inObjMain.lods()) {
        Transform & rootTransform = lod->transform();
        proccessTransform(rootTransform, outResult);
    }
    return outResult;
}

void InstancingAlg::printBreakInstancing(const char * objName, const char * reason) {
    assert(objName);
    assert(reason);
    ULError << "Instancing is broken on \"" << objName << "\". The reason: " << reason;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void InstancingAlg::proccessTransform(Transform & transform, bool & outResult) {
    if (transform.hasAnim()) {
        printBreakInstancing(transform.mName.c_str(),
                             "node has animation. Animation is not allowed for instancing.");
        outResult = false;
    }

    proccessObjects(transform, outResult);

    //-------------------------------------------------------------------------
    // children

    const auto chCount = transform.childrenNum();
    for (Transform::TransformIndex i = 0; i < chCount; ++i) {
        proccessTransform(*static_cast<Transform*>(transform.childAt(i)), outResult);
    }
    //-------------------------------------------------------------------------
}

void InstancingAlg::proccessObjects(Transform & transform, bool & outResult) {
    for (auto & curr : transform.objList()) {
        if (curr->objType() == OBJ_LINE) {
            printBreakInstancing(curr->objectName().c_str(),
                                 "the object is the line object. Lines are not allowed for instancing.");
            outResult = false;
        }
        if (curr->objType() == OBJ_SMOKE) {
            printBreakInstancing(curr->objectName().c_str(),
                                 "the object is the smoke object. Smokes are not allowed for instancing.");
            outResult = false;
        }
        if (curr->objType() == OBJ_MESH) {
            auto * mesh = reinterpret_cast<ObjMesh*>(curr.get());
            proccessAttributes(*mesh, outResult);
        }
        // TODO What about the lights?
    }
}

void InstancingAlg::proccessAttributes(ObjMesh & mesh, bool & outResult) {
    if (mesh.mAttr.mManip) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has the manipulator attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
    if (mesh.mAttr.mPolyOffset) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has the \"").append(ATTR_POLY_OS)
                                                                 .append("\" attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
    if (mesh.mAttr.mBlend) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has on of the \"").append(ATTR_BLEND).append("/")
                                                                       .append(ATTR_NO_BLEND).append("/").append(ATTR_SHADOW_BLEND)
                                                                       .append("\" attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
    if (mesh.mAttr.mShiny) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has the \"").append(ATTR_SHINY_RAT)
                                                                 .append("\" attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
    if (mesh.mAttr.mCockpit) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has on of the \"").append(ATTR_COCKPIT).append("/")
                                                                       .append(ATTR_COCKPIT_REGION)
                                                                       .append("\" attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
    //-------------------------------------------------------------------------
    if (!mesh.mAttr.mIsDraw) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has the \"").append(ATTR_DRAW_DISABLE)
                                                                 .append("\" attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
    if (!mesh.mAttr.mIsCastShadow) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has the \"").append(ATTR_NO_SHADOW)
                                                                 .append("\" attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
    if (mesh.mAttr.mIsSolidForCamera) {
        printBreakInstancing(mesh.objectName().c_str(),
                             std::string("the object has the \"").append(ATTR_SOLID_CAMERA)
                                                                 .append("\" attribute which is not allowed for instancing").c_str());
        outResult = false;
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
