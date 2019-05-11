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

#include <algorithm>
#include "converters/StringStream.h"
#include "ObjAttrString.h"
#include "common/AttributeNames.h"
#include "xpln/obj/attributes/AttrWetDry.h"
#include "xpln/obj/attributes/AttrTint.h"
#include "xpln/obj/attributes/AttrSpecular.h"
#include "xpln/obj/attributes/AttrSlungLoadWeight.h"
#include "xpln/obj/attributes/AttrShiny.h"
#include "xpln/obj/attributes/AttrPolyOffset.h"
#include "xpln/obj/attributes/AttrDrapedLod.h"
#include "xpln/obj/attributes/AttrLightLevel.h"
#include "xpln/obj/attributes/AttrDrapedLayerGroup.h"
#include "xpln/obj/attributes/AttrLayerGroup.h"
#include "xpln/obj/attributes/AttrHard.h"
#include "xpln/obj/attributes/AttrBlend.h"
#include "xpln/obj/attributes/AttrSlopeLimit.h"
#include "xpln/obj/attributes/AttrCockpitRegion.h"
#include "xpln/obj/attributes/AttrCockpit.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void printObjGlobAttr(const AttrBlend & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    if (globAttr.mType == AttrBlend::no_blend) {
        outStr << ATTR_GLOBAL_NO_BLEND;
    }
    else if (globAttr.mType == AttrBlend::shadow_blend) {
        outStr << ATTR_GLOBAL_SHADOW_BLEND;
    }
    outStr << " " << std::clamp(globAttr.mRatio, 0.0f, 1.0f);
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrLayerGroup & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_LAYER_GROUP;
    outStr << " " << globAttr.layer().toString();
    outStr << " " << globAttr.offset();
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrDrapedLayerGroup & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_LAYER_GROUP_DRAPED;
    outStr << " " << globAttr.layer().toString();
    outStr << " " << globAttr.offset();
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrDrapedLod & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_LOD_DRAPED << " " << globAttr.distance();
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrSlungLoadWeight & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_SLUNG_LOAD_WEIGHT << " " << globAttr.weight();
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrSpecular & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_SPECULAR << " " << globAttr.ratio();
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrTint & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_TINT;
    outStr << " " << globAttr.albedo();
    outStr << " " << globAttr.emissive();
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrWetDry & globAttr, AbstractWriter & writer) {
    writer.writeLine(globAttr.state() == AttrWetDry::eState::wet ? ATTR_GLOBAL_WET : ATTR_GLOBAL_DRY);
}

void printObjGlobAttr(const AttrSlopeLimit & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_SLOPE_LIMIT;
    outStr << " " << globAttr.minPitch();
    outStr << " " << globAttr.maxPitch();
    outStr << " " << globAttr.minRoll();
    outStr << " " << globAttr.maxRoll();
    writer.writeLine(outStr.str());
}

void printObjGlobAttr(const AttrCockpitRegion & globAttr, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_GLOBAL_COCKPIT_REGION;
    outStr << " " << globAttr.left();
    outStr << " " << globAttr.bottom();
    outStr << " " << globAttr.right();
    outStr << " " << globAttr.top();
    writer.writeLine(outStr.str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
