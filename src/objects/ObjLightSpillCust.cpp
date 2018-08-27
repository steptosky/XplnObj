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

#include "xpln/obj/ObjLightSpillCust.h"
#include <cmath>

namespace xobj {

/********************************************************************************************************/
///////////////////////////////////////* Constructors/Destructor *////////////////////////////////////////
/********************************************************************************************************/

ObjLightSpillCust::ObjLightSpillCust(const ObjLightSpillCust & copy)
    : ObjAbstractLight(copy),
      mSize(copy.mSize),
      mSemi(copy.mSemi),
      mColor(copy.mColor),
      mDirection(copy.mDirection),
      mDataRef(copy.mDataRef) {}

ObjLightSpillCust::ObjLightSpillCust()
    : mSize(10.0f),
      mSemi(0.0f) {

    setObjectName("Light Spill Custom");
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjLightSpillCust::setSemiAngle(const float radians) {
    mSemi = std::cos(radians / 2.0f);
}

float ObjLightSpillCust::semiAngle() const {
    return std::acos(mSemi) * 2.0f;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjLightSpillCust::applyTransform(const TMatrix & tm, const bool) {
    Point3 pos = mPosition;
    tm.transformPoint(pos);
    mPosition = pos;

    Point3 dir = direction();
    tm.transformVector(dir);
    setDirection(dir);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

eObjectType ObjLightSpillCust::objType() const {
    return OBJ_LIGHT_SPILL_CUSTOM;
}

Point3 ObjLightSpillCust::direction() const {
    return mDirection;
}

void ObjLightSpillCust::setDirection(const Point3 & direction) {
    mDirection = direction;
    mDirection.normalize();
}

void ObjLightSpillCust::setColor(const Color & color) {
    mColor = color;
}

Color ObjLightSpillCust::color() const {
    return mColor;
}

float ObjLightSpillCust::semiRaw() const {
    return mSemi;
}

void ObjLightSpillCust::setSemiRaw(const float semi) {
    mSemi = semi;
}

float ObjLightSpillCust::size() const {
    return mSize;
}

void ObjLightSpillCust::setSize(const float size) {
    mSize = size;
}

const std::string & ObjLightSpillCust::dataRef() const {
    return mDataRef;
}

void ObjLightSpillCust::setDataRef(const std::string & dataRef) {
    mDataRef = dataRef;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ObjAbstract * ObjLightSpillCust::clone() const {
    return new ObjLightSpillCust(*this);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
