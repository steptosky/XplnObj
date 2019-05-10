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
#include "xpln/obj/Transform.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ObjMesh::ObjMesh(const ObjMesh & copy)
    : ObjAbstract(copy),
      mVertices(copy.mVertices),
      mFaces(copy.mFaces) {}

ObjMesh::ObjMesh() {
    setObjectName("Obj Mesh");
}

ObjMesh::~ObjMesh() { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjMesh::attach(const ObjMesh & otherMesh) {
    const size_t vCount = mVertices.size();
    for (auto & currVert : otherMesh.mVertices) {
        mVertices.emplace_back(currVert);
    }
    for (auto & f : otherMesh.mFaces) {
        mFaces.emplace_back(f.mV0 + vCount, f.mV1 + vCount, f.mV2 + vCount);
    }
}

void ObjMesh::flipNormals() {
    for (auto & vert : mVertices) {
        vert.mNormal *= -1.0;
    }
    for (auto & face : mFaces) {
        std::swap(face.mV0, face.mV2);
    }
}

void ObjMesh::makeTwoSided() {
    if (!mIsTwoSided) {
        ObjMesh copy(*this);
        copy.flipNormals();
        attach(copy);
        mIsTwoSided = true;
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjMesh::applyTransform(const TMatrix & tm, const bool useParity) {
    for (auto & curr : mVertices) {
        tm.transformPoint(curr.mPosition);
        tm.transformVector(curr.mNormal);
    }

    if (useParity && tm.parity()) {
        flipNormals();
    }
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
