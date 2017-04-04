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

#include "ObjWriteInstancing.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "ObjWriteAnim.h"
#include "io/ObjValidators.h"
#include "exceptions/defines.h"
#include <cassert>
#include "common/AttributeNames.h"

namespace xobj {

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool ObjWriteInstancing::check(ObjMain & inObjMain) {
		ULWarning << "The instance checking is in the test mode, so it may works incorrectly.";
		ULInfo << " To check whether your object is instanced, put the word DEBUG in the end of the OBJ file and run X-Plane."
			<< " The log file will contain a printout about your object."
			<< " If the word \"complex\" is not present and the word \"additive\" is (or your object does not contain multiple LODs) then your object can be instanced.";
		// TODO checking: LOD must be additive, not selective, or only one LOD 
		bool outResult = true;
		size_t lodCount = inObjMain.lodCount();
		for (size_t i = 0; i < lodCount; ++i) {
			ObjLodGroup & lod = inObjMain.lod(i);
			Transform & rootTransform = lod.transform();
			proccessTransform(rootTransform, outResult);
		}
		return outResult;
	}

	void ObjWriteInstancing::printBreakInstancing(const char * objName, const char * reason) {
		assert(objName);
		assert(reason);
		ULError << "Instancing is broken on \"" << objName << "\". The reason: " << reason;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjWriteInstancing::proccessTransform(Transform & transform, bool & outResult) {
		if (transform.hasAnim()) {
			printBreakInstancing(transform.name().c_str(),
								"node has animation. Animation is not allowed for instancing.");
			outResult = false;
		}

		proccessObjects(transform, outResult);

		//-------------------------------------------------------------------------
		// children

		Transform::TransformIndex chCount = transform.childrenCount();
		for (Transform::TransformIndex i = 0; i < chCount; ++i) {
			proccessTransform(*static_cast<Transform*>(transform.childAt(i)), outResult);
		}
		//-------------------------------------------------------------------------
	}

	void ObjWriteInstancing::proccessObjects(Transform & transform, bool & outResult) {
		for (auto & curr : transform.objList()) {
			if (curr->objType() == OBJ_LINE) {
				printBreakInstancing(curr->objectName().c_str(),
									"the object is the line object. Lines are not allowed for instancing.");
				outResult = false;
			}
			if (curr->objType() == OBJ_SMOKE) {
				printBreakInstancing(curr->objectName().c_str(),
									"the object is the smoke object. Smokes are not allowed for instancing.");
				outResult = false;
			}
			if (curr->objType() == OBJ_MESH) {
				ObjMesh * mesh = reinterpret_cast<ObjMesh*>(curr);
				proccessAttributes(*mesh, outResult);
			}
			// TODO What about the lights?
		}
	}

	void ObjWriteInstancing::proccessAttributes(ObjMesh & mesh, bool & outResult) {
		if (mesh.pAttr.manipulator()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has the manipulator attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
		if (mesh.pAttr.polyOffset()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has the \"").append(ATTR_POLY_OS)
																	.append("\" attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
		if (mesh.pAttr.blend()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has on of the \"").append(ATTR_BLEND).append("/")
																		.append(ATTR_NO_BLEND).append("/").append(ATTR_SHADOW_BLEND)
																		.append("\" attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
		if (mesh.pAttr.shiny()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has the \"").append(ATTR_SHINY_RAT)
																	.append("\" attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
		if (mesh.pAttr.cockpit()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has on of the \"").append(ATTR_COCKPIT).append("/")
																		.append(ATTR_COCKPIT_REGION)
																		.append("\" attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
		//-------------------------------------------------------------------------
		if (!mesh.pAttr.isDraw()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has the \"").append(ATTR_DRAW_DISABLE)
																	.append("\" attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
		if (!mesh.pAttr.isCastShadow()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has the \"").append(ATTR_NO_SHADOW)
																	.append("\" attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
		if (mesh.pAttr.isSolidForCamera()) {
			printBreakInstancing(mesh.objectName().c_str(),
								std::string("the object has the \"").append(ATTR_SOLID_CAMERA)
																	.append("\" attribute which is not allowed for instansing").c_str());
			outResult = false;
		}
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
