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

#include "ObjAbstract.h"
#include "MeshVertex.h"
#include "MeshFace.h"

#include "xpln/obj/attributes/AttrSet.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details Representation of the geometry mesh object
	 * \ingroup Objects
	 */
	class ObjMesh : public ObjAbstract {

		ObjMesh & operator =(const ObjMesh &) = delete;

	protected:

		XpObjLib ObjMesh(const ObjMesh & copy);

	public:

		typedef MeshVertex Vertex;
		typedef MeshFace Face;
		typedef std::vector<MeshVertex> VertexList;
		typedef std::vector<MeshFace> FaceList;

		//-------------------------------------------------------------------------

		XpObjLib ObjMesh();
		XpObjLib virtual ~ObjMesh();

		//-------------------------------------------------------------------------

		/*!
		 * \details Attributes set.
		 */
		AttrSet pAttr;

		/*!
		 * \details Vertices list.
		 */
		VertexList pVertices;

		/*!
		 * \details Faces list.
		 */
		FaceList pFaces;

		//-------------------------------------------------------------------------

		/*!
		 * \details Attaches vertices and faces from another mesh.
		 * \param [in] otherMesh
		 */
		XpObjLib void attach(const ObjMesh & otherMesh);

		/*!
		 * \details Flips mesh normals.
		 */
		XpObjLib void flipNormals();

		/*!
		 * \details It makes mesh copy at the same location and flips its normals.
		 */
		XpObjLib void makeTwoSided();

		//-------------------------------------------------------------------------

		/*! \copydoc ObjAbstract::objType */
		XpObjLib eObjectType objType() const final;

		/*! \copydoc ObjAbstract::applyTransform */
		XpObjLib void applyTransform(const TMatrix & tm, const bool useParity = false) final;

		/* \copydoc ObjAbstract::clone */
		XpObjLib ObjAbstract * clone() const override;

		//-------------------------------------------------------------------------

	private:

		bool mTwoSided = false;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
