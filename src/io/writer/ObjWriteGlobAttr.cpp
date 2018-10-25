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
#include <cstdint>

#include "ObjWriteGlobAttr.h"

#include "AbstractWriter.h"
#include "xpln/obj/ObjMain.h"
#include "io/StringValidator.h"
#include "common/AttributeNames.h"
#include "converters/ObjAttrString.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<typename T>
std::size_t writeAttr(AbstractWriter * writer, const T & attr) {
    printObjGlobAttr(attr, *writer);
    return attr ? 1 : 0;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
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
    // It is printed in another place.
    //writeBool(inWriter, ATTR_GLOBAL_DEBUG, inObj->pAttr.isDebug());

    mCounter += writeAttr(writer, obj->pAttr.wetDry());
    mCounter += writeAttr(writer, obj->pAttr.blend());
    mCounter += writeAttr(writer, obj->pAttr.layerGroup());
    mCounter += writeAttr(writer, obj->pAttr.slungLoadWeight());
    mCounter += writeAttr(writer, obj->pAttr.specular());
    mCounter += writeAttr(writer, obj->pAttr.tint());
    mCounter += writeAttr(writer, obj->pAttr.slopeLimit());
    mCounter += writeAttr(writer, obj->pAttr.cockpitRegion(AttrCockpitRegion::r1));
    mCounter += writeAttr(writer, obj->pAttr.cockpitRegion(AttrCockpitRegion::r2));
    mCounter += writeAttr(writer, obj->pAttr.cockpitRegion(AttrCockpitRegion::r3));
    mCounter += writeAttr(writer, obj->pAttr.cockpitRegion(AttrCockpitRegion::r4));

    mCounter += writeAttr(writer, obj->pDraped.pAttr.layerGroup());
    mCounter += writeAttr(writer, obj->pDraped.pAttr.lod());
}

void ObjWriteGlobAttr::writeTexture(AbstractWriter * inWriter, const char * inAttr, const std::string & inString) {
    if (!inString.empty()) {
        if (!StringValidator::hasIllegalSymbols(inString, "\t\n\r")) {
            inWriter->printLine(std::string(inAttr).append(" ").append(inString));
            ++mCounter;
        }
    }
}

void ObjWriteGlobAttr::writeBool(AbstractWriter * inWriter, const char * inAttr, const bool inState) {
    if (inState) {
        inWriter->printLine(inAttr);
        ++mCounter;
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
