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

#include "xpln/obj/ObjSmoke.h"
#include "xpln/obj/Transform.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ObjSmoke::ObjSmoke(const ObjSmoke & copy)
    : ObjAbstract(copy),
      mSize(copy.mSize),
      mPosition(copy.mPosition),
      mSmokeType(copy.mSmokeType) { }

ObjSmoke::ObjSmoke() {
    setObjectName(String("Smoke"));
}

ObjSmoke::~ObjSmoke() { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjSmoke::setPosition(const Point3 & pos) {
    mPosition = pos;
}

const Point3 & ObjSmoke::position() const {
    return mPosition;
}

void ObjSmoke::setSize(float size) {
    mSize = size;
}

float ObjSmoke::size() const {
    return mSize;
}

void ObjSmoke::setSmokeType(const eSmokeType type) {
    mSmokeType = type;
}

ObjSmoke::eSmokeType ObjSmoke::smokeType() const {
    return mSmokeType;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

eObjectType ObjSmoke::objType() const {
    return OBJ_SMOKE;
}

void ObjSmoke::applyTransform(const TMatrix & tm, const bool) {
    Point3 pos = mPosition;
    tm.transformPoint(pos);
    mPosition = pos;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ObjAbstract * ObjSmoke::clone() const {
    return new ObjSmoke(*this);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
