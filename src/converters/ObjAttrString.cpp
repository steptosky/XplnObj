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

#include "ObjAttrString.h"
#include "common/AttributeNames.h"
#include "xpln/obj/attributes/AttrWetDry.h"
#include "xpln/obj/attributes/AttrTint.h"
#include "xpln/obj/attributes/AttrSpecular.h"
#include "xpln/obj/attributes/AttrSlungLoadWeight.h"
#include "xpln/obj/attributes/AttrShiny.h"
#include "xpln/obj/attributes/AttrPolyOffset.h"
#include "xpln/obj/attributes/AttrLodDrap.h"
#include "xpln/obj/attributes/AttrLightLevel.h"
#include "xpln/obj/attributes/AttrDrapedLayerGroup.h"
#include "xpln/obj/attributes/AttrLayerGroup.h"
#include "xpln/obj/attributes/AttrHard.h"
#include "xpln/obj/attributes/AttrBlend.h"
#include "xpln/obj/attributes/AttrSlopeLimit.h"
#include "xpln/obj/attributes/AttrCockpitRegion.h"
#include "xpln/obj/attributes/AttrCockpit.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

std::string toObjGlobString(const AttrBlend & globAttr) {
    if (!globAttr)
        return "";

    StringStream outStr;
    if (globAttr.type() == AttrBlend::no_blend) {
        outStr << ATTR_GLOBAL_NO_BLEND;
    }
    else if (globAttr.type() == AttrBlend::shadow_blend) {
        outStr << ATTR_GLOBAL_SHADOW_BLEND;
    }
    outStr << " " << globAttr.ratio() << std::flush;
    return outStr.str();
}

std::string toObjGlobString(const AttrLayerGroup & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_LAYER_GROUP;
    outStr << " " << globAttr.layer().toString();
    outStr << " " << globAttr.offset();
    outStr.flush();
    return outStr.str();
}

std::string toObjGlobString(const AttrDrapedLayerGroup & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_LAYER_GROUP_DRAPED;
    outStr << " " << globAttr.layer().toString();
    outStr << " " << globAttr.offset();
    outStr.flush();
    return outStr.str();
}

std::string toObjGlobString(const AttrLodDrap & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_LOD_DRAPED << " " << globAttr.distance() << std::flush;
    return outStr.str();
}

std::string toObjGlobString(const AttrSlungLoadWeight & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_SLUNG_LOAD_WEIGHT << " " << globAttr.weight() << std::flush;
    return outStr.str();
}

std::string toObjGlobString(const AttrSpecular & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_SPECULAR << " " << globAttr.ratio() << std::flush;
    return outStr.str();
}

std::string toObjGlobString(const AttrTint & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_TINT;
    outStr << " " << globAttr.albedo();
    outStr << " " << globAttr.emissive();
    outStr.flush();
    return outStr.str();
}

std::string toObjGlobString(const AttrWetDry & globAttr) {
    if (!globAttr)
        return "";
    return globAttr.state() == AttrWetDry::eState::wet ? ATTR_GLOBAL_WET : ATTR_GLOBAL_DRY;
}

std::string toObjGlobString(const AttrSlopeLimit & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_SLOPE_LIMIT;
    outStr << " " << globAttr.minPitch();
    outStr << " " << globAttr.maxPitch();
    outStr << " " << globAttr.minRoll();
    outStr << " " << globAttr.maxRoll();
    outStr.flush();
    return outStr.str();
}

std::string toObjGlobString(const AttrCockpitRegion & globAttr) {
    if (!globAttr)
        return "";
    StringStream outStr;
    outStr << ATTR_GLOBAL_COCKPIT_REGION;
    outStr << " " << globAttr.left();
    outStr << " " << globAttr.bottom();
    outStr << " " << globAttr.right();
    outStr << " " << globAttr.top();
    outStr.flush();
    return outStr.str();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

std::string toObjString(const AttrBlend & attr) {
    if (!attr)
        return "";

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
    outStr << " " << attr.ratio() << std::flush;
    return outStr.str();
}

std::string toObjString(const AttrHard & attr) {
    if (!attr)
        return "";
    if (!attr.isDeck()) {
        StringStream outStr;
        outStr << ATTR_HARD;
        outStr << " " << attr.surface().toString() << std::flush;
        return outStr.str();
    }
    StringStream outStr;
    outStr << ATTR_HARD_DECK;
    outStr << " " << attr.surface().toString() << std::flush;
    return outStr.str();
}

std::string toObjString(const AttrLightLevel & attr) {
    if (!attr)
        return "";
    StringStream outStr;
    outStr << ATTR_LIGHT_LEVEL;
    outStr << " " << attr.val1();
    outStr << " " << attr.val2();
    outStr << " " << attr.dataref();
    outStr.flush();
    return outStr.str();
}

std::string toObjString(const AttrPolyOffset & attr) {
    if (!attr)
        return "";
    StringStream outStr;
    outStr << ATTR_POLY_OS << " " << attr.offset() << std::flush;
    return outStr.str();
}

std::string toObjString(const AttrShiny & attr) {
    if (!attr)
        return "";
    StringStream outStr;
    outStr << ATTR_SHINY_RAT << " " << attr.ratio() << std::flush;
    return outStr.str();
}

std::string toObjString(const AttrCockpit & attr) {
    if (!attr)
        return "";
    if (attr.type() == AttrCockpit::eType::cockpit) {
        return ATTR_COCKPIT;
    }
    StringStream outStr;
    outStr << ATTR_COCKPIT_REGION << " ";
    if (attr.type() == AttrCockpit::eType::region_1) {
        outStr << "0";
    }
    if (attr.type() == AttrCockpit::eType::region_2) {
        outStr << "1";
    }
    if (attr.type() == AttrCockpit::eType::region_3) {
        outStr << "2";
    }
    if (attr.type() == AttrCockpit::eType::region_4) {
        outStr << "3";
    }
    outStr.flush();
    return outStr.str();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
