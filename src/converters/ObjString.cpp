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

#include "ObjString.h"

#include "sts/string/StringConverters.h"
#include "../common/Logger.h"
#include "common/AttributeNames.h"

#include "xpln/obj/MeshVertex.h"
#include "xpln/obj/LineVertex.h"

#include "xpln/obj/ObjLightCustom.h"
#include "xpln/obj/ObjLightNamed.h"
#include "xpln/obj/ObjLightParam.h"
#include "xpln/obj/ObjLightPoint.h"
#include "xpln/obj/ObjLightSpillCust.h"

#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjSmoke.h"

#include "Defines.h"
#include "StringStream.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const MeshVertex & inVert, bool inIsSunLight) {
		StringStream out;
		out << MESH_VT << " " << inVert.pPosition.toString(PRECISION) << "  ";
		if (inIsSunLight)
			out << inVert.pNormal.normalized().toString(PRECISION);
		else
			out << 0.0f << " " << 1.0f << " " << 0.0f;
		out << "  " << inVert.pTexture.toString(PRECISION);
		return out.str();
	}

	std::string toObjString(const LineVertex & inVert) {
		StringStream out;
		out << VLINE << " " << inVert.pPosition.toString(PRECISION) << " "
				<< inVert.pColor.red() << " " << inVert.pColor.green() << " " << inVert.pColor.blue();
		return out.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const ObjLodGroup & inVal) {
		StringStream out;
		out << ATTR_LOD << " " << inVal.nearVal() << " " << inVal.farVal();
		if (!inVal.objectName().empty()) {
			out << " ## " << inVal.objectName();
		}
		return out.str();
	}

	std::string toObjString(const ObjSmoke & inVal) {
		StringStream out;
		out << (inVal.smokeType() == ObjSmoke::white ? SMOKE_WHITE : SMOKE_BLACK)
				<< " " << inVal.position().toString(PRECISION)
				<< " " << inVal.size();
		return out.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const ObjLightCustom & inVal) {
		StringStream out;
		out << LIGHT_CUSTOM
				<< " " << inVal.position().toString(PRECISION)
				<< " " << inVal.color().toString(PRECISION)
				<< " " << inVal.size()
				<< " " << inVal.textureRect().point1().toString(PRECISION)
				<< " " << inVal.textureRect().point2().toString(PRECISION)
				<< " " << (inVal.dataRef().empty() ? "none" : inVal.dataRef().c_str());
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightNamed & inVal) {
		StringStream out;
		out << LIGHT_NAMED
				<< " " << inVal.lightId().toString()
				<< " " << inVal.position().toString(PRECISION);
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightParam & inVal) {
		StringStream out;
		out << LIGHT_PARAM
				<< " " << inVal.lightId().toString()
				<< " " << inVal.position().toString(PRECISION)
				<< " " << inVal.additionalParams();
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightPoint & inVal) {
		StringStream out;
		out << VLIGHT << " " << inVal.position().toString(PRECISION) << " "
				<< inVal.color().red() << " " << inVal.color().green() << " " << inVal.color().blue();
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightSpillCust & inVal) {
		StringStream out;
		out << LIGHT_SPILL_CUSTOM
				<< " " << inVal.position().toString(PRECISION)
				<< " " << inVal.color().toString(PRECISION)
				<< " " << inVal.size()
				<< " " << inVal.direction().toString(PRECISION)
				<< " " << inVal.semiRaw()
				<< " " << (inVal.dataRef().empty() ? "none" : inVal.dataRef().c_str());
		return out.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
