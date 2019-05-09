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
    if (attr) {
        printObjGlobAttr(*attr, *writer);
    }
    return attr ? 1 : 0;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteGlobAttr::write(AbstractWriter * writer, const ObjMain * obj) {
    assert(obj);

    writeTexture(writer, ATTR_GLOBAL_TEXTURE, obj->pAttr.mTexture);
    writeTexture(writer, ATTR_GLOBAL_TEXTURE_LIT, obj->pAttr.mTextureLit);
    writeTexture(writer, ATTR_GLOBAL_TEXTURE_NORMAL, obj->pAttr.mTextureNormal);

    writeBool(writer, ATTR_GLOBAL_BLEND_GLASS, obj->pAttr.mBlendClass);
    writeBool(writer, ATTR_GLOBAL_NORMAL_METALNESS, obj->pAttr.mNormalMetalness);
    writeBool(writer, ATTR_GLOBAL_TILTED, obj->pAttr.mTilted);
    writeBool(writer, ATTR_GLOBAL_NO_SHADOW, obj->pAttr.mDropShadow);
    writeBool(writer, ATTR_GLOBAL_COCKPIT_LIT, obj->pAttr.mCockpitLit);
    // It is printed in another place.
    //writeBool(inWriter, ATTR_GLOBAL_DEBUG, inObj->pAttr.isDebug());

    mCounter += writeAttr(writer, obj->pAttr.mAttrWetDry);
    mCounter += writeAttr(writer, obj->pAttr.mBlend);
    mCounter += writeAttr(writer, obj->pAttr.mLayerGroup);
    mCounter += writeAttr(writer, obj->pAttr.mSlungLoadWeight);
    mCounter += writeAttr(writer, obj->pAttr.mSpecular);
    mCounter += writeAttr(writer, obj->pAttr.mTint);
    mCounter += writeAttr(writer, obj->pAttr.mAttrSlopeLimit);
    mCounter += writeAttr(writer, obj->pAttr.mAttrCockpitRegion1);
    mCounter += writeAttr(writer, obj->pAttr.mAttrCockpitRegion2);
    mCounter += writeAttr(writer, obj->pAttr.mAttrCockpitRegion3);
    mCounter += writeAttr(writer, obj->pAttr.mAttrCockpitRegion4);

    mCounter += writeAttr(writer, obj->pDraped.pAttr.mLayerGroup);
    mCounter += writeAttr(writer, obj->pDraped.pAttr.mLod);
}

void ObjWriteGlobAttr::writeTexture(AbstractWriter * inWriter, const char * inAttr, const std::optional<std::string> & string) {
    if (string && !string->empty()) {
        if (!StringValidator::hasIllegalSymbols(*string, "\t\n\r")) {
            inWriter->printLine(std::string(inAttr).append(" ").append(*string));
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
