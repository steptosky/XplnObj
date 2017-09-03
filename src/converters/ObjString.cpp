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
#include "xpln/obj/ObjDummy.h"

#include "Defines.h"
#include "StringStream.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const MeshVertex & inVert, bool inIsTree) {
		StringStream out;
		out << MESH_VT << " " << inVert.pPosition.toString(PRECISION) << "  ";

		if (inIsTree)
			out << 0.0f << " " << 1.0f << " " << 0.0f;
		else
			out << inVert.pNormal.normalized().toString(PRECISION);

		out << "  " << inVert.pTexture.toString(PRECISION);
		return out.str();
	}

	std::string toObjString(const LineVertex & inVert) {
		StringStream out;
		out << VLINE
				<< " " << inVert.pPosition.toString(PRECISION)
				<< " " << inVert.pColor.red()
				<< " " << inVert.pColor.green()
				<< " " << inVert.pColor.blue();
		return out.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const ObjLodGroup & obj, bool printName) {
		StringStream out;
		out << ATTR_LOD << " " << obj.nearVal() << " " << obj.farVal();
		if (printName) {
			out << " ## " << obj.objectName();
		}
		return out.str();
	}

	std::string toObjString(const ObjSmoke & obj, bool printName) {
		if (obj.smokeType() == ObjSmoke::none) {
			// todo maybe warning about none?
			return "";
		}
		StringStream out;
		out << (obj.smokeType() == ObjSmoke::white ? SMOKE_WHITE : SMOKE_BLACK)
				<< " " << obj.position().toString(PRECISION)
				<< " " << obj.size();
		if (printName) {
			out << " ## " << obj.objectName();
		}
		return out.str();
	}

	std::string toObjString(const ObjDummy & obj, bool printName) {
		StringStream out;
		if (printName) {
			out << "## Dummy: " << obj.objectName();
		}
		return out.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	std::string toObjString(const ObjLightCustom & obj, bool printName) {
		StringStream out;
		if (printName) {
			out << "## " << obj.objectName() << std::endl;
		}
		out << LIGHT_CUSTOM
				<< " " << obj.position().toString(PRECISION)
				<< " " << obj.color().toString(PRECISION)
				<< " " << obj.size()
				<< " " << obj.textureRect().point1().toString(PRECISION)
				<< " " << obj.textureRect().point2().toString(PRECISION)
				<< " " << (obj.dataRef().empty() ? "none" : obj.dataRef().c_str());
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightNamed & obj, bool printName) {
		StringStream out;
		if (printName) {
			out << "## " << obj.objectName() << std::endl;
		}
		out << LIGHT_NAMED
				<< " " << obj.lightId().toString()
				<< " " << obj.position().toString(PRECISION);
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightParam & obj, bool printName) {
		StringStream out;
		if (printName) {
			out << "## " << obj.objectName() << std::endl;
		}
		if (obj.lightId() == ELightParams(ELightParams::light_params_custom)) {
			out << LIGHT_PARAM << " " << obj.lightName();
		}
		else {
			out << LIGHT_PARAM << " " << obj.lightId().toString();
		}
		out << " " << obj.position().toString(PRECISION) << " " << obj.additionalParams();
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightPoint & obj, bool printName) {
		StringStream out;
		if (printName) {
			out << "## " << obj.objectName() << std::endl;
		}
		const Color & c = obj.color();
		out << VLIGHT << " " << obj.position().toString(PRECISION) << " "
				<< c.red() << " " << c.green() << " " << c.blue();
		return out.str();
	}

	//-------------------------------------------------------------------------

	std::string toObjString(const ObjLightSpillCust & obj, bool printName) {
		StringStream out;
		if (printName) {
			out << "## " << obj.objectName() << std::endl;
		}
		out << LIGHT_SPILL_CUSTOM
				<< " " << obj.position().toString(PRECISION)
				<< " " << obj.color().toString(PRECISION)
				<< " " << obj.size()
				<< " " << obj.direction().toString(PRECISION)
				<< " " << obj.semiRaw()
				<< " " << (obj.dataRef().empty() ? "none" : obj.dataRef().c_str());
		return out.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
