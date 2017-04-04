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

#pragma once

#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/attributes/AttrSet.h"
#include "gtest/gtest.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	class TestUtilsObjMesh {
	public:

		//-----------------------------------------------------

		static ObjMesh * createPyramidTestMesh(const char * inName, const TMatrix & inMtx) {
			if (!inName) {
				inName = "unnamed test mesh";
			}

			ObjMesh * mesh = new ObjMesh();
			mesh->setObjectName(inName);

			mesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(0.0f, 0.0f, -50.0f),
														Point3(0.0f, 0.894427f, -0.447214f),
														Point2(0.968750f, 0.500000f)));
			inMtx.transformPoint(mesh->pVertices.back().pPosition);
			inMtx.transformVector(mesh->pVertices.back().pNormal);
			mesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(-20.0f, 0.0f, 25.0f),
														Point3(-0.468997f, 0.783273f, 0.408075f),
														Point2(0.031250f, 0.750000f)));
			inMtx.transformPoint(mesh->pVertices.back().pPosition);
			inMtx.transformVector(mesh->pVertices.back().pNormal);
			mesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(0.0f, 25.0f, 0.0f),
														Point3(0.0f, 0.998791f, 0.049158f),
														Point2(0.343750f, 0.500000f)));
			inMtx.transformPoint(mesh->pVertices.back().pPosition);
			inMtx.transformVector(mesh->pVertices.back().pNormal);
			mesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(20.0f, 0.0f, 25.0f),
														Point3(0.468997f, 0.783273f, 0.408075f),
														Point2(0.031250f, 0.250000f)));
			inMtx.transformPoint(mesh->pVertices.back().pPosition);
			inMtx.transformVector(mesh->pVertices.back().pNormal);
			mesh->pFaces.emplace_back(ObjMesh::Face(2, 1, 0));
			mesh->pFaces.emplace_back(ObjMesh::Face(2, 3, 1));
			mesh->pFaces.emplace_back(ObjMesh::Face(2, 0, 3));
			return mesh;
		}

		static ObjMesh * createPyramidTestMesh(const char * inName) {
			return createPyramidTestMesh(inName, TMatrix());
		}

		static ObjMesh * createPyramidTestMesh(const char * inName, const Point3 & inShift) {
			TMatrix tm;
			tm.setPosition(inShift);
			return createPyramidTestMesh(inName, tm);
		}

		static ObjMesh * createPyramidTestMesh(const char * inName, float inRotate) {
			TMatrix tm;
			if (inRotate != 0.0f) {
				tm.rotateDegreesY(inRotate);
			}
			return createPyramidTestMesh(inName, tm);
		}

		static ObjMesh * createPyramidTestMesh(const char * inName, const Point3 & inShift, float inRotate) {
			TMatrix tm;
			if (inRotate != 0.0f) {
				tm.rotateDegreesY(inRotate);
			}
			tm.setPosition(inShift);
			return createPyramidTestMesh(inName, tm);
		}

		//-----------------------------------------------------

		static void compareMesh(const ObjMesh * m1, const ObjMesh * m2) {
			ASSERT_TRUE(m1 != nullptr);
			ASSERT_TRUE(m2 != nullptr);
			ASSERT_STREQ(m1->objectName().c_str(), m2->objectName().c_str());
			ASSERT_TRUE(m1->pVertices == m2->pVertices);
			ASSERT_TRUE(m1->pFaces == m2->pFaces);
		}

		static ObjMesh * createObjMesh(const char * inName, float inValShift) {
			ObjMesh * outMesh = new ObjMesh();

			outMesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(-1.0f, -1.0f, 0.0f) + inValShift,
															Point3(1.0f, 0.0f, 0.0f),
															Point2(0.0f, 0.0f) + inValShift));

			outMesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(1.0f, 1.0f, 0.0f) + inValShift,
															Point3(0.0f, 1.0f, 0.0f),
															Point2(0.0f, 0.0f) + inValShift));

			outMesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(1.0f, -1.0f, 0.0f) + inValShift,
															Point3(0.0f, 0.0f, 1.0f),
															Point2(0.0f, 0.0f) + inValShift));

			outMesh->pVertices.emplace_back(ObjMesh::Vertex(Point3(-1.0f, 1.0f, 0.0f) + inValShift,
															Point3(0.0f, 1.0f, 0.0f),
															Point2(0.0f, 0.0f) + inValShift));
			outMesh->pFaces.push_back(MeshFace(0, 1, 2));
			outMesh->pFaces.push_back(MeshFace(0, 2, 3));
			if (inName) {
				outMesh->setObjectName(inName);
			}
			return outMesh;
		}

		//-----------------------------------------------------

		static void compareMeshAttributes(const ObjMesh * m1, const ObjMesh * m2) {
			ASSERT_EQ(m1->pAttr, m2->pAttr);
		}

		static void compareMeshData(const ObjMesh * m1, const ObjMesh * m2) {
			ASSERT_TRUE(m1->pVertices == m2->pVertices);
			ASSERT_TRUE(m1->pFaces == m2->pFaces);
		}

		static ObjMesh * createObjMeshNotDefaultAttributes1(const char * inName, float inValShift) {
			ObjMesh * outMesh = createObjMesh2StatesNotDefaultAttributes(inName, inValShift);
			outMesh->pAttr.setBlend(AttrBlend(AttrBlend::no_blend, 0.2f));
			outMesh->pAttr.setHard(AttrHard(ESurface(ESurface::concrete), true));
			outMesh->pAttr.setCockpit(AttrCockpit(AttrCockpit::cockpit));
			return outMesh;
		}

		static ObjMesh * createObjMeshNotDefaultAttributes2(const char * inName, float inValShift) {
			ObjMesh * outMesh = createObjMesh2StatesNotDefaultAttributes(inName, inValShift);
			outMesh->pAttr.setBlend(AttrBlend(AttrBlend::shadow_blend, 0.2f));
			outMesh->pAttr.setHard(AttrHard(ESurface(ESurface::concrete), false));
			outMesh->pAttr.setCockpit(AttrCockpit(AttrCockpit::region_1));
			return outMesh;
		}

	private:

		static ObjMesh * createObjMesh2StatesNotDefaultAttributes(const char * inName, float inValShift) {
			ObjMesh * outMesh = createObjMesh(inName, inValShift);
			outMesh->pAttr.setDraw(false);
			outMesh->pAttr.setDraped(true);
			outMesh->pAttr.setCastShadow(false);
			outMesh->pAttr.setSolidForCamera(true);

			outMesh->pAttr.setPolyOffset(AttrPolyOffset(1.0f));
			outMesh->pAttr.setShiny(AttrShiny(0.8f));
			outMesh->pAttr.setLightLevel(AttrLightLevel(0.3f, 0.8f, "dataref"));
			outMesh->pAttr.setCockpit(AttrCockpit(AttrCockpit::region_2));
			return outMesh;
		}

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
