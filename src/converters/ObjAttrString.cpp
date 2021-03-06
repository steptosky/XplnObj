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
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    if (globAttr.type() == AttrBlend::no_blend) {
        outStr << ATTR_GLOBAL_NO_BLEND;
    }
    else if (globAttr.type() == AttrBlend::shadow_blend) {
        outStr << ATTR_GLOBAL_SHADOW_BLEND;
    }
    outStr << " " << globAttr.ratio();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrLayerGroup & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_LAYER_GROUP;
    outStr << " " << globAttr.layer().toString();
    outStr << " " << globAttr.offset();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrDrapedLayerGroup & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_LAYER_GROUP_DRAPED;
    outStr << " " << globAttr.layer().toString();
    outStr << " " << globAttr.offset();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrDrapedLod & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_LOD_DRAPED << " " << globAttr.distance();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrSlungLoadWeight & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_SLUNG_LOAD_WEIGHT << " " << globAttr.weight();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrSpecular & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_SPECULAR << " " << globAttr.ratio();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrTint & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_TINT;
    outStr << " " << globAttr.albedo();
    outStr << " " << globAttr.emissive();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrWetDry & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    writer.printLine(globAttr.state() == AttrWetDry::eState::wet ? ATTR_GLOBAL_WET : ATTR_GLOBAL_DRY);
}

void printObjGlobAttr(const AttrSlopeLimit & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_SLOPE_LIMIT;
    outStr << " " << globAttr.minPitch();
    outStr << " " << globAttr.maxPitch();
    outStr << " " << globAttr.minRoll();
    outStr << " " << globAttr.maxRoll();
    writer.printLine(outStr.str());
}

void printObjGlobAttr(const AttrCockpitRegion & globAttr, AbstractWriter & writer) {
    if (!globAttr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_GLOBAL_COCKPIT_REGION;
    outStr << " " << globAttr.left();
    outStr << " " << globAttr.bottom();
    outStr << " " << globAttr.right();
    outStr << " " << globAttr.top();
    writer.printLine(outStr.str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void printObjAttr(const AttrBlend & attr, AbstractWriter & writer) {
    if (!attr) {
        return;
    }
    StringStream outStr;
    if (attr.type() == AttrBlend::no_blend) {
        outStr << ATTR_NO_BLEND;
    }
    else if (attr.type() == AttrBlend::shadow_blend) {
        outStr << ATTR_SHADOW_BLEND;
    }
    else {
        outStr << ATTR_BLEND;
    }
    outStr << " " << attr.ratio();
    writer.printLine(outStr.str());
}

void printObjAttr(const AttrHard & attr, AbstractWriter & writer) {
    if (!attr) {
        return;
    }
    StringStream outStr;
    outStr << (attr.isDeck() ? ATTR_HARD_DECK : ATTR_HARD)
            << " " << attr.surface().toString();
    writer.printLine(outStr.str());
}

void printObjAttr(const AttrLightLevel & attr, AbstractWriter & writer) {
    if (!attr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_LIGHT_LEVEL;
    outStr << " " << attr.val1();
    outStr << " " << attr.val2();
    outStr << " " << writer.actualDataref(attr.dataref());
    writer.printLine(outStr.str());
}

void printObjAttr(const AttrPolyOffset & attr, AbstractWriter & writer) {
    if (!attr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_POLY_OS << " " << attr.offset();
    writer.printLine(outStr.str());
}

void printObjAttr(const AttrShiny & attr, AbstractWriter & writer) {
    if (!attr) {
        return;
    }
    StringStream outStr;
    outStr << ATTR_SHINY_RAT << " " << attr.ratio();
    writer.printLine(outStr.str());
}

void printObjAttr(const AttrCockpit & attr, AbstractWriter & writer) {
    if (!attr) {
        return;
    }
    if (attr.type() == AttrCockpit::eType::cockpit) {
        writer.printLine(ATTR_COCKPIT);
        return;
    }
    StringStream outStr;
    if (attr.type() == AttrCockpit::eType::region_1) {
        outStr << ATTR_COCKPIT_REGION << " " << "0";
    }
    else if (attr.type() == AttrCockpit::eType::region_2) {
        outStr << ATTR_COCKPIT_REGION << " " << "1";
    }
    else if (attr.type() == AttrCockpit::eType::region_3) {
        outStr << ATTR_COCKPIT_REGION << " " << "2";
    }
    else if (attr.type() == AttrCockpit::eType::region_4) {
        outStr << ATTR_COCKPIT_REGION << " " << "3";
    }
    else if (attr.type() == AttrCockpit::eType::cockpit_device) {
        outStr << ATTR_COCKPIT_DEVICE
                << " " << attr.name()
                << " " << attr.bus()
                << " " << attr.lightingChannel()
                << " " << attr.autoAdjust();
    }
    writer.printLine(outStr.str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
