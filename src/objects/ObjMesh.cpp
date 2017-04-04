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

#include "xpln/obj/ObjMesh.h"
#include "sts/geometry/TMatrix3.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	ObjMesh::ObjMesh(const ObjMesh & inCopy)
		: ObjAbstract(inCopy),
		pVertices(inCopy.pVertices),
		pFaces(inCopy.pFaces) {}

	ObjMesh::ObjMesh() {
		setObjectName("Obj Mesh");
	}

	ObjMesh::~ObjMesh() { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjMesh::attach(const ObjMesh & inOtherMesh) {
		size_t currThisVertCount = pVertices.size();
		for (auto & currVert : inOtherMesh.pVertices)
			pVertices.emplace_back(currVert);

		for (auto & currFace : inOtherMesh.pFaces)
			pFaces.emplace_back(MeshFace(currFace.pV0 + currThisVertCount,
										currFace.pV1 + currThisVertCount,
										currFace.pV2 + currThisVertCount));
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjMesh::applyTransform(const TMatrix & inTm) {
		for (auto & curr : pVertices) {
			inTm.transformPoint(curr.pPosition);
			inTm.transformVector(curr.pNormal);
		}

		//		if (reinterpret_cast<const sts::TMatrixD3 *>(inTm.internalPointer())->isParity()) {
		//			for (auto & vert : pVertices) {
		//				inTm.transformVector(vert.pNormal);
		//				vert.pNormal *= -1.0;
		//			}
		//			for (auto & face : pFaces) {
		//				std::swap(face.pV0, face.pV2);
		//			}
		//		}
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	eObjectType ObjMesh::objType() const {
		return OBJ_MESH;
	}

	/**************************************************************************************************/
	//////////////////////////////////////////* Functions */////////////////////////////////////////////
	/**************************************************************************************************/

	ObjAbstract * ObjMesh::clone() const {
		return new ObjMesh(*this);
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
