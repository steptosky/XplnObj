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
#include "xpln/common/Logger.h"
#include "sts/utilities/Compare.h"

#include "xpln/obj/attributes/AttrGlobSet.h"

#include "xpln/obj/ObjDummy.h"
#include "xpln/obj/ObjLine.h"
#include "xpln/obj/ObjMain.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/ObjSmoke.h"

#include "xpln/obj/ObjLightCustom.h"
#include "xpln/obj/ObjLightNamed.h"
#include "xpln/obj/ObjLightParam.h"
#include "xpln/obj/ObjLightPoint.h"
#include "xpln/obj/ObjLightSpillCust.h"
#include "xpln/common/String.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

bool checkParameters(const AttrGlobSet & attrSet, const std::string & prefix) {
    if (!attrSet.mTexture || attrSet.mTexture->empty() || *attrSet.mTexture == "none") {
        XULWarning << prefix << " - Texture is not specified";
    }
    bool result = true;
    if (!String::isValidForTexture(attrSet.mTexture.value_or(std::string()))) {
        result = false;
        XULError << prefix << " contains illegal symbols in the texture name <" << *attrSet.mTexture << ">";
    }
    if (!String::isValidForTexture(attrSet.mTextureLit.value_or(std::string()))) {
        result = false;
        XULError << prefix << " contains illegal symbols in the lit texture name <" << *attrSet.mTextureLit << ">";
    }
    if (!String::isValidForTexture(attrSet.mTextureNormal.value_or(std::string()))) {
        result = false;
        XULError << prefix << " contains illegal symbols in the normal texture name <" << *attrSet.mTextureNormal << ">";
    }
    return result;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

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
    if (mainObj.mAttr.mDebug) {
        XULWarning << prefix
                << " - \"DEBUG\" option is enabled. Turn it off if you don't know what it is or if you don't need it.";
    }
    if (result) {
        result = checkParameters(mainObj.mAttr, prefix);
    }
    return result;
}

bool checkParameters(const ObjMesh & obj, const std::string & prefix) {
    bool result = true;
    if (obj.mVertices.empty()) {
        result = false;
        XLError << prefix << " - Doesn't have any vertices.";
    }

    if (obj.mFaces.empty()) {
        result = false;
        XLError << prefix << " - Doesn't have any faces.";
    }
    {
        std::vector<bool> vertUsed(obj.mVertices.size(), false);
        const size_t vertSize = vertUsed.size();
        for (size_t i = 0; i < obj.mFaces.size(); ++i) {
            const MeshFace & currFace = obj.mFaces[i];
            if (currFace.mV0 >= vertSize || currFace.mV1 >= vertSize || currFace.mV2 >= vertSize) {
                result = false;
                XLError << prefix << " - The face [" << i << "] is out of the vertices range.";
                return result;
            }
            vertUsed[currFace.mV0] = true;
            vertUsed[currFace.mV1] = true;
            vertUsed[currFace.mV2] = true;
        }
        for (size_t i = 0; i < vertUsed.size(); ++i) {
            if (!vertUsed[i]) {
                result = false;
                XLError << prefix << " - The vertex [" << i << "] is isolated.";
            }
        }
    }
    return result;
}

bool checkParameters(const ObjSmoke & obj, const std::string & prefix) {
    bool result = true;
    if (obj.size() < 0.1f) {
        result = false;
        XULError << prefix << " - Smoke size is too small.";
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
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool checkParameters(const ObjLightCustom & inVal, const std::string & inPrefix) {
    bool result = true;
    if (inVal.size() < 1.0f) {
        XULWarning << inPrefix << " - Using too small the light size. Perhaps it is a mistake.";
    }

    const RectangleI & rect = inVal.textureRect();
    if (sts::isEqual(rect.point1().x, rect.point2().x)) {
        result = false;
        XULWarning << inPrefix << " - S1 and S2 should not be equaled.";
    }
    if (sts::isEqual(rect.point1().y, rect.point2().y)) {
        result = false;
        XULWarning << inPrefix << " - T1 and T2 can't be equaled.";
    }

    if (!String::isValidForDataRef(inVal.dataRef())) {
        result = false;
        XULError << inPrefix << " - Dataref contains illegal symbols.";
    }

    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const ObjLightNamed & inVal, const std::string & inPrefix) {
    bool result = true;
    if (inVal.name().empty()) {
        result = false;
        XULError << inPrefix << " - Light name isn't specified.";
    }
    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const ObjLightParam & inVal, const std::string & inPrefix) {
    bool result = true;
    if (inVal.name().empty()) {
        result = false;
        XULError << inPrefix << " - Light name isn't specified.";
    }
    if (inVal.params().empty()) {
        result = false;
        XULError << inPrefix << " - Parameters aren't specified.";
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
        XULError << inPrefix << " - Color isn't specified.";
    }
    return result;
}

//-------------------------------------------------------------------------

bool checkParameters(const ObjLightSpillCust & inVal, const std::string & inPrefix) {
    bool result = true;
    const float semmi = inVal.semiRaw();
    if (semmi > 1.0f || semmi < 0.0f) {
        result = false;
        XULError << inPrefix << " - The semi value must be between 0.0 - 1.0";
    }

    if (semmi < 1.0f && semmi > 0.98f) {
        XULWarning << inPrefix << " - Using too small cone angle. Perhaps it is a mistake.";
    }

    if (semmi < 1.0f) {
        Point3 p = inVal.direction();
        if (p == 0.0) {
            result = false;
            XULError << inPrefix << " - Using as not Omni light but direction isn't specified.";
        }
    }

    const std::string & drf = inVal.dataRef();
    if (drf == "none" || drf.empty()) {
        XULInfo << inPrefix << " - doesn't have dataref, consider to use param light instead of spill custom.";
    }

    if (!String::isValidForDataRef(drf)) {
        result = false;
        XULError << inPrefix << " - Dataref contains illegal symbols.";
    }

    if (inVal.size() < 0.0f) {
        result = false;
        XULError << inPrefix << " - The light size can't be negative.";
    }

    if (inVal.size() < 1.0f) {
        XULWarning << inPrefix << " - Using too small the light size. Perhaps it is a mistake.";
    }

    return result;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
