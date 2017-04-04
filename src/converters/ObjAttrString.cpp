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
#include "StringStream.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjGlobString(const AttrBlend & inVal) {
		if (!inVal)
			return "";

		StringStream outStr;
		if (inVal.type() == AttrBlend::no_blend) {
			outStr << ATTR_GLOBAL_NO_BLEND;
		}
		else if (inVal.type() == AttrBlend::shadow_blend) {
			outStr << ATTR_GLOBAL_SHADOW_BLEND;
		}
		outStr << " " << inVal.ratio() << std::flush;
		return outStr.str();
	}

	std::string toObjGlobString(const AttrLayerGroup & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_LAYER_GROUP;
		outStr << " " << inVal.layer().toString();
		outStr << " " << inVal.offset();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjGlobString(const AttrDrapedLayerGroup & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_LAYER_GROUP_DRAPED;
		outStr << " " << inVal.layer().toString();
		outStr << " " << inVal.offset();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjGlobString(const AttrLodDrap & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_LOD_DRAPED << " " << inVal.distance() << std::flush;
		return outStr.str();
	}

	std::string toObjGlobString(const AttrSlungLoadWeight & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_SLUNG_LOAD_WEIGHT << " " << inVal.weight() << std::flush;
		return outStr.str();
	}

	std::string toObjGlobString(const AttrSpecular & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_SPECULAR << " " << inVal.ratio() << std::flush;
		return outStr.str();
	}

	std::string toObjGlobString(const AttrTint & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_TINT;
		outStr << " " << inVal.albedo();
		outStr << " " << inVal.emissive();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjGlobString(const AttrWetDry & inVal) {
		if (!inVal)
			return "";
		return inVal.state() == AttrWetDry::eState::wet ? ATTR_GLOBAL_WET : ATTR_GLOBAL_DRY;
	}

	std::string toObjGlobString(const AttrSlopeLimit & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_SLOPE_LIMIT;
		outStr << " " << inVal.minPitch();
		outStr << " " << inVal.maxPitch();
		outStr << " " << inVal.minRoll();
		outStr << " " << inVal.maxRoll();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjGlobString(const AttrCockpitRegion & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_GLOBAL_COCKPIT_REGION;
		outStr << " " << inVal.left();
		outStr << " " << inVal.bottom();
		outStr << " " << inVal.right();
		outStr << " " << inVal.top();
		outStr.flush();
		return outStr.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const AttrBlend & inVal) {
		if (!inVal)
			return "";

		StringStream outStr;
		if (inVal.type() == AttrBlend::no_blend) {
			outStr << ATTR_NO_BLEND;
		}
		else if (inVal.type() == AttrBlend::shadow_blend) {
			outStr << ATTR_SHADOW_BLEND;
		}
		else {
			outStr << ATTR_BLEND;
		}
		outStr << " " << inVal.ratio() << std::flush;
		return outStr.str();
	}

	std::string toObjString(const AttrHard & inVal) {
		if (!inVal)
			return "";
		if (!inVal.isDeck()) {
			StringStream outStr;
			outStr << ATTR_HARD;
			outStr << " " << inVal.surface().toString() << std::flush;
			return outStr.str();
		}
		StringStream outStr;
		outStr << ATTR_HARD_DECK;
		outStr << " " << inVal.surface().toString() << std::flush;
		return outStr.str();
	}

	std::string toObjString(const AttrLightLevel & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_LIGHT_LEVEL;
		outStr << " " << inVal.val1();
		outStr << " " << inVal.val2();
		outStr << " " << inVal.dataref();
		outStr.flush();
		return outStr.str();
	}

	std::string toObjString(const AttrPolyOffset & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_POLY_OS << " " << inVal.offset() << std::flush;
		return outStr.str();
	}

	std::string toObjString(const AttrShiny & inVal) {
		if (!inVal)
			return "";
		StringStream outStr;
		outStr << ATTR_SHINY_RAT << " " << inVal.ratio() << std::flush;
		return outStr.str();
	}

	std::string toObjString(const AttrCockpit & inVal) {
		if (!inVal)
			return "";
		if (inVal.type() == AttrCockpit::eType::cockpit) {
			return ATTR_COCKPIT;
		}
		StringStream outStr;
		outStr << ATTR_COCKPIT_REGION << " ";
		if (inVal.type() == AttrCockpit::eType::region_1) {
			outStr << "0";
		}
		if (inVal.type() == AttrCockpit::eType::region_2) {
			outStr << "1";
		}
		if (inVal.type() == AttrCockpit::eType::region_3) {
			outStr << "2";
		}
		if (inVal.type() == AttrCockpit::eType::region_4) {
			outStr << "3";
		}
		outStr.flush();
		return outStr.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
