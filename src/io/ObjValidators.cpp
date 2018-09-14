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

#include "ObjValidators.h"
#include "io/StringValidator.h"
#include "common/Logger.h"
#include "sts/utilities/Compare.h"

#include "xpln/obj/attributes/AttrGlobSet.h"

#include "xpln/obj/ObjDummy.h"
#include "xpln/obj/ObjLine.h"
#include "xpln/obj/ObjMain.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/ObjSmoke.h"

#include "xpln/obj/animation/AnimVisibilityKey.h"
#include "xpln/obj/animation/AnimTrans.h"
#include "xpln/obj/animation/AnimRotate.h"

#include "xpln/obj/ObjLightCustom.h"
#include "xpln/obj/ObjLightNamed.h"
#include "xpln/obj/ObjLightParam.h"
#include "xpln/obj/ObjLightPoint.h"
#include "xpln/obj/ObjLightSpillCust.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

bool checkParameters(const AttrGlobSet & attrSet, const std::string & prefix) {
    if (attrSet.texture() == "none" || attrSet.texture().empty()) {
        ULWarning << prefix << " - Texture is not specified";
    }
    bool result = true;
    if (StringValidator::hasIllegalSymbols(attrSet.texture())) {
        result = false;
        ULError << prefix << " contains illegal symbols in the texture name <" << attrSet.texture() << ">";
    }
    if (StringValidator::hasIllegalSymbols(attrSet.textureLit())) {
        result = false;
        ULError << prefix << " contains illegal symbols in the lit texture name <" << attrSet.textureLit() << ">";
    }
    if (StringValidator::hasIllegalSymbols(attrSet.textureNormal())) {
        result = false;
        ULError << prefix << " contains illegal symbols in the normal texture name <" << attrSet.textureNormal() << ">";
    }
    return result;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

bool findHardPolygons(const ObjAbstract & baseObj, const std::string & lodName) {
    if (baseObj.objType() != eObjectType::OBJ_MESH) {
        return false;
    }
    const auto * mesh = static_cast<const ObjMesh*>(&baseObj);
    if (!mesh->pAttr.hard()) {
        return false;
    }
    ULError << lodName << " LOD contains hard polygons in object <" << baseObj.objectName()
            << ">. Only the first LOD allowed to contain hard polygons";
    return true;
}

/***************************************************************************************/

bool checkParameters(const ObjAbstract & baseObj, const std::string & prefix) {
    switch (baseObj.objType()) {
        case OBJ_NO: return true;
        case OBJ_MESH: return checkParameters(static_cast<const ObjMesh&>(baseObj), prefix);
        case OBJ_LINE: return checkParameters(static_cast<const ObjLine&>(baseObj), prefix);
        case OBJ_LIGHT_NAMED: return checkParameters(static_cast<const ObjLightNamed&>(baseObj), prefix);
        case OBJ_LIGHT_CUSTOM: return checkParameters(static_cast<const ObjLightCustom&>(baseObj), prefix);
        case OBJ_LIGHT_PARAM: return checkParameters(static_cast<const ObjLightParam&>(baseObj), prefix);
        case OBJ_LIGHT_SPILL_CUSTOM: return checkParameters(static_cast<const ObjLightSpillCust&>(baseObj), prefix);
        case OBJ_LIGHT_POINT: return checkParameters(static_cast<const ObjLightPoint&>(baseObj), prefix);
        case OBJ_SMOKE: return checkParameters(static_cast<const ObjSmoke&>(baseObj), prefix);
        case OBJ_DUMMY: return checkParameters(static_cast<const ObjDummy&>(baseObj), prefix);
        default: return true;
    }
}

/***************************************************************************************/

bool checkParameters(const ObjDummy & /*obj*/, const std::string & /*prefix*/) {
    // TODO #Implementation
    return true;
}

bool checkParameters(const ObjLine & /*obj*/, const std::string & /*prefix*/) {
    // TODO #Implementation
    return true;
}

bool checkParameters(const ObjMain & mainObj, const std::string & prefix) {
    bool result = true;
    if (mainObj.pAttr.isDebug()) {
        ULWarning << prefix
                << " - \"DEBUG\" option is enabled. Turn it off if you don't know what it is or if you don't need it.";
    }
    if (result) {
        result = checkParameters(mainObj.pAttr, prefix);
    }
    return result;
}

bool checkParameters(const ObjMesh & obj, const std::string & prefix) {
    bool result = true;
    if (obj.pVertices.empty()) {
        result = false;
        LError << prefix << " - Doesn't have any vertices.";
    }

    if (obj.pFaces.empty()) {
        result = false;
        LError << prefix << " - Doesn't have any faces.";
    }
    {
        std::vector<bool> vertUsed(obj.pVertices.size(), false);
        const size_t vertSize = vertUsed.size();
        for (size_t i = 0; i < obj.pFaces.size(); ++i) {
            const MeshFace & currFace = obj.pFaces[i];
            if (currFace.pV0 >= vertSize || currFace.pV1 >= vertSize || currFace.pV2 >= vertSize) {
                result = false;
                LError << prefix << " - The face [" << i << "] is out of the vertices range.";
                return result;
            }
            vertUsed[currFace.pV0] = true;
            vertUsed[currFace.pV1] = true;
            vertUsed[currFace.pV2] = true;
        }
        for (size_t i = 0; i < vertUsed.size(); ++i) {
            if (!vertUsed[i]) {
                result = false;
                LError << prefix << " - The vertex [" << i << "] is isolated.";
            }
        }
    }
    return result;
}

bool checkParameters(const ObjSmoke & obj, const std::string & prefix) {
    bool result = true;
    if (obj.size() < 0.1f) {
        result = false;
        ULError << prefix << " - Smoke size is too small.";
    }
    return result;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool checkParameters(const Transform & /*transform*/, const std::string & /*prefix*/) {
    return true;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

bool checkParameters(const AnimTransKey & /*key*/, const std::string & /*prefix*/) {
    return true;
}

//-------------------------------------------------------------------------

bool checkParameters(const AnimVisibilityKey & key, const std::string & prefix) {
    bool result = true;
    std::string currtype;
    switch (key.pType) {
        case AnimVisibilityKey::SHOW:
            currtype = " - Show: ";
            break;
        case AnimVisibilityKey::HIDE:
            currtype = " - Hide: ";
            break;
        case AnimVisibilityKey::UNDEFINED:
            currtype = " - Undefined: ";
            break;
    }

    if (key.pType == AnimVisibilityKey::UNDEFINED) {
        result = false;
        ULError << prefix.c_str() << " - The visible key is undefined";
    }

    if (key.pDrf.empty() || key.pDrf == "none") {
        result = false;
        ULError << prefix.c_str() << currtype.c_str() << "Dataref isn't specified.";
    }

    if (StringValidator::hasIllegalSymbols(key.pDrf)) {
        result = false;
        ULError << prefix.c_str() << currtype.c_str() << "Dataref contains illegal symbols.";
    }

    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const AnimTrans & anim, const std::string & prefix) {
    bool result = true;

    if (anim.pKeys.empty()) {
        result = false;
        ULError << prefix << " - Does not contain any keys.";
    }

    if (anim.pKeys.size() == 1) {
        result = false;
        ULError << prefix << " - Contains only one key.";
    }

    if (anim.pKeys.size() != 2) {
        if (anim.pDrf.empty() || anim.pDrf == "none") {
            result = false;
            ULError << prefix << " - Dataref isn't specified.";
        }
    }

    if (StringValidator::hasIllegalSymbols(anim.pDrf)) {
        result = false;
        ULError << prefix << " - Dataref contains illegal symbols.";
    }

    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const AnimRotate & anim, const std::string & prefix) {
    bool result = true;

    if (anim.pKeys.empty()) {
        result = false;
        ULError << prefix << " - Does not contain any keys.";
    }

    if (anim.pKeys.size() == 1) {
        result = false;
        ULError << prefix << " - Contains only one key.";
    }

    if (anim.pKeys.size() != 2) {
        if (anim.pDrf.empty() || anim.pDrf == "none") {
            result = false;
            ULError << prefix.c_str() << " - Dataref isn't specified.";
        }
    }

    if (StringValidator::hasIllegalSymbols(anim.pDrf)) {
        result = false;
        ULError << prefix.c_str() << " - Dataref contains illegal symbols.";
    }

    return result;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool checkParameters(const ObjLightCustom & inVal, const std::string & inPrefix) {
    bool result = true;
    if (inVal.size() < 1.0f) {
        ULWarning << inPrefix << " - Using too small the light size. Perhaps it is a mistake.";
    }

    const RectangleI & rect = inVal.textureRect();
    if (sts::isEqual(rect.point1().x, rect.point2().x)) {
        result = false;
        ULWarning << inPrefix << " - S1 and S2 should not be equaled.";
    }
    if (sts::isEqual(rect.point1().y, rect.point2().y)) {
        result = false;
        ULWarning << inPrefix << " - T1 and T2 can't be equaled.";
    }

    if (StringValidator::hasIllegalSymbols(inVal.dataRef())) {
        result = false;
        ULError << inPrefix << " - Dataref contains illegal symbols.";
    }

    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const ObjLightNamed & inVal, const std::string & inPrefix) {
    bool result = true;
    if (!inVal.lightId().isValid()) {
        result = false;
        ULError << inPrefix << " - Light objectName isn't specified.";
    }
    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const ObjLightParam & inVal, const std::string & inPrefix) {
    bool result = true;
    if (!inVal.lightId().isValid()) {
        result = false;
        ULError << inPrefix << " - Light objectName isn't specified.";
    }
    if (inVal.lightId() == ELightParams(ELightParams::light_params_custom)) {
        if (inVal.lightName().empty()) {
            result = false;
            ULError << inPrefix << " - Custom light name isn't specified.";
        }
    }
    if (inVal.additionalParams().empty()) {
        result = false;
        ULError << inPrefix << " - Parameters isn't specified.";
    }
    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const ObjLightPoint & inVal, const std::string & inPrefix) {
    bool result = true;
    if (inVal.color().red() == 0.0 &&
        inVal.color().green() == 0.0 &&
        inVal.color().blue() == 0.0) {
        result = false;
        ULError << inPrefix << " - Color isn't specified.";
    }
    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const ObjLightSpillCust & inVal, const std::string & inPrefix) {
    bool result = true;
    const float semmi = inVal.semiRaw();
    if (semmi > 1.0f || semmi < 0.0f) {
        result = false;
        ULError << inPrefix << " - The semi value must be between 0.0 - 1.0";
    }

    if (semmi < 1.0f && semmi > 0.98f) {
        ULWarning << inPrefix << " - Using too small cone angle. Perhaps it is a mistake.";
    }

    if (semmi < 1.0f) {
        Point3 p = inVal.direction();
        if (p == 0.0) {
            result = false;
            ULError << inPrefix << " - Using as not Omni light but direction isn't specified.";
        }
    }

    const std::string & drf = inVal.dataRef();
    if (drf == "none" || drf.empty()) {
        ULInfo << inPrefix <<
                " - Hasn't got dataref value, consider to use param light instead spill custom if you don't need dataref.";
    }

    if (StringValidator::hasIllegalSymbols(drf)) {
        result = false;
        ULError << inPrefix << " - Dataref contains illegal symbols.";
    }

    if (inVal.size() < 0.0f) {
        result = false;
        ULError << inPrefix << " - The light size can't be negative.";
    }

    if (inVal.size() < 1.0f) {
        ULWarning << inPrefix << " - Using too small the light size. Perhaps it is a mistake.";
    }

    return result;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
