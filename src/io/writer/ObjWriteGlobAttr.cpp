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

#include "stdafx.h"

#include "ObjWriteGlobAttr.h"

#include "AbstractWriter.h"
#include "xpln/obj/ObjMain.h"
#include "io/StringValidator.h"
#include "common/AttributeNames.h"
#include "converters/ObjAttrString.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteGlobAttr::write(AbstractWriter * writer, const ObjMain * obj) {
    assert(obj);

    writeTexture(writer, ATTR_GLOBAL_TEXTURE, obj->pAttr.texture());
    writeTexture(writer, ATTR_GLOBAL_TEXTURE_LIT, obj->pAttr.textureLit());
    writeTexture(writer, ATTR_GLOBAL_TEXTURE_NORMAL, obj->pAttr.textureNormal());

    writeBool(writer, ATTR_GLOBAL_BLEND_GLASS, obj->pAttr.isBlendGlass());
    writeBool(writer, ATTR_GLOBAL_NORMAL_METALNESS, obj->pAttr.isNormalMetalness());
    writeBool(writer, ATTR_GLOBAL_TILTED, obj->pAttr.isTilted());
    writeBool(writer, ATTR_GLOBAL_NO_SHADOW, obj->pAttr.isNoShadow());
    writeBool(writer, ATTR_GLOBAL_COCKPIT_LIT, obj->pAttr.isCockpitLit());
    // Is printed in another place.
    //writeBool(inWriter, ATTR_GLOBAL_DEBUG, inObj->pAttr.isDebug());

    writeString(writer, toObjGlobString(obj->pAttr.wetDry()));
    writeString(writer, toObjGlobString(obj->pAttr.blend()));
    writeString(writer, toObjGlobString(obj->pAttr.layerGroup()));
    writeString(writer, toObjGlobString(obj->pAttr.layerGroupDraped()));
    writeString(writer, toObjGlobString(obj->pAttr.lodDrap()));
    writeString(writer, toObjGlobString(obj->pAttr.slungLoadWeight()));
    writeString(writer, toObjGlobString(obj->pAttr.specular()));
    writeString(writer, toObjGlobString(obj->pAttr.tint()));
    writeString(writer, toObjGlobString(obj->pAttr.slopeLimit()));
    writeString(writer, toObjGlobString(obj->pAttr.cockpitRegion(AttrCockpitRegion::r1)));
    writeString(writer, toObjGlobString(obj->pAttr.cockpitRegion(AttrCockpitRegion::r2)));
    writeString(writer, toObjGlobString(obj->pAttr.cockpitRegion(AttrCockpitRegion::r3)));
    writeString(writer, toObjGlobString(obj->pAttr.cockpitRegion(AttrCockpitRegion::r4)));
}

void ObjWriteGlobAttr::reset() {
    mCounter = 0;
}

size_t ObjWriteGlobAttr::count() const {
    return mCounter;
}

void ObjWriteGlobAttr::writeTexture(AbstractWriter * inWriter, const char * inAttr, const std::string & inString) {
    if (!inString.empty()) {
        if (!StringValidator::hasIllegalSymbols(inString, "\t\n\r")) {
            inWriter->printLine(std::string(inAttr).append(" ").append(inString));
            ++mCounter;
        }
    }
}

void ObjWriteGlobAttr::writeBool(AbstractWriter * inWriter, const char * inAttr, bool inState) {
    if (inState) {
        inWriter->printLine(inAttr);
        ++mCounter;
    }
}

void ObjWriteGlobAttr::writeString(AbstractWriter * inWriter, const std::string inStr) {
    if (!inStr.empty()) {
        inWriter->printLine(inStr);
        ++mCounter;
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
